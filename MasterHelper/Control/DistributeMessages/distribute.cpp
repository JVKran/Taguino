#include "distribute.hpp"

transceiveMessage::transceiveMessage( hwlib::spi_bus & bus, hwlib::pin_out & ce, hwlib::pin_out & csn ):
	NRF47( bus, ce, csn, 5, 5 ) // Last two numbers are payload size and address width
{ auto nrf = NRF47; }

void transceiveMessage::writeMSG( uint8_t * val, uint8_t len, uint8_t user ){
	nrf.start();
	
	auto tmpAddress = address1;
	tmpAddres[0] = address[0];
	
	nrf.write_pipe( user, tmpAddress );                                   //set the address of default 5 bytes to send it to the right user
    nrf.tx_mode( user );                                                  //we need to be in tx_mode to be able to transmit

	nrf.write( val, len );                                             //transmitting the data in value with a length of len
    hwlib::cout << "send data" << hwlib::endl;

}

void transceiveMessage::readMSG(){
	nrf.start();
	
	nrf.write_register( RX_ADDR_P1, address1, 5 );
  	nrf.read_pipe( 3, address );                                         //on which pipe we are going to listen
  	nrf.rx_mode( 3 );                                                    //go into rx_mode to be able to receive data

  	uint8_t value[5] = {};                                            //the array in which we will put the data
  	uint8_t len = 5;
	
	for(;;){                                                           
      if( nrf.checkRXfifo() ){                                       //checks if there is something in the RX FIFO
          nrf.read( value, len );                                     //reads the RX FIFO
		
		  if( value[0] < 5 ){										// 0-4 are players
		 	writeMSG( value, len, 0 );								// Send data to master
		  }
		  if( value[0] == 5 ){										// 5 is master
		  	writeMSG( value, len, 1 );								// Write to all players
		  }
         hwlib::cout << "\n" << hwlib::flush;                        //set an enter after the array

         nrf.flush_rx();                                             //empties the RX FIFO
         
      }                                  
   }
}