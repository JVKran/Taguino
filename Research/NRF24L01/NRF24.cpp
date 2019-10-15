#include "NRF24.hpp"
#include "NRF24_register.hpp"
#include "hwlib.hpp"

NRF24::NRF24( hwlib::spi_bus & bus, hwlib::pin_out & ce, hwlib::pin_out & csn ):
   bus( bus ), ce( ce ), csn( csn ), payload_size( 5 ), addr_width( 5 )
{} 

NRF24::NRF24( hwlib::spi_bus & bus, hwlib::pin_out & ce, hwlib::pin_out & csn, uint8_t payload_size, uint8_t addr_width ):
   bus( bus ), ce( ce ), csn( csn ), payload_size( payload_size ), addr_width( addr_width )
{}

static const uint8_t pipe[] = {
   RX_ADDR_P0, RX_ADDR_P1, RX_ADDR_P2, RX_ADDR_P3, RX_ADDR_P4, RX_ADDR_P5
};

static const uint8_t pipe_enable[] = {
   ERX_P0, ERX_P1, ERX_P2, ERX_P3, ERX_P4, ERX_P5
};

static const uint8_t pipe_payload[] = {
   RX_PW_P0, RX_PW_P1, RX_PW_P2, RX_PW_P3, RX_PW_P4, RX_PW_P5
};

void NRF24::start(){
   set_ce( 0 );                                                                                                   //set the transmit/receive pin to 0
   set_csn( 1 );                                                                                                  //set csn to 1, to make sure we do not send accidently something

   hwlib::wait_ms( 200 );                                                                                         //wait till the nrf chip is done

   write_register( STATUS, 0x0c );                                                                                //write to the status register a certain value

   write_register( SETUP_RETR, (5 & 0xF) << ARD | (15 & 0xF) << ARC );									                  //sets the retries to 15 with a delay of 5

   write_register( RF_SETUP,  read_register(RF_SETUP) & ~( ( 1 << RF_DR_LOW  )  | ( 1 << RF_DR_HIGH ) ) );	      //sets the data rate to 1 Mbps

   setAddressWidth( addr_width );																					                  //sets the width of the address, by default it will be 5 bytes long

   write_register( RF_SETUP, read_register( RF_SETUP ) | ( 1 <<  RF_PWR_HIGH | 1 << RF_PWR_LOW ) );					//sets power output to low

   write_register( FEATURE, 0 );                                                                                  //set al features to 0
   write_register( DYNPD, 0 );                                                                                    //turn dynamic payload off
   write_register( STATUS, ( 1 << RX_DR ) |( 1 << TX_DS ) | ( 1 << MAX_RT ) );                                    //set certain values in the status register

   setChannel( 100 ); 			//default

   flush_rx();                //make the read pipe empty
   flush_tx();                //make the write pipe empty

   powerup();

   write_register( CONFIG, read_register( CONFIG ) & ~( 1 << PRIM_RX ) );                                         
}

void NRF24::transfer( uint8_t reg ){                                                //simple function to tranfser a single byte
   bus.transaction( csn ).write( reg );                                             //to transfer a single byte                                           
}

uint8_t NRF24::read_register( uint8_t reg ){

   set_csn( 0 );                                                                    //begin transaction
   bus.transaction( hwlib::pin_out_dummy ).write( R_REGISTER | ( 0x1F & reg ) );    //uses the read command to read specific registers
   uint8_t result = bus.transaction( hwlib::pin_out_dummy ).read_byte();            //reads the byte that is send back
   set_csn( 1 );                                                                    //stop transaction

   return result;
}

void NRF24::read_register( uint8_t reg, uint8_t* value, uint8_t len){
   set_csn( 0 );                                                                      
   bus.transaction( hwlib::pin_out_dummy ).write( ( R_REGISTER | ( 0x1F & reg ) ) );   //read a certain register

   while( len-- ){
      *value++ = bus.transaction( hwlib::pin_out_dummy ).read_byte();                  //read the bytes out of the register
   }

   set_csn( 1 );                                                                      
}

