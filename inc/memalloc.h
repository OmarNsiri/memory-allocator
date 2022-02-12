#ifndef MEM_ALLOC
#define MEM_ALLOC

#include <pthread.h>

#ifdef __cplusplus
extern "C"{
#endif 

/* typedef char ALIGN[16];

union header
{
    struct {
	    size_t size;
	    unsigned is_free;
        struct header_t* next;
    } s;
    ALIGN stub;
};
typedef union header header_t; */

struct header
{
	size_t size;
	unsigned is_free;
    struct header* next;
};
typedef struct header header_t;
extern header_t *head, *tail;


pthread_mutex_t global_malloc_mutex;



void* allocate_memory(size_t);
void free_memory(void*);
header_t *get_free_block(size_t size);

#endif

#ifdef __cplusplus
}
#endif