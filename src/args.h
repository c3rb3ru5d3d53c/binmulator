#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#ifndef ARGS_H
#define ARGS_H

#define ARGS_MODE_COUNT 1

class Args {
    private:
        void SetDefault(){
            options.mode = NULL;
            options.input = NULL;
            options.help = false;
            options.list_modes = false;
            options.memory_size = 32;
            options.memory_address = 0x1000000;
        }
        void CheckArg(int argc, int i){
            if (argc < i + 2){
                fprintf(stderr, "[x] not enough arguments\n");
                exit(1);
            }
        }
        void PrintModes(){
            for (int j = 0; j < ARGS_MODE_COUNT; j++){
                printf("%s\n", modes[j]);
            }
            exit(0);
        }
    public:
        char version[7] = "v1.0.0";
        char author[16] = "@c3rb3ru5d3d53c";
        const char *modes[ARGS_MODE_COUNT] = {"linux:elf:x86_64"};
        struct {
            char *mode;
            char *input;
            bool help;
            bool list_modes;
            uint64_t memory_address;
            size_t memory_size;
        } options;
        Args(){
            SetDefault();
        }
        void print_help(){
            printf(
                "binmulator %s\n"
                "  -i  --input\t\tinput file\n"
                "  -m  --mode\t\tmode\n"
                "  -M  --memory\t\tmemory (32MB)\n"
                "  -a  --address\t\tmemory address (0x1000000)\n"
                "  -lm --list-modes\tlist modes\n"
                "  -o  --output\t\toutput file\n"
                "  -v  --version\t\tversion\n"
                "Author: %s\n",
                version,
                author
            );
        }
        void parse(int argc, char **argv){
            if (argc < 2){
                print_help();
                exit(0);
            }
            for (int i = 0; i < argc; i++){
                if (strcmp(argv[i], (char *)"-h") == 0 ||
                    strcmp(argv[i], (char *)"--help") == 0){
                    print_help();
                    exit(0);
                }
                if (strcmp(argv[i], (char *)"-v") == 0 ||
                    strcmp(argv[i], (char *)"--version") == 0){
                    printf("%s\n", version);
                    exit(0);
                }
                if (strcmp(argv[i], (char *)"-i") == 0 ||
                    strcmp(argv[i], (char *)"--input") == 0){
                    CheckArg(argc, i);
                    options.input = argv[i+1];
                }
                if (strcmp(argv[i], (char *)"-lm") == 0 ||
                    strcmp(argv[i], (char *)"--list-modes") == 0){
                    PrintModes();
                }
                if (strcmp(argv[i], (char *)"-M") == 0 ||
                    strcmp(argv[i], (char *)"--memory") == 0){
                    CheckArg(argc, i);
                    options.memory_size = atoi(argv[i+1]);
                }
                if (strcmp(argv[i], (char *)"-m") == 0 ||
                    strcmp(argv[i], (char *)"--mode") == 0){
                    CheckArg(argc, i);
                    options.mode = argv[i+1];
                }
                if (strcmp(argv[i], (char *)"-a") == 0 ||
                    strcmp(argv[i], (char *)"--memory-address") == 0){
                    CheckArg(argc, i);
                    options.memory_address = atoi(argv[i+1]);
                }
            }
        }
        ~Args(){
            SetDefault();
        }
};

#endif
