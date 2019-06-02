#pragma once

#include "Vector2.h"
#include "Vector3.h"

namespace NE
{
	class Matrix3x3
	{
	private:
		float n[3][3];

	public:

		//! Standard initialization for a 3x3 matrix
		//! Sets the matrix to an identity matrix
		Matrix3x3()
		{
			Identity();
		}

		//! Initializes the matrix with 9 different values for the variables
		//! @param n00 The value for the n0-0 value
		//! @param n01 The value for the n0-1 value
		//! @param n02 The value for the n0-2 value
		//! @param n10 The value for the n1-0 value
		//! @param n11 The value for the n1-1 value
		//! @param n12 The value for the n1-2 value
		//! @param n20 The value for the n2-0 value
		//! @param n21 The value for the n2-1 value
		//! @param n22 The value for the n2-2 value
		Matrix3x3(float n00, float n01, float n02,
			float n10, float n11, float n12,
			float n20, float n21, float n22)
		{
			n[0][0] = n00;
			n[0][1] = n01;
			n[0][2] = n02;

			n[1][0] = n10;
			n[1][1] = n11;
			n[1][2] = n12;

			n[2][0] = n20;
			n[2][1] = n21;
			n[2][2] = n22;
		}

		//! Get the value at index i and j
		//! @param i Insert the i'th number for the coord as int
		//! @param j Insert the j'th number for the coord as int
		//! @return Returns the value of i-j as float
		float operator()(int i, int j)
		{
			return n[i][j];
		}

		//! Get the value at index i and j
		//! @param i Insert the i'th number for the coord as int
		//! @param j Insert the j'th number for the coord as int
		//! @return Returns the value of i-j as const float
		const float operator()(int i, int j) const
		{
			return n[i][j];
		}

		//! Get the vector3 in the j'th column
		//! @param j Insert column number as int
		//! @return Returns vector of the column as NE::Vector3
		//! @see NE::Vector3
		NE::Vector3& operator ()(int j)
		{
			return (*reinterpret_cast<NE::Vector3*>(n[j]));
		}

		//! Get the vector3 in the j'th column
		//! @param j Insert column number as int
		//! @return Returns vector of the column as const NE::Vector3
		//! @see NE::Vector3
		const NE::Vector3& operator()(int j) const
		{
			return (*reinterpret_cast<const NE::Vector3*>(n[j]));
		}

		//! Multiply the matrix with another 3x3 matrix
		//! @param B Insert the other 3x3 matrix as const NE::Matrix3x3&
		//! @return Returns the new 3x3 Matrix as NE::Matrix3x3
		Matrix3x3& operator *(const Matrix3x3& B)
		{
			return Matrix3x3((0, 0) * B(0, 0) + (1, 0) * B(0, 1) + (2, 0) * B(0, 2),
				(0, 0) * B(0, 1) + (1, 0) * B(1, 1) + (0, 0) * B(2, 1),
				(0, 0) * B(0, 2) + (1, 0) * B(1, 2) + (0, 0) * B(2, 2),
				//--------
				(0, 1) * B(0, 0) + (1, 1) * B(0, 1) + (1, 2) * B(0, 2),
				(0, 1) * B(1, 0) + (1, 1) * B(1, 1) + (2, 1) * B(1, 2),
				(0, 1) * B(2, 0) + (1, 1) * B(2, 1) + (2, 1) * B(2, 2),
				//--------
				(0, 2) * B(0, 0) + (0, 2) * B(0, 1) + (0, 2) * B(0, 2),
				(1, 2) * B(1, 0) + (1, 2) * B(1, 1) + (1, 2) * B(1, 2),
				(2, 2) * B(2, 0) + (2, 2) * B(2, 1) + (2, 2) * B(2, 2));
		}
		//! Adds the matrix to another 3x3 matrix
		//! @param B Insert the other 3x3 matrix as const NE::Matrix3x3&
		//! @return Returns the new 3x3 Matrix as NE::Matrix3x3
		Matrix3x3& operator +(const Matrix3x3& B)
		{
			return Matrix3x3((0, 0) + B(0, 0),
				(0, 1) + B(0, 1),
				(0, 2) + B(0, 2),

				(1, 0) + B(1, 0),
				(1, 1) + B(1, 1),
				(1, 2) + B(1, 2),

				(2, 0) + B(2, 0),
				(2, 1) + B(2, 1),
				(2, 2) + B(2, 2));
		}
		//! Subtracts the matrix to another 3x3 matrix
		//! @param B Insert the other 3x3 matrix as const NE::Matrix3x3&
		//! @return Returns the new 3x3 Matrix as NE::Matrix3x3
		Matrix3x3& operator -(const Matrix3x3& B)
		{
			return Matrix3x3((0, 0) - B(0, 0),
				(0, 1) - B(0, 1),
				(0, 2) - B(0, 2),

				(1, 0) - B(1, 0),
				(1, 1) - B(1, 1),
				(1, 2) - B(1, 2),

				(2, 0) - B(2, 0),
				(2, 1) - B(2, 1),
				(2, 2) - B(2, 2));
		}

		//! Multiplies the matrix with a 3D Vector
		//! @param v Insert the other vector as const NE::Vector3&
		//! @return Returns the new vector as NE::Vector3&
		NE::Vector3& operator *(const NE::Vector3& v)
		{
			return (NE::Vector3((0, 0) * v.x + (0, 1) * v.x + (0, 2) * v.x,
				(1, 0) * v.y + (1, 1) * v.y + (1, 2) * v.y,
				(2, 0) * v.z + (2, 1) * v.z + (2, 2) * v.z));
		}

		//! Set the current Matrix to an identity matrix
		void Identity()
		{
			for (int y = 0; y < 3; y++)
			{
				for (int x = 0; x < 3; x++)
				{
					n[x][y] = 0.0f;
				}
			}
			n[0][0] = 1.0f;
			n[1][1] = 1.0f;
			n[2][2] = 1.0f;
		}
	};
}