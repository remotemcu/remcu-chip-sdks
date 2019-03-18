/**
 * \file
 *
 * \brief The math::plane class models a plane in 3-dimensional space.
 *
 * This module implements a class modelling a plane in 3-dimensional space.
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


#ifndef _plane_h_
#define _plane_h_

#include "vector.h"

namespace math {

/** \brief 3-dimensional plane class declaration */
class plane {

public:

	typedef math::vector3d vector;

	/** \name Class construction and destruction */
	/** @{ */
	explicit plane (scalar a = 1, scalar b = 0, scalar c = 0, scalar d = 0)
		: n (vector (a, b, c)), d (d) {}

	plane (const vector & normal, scalar d = 0)
		: n (normal), d (d) {}

	plane (const vector & p1, const vector & p2, const vector & p3) {
		vector const v1 = p2 - p1;
		vector const v2 = p3 - p1;

		n = v1.cross (v2);
		d = -(n.dot (p1));
	}
	/** @} */

	/** \name Class public methods */
	/** @{ */
	const vector & normal () const { return n; }
	const scalar & shift () const  { return d; }

	const scalar distanceToPlane (const vector & p) const
		{ return std::fabs (n.dot (p) + d) / n.mag (); }

	const bool pointInPlane (const vector & p) const
		{ return (0 == distanceToPlane (p)); }
	/** @} */

private:

	vector n;     /**< A plane normal vector */
	scalar d;     /**< A plane-shift constant */
};

}

#endif
