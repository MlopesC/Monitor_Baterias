#ifndef SNMP_FLOAT_H
#define SNMP_FLOAT_H

#include <Arduino.h>
#include <SNMP_Agent.h>

/**
 * Classe SNMPFloat para monitorar valores float usando SNMP (via Gauge).
 */
class SNMPFloat {
public:
    /**
     * Construtor: recebe o OID como string.
     */
    SNMPFloat(const char* oid)
        : _oid(oid), _value(0.0f), _handler(nullptr) {}

    /**
     * Associa o objeto SNMPFloat ao SNMPAgent, registrando como Gauge.
     */
    void attach(SNMPAgent& agent) {
        _handler = agent.addGaugeHandler(_oid, reinterpret_cast<uint32_t*>(&_value));
    }

    /**
     * Atualiza o valor do SNMPFloat.
     */
    void setValue(float value) {
        _value = value;
    }

    /**
     * Retorna o valor atual.
     */
    float getValue() const {
        return _value;
    }

private:
    const char* _oid;
    float _value;
    ValueCallback* _handler;
};

#endif
