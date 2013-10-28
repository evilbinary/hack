/*
 * =====================================================================================
 *
 *       Filename:  test.c
 *
 *    Description:  hook test
 *
 *        Version:  1.0
 *        Created:  2013年10月28日 09时16分34秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  小E (), rootntsd@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
//#include <stdlib.h>
#include <stdio.h> 
#include <dlfcn.h> 

# define RTLD_NEXT      ((void *) -1l)
#define EQ_CAT(A, B) EQ_CAT2(A, B)
#define EQ_CAT2(A, B) A##B

#define EQ_FORWARD(name, ...) \
  static void* original = 0; \
  if (original == 0) \
    original = dlsym(RTLD_NEXT, #name); \
  return EQ_CAT(eq_,name)(original, __VA_ARGS__); \



void* malloc(size_t sz)
{
    void *(*libc_malloc)(size_t) =NULL;
    if(libc_malloc==NULL){
        libc_malloc=dlsym(RTLD_NEXT, "malloc");
    }
    printf("malloc\n");
    return libc_malloc(sz);
}

void free(void *p)
{
    void (*libc_free)(void*)=NULL;
    if(libc_free==NULL){
        libc_free= dlsym(RTLD_NEXT, "free");
    }
    printf("free\n");
    return libc_free(p);
}
void* temporary_calloc(size_t nmemb, size_t size)
{
    printf("empty calloc called\n");
    return NULL;
}
void *calloc(size_t nmemb, size_t size){
    static void *(*libc_calloc)(size_t,size_t)=NULL;
    if(!libc_calloc){
        libc_calloc=temporary_calloc;
        libc_calloc= dlsym(RTLD_NEXT, "calloc");
    }
    printf("%s\n",__FUNCTION__);
    return libc_calloc(nmemb,size);
}
void *realloc(void *ptr, size_t size){
    static void *(*libc_realloc)(void *, size_t)=NULL;
    if(libc_realloc==NULL){
        libc_realloc= dlsym(RTLD_NEXT, "realloc");
    }
    printf("%s\n",__FUNCTION__);
    return libc_realloc(ptr,size);
}

/*void* malloc (size_t size)
{
	void * addr=NULL;
    void *(*fptr)(size_t);
    printf("%s\n",__FUNCTION__);
    fptr=dlsym(RTLD_NEXT,"malloc");
    if(fptr!=NULL)
        addr=(*fptr)(size);
	printf("malloc:%p %ld\n",addr,size);
	return addr;
}
void free(void *ptr){
    void * addr=NULL;
    void (*fptr)(void *);
    printf("%s\n",__FUNCTION__);
    fptr=dlsym(RTLD_NEXT,"free");
    if(fptr!=NULL)
        (*fptr)(ptr);
    //printf("free:%p\n",(int*)ptr);
}
void *calloc(size_t nmemb, size_t size){
    char* error=NULL;
    void * addr=NULL;
    void *(*fptr)(size_t nmemb, size_t size);
    printf("%s\n",__FUNCTION__);
    fptr=dlsym(RTLD_NEXT,"calloc");
    if((error=dlerror())!=NULL){

        printf("error:%s\n",error);
        exit(1);
    }
    if(fptr!=NULL)
        addr=(*fptr)(nmemb,size);
    printf("calloc:%p\n",addr);
    return addr;
}
void *realloc(void *ptr, size_t size){
    char* error=NULL;
    void * addr=NULL;
    void *(*fptr)(void *ptr, size_t size);
    printf("%s\n",__FUNCTION__);
    fptr=dlsym(RTLD_NEXT,"realloc");
    if((error=dlerror())!=NULL){

        printf("error:%s\n",error);
        exit(1);
    }
    if(fptr!=NULL)
        addr=(*fptr)(ptr,size);
    printf("realloc:%p\n",addr);
    return addr;
}
*/

