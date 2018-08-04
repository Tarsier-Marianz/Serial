# Serial -Arduino

Collections of samples and experiments on how to use and play [Serial](https://www.arduino.cc/reference/en/language/functions/communication/serial/) in Arduino.



* `SerialEcho` - a simple example on how to echo back read byte from entered data of (any terminal emulator like [putty](https://www.putty.org/), [TeraTerm](https://ttssh2.osdn.jp/index.html.en), Hyperterminal of Windows and etc.).
* `SerialLEDController` - controls LED by sending `ON` or `OFF` (not case sensitive) to serial. Just hit *enter* to send command, report when command is invalid.
* `SerialEventTerminal` - just a simple example using [SerialEvent](https://www.arduino.cc/en/Tutorial/SerialEvent) of [Arduino](https://www.arduino.cc/), mimicking some AT commands and other dummy just to play serial communication of Arduino to PC.