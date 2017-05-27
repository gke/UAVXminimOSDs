## UAVXminimOSDs ##

MinimOSD is a simple on screen display adapter which mixes flight data into real-time inflight video telemetry. 
There are many variants of this code but the ones here are derived from a very early version which compiles under Arduino 1.0.5-r2 This version of the development environment is available as a legacy off the Arduino main site. MinimOSD is not a mainstream UAVX interest so this code is provided for completeness only.

There are two versions:

 * MavLinkOSD which supports MAVLink V1.0 telemetry
 * UAVXOSD which supports native UAVX telemetry

UAVXOSD telemetry permits additional information including explicitly navigation guidance information produced by UAVX. 

*WARNING*: the baseline versions of minimOSD infer the home position to be the first GPS position as received by minimOSD. If for any reason there is a mid-flight power-cycle or reset of the minimOSD board the home and potentially other information will be incorrect.







