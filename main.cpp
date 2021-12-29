#include <stdlib.h>
#include <stdio.h>
#include "code.h"
#include "ncch_build.h"

int main(int argc, char** argv)
{
    ncch_settings* settings = (ncch_settings*)malloc(sizeof(ncch_settings));

    if (argc < 3)
    {
        printf("Usage: %s <input_file> <output_file>\n", argv[0]);
        return 1;
    }
    FILE* input = fopen(argv[1], "rb");
    if (input == NULL)
    {
        printf("Error: Could not open input file.\n");
        return 1;
    }
    fseek(input, 0, SEEK_END);
    long fSize = ftell(input);
    rewind(input);

    settings->componentFilePtrs.elfSize = fSize;
    settings->componentFilePtrs.elf = input;

    int result = BuildExeFsCode(settings);
    if (result != 0)
    {
        printf("Error: BuildExeFsCode returned %d\n", result);
        fclose(input);
        return 1;
    }

    FILE* output = fopen(argv[2], "wb");
    if (output == NULL)
    {
        printf("Error: Could not create output file.\n");
        return 1;
    }

    //The code is saved in a buffer located at "exefsSections.code.buffer"
    //And of size "exefsSections.code.size" so I copy all this stuff into the output file
    fwrite(settings->exefsSections.code.buffer, 1, settings->exefsSections.code.size, output);

    fclose(input);
    fclose(output);
    free(settings);

    printf("Done.\n");

    return 0;
}
