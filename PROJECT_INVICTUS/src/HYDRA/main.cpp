#include <Arduino.h>
#include <MCP9600.h>
#include "Wire.h"

#define MCP9600_ADDRESS 0x60
#define MCP9600_SDA 21
#define MCP9600_SCL 22

MCP9600 thermocouple;
void setup() {
    Wire.begin(MCP9600_SDA, MCP9600_SCL);
    Serial.begin(115200);
    if(!thermocouple.begin(MCP9600_ADDRESS)) {
        Serial.println("MCP9600 not found. Check wiring!");
        while (1);
    }
    thermocouple.setThermocoupleType(TYPE_K); // Set thermocouple type
}

void loop() {
    // read thermocouple
    float hotTemp = thermocouple.getThermocoupleTemp();
    float coldTemp = thermocouple.getAmbientTemp();
    float deltaTemp = thermocouple.getTempDelta();
    Serial.print("Hot Junction Temp: ");
    Serial.print(hotTemp);
    Serial.println(" C");
    Serial.print("Cold Junction Temp: ");
    Serial.print(coldTemp);
    Serial.println(" C");
    Serial.print("Delta Temp: ");
    Serial.print(deltaTemp);
    Serial.println(" C");
    delay(1000); // wait for a second
    // print data
}