#include "Window.h"

#include <stdexcept>

Window::Window()
{
	width = 800;
	height = 600;
}

Window::Window(int windowWidth, int windowHeight)
{
	width = windowWidth;
	height = windowHeight;
}

void Window::framebuffer_size_callback(GLFWwindow * window, int width, int height)
{
	glViewport(0, 0, width, height);
}

NE_ERROR Window::Initialise()
{
	if (!glfwInit())
	{
		printf("Error Initialising GLFW");
		glfwTerminate();
		return NE_FATAL;
	}

	glfwDefaultWindowHints();

	if(msaa)
		glfwWindowHint(GLFW_SAMPLES, msaaFilters);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	mainWindow = glfwCreateWindow(width, height, "Nebula Engine", NULL, NULL);
	if (!mainWindow)
	{
		printf("Unable to create GLFW Window!");
		glfwTerminate();
		return NE_FATAL;
	}

	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);
	glfwMakeContextCurrent(mainWindow);

	// Enable V-Sync
	if(vsync)
		glfwSwapInterval(1);
	else
		glfwSwapInterval(0);

	createCallbacks();
	
	if (showMouse)
		glfwSetInputMode(mainWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	else
		glfwSetInputMode(mainWindow, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

	// Allow modern extension access
	glewExperimental = GL_TRUE;

	GLenum error = glewInit();
	if (error != GLEW_OK)
	{
		printf("Error: %s", glewGetErrorString(error));
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return NE_FATAL;
	}

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_MULTISAMPLE);

	glViewport(0, 0, bufferWidth, bufferHeight);

	glfwSetWindowUserPointer(mainWindow, this);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	glFrontFace(GL_CW);

	previousTime = glfwGetTime();
	return NE_OK;
}

int Window::GetWindowWidth()
{
	return width;
}

int Window::GetWindowHeight()
{
	return height;
}

int Window::GetFPS()
{
	return fps;
}

float Window::GetDeltaTime()
{
	return deltaTime;
}

bool Window::GetShouldClose()
{
	return glfwWindowShouldClose(mainWindow);
}

void Window::SetWireframe(bool value)
{
	if(value)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	wireframe = value;
}

bool Window::GetWireframe()
{
	return wireframe;
}

float Window::GetTime()
{
	return glfwGetTime();
}

void Window::createCallbacks()
{
	glfwSetCursorPosCallback(mainWindow, HandleMouse);
}

void Window::ShowMouse(bool value)
{
	if(value)
		glfwSetInputMode(mainWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	else
		glfwSetInputMode(mainWindow, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
}

void Window::SwitchMouse()
{
	if (showMouse)
		showMouse = false;
	else
		showMouse = true;
}

void Window::SetRefreshRate(int value)
{
	glfwWindowHint(GLFW_REFRESH_RATE, value);
}

int Window::GetRefreshRate()
{
	return refreshRate;
}

bool Window::GetShowMouse()
{
	return showMouse;
}

void Window::SetPerspectiveMode(int x)
{
	if (x == 0 || x == 1)
		perspectiveMode = x;
}

int Window::GetPerspectiveMode()
{
	return perspectiveMode;
}

glm::mat4 Window::CalculateProjectionMatrix(float fovy, float aspect, float zNear, float zFar)
{
	if (perspectiveMode == 0)
	{
		glm::mat4 perspective = glm::mat4();
		
		//perspective = glm::perspective(fovy, aspect, -1.0f, 1.0f);

		perspective[2][2] = 0.0f;

		return glm::mat4();
	}
	else
		return glm::perspective(fovy, aspect, zNear, zFar);
}

void Window::CloseWindow()
{
	glfwSetWindowShouldClose(mainWindow, 1);
}

void Window::SetIcon(std::string file)
{
	int iconHeight, iconWidth;
	unsigned char *texData = stbi_load(file.c_str(), &iconWidth, &iconHeight, NULL, 0);
	if (!texData)
	{
		printf("Unable to find: %s", file);
	}
	
	GLFWimage image;
	image.height = iconHeight;
	image.width = iconWidth;
	image.pixels = texData;
	glfwSetWindowIcon(mainWindow, 1, &image);
	delete texData;
}

void Window::SetMsaa(bool value, int filters)
{
	msaa = value;
	msaaFilters = filters;
}

bool Window::GetMsaa()
{
	return msaa;
}

void Window::SetTitle(std::string title)
{
	glfwSetWindowTitle(mainWindow, title.c_str());
}

void Window::SetVSync(bool value)
{
	vsync = value;
}

void Window::SwitchVSync()
{
	if (vsync)
		vsync = false;
	else
		vsync = true;
}

bool Window::GetVSync()
{
	return vsync;
}

float Window::GetXChange()
{
	float theChange = xChange;
	xChange = 0.0f;
	return theChange;
}

float Window::GetYChange()
{
	float theChange = yChange;
	yChange = 0.0f;
	return theChange;
}

bool Window::Key(KeyCode key)
{
	if (glfwGetKey(mainWindow, key) == GLFW_PRESS)
		return true;
	else
		return false;
}

bool Window::Key(KeyCode key, KeyAction action)
{
	if (glfwGetKey(mainWindow, key) == action)
		return true;
	else
		return false;
}

void Window::WindowUpdate()
{
	glfwPollEvents();

	// Change VSync
	int x = vsync ? 1 : 0;
	glfwSwapInterval(x);

	// DeltaTime
	float now = glfwGetTime();
	deltaTime = now - lastTime;
	lastTime = now;

	// FPS
	float currentTime = glfwGetTime();
	frameCount++;
	if (currentTime - previousTime >= 1.0f)
	{
		fps = frameCount;
		frameCount = 0;
		previousTime = currentTime;
	}

	// Get current window size
	glfwGetWindowSize(mainWindow, &width, &height);
	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

	if(Window::Key(Window::KeyCode::Escape, KeyDown))
		glfwSetWindowShouldClose(mainWindow, GL_TRUE);
}

void Window::HandleMouse(GLFWwindow* window, double xPos, double yPos)
{
	Window* glfwwindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

	if (glfwwindow->mouseFirstMoved)
	{
		glfwwindow->lastX = xPos;
		glfwwindow->lastY = yPos;
		glfwwindow->mouseFirstMoved = false;
	}

	glfwwindow->xChange = xPos - glfwwindow->lastX;
	glfwwindow->yChange = glfwwindow->lastY - yPos;

	glfwwindow->lastX = xPos;
	glfwwindow->lastY = yPos;
}

void Window::SwapBuffers()
{
	glfwSwapBuffers(mainWindow);
}

Window::~Window()
{
	glfwDestroyWindow(mainWindow);
	glfwTerminate();
}