/**
 * @file sfp_utils.c
 * @author ajheck
 * @brief Contains utility functions for the sfp library
 * @version 0.1
 * @date 2022-10-14
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "sfp_utils.h"

#define SFP_CRC_INIT_VAL (0xFFFF)

sfp_crc_t sfp_crc_init(void) {
    return SFP_CRC_INIT_VAL;
}

sfp_crc_t sfp_crc(sfp_crc_t crc, const uint8_t data[], uint16_t len) {
    uint_fast16_t i;

    if( NULL == data ) {
        return crc;
    }

    for(i = 0; i < len; ++i) {
        uint_fast8_t temp;
        temp = data[i] ^ (crc >> 8);
        temp ^= (temp >> 4);
        crc = (crc << 8) ^ temp ^ (temp << 5) ^ (temp << 12);
    }

    return crc;
}