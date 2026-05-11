# Project SCIR

Public dashboard is available at: [http://grafana.scir.studia.pacjo.ovh/public-dashboards/1379ea0022974383be55006346a08b78](http://grafana.scir.studia.pacjo.ovh/public-dashboards/1379ea0022974383be55006346a08b78).


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

- [x] ~~make utils return SensorReading classes~~
- [x] ~~simplify all reading functions in main (since all share basically the same structure). maybe create a sensor class per each and have a generic function with this class as parameter and this class would hold setup code, measurement function and delay. also rename from print* since that's no longer correct~~
- [x] ~~move server code out of platformio project~~
- [x] ~~add json parsing error handling and reconnection support~~
- [x] ~~maybe introduce logger which could log to serial and network?~~
- [x] ~~maybe namespaces to separate the same sensors per plant?~~
- [x] ~~can we replace SensorTask::getIntervalMs() with a value/attribute? - not have a function?~~
- [x] ~~add logger to troubleshoot queuing issues and server disconnects~~
- [x] ~~are we using tcp or udp? - let's use udp~~
- [ ] use (u)intNN_t
- [ ] full queue should drop old reading instead of new ones - or should it? tbd.
- [ ] maybe instead of `pushReading(take*())` we just do `push*()` - this would require a way to retrive those value locally (a queue before the network queue or smth)
- [ ] optimize stack size in setup()
- [ ] use Adafruit Unified Sensor based BMP280 library
- [ ] add `xTaskCreate(SensorTask::runTask, ...)` macro or something
- [ ] get rid of opaque attributes
- [ ] replace virtual with abstract methods?
