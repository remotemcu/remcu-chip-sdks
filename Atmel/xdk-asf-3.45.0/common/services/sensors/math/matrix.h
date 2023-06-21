/**
 * \file
 *
 * \brief This module defines a collection of matrix classes.
 *
 * Copyright (c) 2011-2018 Microchip Technology Inc. and its subsidiaries.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Subject to your compliance with these terms, you may use Microchip
 * software and any derivatives exclusively with Microchip products.
 * It is your responsibility to comply with third party license terms applicable
 * to your use of third party software (including open source software) that
 * may accompany Microchip software.
 *
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE,
 * INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY,
 * AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT WILL MICROCHIP BE
 * LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, INCIDENTAL OR CONSEQUENTIAL
 * LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND WHATSOEVER RELATED TO THE
 * SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS BEEN ADVISED OF THE
 * POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE FULLEST EXTENT
 * ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN ANY WAY
 * RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
 * THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * \asf_license_stop
 *
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#ifndef _MATRIX_MATH_H_
#define _MATRIX_MATH_H_

#include "vector.h"

namespace math {

/** \brief 3-Dimensional Matrix Class */
class matrix3d {
private:

	/** \brief column vector storage */
	vector3d  C[3];

public:

	/** \name class construction and destruction */
	/** @{ */
	matrix3d () {}

	matrix3d
		(const vector3d & c0,
		 const vector3d & c1,
		 const vector3d & c2)
		{ C[0] = c0; C[1] = c1; C[2] = c2; }

	matrix3d
		(scalar m11, scalar m12, scalar m13,
		 scalar m21, scalar m22, scalar m23,
		 scalar m31, scalar m32, scalar m33)
		{
		C[0] = vector3d (m11, m21, m31);
		C[1] = vector3d (m12, m22, m32);
		C[2] = vector3d (m13, m23, m33);
		}

	/* this ctor is not intended to be an implied type converter */
	explicit matrix3d
		(const scalar * m)
		{
		C[0] = vector3d (m[0], m[3], m[6]);
		C[1] = vector3d (m[1], m[4], m[7]);
		C[2] = vector3d (m[2], m[5], m[8]);
		}
	/** @} */

	const matrix3d adjoint () const;
	const matrix3d inverse () const;

	const scalar determinant () const
		{ return C[0].dot (C[1].cross (C[2])); }

	void  identity ()
	{
		C[0] = vector3d (1, 0, 0);
		C[1] = vector3d (0, 1, 0);
		C[2] = vector3d (0, 0, 1);
	}

	void  transpose ()
	{
		matrix3d const m (*this);

		C[0] = vector3d (m.C[0][0], m.C[1][0], m.C[2][0]);
		C[1] = vector3d (m.C[0][1], m.C[1][1], m.C[2][1]);
		C[2] = vector3d (m.C[0][2], m.C[1][2], m.C[2][2]);
	}

	void  zero () { C[2] = C[1] = C[0] = vector3d (0, 0, 0); }

	/** \name class member operators */
	/** @{ */
	scalar & operator() (int i, int j)
	{
		return C[j][i];
	}
	
	const scalar & operator() (int i, int j) const
	{
		return C[j][i];
	}

	const vector3d operator * (const vector3d & v) const
		{ return ((C[0] * v.x) + (C[1] * v.y) + (C[2] * v.z)); }

	const matrix3d & operator += (const matrix3d & b)
	{
		C[0] += b.C[0]; C[1] += b.C[1]; C[2] += b.C[2];
		return *this;
	}

	const matrix3d & operator -= (const matrix3d & b)
	{
		C[0] -= b.C[0]; C[1] -= b.C[1]; C[2] -= b.C[2];
		return *this;
	}

	const matrix3d & operator *= (const matrix3d & b)
	{
		matrix3d const m (*this);

		C[0] = m * b.C[0]; C[1] = m * b.C[1]; C[2] = m * b.C[2];
		return *this;
	}

	const matrix3d & operator *= (const scalar & s)
	{
		C[0] *= s; C[1] *= s; C[2] *= s;
		return *this;
	}

	const matrix3d operator + (const matrix3d & m) const
		{ return matrix3d (C[0] + m.C[0], C[1] + m.C[1], C[2] + m.C[2]); }

	const matrix3d operator - (const matrix3d & m) const
		{ return matrix3d (C[0] - m.C[0], C[1] - m.C[1], C[2] - m.C[2]); }

	const matrix3d operator * (const matrix3d & m) const
		{
		return matrix3d ((*this) * m.C[0], (*this) * m.C[1], (*this) * m.C[2]);
		}
	/** @} */

	/** \name class friend operators */
	/** @{ */
	friend const matrix3d operator * (const scalar & s, const matrix3d & A)
		{ return (matrix3d (A) *= s); }

