// [CFXS] //
#include <CFXS/Base/Debug.hpp>
#include <CFXS/Platform/CPU.hpp>

extern "C" void abort() {
    CFXS_ERROR("abort");
    CFXS::CPU::Reset();
}