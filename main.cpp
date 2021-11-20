#include <stdio.h>
#include <stdlib.h>
#include <unicorn/unicorn.h>
#include "src/args.h"
#include "src/common.h"
#include "src/linux/emulator.h"

#define X86_CODE32 "\x41\x4a"

int main(int argc, char **argv){
    Args args;
    args.parse(argc, argv);
    if (strcmp(args.options.mode, (char *)"linux:elf:x86_64") == 0){
        int r_ecx = 0x1234;
        int r_edx = 0x7890;
        LinuxEmulator emu;
        if (emu.Setup(UC_ARCH_X86, UC_MODE_32, args.options.memory_address, args.options.memory_size * 1024 * 1024) == false){
            return 1;
        }
        void *data = malloc(sizeof(X86_CODE32)-1);
        memcpy(data, X86_CODE32, sizeof(X86_CODE32)-1);
        common_hex_dump("code", data, sizeof(X86_CODE32)-1);
        emu.WriteMemory(args.options.memory_address, data, sizeof(X86_CODE32)-1);
        emu.WriteRegister(UC_X86_REG_ECX, &r_ecx);
        emu.WriteRegister(UC_X86_REG_EDX, &r_edx);
        printf("rcx: 0x%x\n", r_ecx);
        emu.Start(args.options.memory_address, sizeof(X86_CODE32)-1);
        emu.ReadRegiser(UC_X86_REG_ECX, &r_ecx);
        printf("rcx: 0x%x\n", r_ecx);
        free(data);
        return 0;
    }
    fprintf(stderr, "[x] %s is an invalid mode\n", args.options.mode);
    return 1;
}
