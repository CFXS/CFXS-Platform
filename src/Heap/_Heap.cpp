// [CFXS] //
#include <CFXS/Platform/Heap/_Heap.hpp>
#include <CFXS/Base/Debug.hpp>

//////////////////////////////////////////////////////////////////////////////////
// dlmalloc extern
extern "C" void* create_mspace_with_base(void* base, size_t capacity, int locked);
//////////////////////////////////////////////////////////////////////////////////

namespace CFXS {

    Heap::Heap(const char* label, void* base, size_t size) : m_Label(label) {
        m_Handle = create_mspace_with_base(base, size, 0);
        if (m_Handle) {
            m_Size         = size;
            m_UsedBytes    = 0;
            m_MaxUsedBytes = 0;
            m_AllocCount   = 0;
            m_FreeCount    = 0;
        } else {
            CFXS_ERROR("Heap: Failed to create mspace [base = 0x%p, size = %u]", base, size);
        }
    }

    Heap::~Heap() {
        CFXS_ERROR("~Heap: ???");
    }

    //////////////////////////////////////////////////////////////////////////////////

    /// Allocate block of memory
    /// \param size bytes to allocate
    void* Heap::Allocate(size_t size) {
#ifdef CFXS_HEAP_CHECK_LOCK
        CFXS_ASSERT(!m_Locked, "Heap(%s): locked :(", GetLabel());
        m_Locked = true;
#endif

        size += 4;
        if (auto ptr = mspace_malloc(GetHandle(), size)) {
            m_AllocCount++;
            m_UsedBytes += size;
            if (m_UsedBytes > m_MaxUsedBytes)
                m_MaxUsedBytes = m_UsedBytes;
            *(uint32_t*)ptr = size;
#ifdef CFXS_HEAP_CHECK_LOCK
            m_Locked = false;
#endif
            return (uint32_t*)ptr + 1;
        }

        CFXS_ERROR("Heap(%s): failed to allocate %u bytes\n", GetLabel(), size);

#ifdef CFXS_HEAP_CHECK_LOCK
        m_Locked = false;
#endif
        return nullptr;
    }

    /// Deallocate pointer
    void Heap::Deallocate(void* ptr) {
#ifdef CFXS_HEAP_CHECK_LOCK
        CFXS_ASSERT(!m_Locked, "Heap(%s): locked :(", GetLabel());
        m_Locked = true;
#endif

        if (ptr) {
            m_FreeCount++;
            m_UsedBytes -= *(((uint32_t*)ptr) - 1);
            mspace_free(GetHandle(), ((uint32_t*)ptr) - 1);
        } else {
            CFXS_ERROR("Heap(%s): free nullptr :(\n", GetLabel());
        }

#ifdef CFXS_HEAP_CHECK_LOCK
        m_Locked = false;
#endif
    }

} // namespace CFXS