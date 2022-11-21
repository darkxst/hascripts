/*
  user_config_override.h - user configuration overrides my_user_config.h for Tasmota

  Copyright (C) 2021  Theo Arends

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef _USER_CONFIG_OVERRIDE_H_
#define _USER_CONFIG_OVERRIDE_H_

/*****************************************************************************************************\
 * USAGE:
 *   To modify the stock configuration without changing the my_user_config.h file:
 *   (1) copy this file to "user_config_override.h" (It will be ignored by Git)
 *   (2) define your own settings below
 *
 ******************************************************************************************************
 * ATTENTION:
 *   - Changes to SECTION1 PARAMETER defines will only override flash settings if you change define CFG_HOLDER.
 *   - Expect compiler warnings when no ifdef/undef/endif sequence is used.
 *   - You still need to update my_user_config.h for major define USE_MQTT_TLS.
 *   - All parameters can be persistent changed online using commands via MQTT, WebConsole or Serial.
\*****************************************************************************************************/

// -- Master parameter control --------------------
#undef  CFG_HOLDER
#define CFG_HOLDER        4618                   // [Reset 1] Change this value to load SECTION1 configuration parameters to flash

// -- Setup your own Wifi settings  ---------------
// #undef  STA_SSID1
// #define STA_SSID1         "YourSSID"             // [Ssid1] Wifi SSID

// #undef  STA_PASS1
// #define STA_PASS1         "YourWifiPassword"     // [Password1] Wifi password

//#if defined(FIRMWARE_USEE) || defined(FIRMWARE_DIALED)
#ifdef FIRMWARE_USEE
  //UseeLink Template
  #undef USER_TEMPLATE
  #define USER_TEMPLATE     "{\"NAME\":\"SM-SO301-AU\",\"GPIO\":[52,0,0,57,29,17,0,0,31,30,32,0,25],\"FLAG\":0,\"BASE\":18}"
  #define MODULE            USER_MODULE

  #undef SWITCH_MODE
  #define SWITCH_MODE       PUSHBUTTON            // [SwitchMode] TOGGLE, FOLLOW, FOLLOW_INV, PUSHBUTTON

  #define USER_BACKLOG      "Rule 1 ON"
  #define USER_RULE1         "ON button1#state==2 DO add1 1 ENDON ON var1#state|2 DO power0 1 BREAK ON var1#state DO power0 0 ENDON"

  #undef OTA_URL
  #define OTA_URL           "https://github.com/darkxst/hascripts/blob/main/config/tasmota/firmware-useelink.bin.gz?raw=true"  // [OtaUrl]
#endif


#ifdef FIRMWARE_ATHOM
  #define USER_TEMPLATE     "{\"NAME\":\"Athom Plug V2\",\"GPIO\":[0,0,0,3104,0,32,0,0,224,576,0,0,0,0],\"FLAG\":0,\"BASE\":18}"
  #define MODULE            USER_MODULE
#endif


//full config will include MQTT and maybe iDioT wifi
#ifdef FIRMWARE_DIALED
// -- Setup your own MQTT settings  ---------------
  #undef  MQTT_HOST
  #define MQTT_HOST         "homeassistant.local" // [MqttHost]

  #undef  MQTT_PORT
  #define MQTT_PORT         1883                   // [MqttPort] MQTT port (10123 on CloudMQTT)

  #undef  MQTT_USER
  #define MQTT_USER         "mqtt"         // [MqttUser] Optional user

  #undef  MQTT_PASS
  #define MQTT_PASS         "smqrt"         // [MqttPassword] Optional password
#endif




#ifdef FIRMWARE_ZBBRIDGE_DI
  //pre-built for ZHA integration EZSP

  //set OTA_URL and issue Updrade=1 command then we revert OTA_URL #needs testing
   //do test #define USER_BACKLOG      "Rule 1 ON;Upgrade 1;OtaUrl 1"

  #undef OTA_URL
  #define OTA_URL           "http://ota.tasmota.com/tasmota/release/tasmota-zbbridge.bin.gz"

  #define USER_TEMPLATE     "{\"NAME\":\"ZHA ZBBridge\",\"GPIO\":[56,208,0,209,59,58,0,0,0,0,0,0,17],\"FLAG\":0,\"BASE\":18}"
  #define MODULE            USER_MODULE

 
  #define USER_RULE1        "ON System#Boot do TCPStart 8888 endon"
  #define USER_BACKLOG      "Rule 1 ON;"
#endif

#endif  // _USER_CONFIG_OVERRIDE_H_
