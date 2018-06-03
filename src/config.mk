THIS_DIR := $(realpath $(dir $(realpath $(lastword $(MAKEFILE_LIST)))))
ROOT := $(THIS_DIR)/..
CHIP=esp32
UPLOAD_PORT = /dev/ttyUSB0
UPLOAD_SPEED = 1500000
VERBOSE=1
