#include "OPT3001.h"
#include "esphome/core/log.h"

namespace esphome {
namespace opt3001 {

  ClosedCube_OPT3001 myopt3001;
  
  void OPT3001Component::setup(){
    
    myopt3001.begin(0x45);
    delay(100);
    configureSensor();
    delay(100);
    myopt3001.readManufacturerID();
    myopt3001.readDeviceID();
  }

  // Most of this copied from https://github.com/closedcube/ClosedCube_OPT3001_Arduino/blob/master/examples/opt3001demo/opt3001demo.ino
  // I have no real idea what I'm doing.
  void OPT3001Component::configureSensor() {
    OPT3001_Config newConfig;

    newConfig.RangeNumber = B1100;
    newConfig.ConvertionTime = B0;
    newConfig.Latch = B1;
    newConfig.ModeOfConversionOperation = B11;

    OPT3001_ErrorCode errorConfig = myopt3001.writeConfig(newConfig);
    if (errorConfig != NO_ERROR)
      ESP_LOGD("error","OPT3001 configuration %i", errorConfig);
    else {
      OPT3001_Config sensorConfig = myopt3001.readConfig();
      ESP_LOGD("config","OPT3001 Current Config:");
      ESP_LOGD("config","------------------------------");
      ESP_LOGD("config","Conversion ready (R): %i", sensorConfig.ConversionReady);
      ESP_LOGD("config","Conversion time (R/W): %i", sensorConfig.ConvertionTime);
      ESP_LOGD("config","Fault count field (R/W): %i", sensorConfig.FaultCount);
      ESP_LOGD("config","Flag high field (R-only): %i", sensorConfig.FlagHigh);
      ESP_LOGD("config","Flag low field (R-only): %i", sensorConfig.FlagLow);
      ESP_LOGD("config","Latch field (R/W): %i", sensorConfig.Latch);
      ESP_LOGD("config","Mask exponent field (R/W): %i", sensorConfig.MaskExponent);
      ESP_LOGD("config","Mode of conversion operation (R/W): %i", sensorConfig.ModeOfConversionOperation);
      ESP_LOGD("config","Polarity field (R/W): %i", sensorConfig.Polarity);
      ESP_LOGD("config","Overflow flag (R-only): %i", sensorConfig.OverflowFlag);
      ESP_LOGD("config","Range number (R/W): %i", sensorConfig.RangeNumber);
      ESP_LOGD("config","------------------------------");
    }

    u_short manufacturer_id = myopt3001.readManufacturerID();
    manufacturer_id_sensor->publish_state(manufacturer_id);

    u_short device_id = myopt3001.readDeviceID();
    device_id_sensor->publish_state(device_id);

    u_short high_limit = myopt3001.readHighLimit().lux;
    high_limit_sensor->publish_state(high_limit);

    u_short low_limit = myopt3001.readLowLimit().lux;
    low_limit_sensor->publish_state(low_limit);

    u_short error_code = myopt3001.readResult().error;
  }

  void OPT3001Component::update() {
    ESP_LOGD("update", "Sending update");
    int lux_level = myopt3001.readResult().lux;
    lux_sensor->publish_state(lux_level);
  }

}  // namespace opt3001
}  // namespace esphome

