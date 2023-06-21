/**
 * \file
 *
 * \brief The math::quaternion class defines quaternion types and utilities.
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


#ifndef _QUATERNION_MATH_H_
#define _QUATERNION_MATH_H_

#include "matrix.h"
#include "vector.h"

namespace math {

/**
 * \brief 4-dimensional normed division algebra over the Real Numbers
 *
 * Every quaternion is uniquely expressible as a Real linear combination of
 * basis quaternions \f$ 1, i, j, k \f$ satisfying the relation:
 *
 * \f[
 *      i^{2} = j^{2} = k^{2} = ijk = -1    \label{ eq. 1 }
 * \f]
 *
 * Quaternions satisfy vector space axioms over the Reals.  The set
 * \f$ \mathbf{H} \f$ of all quaternions has dimension 4.  However, unlike
 * Real and Complex numbers, multiplication of quaternions is not commutative.
 * However, multiplication associates, and every non-zero element has a unique
 * inverse.
 *
 * The set of equations (eq. 1) is the fundamental formula for quaternion
 * multiplication.  The multiplication table of basis quaternions is easily
 * derived from the relation \f$ ijk = -1 \f$.
 *
 * Given quaternion set \f$ \mathbf{H} \f$, Real scalars
 * \f$ a, b, c, d \f$, and quaternion \f$ z = a + bi + cj + dk \f$ the
 * following additional definitions apply:
 *
 * - Conjugate of \f$ \mathit{z} \f$ is \f$ z^{*} = a - bi - cj - dk \f$
 *
 * - Absolute value (magnitude) of \f$ \mathit{z} \f$ is the non-negative Real
 *   scalar value
 *
 *   \f[
 *      \vert z \vert = (zz^{*})^{\frac{1}{2}} =
 *          \sqrt{a^{2} + b^{2} + c^{2} + d^{2}}
 *   \f]
 *
 * - Multiplicative inverse (reciprocal) \f$ \mathit{z} \f$ can be computed as
 *
 *   \f[
 *      \frac{1}{z} = \frac{z^{*}}{\vert z\vert^{2}} = \frac{z^{*}}{zz^{*}}
 *   \f]
 *
 * - Given two distinct quaternions, \f$ q_1 = (a + \vec{u}) \f$ and
 *   \f$ q_2 = (b + \vec{v}) \f$, the product is not generally commutable and
 *   is defined as
 *
 *   \f[
 *      q_1 q_2 = (ab - \langle \vec{u}, \vec{v} \rangle) +
 *          (a\vec{v} + b\vec{u} + \vec{u} \times \vec{v})
 *   \f]
 *
 * - Let \f$ z = \cos{(\frac{\alpha}{2})} + \sin{(\frac{\alpha}{2})}\vec{U} \f$
 *   be a unit quaternion.  The mapping \f$ f(\vec{x}) = z\vec{x}z^{*} \f$ is
 *   known as conjugation by \f$ \mathit{z}, \f$ where the vector
 *   \f$ \vec{x} \f$ is considered a quaternion with its scalar component equal
 *   to zero.  \f$ f(\vec{x}) \f$ rotates \f$ \vec{x} \f$ counterclockwise
 *   through an angle \f$ \alpha \f$ about an axis \f$ \vec{U} \f$.  The
 *   composition of two rotations corresponds to quaternion multiplication.
 */
class quaternion {

private:

	/** \name (scalar, vector) element storage */
	/** @{ */
	scalar    _s;
	vector3d  _v;
	/** @} */

public:

	/** \name class construction and type conversion */
	/** @{ */
	quaternion ()
		: _s (0), _v (vector3d (0, 0, 0)) {}

	quaternion (const scalar & s, const vector3d & v)
		: _s (s), _v (v) {}

	quaternion (const scalar & q1, const scalar & q2,
		 const scalar & q3, const scalar & q4)
		: _s (q1), _v (q2, q3, q4) {}
	/** @} */

	/** \name class public methods
	/** @{ */
	
	const quaternion conjugate () const
		{ return quaternion (_s, -_v); }

	const vector3d cross (const quaternion & q) const
		{ return _v.cross (q._v); }
		
	/** \brief dot-product (Euclidean inner-product) */
	const scalar dot (const quaternion & q) const
		{ return (_s * q._s) + _v.dot (q._v); }

	/** \brief modulus (absolute value or length from origin) */
	const scalar length () const
		{ return static_cast<const scalar>(sqrt (this->dot(*this))); }

