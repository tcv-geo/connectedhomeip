/* I2C interface driver
 * Copyright Green Energy Options Limited
 */

#pragma once

#include <stddef.h>
#include <stdint.h>
#include "fsl_common.h"

#ifdef __cplusplus
extern "C" {
#endif

status_t i2c_init(void);

status_t i2c_write(uint8_t  slave_address,
                  uint32_t  register_address,
                    size_t  register_length,
             const uint8_t *data,
                    size_t  data_length);

status_t i2c_read( uint8_t  slave_address,
                  uint32_t  register_address,
                    size_t  register_length,
                   uint8_t *data,
                    size_t  data_length);

#ifdef __cplusplus
}
#endif
