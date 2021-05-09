#include "pic18f4550.h"
#include "main.h"
#include <stdio.h>
#include <string.h>

#define  O1_PIN PORTBbits.RB0
#define  O2_PIN PORTBbits.RB1
#define  O3_PIN PORTBbits.RB2
#define  O4_PIN PORTBbits.RB3
#define  Inp1_PIN  PORTBbits.RB4
#define  Inp2_PIN  PORTBbits.RB5
#define  Inp3_PIN  PORTBbits.RB6
#define  Inp4_PIN  PORTBbits.RB7

#define _XTAL_FREQ 20000000
#define lcd PORTD        // assing portd as lcd
#define rs PORTDbits.RD0 // rs pin for lcd control
#define en PORTDbits.RD1 // en pin for lcd control

//----------------------------------------------------

typedef union {

    struct {
        float FV; //32 bit
    };

    struct {
        unsigned char B0;
        unsigned char B1;
        unsigned char B2;
        unsigned char B3;
    };
} t_float;

void lcd_reset(void);                   // reset lcd
void lcd_cmd(unsigned char x);          // send command to lcd
void lcd_cmd_hf(unsigned char x);       // send 4 bit command to lcd
void lcd_dwr(unsigned char x);          // send data to lcd
void lcd_msg(unsigned char *c);         // send string of data to lcd
void lcd_init(void);                    // initializer
void lcd_lat(void);                     // latch lcd data

unsigned char GetKey(void);
unsigned char TaraKey(void);
unsigned char KeyOther(unsigned char key);
void KeyRelease(void);

void GetData(void);

void UART_Init(void);

unsigned char flag1 = 0;
unsigned char flag2 = 0;
unsigned char flag3 = 0;
unsigned char sequential = 0;
unsigned char pass = 0;
unsigned char proc[1];
long h[3] = 0;
unsigned char s_operand_minus = 0;
unsigned char f_operand_minus = 0;
unsigned char whole[25];
unsigned long operand1;
unsigned long operand2;
unsigned char ttt[25];
unsigned char get_count=0;
unsigned char bufferread[12];

void Send(unsigned char data)
{
    TXREG = data;
    while(TXSTAbits.TRMT == 0);
}

void main(){
   
    
    TRISB = 0b11110000;
    TRISD = 0x00;                      // D Ports are OUTPUT 
    lcd_init();                        // LCD INIT
    lcd_cmd(0x0F);                     // display on, cursor blinks, cursor 10
    
    UART_Init();
    
    t_float val;
    while(1){
        
        GetData(); //gets number as string and place it inside the whole
        
        val.FV = atof(whole);
        Send(0xAA);   // 11
        Send(0xFF);   // 10
        Send(val.B0); // 9
        Send(val.B1); // 8
        Send(val.B2); // 7
        Send(val.B3); // 6   
        
        GetData(); //gets number as string and place it inside the whole
                
        val.FV = atof(whole);
        Send(val.B0); // 5
        Send(val.B1); // 4
        Send(val.B2); // 3
        Send(val.B3); // 2   
        
        Send(proc[0]);// 1
        
        flag1 = GetKey();
        lcd_reset();
        flag1 = 0;
        flag2 = 0;
        proc[0] = 0;
        s_operand_minus = 0;
        f_operand_minus = 0;
        get_count = 0;
        
    }
}
void GetData(void){
    unsigned char j = 0;
    unsigned char y[2];
    do{
        y[0] = GetKey();
        whole[j] = y[0];
        y[1] = '\0';
        lcd_msg(&y[0]);
        
        if(j == 0 && (whole[0] == '-' || whole[0] == '+')){
            if(whole[0] == '-'){
                if(get_count == 0)
                    f_operand_minus = 1;
                if(get_count != 0)
                    s_operand_minus = 1;
            }
                y[0] = GetKey();
                whole[j] = y[0];
                y[1] = '\0';
                lcd_msg(&y[0]);
        }
        j++;
    }while(!(whole[j-1] == '+' || whole[j-1] == '=' || whole[j-1] == '-' || whole[j-1] == '/' || whole[j-1] == 'x'));
    
    if(whole[j-1] == '+' || whole[j-1] == '-' || whole[j-1] == '/' || whole[j-1] == 'x')
        proc[0] = whole[j-1];
    whole[j-1] = '\0';
    get_count++;
}

void lcd_reset(void){
    
    lcd_cmd(0x01);
    lcd_cmd(0x02);
}


