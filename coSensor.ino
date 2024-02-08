boolean debug=true;

const char* appName="coSensor";
const char* appDesc="MQ-7 CO Sensor";

#include "mq7.h"
#include "WLAN.h"
#include "DNS.h"
#include "HTTP.h"

void setup() {
  if (debug) { Serial.begin(115200); }
  initMQ7();
  initWLAN();
  initDNS();
  initHTTP(); }

void loop() { wlanWorker(); dnsWorker(); httpWorker(); mq7Worker(); }
