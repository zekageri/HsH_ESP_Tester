#ifndef fileSys_h
#define fileSys_h

#include <Arduino.h>
#include <LittleFS.h>
#include <displayTest.h>

#define FILE_SYSTEM LittleFS

class fsDriver {
    private:
        spiDisplay display;
        boolean mounted = false;
    public:
        void begin();
        void createFile(const char* fileName, uint32_t fileSize);
        void readFile(const char* fileName, uint32_t fileSize);
        void seekFile(const char* fileName, uint32_t fileSize, uint16_t numSeeks, uint32_t readSize);
};

#endif