#include <stdio.h>

int main(int argc, char** argv) {
    if (argc != 2) {
        printf("Usage: ./decipher <filename>\n");
    }
    FILE* fp = fopen(argv[1], "r");
    char c = fgetc(fp);
    while (c != EOF)
    {
        unsigned char u = c;
        u = u >> 1;
        printf("%c", u);
        c = fgetc(fp);
    }
    fclose(fp);
    return 0;
}
