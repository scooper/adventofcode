#include <string.h>

#include "common/help.h"

int main(int argc, char *argv[]) {
    if(argc < 2) {
        print_help();
        return 0;
    }

    if(strcmp(argv[1], "-h") || strcmp(argv[1], "--help")) {
        print_help();
    }

    return 0;
}
