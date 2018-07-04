# esp32-sensor-elk

## Prerequisites

- `python2`

```
cd esp8266/tools && python2 get.py && cd ../../
```

## Build

```
BUILD_EXTRA_FLAGS='\
  -D SSID_NAME=\"<SSID_NAME>\" \
  -D SSID_PASS=\"<SSID_PASS>\" \
  -D LOGZIO_TOKEN=\"<LOGZIO_TOKEN>\"' \
  ./espmake
```
