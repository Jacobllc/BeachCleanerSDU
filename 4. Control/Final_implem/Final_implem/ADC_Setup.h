/*
 * ADC_Setup.h
 *
 * Created: 10/24/2019 4:48:02 PM
 *  Author: Red
 */ 




#ifndef ADC_SETUP_H_
#define ADC_SETUP_H_

 float adc_result;
 uint8_t  Max_Curren;
 uint8_t  ADC_Channel;
 float adcv1, adcc1;
 int mes[3];

void Enable_ADC(void);
uint16_t adc_read(uint8_t adc_channel);
void Calculate_ADC(void);



#endif /* ADC_SETUP_H_ */