#ifndef displayTest_h
#define displayTest_h

#include <Arduino.h>
#include <TFT_eSPI.h>
#include <SPI.h>

#define DISP_INFO 0
#define DISP_ERROR 1
#define DISP_WARN 2

#define USE_SERIAL_DEBUG true

class spiDisplay {
    private:
        boolean hasDisplay = true;
        TFT_eSPI tft = TFT_eSPI();
        String allText;
        void scrollOne();
    public:
        void init( boolean hasDisplay = true );
        int printf( int type, const char *message, ...  );
        void clear();
};

#endif