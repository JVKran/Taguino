


class signUp : public rtos::task<> {
private:
	rtos::channel signUpChannel;

	PlayerData& player;
	Display& oled;
	RotaryEncoder& encoder;
	Keypad& keypad;

public:
	void getPlayerData();
	void setPlayerData();
	void draw();
	void keyPressed();
	void encoderPressed();
	void encoderTurnedToPos();

}