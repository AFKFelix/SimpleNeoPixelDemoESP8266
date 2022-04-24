#define pin 5
#define numPixels 64

inline void IRAM_ATTR setPinOn(){
    *(volatile uint32_t *)0x60000304 = 1 << pin;    //set pin output to HIGH 
}

inline void IRAM_ATTR setPinOff(){
    *(volatile uint32_t *)0x60000308 = 1 << pin;    //set pin output to LOW 
}

inline void IRAM_ATTR sendBit0(){   //send a bit with value 0
    setPinOn(); //set pin to HIGH 

    // delay 0.35us 350ns 28 cycles
    asm volatile("nop; nop; nop; nop; nop; nop; nop; nop;"); // 100 ns delay
    asm volatile("nop; nop; nop; nop; nop; nop; nop; nop;"); // 100 ns delay
    asm volatile("nop; nop; nop; nop; nop; nop; nop; nop;"); // 100 ns delay
    asm volatile("nop; nop; nop; nop;"); // 50 ns delay             

    setPinOff(); //set pin to LOW

    // delay 0.80us 800ns 64 cycles

    asm volatile("nop; nop; nop; nop; nop; nop; nop; nop;"); // 100 ns delay
    asm volatile("nop; nop; nop; nop; nop; nop; nop; nop;"); // 100 ns delay
    asm volatile("nop; nop; nop; nop; nop; nop; nop; nop;"); // 100 ns delay
    asm volatile("nop; nop; nop; nop; nop; nop; nop; nop;"); // 100 ns delay
    asm volatile("nop; nop; nop; nop; nop; nop; nop; nop;"); // 100 ns delay
    asm volatile("nop; nop; nop; nop; nop; nop; nop; nop;"); // 100 ns delay
    asm volatile("nop; nop; nop; nop; nop; nop; nop; nop;"); // 100 ns delay
    asm volatile("nop; nop; nop; nop; nop; nop; nop; nop;"); // 100 ns delay
}

inline void IRAM_ATTR sendBit1(){ //send a bit with value 1
  setPinOn(); //set pin to HIGH 

  //delay 0.7us 700ns 56 cycles
  asm volatile("nop; nop; nop; nop; nop; nop; nop; nop;"); //100 ns delay
  asm volatile("nop; nop; nop; nop; nop; nop; nop; nop;"); //100 ns delay
  asm volatile("nop; nop; nop; nop; nop; nop; nop; nop;"); //100 ns delay
  asm volatile("nop; nop; nop; nop; nop; nop; nop; nop;"); //100 ns delay
  asm volatile("nop; nop; nop; nop; nop; nop; nop; nop;"); //100 ns delay
  asm volatile("nop; nop; nop; nop; nop; nop; nop; nop;"); //100 ns delay
  asm volatile("nop; nop; nop; nop; nop; nop; nop; nop;"); //100 ns delay

  setPinOff(); //set pin to LOW

  //delay 0.6us 600ns 48 cycles
  asm volatile("nop; nop; nop; nop; nop; nop; nop; nop;"); //100 ns delay
  asm volatile("nop; nop; nop; nop; nop; nop; nop; nop;"); //100 ns delay
  asm volatile("nop; nop; nop; nop; nop; nop; nop; nop;"); //100 ns delay
  asm volatile("nop; nop; nop; nop; nop; nop; nop; nop;"); //100 ns delay
  asm volatile("nop; nop; nop; nop; nop; nop; nop; nop;"); //100 ns delay
  asm volatile("nop; nop; nop; nop; nop; nop; nop; nop;"); //100 ns delay

}

inline void sendByte(byte byte){                //send a color byte
    for( int bit = 0 ; bit < 8 ; bit++ ) {      //go through the byte 
        if(bitRead(byte, bit)){                 //check bit value
            sendBit1();                         //send a one     
        }else 
        {
            sendBit0();                         //send a zero
        }
        
    }   
}

inline void sendColor(byte r, byte g, byte b){  //send the whole 24bit color data
    sendByte(g);
    sendByte(r);
    sendByte(b);
}

void fill(byte r, byte g, byte b){              //fill the whole strip with a color
    cli();
    for( int i=0; i<numPixels; i++ ) {
        sendColor( r , g , b );
    }
    sei();
}


void show() {
    delayMicroseconds(50);                      //wait the 50us to reset the signal   
}

void setupPixels(){
    pinMode(pin, OUTPUT);   //set pinmode to output
    setPinOff();            //set pin to low
}


void setup() {
  setupPixels();
}

void loop() {
  fill(0b11111111, 0b00000000, 0b00000000);
  delay(1000);
  fill(0b00000000, 0b11111111, 0b00000000);
  delay(1000);
  fill(0b00000000, 0b00000000, 0b11111111);
  delay(1000);
}
