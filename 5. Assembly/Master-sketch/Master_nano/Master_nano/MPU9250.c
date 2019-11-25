/*
 * MPU9250.c
 *
 * Created: 20.9.2019 20:40:15
 *  Author: User
 */ 

 #include <avr/io.h>
 #include <stdio.h>
 #include "i2c_atmega_328p_master.h"
 #include "Register_map.h" 
 #include "MPU_9250.h"
 #include <math.h>
 
 
 void MPU9250_init()
 {
	 
	  MPU9250_setdata(0X80, MPU9250_PWR_MGMT_1, MPU9250_I2C_ADDRESS );		//Reseting the device
	  _delay_ms(100);
	  MPU9250_setdata(0X00, MPU9250_PWR_MGMT_1, MPU9250_I2C_ADDRESS );		// Clear sleep mode bit (6), enable all sensors
	  _delay_ms(100);
	  MPU9250_setdata(0X01, MPU9250_PWR_MGMT_1, MPU9250_I2C_ADDRESS );		// Set clock source 
	  MPU9250_setdata(0X00, MPU9250_PWR_MGMT_2, MPU9250_I2C_ADDRESS );		// Enable Gyro and Accelerator	 
	  MPU9250_setdata(0X00, MPU9250_CONFIG, MPU9250_I2C_ADDRESS );			// Gyro LPF Bandwidth 250 Hz					
	  MPU9250_setdata(0x00, MPU9250_SMPLRT_DIV, MPU9250_I2C_ADDRESS);		// Sampling rate 1Khz  
	  MPU9250_setdata(0x00, MPU9250_GYRO_CONFIG, MPU9250_I2C_ADDRESS);		// Gyro full scale 250 DPS (degree per seconds)
	  MPU9250_setdata(0x00, MPU9250_ACCEL_CONFIG, MPU9250_I2C_ADDRESS);		// Accelerometer full scale +/- 2G	
	  MPU9250_setdata(0x03, MPU9250_ACCEL_CONFIG_2, MPU9250_I2C_ADDRESS);	// Accelerometer LPF Bandwidth 41 Hz
	  MPU9250_setdata(0x02, MPU9250_INT_PIN_CFG, MPU9250_I2C_ADDRESS);		// By Pass enable 
		
	   for (int i=0; i<coeffaccel; i++)
	   {
		   Accel_moving_average_x[i]=0;
		   Accel_moving_average_y[i]=0;
		   Accel_moving_average_z[i]=0;
	   }
	   
 }
 
 void AK8963_init()
 {
		int senseData_x, senseData_y, senseData_z;
		 
		Magnometer_x_min=Max_value;
		Magnometer_x_max=Min_value;
		Magnometer_y_min=Max_value;
		Magnometer_y_max=Min_value;
		Magnometer_z_min=Max_value;
		Magnometer_z_max=Min_value;
		MPU9250_setdata(0x00, AK8963_CNTL1, AK8963_I2C_ADDR);			// Power down magnetometer
		_delay_us(100);
		MPU9250_setdata(0x0F, AK8963_CNTL1, AK8963_I2C_ADDR);			// Enter Fuse ROM access mode
		_delay_us(100);
		senseData_x=MPU9250_getdata(AK8963_ASAX, MPU9250_I2C_ADDRESS );	//Getting Magnetic sensor adjustment value 
		senseData_y=MPU9250_getdata(AK8963_ASAY, MPU9250_I2C_ADDRESS );	//Getting Magnetic sensor adjustment value 
		senseData_z=MPU9250_getdata(AK8963_ASAZ, MPU9250_I2C_ADDRESS );	//Getting Magnetic sensor adjustment value 	
		
		ASAX= (((senseData_x-128)*0.5)/128)+1;							// Magnometer adjust values 
		ASAY= (((senseData_y-128)*0.5)/128)+1;							// Magnometer adjust values 
		ASAZ= (((senseData_z-128)*0.5)/128)+1;							// Magnometer adjust values 
		
		MPU9250_setdata(0x00, AK8963_CNTL1, AK8963_I2C_ADDR);			// Power down magnetometer
		_delay_us(100);
	
		MPU9250_setdata(0x16, AK8963_CNTL1, AK8963_I2C_ADDR);			// Set the magnemeter to continous mode 2 (100Hz) and 16-bit
		_delay_us(100);
		
 }

