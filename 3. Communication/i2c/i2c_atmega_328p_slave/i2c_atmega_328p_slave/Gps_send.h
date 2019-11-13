/*
 * Gps_send.h
 *
 * Created: 11.11.2019 22:08:00
 *  Author: User
 */ 


#ifndef GPS_SEND_H_
#define GPS_SEND_H_




char bytes;
// Function prototypes

void Gps_send_status(void);
void Gps_send_Direction(void);
void Gps_send_Distance(void);
void i2c_service(void);
void set_opcode(uint8_t value);
int cal_checksum(int value, char length);



#endif /* GPS_SEND_H_ */