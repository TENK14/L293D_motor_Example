
/**
*
* Vpøed: [1,0,1,0] => F
* Vzad:  [0,1,0,1] => B
* Vlevo: [0,0,1,0] => L
* Vpravo:[1,0,0,0] => R
*/


const int leftForward = 2;
const int leftBackward = 3;
const int rightForward = 4;
const int rightBackward = 5;

//String readString, servo1, servo2;
String readString, pin, val;
int p, v;

char buff[255];

void setup()
{

	Serial.begin(9600);

	pinMode(leftForward, OUTPUT);
	pinMode(leftBackward, OUTPUT);
	pinMode(rightForward, OUTPUT);
	pinMode(rightBackward, OUTPUT);

	//ardprintf("Mapped pins: %d,%d,%d,%d",leftForward, leftBackward, rightForward, rightBackward);
	sprintf(buff, "Mapped pins: %d,%d,%d,%d", leftForward, leftBackward, rightForward, rightBackward);
	Serial.println(buff);
	Serial.println("Input: pin,val");
	Serial.println("Example: 2,1");
	Serial.println("Example: 3,0");
	Serial.println("------------");
	Serial.println("OR use functions");
	Serial.println("X,F or B or L or R or S");
	Serial.println("Example: X,F");
}

void loop()
{


	//digitalWrite(leftForward , HIGH);
	//digitalWrite(leftBackward , LOW);
	//digitalWrite(rightForward , HIGH);
	//digitalWrite(rightBackward , LOW);

	while (Serial.available()) {
		delay(3);  //delay to allow buffer to fill 
		if (Serial.available() >0) {
			char c = Serial.read();  //gets one byte from serial buffer
			readString += c; //makes the string readString
		}
	}

	if (readString.length() >0) {
		//sprintf(buff,"Input: %s",readString);
		Serial.println("Input: " + readString);

		pin = readString.substring(0, 1);
		val = readString.substring(2);

		if (pin == "x" || pin == "X")
		{
			if (val == "f" || val == "F")
			{
				forward();
			}
			else if (val == "b" || val == "B")
			{
				backward();
			}
			else if (val == "l" || val == "L")
			{
				left();
			}
			else if (val == "r" || val == "R")
			{
				right();
			}
			else if (val == "s" || val == "S")
			{
				stop();
			}
			else
			{
				Serial.println("Wrong input.");
			}
		}
		else
		{
			p = pin.toInt();
			v = val.toInt();

			sprintf(buff, "Set [%d,%d]", p, v);
			Serial.println(buff);

			digitalWrite(p, v);
		}

		readString = "";
	}

}

void forward()
{
	Serial.println("forward()");
	setMove(1, 0, 1, 0);
}

void backward()
{
	Serial.println("backward()");
	setMove(0, 1, 0, 1);
}

void left()
{
	Serial.println("left()");
	setMove(0, 0, 1, 0);
}

void right()
{
	Serial.println("right()");
	setMove(1, 0, 0, 0);
}

void stop()
{
	Serial.println("stop()");
	setMove(0, 0, 0, 0);
}

void setMove(int lf, int lb, int rf, int rb)
{
	sprintf(buff, "Set [%d,%d,%d,%d]", lf, lb, rf, rb);
	Serial.println(buff);
	digitalWrite(leftForward, lf);
	digitalWrite(leftBackward, lb);
	digitalWrite(rightForward, rf);
	digitalWrite(rightBackward, rb);
}
