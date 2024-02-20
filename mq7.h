#include <Adafruit_ADS1X15.h>
Adafruit_ADS1115 ads1115;

#define heatTimeHigh 60
#define heatTimeLow 90
#define heatGPIO 25
#define Ro (1900000.0/25.75) // Ro = Rs 100ppm = (Rs clean air / 25.75)
#define Rout 9400.0

void doHeat(bool heatTemp) {
  mq7.heatTemp=heatTemp;
  digitalWrite(heatGPIO,heatTemp);
  if (heatTemp) {
    mq7.heatTimer=millis()+(heatTimeHigh*1000);
    if (debug) { Serial.println("Heat High."); } }
  else {
    mq7.heatTimer=millis()+(heatTimeLow*1000);
    if (debug) { Serial.println("Heat Low."); } } }

void initMQ7() {
  if (!ads1115.begin()) { Serial.println("Failed to initialize ADS1115."); }
  ads1115.setGain(GAIN_ONE);
  ads1115.setDataRate(RATE_ADS1115_8SPS);
  pinMode(heatGPIO,OUTPUT);
  doHeat(true); }

double getUout(int cycles=10) {
  double Uout=0;
  if (ads1115.computeVolts(ads1115.readADC_SingleEnded(0))<0.8) { ads1115.setGain(GAIN_FOUR); }
  for (int i=0;i<cycles;i++) {
    Uout+=ads1115.computeVolts(ads1115.readADC_SingleEnded(0))*2; }
  Uout/=cycles;
  ads1115.setGain(GAIN_ONE);
  return Uout; }

double getUsensor(int cycles=10) {
  double Usensor=0;
  for (int i=0;i<cycles;i++) {
    Usensor+=ads1115.computeVolts(ads1115.readADC_SingleEnded(2))*2; }
  Usensor/=cycles;
  return Usensor; }

double getUheat(int cycles=10) {
  double Uheat=0;
  for (int i=0;i<cycles;i++) {
    Uheat+=ads1115.computeVolts(ads1115.readADC_Differential_2_3())*2; }
  Uheat/=cycles;
  return Uheat; }

void getCoPPM(int cycles=10) {
  mq7.Uout=getUout(cycles);
  mq7.Usensor=getUsensor(cycles);
  mq7.Rs=Rout/mq7.Uout*(mq7.Usensor-mq7.Uout);
  mq7.RsRo=mq7.Rs/Ro;
  mq7.coPPM=100.0*pow(mq7.RsRo,-1.513); }

void mq7Worker() {
  if (millis()>=mq7.heatTimer) {
    if (mq7.heatTemp) {
      mq7.UheatHigh=getUheat();
      doHeat(false); }
    else {
      getCoPPM();
      mq7.UheatLow=getUheat();
      doHeat(true);
#ifdef httpClientFlag
      httpClientRequest.post(httpClientHost,httpClientPath,"update=" + String(mq7.coPPM,3));
#endif
      if (debug) {
        Serial.println("UheatHigh: " + String(mq7.UheatHigh,3) + " Volt");
        Serial.println("UheatLow: " + String(mq7.UheatLow,3) + " Volt");
        Serial.println("Usensor: " + String(mq7.Usensor,3) + " Volt");
        Serial.println("Uout: " + String(mq7.Uout*1000.0,3) + " milliVolt");
        Serial.println("Rs: " + String(mq7.Rs/1000.0,3) + " kOhm");
        Serial.println("Rs/Ro: " + String(mq7.RsRo,3));
        Serial.println("CO: " + String(mq7.coPPM,3) + " ppm"); } } } }
