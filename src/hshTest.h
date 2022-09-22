#ifndef psRamTest_h
#define psRamTest_h

#include <Arduino.h>
#include <ArduinoJson.h>
#include <displayTest.h>
#include <drivers/fileSys.h>
#include <vector>

template <class T>
struct PSallocator {
    typedef T value_type;
    PSallocator() = default;
    template <class U> constexpr PSallocator(const PSallocator<U>&) noexcept {}
    [[nodiscard]] T* allocate(std::size_t n) {
        if(n > std::size_t(-1) / sizeof(T)) throw std::bad_alloc();
        if(auto p = static_cast<T*>(ps_malloc(n*sizeof(T)))) return p;
        throw std::bad_alloc();
    }
    void deallocate(T* p, std::size_t) noexcept { std::free(p); }
};
template <class T, class U>
bool operator==(const PSallocator<T>&, const PSallocator<U>&) { return true; }
template <class T, class U>
bool operator!=(const PSallocator<T>&, const PSallocator<U>&) { return false; }

struct allocator {
    void* allocate(size_t size) {return heap_caps_malloc(size, MALLOC_CAP_SPIRAM);}
    void deallocate(void* pointer) {heap_caps_free(pointer);}
    void* reallocate(void* ptr, size_t new_size) {return heap_caps_realloc(ptr, new_size, MALLOC_CAP_SPIRAM);}
};

class hshTest {
    private:
        int rs[13] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4000};
        spiDisplay display;
        fsDriver fs;

        std::vector<int, PSallocator<int> > psAlloc;
        using jsonDoc = BasicJsonDocument<allocator>;

        int arraySize = 10000;
        int* testArr;

        double getTime();
        boolean isEven(int x);
    public:
        void ramFill();
        void json( const char* jsonChar );
        void setArraySize(int size);
        int ramSpeed( boolean isExtRam = true );
        void flashSpeed();
};

#endif