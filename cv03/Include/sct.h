#ifndef SCT_H_
#define SCT_H_
#include <stdint.h>

#define SDI_PIN 4
#define CLK_PIN 3
#define NLA_PIN 5
#define NOE_PIN 10

void sct_init();
void sct_value(uint16_t value);
void sct_noe(uint8_t x);
void sct_sdi(uint8_t x);
void sct_clk(uint8_t x);
void sct_nla(uint8_t x);
void sct_led(uint32_t value);

#endif /* SCT_H_ */
