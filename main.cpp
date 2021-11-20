#include <stdio.h>
#include <stdlib.h>
#include "src/args.h"

int main(int argc, char **argv){
    Args args;
    args.parse(argc, argv);
    return 0;
}
