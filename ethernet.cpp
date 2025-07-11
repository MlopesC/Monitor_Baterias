#include <Arduino.h>
#include <ETH.h>           // IMPORTANTE
#include <Ethernet.h>
#include <WiFi.h>
#include "ethernet.h"
#include "snmp_handler.h"


#define ETH_CLK_MODE ETH_CLOCK_GPIO0_IN
#define ETH_PHY_POWER 16
#define ETH_PHY_MDC 23
#define ETH_PHY_MDIO 18
#define ETH_TYPE ETH_PHY_LAN8720
#define ETH_ADDR 0

bool USE_DHCP = true;

void EthernetEvent(WiFiEvent_t event) {
  switch (event) {
    case ARDUINO_EVENT_ETH_START:
      ETH.setHostname("esp32-battery-monitor");
      break;
    case ARDUINO_EVENT_ETH_GOT_IP:
      Serial.print("ETH MAC: "); Serial.println(ETH.macAddress());
      Serial.print("IP: "); Serial.println(ETH.localIP());
      beginSNMP();
      break;
    case ARDUINO_EVENT_ETH_CONNECTED:    Serial.println("ETH Connected"); break;
    case ARDUINO_EVENT_ETH_DISCONNECTED: Serial.println("ETH Disconnected"); break;
    case ARDUINO_EVENT_ETH_STOP:         Serial.println("ETH Stopped"); break;
    default: break;
  }
}

void initEthernet() {
  WiFi.onEvent(EthernetEvent);
  ETH.begin(ETH_ADDR, ETH_PHY_POWER, ETH_PHY_MDC, ETH_PHY_MDIO, ETH_TYPE, ETH_CLK_MODE);
  delay(2000);
}
