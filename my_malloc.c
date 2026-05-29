#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>

typedef struct block{
	size_t size;  //size to be allocated
	bool free;    //whether block is free or not
	struct block *next;	//pointer to next block
} block_t;

block_t *head = NULL;

block_t *find_free_block(size_t size){
	block_t *curr = (block_t *)head;
	while(curr){
		if(curr->free && curr->size >= size){
			return curr;
		}
		curr = curr->next;
	}
	return NULL;
}

block_t *request_free_space(size_t size){
	void *request = sbrk(sizeof(block_t)+size);
	if(request == (void *)-1){
		return NULL;
	}
	block_t *block = request;
	block->size = size;
	block->free = 0;
	block->next = NULL;
	return block;
}

void *my_malloc(size_t size){
	if(size==0) return NULL;
	block_t *block;
	if(!head){
		block = request_free_space(size);
		if(!block){
			return NULL;
		}
		head=block;
	}
	else{
		block = find_free_block(size);
		if(block){
			block->free=0;
		}
		else{
			block_t *curr = head;
			while(curr->next){
				curr=curr->next;
			}
			block = request_free_space(size);
		
			if(!block){
				return NULL;
			}
			curr->next = block;
		}
	}
	return (block+1);  //return memory after metadata header
}
void my_free(void *ptr){
	if(!ptr) return;
	block_t *curr = ((block_t *)ptr)-1;
	curr->free=1;
}
int main(){
	char *a = my_malloc(100);
	char *b = my_malloc(50);
	
	printf("a = %p\n", a);
	printf("b = %p\n", b);

	my_free(a);

	char *c = my_malloc(70);
	
	printf("c = %p\n", c);

	return 0;
}

