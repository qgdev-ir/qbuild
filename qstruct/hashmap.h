#ifndef _qstruct_hashmap_h_
#define _qstruct_hashmap_h_
#ifdef __cplusplus
extern "C" {
#endif

#define QSTRUCT_HASHMAP_DEFAULT_CAPACITY	16
#define QSTRUCT_HASHMAP_DEFAULT_MAX_LOADFACTOR	0.5

/*
 * A pointer to actual hashmap
 */
typedef void* qstruct_hashmap_t;

/*
 * Hash the given buffer
 */
typedef long (*qstruct_hashmap_hasher_t)(char *x, size_t size, long seed);

#ifdef __cplusplus
}
#endif
#endif
