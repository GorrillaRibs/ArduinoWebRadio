/*
  Robert Raffaele "GorrillaRIBS" Miller
  Arduino ICEcast streamer
  Code finalized Sun, 22 May, 2016
  Using own modified libraries that "work" with cleap 3rd party shields I'm using - should work properly
  with the actual shields/libraries as well

  Grabs data from the internet, then
  transmits data over I2C to second arduino,
  which has a VS1053 shield for processing the sound data

  Wake me up
  (Wake me up inside)
  Can't wake up
  (Wake me up inside)
  SAAAVVVEE MEEEE
*/

#include <SPI.h>
#include <EthernetV2_0.h>
#include <Wire.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
byte server[] = { 45, 79, 186, 124 };  // station ip
// byte port = 8268; // station port, doesn't work properly if called as byte or int

IPAddress ip(192, 168, 0, 177);
EthernetClient client;

void setup() {
  while (!Serial) {} // wait for serial
  Serial.begin(115200);
  Wire.begin(); // join i2c bus (address optional for master)

  Serial.println("Starting connection");
  Ethernet.begin(mac, ip);
  Serial.println("Your ip is...");
  Serial.println(Ethernet.localIP());

  Serial.println("connecting...");

  if (client.connect(server, 8268)) {
    Serial.println("connected");
    client.println("GET /stream HTTP/1.0");
    client.println();
  } else {
    Serial.println("connection failed");
  }

}

void loop() {

  if (client.available()) {
    Wire.beginTransmission(8); // transmit to device #8
    char c = client.read();
    // Serial.print(c); // this will NEVER END as long as connected to internet
    Wire.write(c);              // sends one byte
    Wire.endTransmission();    // stop transmitting

  }

  if (!client.connected()) {
    Serial.println();
    Serial.println("disconnecting.");
    client.stop();
    for (;;)
      ;
  }


}
