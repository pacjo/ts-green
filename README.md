# Project SCIR

## Troubleshooting

### Adding Firebeetle 2 ESP32-C6 support to PlatformIO

Since Arduino Core 3.X platforms aren't supported by upstream PlatformIO project it is necessary to use [pioarduino](https://github.com/pioarduino/platform-espressif32) provided version instead. To do that modify `platformio.ini` to have this line:

```ini
platform = https://github.com/pioarduino/platform-espressif32/releases/download/stable/platform-espressif32.zip
board = ...
```


### Python package errors when executing `pio ...` commands

When executing some `pio`/`platformio` commands errors such as `ModuleNotFoundError: No module named 'platformio'.` can occur. This shouldn't affect the project in any way. It's recommended to wait and let the command continue on it's own instead of stopping the execution.


### IDE completions for pio libraries

1. run:
    ```bash
    pio run --target compiledb
    ```
2. (optional) restart IDE language servers


## TODO:

- [ ] make utils return SensorReading classes
- [ ] full queue should drop old reading instead of new ones - or should it? tbd.
