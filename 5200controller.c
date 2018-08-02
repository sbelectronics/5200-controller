// 5200controller
//#define F_CPU 14745600

#include <stdio.h>

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <inttypes.h>

#include <util/atomic.h>
#include <util/delay.h>

#define POT_CLK_PIN  PB2
#define POT_CS_PIN PB1
#define POT_DATA_PIN  PB0

#define SPI_MOSI_HIGH PORTB |= (1<<POT_DATA_PIN)
#define SPI_MOSI_LOW PORTB &= ~(1<<POT_DATA_PIN)
#define SPI_CLK_HIGH PORTB |= (1<<POT_CLK_PIN)
#define SPI_CLK_LOW PORTB &= ~(1<<POT_CLK_PIN)
#define SPI_CS_HIGH PORTB |= (1<<POT_CS_PIN)
#define SPI_CS_LOW PORTB &= ~(1<<POT_CS_PIN)

uint8_t readADC(uint8_t mux)
{
    ADMUX =
            (1 << ADLAR) |     // left shift result
            (0 << REFS1) |     // Sets ref. voltage to VCC, bit 1
            (0 << REFS0) |     // Sets ref. voltage to VCC, bit 0
            (mux << MUX0);       // use ADC3 for input (PB4), MUX bit 0

    ADCSRA =
            (1 << ADEN)  |     // Enable ADC
            (1 << ADPS2) |     // set prescaler to 64, bit 2
            (1 << ADPS1) |     // set prescaler to 64, bit 1
            (0 << ADPS0);      // set prescaler to 64, bit 0

    ADCSRA |= (1 << ADSC);         // start ADC measurement
    while (ADCSRA & (1 << ADSC) ); // wait till conversion complete

    return ADCH;
}

void writeSPI(uint8_t v)
{
    uint8_t i;
    for (i=0; i<8; i++) {
        if (v & 128) {
            SPI_MOSI_HIGH;
        } else {
            SPI_MOSI_LOW;
        }

        SPI_CLK_HIGH;
        SPI_CLK_LOW;

        v = v << 1;
    }
}

void setPOT(uint8_t pot_num, uint8_t pot_val)
{
    SPI_CS_LOW;
    writeSPI(0x11 + pot_num);
    writeSPI(pot_val);
    //shiftOut(POT_DATA_PIN, POT_CLOCK_PIN, MSBFIRST, 0x11 + pot_num);
    //shiftOut(POT_DATA_PIN, POT_CLOCK_PIN, MSBFIRST, pot_val);
    SPI_CS_HIGH;
}

int main() {
    // configure SPI pins as outputs
    DDRB |= (1<<POT_DATA_PIN);
    DDRB |= (1<<POT_CLK_PIN);
    DDRB |= (1<<POT_CS_PIN);

    SPI_CLK_LOW;

    while (1) {
        uint8_t v;

        v = readADC(3); // Y
        //setPOT(1, 255-(v*19/20));

        setPOT(1, 255-((v-128)*18/20)+128);

        v = readADC(2); // X
        //setPOT(0, 255-(v*19/20));

        setPOT(0, 255-((v-128)*17/20)+128-4);
    }
    return 0;
}
