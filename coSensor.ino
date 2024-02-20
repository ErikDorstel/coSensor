boolean debug=true;

const char* appName="coSensor";
const char* appDesc="MQ-7 CO Sensor";

#define httpClientFlag
#define httpClientHost "office.dorstel.de"
#define httpClientPath "/receiver.php"

#include "dataStore.h"
#include "WLAN.h"
#include "DNS.h"
#include "HTTPserver.h"
#include "HTTPclient.h"
#include "mq7.h"

void setup() {
  if (debug) { Serial.begin(115200); }
  initWLAN();
  initDNS();
  initHTTPServer();
  initMQ7(); }

void loop() { wlanWorker(); dnsWorker(); httpServerWorker(); mq7Worker(); }
