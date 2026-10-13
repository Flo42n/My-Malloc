#include <stddef.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/mman.h>
#include <string.h>
#include <errno.h>

#include "malloc.h"

// allouer le meilleur block

struct global_variable{  
    struct header* head; // le pointeur vers le premier bloc de mémoire
    struct header* tail; // le pointeur vers le dernier bloc de mémoire
};

static struct global_variable gv={NULL,NULL};



/* aligne la taille de mémoire allouée avec avec la taille d'un long double */
static size_t align(size_t size)
{
    return (size+sizeof(long double)-1) & ~(sizeof(long double)-1);
}



/* renvoie la block libre dont la taille se rapproche le plus de la taille du block à allouer */
static struct header* best_fit_free(size_t size)
{
    struct header* closest=NULL;
    size_t dif=SIZE_MAX;
    struct header* current=gv.head;
    while(current!=NULL)
    {

            if( current->free == 0 && current->size>=size && current->size-size<dif)
            {
                closest=current;
                dif=current->size-size;
                if (dif == 0)           return closest;
            }
       current = current->next;
    }
    return closest;
}

/* crée ou rajoute un nouveau bloc de mémoire à head */
static struct header* new_block(size_t size)   
{
    void* block=mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (block == MAP_FAILED) {
        return NULL;
    }
    struct header* new_header=block;
    new_header->size=size-sizeof(struct header);
    new_header->prev=NULL;
    new_header->next=NULL;
    new_header->free=0;
    if (gv.head==NULL)
    {
        gv.head=new_header;
        gv.tail=new_header;
    }
    else
    {
        new_header->prev=gv.tail;
        gv.tail->next=new_header;
        gv.tail=new_header;
    }
    return new_header;
}


/* fusionne le bloc header avec le bloque suivant si libre */
static struct header* merge_block(struct header* header) 
{
    if (header==NULL || header->next==NULL) 
    {
        return NULL;
    }
    void* temp=((char*)(header + 1) + header->size);
    struct header* next_one=temp;
    if (next_one != header->next) return header;
    if (header->next==NULL || header->next->free==1) 
    {
        return header;
    }
    struct header* next=header->next;
    if (next->free==0)
    {
        header->size+=sizeof(struct header)+next->size;
        header->next=next->next;
        if (header->next != NULL)  header->next->prev = header;
        if (next==gv.tail) gv.tail=header;
    }
    return header;
}




/* découpe un bloc de mémoire en 2 et renvoie le nouveau block */
static struct header* split_block(struct header* header,size_t size)
{
    if (size>=header->size)
    {
        return header;
    }
    void* temp=((char*)(header+1)+size);
    struct header* new_block=temp;
    new_block->size=header->size-sizeof(struct header)-size;
    new_block->free=0;
    new_block->prev=header;
    if(header==gv.tail) gv.tail=new_block;
    new_block->next=header->next;
    if (new_block->next != NULL) new_block->next->prev = new_block;
    header->next=new_block;
    header->size=size;
    if (new_block!=gv.tail && new_block->next->free==0) new_block=merge_block(new_block);
    return new_block;
}




/* alloue un bloc de mémoire comme malloc */
void* malloc(size_t s)  
{    
    if (s==0) s=16;
    size_t size=align(s);
    struct header* best_fit=best_fit_free(size);
    if (gv.head==NULL || best_fit==NULL) 
    {
        long size_new_block=sysconf(_SC_PAGESIZE);
        size_t s_final=size_new_block;   
        while (s_final<size+sizeof(struct header))
        {
            s_final+=size_new_block;
        }                
        struct header* h=new_block(s_final);
        if (h==NULL) 
        {
            return NULL;
        }
        return malloc(s);
    }
    best_fit->free=1;
    if (best_fit->size>=size+sizeof(struct header)+sizeof(long double))
    {
        best_fit->next=split_block(best_fit, size);
        if (best_fit==gv.tail) gv.tail=best_fit->next;
    } 
    return best_fit+1;

}



/* libère un bloc de mémoire comme free */
void free(void* ptr)   
{
    if (ptr==NULL) return;
    struct header* header=(struct header *)ptr - 1;
    header->free=0;
    if (header != gv.head && header->prev->free==0) header=merge_block(header->prev);
    if (header!=gv.tail && header->next->free==0) header=merge_block(header);
}



/* alloue un bloc de mémoire comme calloc */
void* calloc(size_t number, size_t size)  
{
    size_t total_size;
    if (__builtin_mul_overflow(number, size, &total_size)) 
    {
      //  errno = ENOMEM;
        return NULL;    
    }
    void* ptr=malloc(total_size);
    if (ptr==NULL)
    {
        return NULL;
    } 
    memset(ptr,0,total_size);
    return ptr;
}



/* realloue un bloc de mémoire comme realloc */
void* realloc(void* ptr, size_t s)   
{
    if (ptr==NULL) return malloc(s);
    if (s==0) 
    {
        free(ptr);
        return NULL;
    }
    size_t size=align(s);
    struct header* header=(struct header *)ptr - 1;
    if (header->size==size) return ptr;
    else if (header->size>size)
    {
        if (header->size>size+sizeof(struct header)+sizeof(long double)) 
        {
            split_block(header,size);
        }
        return ptr;
    }
    else // necécessaire de déplacer le bloc mémoire et ses éléments
    {
        if (header!=gv.tail && header->next->free==0 && header->next->size+header->size+sizeof(struct header)>=size )
        {
            merge_block(header);
        }
        if (header->size < size)
        {
            void* res=malloc(size);
            if (res==NULL) return NULL;
            memcpy(res,ptr,header->size);
            free(ptr);
            return res;
        }
    }
    return (header+1);
}
