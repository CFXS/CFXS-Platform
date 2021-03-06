// [CFXS] //
#pragma once

//////////////////////////////////////////////////////////////////////////////////
extern "C" void* mspace_malloc(void* msp, size_t bytes);
extern "C" void mspace_free(void* msp, void* mem);
//////////////////////////////////////////////////////////////////////////////////

// CFXS_HEAP_CHECK_LOCK (CFXSDEF:Platform) Check if heap is locked on alloc and free

namespace CFXS {

    class Heap {
    public:
        Heap() = default;
        Heap(const char* label, void* handle, size_t size);
        ~Heap();

        /// Allocate block of memory
        /// \param size bytes to allocate
        void* Allocate(size_t size);

        /// Allocate block of memory with type
        template<typename T>
        T* Allocate(size_t n = 1) {
            return reinterpret_cast<T*>(Allocate(sizeof(T) * n));
        }

        /// Deallocate pointer
        void Deallocate(void* ptr);

        /// Allocate memory and call constructor
        template<typename T, typename... Args>
        T* New(Args&&... args) {
            return new (Allocate<T>()) T(std::forward<Args>(args)...);
        }

        /// Call destructor and free memory
        template<typename T>
        void Delete(T* obj) {
            obj->~T();
            Deallocate(obj);
        }

        /// Check if handle is set
        __always_inline bool IsValid() const {
            return m_Handle != nullptr;
        }

        /// Get handle
        __always_inline void* GetHandle() const {
            return m_Handle;
        }

        /// Get label
        __always_inline const char* GetLabel() const {
            return m_Label;
        }

        /// Get max heap size
        __always_inline size_t GetMaxSize() const {
            return m_Size;
        }

        /// Get used byte count
        __always_inline size_t GetUsedBytes() const {
            return m_UsedBytes;
        }

        /// Get unused byte count
        __always_inline size_t GetFreeBytes() const {
            return GetMaxSize() - GetUsedBytes();
        }

        /// Get alloc call count
        __always_inline uint64_t GetAllocCount() const {
            return m_AllocCount;
        }

        /// Get free call count
        __always_inline uint64_t GetFreeCount() const {
            return m_FreeCount;
        }

        /// Get allocated - free difference
        __always_inline uint64_t GetDelta() const {
            return GetAllocCount() - GetFreeCount();
        }

    private:
        const char* m_Label;
        void* m_Handle;        // Handle for dlmalloc mspace
        size_t m_Size;         // Max size of this heap
        size_t m_UsedBytes;    // Allocated byte count
        size_t m_MaxUsedBytes; // Max allocated byte count
        uint64_t m_AllocCount; // Allocation count
        uint64_t m_FreeCount;  // Free count

#ifdef CFXS_HEAP_CHECK_LOCK
        bool m_Locked = false;
#endif
    };

} // namespace CFXS