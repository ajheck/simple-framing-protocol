/**
 * @file sfp_utils.h
 * @author ajheck
 * @brief Contains utility functions for the sfp library
 * @version 0.1
 * @date 2022-10-14
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef SFP_UTILS_H
#define SFP_UTILS_H

#include <stdint.h>

/**
 * @brief Typedef for CRC values
 * 
 */
typedef uint_fast16_t sfp_crc_t;

/**
 * @brief Length of the CRC
 * @note This may be different than sizeof(sfp_crc_t);
 * it should reflect the number of bits transmitted for the CRC
 * 
 */
#define CRC_LEN_BITS (16)

/**
 * @brief Get the initial value for a new CRC, and optionally initialize the CRC module as needed.
 * Can be modified to initialize hardware, etc. for custom CRC implementations
 * 
 * @return uint16_t The initial value of the CRC to be passed to sfp_crc()
 */
sfp_crc_t sfp_crc_init(void);

/**
 * @brief Calculate the CRC for an array of bytes.
 * The default implementation is equivalent to CRC16-CCITT (poly 0x1021) with a starting value of 0xFFFF
 * 
 * @param crc The previous value of the CRC, or the return of sfp_crc_init() when calculating a new CRC 
 * @param data An arrray of bytes to "feed" into the CRC
 * @param len The length of data
 * @return uint16_t The new value of the CRC
 */
sfp_crc_t sfp_crc(sfp_crc_t crc, const uint8_t data[], uint16_t len);

#endif