/*
 * Register_map.h
 *
 * Created: 20.9.2019 20:39:11
 *  Author: Hörður Hermannsson
 */ 


#ifndef REGISTER_MAP_H_
#define REGISTER_MAP_H_


#ifndef MPU9250_REG_H_INCLUDED
#define MPU9250_REG_H_INCLUDED

#define MPU9250_I2C_CLOCK_SPEED                  400000UL // I2C is 400KHz max
#define MPU9250_I2C_ADDRESS                      0x68 // This address is used by MPU9250 when ADC0 pin is logic low
#define MPU9250_I2C_ADDRESS_ALT                  0x69 // This address is used by MPU9250 when ADC0 pin is logic high

// Note, this is the reset value for all registers except
// - Register 107 (0x01) Power Management 1
// - Register 117 (0x71) WHO_AM_I
#define MPU9250_REG_RESET                        0x00
#define MPU9250_READ_MASK                        0x80

// Self Test, Gyro
#define MPU9250_SELF_TEST_X_GYRO                 0x00
#define MPU9250_SELF_TEST_Y_GYRO                 0x01
#define MPU9250_SELF_TEST_Z_GYRO                 0x02



// Self Test, Accelerometer
#define MPU9250_SELF_TEST_X_ACCEL                0x0d
#define MPU9250_SELF_TEST_Y_ACCEL                0x0e
#define MPU9250_SELF_TEST_Z_ACCEL                0x0f

// Gyro Offset
#define MPU9250_XG_OFFSET_H                      0x13
#define MPU9250_XG_OFFSET_L                      0x14
#define MPU9250_YG_OFFSET_H                      0x15
#define MPU9250_YG_OFFSET_L                      0x16
#define MPU9250_ZG_OFFSET_H                      0x17
#define MPU9250_ZG_OFFSET_L                      0x18


#define MPU9250_SMPLRT_DIV                       0x19

// Config
#define MPU9250_CONFIG                           0x1a
#define MPU9250_GYRO_CONFIG                      0x1b
#define MPU9250_ACCEL_CONFIG                     0x1c
#define MPU9250_ACCEL_CONFIG_2                   0x1d
#define MPU9250_LP_ACCEL_ODR                     0x1e

#define MPU9250_WOM_THR                          0x1f

#define MPU9250_FIFO_EN                          0x23

// I2C
#define MPU9250_I2C_MST_CTRL                     0x24
#define MPU9250_I2C_SLV0_ADDR                    0x25
#define MPU9250_I2C_SLV0_REG                     0x26
#define MPU9250_I2C_SLV0_CTRL                    0x27

#define MPU9250_I2C_SLV1_ADDR                    0x28
#define MPU9250_I2C_SLV1_REG                     0x29
#define MPU9250_I2C_SLV1_CTRL                    0x2a

#define MPU9250_I2C_SLV2_ADDR                    0x2b
#define MPU9250_I2C_SLV2_REG                     0x2c
#define MPU9250_I2C_SLV2_CTRL                    0x2d

#define MPU9250_I2C_SLV3_ADDR                    0x2e
#define MPU9250_I2C_SLV3_REG                     0x2f
#define MPU9250_I2C_SLV3_CTRL                    0x30

#define MPU9250_I2C_SLV4_ADDR                    0x31
#define MPU9250_I2C_SLV4_REG                     0x32
#define MPU9250_I2C_SLV4_DO                      0x33
#define MPU9250_I2C_SLV4_CTRL                    0x34
#define MPU9250_I2C_SLV4_DI                      0x35

#define MPU9250_I2C_MST_STATUS                   0x36

#define MPU9250_INT_PIN_CFG                      0x37
#define MPU9250_INT_ENABLE                       0x38

#define MPU9250_DMP_INT_STATUS                   0x39					// Check DMP Interrupt, see 0x6d

#define MPU9250_INT_STATUS                       0x3a

// Accel XOUT
#define MPU9250_ACCEL_XOUT_H                     0x3b
#define MPU9250_ACCEL_XOUT_L                     0x3c
#define MPU9250_ACCEL_YOUT_H                     0x3d
#define MPU9250_ACCEL_YOUT_L                     0x3e
#define MPU9250_ACCEL_ZOUT_H                     0x3f
#define MPU9250_ACCEL_ZOUT_L                     0x40

// Temp.
#define MPU9250_TEMP_OUT_H                       0x41
#define MPU9250_TEMP_OUT_L                       0x42

// Gyro.
#define MPU9250_GYRO_XOUT_H                      0x43
#define MPU9250_GYRO_XOUT_L                      0x44
#define MPU9250_GYRO_YOUT_H                      0x45
#define MPU9250_GYRO_YOUT_L                      0x46
#define MPU9250_GYRO_ZOUT_H                      0x47
#define MPU9250_GYRO_ZOUT_L                      0x48


