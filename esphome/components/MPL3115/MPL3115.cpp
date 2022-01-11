#include "MPL3115.h"
#include "SparkFunMPL3115A2.h"
#include "esphome/core/log.h"
#include "Wire.h" // for IIC communication

#define MPL3115A2_ADDRESS 0x60 // 7-bit I2C address

long startTime;


namespace esphome {
namespace mpl3115 {

static const char *const TAG = "mpl3115";
//Create an instance of the object
  MPL3115A2 myMpl3115;
  
  void MPL3115Component::setup () {
    myMpl3115.begin();
    delay(100);
    configureSensor_();
    delay(100);
  }

  // I have no real idea what I'm doing.
  void MPL3115Component::configureSensor_() {
 
  //Configure the sensor
  //myMpl3115.setModeAltimeter(); // Measure altitude above sea level in meters
  myMpl3115.setModeBarometer(); // Measure pressure in Pascals from 20 to 110 kPa

  myMpl3115.setOversampleRate(7); // Set Oversample to the recommended 128
  myMpl3115.enableEventFlags(); // Enable all three pressure and temp event flags 

   
   u_short manufacturer_id = myMpl3115.readManufacturer_id(); 
    if (manufacturer_id != 196)
      ESP_LOGD("error","Device nicht gefiunden");
    else {
      ESP_LOGD("config","MPL3115 Current Config:");
      ESP_LOGD("config","------------------------------");
      ESP_LOGD("config","manufacturer_id: %i", manufacturer_id);
      ESP_LOGD("config","------------------------------");
    }

  }
  
  void MPL3115Component::dump_config() {
  ESP_LOGCONFIG(TAG, "MPL3115:");
  LOG_I2C_DEVICE(this);
  if (this->is_failed()) {
    ESP_LOGE(TAG, "Communication with MPL3115 failed!");
  }

  LOG_UPDATE_INTERVAL(this);
}
  
  float MPL3115Component::get_setup_priority() const { return setup_priority::DATA; }
 
  void MPL3115Component::update() {
    
    float pressure = myMpl3115.readPressure()/100;
    float temperature = myMpl3115.readTemp();
    float altitude = NAN;

  ESP_LOGD("update", "Sending update");
  ESP_LOGD(TAG, "Got temperature=%.1f°C pressure=%.1fHPa altitude=%.1fm", temperature, pressure,
           altitude);
  if (this->mpl3115_temperature_sensor_ != nullptr)
    this->mpl3115_temperature_sensor_->publish_state(temperature);
  if (this->mpl3115_pressure_sensor_ != nullptr)
    this->mpl3115_pressure_sensor_->publish_state(pressure);
  if (this->mpl3115_altitude_sensor_ != nullptr)
    this->mpl3115_altitude_sensor_->publish_state(altitude);
    this->status_clear_warning();    
  
  }

}// Namespace ESP
}// Namespace MPL3115
