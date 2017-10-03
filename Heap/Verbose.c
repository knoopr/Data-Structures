#include <stdio.h>
#include <stdbool.h>
#include <stdarg.h>
#include "Verbose.h"

bool Verbose = false;

int Set_Verbose(bool setting){
    Verbose = setting;
}

void Verbose_Print(const char * restrict format, ...){
    if( !Verbose )
        return;

    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
}