void NRF24::write_register( uint8_t reg, uint8_t value ){
   set_csn( 0 );                                                                      //starts the transaction
   bus.transaction( hwlib::pin_out_dummy ).write( ( W_REGISTER | ( 0x1F & reg ) ) );  //uses the write command to write values to certain registers
   bus.transaction( hwlib::pin_out_dummy ).write(value);                              //writes a value of 8 bits to the register
   set_csn( 1 );                                                                      //stops the transaction
}

void NRF24::write_register( uint8_t reg, uint8_t* value, uint8_t len ){
   set_csn( 0 );                                                                      //start the transaction                                                           
   bus.transaction( hwlib::pin_out_dummy ).write( ( W_REGISTER | ( 0x1F & reg ) ) );  //writes a value to a register

   while( len-- ){                                                                    //loop through every byte
      bus.transaction( hwlib::pin_out_dummy ).write( *value++ );                      //write every byte
   }

   set_csn( 1 );                                                                      //stop the transaction
}

void NRF24::setChannel( uint8_t channel ){
   channel = ( channel < 125 ) ? channel : 125;                   //a ternary operator to check if the channel is not bigger than 125     
   write_register( RF_CH, channel );                              //write the channel to the RF_CH register
}

void NRF24::set_csn( bool x ){                                    //a function that changes if the csn pin is 0 or 1
   csn.write( x );                           
   csn.flush();                             
}

void NRF24::set_ce( bool x ){                                     //a function that changes the ce pin to 0 or 1
   ce.write( x );                          
   ce.flush();                              
}

void NRF24::write_pipe( uint8_t child, uint8_t *address ){ 

   if(child < 6){                                                       //check if the child is smaller than 6
      if(child < 2){                                                    //if the child is smaller than 2, we can write all 5 bytes of the address
         write_register( pipe[child], address, addr_width );            //write to receive address which address we are going to use
      }else{                                                            //else we can only write 1 byte of the address
         write_register( pipe[child], address, 1 );
      }
   }             

   write_register( TX_ADDR, address, addr_width );                //write to the transmit address the same address
   write_register( pipe_payload[child], payload_size );           //set the size of the payload
}

void NRF24::read_pipe( uint8_t child, uint8_t *address ){

   if(child < 6){
      if(child < 2){
         write_register( pipe[child], address, addr_width );  
      }else{
         write_register( pipe[child], address, 1 );  
      }
   }

   write_register( pipe_payload[child], payload_size );                                      //set the payload size of the receiver
   write_register( EN_RXADDR, read_register( EN_RXADDR ) | ( 1 << pipe_enable[child] ) );    //enable the receive address
}

void NRF24::rx_mode(){                                                              //set to rx_mode

   powerup();                                                                       
   set_ce( 0 );                                                                  
   write_register( CONFIG, read_register( CONFIG ) | ( 1 << PRIM_RX ) );         
   write_register( STATUS, ( 1 << RX_DR ) | ( 1 << TX_DS ) | ( 1 << MAX_RT ) );  
   set_ce( 1 );                                                                  
                            
}

void NRF24::tx_mode( uint8_t child ){                                                              //set to tx_mode

   set_ce( 0 );

   hwlib::wait_ns( 20000 );  //200 microseconds

   write_register( CONFIG, read_register( CONFIG ) & ~( 1 << PRIM_RX ) );         
   powerup();                                                                     
   write_register( EN_RXADDR, read_register( EN_RXADDR ) | ( 1 << pipe_enable[child] ) );     
}

void NRF24::powerup(){
   write_register( CONFIG, read_register( CONFIG ) | ( 1 << PWR_UP ) );           //writes a 1 to the PWR_UP in the CONFIG register
}

void NRF24::flush_rx(){
   transfer( FLUSH_RX );                   //uses the flush_rx command to empty the rx FIFO
}