	friend const matrix3d operator - (const matrix3d & A)
		{ return (matrix3d (A) *= -1); }
	/** @} */
};


/** \brief 4-Dimensional Matrix Class */
class matrix4d {

private:

	/** \brief column vector storage */
	vector4d C[4];

public:

	/** \name class construction and destruction */
	/** @{ */
	matrix4d () {}

	matrix4d
		(const vector4d & c0,
		 const vector4d & c1,
		 const vector4d & c2,
		 const vector4d & c3)
		{ C[0] = c0; C[1] = c1; C[2] = c2; C[3] = c3; }

	matrix4d
		(scalar m11, scalar m12, scalar m13, scalar m14,
		 scalar m21, scalar m22, scalar m23, scalar m24,
		 scalar m31, scalar m32, scalar m33, scalar m34,
		 scalar m41, scalar m42, scalar m43, scalar m44)
		{
		C[0] = vector4d (m11, m21, m31, m41);
		C[1] = vector4d (m12, m22, m32, m42);
		C[2] = vector4d (m13, m23, m33, m43);
		C[3] = vector4d (m14, m24, m34, m44);
		}

	/* this ctor is not intended to be an implied type converter */
	explicit matrix4d (const scalar * m)
	{
		C[0] = vector4d (m[0], m[4], m[8],  m [12]);
		C[1] = vector4d (m[1], m[5], m[9],  m [13]);
		C[2] = vector4d (m[2], m[6], m[10], m [14]);
		C[3] = vector4d (m[3], m[7], m[11], m [15]);
	}
	/** @} */

	const matrix4d adjoint () const;
	const matrix4d inverse () const;
	const scalar determinant () const;

	void identity ()
	{
		C[0] = vector4d (1, 0, 0, 0);
		C[1] = vector4d (0, 1, 0, 0);
		C[2] = vector4d (0, 0, 1, 0);
		C[3] = vector4d (0, 0, 0, 1);
	}

	void transpose ()
	{
		matrix4d const m (*this);

		C[0] = vector4d (m.C[0][0], m.C[1][0], m.C[2][0], m.C[3][0]);
		C[1] = vector4d (m.C[0][1], m.C[1][1], m.C[2][1], m.C[3][1]);
		C[2] = vector4d (m.C[0][2], m.C[1][2], m.C[2][2], m.C[3][2]);
		C[3] = vector4d (m.C[0][3], m.C[1][3], m.C[2][3], m.C[3][3]);
	}

	void zero () { C[3] = C[2] = C[1] = C[0] = vector4d (0, 0, 0, 0); }

	/** \name class member operators */
	/** @{ */
	scalar & operator() (int i, int j)
	{
		return C[j][i];
	}
	const scalar & operator() (int i, int j) const
	{
		return C[j][i];
	}

	const vector4d operator * (const vector4d & v) const
	{
		return ((C[0] * v.x) + (C[1] * v.y) + (C[2] * v.z) + (C[3] * v.w));
	}

	const matrix4d & operator += (const matrix4d & b)
	{
		C[0] += b.C[0]; C[1] += b.C[1];
		C[2] += b.C[2]; C[3] += b.C[3];

		return *this;
	}

	const matrix4d & operator -= (const matrix4d & b)
	{
		C[0] -= b.C[0]; C[1] -= b.C[1];
		C[2] -= b.C[2]; C[3] -= b.C[3];

		return *this;
	}

	const matrix4d & operator *= (const matrix4d & b)
	{
		matrix4d const m (*this);

		C[0] = m * b.C[0]; C[1] = m * b.C[1];
		C[2] = m * b.C[2]; C[3] = m * b.C[3];

		return *this;
	}

	const matrix4d & operator *= (const scalar & s)
	{
		C[0] *= s; C[1] *= s;
		C[2] *= s; C[3] *= s;

		return *this;
	}

	const matrix4d operator + (const matrix4d & m) const
	{
		return matrix4d
			(C[0] + m.C[0], C[1] + m.C[1],
			 C[2] + m.C[2], C[3] + m.C[3]);
	}

	const matrix4d operator - (const matrix4d & m) const
	{
		return matrix4d
			(C[0] - m.C[0], C[1] - m.C[1],
			 C[2] - m.C[2], C[3] - m.C[3]);
	}

	const matrix4d operator * (const matrix4d & m) const
	{
		return matrix4d
			((*this) * m.C[0], (*this) * m.C[1],
			 (*this) * m.C[2], (*this) * m.C[3]);
	}
	/** @} */

	friend const matrix4d operator * (const scalar & s, const matrix4d & A)
		{ return (matrix4d (A) *= s); }

	friend const matrix4d operator - (const matrix4d & A)
		{ return (matrix4d (A) *= -1); }
};

}

#endif
