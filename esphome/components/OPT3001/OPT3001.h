#pragma once

#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/i2c/i2c.h"
#include "ClosedCube_OPT3001/ClosedCube_OPT3001.h"


namespace esphome {
namespace opt3001 {

/// This class implements support for the OPT3001 family of temperature+humidity i2c sensors.
class OPT3001Component : public PollingComponent, public i2c::I2CDevice {
 public:
  
  void setup() override;
  void dump_config() override;
  float get_setup_priority() const override;
  void update() override;
  
 protected:
   
  void configureSensor();

  sensor::Sensor *luminosity_sensor_;
};

}  // namespace opt3001
}  // namespace esphome
