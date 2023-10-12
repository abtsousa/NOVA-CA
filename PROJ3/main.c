#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#define BLOCK_SIZE sizeof(struct s_block)

typedef struct s_block *t_block;

struct s_block {
    unsigned long long size;  // current size of block
    t_block next; // pointer to next block
    unsigned long long  free;     // flag indicating that the block is free (1) or occupied  (0).
};

t_block head = NULL; // points to the beginning of the list
t_block tail = NULL; // points to the last element of the list

void *myMalloc(size_t size);

void myFree(void *ptr);

t_block extend_heap(size_t s) {
    t_block b = sbrk(BLOCK_SIZE+s); //b é o bloco de metadados; BLOCK_SIZE o tamanho dos metadados e s o tamanho do bloco de dados
    if (b == (void *)-1)
        return NULL; /* if sbrk fails, return NULL pointer*/

    b->size = s; //equivalente a (*b).size
    b->next = NULL;
    b->free = 1;
    if (head==NULL) head = b;
    else tail->next = b;
    tail = b;
    return b;   // with metadata
}

void debugBlockList() {
    t_block p = head;
    printf("current block list:\n");
	while (p!=NULL){
		printf("address: %llu - %llu bytes (%s)\n",
			(unsigned long long)(p), p->size, p->free?"free":"in use");
		p = p->next;
	}
}

/**
 * teste myMalloc/myFree
 **/
int main(int argc, char *argv[]) {
    unsigned int maxSpace;

    if (argc != 2) {
        printf("%s max_memory_to_allocate\n", argv[0]);
        exit(1);
    }
    maxSpace = atoi(argv[1]);
//
    //printf("Current program break = %lu\n", (unsigned long)sbrk(0));

    for (int s = 1; s < maxSpace; s *= 2) {
        void *ptr = myMalloc(s);
        if (ptr == NULL)
            printf("No more mem\n");
        //else
        //    printf("returned pointer = %lu\n", (unsigned long)ptr);
        myFree(ptr);
    }
    debugBlockList();
    // getting the current break value
    // printf("Current program break = %lu\n", (unsigned long)sbrk(0));
    for (int s = maxSpace; s>0; s /= 2) {
        void *ptr = myMalloc(s);
        if (ptr == NULL)
            printf("No more mem\n");
        //else
        //    printf("returned pointer = %lu\n", (unsigned long)ptr);
    }
    debugBlockList();

    return 0;
}
