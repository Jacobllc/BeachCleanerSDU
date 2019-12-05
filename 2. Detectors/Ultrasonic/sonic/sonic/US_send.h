/*
 * Gps_send.h
 *
 * Created: 11.11.2019 22:08:00
 *  Author: User
 */ 

#ifndef GPS_SEND_H_
#define GPS_SEND_H_

//DATA *NMEA1; 


char bytes;
// Function prototypes
//void init_GPSDATA(struct DATA *GPS_Data_NMEA1);  //To access NMEA1 from main 

void i2c_service(void);
void set_opcode(uint8_t value);
int cal_checksum(int value, char length);
void US_send_zone(void);
void US_send_dist(int nr);


//void Gps_send_status(void);
//void Gps_send_Distance(void);



#endif /* GPS_SEND_H_ */