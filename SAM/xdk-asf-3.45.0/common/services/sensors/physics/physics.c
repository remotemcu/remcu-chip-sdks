/**
 * \file
 *
 * \brief ASF Sensor API physics utilities
 *
 * This module defines types and operations that support basic physical
 * modelling and equations for sensor data.
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

#include "physics.h"

#define degrees(a)  (RAD_TO_DEG * (a))

/*! \brief Calculate direction, inclination, and field strength
 *
 * This routine calculates horizontal direction, vertical inclination and
 * net field magnitude for a "raw" (unscaled) magnetic \c field sample from
 * a 3-axis magnetometer.
 *
 * \param   field       Magnetometer raw vector field sample input
 * \param   theta       Calculated direction angle (degrees) output
 * \param   delta       Calculated inclination angle (degrees) output
 * \param   strength    Calculated raw vector field magnitude output
 *
 * \return  bool        true if the call succeeds, else false is returned.
 */
bool field_direction(vector3_t *field, scalar_t *theta, scalar_t *delta,
		scalar_t *strength)
{
	/* Calculate the geomagnetic field direction vector (unit vector) and
	 * strength (field magnitude).
	 */
	scalar_t const magnitude = vector3_magnitude(field);

	if (0 == magnitude) {
		return false;
	}

	vector3_scale((1 / magnitude), field);

	*strength = magnitude;

	/* Calculate the direction angle (degrees) assuming no mounting tilt.
	 * "Wraparound" negative results to a positive heading.  The angle is
	 * calculated relative to +Y axis, so atan2() arguments are (x,y)
	 * instead of (y,x).  Result is inverted (* -1) so positive values
	 * reflect clockwise rotation.
	 */
	*theta = degrees(-1 * atan2(field->x, field->y));

	if (*theta < 0) {
		*theta += 360;
	}

	/* Calculate the inclination angle degrees (assuming no mounting tilt).
	 * Downward angle is indicated by a positive inclination value.
	 */
	*delta = degrees(-1 * asin(field->z));

	return true;
}