int MPU9250_getdata(uint8_t data, uint8_t address)
{
	uint8_t result=0;
	i2c_start(address<<1 | I2C_WRITE);
	i2c_write(data);
	i2c_start(address<<1 | I2C_READ);
	result=i2c_read_nack();
	i2c_stop();
	return result;

}

void MPU9250_setdata( uint8_t data, uint8_t register_Val, uint8_t address )
{
	
	i2c_start(address<<1 | I2C_WRITE);
	i2c_write(register_Val);
	i2c_write(data);
	i2c_stop();

}

void Gyro_x_out()
{
	uint8_t data[2];
	int sample=0;
	
    
	data[0] = MPU9250_getdata(MPU9250_GYRO_XOUT_L, MPU9250_I2C_ADDRESS );	
	data[1] = MPU9250_getdata(MPU9250_GYRO_XOUT_H, MPU9250_I2C_ADDRESS );	
	
	sample= data[1]<<8;
	sample = sample | data[0];
	
	Gyro_x=((float)sample*250)/32768;
	
}
	

void Gyro_y_out()
{
	uint8_t data[2];
	int sample=0;
	
	data[0] = MPU9250_getdata(MPU9250_GYRO_YOUT_L, MPU9250_I2C_ADDRESS );
	data[1] = MPU9250_getdata(MPU9250_GYRO_YOUT_H, MPU9250_I2C_ADDRESS );
	
	sample= data[1]<<8;
	sample = sample | data[0];
	
	Gyro_y=((float)sample*250)/32768;
}

void Gyro_z_out()
{
	uint8_t data[2];
	int sample=0;
	
	data[0] = MPU9250_getdata(MPU9250_GYRO_ZOUT_L, MPU9250_I2C_ADDRESS );
	data[1] = MPU9250_getdata(MPU9250_GYRO_ZOUT_H, MPU9250_I2C_ADDRESS );
	
	sample= data[1]<<8;
	sample = sample | data[0];
	
	Gyro_z=((float)sample*250)/32768;
}

void Accel_x_out()
{
	uint8_t data[2];
	int sample=0;
	long int sum=0;
	
	data[0] = MPU9250_getdata(MPU9250_ACCEL_XOUT_L, MPU9250_I2C_ADDRESS );
	data[1] = MPU9250_getdata(MPU9250_ACCEL_XOUT_H, MPU9250_I2C_ADDRESS );
	
	sample= data[1]<<8;
	sample = sample | data[0];
	
	  for (int i=1; i<coeffaccel; i++)
	  {
		  Accel_moving_average_x[i+1]=Accel_moving_average_x[i];
	  }
		   Accel_moving_average_x[0]=sample;
		   
		for (int i=0; i<coeffaccel; i++)
		{
			sum=sum+Accel_moving_average_x[i];
		}  
	
		sum=sum/coeffaccel;
		Accel_x=((float)sum/32768)*2*GFORCE;

}

void Accel_y_out()
{
	uint8_t data[2];
	int sample=0;
	long int sum=0;
	
	data[0] = MPU9250_getdata(MPU9250_ACCEL_YOUT_L, MPU9250_I2C_ADDRESS );
	data[1] = MPU9250_getdata(MPU9250_ACCEL_YOUT_H, MPU9250_I2C_ADDRESS );
	
	sample= data[1]<<8;
	sample = sample | data[0];
	
			
			for (int i=1; i<coeffaccel; i++)
			{
				Accel_moving_average_y[i+1]=Accel_moving_average_y[i];
			}
			Accel_moving_average_y[0]=sample;
			
			for (int i=0; i<coeffaccel; i++)
			{
				sum=sum+Accel_moving_average_y[i];
			}
						
			sum=sum/coeffaccel;
			Accel_y=((float)sum/32768)*2*GFORCE;
}

