//WHITE BREADBOARD

#include <RFduinoGZLL.h>

device_t role = DEVICE0;

int led = 6;
int dist = 0;

void setup()
{
  pinMode(led, OUTPUT);

  RFduinoGZLL.txPowerLevel = 0;

  // start the GZLL stack
  RFduinoGZLL.begin(role);
}

void loop()
{
  delay(200);

  // request the state from the Host (send a 0 byte payload)
  RFduinoGZLL.sendToHost(NULL, 0);
}

void RFduinoGZLL_onReceive(device_t device, int rssi, char *data, int len)
{
  dist = map(rssi, -30, -70, 255, 0);
  dist = constrain(dist, 0, 255);
  analogWrite(led, dist);
}
