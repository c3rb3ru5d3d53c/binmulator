#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <stdint.h>

#ifndef WINDOWS_EMULATOR_H
#define WINDOWS_EMULATOR_H

class WindowsEmulator{
    public:
        struct {
            void *uc;
        } options;
};

#endif