void lcd_lat(void){
    //latching function high to low
    en =1 ;         // enable pin is high
    __delay_ms(1);    // 1 ms delay   
    en=0;           // enable pin is low
    
}
void lcd_cmd(unsigned char x){
    
    rs = 0 ;                   // register selected is command register
    lcd &= 0x0F;               // masking higher 4-bit of portD
    lcd |= (x & 0xF0);         // masking lower 4-bit of command
    lcd_lat();                 // latching it to lcd
    
    lcd &= 0x0F;                  // masking higher 4-bit of portD
    lcd |= ((x & 0x0F) << 4);     // masking higher 4-bit of command
    lcd_lat();                    // latching it to lcd

}

void lcd_cmd_hf(unsigned char x){
    
    rs = 0 ;                   // register selected is command register
    lcd &= 0x0F;               // masking higher 4- bit of portD
    lcd |= (x & 0xF0);         // masking lower 4-bit of command
    lcd_lat();                 // latching it to lcd
}

void lcd_dwr(unsigned char x){
    
    rs = 1;                 // Register select pin is set to data register
    lcd &= 0x0F;            // Masking higher 4-bit of portD
    lcd |= ( (x & 0xF0));   // Masking Lower 4-bit of data
    lcd_lat();              // latching it to lcd
    
    lcd &= 0x0F;            // Masking higher 4-bit of portD
    //lcd |= ( (x & 0xF0));   // Masking higher 4-bit of data
    lcd |= ((x & 0x0F) << 4);
    lcd_lat();              // latching it to lcd
    
}

void lcd_msg(unsigned char * c){
    
    while(*c !=0){
        lcd_dwr(*c++);
        
    } 
}

void lcd_init(void){

    lcd_cmd_hf(0x30);   //---Sending Sequence Command
    lcd_cmd_hf(0x20);   //---Sending Sequence Command
    lcd_cmd(0x28);      //---Command to Select 4-bit LCD
    lcd_cmd(0x0E);      //---Cursor Blinking
    lcd_cmd(0x01);      //---Clear LCD Display
    lcd_cmd(0x06);      //---Auto-Increment LCD
    lcd_cmd(0x80);      
 
}
void __interrupt() ISR(void){
    
    //If the received interrupt is because of
    //data received in UART
    unsigned char a;
    
    if(PIR1bits.RCIF == 1)
    {
        //TXREG = RCREG;

        t_float al;
        a = RCREG;  
        char arra[12];
        // take message
        bufferread[11] = bufferread[10];
        bufferread[10] = bufferread[9];
        bufferread[9] = bufferread[8];
        bufferread[8] = bufferread[7];
        bufferread[7] = bufferread[6];
        bufferread[6] = bufferread[5];
        bufferread[5] = bufferread[4];
        bufferread[4] = bufferread[3];
        bufferread[3] = bufferread[2];
        bufferread[2] = bufferread[1];
        bufferread[1] = a;

        if(bufferread[5] == 255 && bufferread[6] == 170){

            al.B0 = bufferread[4];
            al.B1 = bufferread[3];
            al.B2 = bufferread[2];
            al.B3 = bufferread[1];
            sprintf(arra,"%f", al.FV);  
            lcd_msg(arra);
       }
    }
}

void UART_Init(void){
    
    TRISCbits.RC7 = 1; // SET AS INPUT
    
    TRISCbits.RC6 = 0; // SET AS OUTPUT
    
    //Select 8bit transmission
    TXSTAbits.TX9 = 0;

    //Enable Transmit
    TXSTAbits.TXEN = 1;
    
    //Async mode select
    TXSTAbits.SYNC = 0;
    
    //Operate in Low Speed
    TXSTAbits.BRGH = 0;
 
    //Enable Serial Port
    RCSTAbits.SPEN = 1;
    
    //Enable continuous receive
    RCSTAbits.CREN = 1;
 
    //16bit baudrate
    BRG16 = 0;
    
    //Baudrate 9600
    SPBRG = 31;
 
    //Clear the receive interrupt flag
    PIR1bits.RCIF = 0;
    
    //Enable receive interrupt
    PIE1bits.RCIE = 1;
    
    //Enable global interrupt
    INTCONbits.GIE = 1;
    
    //Enable Peripheral interrupt
    INTCONbits.PEIE = 1;
}

