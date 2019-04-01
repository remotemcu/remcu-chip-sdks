/***************************************************************************//**
 * @file rfs.h
 * @brief ROM File System Drive
 * @version 5.1.1
 *******************************************************************************
 * @section License
 * <b>Copyright 2016 Silicon Laboratories, Inc. http://www.silabs.com</b>
 *******************************************************************************
 *
 * This file is licensed under the Silicon Labs License Agreement. See the file
 * "Silabs_License_Agreement.txt" for details. Before using this software for
 * any purpose, you must agree to the terms of that agreement.
 *
 ******************************************************************************/

#ifndef __RFS_H_
#define __RFS_H_

#include <stdint.h>

/***************************************************************************//**
 * @cond DOXYGEN_INCLUDE_RFS
 * @addtogroup RFS
 * @{
 ******************************************************************************/

/***************************************************************************//**
 * @cond DOXYGEN_INCLUDE_RFS
 * @defgroup RFS_Typedefs ROM File System Type Definitions
 * @{
 * @brief ROM File System type definitions
 ******************************************************************************/

/***************************************************************************//**
 * @brief
 *    RFS file handle structure
 ******************************************************************************/
typedef struct __RFS_FileHandle {

   uint16_t fileIndex;        /**< Index of the file within the file system */
   uint32_t currentIndex;     /**< Current index position within the file   */

} RFS_FileHandle;

/** @} {end defgroup RFS_Typedefs ROM} */
/** @endcond {DOXYGEN_INCLUDE_RFS} */

/***************************************************************************//**
 * @cond DOXYGEN_INCLUDE_RFS
 * @defgroup RFS_Macros ROM File System Macro Definitions
 * @{
 * @brief ROM File System macro definitions
 ******************************************************************************/

#define RFS_MAX_FILE_NAME_SIZE 256  /**< Maximum length of the file name string  */

#define RFS_SEEK_SET 0x80000000     /**< The beginnig of the file                */
#define RFS_SEEK_CUR 0x80000001     /**< The current index position of the file  */
#define RFS_SEEK_END 0x80000002     /**< The end of the file                     */

/** @} {end defgroup RFS_Macros} */
/** @endcond {DOXYGEN_INCLUDE_RFS} */

/***************************************************************************//**
 * @cond DOXYGEN_INCLUDE_RFS
 * @addtogroup RFS_Functions
 * @{
 ******************************************************************************/

uint32_t RFS_getFileCount( void );
uint8_t *RFS_getFileNameByIndex( uint32_t index );
int32_t RFS_getFileLengthByIndex( uint32_t index );
int16_t RFS_getFileIndex( uint8_t name[] );

int32_t RFS_fileOpen( RFS_FileHandle *fileHandle, uint8_t name[] );
int32_t RFS_fileSeek( RFS_FileHandle *fileHandle, int32_t offset, uint32_t whence );
int32_t RFS_fileRead( uint8_t *buf, uint32_t size, uint32_t nmemb, RFS_FileHandle *fileHandle );
int32_t RFS_getFileLength( RFS_FileHandle *fileHandle );
uint8_t *RFS_getFileName( RFS_FileHandle *fileHandle );
uint8_t *RFS_fileGetRawData( RFS_FileHandle *fileHandle );

/** @} {end addtogroup RFS_Functions} */
/** @endcond {DOXYGEN_INCLUDE_RFS} */

/** @} {end addtogroup RFS} */
/** @endcond {DOXYGEN_INCLUDE_RFS} */

/** @endcond {DOXYGEN_INCLUDE_RFS} */

#endif /* __RFS_H_ */
