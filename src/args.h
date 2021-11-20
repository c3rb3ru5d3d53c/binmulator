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
        }
    public:
        char version[7] = "v1.0.0";
        char author[16] = "@c3rb3ru5d3d53c";
        const char *modes[ARGS_MODE_COUNT] = {"pe:x86"};
        struct {
            char *mode;
            char *input;
            bool help;
            bool list_modes;
        } options;
        Args(){
            SetDefault();
        }
        void print_help(){
            printf(
                "binmulator %s\n"
                "  -i --input\tinput file\n"
                "  -m --mode\tmode"
                "  -lm --list-modes\tlist modes\n"
                "  -o --output\toutput file\n"
                "  -v --version\tversion\n"
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
            }
        }
        ~Args(){
            SetDefault();
        }
};

#endif
