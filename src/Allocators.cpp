#include "Allocators.h"
#include "assert_utils.h"

#include <cstdlib>

// Non-array new operator
void* __cdecl operator new(size_t size) 
{
    void* ptr = std::malloc(size);

    BE_ASSERT(ptr);

    return ptr;
}

void __cdecl operator delete(void* ptr) noexcept 
{
    free(ptr);
}

void* __cdecl operator new[](size_t size) 
{
    void* ptr = std::malloc(size);

    BE_ASSERT(ptr);

    return ptr;
}

void __cdecl operator delete[](void* ptr) noexcept 
{
    free(ptr);
}

void* operator new[](unsigned __int64 size, unsigned __int64 param1, unsigned __int64 param2, 
                     const char* filename, int line, unsigned int flags, 
                     const char* functionName, int param3) 
{
    void* ptr = malloc(size);

    BE_ASSERT(ptr);

    return ptr;
}


void* __cdecl operator new[](unsigned __int64 size, char const* filename, int line, 
                             unsigned int flags, char const* functionName, int param)
{
    void* ptr = malloc(size);

    BE_ASSERT(ptr);

    return ptr;
}