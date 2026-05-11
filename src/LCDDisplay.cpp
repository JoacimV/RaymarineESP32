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
    constexpr int kLabelX = 5;
    constexpr int kLabelY = 40;
    constexpr int kValueX = 5;
    constexpr int kValueY = 140;
    constexpr int kValueWidth = 160;
    constexpr int kValueHeight = 48;
} // namespace

void LCDDisplay::begin()
{
    lcd.init();
    lcd.invertDisplay(true);
    lcd.setRotation(1);

    pinMode(kBacklightPin, OUTPUT);
    digitalWrite(kBacklightPin, HIGH);

    lcd.fillScreen(TFT_BLACK);
    lcd.setTextColor(TFT_WHITE, TFT_BLACK);
    lcd.setTextFont(4);
    lcd.setTextSize(1);

    lcd.drawString("hej", kLabelX, kLabelY);
}

void LCDDisplay::showValue(int value)
{
    if (hasValue_ && value == lastValue_)
    {
        return;
    }

    lcd.fillRect(kValueX, kValueY, kValueWidth, kValueHeight, TFT_BLACK);
    lcd.drawString(String(value), kValueX, kValueY);

    lastValue_ = value;
    hasValue_ = true;
}
