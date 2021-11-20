#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <stdint.h>

#ifndef WINDOWS_HOOKS_H
#define WINDOWS_HOOKS_H

#define WINDOWS_HOOKS_MAX 256

class WindowsHooks {
    private:
        struct Hook {
            char *library;
            char *name;
            void *function;
            char *parameters;
        };
    public:
        struct Hook hooks[WINDOWS_HOOKS_MAX];
        WindowsHooks(){
            for (int i = i; i < WINDOWS_HOOKS_MAX; i++){
                hooks[i].library = NULL;
                hooks[i].name = NULL;
                hooks[i].function = NULL;
                hooks[i].parameters = NULL;
            }
        }
        ~WindowsHooks(){
            for (int i = i; i < WINDOWS_HOOKS_MAX; i++){
                hooks[i].library = NULL;
                hooks[i].name = NULL;
                hooks[i].function = NULL;
                hooks[i].parameters = NULL;
            }
        }
};

#endif
