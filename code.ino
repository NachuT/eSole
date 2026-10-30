#include <Wire.h>
#include <Adafruit_MPR121.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#define I2C_SDA_PIN 40
#define I2C_SCL_PIN 41
#define MPR121_IRQ 42
#define MPR121_I2C_ADDR 0x5A
#define ELE_HEEL 0
#define ELE_MID 1
#define ELE_OBALL 2
#define ELE_OTOE 3
#define ELE_BTOE 4
#define ELE_BBALL 5
#define SERVICE_UUID "6E400001-B5A3-F393-E0A9-E50E24DCCA9E"
#define CHARACTERISTIC_UUID_TX "6E400003-B5A3-F393-E0A9-E50E24DCCA9E"
Adafruit_MPR121 cap = Adafruit_MPR121();
BLEServer *pServer = NULL;
BLECharacteristic *pTxCharacteristic = NULL;
bool deviceConnected = false;
bool oldDeviceConnected = false;
class MyServerCallbacks : public BLEServerCallbacks {
void onConnect(BLEServer* pServer) {
deviceConnected = true;
}
void onDisconnect(BLEServer* pServer) {
deviceConnected = false;
}
};
float rawToPicofarads(uint16_t rawAdc) {
if (rawAdc < 10) return 10.0f;
float pF = 4500.0f / (float)rawAdc;
if (pF < 1.0f) pF = 1.0f;
if (pF > 10.0f) pF = 10.0f;
return pF;
}
float pFToPressurePercent(float pF) {
float pct = ((pF - 1.0f) / (10.0f - 1.0f)) * 100.0f;
if (pct < 0.0f) pct = 0.0f;
if (pct > 100.0f) pct = 100.0f;
return pct;
}
void setup() {
Serial.begin(115200);
Wire.begin(I2C_SDA_PIN, I2C_SCL_PIN, 400000);
if (!cap.begin(MPR121_I2C_ADDR, &Wire)) {
Serial.println("MPR121 not detected! Check wiring.");
while (1) {
delay(500); }
}
Serial.println("MPR121 ready.");
BLEDevice::init("E-Sole");
pServer = BLEDevice::createServer();
pServer->setCallbacks(new MyServerCallbacks());
BLEService *pService = pServer->createService(SERVICE_UUID);
pTxCharacteristic = pService->createCharacteristic(
CHARACTERISTIC_UUID_TX,
BLECharacteristic::PROPERTY_NOTIFY 
  );
pTxCharacteristic->addDescriptor(new BLE2902());
pService->start();
BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
pAdvertising->addServiceUUID(SERVICE_UUID);
pAdvertising->setScanResponse(true);
pAdvertising->setMinPreferred(0x06);
pAdvertising->setMinPreferred(0x12);
BLEDevice::startAdvertising();
Serial.println("BLE advertising started as 'E-Sole'. Waiting for connections..."); }
void loop() {
uint16_t raw_heel = cap.filteredData(ELE_HEEL);
uint16_t raw_mid = cap.filteredData(ELE_MID);
uint16_t raw_oball = cap.filteredData(ELE_OBALL);
uint16_t raw_bball = cap.filteredData(ELE_BBALL);
uint16_t raw_btoe = cap.filteredData(ELE_BTOE);
uint16_t raw_otoe = cap.filteredData(ELE_OTOE);
float pf_heel = rawToPicofarads(raw_heel);
float pf_mid = rawToPicofarads(raw_mid);
float pf_oball = rawToPicofarads(raw_oball);
float pf_bball = rawToPicofarads(raw_bball);
float pf_btoe = rawToPicofarads(raw_btoe);
float pf_otoe = rawToPicofarads(raw_otoe);
float pr_heel = pFToPressurePercent(pf_heel);
float pr_mid = pFToPressurePercent(pf_mid);
float pr_oball = pFToPressurePercent(pf_oball);
float pr_bball = pFToPressurePercent(pf_bball);
float pr_btoe = pFToPressurePercent(pf_btoe);
float pr_otoe = pFToPressurePercent(pf_otoe);
char payload[96];
int len = snprintf(payload, sizeof(payload), "%.1f,%.1f,%.1f,%.1f,%.1f,%.1f\n", pr_heel, pr_mid, pr_oball, pr_bball, pr_btoe, pr_otoe);
Serial.print(payload);
if (deviceConnected) {
pTxCharacteristic->setValue((uint8_t*)payload, len);
pTxCharacteristic->notify(); }
if (!deviceConnected && oldDeviceConnected) {
delay(500);
pServer->startAdvertising();
Serial.println("Restarting advertising...");
oldDeviceConnected = deviceConnected; }
if (deviceConnected && !oldDeviceConnected) {
oldDeviceConnected = deviceConnected; }
delay(30); }
