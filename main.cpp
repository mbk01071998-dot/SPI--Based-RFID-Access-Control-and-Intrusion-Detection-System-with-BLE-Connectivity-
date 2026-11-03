
#include <Arduino.h>
#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

// RFID pins
#define SS_PIN    5
#define RST_PIN   4

// Other component pins
#define IR_PIN       27
#define GREEN_LED    25
#define RED_LED      26

// RFID UID
String authorizedUID = "B4 66 FF0 6";

// LCD I2C address
LiquidCrystal_I2C lcd(0x27, 16, 2);

// RFID object
MFRC522 rfid(SS_PIN, RST_PIN);

// BLE UUIDs
#define SERVICE_UUID \
"12345678-1234-1234-1234-123456789001"

#define CHARACTERISTIC_UUID \
"12345678-1234-1234-1234-123456789002"

BLECharacteristic *bleCharacteristic;

unsigned long accessTimer = 0;
const unsigned long ACCESS_DURATION = 3000;

bool accessGranted = false;
bool previousIntrusion = false;

// Display message
void showMessage(String line1, String line2) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(line1);
    lcd.setCursor(0, 1);
    lcd.print(line2);
}

// Send event to mobile through BLE
void sendBLE(String message) {
    if (bleCharacteristic != nullptr) {
        bleCharacteristic->setValue(
            (uint8_t*)message.c_str(),
            message.length()
        );
        bleCharacteristic->notify();
    }
}

// Return to default status
void showDefaultStatus() {
    accessGranted = false;
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(RED_LED, HIGH);

    showMessage("ACCESS DENIED", "System Ready");
}

// Read RFID UID
String readCardUID() {
    String uid = "";

    for (byte i = 0; i < rfid.uid.size; i++) {
        if (rfid.uid.uidByte[i] < 0x10) {
            uid += "0";
        }

        if (i > 0) {
            uid += " ";
        }

        uid += String(rfid.uid.uidByte[i], HEX);
    }

    uid.toUpperCase();
    return uid;
}

void setup() {
    Serial.begin(115200);

    // LED and IR setup
    pinMode(GREEN_LED, OUTPUT);
    pinMode(RED_LED, OUTPUT);
    pinMode(IR_PIN, INPUT);

    // Initial LED status
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(RED_LED, HIGH);

    // LCD setup
    Wire.begin(21, 22);
    lcd.init();
    lcd.backlight();

    showMessage("SYSTEM STARTING", "Please Wait");

    // SPI and RFID setup
    SPI.begin(18, 19, 23, 5);
    rfid.PCD_Init();
    rfid.PCD_DumpVersionToSerial();
    Serial.println("place RFID Card");

    Serial.println("RFID Reader Ready");

    // BLE setup
    BLEDevice::init("ESP32_RFID_SYSTEM");

    BLEServer *server = BLEDevice::createServer();

    BLEService *service =
        server->createService(SERVICE_UUID);

    bleCharacteristic =
        service->createCharacteristic(
            CHARACTERISTIC_UUID,
            BLECharacteristic::PROPERTY_READ |
            BLECharacteristic::PROPERTY_NOTIFY
        );

    bleCharacteristic->addDescriptor(new BLE2902());

    service->start();

    server->getAdvertising()->start();

    Serial.println("Bluetooth Started");

    showDefaultStatus();

    sendBLE("SYSTEM READY");
}

void loop() {

    // IR intrusion detection
    // Typical IR modules give LOW when an object is detected.
    bool intrusion = (digitalRead(IR_PIN) == LOW);

    if (intrusion && !previousIntrusion) {
        digitalWrite(RED_LED, HIGH);
        digitalWrite(GREEN_LED, LOW);

        showMessage("INTRUSION", "DETECTED!");

        Serial.println("INTRUSION DETECTED");
        sendBLE("INTRUSION DETECTED");
    }

    if (!intrusion && previousIntrusion) {
        if (accessGranted &&
            millis() - accessTimer < ACCESS_DURATION) {

            digitalWrite(GREEN_LED, HIGH);
            digitalWrite(RED_LED, LOW);

            showMessage("ACCESS GRANTED", "Welcome!");

        } else {
            showDefaultStatus();
        }
    }

    previousIntrusion = intrusion;

    // RFID card detection
    if (rfid.PICC_IsNewCardPresent() &&
        rfid.PICC_ReadCardSerial()) {

        String cardUID = readCardUID();

        Serial.print("Card UID: ");
        Serial.println(cardUID);

        if (cardUID == authorizedUID) {

            accessGranted = true;
            accessTimer = millis();

            Serial.println("ACCESS GRANTED");

            sendBLE("ACCESS GRANTED - " + cardUID);

            if (!intrusion) {
                digitalWrite(GREEN_LED, HIGH);
                digitalWrite(RED_LED, LOW);

                showMessage("ACCESS GRANTED", "Welcome!");
            }

        } else {

            accessGranted = false;

            Serial.println("ACCESS DENIED");

            sendBLE("ACCESS DENIED - " + cardUID);

            if (!intrusion) {
                digitalWrite(GREEN_LED, LOW);
                digitalWrite(RED_LED, HIGH);

                showMessage("ACCESS DENIED", "Invalid Card");
            }
        }

        rfid.PICC_HaltA();
        rfid.PCD_StopCrypto1();
    }

    // Return to default after 3 seconds
    if (accessGranted &&
        millis() - accessTimer >= ACCESS_DURATION) {

        accessGranted = false;

        if (!intrusion) {
            showDefaultStatus();
        }
    }

    delay(50);
}