#include <ArduinoBLE.h>

#define MOTOR_F 12
#define MOTOR_B 11
#define MOTOR_F_OFF 10
#define MOTOR_B_OFF 9
// Botname can't have uppercase letters!
#define BOT_NAME "hebobot #1"

BLEService ledService("19B10000-E8F2-537E-4F6C-D104768A1214");
BLECharCharacteristic switchCharacteristic("19B10001-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite);

void setup() { 
  pinMode(MOTOR_F, OUTPUT);
  pinMode(MOTOR_B, OUTPUT);
  pinMode(MOTOR_F_OFF, OUTPUT);
  pinMode(MOTOR_B_OFF, OUTPUT);

  if (!BLE.begin()) {
    while (1);
  }
  
  BLE.setLocalName(BOT_NAME);
  BLE.setAdvertisedService(ledService);

  ledService.addCharacteristic(switchCharacteristic);

  BLE.addService(ledService);

  BLE.setEventHandler(BLEConnected, blePeripheralConnectHandler);
  BLE.setEventHandler(BLEDisconnected, blePeripheralDisconnectHandler);

  switchCharacteristic.setEventHandler(BLEWritten, switchCharacteristicWritten);
  switchCharacteristic.setValue(0);

  BLE.advertise();
}

void loop() {
  BLE.poll();
}

void blePeripheralConnectHandler(BLEDevice central) {
  
}

void blePeripheralDisconnectHandler(BLEDevice central) {
  
}

void switchCharacteristicWritten(BLEDevice central, BLECharacteristic characteristic) {
  char value = switchCharacteristic.value();
  switch (value) {
    case 'w' :
      digitalWrite(MOTOR_F_OFF, LOW);
      digitalWrite(MOTOR_B, LOW);
      digitalWrite(MOTOR_B_OFF, HIGH);
      digitalWrite(MOTOR_F, HIGH);
      break;
    case 's' :
      digitalWrite(MOTOR_B_OFF, LOW);
      digitalWrite(MOTOR_F, LOW);
      digitalWrite(MOTOR_F_OFF, HIGH);
      digitalWrite(MOTOR_B, HIGH);
      break;
    default:
      digitalWrite(MOTOR_B, LOW);
      digitalWrite(MOTOR_F, LOW);
      digitalWrite(MOTOR_B_OFF, HIGH);
      digitalWrite(MOTOR_F_OFF, HIGH); 
  ;}
}
  
