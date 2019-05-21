#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D hdrBuffer;
uniform bool hdr;
uniform float exposure;

void main()
{             
    const float gamma = 2.2;
    vec3 hdrColor = texture(hdrBuffer, TexCoords).rgb;
    if(hdr)
    {
        // reinhard
        // vec3 result = hdrColor / (hdrColor + vec3(1.0));
        // exposure
        vec3 result = vec3(1.0) - exp(-hdrColor * exposure);
        // also gamma correct while we're at it       
        result = pow(result, vec3(1.0 / gamma));
        FragColor = vec4(result, 1.0);
    }
    else
    {
        vec3 result = pow(hdrColor, vec3(1.0 / gamma));
        FragColor = vec4(result, 1.0);
    }
	
	if(textureSize(hdrBuffer, 0).x > 0)
		FragColor = vec4(1.0, 0.0, 0.0, 1.0);
	//if(textureSize(hdrBuffer, 0).x > 0)
		//FragColor = vec4(texture(hdrBuffer, TexCoords).rgb, 1.0);
	//else
		//FragColor = vec4(1.0, 0.0, 0.0, 1.0);
	
	vec3 texColor = texture(hdrBuffer, TexCoords).rgb;
	if(texColor.r == 0.0 && texColor.g == 0.0 && texColor.b == 0.0)
		FragColor = vec4(1.0, 0.0, 0.0, 1.0);
	//FragColor = vec4(texture(hdrBuffer, TexCoords).rgb * 2.0, 1.0);
	
}