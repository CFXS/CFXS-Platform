#include <stddef.h>

extern const char __HEAP_START__;

extern "C" void* _sbrk(ptrdiff_t incr) {
    return (void*)&__HEAP_START__;
}