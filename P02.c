#INCLUDE <18f4550.h>
#FUSES NOPROTECT, NOWDT, NOLVP, HSPLL, PLL5, CPUDIV2
#USE delay(clock = 48M, crystal = 20M)

#BYTE TRISA = 0xF92
#BIT TRIGOUT = 0xF80.0
#BIT ECHO = 0xF80.1

#BYTE TRISC = 0xF94
#BYTE PORTC = 0xF82

#BYTE TRISD = 0xF95
#BYTE PORTD = 0xF83

#BYTE TRISB = 0xF93
#BYTE INTCON = 0xFF2
#BIT IPEN = 0xFD0.7
#BIT INT1IE = 0xFF0.3
#BIT INTEDG1 = 0xFF1.5

int med[10] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x67};
int8 cen = 0, uni = 0;
int32 cont1 = 0;
float32 t = 0.0, d = 0.0;

#INT_EXT1
void medUltra(){
    while(ECHO == 1){
         cont1++;
      }
   t = cont1*0.9764;
   d = t/58.4;
   cen = (int8)d/10;
   uni = (int8)(d - (cen*10));
   cont1 = 0;
}

void main(){
   
   TRISA = 0x06;
   TRISB = 0xFF;
   TRISC = 0x00;
   TRISD = 0x00;
   IPEN = 0;
   INTCON = 0b11000000;
   INT1IE = 1;
   INTEDG1 = 1;
   TRIGOUT = 0;
   
   while(TRUE){
         TRIGOUT = 1;
         delay_us(10);
         TRIGOUT = 0;
         
         PORTC = 0x80; 
         PORTD = med[uni]; 
         delay_ms(1);
      
         PORTC = 0x40; 
         PORTD = med[cen]; 
         delay_ms(1);
      }
}
