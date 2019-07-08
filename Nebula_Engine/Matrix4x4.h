#pragma once

#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"

namespace NE
{
	class Matrix4x4
	{
	private:
		float n[4][4];

	public:

		//! Standard initialization for a 4x4 matrix
		//! Sets the matrix to an identity matrix
		Matrix4x4()
		{
			Identity();
		}

		//! Initializes the matrix with 16 different values for the variables
		//! n00 stands for the coord
		//! Insert numbers from left to right and top to bottom
		Matrix4x4(float n00, float n01, float n02, float n03,
			float n10, float n11, float n12, float n13,
			float n20, float n21, float n22, float n23,
			float n30, float n31, float n32, float n33)
		{
			n[0][0] = n00;
			n[0][1] = n01;
			n[0][2] = n02;
			n[0][3] = n03;

			n[1][0] = n10;
			n[1][1] = n11;
			n[1][2] = n12;
			n[1][3] = n13;

			n[2][0] = n20;
			n[2][1] = n21;
			n[2][2] = n22;
			n[2][3] = n23;

			n[3][0] = n30;
			n[3][1] = n31;
			n[3][2] = n32;
			n[3][3] = n33;
		}

		//! Get the value at index i and j
		//! @param i Insert the i'th number for the coord as int
		//! @param j Insert the j'th number for the coord as int
		//! @return Returns the value of i-j as float
		float& operator()(int i, int j)
		{
			return n[i][j];
		}

		//! Get the value at index i and j
		//! @param i Insert the i'th number for the coord as int
		//! @param j Insert the j'th number for the coord as int
		//! @return Returns the value of i-j as const float
		const float& operator()(int i, int j) const
		{
			return n[i][j];
		}

		//! Get the vector3 in the j'th column
		//! @param j Insert column number as int
		//! @return Returns vector of the column as NE::Vector3
		//! @see NE::Vector3
		NE::Vector3& operator()(int j)
		{
			return NE::Vector3(n[j][0], n[j][1], n[j][2]);
		}

		//! Get the vector4 in the j'th column
		//! @param j Insert column number as int
		//! @return Returns vector of the column as NE::Vector4
		//! @see NE::Vector4
		const NE::Vector4& operator()(int j) const
		{
			return (*reinterpret_cast<const NE::Vector4*>(n[j]));
		}

		//! Multiply the matrix with another 4x4 matrix
		//! @param B Insert the other 4x4 matrix as const NE::Matrix4x4&
		//! @return Returns the new 4x4 Matrix as NE::Matrix4x4
		Matrix4x4& operator *(const Matrix4x4& B)
		{
			return Matrix4x4((0, 0) * B(0, 0) + (0, 0) * B(1, 0) + (0, 0) * B(2, 0) + (0, 0) * B(3, 0),
				(0, 1) * B(0, 1) + (0, 1) * B(1, 1) + (0, 1) * B(2, 1) + (0, 1) * B(3, 1),
				(0, 2) * B(0, 2) + (0, 2) * B(1, 2) + (0, 2) * B(2, 2) + (0, 2) * B(3, 2),
				(0, 3) * B(0, 3) + (0, 3) * B(1, 3) + (0, 3) * B(2, 3) + (0, 3) * B(3, 3),

				(1, 0) * B(0, 0) + (1, 0) * B(1, 0) + (1, 0) * B(2, 0) + (1, 0) * B(3, 0),
				(1, 1) * B(0, 1) + (1, 1) * B(1, 1) + (1, 1) * B(2, 1) + (1, 1) * B(3, 1),
				(1, 2) * B(0, 2) + (1, 2) * B(1, 2) + (1, 2) * B(2, 2) + (1, 2) * B(3, 2),
				(1, 3) * B(0, 3) + (1, 3) * B(1, 3) + (1, 3) * B(2, 3) + (1, 3) * B(3, 3),

				(2, 0) * B(0, 0) + (2, 0) * B(1, 0) + (2, 0) * B(2, 0) + (2, 0) * B(3, 0),
				(2, 1) * B(0, 1) + (2, 1) * B(1, 1) + (2, 1) * B(2, 1) + (2, 1) * B(3, 1),
				(2, 2) * B(0, 2) + (2, 2) * B(1, 2) + (2, 2) * B(2, 2) + (2, 2) * B(3, 2),
				(2, 3) * B(0, 3) + (2, 3) * B(1, 3) + (2, 3) * B(2, 3) + (2, 3) * B(3, 3),

				(3, 0) * B(0, 0) + (3, 0) * B(1, 0) + (3, 0) * B(2, 0) + (3, 0) * B(3, 0),
				(3, 1) * B(0, 1) + (3, 1) * B(1, 1) + (3, 1) * B(2, 1) + (3, 1) * B(3, 1),
				(3, 2) * B(0, 2) + (3, 2) * B(1, 2) + (3, 2) * B(2, 2) + (3, 2) * B(3, 2),
				(3, 3) * B(0, 3) + (3, 3) * B(1, 3) + (3, 3) * B(2, 3) + (3, 3) * B(3, 3));
		}

