#ifndef MEM_H_
#define MEM_H_

#define MEM_DEBUG 0 // MEM_DEBUG == 0 is debug mode, otherwise It will release mode

#include <stddef.h>
#include <stdbool.h>

/**
 * @name mem_init
 * 
 * @param ptr the memory block's pointer
 * @param size the size of the memory block
 */
void  mem_init(void* ptr, size_t size);

/**
 * @name mem_alloc
 * This function will return a valid pointer of memory.
 * A valid pointer should be in range of the block pointer and the
 * capacity of the block.
 * @param size the size of memory that will be allocated
 * @returns the pointer of the memory allocated or NULL on failed
 */
void* mem_alloc(size_t size);

/**
 * @name mem_free
 * This function will free a valid pointer
 * @param ptr the pointer that will be freed
 * @returns the pointer of the memory allocated or NULL on failed
 */
void  mem_free(void* ptr);

/**
 * @name mem_ptr_size
 * 
 * @param ptr the pointer that will be tracked
 * @returns the size of pointer or 0 if it's an invalid pointer
 * This function is used to get the size of a certain pointer 
 */
size_t mem_ptr_size(void* ptr);

size_t mem_used(void);
void mem_status(void);


#endif