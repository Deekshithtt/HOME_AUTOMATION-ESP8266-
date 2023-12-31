#define SECRET_SSID "Redmi" //Enter WIFI NAME 
#define SECRET_PASS "praneeth111" //Enter WIFI PASSWORD 
#define SECRET_DEVICE_KEY "TFXHJXHISKUIOV0TJP4I" //Enter Secret Key

#include <ArduinoIoTCloud.h>
#include <Arduino_ConnectionHandler.h>

const char THING_ID[ ]  = "73847a65-352e-449d-8216-89ca069ad945";  //Enter THING ID
const char  DEVICE_LOGIN_NAME[]  = "0cd66500-de33-4395-ba76-7a76c0819d0d"; //Enter DEVICE ID
const char SSID[] = SECRET_SSID;    // Network SSID (name)
const char PASS[] = SECRET_PASS;    // Network password (use for WPA, or use as key for WEP)
const char DEVICE_KEY[]  = SECRET_DEVICE_KEY;// Secret device password


void onSwitch1Change();


CloudSwitch switch1;


void initProperties()
{


  ArduinoCloud.setBoardId(DEVICE_LOGIN_NAME);
  ArduinoCloud.setSecretDeviceKey(DEVICE_KEY);
  ArduinoCloud.setThingId(THING_ID);
  ArduinoCloud.addProperty(switch1, READWRITE, ON_CHANGE, onSwitch1Change);
}


WiFiConnectionHandler ArduinoIoTPreferredConnection(SSID, PASS);


#define RelayPin1 5  //D1
#define SwitchPin1 10  //SD3
#define wifiLed   16   //D0


int toggleState_1 = 0; //Define integer to remember the toggle state relay 1


void relayOnOff(int relay) 
{
  switch (relay) 
  {
    case 1:
      if (toggleState_1 == 0) 
      {
        digitalWrite(RelayPin1, LOW); // turn on relay 1
        toggleState_1 = 1;
        Serial.println("Device1 ON");
      }
      
else 
     {
        digitalWrite(RelayPin1, HIGH); // turn off relay 1
        toggleState_1 = 0;
        Serial.println("Device1 OFF");
      }
      delay(100);
      break;
      default : break;
 }
}
void manual_control() 
{
  if (digitalRead(SwitchPin1) == LOW) 
  {
    delay(200);
    relayOnOff(1);
   }
}


void setup() {
  
  Serial.begin(9600);
  
  delay(1500);


  
  initProperties();


  
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);


 pinMode(RelayPin1, OUTPUT);
 pinMode(wifiLed, OUTPUT);
 pinMode(SwitchPin1, INPUT_PULLUP);


digitalWrite(RelayPin1, HIGH);
digitalWrite(wifiLed, HIGH);  //Turn OFF WiFi LED
}


void loop() {
  ArduinoCloud.update();
  
  manual_control(); //Control relays manually


  if (WiFi.status() != WL_CONNECTED)
  {
    digitalWrite(wifiLed, HIGH); //Turn OFF WiFi LED
  }
  else{
    digitalWrite(wifiLed, LOW); //Turn ON WiFi LED
  }
}


void onSwitch1Change() {
  if (switch1 == 1)
  {
    digitalWrite(RelayPin1, HIGH);
    Serial.println("Device1 ON");
    toggleState_1 = 1;
  }
  else
  {
    digitalWrite(RelayPin1, LOW);
    Serial.println("Device1 OFF");
    toggleState_1 = 0;
  }
}