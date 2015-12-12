//RED BREADBOARD

#define  MAX_DEVICES  2
#include <RFduinoGZLL.h>

int rssi_total[MAX_DEVICES];
int rssi_count[MAX_DEVICES];

int averageAll = 0;
int dist = 0;

char closest_device = 0;
int collect_samples = 0;

void setup()
{
  Serial.begin(9600);
  RFduinoGZLL.begin(HOST);  
}

void loop()
{
  int i;

  for (i = 0; i < MAX_DEVICES; i++)
  {
    rssi_total[i] = 0;
    rssi_count[i] = 0;
  }
  
  collect_samples = 1;
  delay(300);
  collect_samples = 0;

  int average[MAX_DEVICES];
 
  for (i = 0; i < MAX_DEVICES; i++)
  {
    if (rssi_count[i] == 0)
      average[i] = -128;
    else
      average[i] = rssi_total[i] / rssi_count[i];
  }

//  average rssi values to calculate average distance from devices

  averageAll = (average[0] + average[1])/2;
//  Serial.println(averageAll);
  dist = map(averageAll, -30, -70, 255, 0);
  dist = constrain(dist, 0, 255);
  analogWrite(6, dist);
}

void RFduinoGZLL_onReceive(device_t device, int rssi, char *data, int len)
{
  // ignore device if outside range
  if (device > MAX_DEVICES)
    return;
    
  // if collecting samples, update the RSSI total and count
  if (collect_samples)
  {
    rssi_total[device] += rssi;
    rssi_count[device]++;
  }
  
  RFduinoGZLL.sendToDevice(device, 0);
}
