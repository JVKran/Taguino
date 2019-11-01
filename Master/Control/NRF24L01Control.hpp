#ifndef __NRF24L01CONTROL_HPP
#define __NRF24L01CONTROL_HPP

#include "hwlib.hpp"
#include "rtos.hpp"

// this file contains Doxygen lines
/// @file

/// \brief
/// control object to NRF24L01Control
/// \details
/// This object can be used to send and receive messages

class NRF24L01Control : public NRFControl, public rtos<>{
private:
	NRF24L01& nrf;

public:

	/// \brief
    /// constructor
    /// \details
    /// Creates a object of NRF24L01Control
	NRF24L01Control();

	/// \brief
	/// start the nrf
	/// \details
	/// with this function certain values will be set to be able to read and
	/// write data
	void start();

	/// \brief
    /// start listening mode
    /// \details
    /// With this function the nrf wil start to listen
	void startListening();

	/// \brief
    /// check what is in the FIFO
    /// \details
    /// With this function you are able to read the value out of the FIFO
	void read();

	/// \brief
    /// simple read
    /// \details
    /// This function is used to simplify reading, it is just the function 
    /// startListening() en read()
	void readFast();

	/// \brief
    /// start write mode
    /// \details
    /// This function will set certain pins high/low to get into transmit mode 
    /// and it will set the address on which we are going to write
	void startWriting();

	/// \brief
    /// send data
    /// \details
    /// With this function you are able to set data inside the transmit fifo
    /// and send it
	void send();

	/// \brief
    /// simple send
    /// \details
    /// This function is meant to be used when you are going to send one time
    /// a message and than go back to reading again.
	void sendFast();

	/// \brief
    /// main
    /// \details
    /// The main
	void main();

};

#endif //__NRF24L01CONTROL_HPP