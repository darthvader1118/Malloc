#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "myMalloc.h"

#define MESIZE sizeof(struct memEntry)
#define BLOCKSIZE (1024*1024)

static char big_block[BLOCKSIZE];

void* myMalloc(unsigned int size, char *filename, unsigned int lnumber){
	static int initialized = 0;
	static memEntry *root;
	memEntry *p, *succ;

	if(!initialized){
		root = (memEntry*) big_block;
		root->prev = root->succ = 0;
		root->size = BLOCKSIZE - MESIZE;
		root->isFree = 1; 
		initialized = 1;
	}

	p=root;

	do{
		if(p->size < size) //the block is too small
			p = p->succ;
		else if(!p->isFree) // is the block allocated?
			p=p->succ;
		else if(p->size < (size + MESIZE)){ // is it too small to chop up?
			p->isFree = 0;
			printf("malloced space at line %d in file %s\n",lnumber,filename);
			return (char*) p + MESIZE; //room for more!
		}
		else{
			succ = (memEntry*)((char*) p + MESIZE + size);
			succ->succ = p->succ;
			if(p->succ != 0)
				p->succ->prev = succ;
			p->succ = succ;
			succ->size = p->size - MESIZE - size;
			succ->isFree = 1;
			p->size = size;
			puts("looking for a new spot");
		}
		

	} while(p!=0);
	printf("cannot malloc space at line %d in file %s\n",lnumber,filename);
	return 0;
}

void myFree(void *p, char *filename,unsigned int lnum){
	memEntry *ptr, * pred, *succ;
	ptr = (memEntry*) ((char*)p - MESIZE);
	if(p == 0){
		puts("No object found in heap");
	}
	if(((pred = ptr->prev) != 0) && pred->isFree){
		pred->size += MESIZE + ptr->size;
		pred->succ = ptr->succ;
		if(ptr->succ != 0)
			ptr->succ->prev = pred;
	} else {
		printf("freed successfully\n");
		ptr->isFree =1;
		pred = ptr;
		fragRed(ptr);
	}
	if(((succ=ptr->succ) != 0) && succ->isFree){
		pred->size += MESIZE;
		pred->succ = succ->succ;
		if(succ->succ != 0)
			succ->succ->prev = pred;
	}
}

void myFree2(void *p){
	memEntry *ptr, * pred, *succ;
	ptr = (memEntry*) ((char*)p - MESIZE);
	if(p == 0){
		//puts("No object found in heap");
	}
	if(((pred = ptr->prev) != 0) && pred->isFree){
		pred->size += MESIZE + ptr->size;
		pred->succ = ptr->succ;
		if(ptr->succ != 0)
			ptr->succ->prev = pred;
	} else {
		//printf("freed successfully\n");
		ptr->isFree =1;
		pred = ptr;
	}
	if(((succ=ptr->succ) != 0) && succ->isFree){
		pred->size += MESIZE;
		pred->succ = succ->succ;
		if(succ->succ != 0)
			succ->succ->prev = pred;
	}
}

void* myCalloc(int n, unsigned int size, char *file, unsigned int line){
	void *p = myMalloc(size*n, file, line);
	p = memset(p,0,n*size);
	return p;

}


void fragRed(memEntry *p) {
	memEntry *t;
	if (p && p->succ && p->succ->isFree) { /* If block to the right is free, merge with it! */
		p->size += p->succ->size;
		t = p->succ;
		p->succ = p->succ->succ;
		myFree2(t); /* Clean up by destroying the node out of work */
		fragRed(p->succ);
	}
	if (p && p->prev && p->prev->isFree) { /* If adjacent blocks are free, merge them! */
		p->prev->size += p->size;
		p->prev->succ = p->succ;
		t = p->prev;
		myFree2(p); /* Clean up by destroying the node out of work */
		fragRed(t);
	}
}




void LeakDetect(){
	memEntry *p = (memEntry *) big_block;
	//memEntry *ptr, *pre, *succ;
	while(p!=NULL){
		if(!p->isFree){
			puts("memory leak found");
			return;
		}
		p = p->succ;
	}
	puts("no memory leakage found");
	return;

}
