// [CFXS] //
#ifdef CFXS_CORE_CORTEX_M // Generic Cortex-M
    #include <CFXS/Platform/CPU.hpp>

namespace CFXS::CPU {

    void __naked BlockingCycles(uint32_t cycles) {
        asm("    subs    r0, #1\n"
            "    bne     SysCtlDelay\n"
            "    bx      lr");
    }

} // namespace CFXS::CPU

#endif