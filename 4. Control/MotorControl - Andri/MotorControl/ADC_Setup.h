/*
 * ADC_Setup.h
 *
 * Created: 10/24/2019 4:48:02 PM
 *  Author: Red
 */ 




#ifndef ADC_SETUP_H_
#define ADC_SETUP_H_


uint16_t adc_result;
uint8_t  Max_Curren;
uint8_t  ADC_Channel;


void Enable_ADC(void);
uint16_t adc_read(uint8_t adc_channel);



#endif /* ADC_SETUP_H_ */