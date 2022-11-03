#include <avr/io.h>
#include <util/delay.h>
#include "adc.h"
#include "uart.h"

//define the components
#define sw 0
#define led2 1
#define ledsw 2


int main() {
  init();
  Serial.begin(9600);
  while (1)
  {
    // check if button is pressed or not
    int check = (PINB &(1<<sw))!=0;
    
    if( check != 1)
    {
      PORTB = PORTB | (1<<ledsw);
      uart_transmit('k');
      uart_transmit('e');
      uart_transmit('y');
      uart_transmit(' ');
      uart_transmit('p');
      uart_transmit('r');
      uart_transmit('e');
      uart_transmit('s');
      uart_transmit('s');
      uart_transmit('e');
      uart_transmit('d');
    }
    else
    {
      PORTB = PORTB &~ (1<<ledsw);
      
    }
 

   int adc_r = Adc_ReadChannel(0);
    Serial.println(adc_r);
    if(adc_r < 200) // chech the condition of ldr
    {
      PORTB = PORTB | (1<<led2);
      uart_transmit('L');
      uart_transmit('E');
      uart_transmit('D');
      uart_transmit(' ');
      uart_transmit('i');
      uart_transmit('s');
      uart_transmit(' ');
      uart_transmit('o');
      uart_transmit('n');
      _delay_ms(500);
    }
    else
    {
       PORTB = PORTB &~ (1<<led2);
      uart_transmit('L');
      uart_transmit('E');
      uart_transmit('D');
      uart_transmit(' ');
      uart_transmit('i');
      uart_transmit('s');
      uart_transmit(' ');
      uart_transmit('o');
      uart_transmit('f');
      uart_transmit('f');
      _delay_ms(500);
    }

  }
  return 0; 
}
  
void init(){
  // ldr is input
 // uart_init(9600);        
  Adc_Init();
  // button is input
  DDRB = DDRB & ~(1<<sw); // which is pin 8  
  PORTB = PORTB |(1 << sw); // activate pull up resistor
  
  // led is output for button
  DDRB = DDRB | (1<<ledsw); // connected to pin 10

   // led is output for ldr
  DDRB = DDRB | (1<<led2);  // connected to pin 9
  
  // ldr is connected to pin A0
 
}
