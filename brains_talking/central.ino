#include <ArduinoBLE.h>
#include <Arduino_APDS9960.h>



const char* deviceServiceUuid = "aaf74645-76af-42c0-b22f-4d523025f4c2";
const char* deviceServiceCharacteristicUuid = "aaf74645-76af-42c0-b22f-4d523025f4c2";



int gesture = -1;
int oldGestureValue = -1;



void setup() {
Serial.begin(9600);
//while (!Serial);



pinMode(LEDR, OUTPUT);
pinMode(D10, OUTPUT);



if (!APDS.begin()) {
Serial.println("* Error initializing APDS9960 sensor!");
}



APDS.setGestureSensitivity(80);



if (!BLE.begin()) {
Serial.println("* Starting BLE module failed!");
while (1);
}



BLE.setLocalName("Nano 33 BLE (Central)");
BLE.advertise();



Serial.println("Arduino Nano 33 BLE Sense (Central Device)");
Serial.println(" ");
}



void loop() {
connectToPeripheral();
}



void connectToPeripheral() {
BLEDevice peripheral;



Serial.println(peripheral.rssi());
if (peripheral.rssi() > -80 and peripheral.rssi() < -30)
{
digitalWrite(LEDR, HIGH);
// digitalWrite(D10, HIGH);
// delay(2000);
// digitalWrite(D10, LOW);
}
else
{
digitalWrite(LEDR, LOW);
// digitalWrite(D10, HIGH);
// delay(500);
// digitalWrite(D10, LOW);
}



Serial.println("- Discovering peripheral device...");



do
{
BLE.scanForUuid(deviceServiceUuid);
peripheral = BLE.available();
} while (!peripheral);



if (peripheral) {
Serial.println("* Peripheral device found!");
Serial.print("* Device MAC address: ");
Serial.println(peripheral.address());
Serial.print("* Device name: ");
Serial.println(peripheral.localName());
Serial.print("* Advertised service UUID: ");
Serial.println(peripheral.advertisedServiceUuid());
Serial.println(" ");
BLE.stopScan();
controlPeripheral(peripheral);
}
}



void controlPeripheral(BLEDevice peripheral) {
Serial.println("- Connecting to peripheral device...");



if (peripheral.connect()) {
Serial.println("* Connected to peripheral device!");
Serial.println(" ");
} else {
Serial.println("* Connection to peripheral device failed!");
Serial.println(" ");
return;
}



Serial.println("- Discovering peripheral device attributes...");
if (peripheral.discoverAttributes()) {
Serial.println("* Peripheral device attributes discovered!");
Serial.println(" ");
} else {
Serial.println("* Peripheral device attributes discovery failed!");
Serial.println(" ");
peripheral.disconnect();
return;
}



BLECharacteristic gestureCharacteristic = peripheral.characteristic(deviceServiceCharacteristicUuid);



if (!gestureCharacteristic) {
Serial.println("* Peripheral device does not have gesture_type characteristic!");
peripheral.disconnect();
return;
} else if (!gestureCharacteristic.canWrite()) {
Serial.println("* Peripheral does not have a writable gesture_type characteristic!");
peripheral.disconnect();
return;
}



while (peripheral.connected()) {
//Serial.print(“RSSI = “);
//Serial.println(peripheral.rssi());



gesture = gestureDetectection();



if (oldGestureValue != gesture) {
oldGestureValue = gesture;
Serial.print("* Writing value to gesture_type characteristic: ");
Serial.println(gesture);
gestureCharacteristic.writeValue((byte)gesture);
Serial.println("* Writing value to gesture_type characteristic done!");
Serial.println(" ");
}



}
Serial.println("- Peripheral device disconnected!");
}



int gestureDetectection() {
if (APDS.gestureAvailable()) {
gesture = APDS.readGesture();



switch (gesture) {
case GESTURE_UP:
Serial.println("- UP gesture detected");
break;
case GESTURE_DOWN:
Serial.println("- DOWN gesture detected");
break;
case GESTURE_LEFT:
Serial.println("- LEFT gesture detected");
break;
case GESTURE_RIGHT:
Serial.println("- RIGHT gesture detected");
break;
default:
Serial.println("- No gesture detected");
break;
}
}
return gesture;
}