void NRF24::flush_tx(){
   transfer( FLUSH_TX );                   //uses the flush_tx command to empty the tx FIFO
}

void NRF24::setDataRate( uint8_t speed ){

   if(speed == 0){         //250Kbps
      write_register( RF_SETUP, ( read_register(RF_SETUP) | ( 1 << RF_DR_LOW  ) ) & ~( 1 << RF_DR_HIGH ) );
   }else if(speed == 1){   //1Mpbs
      write_register( RF_SETUP,  read_register(RF_SETUP) & ~( ( 1 << RF_DR_LOW  )  | ( 1 << RF_DR_HIGH ) ) );
   }else if(speed == 2){   //2Mbps
      write_register( RF_SETUP, ( read_register(RF_SETUP) & ~( 1 << RF_DR_LOW  ) ) | ( 1 << RF_DR_HIGH ) );
   }else{                  //in case or number that does not fit the data rate will be set to 250Kbps
      write_register( RF_SETUP, ( read_register(RF_SETUP) | ( 1 << RF_DR_LOW  ) ) & ~( 1 << RF_DR_HIGH ) );
   }
}

void NRF24::write( uint8_t* value, uint8_t len ){

   write_payload( value, len );                                                   //writes the payload into the FIFO
   hwlib::wait_ns(20000);                                                         //waits 20 microseconds to send the data
   set_ce( 0 );                                                                   //turns TX mode off
   write_register( STATUS, ( 1 << RX_DR ) | ( 1 << TX_DS ) | ( 1 << MAX_RT ) );
}

void NRF24::read( uint8_t* value, uint8_t len ){

   read_payload( value, len );                                                    //reads the value in the FIFO

   write_register( STATUS, ( 1 << RX_DR ) | ( 1 << MAX_RT ) | ( 1 << TX_DS ) );

   flush_tx();

}

void NRF24::write_payload( uint8_t* value, uint8_t len ){

   set_csn( 0 );
   bus.transaction( hwlib::pin_out_dummy ).write( W_TX_PAYLOAD );

   uint8_t empty = len - payload_size;

   while( len-- ){
      bus.transaction( hwlib::pin_out_dummy ).write( *value++ );                  //writes al the bytes to the FIFO
   }

   while( empty-- ){
         bus.transaction( hwlib::pin_out_dummy ).write( 0 );                      //in case the length is shorter than the payload length 
   }

   set_csn( 1 );
   set_ce( 1 );                                                                   //start transmitting                                               
}

void NRF24::read_payload( uint8_t* value, uint8_t len ){

   set_csn( 0 );
   bus.transaction( hwlib::pin_out_dummy ).write( R_RX_PAYLOAD );                 //starts the reading of the FIFO

   while( len-- ){
      *value++ = bus.transaction( hwlib::pin_out_dummy ).read_byte();             //add the bytes to value
   }

   set_csn( 1 );
}

void NRF24::setAddressWidth( uint8_t width ){
   if( width > 2 && width < 6 ){
      write_register( SETUP_AW, ( width - 2 ) );
      addr_width = width;
   }else{
      addr_width = 5;
      write_register( SETUP_AW, ( addr_width - 2 ) );
   }
}

void NRF24::setRetries( uint8_t delay, uint8_t count ){
   write_register( SETUP_RETR, (delay & 0xF) << ARD | (count & 0xF) << ARC );       //writes the amount of retries you want to use and what the delay must be
}

bool NRF24::checkRXfifo(){

   if ( ( read_register( FIFO_STATUS ) & ( 1 << RX_EMPTY ) ) == 0 ){
      return 1;                                                               //returns 1 if there is something in the RX fifo
   }else{
      return 0;                                                               //returns 0 if RX fifo is empty
   }
}

void NRF24::readPipeAddress( uint8_t* value, uint8_t child ){
   int len = 5;

   read_register( pipe[child], value, len );

   while( len-- ){
      hwlib::cout << *value++ << " ";
   }

   hwlib::cout << "\n";
}