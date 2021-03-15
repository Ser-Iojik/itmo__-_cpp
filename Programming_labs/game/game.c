// Вики которые использовались для создания программы
// Конспекты лекций
// Статья по созданию игры жизнь на с++ (Исчерпывающая статья с многими функциями) https://code-live.ru/post/cpp-life-game/
// Статья по bmp файлам на википедииhttps://ru.wikipedia.org/wiki/BMP
// Union https://radioprog.ru/post/655
// Статья по игре на википедии https://ru.wikipedia.org/wiki/Игра_«Жизнь»
// Использовалось для понимания игры в целом https://playgameoflife.com/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <errno.h>

unsigned long long strtolong(char* str) {
    unsigned long long a = 0;
    for (unsigned long long i = 0; i < strlen(str); i++) {
        a = a*10 + str[i] - '0';
    }
    return a;
}

void parse_args(int argc, char* argv[], char** file_path, char** output_dir,
        long long* max_iterations, unsigned long long* dump_freq) {
    int i = 1;

    while (i < argc) {
        if (!strcmp(argv[i], "--input")) {
            i++;
            *file_path = argv[i];
            continue;
        }

        if (!strcmp(argv[i], "--output")) {
            i++;
            *output_dir = argv[i];
            continue;
        }

        if (!strcmp(argv[i], "--max_iter")) {
            i++;
            *max_iterations = strtolong(argv[i]);
            continue;
        }

        if (!strcmp(argv[i], "--dump_freq")) {
            i++;
            *dump_freq = strtolong(argv[i]);
            continue;
        }
        i++;
    }

    printf("\nParameters: \n\n");
    printf("Input file: %s\n", *file_path);
    printf("Output dir: %s\n", *output_dir);
    printf("Max iter: %llu\n", *max_iterations);
    printf("Dump freq: %llu\n\n", *dump_freq);
    printf("The game is now on!\n\n");
}

// Объявим объединение 
// Вики: https://radioprog.ru/post/655 
union bmp_headers {
    unsigned char buffer[56];

    struct {
        unsigned short empty;
        unsigned short BM; // 2 bytes
        unsigned int size; // 4 bytes
        unsigned int reserved; // 4 bytes
        unsigned int image_offset; // 4 bytes

        unsigned int header_size; // 4 bytes
        unsigned int width; // 4 bytes
        unsigned int height; // 4 bytes
        unsigned short planes; // 2 bytes
        unsigned short bit_count; // 2 bytes
        unsigned int compression; // 4 bytes
        unsigned int image_size; // 4 bytes
        unsigned int x_pixels_per_meter; // 4 bytes
        unsigned int y_pixels_per_meter; // 4 bytes
        unsigned int color_used; // 4 bytes
        unsigned int colors_important; // 4 bytes
    } data; // total of 54 bytes
};

union bmp_rgbquad {
    unsigned char buffer[4];

    struct {
        unsigned char rgbBlue;
        unsigned char rgbGreen;
        unsigned char rgbRed;
        unsigned char rgbReserved;
    } data;
};

// Создание map
int** map_alloc(size_t Y, size_t X) {
    int **A = (int **)malloc(Y * sizeof(int *));
    if (A == NULL) perror("Error while allocating map:");
    for (size_t i = 0; i < X; i++){
        A[i] = (int *)malloc(X * sizeof(int));
        if (A[i] == NULL) perror("Error while allocating map:");
    }
    return A;
}

// Очистка map
void map_free(int** A, size_t Y) {
    for(size_t i = 0; i < Y; i++) {
        free(A[i]);
        if(A[i] == NULL) perror("Error freeing map:");
    }
    free(A);
    if (A == NULL) perror("Error freeing map:");
}

void map_copy_and_discard(int** from, int** to, unsigned long long dimensions_y, unsigned long long dimensions_x) {
    for (unsigned long long y = 0; y < dimensions_y; y++) {
        for (unsigned long long x = 0; x < dimensions_x; x++) {
            to[y][x] = from[y][x];
        }
    }
    map_free(from, dimensions_y);
}

