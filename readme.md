# Connecting Wiring Between ESP32CAM Ai Thinker - TFT 1.8 inch. ST7735
 TFT Screen pin ||  esp32cam pin
 TFT_MISO || -1  // not connect
 TFT_MOSI || 13  // Master out slave in
 TFT_SCLK || 14  // Clock signal
 TFT_CS   ||  15 // Chip select control pin
 TFT_DC   ||  2  // Data Command control pin
 TFT_RST  || 12  // Set TFT_RST to -1 if display RESET is connected to ESP32 board RST

![Pinout](https://github.com/BinaryBearzz/ESP32CAM_TFT/blob/main/Images/esp32-cam-connectTFT.png?=250x250)

