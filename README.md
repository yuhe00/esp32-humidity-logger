# esp32-humidity-logger

## Hardware

- [ESP32](https://www.aliexpress.com/item/MH-ET-LIVE-ESP32-Development-Board-WiFi-Bluetooth-Ultra-Low-Power-Consumption-Dual-Core-ESP-32/32813121497.html?spm=2114.search0104.3.1.617d4071jQsPpx&ws_ab_test=searchweb0_0,searchweb201602_4_10152_10151_10065_10344_10068_10342_10343_10059_10340_10341_10696_100031_10084_10083_10103_10618_10624_10307_10623_10622_10621_10620,searchweb201603_6,ppcSwitch_7&algo_expid=c8f7d55f-16c9-4781-a921-fe2b3cb0994c-0&algo_pvid=c8f7d55f-16c9-4781-a921-fe2b3cb0994c&transAbTest=ae803_2&priceBeautifyAB=0)
- [DHT-11](https://www.aliexpress.com/item/Free-Shipping-1x-DHT11-DHT-11-Digital-Temperature-and-Humidity-Temperature-sensor-for-Arduino-Hot/32243034419.html?spm=2114.search0104.3.1.6dd468fdBddFND&ws_ab_test=searchweb0_0,searchweb201602_4_10152_10151_10065_10344_10068_10342_10343_10059_10340_10341_10696_100031_10084_10083_10103_10618_10624_10307_10623_10622_10621_10620,searchweb201603_6,ppcSwitch_7&algo_expid=60d4ec53-0206-45fb-a473-c76441e9711d-0&algo_pvid=60d4ec53-0206-45fb-a473-c76441e9711d&transAbTest=ae803_2&priceBeautifyAB=0)

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
