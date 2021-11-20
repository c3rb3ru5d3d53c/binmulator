#include <stdio.h>
#include <stdlib.h>
#include <unicorn/unicorn.h>
#include "src/args.h"
#include "src/common.h"
#include "src/linux/emulator.h"
#include "src/linux/elf.h"

#define X86_CODE32 "\x41\x4a"

int main(int argc, char **argv){
    Args args;
    args.parse(argc, argv);
    if (args.options.input_type != ARGS_INPUT_TYPE_FILE){
        fprintf(stderr, "[x] %s is not a file\n", args.options.input);
        return 1;
    }
    if (strcmp(args.options.mode, (char *)"linux:elf:x86_64") == 0){
        LinuxEmulator emu;
        LinuxELF elf;
        elf.Setup(LINUX_ELF_MODE_X86_64);
        printf("[-] reading %s\n", args.options.input);
        if (elf.ReadFile(args.options.input) == false){
            return 1;
        }
        printf("[*] read %s successful\n", args.options.input);
        if (emu.Setup(UC_ARCH_X86, UC_MODE_32, args.options.memory_address,
            args.options.memory_size * 1024 * 1024) == false){
            return 1;
        }
        void *data = malloc(sizeof(X86_CODE32)-1);
        memcpy(data, X86_CODE32, sizeof(X86_CODE32)-1);
        common_hex_dump("code", data, sizeof(X86_CODE32)-1);
        emu.WriteMemory(args.options.memory_address, data, sizeof(X86_CODE32)-1);
        int r_ecx = 0x1234;
        int r_edx = 0x7890;
        emu.WriteRegister(UC_X86_REG_ECX, &r_ecx);
        emu.WriteRegister(UC_X86_REG_EDX, &r_edx);
        printf("rcx: 0x%x\n", r_ecx);
        emu.Start(args.options.memory_address, sizeof(X86_CODE32)-1);
        emu.ReadRegiser(UC_X86_REG_ECX, &r_ecx);
        printf("rcx: 0x%x\n", r_ecx);
        free(data);
        return 0;
    }
    fprintf(stderr, "[x] something went wrong\n");
    return 1;
}
