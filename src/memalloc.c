#include <unistd.h>
#include <string.h>

#include "memalloc.h"

header_t *head = NULL, *tail = NULL;

void* allocate_memory(size_t size)
{
	void* block;		/* Allocated memory block */
	header_t* header;	/* Header part of allocated memory */
	size_t total_size;	/* Total size of allocated block = header size + requested size */

	/* If requested to allocate a 0 sized memory space return a NULL pointer */
	if(!size)
		return NULL;

	pthread_mutex_lock(&global_malloc_mutex);
	/* Try to create a memory space from already freed blocks */
	header = get_free_block(size);
	if(header)
	{
		header->is_free = 0;
		pthread_mutex_unlock(&global_malloc_mutex);
		return (header + 1);
	}

	/* Allocation from free blocks was not possible.
	   Create a new block at the tail of the heap (program break) */
	total_size = sizeof(header_t) + size;
	block = sbrk(total_size);
	if (block == (void*) -1)
	{
		pthread_mutex_unlock(&global_malloc_mutex);
		return NULL;
	}

	/* Prepare header for the newly created memory block */
	header = block;
	header->is_free = 0;
	header->size = size;
	header->next = NULL;

	if (!head)
	{
		/* This is executed once for creating the first memory block in heap */
		head = header;
		tail = head;
	}
	else
	{
		/* update the linked list */
		tail->next = header;
		tail = header;
	}

	pthread_mutex_unlock(&global_malloc_mutex);
	return (header + 1);
}

void free_memory(void* block)
{
	header_t* header, *tmp;
	void *programbreak = sbrk(0);
	if (!block)
		return NULL;

	pthread_mutex_lock(&global_malloc_mutex);
	header = (header_t*)block - 1;

	/* if the memory to free is at the tail of the heap */
	if (programbreak == (char*)block + header->size)
	{
		/* if about to free the only memory block */
		if (head == tail)
			tail = head = NULL;
		/* search for the block just before the tail */
		else
		{
			while (tmp)
			{
				if(tmp->next == tail)
				{
					tmp->next = NULL;
					tail = tmp;
				}
				tmp = tmp->next;
			}
			/* release memory to the OS */
			sbrk(0 - sizeof(header_t) - header->size);
			pthread_mutex_unlock(&global_malloc_mutex);
			return;
		}
	}

	/* the memory block is at the middle of the memory linked list */
	header->is_free = 1;
	pthread_mutex_unlock(&global_malloc_mutex);

}

header_t* get_free_block(size_t size)
{
	header_t* curr = head;

	/* Iterate over free memory headers */ 
	while(curr != NULL)
	{
		/*  Check if the current memory block can fit the requested size*/
		if(curr->is_free && curr->size >= size)
			return curr;
		else curr = curr->next;
	}

	/*  Unable to find a fitting memory block */
	return NULL;
}