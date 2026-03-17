#include "LCD.h"
#include <fcntl.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdexcept>

#define LCD_CHR 1
#define LCD_CMD 0
#define LCD_BACKLIGHT 0x08
#define ENABLE 0b00000100

LCD::LCD(int address) : address(address), fd(-1) {}

LCD::~LCD() {
    if (fd >= 0) {
        clear();
        close(fd);
    }
}

bool LCD::init() {
    fd = open("/dev/i2c-1", O_RDWR);
    if (fd < 0) return false;
    if (ioctl(fd, I2C_SLAVE, address) < 0) return false;

    sendByte(0x33, LCD_CMD);
    sendByte(0x32, LCD_CMD);
    sendByte(0x06, LCD_CMD);
    sendByte(0x0C, LCD_CMD);
    sendByte(0x28, LCD_CMD);
    sendByte(0x01, LCD_CMD);
    usleep(500);

    return true;
}

void LCD::clear() {
    sendByte(0x01, LCD_CMD);
    usleep(500);
}

void LCD::setCursor(int col, int row) {
    int row_offsets[] = {0x00, 0x40};
    sendByte(0x80 | (col + row_offsets[row]), LCD_CMD);
}

void LCD::print(const std::string& text) {
    for (char c : text) {
        sendByte(c, LCD_CHR);
    }
}

void LCD::printLine(int row, const std::string& text) {
    
    std::string padded = text;
    while (padded.length() < 16) padded += ' ';
    padded = padded.substr(0, 16);
    
    setCursor(0, row);
    print(padded);
}

void LCD::writeByte(unsigned char val) {
    unsigned char buf[1] = {val};
    write(fd, buf, 1);
}

void LCD::toggleEnable(unsigned char bits) {
    usleep(500);
    writeByte(bits | ENABLE);
    usleep(500);
    writeByte(bits & ~ENABLE);
    usleep(500);
}

void LCD::sendByte(unsigned char bits, int mode) {
    unsigned char bits_high = mode | (bits & 0xF0) | LCD_BACKLIGHT;
    unsigned char bits_low  = mode | ((bits << 4) & 0xF0) | LCD_BACKLIGHT;
    writeByte(bits_high);
    toggleEnable(bits_high);
    writeByte(bits_low);
    toggleEnable(bits_low);
}