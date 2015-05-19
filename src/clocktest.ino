// 
// Program to test the accuracy of a cheap DS1307 module
// using the 1PPS signal on an Adafruit Ultimate GPS

#include <stdint.h>

// Hook the PPS pin to Arduino Pin #2, IRQ 0
const int pps_pin = 2 ;
const int pps_irq = 0 ;

// Hook the CLK pin to Arduino Pin #3, IRQ 1
const int clk_pin = 3 ;
const int clk_irq = 1 ;

volatile uint32_t pps_cnt = 0UL;
volatile uint32_t clk_cnt = 0UL;

uint32_t old_pps_cnt = 0UL;
uint32_t old_clk_cnt = 0UL;

bool dirty = false ;

void
pps_interrupt()
{
    pps_cnt ++ ;
    dirty = true ;
}

void
clk_interrupt()
{
    clk_cnt ++ ;
}

void
setup() 
{
    Serial.begin(115200);
    Serial.println() ;
    Serial.println("CLOCKTEST") ;

    pinMode(pps_pin, INPUT) ;
    pinMode(clk_pin, INPUT) ;

    attachInterrupt(0, pps_interrupt, RISING) ;
    attachInterrupt(1, clk_interrupt, RISING) ;
}

void
loop()
{
    if (dirty) {
        old_pps_cnt = pps_cnt ;
        old_clk_cnt = clk_cnt ;
        dirty = false ;
        Serial.print(old_pps_cnt) ;
        Serial.print(",") ;
        Serial.println(old_clk_cnt) ;
    }
}
