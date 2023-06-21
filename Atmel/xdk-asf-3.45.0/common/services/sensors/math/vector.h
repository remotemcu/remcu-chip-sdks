/**
 * \file
 *
 * \brief This module defines a collection of vector classes.
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

#ifndef _VECTOR_MATH_H_
#define _VECTOR_MATH_H_

#include "precision.h"

namespace math {

/** \brief Calculate the determinant of a 2x2 matrix.
 *
 * This routine calculates the determinant of a 2x2 matrix consisting of
 * entries \p a, \p b, \p c, and \p d arranged in the matrix
 * as follows:
 *
 *  \f[ \left| \begin{array}{cc}
 *    a & b \\
 *    c & d \end{array} \right| \f]
 *
 * \retval  scalar  The real-valued determinant of the input matrix.
 */
inline scalar det (scalar a, scalar b, scalar c, scalar d)
{
	return ((a * d) - (b * c));
}

/** \brief Calculate the determinant of a 3x3 matrix.
 *
 * This routine calculates the determinant of a 3x3 matrix consisting of
 * entries arranged in the matrix as follows:
 *
 *  \f[ \left| \begin{array}{ccc}
 *    a_1 & b_1 & c_1\\
 *    a_2 & b_2 & c_2\\
 *    a_3 & b_3 & c_3 \end{array} \right| \f]
 *
 * \retval  scalar  The real-valued determinant of the input matrix.
 */
inline scalar det (scalar a1, scalar b1, scalar c1,
	scalar a2, scalar b2, scalar c2,
	scalar a3, scalar b3, scalar c3)
{
	return (a1 * det (b2, c2, b3, c3)
		- b1 * det (a2, c2, a3, c3)
		+ c1 * det (a2, b2, a3, b3));
}

/** \brief Ordered 2-tuple implementing Euclidean vector operations */
class vector2d {

public:

	/** \name vector element storage */
	/** @{ */
	scalar x, y;
	/** @} */

	/** \name class construction and destruction */
	/** @{ */
	explicit vector2d (scalar x = 0, scalar y = 0)
		: x (x), y (y) {}
	/** @} */

	/** \name class public methods */
	/** @{ */
	const scalar dot (const vector2d & v) const
		{ return ((x * v.x) + (y * v.y)); }

	void  normalize ()
		{ (*this) /= this->mag (); }

	const scalar mag () const
		{ return static_cast<const scalar>(sqrt (this->dot(*this))); }

	const vector2d unit () const
		{ return (*this) / this->mag (); }

	bool nearlyEquals (const vector2d & v, const scalar & e) const
		{ return (fabs (x - v.x) < e) && (fabs (y - v.y) < e); }
	/** @} */

	/** \name class member operators */
	/** @{ */
	scalar & operator() (int i)
		{ return *(&x + i); }

	const scalar & operator() (int i) const
		{ return *(&x + i); }

	scalar & operator[] (int i)
		{ return this->operator () (i); }

	const scalar & operator[] (int i) const
		{ return this->operator () (i); }

	const vector2d & operator += (const vector2d & v)
	{
		x += v.x; y += v.y;
		return *this;
	}

	const vector2d & operator -= (const vector2d & v)
	{
		x -= v.x; y -= v.y;
		return *this;
	}

	const vector2d & operator *= (const scalar & s)
	{
		x *= s; y *= s;
		return *this;
	}

	const vector2d & operator /= (const scalar & s)
	{
		x /= s; y /= s;
		return *this;
	}

	const vector2d operator + (const vector2d & v) const
		{ return vector2d (x + v.x, y + v.y); }

	const vector2d operator - (const vector2d & v) const
		{ return vector2d (x - v.x, y - v.y); }

	const vector2d operator * (const scalar & s) const
		{ return vector2d (x * s, y * s); }

	const vector2d operator / (const scalar & s) const
		{ return vector2d (x / s, y / s); }

	bool operator == (const vector2d & v) const
		{ return ((x == v.x) && (y == v.y)); }

	bool operator != (const vector2d & v) const
		{ return ! (v == *this); }
	/** @} */


	/** \name class friend operators */
	/** @{ */
	friend const vector2d operator * (const scalar & s, const vector2d & v)
		{ return (vector2d (v) *= s); }

	friend const vector2d operator - (const vector2d & u)
		{ return vector2d (-u.x, -u.y); }
	/** @} */
};

