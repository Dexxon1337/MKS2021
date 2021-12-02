#include "sct.h"
#include "stm32f0xx.h"

static const uint32_t reg_values[3][10] = {
		{
				//PCDE--------GFAB @ DIS1
				0b0111000000000111 << 16,
				0b0100000000000001 << 16,
				0b0011000000001011 << 16,
				0b0110000000001011 << 16,
				0b0100000000001101 << 16,
				0b0110000000001110 << 16,
				0b0111000000001110 << 16,
				0b0100000000000011 << 16,
				0b0111000000001111 << 16,
				0b0110000000001111 << 16,
		},
		{
				//----PCDEGFAB---- @ DIS2
				0b0000011101110000 << 0,
				0b0000010000010000 << 0,
				0b0000001110110000 << 0,
				0b0000011010110000 << 0,
				0b0000010011010000 << 0,
				0b0000011011100000 << 0,
				0b0000011111100000 << 0,
				0b0000010000110000 << 0,
				0b0000011111110000 << 0,
				0b0000011011110000 << 0,
		},
		{
				//PCDE--------GFAB @ DIS3
				0b0111000000000111 << 0,
				0b0100000000000001 << 0,
				0b0011000000001011 << 0,
				0b0110000000001011 << 0,
				0b0100000000001101 << 0,
				0b0110000000001110 << 0,
				0b0111000000001110 << 0,
				0b0100000000000011 << 0,
				0b0111000000001111 << 0,
				0b0110000000001111 << 0,
		},
};

void sct_noe(uint8_t x) {
		if (x) {
			GPIOB->BSRR = (1 << NLA_PIN);
		}
		else {
			GPIOB->BRR = (1 << NLA_PIN);
		}
}
void sct_clk(uint8_t x) {
	if (x) {
		GPIOB->BSRR = (1 << CLK_PIN);
	}
	else {
		GPIOB->BRR = (1 << CLK_PIN);
	}
}
void sct_sdi(uint8_t x) {
	if (x) {
		GPIOB->BSRR = (1 << SDI_PIN);
	}
	else {
		GPIOB->BRR = (1 << SDI_PIN);
	}
}

void sct_nla(uint8_t x) {
	if (x) {
		GPIOB->BSRR = (1 << NLA_PIN);
	}
	else {
		GPIOB->BRR = (1 << NLA_PIN);
	}
}

void sct_led(uint32_t value) {
	for (uint32_t a=0; a<=31; a++) {
		// SCT_SDA
		sct_sdi(value&1);
		sct_clk(1);
		sct_clk(0);
		value>>=1;
	}
	sct_nla(1);
	sct_nla(0);
}

void sct_value(uint16_t value) {
	uint32_t reg = 0;
	reg |= reg_values[0][value / 100 % 10];
	reg |= reg_values[1][value / 10 % 10];
	reg |= reg_values[2][value / 1 % 10];

	sct_led(reg);
}

void sct_init() {
	GPIOB->MODER |= GPIO_MODER_MODER3_0;  // PB3, output
	GPIOB->MODER |= GPIO_MODER_MODER4_0;  // PB4, output
	GPIOB->MODER |= GPIO_MODER_MODER5_0;  // PB3, output
	GPIOB->MODER |= GPIO_MODER_MODER10_0; // PB10, output
	sct_noe(0);
	sct_led(0);
}
