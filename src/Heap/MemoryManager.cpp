// ---------------------------------------------------------------------
// CFXS Framework Platform Module <https://github.com/CFXS/CFXS-Platform>
// Copyright (C) 2022 | CFXS / Rihards Veips
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>
// ---------------------------------------------------------------------
// [CFXS] //
#include <array>
#include <CFXS/Base/Debug.hpp>
#include <CFXS/Platform/Heap/MemoryManager.hpp>

#ifndef CFXS_PLATFORM_MAX_HEAP_COUNT // [CFXSDEF:Platform] Max user heaps
    #define CFXS_PLATFORM_MAX_HEAP_COUNT 4
#endif

//////////////////////////////////////////////////////////////////////////////////
// dlmalloc extern
extern "C" void* dlmalloc(size_t bytes);
extern "C" void dlfree(void* mem);
//////////////////////////////////////////////////////////////////////////////////
void* operator new(size_t size) {
    void* p = dlmalloc(size);
    return p;
}
void* operator new[](size_t size) {
    void* p = dlmalloc(size);
    return p;
}

void operator delete(void* p) {
    dlfree(p);
}

void operator delete(void* p, size_t s) {
    dlfree(p);
}
//////////////////////////////////////////////////////////////////////////////////

namespace CFXS {

    //////////////////////////////////////////////////////////////////////////////////
    static __noinit std::array<Heap, CFXS_PLATFORM_MAX_HEAP_COUNT> s_Heaps;
    static size_t s_HeapCount = 0;
    //////////////////////////////////////////////////////////////////////////////////

    /// Create new heap
    /// \param label heap label
    /// \param size max size
    /// \param baseAddres use specified base address (if nullptr, allocate in main heap)
    Heap* MemoryManager::CreateHeap(const char* label, size_t size, void* baseAddress) {
        CFXS_ASSERT(size, "CreateHeap: Size is 0");

        if (s_HeapCount == CFXS_PLATFORM_MAX_HEAP_COUNT) {
            CFXS_ERROR("CreateHeap(%s, %u, 0x%p): Too many heaps", label, size, baseAddress);
            return nullptr;
        }

        if (baseAddress) {
            CFXS_ASSERT(!((size_t)baseAddress & 3), "CreateHeap(%s, %u, 0x%p): Base address not aligned to 4", label, size, baseAddress);
        } else {
            baseAddress = new uint8_t[size];
            if (!baseAddress) {
                CFXS_ERROR("CreateHeap(%s, %u, 0x%p): Failed to allocate region", label, size, baseAddress);
                return nullptr;
            }
        }

        s_HeapCount++;
        return new (&s_Heaps[s_HeapCount - 1]) Heap(label, baseAddress, size);
    }

} // namespace CFXS