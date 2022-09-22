#include <drivers/fileSys.h>

void fsDriver::begin(){
    if ( !FILE_SYSTEM.begin() ) {
        Serial.println("Failed to mount the file system.");
        return;
    }
    Serial.println("File system mounted.");
    mounted = true;
}

void fsDriver::createFile(const char* fileName, uint32_t fileSize) {
    if( !mounted ){ return; }
    File f = FILE_SYSTEM.open(fileName, "w");
    for (uint32_t i = 0; i < fileSize; i++) {
        f.write((uint8_t)i);
    }
    f.close();
}

void fsDriver::readFile(const char* fileName, uint32_t fileSize) {
    if( !mounted ){ return; }
    File f = FILE_SYSTEM.open(fileName, "r");
    for (uint32_t i = 0; i < fileSize; i++) {
        uint8_t c = f.read();
        if (c != (uint8_t)i) {
            display.printf(DISP_INFO, "Unexpected byte at index %lu\n", (unsigned long)i);
        }
    }
    f.close();
}

void fsDriver::seekFile(
    const char* fileName,
    uint32_t fileSize,
    uint16_t numSeeks,
    uint32_t readSize) {

    if( !mounted ){ return; }

    File f = FILE_SYSTEM.open(fileName, "r");
    for (uint16_t i = 0; i < numSeeks; i++) {
        uint32_t offset = random(fileSize);
        f.seek(offset);
        for (uint32_t i = offset; i < offset + readSize && i < fileSize; i++) {
            uint8_t c = f.read();
            if (c != (uint8_t)i) {
                display.printf(DISP_INFO, "Unexpected byte at index %lu\n", (unsigned long)i);
            }
        }
    }
    f.close();
}