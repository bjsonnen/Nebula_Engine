#pragma once

#include "Vector2.h"

namespace NE
{
	class Matrix2x2
	{
	private:
		float n[2][2];

	public:
		//! Standard initialization for a 2x2 matrix
		//! Sets the matrix to an identity matrix
		Matrix2x2()
		{
			Identity();
		}

		//! Initializes the matrix with 4 different values for the variables
		//! @param n00 The value for the n0-0 value
		//! @param n01 The value for the n0-1 value
		//! @param n10 The value for the n1-0 value
		//! @param n11 The value for the n1-1 value
		Matrix2x2(float n00, float n01,
			float n10, float n11)
		{
			n[0][0] = n00;
			n[0][1] = n01;

			n[1][0] = n10;
			n[1][1] = n11;
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
		//! @see NE::Vector2
		NE::Vector2& operator ()(int j)
		{
			return (*reinterpret_cast<NE::Vector2*>(n[j]));
		}

		//! Get the vector3 in the j'th column
		//! @param j Insert column number as int
		//! @return Returns vector of the column as const NE::Vector3
		//! @see NE::Vector2
		const NE::Vector2& operator()(int j) const
		{
			return (*reinterpret_cast<const NE::Vector2*>(n[j]));
		}

		//! Multiply the matrix with another 2x2 matrix
		//! @param B Insert the other 2x2 matrix as const NE::Matrix2x2&
		//! @return Returns the new 2x2 Matrix as NE::Matrix2x2&
		Matrix2x2& operator *(const Matrix2x2& B)
		{
			return Matrix2x2((0, 0) * B(0, 0) + (1, 0) * B(0, 1) + (2, 0) * B(0, 2),
				(0, 0) * B(0, 1) + (1, 0) * B(1, 1) + (0, 0) * B(2, 1),
				//--------
				(0, 1) * B(0, 0) + (1, 1) * B(0, 1) + (1, 2) * B(0, 2),
				(0, 1) * B(1, 0) + (1, 1) * B(1, 1) + (2, 1) * B(1, 2));
		}

		//! Adds the matrix to another 2x2 matrix
		//! @param B Insert the other 2x2 matrix as const NE::Matrix2x2&
		//! @return Returns the new 2x2 Matrix as NE::Matrix2x2&
		Matrix2x2& operator +(const Matrix2x2& B)
		{
			return Matrix2x2((0, 0) + B(0, 0),
				(0, 1) + B(0, 1),

				(1, 0) + B(1, 0),
				(1, 1) + B(1, 1));
		}

		//! Subtracts the matrix to another 2x2 matrix
		//! @param B Insert the other 2x2 matrix as const NE::Matrix2x2&
		//! @return Returns the new 2x2 Matrix as NE::Matrix2x2&
		Matrix2x2& operator -(const Matrix2x2& B)
		{
			return Matrix2x2((0, 0) - B(0, 0),
				(0, 1) - B(0, 1),

				(1, 0) - B(1, 0),
				(1, 1) - B(1, 1));
		}

		//! Multiplies the matrix with a 2D Vector
		//! @param v Insert the other vector as const NE::Vector2&
		//! @return Returns the new vector as NE::Vector2&
		NE::Vector2& operator *(const NE::Vector2& v)
		{
			return (NE::Vector2((0, 0) * v.x + (0, 1) * v.x + (0, 2) * v.x,
								(1, 0) * v.y + (1, 1) * v.y + (1, 2) * v.y));
		}

		//! Set the current Matrix to an identity matrix
		void Identity()
		{
			for (int y = 0; y < 2; y++)
			{
				for (int x = 0; x < 2; x++)
				{
					n[x][y] = 0.0f;
				}
			}
			n[0][0] = 1.0f;
			n[1][1] = 1.0f;
		}
	};
}