/** \brief Ordered 3-tuple implementing Euclidean vector operations */
class vector3d
	{
public:

	/** \name vector element storage */
	/** @{ */
	scalar x, y, z;
	/** @} */

	/** \brief class construction and destruction */
	/** @{ */
	explicit vector3d (scalar x = 0, scalar y = 0, scalar z = 0)
		: x (x), y (y), z (z) {}
	/** @} */

	/** \name class public methods */
	/** @{ */
	const scalar dot (const vector3d & v) const
		{ return ((x * v.x) + (y * v.y) + (z * v.z)); }

	const vector3d cross (const vector3d & v) const
	{
		return vector3d (det (y, z, v.y, v.z),
			-det (x, z, v.x, v.z), det (x, y, v.x, v.y));
	}

	void  normalize ()
		{ (*this) /= this->mag (); }

	const scalar mag () const
		{ return static_cast<const scalar>(sqrt (this->dot(*this))); }

	const vector3d unit () const
		{ return (*this) / this->mag (); }

	bool nearlyEquals (const vector3d & v, const scalar & e) const
	{
		return (fabs (x - v.x) < e) && (fabs (y - v.y) < e)
			&& (fabs (z - v.z) < e);
	}
	/** @} */

	/** \name class member operators */
	/** @{ */
	scalar & operator() (int i)
		{ return *(&x + i); }

	const scalar & operator() (int i) const
		{ return *(&x + i); }

	scalar & operator[] (int i)
		{ return this->operator () (i); }

	const scalar & operator[] (int i) const
		{ return this->operator () (i); }

	const vector3d & operator += (const vector3d & v)
	{
		x += v.x; y += v.y; z += v.z;
		return *this;
	}

	const vector3d & operator -= (const vector3d & v)
	{
		x -= v.x; y -= v.y; z -= v.z;
		return *this;
	}

	const vector3d & operator *= (const scalar & s)
	{
		x *= s; y *= s; z *= s;
		return *this;
	}

	const vector3d & operator /= (const scalar & s)
	{
		x /= s; y /= s; z /= s;
		return *this;
	}

	const vector3d operator + (const vector3d & v) const
		{ return vector3d (x + v.x, y + v.y, z + v.z); }

	const vector3d operator - (const vector3d & v) const
		{ return vector3d (x - v.x, y - v.y, z - v.z); }

	const vector3d operator * (const scalar & s) const
		{ return vector3d (x * s, y * s, z * s); }

	const vector3d operator / (const scalar & s) const
		{ return vector3d (x / s, y / s, z / s); }

	bool operator == (const vector3d & v) const
		{ return ((x == v.x) && (y == v.y) && (z == v.z)); }

	bool operator != (const vector3d & v) const
		{ return ! (v == *this); }
	/** @} */

	/** \name class friend operators */
	/** @{ */
	friend const vector3d operator * (const scalar & s, const vector3d & v)
		{ return (vector3d (v) *= s); }

	friend const vector3d operator - (const vector3d & u)
		{ return vector3d (-u.x, -u.y, -u.z); }
	/** @} */
	};

/** \brief Augmented 3-dimensional vector / homogeneous vector / projected point */
class vector4h {
public:

	/** \name homogeneous vector element storage */
	/** @{ */
	scalar x, y, z, w;
	/** @} */

	/** \name class construction and destruction */
	/** @{ */
	explicit vector4h (scalar x = 0, scalar y = 0, scalar z = 0, scalar w = 1)
		: x (x), y (y), z (z), w (w) {}

	explicit vector4h (const vector3d & v)
		: x (v.x), y (v.y), z (v.z), w (1) {}
	/** @} */

	/** \name class public methods */
	/** @{ */
	const scalar dot (const vector4h & v) const
		{ return ((x * v.x) + (y * v.y) + (z * v.z)); }

	const vector4h cross (const vector4h & v) const
	{
		return vector4h (det (y, z, v.y, v.z),
			-det (x, z, v.x, v.z), det (x, y, v.x, v.y));
	}

	void  normalize ()
		{ (*this) /= this->mag (); }

	const scalar mag () const
		{ return static_cast<const scalar>(sqrt (this->dot(*this))); }

	const vector4h unit () const
		{ return (*this) / this->mag (); }

	bool nearlyEquals (const vector4h & v, const scalar & e) const
	{
		return (fabs (x - v.x) < e) && (fabs (y - v.y) < e)
			&& (fabs (z - v.z) < e);
	}
	/** @} */

	/** \name class member operators */
	/** @{ */
	scalar & operator() (int i)
		{ return *(&x + i); }

	const scalar & operator() (int i) const
		{ return *(&x + i); }

	scalar & operator[] (int i)
		{ return this->operator () (i); }

	const scalar & operator[] (int i) const
		{ return this->operator () (i); }

