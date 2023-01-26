# Try setting platform to sky130hd, nangate45, asap7
# Be aware that the time units for asap7 are in ps, not ns!
# You may want to change your constraint.sdc
export PLATFORM    = 

export DESIGN_NAME = alu
export VERILOG_FILES = ../../exercise4/alu.v
export SDC_FILE      = ../../exercise4/constraint.sdc

export CORE_UTILIZATION = 35
export PLACE_DENSITY = 0.60
export CORE_ASPECT_RATIO = 1
export CORE_MARGIN = 1.0
