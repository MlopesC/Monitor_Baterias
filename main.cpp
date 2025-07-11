#include <Arduino.h>
#include "modbus.h"
#include "snmp_handler.h"

BatteryData batteryData[NUM_BATTERIES];

void setup() {
  Serial.begin(115200);
  delay(1000);  // Espera monitor serial abrir

  initModbus();
  beginSNMP();

  Serial.println("Sistema de monitoramento iniciado.");
}

void loop() {
  readAllBatteries(batteryData);

  for (int i = 0; i < NUM_BATTERIES; i++) {
    if (batteryData[i].isValid) {
      updateSNMP(i, batteryData[i].voltage, batteryData[i].current, batteryData[i].storedPower);

      Serial.printf("Bateria %d: V=%.2f V | I=%.2f A | P=%.2f Wh\n",
                    i + 1,
                    batteryData[i].voltage,
                    batteryData[i].current,
                    batteryData[i].storedPower);
    } else {
      Serial.printf("Bateria %d: leitura inválida\n", i + 1);
    }
  }

  snmpLoop();
  delay(2000);  // Atualiza a cada 2 segundos
}
