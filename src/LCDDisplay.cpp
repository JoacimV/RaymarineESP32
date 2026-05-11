#include "LCDDisplay.h"

#include <Arduino.h>
#include <LovyanGFX.hpp>

namespace
{
    class LGFX : public lgfx::LGFX_Device
    {
        lgfx::Panel_ST7789 panel_;
        lgfx::Bus_SPI bus_;

    public:
        LGFX()
        {
            auto cfg = bus_.config();

            cfg.spi_host = SPI2_HOST;
            cfg.spi_mode = 0;
            cfg.freq_write = 20000000;

            cfg.pin_sclk = 7;
            cfg.pin_mosi = 6;
            cfg.pin_miso = -1;
            cfg.pin_dc = 15;

            bus_.config(cfg);
            panel_.setBus(&bus_);

            auto pcfg = panel_.config();

            pcfg.pin_cs = 14;
            pcfg.pin_rst = 21;
            pcfg.memory_width = 172;
            pcfg.memory_height = 320;
            pcfg.panel_width = 172;
            pcfg.panel_height = 320;
            pcfg.offset_x = 0;
            pcfg.offset_y = 0;

            pcfg.offset_rotation = 0;
            panel_.config(pcfg);

            setPanel(&panel_);
        }
    };

    LGFX lcd;
    constexpr int kBacklightPin = 22;
} // namespace

void LCDDisplay::begin()
{
    lcd.init();
    lcd.setRotation(1);

    pinMode(kBacklightPin, OUTPUT);
    digitalWrite(kBacklightPin, HIGH);

    lcd.setTextColor(TFT_WHITE, TFT_BLACK);
    lcd.setTextSize(4);
    lcd.setTextDatum(middle_center);

    randomSeed(analogRead(0));
}

void LCDDisplay::showValue(int value)
{
    lcd.fillScreen(TFT_BLACK);
    lcd.drawString(String(value), 86, 160);
    lcd.drawString("hej", 10, 12);
}
