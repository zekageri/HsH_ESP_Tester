#include <displayTest.h>

#define ARDPRINTF
#define ARDBUFFER 16

void spiDisplay::init() {
    tft.init();
    tft.setRotation(3);
    tft.setTextSize(2);
    tft.setSwapBytes(true);
    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_WHITE);
}

int spiDisplay::printf( int type, const char *message, ... ) {
    if( type == -1 ){ tft.println("\n"); return 0; }

    if( type == DISP_INFO ){
        tft.setTextColor(TFT_WHITE);
    }else if( type == DISP_ERROR ){
        tft.setTextColor(TFT_RED);
    }else if( type == DISP_WARN ){
        tft.setTextColor(TFT_ORANGE);
    }else{
        tft.setTextColor(TFT_BLUE);
    }

    char s[564];
    va_list  args;
    va_start (args, message);
    vsprintf (s, message, args);
    tft.print(s);
    va_end (args);

    #if USE_SERIAL_DEBUG
        Serial.print(s);
    #endif
    tft.setTextColor(TFT_WHITE);
    //allText += String(s);
    int cursorPos = tft.getCursorY();
    if( cursorPos >= 104 ){
        //scrollOne();
        clear();
    }
    return 0;
}

void spiDisplay::scrollOne(){
    int startNewLine = allText.indexOf('\n');
    allText.remove(0,startNewLine);
    startNewLine = allText.indexOf('\n');
    allText.remove(0,startNewLine);
    clear();
    tft.print(allText);
}

void spiDisplay::clear(){
    tft.setCursor(0,0);
    tft.fillScreen(TFT_BLACK);
}