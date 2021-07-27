import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import i2c, sensor

DEPENDENCIES = ["i2c"]

opt3001_ns = cg.esphome_ns.namespace("opt3001")
OPT3001Component = opt3001_ns.class_(
    "OPT3001Component", cg.PollingComponent, i2c.I2CDevice
)