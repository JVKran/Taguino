#ifndef _MSG_DECODER_HPP
#define _MSG_DECODER_HPP

class msg_decoder{
private:

	msg_listener listener;

public:

	msg_decoder( msg_listener listener){
		listener( listener )
	}

};

#endif //_MSG_DECODER_HPP