#define ADC_chnl 1;
static uint16_t adc_buf[ADC_chnl][320];
uint16_t getFreq(uint16_t chnl);
uint16_t getRMS(uint16_t chnl);
int16_t getMaxV();
int16_t getMinV();
int16_t getPP(); //peak to peak
