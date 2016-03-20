// This #include statement was automatically added by the Particle IDE.
#include "Adafruit_DHT/Adafruit_DHT.h"

// Example testing sketch for various DHT humidity/temperature sensors
// Written by ladyada, public domain

#define DHTPIN 2     // what pin we're connected to
#define LIGHTPIN A0

// Uncomment whatever type you're using!
#define DHTTYPE DHT11


#define READDELAY 10000

// Connect pin 1 (on the left) of the sensor to +5V
// Connect pin 2 of the sensor to whatever your DHTPIN is
// Connect pin 4 (on the right) of the sensor to GROUND
// Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor

DHT dht(DHTPIN, DHTTYPE);

int lastRead = 0;

int device_id = 0;
char device_secret[9] = "dankmeme";

void setup() {
	Serial.begin(12800); 
	Serial.println("I'm feeling the heat!");

	dht.begin();
}

void loop() {
// Wait a few seconds between measurements.
    int currentTime = millis();
	if((currentTime - 10000) < lastRead) {
	    return;
	}
	
	lastRead = currentTime;

// Reading temperature or humidity takes about 250 milliseconds!
// Sensor readings may also be up to 2 seconds 'old' (its a 
// very slow sensor)
	float h = dht.getHumidity();
// Read temperature as Celsius
	float t = dht.getTempCelcius();
// Read temperature as Farenheit
	float f = dht.getTempFarenheit();
	
	int l = analogRead(LIGHTPIN);
  
// Check if any reads failed and exit early (to try again).
	if (isnan(h) || isnan(t) || isnan(f) || isnan(l)) {
		Serial.println("Failed to read from DHT sensor!");
		return;
	}

// Compute heat index
// Must send in temp in Fahrenheit!
	float hi = dht.getHeatIndex();
	float dp = dht.getDewPoint();
	float k = dht.getTempKelvin();

    /*
	Serial.print("Humid: "); 
	Serial.print(h);
	Serial.print("% - ");
	Serial.print("Temp: "); 
	Serial.print(t);
	Serial.print("*C ");
	Serial.print(f);
	Serial.print("*F ");
	Serial.print(k);
	Serial.print("*K - ");
	Serial.print("DewP: ");
	Serial.print(dp);
	Serial.print("*C - ");
	Serial.print("HeatI: ");
	Serial.print(hi);
	Serial.println("*C");
	Serial.print("Light: ");
	Serial.println(l);
	Serial.println(Time.timeStr());
	*/
	
	Particle.publish("glasshouse", "{\"device_id\":" + String(device_id) + ", \"device_secret\":\"" + String(device_secret) + "\" ," + 
	    "\"centigrade\":" + String(t) + ", \"fahrenheit\":" + String(f) + ", \"humidity\":" + String(h) + ", \"kelvin\":" + String(k) + ", \"dewpoint\":" + String(dp) +
	    ", \"light\":" + String(l) + ", \"heatindex\":" + String(hi) + "}");
}

