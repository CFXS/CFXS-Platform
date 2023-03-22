/////////////////////////////////////////////////////////////////////////////////
// Copyright (c) Electronic Arts Inc. All rights reserved.
/////////////////////////////////////////////////////////////////////////////////


#ifndef EASTL_ATOMIC_INTERNAL_COMPILER_THREAD_FENCE_H
#define EASTL_ATOMIC_INTERNAL_COMPILER_THREAD_FENCE_H

#if defined(EA_PRAGMA_ONCE_SUPPORTED)
	#pragma once
#endif


/////////////////////////////////////////////////////////////////////////////////
//
// void EASTL_COMPILER_ATOMIC_THREAD_FENCE_*()
//
#if defined(EASTL_COMPILER_ATOMIC_THREAD_FENCE_RELAXED)
	#define EASTL_COMPILER_ATOMIC_THREAD_FENCE_RELAXED_AVAILABLE 1
#else
	#define EASTL_COMPILER_ATOMIC_THREAD_FENCE_RELAXED_AVAILABLE 0
#endif

#if defined(EASTL_COMPILER_ATOMIC_THREAD_FENCE_ACQUIRE)
	#define EASTL_COMPILER_ATOMIC_THREAD_FENCE_ACQUIRE_AVAILABLE 1
#else
	#define EASTL_COMPILER_ATOMIC_THREAD_FENCE_ACQUIRE_AVAILABLE 0
#endif

#if defined(EASTL_COMPILER_ATOMIC_THREAD_FENCE_RELEASE)
	#define EASTL_COMPILER_ATOMIC_THREAD_FENCE_RELEASE_AVAILABLE 1
#else
	#define EASTL_COMPILER_ATOMIC_THREAD_FENCE_RELEASE_AVAILABLE 0
#endif

#if defined(EASTL_COMPILER_ATOMIC_THREAD_FENCE_ACQ_REL)
	#define EASTL_COMPILER_ATOMIC_THREAD_FENCE_ACQ_REL_AVAILABLE 1
#else
	#define EASTL_COMPILER_ATOMIC_THREAD_FENCE_ACQ_REL_AVAILABLE 0
#endif

#if defined(EASTL_COMPILER_ATOMIC_THREAD_FENCE_SEQ_CST)
	#define EASTL_COMPILER_ATOMIC_THREAD_FENCE_SEQ_CST_AVAILABLE 1
#else
	#define EASTL_COMPILER_ATOMIC_THREAD_FENCE_SEQ_CST_AVAILABLE 0
#endif


#endif /* EASTL_ATOMIC_INTERNAL_COMPILER_THREAD_FENCE_H */