void Accel_z_out()
{
	uint8_t data[2];
	int sample=0;
	long int sum=0;
	
	data[0] = MPU9250_getdata(MPU9250_ACCEL_ZOUT_L, MPU9250_I2C_ADDRESS );
	data[1] = MPU9250_getdata(MPU9250_ACCEL_ZOUT_H, MPU9250_I2C_ADDRESS );
	
	sample= data[1]<<8;
	sample = sample | data[0];
	
		
		for (int i=1; i<coeffaccel; i++)
		{
			Accel_moving_average_z[i+1]=Accel_moving_average_z[i];
		}
		Accel_moving_average_z[0]=sample;
		
		for (int i=0; i<coeffaccel; i++)
		{
			sum=sum+Accel_moving_average_z[i];
		}
		
		sum=sum/coeffaccel;
		Accel_z=((float)sum/32768)*2*GFORCE;
}


void Magnometer_out(void)
{
	uint8_t data[6];
	char data_ready=0;
	char overflow=0;
	int offset_x, offset_y, offset_z;
	data_ready=MPU9250_getdata(MPU9250_INT_PIN_CFG, MPU9250_I2C_ADDRESS );
	
	while(!(data_ready & (1<<1)));
	
		
	data[0] = MPU9250_getdata(AK8963_XOUT_L, AK8963_I2C_ADDR );
	data[1] = MPU9250_getdata(AK8963_XOUT_H, AK8963_I2C_ADDR );
	
	data[2] = MPU9250_getdata(AK8963_YOUT_L, AK8963_I2C_ADDR );
	data[3] = MPU9250_getdata(AK8963_YOUT_H, AK8963_I2C_ADDR );
	
	data[4] = MPU9250_getdata(AK8963_ZOUT_L, AK8963_I2C_ADDR );
	data[5] = MPU9250_getdata(AK8963_ZOUT_H, AK8963_I2C_ADDR );

	overflow=MPU9250_getdata(AK8963_ST2, AK8963_I2C_ADDR);
	
	if(!(overflow & (4<<4)))
	{
	
	Magnometer_x= data[1]<<8;
	Magnometer_x = Magnometer_x | data[0];
	
	Magnometer_y= data[3]<<8;
	Magnometer_y = Magnometer_y | data[2];
	
	
	Magnometer_z= data[5]<<8;
	Magnometer_z = Magnometer_z | data[4];
/*	
	if (Magnometer_x>Magnometer_x_max)
		Magnometer_x_max=Magnometer_x;
		
	if (Magnometer_x<Magnometer_x_min)
		Magnometer_x_min=Magnometer_x;
	
	if (Magnometer_y>Magnometer_y_max)
	Magnometer_y_max=Magnometer_y;
	
	if (Magnometer_y<Magnometer_y_min)
	Magnometer_y_min=Magnometer_y;
	
	if (Magnometer_z>Magnometer_z_max)
	Magnometer_z_max=Magnometer_z;
	
	if (Magnometer_z<Magnometer_z_min)
	Magnometer_z_min=Magnometer_z;
	
	offset_x=(Magnometer_x_max-Magnometer_x_min)/2;
	offset_y=(Magnometer_y_max-Magnometer_y_min)/2;
	offset_z=(Magnometer_z_max-Magnometer_z_min)/2;
*/	
	Magnometer_x = (Magnometer_x * ASAX * magno_scale);
	Magnometer_y = (Magnometer_y * ASAX * magno_scale);
	Magnometer_z = (Magnometer_z * ASAX * magno_scale);
	
	}

	
	Heading_out();
	
}


void Heading_out(void)
{
	
	if(Magnometer_y>0)
	Heading = 90 - (atan((float)Magnometer_x/(float)Magnometer_y))*(180/PI);
	
	if(Magnometer_y<0)
	Heading = 270 - (atan((float)Magnometer_x/(float)Magnometer_y))*(180/PI);
			
	if(Magnometer_y==0)
	{
				
	if (Magnometer_x<0)
	Heading = 180;
	
	if (Magnometer_x>0)
	Heading = 0;
								
	}	
	
}


void print_gyro()
{
	printf("Gyro-X %.2f \t Gyro-Y %.2f \t Gyro-Z %.2f \n", Gyro_x, Gyro_y, Gyro_z);	
}

void print_accelerometer()
{
	printf("Acc-X %.2f \t   Acc-Y %.2f \t   Acc-Z %.2f \n", Accel_x, Accel_y, Accel_z);
}

void print_magnometer()
{
	printf("Magno_x %d \t Magno_y %d \t Magno_Z %d \n", Magnometer_x, Magnometer_y, Magnometer_z);
}

void print_heading()
{
	printf("Heading = %.2f \n", Heading);
}