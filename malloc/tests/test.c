#include "../src/malloc.h"
#include <assert.h>

static size_t align(size_t size)
{
    return (size+sizeof(long double)-1) & ~(sizeof(long double)-1);
}

struct header *cast(void *header)
{
    return (struct header *)header;
}

 
int main(void)
{
    int* ptr=malloc(670);
    assert(ptr!=NULL);
 
    int* ptr2=malloc(0);
    assert(ptr2!=NULL);
 
    int* ptr3=calloc(10,sizeof(int));
    assert(ptr3!=NULL);
    for (int i=0;i<10;i++)
    {
        assert(ptr3[i]==0);      
    }
 
    int* ptr4=realloc(ptr,4096);
    assert(ptr4!=NULL);
 
 
    int* ptr5=malloc(38);
    int* ptr6=realloc(ptr5,38);
    assert(ptr6!=NULL);
    assert(ptr6==ptr5);   
    
    long* ptr7=realloc(NULL,65);
    assert(ptr7!=NULL);
    struct header *h=cast(ptr7)-1;
    assert(h->size>=align(65));
 
    int* ptr8=malloc(10000);
    assert(ptr8!=NULL);
 
    char* ptr9=malloc(4097);
    assert(ptr9!=NULL);
 
    unsigned int *ptr10=calloc(0,5);
    assert(ptr10!=NULL);
 
    unsigned int *ptr11=calloc(50,0);
    assert(ptr11!=NULL);  
    
    unsigned int *ptr12=calloc(50,100);
    assert(ptr12!=NULL); 
    struct header *h1=cast(ptr12)-1;
    assert(h1->size==align(50*100));
 
    int* ptr13=calloc(67,1);
    assert(ptr13!=NULL);
    struct header *h2=cast(ptr13)-1; 
    assert(h2->free==1);
    assert(realloc(ptr13, 0) == NULL);
 
    free(NULL);
    free(ptr2);
    free(ptr3);
    free(ptr6);
    free(ptr7);
    free(ptr8);
    free(ptr10);
    free(ptr11);
    free(ptr12);
 
    int* ptr14=malloc(670);
    assert(ptr14!=NULL); 
    int* ptr15=realloc(ptr14,10);
    struct header *h3=cast(ptr15)-1;
    assert(h3->size==align(10));
    assert(ptr14==ptr15);
 
    int* ptr13bis=malloc(670);
    assert(ptr13bis!=NULL);
 
 
    int* ptr16=malloc(67);
    int* ptr16bis=malloc(10);
    assert(ptr16!=NULL); 
    free(ptr13bis);
    int* ptr17=realloc(ptr16,670);
    struct header *h4=cast(ptr17)-1;
    assert(h4->size==align(670));
    assert(ptr16!=ptr17);
 
 
    size_t *ptr18=malloc(67);
    *ptr18=6767;
    size_t t18=*ptr18;
    assert(ptr18!=NULL); 
    size_t *ptr19=realloc(ptr18,70);
    struct header *h5=cast(ptr19)-1;
    assert(h5->size==align(67));
    assert(t18==*ptr19);
 
    size_t *ptr20=malloc(50);
    size_t *ptr22=malloc(100);
    assert(ptr22!=NULL);
    *ptr20=15;
    assert(ptr20!=NULL); 
    size_t *ptr21=realloc(ptr20,500);
    struct header *h6=cast(ptr21)-1;
    assert(h6->size==align(500));
    assert(*ptr21==15);
 
    free(ptr9);
    free(ptr4);
    free(ptr15);
    free(ptr17);
    free(ptr19);
    free(ptr21);
    free(ptr16bis);
 
    char* ptr23=malloc(1);
    assert(ptr23!=NULL);
    assert((size_t)ptr23%sizeof(long double)==0);
    char* ptr23bis=malloc(33);
    assert(ptr23bis!=NULL);
    assert((size_t)ptr23bis%sizeof(long double)==0);
 

    char* ptr24=malloc(300);
    char* ptr25=malloc(300);
    assert(ptr24!=NULL);
    assert(ptr25!=NULL);
    for (int i=0;i<300;i++)
    {
        ptr24[i]='a';
        ptr25[i]='b';
    }
    for (int i=0;i<300;i++)
    {
        assert(ptr24[i]=='a');
        assert(ptr25[i]=='b');
    }
 

    char* ptr26=malloc(100);
    assert(ptr26!=NULL);
    free(ptr26);
    char* ptr27=malloc(100);
    assert(ptr27==ptr26);
 

    char* ptr28=malloc(200);
    assert(ptr28!=NULL);
    for (int i=0;i<200;i++)
    {
        ptr28[i]=1;
    }
    free(ptr28);
    char* ptr29=calloc(25,8);
    assert(ptr29!=NULL);
    for (int i=0;i<200;i++)
    {
        assert(ptr29[i]==0);
    }
 

    char* ptr30=malloc(100);
    assert(ptr30!=NULL);
    for (int i=0;i<100;i++)
    {
        ptr30[i]=i;
    }
    char* ptr31=realloc(ptr30,20000);
    assert(ptr31!=NULL);
    for (int i=0;i<100;i++)
    {
        assert(ptr31[i]==i);
    }
    ptr31[19999]='z';
    assert(ptr31[19999]=='z');
 
    free(ptr22);
    free(ptr23);
    free(ptr23bis);
    free(ptr24);
    free(ptr25);
    free(ptr27);
    free(ptr29);
    free(ptr31);
}
