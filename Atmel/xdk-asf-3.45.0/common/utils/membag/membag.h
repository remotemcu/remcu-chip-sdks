/**
 * \file
 *
 * \brief Memory Bag allocator for 8-bit AVR, 32-bit AVR, SAM
 *
 * Copyright (c) 2014-2018 Microchip Technology Inc. and its subsidiaries.
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

#ifndef UTILS_MEMBAG_H
#define UTILS_MEMBAG_H

#include <stddef.h>

/**
 * \defgroup membag_group Memory Bag Allocator
 *
 * The Membag allocator is a optimized, fragmentationless general purpose
 * memory allocator utility module designed to replace the standard C library
 * \c malloc() and \c free() functions in resource constrained environments.
 *
 *
 * Internally, the Membag allocator uses several user defined "bags" of one or
 * more fixed-size blocks to form a memory pool for use in a user application.
 * When an allocation is requested, the Membag module will search all available
 * bags and find the smallest unallocated block of sufficient size, and return
 * this block to the calling function. The size of each bag and number of blocks
 * in each bag is user configurable, via the \ref conf_membag.h header file
 * added to the user project.
 *
 * The allocator also has basic statistics functionality to obtain the size of
 * the entire memory pool, amount of free memory, and the size of the smallest
 * and largest free memory block.
 *
 * The memory bag allocator always allocates memory as a block from a fixed size
 * bag/pool. This helps reduce memory fragmentation compared to an generic
 * allocator that gives exactly the bytes requested. While this gives a
 * trade-off of the maximum number of concurrent allocations and the size of
 * allocations that are allowable, the allocator prevents memory fragmentation
 * from occuring in an embedded application.
 *
 * The allocation and deallocation of memory with the Membag module is
 * non-deterministic, however the module functions all have a maximum run time
 * that is dependent on the number of bags that have been configured.
 *
 * @{
 */

/**
 * Macro used to create memory bags in conf_membag.h
 *
 * \note Multiple bags of the same size are allowed, if more than 32 bags of a
 *       given size are required in an application.
 *
 * \param objsize  Size of each block in the bag
 * \param nr_objs  Number of blocks in the bag, a value less than 32
 */
#define MEMBAG(objsize, nr_objs)\
	{ .block_size = objsize, .num_blocks = nr_objs }

/**
 * Macro used to store the size of the membags in conf_membag.h
 *
 * \note Multiple bags of the same size are allowed, if more than 32 bags of a
 *       given size are required in an application.
 *
 * \param objsize  Size of each block in the bag
 * \param nr_objs  Number of blocks in the bag, a value less than 32
 */
#define MEMBAG_SIZE(objsize, nr_objs)\
	(objsize * nr_objs)

void membag_init(void);

size_t membag_get_total(void);
size_t membag_get_total_free(void);

size_t membag_get_smallest_free_block_size(void);
size_t membag_get_largest_free_block_size(void);

void *membag_alloc(const size_t size);
void membag_free(const void *ptr);

/** @} */

#endif /* UTILS_MEMBAG_H */
