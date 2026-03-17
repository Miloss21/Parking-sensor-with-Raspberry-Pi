#pragma once
#include <string>

class LCD {
public:
    LCD(int address);
    ~LCD();
    
    bool init();
    void clear();
    void setCursor(int col, int row);
    void print(const std::string& text);
    void printLine(int row, const std::string& text);

private:
    int fd;
    int address;
    
    void writeByte(unsigned char val);
    void toggleEnable(unsigned char bits);
    void sendByte(unsigned char bits, int mode);
};