int next_generation(int** array, unsigned long long y, unsigned long long x,
                    unsigned long long dimensions_y, unsigned long long dimensions_x){

    unsigned int count = 0; // Счётчик соседей
    dimensions_x--;
    dimensions_y--;
    if (x == 0) {
        if (array[y][x + 1]) count++;
        if (y == 0) {
            if (array[y + 1][x]) count++;
            if (array[y + 1][x + 1]) count++;
        } else if (y == dimensions_y){
            if (array[y - 1][x]) count++;
            if (array[y - 1][x + 1]) count++;
        } else {
            if (array[y + 1][x]) count++;
            if (array[y - 1][x]) count++;
            if (array[y + 1][x + 1]) count++;
            if (array[y - 1][x + 1]) count++;
        }
    }else if (x == dimensions_x) {
        if (array[y][x - 1]) count++;
        if (y == 0) {
            if (array[y + 1][x]) count++;
            if (array[y + 1][x - 1]) count++;
        } else if (y == dimensions_y){
            if (array[y - 1][x]) count++;
            if (array[y - 1][x - 1]) count++;
        } else {
            if (array[y + 1][x]) count++;
            if (array[y - 1][x]) count++;
            if (array[y + 1][x - 1]) count++;
            if (array[y - 1][x - 1]) count++;
        }
    } else {
        if (array[y][x - 1]) count++;
        if (array[y][x + 1]) count++;
        if (y == 0) {
            if (array[y + 1][x]) count++;
            if (array[y + 1][x + 1]) count++;
            if (array[y + 1][x - 1]) count++;
        } else if (y == dimensions_y){
            if (array[y - 1][x]) count++;
            if (array[y - 1][x + 1]) count++;
            if (array[y - 1][x - 1]) count++;
        } else {
            if (array[y + 1][x]) count++;
            if (array[y + 1][x + 1]) count++;
            if (array[y + 1][x - 1]) count++;
            if (array[y - 1][x]) count++;
            if (array[y - 1][x + 1]) count++;
            if (array[y - 1][x - 1]) count++;
        }
    }

    // printf("current value = %d, count of neighbour = %d, value = %d\n", array[y][x], count, ((count == 2 && array[y][x]) || count == 3));
    
    return ((count == 2 && array[y][x]) || (count == 3));
}

// Чтение поля игры и запись в массив
int** get_game_field(char* file_path, unsigned long long* dimensions_y, unsigned long long* dimensions_x) {
    FILE* image_file;
    image_file = fopen(file_path, "rb");

    // Если не получилось открыть файл
    if (image_file == NULL) perror("Error: while opening file of first generation:");

    union bmp_headers first_gen;

    // Также проверяем на ошибки чтения файлов
    if (!fread(first_gen.buffer + 2, sizeof(char), 54, image_file)) perror("Error: reading file:");

    if ((first_gen.data.bit_count == 1 && first_gen.data.color_used != 0) || first_gen.data.bit_count != 1) {

        printf("\n Error: bit count must be != 1\n");

        printf("file size: %d\n", first_gen.data.size);
        printf("image offset: %d\n", first_gen.data.image_offset);
        printf("image offset: %d", first_gen.data.image_offset);

        exit(EXIT_FAILURE);
    }

    union bmp_rgbquad rgbquad_array[2];

    if (!fread(rgbquad_array[1].buffer, sizeof(char), 4, image_file)) perror("Error reading rgbquad array from file:");
    if (!fread(rgbquad_array[0].buffer, sizeof(char), 4, image_file)) perror("Error reading rgbquad array from file:");

    *dimensions_y = first_gen.data.height;
    *dimensions_x = first_gen.data.width;

    int** map = map_alloc(*dimensions_y, *dimensions_x);

    unsigned char byte = 0;
    int counter = 8;
    for (long long y = *dimensions_y - 1; y >= 0; y--) {
        for (long long x = 0; x < *dimensions_x ; x++) {
            if (counter % 8 == 0) {
                if(!fread(&byte, sizeof(char), 1, image_file)) perror("Error reading bitmap from file:");
            }

            int pos = (byte >> (7 - (counter%8)) % 8) % 2;

            map[y][x] = rgbquad_array[pos].data.rgbBlue;

            counter++;
        }
    }

    fclose(image_file);
    return map;
}