		//! Adds the matrix to another 4x4 matrix
		//! @param B Insert the other 4x4 matrix as const NE::Matrix3x3&
		//! @return Returns the new 4x4 Matrix as NE::Matrix4x4&
		Matrix4x4& operator +(const Matrix4x4& B)
		{
			return Matrix4x4((0, 0) + B(0, 0),
				(0, 1) + B(0, 1),
				(0, 2) + B(0, 2),
				(0, 3) + B(0, 3),

				(1, 0) + B(1, 0),
				(1, 1) + B(1, 1),
				(1, 2) + B(1, 2),
				(1, 3) + B(1, 3),

				(2, 0) + B(2, 0),
				(2, 1) + B(2, 1),
				(2, 2) + B(2, 2),
				(2, 3) + B(2, 3),

				(3, 0) + B(3, 0),
				(3, 1) + B(3, 1),
				(3, 2) + B(3, 2),
				(3, 3) + B(3, 3));
		}

		//! Subtracts the matrix to another 4x4 matrix
		//! @param B Insert the other 4x4 matrix as const NE::Matrix4x4&
		//! @return Returns the new 4x4 Matrix as NE::Matrix4x4&
		Matrix4x4& operator -(const Matrix4x4& B)
		{
			return Matrix4x4((0, 0) - B(0, 0),
				(0, 1) - B(0, 1),
				(0, 2) - B(0, 2),
				(0, 3) - B(0, 3),

				(1, 0) - B(1, 0),
				(1, 1) - B(1, 1),
				(1, 2) - B(1, 2),
				(1, 3) - B(1, 3),

				(2, 0) - B(2, 0),
				(2, 1) - B(2, 1),
				(2, 2) - B(2, 2),
				(2, 3) - B(2, 3),

				(3, 0) - B(3, 0),
				(3, 1) - B(3, 1),
				(3, 2) - B(3, 2),
				(3, 3) - B(3, 3));
		}

		//! Multiplies the matrix with a 4D Vector
		//! @param v Insert the other vector as const NE::Vector4&
		//! @return Returns the new vector as NE::Vector4&
		NE::Vector4& operator *(const NE::Vector4& v)
		{
			return (NE::Vector4((0, 0) * v.x + (0, 1) * v.x + (0, 2) * v.x + (0, 3) * v.x,
				(1, 0) * v.y + (1, 1) * v.y + (1, 2) * v.y + (1, 3) * v.y,
				(2, 0) * v.z + (2, 1) * v.z + (2, 2) * v.z + (2, 3) * v.x,
				(3, 0) * v.w + (3, 1) * v.w + (3, 2) * v.w + (3, 3) * v.w));
		}

		//! Set the current Matrix to an identity matrix
		void Identity()
		{
			for (int y = 0; y < 4; y++)
			{
				for (int x = 0; x < 4; x++)
				{
					n[x][y] = 0.0f;
				}
			}
			n[0][0] = 1.0f;
			n[1][1] = 1.0f;
			n[2][2] = 1.0f;
			n[3][3] = 1.0f;
		}

	};
}