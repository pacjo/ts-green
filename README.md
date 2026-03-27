# Project SCIR

## Troubleshooting

### Adding Firebeetle 2 ESP32-C6 support to PlatformIO

create new file `.platformio/platforms/espressif32/boards/dfrobot_firebeetle2_esp32c6.json` with following contents:

```json
{
  "build": {
    "core": "esp32",
    "extra_flags": [
      "-DARDUINO_DFROBOT_FIREBEETLE_2_ESP32C6",
      "-DARDUINO_USB_MODE=1",
      "-DARDUINO_USB_CDC_ON_BOOT=1"
    ],
    "f_cpu": "160000000L",
    "f_flash": "80000000L",
    "flash_mode": "qio",
    "mcu": "esp32c6",
    "variant": "dfrobot_firebeetle2_esp32c6"
  },
  "connectivity": [
    "wifi",
    "bluetooth",
    "zigbee",
    "thread"
  ],
  "debug": {
    "openocd_target": "esp32c6.cfg"
  },
  "frameworks": [
    "arduino",
    "espidf"
  ],
  "name": "DFRobot FireBeetle 2 ESP32-C6",
  "upload": {
    "flash_size": "4MB",
    "maximum_ram_size": 327680,
    "maximum_size": 4194304,
    "require_upload_port": true,
    "speed": 460800
  },
  "url": "https://wiki.dfrobot.com/SKU_DFR1075_FireBeetle_2_Board_ESP32_C6/",
  "vendor": "DFRobot"
}
```

> [!IMPORTANT]
> In case of python package errors use virtual env `pio` at least once. E.g. `./.platformio/penv/bin/pio run`


### IDE completions for pio libraries

1. run:
    ```bash
    pio run --target compiledb
    ```
2. (optional) restart IDE language servers


## TODO:

- [ ] make utils return SensorReading classes
- [ ] full queue should drop old reading instead of new ones - or should it? tbd.