	void  normalize ()
		{ (*this) /= this->length (); }

	const quaternion unit () const
		{ return (*this) / this->length (); }

	const scalar &   Scalar () const
		{ return _s; }

	const vector3d & Vector () const
		{ return _v; }

	/**
     * \brief Sign, sgn(z), of a complex number finds the complex number
     * of the same direction found on the unit circle.
	 */
	const quaternion sgn () const
		{ return this->unit (); }

	/**
     * \brief Argument, arg(z), finds the angle of the 4-vector quaternion
	 * from the unit scalar (i.e. 1).
	 */
	const scalar arg () const
		{ return acos (_s / this->length ()); }

	/** \name class member operators */
	/** @{ */
	const quaternion & operator *= (const quaternion & q)
	{
		quaternion const p (*this);

		*this = p * q;

		return *this;
	}

	const quaternion & operator += (const quaternion & q)
	{
		_s += q._s; _v += q._v;
		return *this;
	}

	const quaternion & operator -= (const quaternion & q)
	{
		_s -= q._s; _v -= q._v;
		return *this;
	}

	const quaternion & operator *= (const scalar & s)
	{
		_s *= s; _v *= s;
		return *this;
	}

	const quaternion & operator /= (const scalar & s)
	{
		_s /= s; _v /= s;
		return *this;
	}
	/** @} */

	/** \brief quaternion multiplication (Grassmann Product) */
	const quaternion operator * (const quaternion & q) const
	{
		return quaternion ((_s * q._s) - _v.dot (q._v),
			(q._v * _s) + (_v * q._s) + _v.cross (q._v));
	}

	const quaternion operator + (const quaternion & q) const
		{ return quaternion (_s + q._s, _v + q._v); }

	const quaternion operator - (const quaternion & q) const
		{ return quaternion (_s - q._s, _v - q._v); }

	const quaternion operator * (const scalar & s) const
		{ return quaternion (_s * s, _v * s); }

	const quaternion operator / (const scalar & s) const
		{ return quaternion (_s / s, _v / s); }

	const bool   operator == (const quaternion & q) const
		{ return ((_s == q._s) && (_v == q._v)); }

	const bool   operator != (const quaternion & q) const
		{ return ! (q == *this); }

	/** @} */

	friend const quaternion operator * (const scalar & s, const quaternion & q)
		{ return quaternion (q._s * s, q._v * s); }

	friend const quaternion operator - (const quaternion & q)
		{ return quaternion (-q._s, -q._v); }
};


/** \brief Multiply a vector by a quaternion.
 *
 * This operator multiplies a math::vector3d object on the right-side of
 * the operator by math::quaternion object on the left-side of the operator.
 *
 * \param   q   A math::quaternion operand.
 * \param   v   A math::vector3d operand.
 *
 * \retval  math::quaternion    The product of the input operands.
 */
inline const quaternion operator *
	(const quaternion & q, const vector3d & v)
{
	const scalar &   _s = q.Scalar ();
	const vector3d & _v = q.Vector ();

	return quaternion (- _v.dot (v), (v * _s) + _v.cross (v));
}

/** \brief Multiply a quaternion by a vector.
 *
 * This operator multiplies a math::quaternion object on the right-side of
 * the operator by math::vector3d object on the left-side of the operator.
 *
 * \param   v   A math::vector3d operand.
 * \param   q   A math::quaternion operand.
 *
 * \retval  math::quaternion    The product of the input operands.
 */
inline const quaternion operator *
	(const vector3d & v, const quaternion & q)
{
	const scalar &   _s = q.Scalar ();
	const vector3d & _v = q.Vector ();

	return quaternion (- v.dot (_v), (v * _s) + v.cross (_v));
}

