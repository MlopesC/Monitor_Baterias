#include "snmp_handler.h"

// Definições (declarar variáveis globais AQUI, só neste arquivo)
SNMPAgent snmp;

SNMPFloat snmpVoltageObj[NUM_BATTERIES] = {
  SNMPFloat("1.3.6.1.4.1.99999.1.1"), SNMPFloat("1.3.6.1.4.1.99999.1.2"),
  SNMPFloat("1.3.6.1.4.1.99999.1.3"), SNMPFloat("1.3.6.1.4.1.99999.1.4"),
  SNMPFloat("1.3.6.1.4.1.99999.1.5"), SNMPFloat("1.3.6.1.4.1.99999.1.6")
};

SNMPFloat snmpCurrentObj[NUM_BATTERIES] = {
  SNMPFloat("1.3.6.1.4.1.99999.2.1"), SNMPFloat("1.3.6.1.4.1.99999.2.2"),
  SNMPFloat("1.3.6.1.4.1.99999.2.3"), SNMPFloat("1.3.6.1.4.1.99999.2.4"),
  SNMPFloat("1.3.6.1.4.1.99999.2.5"), SNMPFloat("1.3.6.1.4.1.99999.2.6")
};

SNMPFloat snmpStoredPowerObj[NUM_BATTERIES] = {
  SNMPFloat("1.3.6.1.4.1.99999.3.1"), SNMPFloat("1.3.6.1.4.1.99999.3.2"),
  SNMPFloat("1.3.6.1.4.1.99999.3.3"), SNMPFloat("1.3.6.1.4.1.99999.3.4"),
  SNMPFloat("1.3.6.1.4.1.99999.3.5"), SNMPFloat("1.3.6.1.4.1.99999.3.6")
};

void beginSNMP() {
  for (int i = 0; i < NUM_BATTERIES; i++) {
    snmpVoltageObj[i].attach(snmp);
    snmpCurrentObj[i].attach(snmp);
    snmpStoredPowerObj[i].attach(snmp);
  }
  snmp.begin();
}

void updateSNMP(int i, float v, float c, float p) {
  if (i >= 0 && i < NUM_BATTERIES) {
    snmpVoltageObj[i].setValue(v);
    snmpCurrentObj[i].setValue(c);
    snmpStoredPowerObj[i].setValue(p);
  }
}

void snmpLoop() {
  snmp.loop();
}
