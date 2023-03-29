#include <stdio.h>
#include <mem.h>

#define HEAP_SIZE 64000
char HEAP[HEAP_SIZE] = {0};

int main(int argc, char** argv)
{
    mem_init((void*)HEAP, HEAP_SIZE);
    char* abc = mem_alloc(26);
    for(int i = 0; i < 26; ++i) {
        abc[i] = 'A' + i;
    }

    char* zyx = mem_alloc(26);
    for(int i = 25; i >= 0; --i) {
        zyx[i] = 'Z' - i;
    }
    zyx[26] = 0;

    printf("sizeof %p: %zu\n",zyx,  mem_ptr_size(zyx));

    mem_status();
    return 0;
}