// Magneticmeter
#define AK8963_I2C_ADDR							0x0C				// slave address for the AK8963
#define AK8963_DEVICE_ID						0x48				// Device ID read only
#define AK8963_WIA								0x00				// Device ID read only
#define AK8963_INFO								0x01				// Device information
#define AK8963_ST1								0x02				// data ready status bit 0
#define AK8963_XOUT_L							0x03				// Measurement X lower 8 bit
#define AK8963_XOUT_H							0x04				// Measurement X Higher 8 bit
#define AK8963_YOUT_L							0x05				// Measurement Y lower 8 bit
#define AK8963_YOUT_H							0x06				// Measurement Y Higher 8 bit
#define AK8963_ZOUT_L							0x07				// Measurement Z lower 8 bit
#define AK8963_ZOUT_H							0x08				// Measurement Z Higher 8 bit
#define AK8963_ST2								0x09				// Data overflow bit 3 and data read error status bit 2


#define AK8963_CNTL1							0x0A				// Power down (0000), single-measurement (0001), self-test (1000) and Fuse ROM (1111) modes on bits 3:0
#define AK8963_CNTL2							0x0B				// Soft reset
#define AK8963_ASTC								0x0C				// Self test control 
#define AK8963_TS1								0x0D				// Test register1 Do not use 
#define AK8963_TS2								0x0E				// Test register2 Do not use
#define AK8963_I2CDIS							0x0F				// I2C disable
#define AK8963_ASAX								0x10				// Fuse ROM x-axis sensitivity adjustment value
#define AK8963_ASAY								0x11				// Fuse ROM y-axis sensitivity adjustment value
#define AK8963_ASAZ								0x12				// Fuse ROM z-axis sensitivity adjustment value


// Ext. Sensor data
#define MPU9250_EXT_SENS_DATA_00                 0x49
#define MPU9250_EXT_SENS_DATA_01                 0x4a
#define MPU9250_EXT_SENS_DATA_02                 0x4b
#define MPU9250_EXT_SENS_DATA_03                 0x4c
#define MPU9250_EXT_SENS_DATA_04                 0x4d
#define MPU9250_EXT_SENS_DATA_05                 0x4e
#define MPU9250_EXT_SENS_DATA_06                 0x4f
#define MPU9250_EXT_SENS_DATA_07                 0x50
#define MPU9250_EXT_SENS_DATA_08                 0x51
#define MPU9250_EXT_SENS_DATA_09                 0x52
#define MPU9250_EXT_SENS_DATA_10                 0x53
#define MPU9250_EXT_SENS_DATA_11                 0x54
#define MPU9250_EXT_SENS_DATA_12                 0x55
#define MPU9250_EXT_SENS_DATA_13                 0x56
#define MPU9250_EXT_SENS_DATA_14                 0x57
#define MPU9250_EXT_SENS_DATA_15                 0x58
#define MPU9250_EXT_SENS_DATA_16                 0x59
#define MPU9250_EXT_SENS_DATA_17                 0x5a
#define MPU9250_EXT_SENS_DATA_18                 0x5b
#define MPU9250_EXT_SENS_DATA_19                 0x5c
#define MPU9250_EXT_SENS_DATA_20                 0x5d
#define MPU9250_EXT_SENS_DATA_21                 0x5e
#define MPU9250_EXT_SENS_DATA_22                 0x5f
#define MPU9250_EXT_SENS_DATA_23                 0x60

// I2C slave
#define MPU9250_I2C_SLV0_DO                      0x63
#define MPU9250_I2C_SLV1_DO                      0x64
#define MPU9250_I2C_SLV2_DO                      0x65
#define MPU9250_I2C_SLV3_DO                      0x66

#define MPU9250_I2C_MST_DELAY_CTRL               0x67


// Signal path
#define MPU9250_SIGNAL_PATH_RESET                0x68

// Motion detect
#define MPU9250_MOT_DETECT_CTRL                  0x69

// User
#define MPU9250_USER_CTRL                        0x6a // Bit 7 enable DMP, bit 3 reset DMP. See 0x6d

// Power management
#define MPU9250_PWR_MGMT_1                       0x6b
#define MPU9250_PWR_MGMT_2                       0x6c

// ...Looked for notes on DMP features, but Invensense docs were lacking.
// Found kriswiner's Arduino sketch for Basic AHRS, and found values/notes for
// Digital Motion Processing registers.
//
// See https://github.com/kriswiner/MPU-9250/blob/master/MPU9250BasicAHRS.ino
#define MPU9250_DMP_BANK                         0x6d
#define MPU9250_DMP_RW_PNT                       0x6e
#define MPU9250_DMP_REG                          0x6f
#define MPU9250_DMP_REG_1                        0x70
#define MPU9250_DMP_REG_2                        0x71

// FIFO Count
#define MPU9250_FIFO_COUNTH                      0x72
#define MPU9250_FIFO_COUNTL                      0x73
#define MPU9250_FIFO_R_W                         0x74
#define MPU9250_FIFO_WHO_AM_I                    0x75

// Accel. offset
#define MPU9250_XA_OFFSET_H                      0x77
#define MPU9250_XA_OFFSET_L                      0x78
#define MPU9250_YA_OFFSET_H                      0x7a
#define MPU9250_YA_OFFSET_L                      0x7b
#define MPU9250_ZA_OFFSET_H                      0x7d
#define MPU9250_ZA_OFFSET_L                      0x7e

#endif

#endif /* REGISTER_MAP_H_ */