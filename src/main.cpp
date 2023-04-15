#include <Arduino.h>
#include "esp_camera.h"
#include <WiFi.h>
#include <TFT_eSPI.h>
#include <TJpg_Decoder.h>
#include <Joystick.h> //that my library :P https://github.com/BinaryBearzz/JoyStickModule.git
#include "screenprint.h"
#include "configCamera.h"

#define BUTTON 4
// Attention this code config and connect with TFT Screen TFT 1.8 inch. ST7735 inch 160x128 
camera_config_t config;

screenprint scrPrint;

Joystick button(-1, -1, BUTTON); // (xAxis, yAxis, button)

TFT_eSPI tft = TFT_eSPI(); /* TFT instance */

bool readyToSNAP = true;

unsigned long previousTime = 0;
int interval = 10000; //set interval (10000millis)10sec

void initTJpDec() // for convert buffer camera display to TFT screen
{
  TJpgDec.setJpgScale(2);
  TJpgDec.setSwapBytes(true);
  TJpgDec.setCallback(tft_output);
}

bool tft_output(int16_t x, int16_t y, uint16_t w, uint16_t h, uint16_t *bitmap)
{
  tft.setRotation(1);
  if (y >= tft.height())
    return 0;
  tft.pushImage(x, y, w, h, bitmap);
  return 1;
}

void statusCameraIsReady()
{
  if (readyToSNAP)
  {
    tft.fillCircle(6, 10, 4, tft.color565(0, 255, 0));
  }
  else
  {
    tft.fillCircle(6, 10, 4, tft.color565(255, 0, 0));
  }
}

void takePicture()
{
  camera_fb_t *fb = NULL;
  fb = esp_camera_fb_get();
  if (!fb)
  {
    Serial.println("Camera capture failed");
    return;
  }
  else
  {
    if (readyToSNAP)
    {
      readyToSNAP = false;
      TJpgDec.drawJpg(0, 4, (const uint8_t *)fb->buf, fb->len);
    }
    else
    {
      Serial.println("Camera is busy!!!!");
    }
  }
  esp_camera_fb_return(fb);
  readyToSNAP = true;
}


void setup()
{
  Serial.begin(115200);
  tft.begin();        /* TFT init */
  tft.setRotation(1); /* Landscape orientation, flipped */
  scrPrint.print("*Screen RDY*", 10, 2, tft.color565(0, 255, 0));
  delay(5000);
  tft.fillScreen(TFT_WHITE);
  initTJpDec();
  button.onEvent_SW([](bool stateSwitch){
    Serial.println("stateSwitch: "+String(stateSwitch));
    if(stateSwitch){
      takePicture();
    } });
  setupCamera();
}

void loop()
{
  delay(10);
  button.handle();

  if (millis() - previousTime >= interval)
  {
    takePicture(); // capture image every interval from you set
    statusCameraIsReady(); // capture image every interval from you set
    previousTime = millis();
  }
}
