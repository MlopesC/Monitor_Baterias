#ifndef SNMP_HANDLER_H
#define SNMP_HANDLER_H

#include <SNMP_Agent.h>
#include "snmp_float.h"

#define NUM_BATTERIES 6

extern SNMPAgent snmp;

extern SNMPFloat snmpVoltageObj[NUM_BATTERIES];
extern SNMPFloat snmpCurrentObj[NUM_BATTERIES];
extern SNMPFloat snmpStoredPowerObj[NUM_BATTERIES];

void beginSNMP();
void updateSNMP(int i, float v, float c, float p);
void snmpLoop();

#endif
