#ifndef MODBUS_H
#define MODBUS_H

#include <Arduino.h>

// -----------------------------
// Definições de pinos RS-485
// -----------------------------
#define MAX485_DE_RE_PIN 4   // Controle do driver RS-485
#define RX_PIN 16            // Pino RX da UART2
#define TX_PIN 17            // Pino TX da UART2

// -----------------------------
// Parâmetros Modbus
// -----------------------------
#define NUM_BATTERIES 6

const uint8_t SLAVE_ADDRESSES[NUM_BATTERIES] = {1, 2, 3, 4, 5, 6};

// Endereços dos registradores
#define REG_VOLTAGE_START 0x0000
#define REG_CURRENT_START 0x0002
#define REG_POWER_START   0x0004

// -----------------------------
// Estrutura de dados da bateria
// -----------------------------
struct BatteryData {
  float voltage;
  float current;
  float storedPower;
  bool isValid;
};

// -----------------------------
// Protótipos de funções
// -----------------------------
void preTransmission();
void postTransmission();
void initModbus();
void readAllBatteries(BatteryData* batteryData);
float decodeModbusFloat(uint16_t reg1, uint16_t reg2);

#endif
