/* gcc keeps its own copies hidden inside libgcc, so a glibc object opened
   at run time has no way to reach them */

#include <stdint.h>

#define MODELS(M, size, type)                                                  \
	M(size, type, relax, __ATOMIC_RELAXED)                                 \
	M(size, type, acq, __ATOMIC_ACQUIRE)                                   \
	M(size, type, rel, __ATOMIC_RELEASE)                                   \
	M(size, type, acq_rel, __ATOMIC_ACQ_REL)                               \
	M(size, type, sync, __ATOMIC_SEQ_CST)

#define CAS_MODELS(size, type)                                                 \
	CAS(size, type, relax, __ATOMIC_RELAXED, __ATOMIC_RELAXED)             \
	CAS(size, type, acq, __ATOMIC_ACQUIRE, __ATOMIC_ACQUIRE)               \
	CAS(size, type, rel, __ATOMIC_RELEASE, __ATOMIC_RELAXED)               \
	CAS(size, type, acq_rel, __ATOMIC_ACQ_REL, __ATOMIC_ACQUIRE)           \
	CAS(size, type, sync, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST)

#define CAS(size, type, model, mo, fmo)                                        \
	type __aarch64_cas##size##_##model(type cmp, type new, type *ptr)      \
	{                                                                      \
		__atomic_compare_exchange_n(ptr, &cmp, new, 0, mo, fmo);       \
		return cmp;                                                    \
	}

#define SWP(size, type, model, mo)                                             \
	type __aarch64_swp##size##_##model(type val, type *ptr)                \
	{                                                                      \
		return __atomic_exchange_n(ptr, val, mo);                      \
	}

#define LDADD(size, type, model, mo)                                           \
	type __aarch64_ldadd##size##_##model(type val, type *ptr)              \
	{                                                                      \
		return __atomic_fetch_add(ptr, val, mo);                       \
	}

#define LDCLR(size, type, model, mo)                                           \
	type __aarch64_ldclr##size##_##model(type val, type *ptr)              \
	{                                                                      \
		return __atomic_fetch_and(ptr, ~val, mo);                      \
	}

#define LDEOR(size, type, model, mo)                                           \
	type __aarch64_ldeor##size##_##model(type val, type *ptr)              \
	{                                                                      \
		return __atomic_fetch_xor(ptr, val, mo);                       \
	}

#define LDSET(size, type, model, mo)                                           \
	type __aarch64_ldset##size##_##model(type val, type *ptr)              \
	{                                                                      \
		return __atomic_fetch_or(ptr, val, mo);                        \
	}

#define SIZES(M)                                                               \
	MODELS(M, 1, uint8_t)                                                  \
	MODELS(M, 2, uint16_t)                                                 \
	MODELS(M, 4, uint32_t)                                                 \
	MODELS(M, 8, uint64_t)

SIZES(SWP)
SIZES(LDADD)
SIZES(LDCLR)
SIZES(LDEOR)
SIZES(LDSET)

CAS_MODELS(1, uint8_t)
CAS_MODELS(2, uint16_t)
CAS_MODELS(4, uint32_t)
CAS_MODELS(8, uint64_t)
CAS_MODELS(16, unsigned __int128)
