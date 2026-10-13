#include "../src/malloc.h"
#include <assert.h>

static size_t align(size_t size)
{
    return (size+sizeof(long double)-1) & ~(sizeof(long double)-1);
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
    assert(ptr4!=ptr);

    int* ptr5=malloc(38);
    int* ptr6=realloc(ptr5,38);
    assert(ptr6!=NULL);
    assert(ptr6==ptr5);   
    
    long* ptr7=realloc(NULL,65);
    assert(ptr7!=NULL);

    struct header* h=(struct header*)(ptr7)-1;
    assert(h->size==align(65));

    int* ptr8=malloc(10000);
    assert(ptr8!=NULL);

    char* ptr9=malloc(4097);
    assert(ptr9!=NULL);

    unsigned int* ptr10=calloc(0,5);
    assert(ptr10!=NULL);

    unsigned int* ptr11=calloc(50,0);
    assert(ptr11!=NULL);  
    
    unsigned int* ptr12=calloc(50,100);
    assert(ptr12!=NULL); 
    struct header* h1=(struct header*)(ptr12)-1;
    assert(h1->size==align(50*100));

    int* ptr13=calloc(67,1);
    assert(ptr13!=NULL);
    struct header* h2=(struct header*)(ptr13)-1; 
    assert(h2->free==1);
    int* p=realloc(ptr13,0);
  //  struct header* h2bis=(struct header*)(p)-1;
  //  assert(h2bis->free==0);

    free(NULL);
    free(ptr2);
    free(ptr3);
    free(ptr6);
    free(ptr7);
    free(ptr8);
    free(ptr10);
    free(ptr11);
    free(ptr12);
    free(p);


    int* ptr14=malloc(670);
    assert(ptr14!=NULL); 
    int* ptr15=realloc(ptr14,10);
    struct header* h3=(struct header*)(ptr15)-1;
    assert(h3->size==align(10));
    assert(ptr14==ptr15);

    int* ptr13bis=malloc(670);
    assert(ptr13bis!=NULL);


    int* ptr16=malloc(67);
    int* ptr16bis=malloc(10);
    assert(ptr16!=NULL); 
    free(ptr13bis);
    int* ptr17=realloc(ptr16,670);
    struct header* h4=(struct header*)(ptr17)-1;
    assert(h4->size==align(670));
    assert(ptr16!=ptr17);


    size_t* ptr18=malloc(67);
    size_t* temp18=ptr18;
    size_t t18=*ptr18;
    assert(ptr18!=NULL); 
    size_t* ptr19=realloc(ptr18,70);
    struct header* h5=(struct header*)(ptr19)-1;
    assert(h5->size==align(67));
    assert(temp18==ptr19);
    assert(t18==*ptr19);

    size_t* ptr20=malloc(50);
    size_t temp20=*ptr20;
    size_t* ptr22=malloc(100);
    assert(ptr22!=NULL);
    *ptr20=15;
    assert(ptr20!=NULL); 
    size_t* ptr21=realloc(ptr20,500);
    struct header* h6=(struct header*)(ptr21)-1;
    assert(h6->size==align(500));
    assert(*ptr21==15);
    assert(*ptr21==temp20);

    free(ptr9);
    free(ptr4);
    free(ptr15);
    free(ptr17);
    free(ptr19);
    free(ptr21);
    free(ptr16bis);
}

