#include "serial.hpp"
#include "hwlib.hpp"
/*
send::send(hwlib::pin_out & mp3Transmit, hwlib::pin_in & mp3Receive):
	mp3Transmit( mp3Transmit ),
	mp3Receive( mp3Receive )
{ hwuart();}
*/
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

/*
void send::readUart(){  hwlib::cout<<uint8_t(usart_getc())<<"\n"; }
void send::sendUart( uint8_t c ){
	//hwlib::cout<< c << "\n";
	//hwlib::uart_putc_bit_banged_pin( c, mp3Transmit); 
	usart_putc( c );
	//if(usart_char_available()){
	//readUart();
	//}
	//hwlib::cout<<"ja"<<hwlib::endl;
}
*/

		