#pragma once

#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/i2c/i2c.h"

namespace esphome {
namespace mpl3115 {

class MPL3115Component : public PollingComponent, public i2c::I2CDevice{
 public:
  void set_pressure_sensor(sensor::Sensor *mpl3115_pressure_sensor) { mpl3115_pressure_sensor_ = mpl3115_pressure_sensor; }
  void set_temperture_sensor(sensor::Sensor *mpl3115_temperature_sensor) { mpl3115_temperature_sensor_ = mpl3115_temperature_sensor; }
  void set_altitiude_light_sensor(sensor::Sensor *mpl3115_altitude_sensor) { mpl3115_altitude_sensor_ = mpl3115_altitude_sensor; }

  void setup() override;
  void dump_config() override;
  float get_setup_priority() const override;
  void update() override;

  protected:
    void configureSensor_();
    sensor::Sensor *mpl3115_pressure_sensor_;
    sensor::Sensor *mpl3115_temperature_sensor_;
    sensor::Sensor *mpl3115_altitude_sensor_;
  
};
}// Namespace ESP
}// Namespace MPL3115
