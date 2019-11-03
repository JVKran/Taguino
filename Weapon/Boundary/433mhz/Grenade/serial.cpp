#include "serial.hpp"
#include "hwlib.hpp"
wuart();}

hwuart::hwuart(){

		    // enable the clock to port A
	    PMC->PMC_PCER0 = 1 << ID_PIOA;
		
	    // disable PIO Control on PA10 and PA11 and set up for Peripheral A
		PIOA->PIO_PDR   = PIO_PA10; 
		PIOA->PIO_ABSR &= ~PIO_PA10; 
		PIOA->PIO_PDR   = PIO_PA11; 
		PIOA->PIO_ABSR &= ~PIO_PA11; 
        PIOA -> PIO_PUDR |= PIO_PA10;

		// enable the clock to the USART
	    PMC->PMC_PCER0 = ( 0x01 << ID_USART0 );

	    // Reset and disable receiver and transmitter.
	    USART0->US_CR = US_CR_RSTRX | US_CR_RSTTX | US_CR_RXDIS | US_CR_TXDIS;

	    // Set the baudrate to 9600.

	    USART0->US_BRGR = 2188; 

	    // No parity, normal channel mode.
	    USART0->US_MR = US_MR_PAR_NO| US_MR_NBSTOP_1_BIT | US_MR_CHRL_8_BIT;

	    // Disable all interrupts.	  
	    USART0->US_IDR = 0xFFFFFFFF;   

	    // Enable the receiver and the trasmitter.
	    USART0->US_CR = US_CR_RXEN | US_CR_TXEN;      
	}



	bool hwuart::usart_char_available(){
	   	
	   return ( USART0->US_CSR & 1 ) != 0;
	}

	char hwuart::usart_getc(){
	   // uart_init() is not needed because uart_char_available does that
	   while( ! usart_char_available() ){}
	   return USART0->US_RHR; 
	}
	void hwuart::usart_putc( char c ){
	      
	   //usart_init();	
	   while( ( USART0->US_CSR & 2 ) == 0 ){}
	   USART0->US_THR = c;

	}

void mhz433::write( uint8_t player, uint8_t damage ){
	 uint8_t checksum = ( damage / 256 ) ^ ( damage & 0xFF);
	
	// Start bit, player id, damage, sound, checksum, end bit.
	 uint8_t explosionData[amount] = { 100, player, damage, 1, checksum }; 
        
	 for(;;){
		 hwlib::wait_ms(500);
		 for(int i=0; i<amount; i++){
			usart_putc( explosionData[i] );
			hwlib::wait_us(400);
		 }
	 hwlib::cout<<"sending"<<hwlib::endl;
	 }
}

void mhz433::read(){
   for(;;){
	   
	   if( usart_getc() == 100 ){												// If it's the start bit
		   
		   uint8_t tmpArray[amount] = { 0, 0, 0, 0, 0 };
		   
		   for(int i=0; i<amount; i++){
			   tmpArray[i] = usart_getc();
			   hwlib::wait_us(800);
		   }
		   
		   for(int i=0; i<amount; i++){
			  hwlib::cout<<tmpArray[i]<<"\n";
			   hwlib::wait_us(800);
		   }
		   
		   uint8_t damage = tmpArray[1];
		   
		   if( tmpArray[4] != ( ( damage / 256 ) ^ ( damage & 0xFF) ) ){		// If the checksum is not the same, it will stop.
		   		return;
		   }
		   
		   // startPlayingSound( tmpArray[2] );									// Op positie 2 staat data voor muziek.
		   // Verzend de speler en damage naar de master via nrf
   		}

   }

}
		