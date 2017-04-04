/********************************************************************/
// First we include the libraries
#include <OneWire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal.h>
/********************************************************************/
// Data wire is plugged into pin 2 on the Arduino
#define ONE_WIRE_BUS 2
/********************************************************************/
// Setup a oneWire instance to communicate with any OneWire devices
// (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);
/********************************************************************/
// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);
/********************************************************************/

LiquidCrystal lcd(12, 13, 4, 5, 6, 7);
DeviceAddress sensorOne = { 0x28, 0xFF, 0x63, 0xC2, 0x85, 0x16, 0x04, 0x59 };

int relayPin = 11;
float tempCur = 0;

/*laten staan, te gebruiken bij nieuwe sensoren om het address te vinden*/
void printAddress(DeviceAddress deviceAddress)
{
  for (uint8_t i = 0; i < 8; i++)
  {
    // zero pad the address if necessary
    if (deviceAddress[i] < 16) Serial.print("0");
    Serial.print(deviceAddress[i], HEX);
  }
}


void setup(void)
{
 // start serial port
 Serial.begin(9600);

pinMode(relayPin, OUTPUT);

 lcd.begin(16, 2);
 lcd.print("Send Nudes");
 lcd.setCursor(0,1);
 lcd.print("Send Nudes");
 delay(1000);
 lcd.clear();
 lcd.print("Temperature is: ");
 lcd.setCursor(6,1);
 lcd.print(char(223));
 lcd.print("C");
 sensors.begin();
 Serial.print("Device address is: ");
 printAddress(sensorOne);
 Serial.println("");
 Serial.print("Resolution is: ");
 Serial.println(sensors.getResolution(sensorOne));
}

void loop(void)
{
sensors.requestTemperatures(); // Send the command to get temperature readings
/********************************************************************/
lcd.setCursor(0,1);
tempCur = sensors.getTempC(sensorOne);
if (tempCur < 20) {
  digitalWrite(relayPin, HIGH);
}
if (tempCur > 22) {
  digitalWrite(relayPin, LOW);
}

lcd.print(sensors.getTempC(sensorOne));
delay(1000);
}