/** \brief Rotate a vector by a unit quaternion.
 *
 * Given unit quaternion \f$ q = (s, \vec{v}) \f$ and its conjugate
 * \f$ q^{*} = (s, -\vec{v}), \f$ to rotate arbitrary vector \f$ \vec{r} \f$
 * by an angle \f$ \alpha \f$ about a vector \f$ \hat{N} \f$:
 *
 *  - Convert the vector \f$ \vec{r} \f$ to quaternion form
 *    \f$ p = (0, \vec{r}) \f$ and express the rotation quaternion as:
 *
 * \f[
 *      q = (\cos{(\frac{\alpha}{2})}, \sin{(\frac{\alpha}{2})}\hat{N})
 * \f]
 *
 *  - Perform the following multiplication which is equivalent to
 *    rotation about \f$ \hat{N} \f$:
 *
 * \f[
 *      qpq^{*} = (0, (s^{2} - \vec{v} \cdot \vec{v})\vec{r} +
 *          2\vec{v}(\vec{v} \cdot \vec{r}) + 2s\vec{v} \times \vec{r})
 *          = (0, \vec{r}^{\prime})
 * \f]
 *
 * \param   q   A math::quaternion operand.
 * \param   v   A math::vector3d operand.
 *
 * \retval  math::vector3d  The resulting rotated vector object.
 */
inline const vector3d rotate
	(const quaternion & q, const vector3d & v)
{
	quaternion const z (q * v * q.conjugate ());

	return z.Vector ();
}

/** \brief Quaternion to direction cosine matrix (DCM) conversion.
 *
 * This routine converts a specified quaternion \f$ \mathbf{q} \f$
 * to a 3x3 direction cosine matrix (\p DCM).
 *
 * If point \f$ \mathbf{P} \f$ is transformed to \f$ \mathbf{P^{\prime}} \f$
 * as a result of a rotation described by quaternion \f$ \mathbf{q} \f$
 * according to the following quaternion algebra:
 *
 *  \f$ P^{\prime} = qPq^{*} \f$
 *
 * where
 *
 *  \f$ q = q_0 + \hat{i}q_1 + \hat{j}q_2 + \hat{k}q_3 \f$
 *
 *  \f$ q^{*} = q_0 - \hat{i}q_1 - \hat{j}q_2 - \hat{k}q_3 \f$
 *
 *  \f$ P = 0 + \hat{i}x + \hat{j}y + \hat{k}z \f$
 *
 * \param   q   A rotation math::quaternion argument.
 *
 * \retval  math::matrix3d  A 3x3 direction cosine matrix.
 */
inline const matrix3d quaternion2DCM (const quaternion & q)
{
	const scalar &   _s (q.Scalar ());
	const vector3d & _v (q.Vector ());

	scalar const ww (_s * _s);
	scalar const wx (_s * _v.x);
	scalar const wy (_s * _v.y);
	scalar const wz (_s * _v.z);

	scalar const xx (_v.x * _v.x);
	scalar const xy (_v.x * _v.y);
	scalar const xz (_v.x * _v.z);

	scalar const yy (_v.y * _v.y);
	scalar const yz (_v.y * _v.z);

	scalar const zz (_v.z * _v.z);

	return matrix3d
		(ww + xx - yy - zz,  2 * (xy - wz),      2 * (xz + wy),
		 2 * (xy + wz),      ww - xx + yy - zz,  2 * (yz - wx),
		 2 * (xz - wy),      2 * (yz + wx),      ww - xx - yy + zz);
}

/** \brief Quaternion to Euler angle conversion.
 *
 * This routine converts a specified quaternion \f$ \mathbf{q} \f$ to a 3x1
 * vector storing bank (rotation about x-axis), attitude (rotation about
 * y-axis), and heading (rotation about z-axis) values in the x, y, and z
 * vector elements, respectively.
 *
 * \note
 *
 *  - Singularities are not accounted for when the pitch approaches
 *    \f$ \pm 90 \f$ degrees (north / south pole); i.e. gimbal lock.
 *
 *  - This is a special-case assuming a particular right-hand system,
 *    but there are many types of Euler angles depending upon the system
 *    being described.  Additional work is required to create a set of
 *    useful utility methods for converting quaternions to Euler angles.
 *
 * \param   q   A rotation math::quaternion argument.
 *
 * \retval  math::vector3d  A 3x1 vector storing roll, pitch, and yaw.
 */
inline const vector3d quaternion2euler (const quaternion & q)
{
	scalar const q0 (q.Scalar());
	scalar const q1 (q.Vector().x);
	scalar const q2 (q.Vector().y);
	scalar const q3 (q.Vector().z);

	return vector3d
		(atan2 (2 * ((q0*q1) + (q2*q3)), 1 - 2 * ((q1*q1) + (q2*q2))),
		 asin  (2 * ((q0*q2) - (q3*q1))),
		 atan2 (2 * ((q0*q3) + (q1*q2)), 1 - 2 * ((q2*q2) + (q3*q3))));
}

}

#endif
