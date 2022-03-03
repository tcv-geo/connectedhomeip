/* HS300x temperature and humidity sensor driver
 * Copyright Green Energy Options Limited
 */

#include <stddef.h>
#include <stdint.h>
#include "fsl_common.h"
#include "FreeRTOS.h"
#include "task.h"
#include "i2c_interface.h"

#include "fsl_debug_console.h"
#include "temperature_sensor.h"

#define I2C_SLAVE_ADDRESS 0x44

status_t temperature_sensor_read(int32_t *millicelcius, int32_t *millihumidity)
{
  PRINTF("call\r\n");
	// conversion is triggered by slave write address with no data:
	status_t status = i2c_write(I2C_SLAVE_ADDRESS, 0, 0, NULL, 0);
  PRINTF("return\r\n");

	if (status != kStatus_Success) {
		return status;
	}

	vTaskDelay(pdMS_TO_TICKS(35));

	uint8_t data[4];

	status = i2c_read(I2C_SLAVE_ADDRESS, 0, 0, data, sizeof data);

	if (status != kStatus_Success) {
		return status;
	}

	unsigned int flags = ((data[0] >> 6) & 3);

	if (flags != 0) {
		return kStatus_Fail;
	}

	unsigned int packed_humidity = (((data[0] & 0x3Fu) << 8) | data[1]);
	unsigned int packed_temperature = (((data[2] & 0xFFu) << 6) | (data[3] >> 2));

	*millihumidity = (((packed_humidity * 1000u) + 0x1FFFu) / 0x3FFFu);

	*millicelcius = ((int32_t)(((packed_temperature * 165000u) + 0x1FFFu) / 0x3FFFu) - 40000);

	return status;
}