void dump_game_field(char* output_dir, int** map, unsigned long long dimensions_y,
        unsigned long long dimensions_x, unsigned long long dump_number) {
    struct stat st = {0};

    if (stat(output_dir, &st) == -1) {
        mkdir(output_dir);
    }

    char* generation = (char*)malloc(sizeof(char) * 20);

    if (generation == NULL) perror("Error while allocating output file path: ");
    if (!sprintf(generation, "%llu", dump_number)) perror("Error generating output file path: ");

    char* output_file_name = (char*)malloc(sizeof(char)*200);

    if (output_file_name == NULL) perror("Error while allocating output file path: ");
    if (!strcpy(output_file_name, output_dir)) perror("Error generating output file path: ");
    if (!strcat(output_file_name, "/dump_")) perror("Error generating output file path: ");
    if (!strcat(output_file_name, generation)) perror("Error generating output file path: ");
    if (!strcat(output_file_name, ".bmp")) perror("Error generating output file path: ");

    FILE* output_file;
    output_file = fopen(output_file_name, "wb");
    if (output_file == NULL) perror("Error opening/creating output file:");
    free(generation);
    free(output_file_name);

    union bmp_headers image_header;
    image_header.data.empty = 0;
    image_header.data.BM = 19778;
    image_header.data.size = dimensions_x * dimensions_y + 54;
    image_header.data.reserved = 0;
    image_header.data.image_offset = 62;
    image_header.data.header_size = 40;
    image_header.data.width = dimensions_x;
    image_header.data.height = dimensions_y;
    image_header.data.planes = 1;
    image_header.data.bit_count = 1;
    image_header.data.compression = 0;
    image_header.data.image_size = dimensions_x * dimensions_y / 8;
    image_header.data.x_pixels_per_meter = 2925;
    image_header.data.y_pixels_per_meter = 2925;
    image_header.data.colors_important = 0;
    image_header.data.color_used = 0;

    if (!fwrite((image_header.buffer + 2), sizeof(char), 54, output_file)) perror("Error while forming output file:");

    union bmp_rgbquad rgbquad_array[2];
    rgbquad_array[0].data.rgbBlue = 255;
    rgbquad_array[0].data.rgbRed = 255;
    rgbquad_array[0].data.rgbGreen = 255;
    rgbquad_array[0].data.rgbReserved = 0;

    rgbquad_array[1].data.rgbBlue = 0;
    rgbquad_array[1].data.rgbRed = 0;
    rgbquad_array[1].data.rgbGreen = 0;
    rgbquad_array[1].data.rgbReserved = 0;

    if (!fwrite(rgbquad_array[0].buffer, sizeof(int), 1, output_file)) perror("Error while forming output file:");

    if (!fwrite(rgbquad_array[1].buffer, sizeof(int), 1, output_file)) perror("Error while forming output file:");

    unsigned char byte = 0;
    int counter = 0;
    for (long long y = dimensions_y - 1; y >= 0; y--) {
        for (long long x = 0; x < dimensions_x ; x++) {
            byte = byte << 1;

            if (map[y][x]) {
                byte += 1;
            }

            counter++;

            if (counter % 8 == 0) {
                if (!fwrite(&byte, sizeof(char), 1, output_file)) perror("Error while forming output file:");
                counter = 0;
                byte = 0;
            }
        }
    }
    fclose(output_file);
}

void simulation_game_of_life(char* file_path, char* output_dir, long long max_iter, unsigned long long dump_freq) {
    unsigned long long dimensions_y, dimensions_x;

    int** map = get_game_field(file_path, &dimensions_y, &dimensions_x);

    unsigned long long gen_counter = 0;

    dump_game_field(output_dir, map, dimensions_y, dimensions_x, gen_counter);

    while(true) {
        if (max_iter == 0) {
            break;
        }

        if (max_iter > 0){
            max_iter--;
        }

        gen_counter++;

        int** modified_map = map_alloc(dimensions_y, dimensions_x);

        for (unsigned long long y = 0; y < dimensions_y; y++) {
            for (unsigned long long x = 0; x < dimensions_x; x++) {
                modified_map[y][x] = next_generation(map, y, x, dimensions_y, dimensions_x);
            }
        }

        map_copy_and_discard(modified_map, map, dimensions_y, dimensions_x);

        if (gen_counter%dump_freq == 0) {
            dump_game_field(output_dir, map, dimensions_y, dimensions_x, gen_counter);
        }
    }

    printf("Game played successfully!\n");
    map_free(map, dimensions_y);
}

int main(int argc, char* argv[]) {

    char* file_path = NULL;
    char* output_dir = NULL;
    long long max_iter = -1;
    unsigned long long dump_freq = 1;

    parse_args(argc, argv, &file_path, &output_dir, &max_iter, &dump_freq);

    simulation_game_of_life(file_path, output_dir, max_iter, dump_freq);

    return 0;
}
