#ifndef LCD_DISPLAY_H
#define LCD_DISPLAY_H

class LCDDisplay {
public:
    void begin();
    void showValue(int value);

private:
    int lastValue_ = 0;
    bool hasValue_ = false;
};

#endif // LCD_DISPLAY_H
