#include <stdio.h>
#include <string.h>


int main(int argc, char* argv[]) {
    FILE *file;
    
    char* res = argv[1];

    int n = 1;
    while(argc > 1) {
        n++;
        char* name = argv[n];

        file = fopen(name, "w");
        fclose(file);
    
        file = fopen(res, "a");
        fprintf(file, "%s", name);
        fprintf(file, "%s", "\n");
        fclose(file);
    }

    return 0;
}
