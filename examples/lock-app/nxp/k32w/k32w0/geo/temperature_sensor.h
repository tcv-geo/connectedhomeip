/* Temperature and humidity sensor driver
 * Copyright Green Energy Options Limited
 */

#pragma once

#include <stdint.h>
#include "fsl_common.h"

#ifdef __cplusplus
extern "C" {
#endif

status_t temperature_sensor_read(int32_t *millicelcius, int32_t *millihumidity);

#ifdef __cplusplus
}
#endif