void KeyRelease(void) {
    
    unsigned char key;
    do {
        do {
            key = TaraKey();
        } while (key != 0xFF);

        __delay_ms(1);

        key = TaraKey();
    } while (key != 0xFF);
}

unsigned char GetKey(void) {
    
    unsigned char key;
    
    KeyRelease();
    
    do {
        key = TaraKey();
    } while (key == 0xFF);

    return key;
}

unsigned char TaraKey(void){
    
    O1_PIN = 0;
    O2_PIN = 1;
    O3_PIN = 1;
    O4_PIN = 1;
        
    __delay_ms(2);
    if (Inp1_PIN == 0){ __delay_ms(10); return(55);}
    if (Inp2_PIN == 0){ __delay_ms(10); return('8');}
    if (Inp3_PIN == 0){ __delay_ms(10); return('9');}
    if (Inp4_PIN == 0){ __delay_ms(10); return('/');}
    
    O1_PIN = 1;
    O2_PIN = 0;
    O3_PIN = 1;
    O4_PIN = 1;
    
    __delay_ms(2);
    if (Inp1_PIN == 0){ __delay_ms(10); return('4');}
    if (Inp2_PIN == 0){ __delay_ms(10); return('5');}
    if (Inp3_PIN == 0){ __delay_ms(10); return('6');}
    if (Inp4_PIN == 0){ __delay_ms(10); return('x');}

    O1_PIN = 1;
    O2_PIN = 1;
    O3_PIN = 0;
    O4_PIN = 1;
    
    __delay_ms(2);
    if (Inp1_PIN == 0){ __delay_ms(10); return('1');}
    if (Inp2_PIN == 0){ __delay_ms(10); return('2');}
    if (Inp3_PIN == 0){ __delay_ms(10); return('3');}
    if (Inp4_PIN == 0){ __delay_ms(10); return('-');}
    
    O1_PIN = 1;
    O2_PIN = 1;
    O3_PIN = 1;    
    O4_PIN = 0;
    
    __delay_ms(2);
    if (Inp1_PIN == 0){ __delay_ms(10); return('N');}
    if (Inp2_PIN == 0){ __delay_ms(10); return('0');}
    if (Inp3_PIN == 0){ // if = is pressed
        
        while(Inp3_PIN == 0)
        {

            if( KeyOther('=') == '0'){

                return '.';
            }
            
            O1_PIN = 1;
            O2_PIN = 1;
            O3_PIN = 1;    
            O4_PIN = 0;

        }
        return '=';
    }
    if (Inp4_PIN == 0){ __delay_ms(10); return('+');}
    
    return (0xff);
    
}

unsigned char KeyOther(unsigned char key){
    
    O1_PIN = 0;
    O2_PIN = 1;
    O3_PIN = 1;
    O4_PIN = 1;
        
    __delay_ms(2);
    if ((Inp1_PIN == 0) && (key != 55))  return(55);
    if ((Inp2_PIN == 0) && (key != '8'))  return('8');
    if ((Inp3_PIN == 0) && (key != '9'))  return('9');
    if ((Inp4_PIN == 0) && (key != '/'))  return('/');
    
    O1_PIN = 1;
    O2_PIN = 0;
    O3_PIN = 1;
    O4_PIN = 1;
    
    __delay_ms(2);
    if ((Inp1_PIN == 0) && (key != '4')) return('4');
    if ((Inp2_PIN == 0) && (key != '5'))  return('5');
    if ((Inp3_PIN == 0) && (key != '6'))  return('6');
    if ((Inp4_PIN == 0) && (key != 'x')) return('x');

    O1_PIN = 1;
    O2_PIN = 1;
    O3_PIN = 0;
    O4_PIN = 1;
    
    __delay_ms(2);
    if ((Inp1_PIN == 0) && (key != '1'))  return('1');
    if ((Inp2_PIN == 0) && (key != '2'))  return('2');
    if ((Inp3_PIN == 0) && (key != '3'))  return('3');
    if ((Inp4_PIN == 0) && (key != '-'))  return('-');
    
    O1_PIN = 1;
    O2_PIN = 1;
    O3_PIN = 1;    
    O4_PIN = 0;
    
    __delay_ms(2);
    if ((Inp1_PIN == 0) && (key != 'N')) return('N');
    if ((Inp2_PIN == 0) && (key != '0')) return('0');
    if ((Inp3_PIN == 0) && (key != '='))  return('=');
    if ((Inp4_PIN == 0) && (key != '+'))  return('+');
    
    return (0xff); 
}
