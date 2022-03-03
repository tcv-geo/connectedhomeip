/* I2C interface driver
 * Copyright Green Energy Options Limited
 */

#include <stddef.h>
#include <stdint.h>
#include "fsl_common.h"
#include "fsl_i2c.h"
#include "fsl_i2c_freertos.h"

#include "i2c_interface.h"

// I2C0 (aka. FLEXCOMM2) on PIO10 and PIO11
#define I2C_MASTER ((I2C_Type *)I2C0_BASE)
#define I2CM_IRQn FLEXCOMM2_IRQn
#define I2CM_NVIC_PRIO 2
#define I2CM_CLOCK_FREQ (48u * 1000 * 1000) // CLOCK_GetFreq(kCLOCK_I2c0) doesn't work

#define I2C_BAUDRATE (100 * 1000)

static i2c_rtos_handle_t g_i2c_handle;

status_t i2c_init(void)
{
	NVIC_SetPriority(I2CM_IRQn, I2CM_NVIC_PRIO);

	i2c_master_config_t config;

	I2C_MasterGetDefaultConfig(&config);

	config.baudRate_Bps = I2C_BAUDRATE;

	return I2C_RTOS_Init(&g_i2c_handle, I2C_MASTER, &config, I2CM_CLOCK_FREQ);
}

status_t i2c_write(uint8_t  slave_address,
                  uint32_t  register_address,
                    size_t  register_length,
             const uint8_t *data,
                    size_t  data_length)
{
	i2c_master_transfer_t transfer;

	transfer.flags          = kI2C_TransferDefaultFlag;
	transfer.slaveAddress   = slave_address;
	transfer.direction      = kI2C_Write;
	transfer.subaddress     = register_address;
	transfer.subaddressSize = register_length;
	transfer.data           = (uint8_t*)data;
	transfer.dataSize       = data_length;

	return I2C_RTOS_Transfer(&g_i2c_handle, &transfer);
}

status_t i2c_read( uint8_t  slave_address,
                  uint32_t  register_address,
                    size_t  register_length,
                   uint8_t *data,
                    size_t  data_length)
{
	i2c_master_transfer_t transfer;

	transfer.flags          = kI2C_TransferDefaultFlag;
	transfer.slaveAddress   = slave_address;
	transfer.direction      = kI2C_Read;
	transfer.subaddress     = register_address;
	transfer.subaddressSize = register_length;
	transfer.data           = data;
	transfer.dataSize       = data_length;

	return I2C_RTOS_Transfer(&g_i2c_handle, &transfer);
}
