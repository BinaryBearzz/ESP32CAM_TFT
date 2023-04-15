#include <Arduino.h>
#include <TFT_eSPI.h>

extern TFT_eSPI tft;
class screenprint
{
private:
    
    bool haveColor = false;
    uint16_t defaultColor;

public:
    String buff_printText;
    screenprint() { haveColor = false; };
    screenprint(uint16_t setColor)
    {
        haveColor = true;
        defaultColor = setColor;
    };

    void print(String txt, int x, int y, uint16_t color, uint8_t txtsize, bool clearTxt = true)
    {
        int locatX = x;
        int locatY = y;

        tft.setRotation(3); //(0 defualt, 1 left rotate , 2 up side down, 3 right rotate) First cursor under the usage pin.
        tft.setTextWrap(true);
        tft.setTextSize(txtsize);
        if (buff_printText != NULL && (buff_printText != txt) && clearTxt)
        {
            tft.setTextColor(TFT_GREEN);
            tft.setCursor(locatX, locatY);
            tft.println(buff_printText);
        }
        tft.setTextColor(color);
        tft.setCursor(locatX, locatY);
        tft.println(txt);
        buff_printText = txt;
    }

    void print(String txt, int x, int y)
    {
        const uint8_t textSize = 1;
        if (!haveColor)
            print(txt, x, y, tft.color565(0, 0, 255), textSize, false);
        else
            print(txt, x, y, defaultColor, textSize, false);
    }

    void print(String txt, int x, int y, uint16_t color, bool clearTxt = true)
    {
        const uint8_t textSize = 1;
        print(txt, x, y, color, textSize, clearTxt);
    }
};
