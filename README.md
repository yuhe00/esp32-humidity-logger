# esp32-humidity-logger

## Prerequisites

- `python2`

```
cd arduino-esp32/tools && python2 get.py && cd ../../
```

## Build

```
BUILD_EXTRA_FLAGS='\
  -D SSID_NAME=\"<SSID_NAME>\" \
  -D SSID_PASS=\"<SSID_PASS>\" \
  -D LOGZIO_TOKEN=\"<LOGZIO_TOKEN>\"' \
  ./espmake
```
