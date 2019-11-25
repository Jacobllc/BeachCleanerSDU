/*
 * MPU_9250.h
 *
 * Created: 20.9.2019 20:39:43
 *  Author: Hörður Hermannsson 
 */ 

#ifndef MPU_9250_H
#define MPU_9250_H

 #define  F_CPU 16000000
 #include <util/delay.h>


// Constants definition 

#define GFORCE 9.805
#define magno_scale 4800/32768
#define PI 3.1416
#define coeffaccel 10
#define Max_value 32767
#define Min_value -32768

// Variables
float Gyro_x, Gyro_y, Gyro_z;
float Accel_x, Accel_y, Accel_z;
int Accel_moving_average_x[coeffaccel], Accel_moving_average_y[coeffaccel], Accel_moving_average_z[coeffaccel];
int Magnometer_x, Magnometer_y, Magnometer_z, Magnometer_x_min, Magnometer_x_max, Magnometer_y_min, Magnometer_y_max, Magnometer_z_min, Magnometer_z_max ;
float ASAX, ASAY, ASAZ;
float Heading;

// Function prototypes
void MPU9250_init();
void AK8963_init();
int MPU9250_getdata(uint8_t data, uint8_t address);
void MPU9250_setdata( uint8_t data, uint8_t register_Val, uint8_t address );
void Gyro_x_out(void);
void Gyro_y_out(void);
void Gyro_z_out(void);
void Accel_x_out(void);
void Accel_y_out(void);
void Accel_z_out(void);
void Magnometer_out(void);
void Heading_out(void);
void print_gyro(void);
void print_accelerometer(void);
void print_magnometer(void);
void print_heading(void);










#endif

