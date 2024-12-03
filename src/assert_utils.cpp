#include "assert_utils.h"

#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <cstdio>
#include <cstdlib>

void assert_failed(const char* condition, const char* function, const char* file, int line) {
    char message[512];

    snprintf(message, sizeof(message),
             "Assertion failed: %s\nFunction: %s\nFile: %s\nLine: %d",
             condition, function, file, line);

    MessageBoxA(NULL, message, "Assertion Failed", MB_OK | MB_ICONERROR);
    __debugbreak();
} 