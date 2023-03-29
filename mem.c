#include "mem.h"

#if MEM_DEBUG == 0
    #include <stdio.h>
    #define LOG(...) printf(__VA_ARGS__)
#else
    #define LOG(...)
#endif

#define MAXIMUM_ALLOCATION 1024

struct {
    size_t capacity;
    void* ptr;
    size_t ptr_sizes[MAXIMUM_ALLOCATION];
    size_t valid_ptr_count;
} MEM = {0};

/** ****************
 * Helper Functions 
 * *****************/

size_t _mem_real_usage()
{
    size_t result = 0;
    for(size_t i = 0; i < MEM.valid_ptr_count; ++i)
        result += MEM.ptr_sizes[i] + 1;
    return result;
}

size_t _mem_real_ptr_size(void* ptr)
{
    /**
     * The real size of a pointer is n + 1 where n is the size that user request
     * The n + 1 byte will be set as 0 to make sure if the memory used for 
     * string operations the operation will only use n size memory. Also if the n + 1
     * byte is not 0 it will become an invalid pointer
     */
    return mem_ptr_size(ptr) + 1;
}

size_t mem_ptr_size(void* ptr)
{
    if(!(MEM.ptr <= ptr && ptr <= MEM.ptr + MEM.capacity)) 
        return 0;
    void* ptr2 = MEM.ptr;
    for(size_t i = 0; i < MEM.valid_ptr_count; ++i) {
        if(ptr2 == ptr)
            return MEM.ptr_sizes[i];
        ptr2 += MEM.ptr_sizes[i] + 1;
    }
    return 0;
}

size_t mem_used(void) 
{
    size_t result = 0;
    for(size_t i = 0; i < MEM.valid_ptr_count; ++i)
        result += MEM.ptr_sizes[i];
    return result;
}

void mem_status(void)
{
#if MEM_DEBUG == 0
    LOG("Capacity: %zu\n", MEM.capacity);
    LOG("Used: %zu\n", mem_used());
    LOG("Items:\n");
    void* ptr = MEM.ptr;
    for(size_t i = 0; i < MEM.valid_ptr_count; ++i) {
        size_t sz = _mem_real_ptr_size(ptr);
        LOG("  [%zu] start: %p | size: %zu\n", i, ptr, sz - 1);
        ptr += sz;
    }
#endif
}

/** Core Allocation Functions */

void mem_init(void* ptr, size_t size)
{
    MEM.capacity = size;
    MEM.ptr = ptr;
    MEM.valid_ptr_count = 0;
    for(size_t i = 0; i < MAXIMUM_ALLOCATION; ++i)
        MEM.ptr_sizes[i] = 0;
}

void* mem_alloc(size_t size)
{
    if(size == 0)
        return NULL;
    if(_mem_real_usage() + size > MEM.capacity) {
        return NULL;
    }
    char* result = MEM.ptr + _mem_real_usage();
    MEM.ptr_sizes[MEM.valid_ptr_count] = size;
    ++MEM.valid_ptr_count;
    result[size] = 0;
    return result;
}

void mem_free(void* ptr)
{
    size_t sz = _mem_real_ptr_size(ptr);
    if(sz == 1)
        return; // TODO: error Invalid pointer to be freed
    char* cptr = (char*) ptr;
    if(cptr[sz] != 0)
        return; // TODO: error Invalid pointer to be freed
    cptr[sz] = 0;
}