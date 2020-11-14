#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[]) {
    FILE *File_1, *File_2, *File_3;

    char* name_1 = argv[1];
    File_1 = fopen(name_1, "w");
    char* name_2 = argv[2];
    File_2 = fopen(name_2, "w");

    char* name_3 = argv[3];
    File_3 = fopen(name_3, "w");
    fprintf(File_3, "Created files:\n");
    fprintf(File_3, name_1);
    fprintf(File_3, "\n");
    fprintf(File_3, name_2);   
    fprintf(File_3, "\n"); 

    fclose(File_1);
    fclose(File_2);
    fclose(File_3);

    return 0;
}
