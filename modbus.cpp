#include <Arduino.h>
#include <ModbusMaster.h>
#include "modbus.h"


HardwareSerial ModbusSerial(2);
ModbusMaster nodes[NUM_BATTERIES];

void preTransmission() {
  digitalWrite(MAX485_DE_RE_PIN, HIGH);
}

void postTransmission() {
  digitalWrite(MAX485_DE_RE_PIN, LOW);
}

void initModbus() {
  pinMode(MAX485_DE_RE_PIN, OUTPUT);
  digitalWrite(MAX485_DE_RE_PIN, LOW);

  ModbusSerial.begin(9600, SERIAL_8N1, RX_PIN, TX_PIN);

  for (int i = 0; i < NUM_BATTERIES; i++) {
    nodes[i].begin(SLAVE_ADDRESSES[i], ModbusSerial);
    nodes[i].preTransmission(preTransmission);
    nodes[i].postTransmission(postTransmission);
  }
}

float decodeModbusFloat(uint16_t reg1, uint16_t reg2) {
  union {
    uint32_t u32;
    float f;
  } conv;
  conv.u32 = ((uint32_t)reg1 << 16) | reg2;
  return conv.f;
}

void readAllBatteries(BatteryData* batteryData) {
  for (int i = 0; i < NUM_BATTERIES; i++) {
    batteryData[i].isValid = false;

    auto& node = nodes[i];
    BatteryData data;

    uint8_t result;

    result = node.readHoldingRegisters(REG_VOLTAGE_START, 2);
    if (result == node.ku8MBSuccess) {
      data.voltage = decodeModbusFloat(node.getResponseBuffer(0), node.getResponseBuffer(1));
    } else continue;

    result = node.readHoldingRegisters(REG_CURRENT_START, 2);
    if (result == node.ku8MBSuccess) {
      data.current = decodeModbusFloat(node.getResponseBuffer(0), node.getResponseBuffer(1));
    } else continue;

    result = node.readHoldingRegisters(REG_POWER_START, 2);
    if (result == node.ku8MBSuccess) {
      data.storedPower = decodeModbusFloat(node.getResponseBuffer(0), node.getResponseBuffer(1));
    } else continue;

    data.isValid = true;
    batteryData[i] = data;
  }
}