	const vector4h & operator += (const vector4h & v)
	{
		x += v.x; y += v.y; z += v.z;
		return *this;
	}

	const vector4h & operator -= (const vector4h & v)
	{
		x -= v.x; y -= v.y; z -= v.z;
		return *this;
	}

	const vector4h & operator *= (const scalar & s)
	{
		x *= s; y *= s; z *= s;
		return *this;
	}

	const vector4h & operator /= (const scalar & s)
	{
		x /= s; y /= s; z /= s;
		return *this;
	}

	const vector4h operator + (const vector4h & v) const
		{ return vector4h (x + v.x, y + v.y, z + v.z); }

	const vector4h operator - (const vector4h & v) const
		{ return vector4h (x - v.x, y - v.y, z - v.z); }

	const vector4h operator * (const scalar & s) const
		{ return vector4h (x * s, y * s, z * s); }

	const vector4h operator / (const scalar & s) const
		{ return vector4h (x / s, y / s, z / s); }

	bool operator == (const vector4h & v) const
		{ return ((x == v.x) && (y == v.y) && (z == v.z)); }

	bool operator != (const vector4h & v) const
		{ return ! (v == *this); }
	/** @} */

	/** \name class friend operators */
	/** @{ */
	friend const vector4h operator * (const scalar & s, const vector4h & v)
		{ return (vector4h (v) *= s); }

	friend const vector4h operator - (const vector4h & u)
		{ return vector4h (-u.x, -u.y, -u.z); }
	/** @} */
};

/** \brief Ordered 4-tuple implementing Euclidean vector operations */
class vector4d
{
public:

	/** \name vector element storage */
	scalar x, y, z, w;

	/** \name class construction and destruction */
	/** @{ */
	explicit vector4d (scalar x = 0, scalar y = 0, scalar z = 0, scalar w = 0)
		: x (x), y (y), z (z), w (w) {}

	explicit vector4d (const vector4h & v)
		: x (v.x), y (v.y), z (v.z), w (v.w) {}
	/** @} */

	/** \name class public methods */
	/** @{ */
	const scalar dot (const vector4d & v) const
		{ return ((x * v.x) + (y * v.y) + (z * v.z) + (w * v.w)); }

	void  normalize ()
		{ (*this) /= this->mag (); }

	const scalar mag () const
		{ return static_cast<const scalar>(sqrt (this->dot(*this))); }

	const vector4d unit () const
		{ return (*this) / this->mag (); }

	bool nearlyEquals (const vector4d & v, const scalar & e) const
	{
		return (fabs (x - v.x) < e) && (fabs (y - v.y) < e)
			&& (fabs (z - v.z) < e) && (fabs (w - v.z) < e);
	}
	/** @} */

	/** \name class member operators */
	/** @{ */
	scalar & operator() (int i)
		{ return *(&x + i); }

	const scalar & operator() (int i) const
		{ return *(&x + i); }

	scalar & operator[] (int i)
		{ return this->operator () (i); }

	const scalar & operator[] (int i) const
		{ return this->operator () (i); }

	const vector4d & operator += (const vector4d & v)
	{
		x += v.x; y += v.y; z += v.z; w += v.w;

		return *this;
	}

	const vector4d & operator -= (const vector4d & v)
	{
		x -= v.x; y -= v.y; z -= v.z; w -= v.w;

		return *this;
	}

	const vector4d & operator *= (const scalar & s)
	{
		x *= s; y *= s; z *= s; w *= s;

		return *this;
	}

	const vector4d & operator /= (const scalar & s)
	{
		x /= s; y /= s; z /= s; w /= s;

		return *this;
	}

	const vector4d operator + (const vector4d & v) const
		{ return (vector4d (*this) += v); }

	const vector4d operator - (const vector4d & v) const
		{ return (vector4d (*this) -= v); }

	const vector4d operator * (const scalar & s) const
		{ return vector4d (*this) *= s; }

	const vector4d operator / (const scalar & s) const
		{ return vector4d (*this) /= s; }

	bool operator == (const vector4d & v) const
		{ return ((x == v.x) && (y == v.y) && (z == v.z) && (w == v.w)); }

	bool operator != (const vector4d & v) const
		{ return ! (v == *this); }
	/** @} */

	/** \name class friend operators */
	/** @{ */
	friend const vector4d operator * (const scalar & s, const vector4d & v)
		{ return (vector4d (v) *= s); }

	friend const vector4d operator - (const vector4d & u)
		{ return vector4d (-u.x, -u.y, -u.z, -u.w); }
	/** @} */
};

}

#endif
