#ifndef psRamTest_h
#define psRamTest_h

#include <Arduino.h>
#include <ArduinoJson.h>
#include <displayTest.h>
#include <drivers/fileSys.h>

class hshTest {
    private:
        int rs[13] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4000};
        spiDisplay display;
        fsDriver fs;
        struct allocator {
            void* allocate(size_t size) {return heap_caps_malloc(size, MALLOC_CAP_SPIRAM);}
            void deallocate(void* pointer) {heap_caps_free(pointer);}
            void* reallocate(void* ptr, size_t new_size) {return heap_caps_realloc(ptr, new_size, MALLOC_CAP_SPIRAM);}
        };
        using jsonDoc = BasicJsonDocument<allocator>;

        int arraySize = 10000;
        char* charArr;

        double getTime();
    public:
        void ramFill();
        void json( const char* jsonChar );
        void setArraySize(int size);
        int ramSpeed( boolean isExtRam = true );
        void flashSpeed();
};

#endif