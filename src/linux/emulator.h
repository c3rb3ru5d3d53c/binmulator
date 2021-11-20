#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <stdint.h>
#include <unicorn/unicorn.h>

#ifndef LINUX_EMULATOR_H
#define LINUX_EMULATOR_H

#define LINUX_EMULATOR_CHECK_ERROR if(CheckEngineError()==false){return false;}

class LinuxEmulator{
    private:
        struct {
            uc_engine *uc;
            uc_err err;
            uint64_t memory_address;
            size_t memory_size;
        } engine;
        bool CheckEngineError(){
            if (engine.err != UC_ERR_OK) {
                fprintf(stderr, "[x] %s\n", uc_strerror(engine.err));
                return false;
            }
            return true;
        }
    public:
        LinuxEmulator(){
            engine.memory_address = 0;
            engine.memory_size = 0;
        }
        bool Setup(uc_arch arch, uc_mode mode, uint64_t memory_address, size_t memory_size){
            engine.err = uc_open(arch, mode, &engine.uc);
            LINUX_EMULATOR_CHECK_ERROR
            engine.memory_address = memory_address;
            engine.memory_size = memory_size;
            engine.err = uc_mem_map(engine.uc, engine.memory_address, engine.memory_size, UC_PROT_ALL);
            LINUX_EMULATOR_CHECK_ERROR
            return true;
        }
        bool WriteMemory(uint64_t address, void *data, size_t data_size){
            engine.err = uc_mem_write(engine.uc, address, data, data_size);
            LINUX_EMULATOR_CHECK_ERROR
            return true;
        }
        bool WriteRegister(int regid, void *value){
            engine.err = uc_reg_write(engine.uc, regid, value);
            LINUX_EMULATOR_CHECK_ERROR
            return true;
        }
        bool ReadRegiser(int regid, void *value){
            engine.err = uc_reg_read(engine.uc, regid, value);
            LINUX_EMULATOR_CHECK_ERROR
            return false;
        }
        bool Start(int address, int size){
            engine.err = uc_emu_start(engine.uc, address, address + size, 0, 0);
            LINUX_EMULATOR_CHECK_ERROR
            return true;
        }
        ~LinuxEmulator(){
            engine.memory_address = 0;
            engine.memory_size = 0;
            uc_close(engine.uc);
        }
};

#endif
