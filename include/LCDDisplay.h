#ifndef LCD_DISPLAY_H
#define LCD_DISPLAY_H
#include <stdint.h>

class LCDDisplay {
public:
    void begin();
    void showValue(int value);
    void showButton(const char* label);

private:
    int lastValue_ = 0;
    bool hasValue_ = false;
};

#endif // LCD_DISPLAY_H
