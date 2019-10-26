// Project sponsor: 
// Email: 
// Creator: Cedar Lake Instruments LLC
// Date: October, 2019
//
// Description:
// Detect person approaching
// Detect object dropped into donation box
// Flash LEDs on either condition

// I/O Connections:
// Arduino pin   - I/O description 
// 2 - IR sensor
// 3 - Ultrasonic detect
// 4 - Ultrasonic send
// 5-8 LEDs
/* The circuit :
** Module HR - SC04(four pins) or PING))) (and other with
*   three pins), attached to digital pins as follows :
*-------------------- - --------------------
* | HC - SC04 | Arduino |    | 3 pins | Arduino |
*-------------------- - --------------------
* | Vcc | 5V    |    |   Vcc | 5V |
*| Trig | 12 | OR | SIG | 13 |
*| Echo | 13    |    |   Gnd | GND |
*| Gnd | GND | --------------------
* --------------------*/

// Constant definitions
#include <Ultrasonic.h>
const int IR = 2;
const int US_ECHO = 3;
const int US_TRIG = 4;

// List of LED pins
const int LEDS[] = { 5,6,7,8 };
// Distance trigger in cm
const int DISTANCE_LIMIT = 90;

// Global variables
// Create ultrasonic object
Ultrasonic _ultrasonic(US_TRIG, US_ECHO);

// Runs once
void setup() 
{
	Serial.begin(9600);
	pinMode(IR, INPUT_PULLUP);

	// All LEDs off
	for (int i = 0; i < sizeof(LEDS) / sizeof(LEDS[0]); i++)
	{
		pinMode(LEDS[i], OUTPUT);
		digitalWrite(LEDS[i], LOW);
	}
}

// Runs continuously
void loop() 
{
	// Check for US trigger
	int distance = _ultrasonic.distanceRead();

	// If someone comes closer than the limit, turn LEDs on
	if (distance < DISTANCE_LIMIT && distance != 0)
	{
		Serial.println("US detect");
		// Light up all LEDs
		for (int i = 0; i < sizeof(LEDS) / sizeof(LEDS[0]); i++)
		{
			digitalWrite(LEDS[i], HIGH);
		}
	}
	else
	{
		// All LEDs off
		for (int i = 0; i < sizeof(LEDS) / sizeof(LEDS[0]); i++)
		{
			digitalWrite(LEDS[i], LOW);
		}
	}


	// Check if IR sensor triggered
	static bool lastTrigger = false;

	// Triggered state is HIGH
	bool iRState = digitalRead(IR);
	// If triggered this time but not last time, cheer
	if (!lastTrigger && iRState)
	{
		Serial.println("IR detect");
		cycleLeds(5);
	}
	lastTrigger = iRState;

}

// Blink LEDs one at a time for n times
void cycleLeds(int n)
{
	// Cycle LEDS 5 times
	for (int j = 0; j < n; j++)
	{
		for (int i = 0; i < sizeof(LEDS) / sizeof(LEDS[0]); i++)
		{
			digitalWrite(LEDS[i], HIGH);
			delay(50);
			digitalWrite(LEDS[i], LOW);
			delay(150);
		}
	}
}

