#ifndef MY_MALLOC_H
#define MY_MALLOC_H

#include <stddef.h>

struct header {
    size_t size;  // taille du block mémoire 
    int free;   // 0 si libre, 1 sinon
    struct header* next;
    struct header* prev;
} __attribute__((aligned(16)));



__attribute__((visibility("default"))) void *malloc(size_t size);
__attribute__((visibility("default"))) void free(void *ptr);
__attribute__((visibility("default"))) void *calloc(size_t number, size_t size);
__attribute__((visibility("default"))) void *realloc(void *ptr, size_t size);


#endif /* MY_MALLOC_H */
