## UAVXminimOSDs ##

MinimOSD is a simple on screen display adapter which mixes flight controller data into real-time inflight video telemetry. MinimOSD can also act as a freestanding device as it canb programmed to use the various inputs available on simple ATmega based development boards.

There are many many variants of the MinimOSD code but the ones here are derived from a very early version which compiles under Arduino 1.0.5-r2 This version of the development environment is available as a legacy off the Arduino main site. MinimOSD is not a mainstream UAVX interest so this code is provided for completeness only. Not all of the functionality described in the various wikis is available.

There are two versions which may be selected in OSD_Config.h by commenting/uncommenting #define UAVX before comping and loading using Arduino.

UAVX telemetry permits additional information including explicit navigation guidance information produced by UAVX. 

*WARNING*: the baseline versions of minimOSD infer the home position to be the first GPS position as received by minimOSD. If for any reason there is a mid-flight power-cycle or reset of the minimOSD board the home and potentially other information will be incorrect. Adding a suitable electrolytic capacitor across the minimOSD supply pins "may" reduce the risk.







