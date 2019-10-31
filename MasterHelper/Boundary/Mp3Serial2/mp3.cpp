#include "mp3.hpp"
#include "hwlib.hpp"
send::send(hwlib::pin_out & mp3Transmit, hwlib::pin_in & mp3Receive):
	mp3Transmit( mp3Transmit ),
	mp3Receive( mp3Receive )
{ hwuart();}

hwuart::hwuart(){

		    // enable the clock to port A
	    PMC->PMC_PCER0 = 1 << ID_PIOA;
		
	    // disable PIO Control on PA10 and PA11 and set up for Peripheral A
		PIOA->PIO_PDR   = PIO_PA10; 
		PIOA->PIO_ABSR &= ~PIO_PA10; 
		PIOA->PIO_PDR   = PIO_PA11; 
		PIOA->PIO_ABSR &= ~PIO_PA11; 

		// enable the clock to the USART
	    PMC->PMC_PCER0 = ( 0x01 << ID_USART0 );

	    // Reset and disable receiver and transmitter.
	    USART0->US_CR = US_CR_RSTRX | US_CR_RSTTX | US_CR_RXDIS | US_CR_TXDIS;

	    // Set the baudrate to 9600.

	    USART0->US_BRGR = 567; 

	    // No parity, normal channel mode.
	    USART0->US_MR = US_MR_PAR_NO /*| US_MR_NBSTOP_1_BIT | US_MR_CHRL_8_BIT*/ ;

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

void send::executeCMD( uint8_t CMD, uint8_t par1, uint8_t par2 ){ 		// Command, folder(in numbers 1-99), song(0-255)
	/*uint16_t checksum = -( versionByte + commandLength + CMD + acknowledge + par1 + par2 ); //Add all and invert it
	uint8_t commandLine[10] = { startByte, versionByte, commandLength, CMD, acknowledge, 
											 par1, par2, uint8_t(checksum >> 8), uint8_t (checksum & 0xFF), endByte}; // checksum shifting to send the first half and the second half as show
	*///126, 255, 6, CMD, 01,
	uint8_t testArray[10] = { 0x7E, 0xFF, 0x06, 0x03, 0x00, 0x00, 0x01, 0xFF, 0xE6, 0xEF };
	for( uint8_t i = 0; i<10; i++){
		sendUart( testArray[i] );
		hwlib::wait_us(400);
	}
	//readUart();
}

mp3::mp3( hwlib::pin_out & mp3Transmit, hwlib::pin_in & mp3Receive ):
	send(  mp3Transmit,  mp3Receive )
{}

void mp3::playSound( int sound ){ executeCMD( 3, 1, sound );  }			//0x03 = specify track command, folder 0, number with corresponding mp3 track

void mp3::pauseSound(){ executeCMD( 0x0E, 0, 0 );}					    //Pause

void mp3::setVolume( int volume ){ executeCMD( 6, 0, volume); };		// 6=set volume, nothing, volume range 0-30

void mp3::init(){ executeCMD( 0x3F, 0, 0 );}
//void mp3Control::dataReceived( uint32_t data, sounds select ){ //Pseudocode ; Read data from the transceiver and play the right sound
	
//	if(data == select[shot/death/win/lose/powerup]){ 
//		startSound( play(select[shot/death/win/lose/powerup]) );
//	}

//}				