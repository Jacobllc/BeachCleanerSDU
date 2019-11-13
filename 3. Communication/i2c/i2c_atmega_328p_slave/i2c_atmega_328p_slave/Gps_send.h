/*
 * Gps_send.h
 *
 * Created: 11.11.2019 22:08:00
 *  Author: User
 */ 


#ifndef GPS_SEND_H_
#define GPS_SEND_H_




// Function prototypes

void Gps_send_status(void);
void Gps_send_Direction(void);
void Gps_send_Distance(void);
void i2c_service(void);
void set_opcode(uint8_t value);

#endif /* GPS_SEND_H_ */