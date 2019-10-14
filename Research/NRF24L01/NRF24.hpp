#ifndef NRF24_HPP
#define NRF24_HPP

#include "hwlib.hpp"

class NRF24 {
protected:
   hwlib::spi_bus & bus; 
   hwlib::pin_out & ce;
   hwlib::pin_out & csn;
   uint8_t payload_size;
   uint8_t addr_width;

public:
   NRF24( hwlib::spi_bus & bus, hwlib::pin_out & ce, hwlib::pin_out & csn);

   NRF24( hwlib::spi_bus & bus, hwlib::pin_out & ce, hwlib::pin_out & csn, uint8_t payload_size, uint8_t addr_width );

   void start();

   void transfer( uint8_t reg );

   uint8_t read_register( uint8_t reg );

   void read_register( uint8_t reg, uint8_t* value, uint8_t len);

   void write_register( uint8_t reg, uint8_t value );

   void write_register( uint8_t reg, uint8_t* value, uint8_t len );

   void setChannel( uint8_t channel );

   void set_csn( bool x );

   void set_ce( bool x );

   void write_pipe( uint8_t *address );

   void read_pipe( uint8_t *address );

   void rx_mode();

   void tx_mode();

   void powerup();

   void flush_rx();

   void flush_tx();

   void setDataRate( uint8_t speed );

   void write( uint8_t* value, uint8_t len );

   void read( uint8_t* value, uint8_t len );

   void write_payload( uint8_t* value, uint8_t len );

   void read_payload( uint8_t* value, uint8_t len );

   void setAddressWidth( uint8_t width );

   void setRetries( uint8_t delay, uint8_t count );

   bool checkRXfifo();

};

#endif // NRF24_HPP