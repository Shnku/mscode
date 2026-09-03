#include "file_open_buffer.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *read_file_ret_char_buffer(const char *filename)
{
    if (filename == NULL)
        return NULL;

    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
        return NULL;

    if (fseek(fp, 0, SEEK_END) != 0)
    {
        fclose(fp);
        return NULL;
    }

    long fsize = ftell(fp);
    if (fsize < 0 || fseek(fp, 0, SEEK_SET) != 0)
    {
        fclose(fp);
        return NULL;
    }

    char *buffer = malloc((size_t)fsize + 1);
    if (buffer == NULL)
    {
        fclose(fp);
        return NULL;
    }

    size_t bytes_read = fread(buffer, 1, (size_t)fsize, fp);
    fclose(fp);

    if (bytes_read != (size_t)fsize)
    {
        free(buffer);
        return NULL;
    }

    buffer[bytes_read] = '\0';
    return buffer;
}

#ifdef FILE_OPEN_BUFFER_STANDALONE
int main(void)
{
    char *buffer = read_file_ret_char_buffer("file.txt");
    if (buffer == NULL)
    {
        fprintf(stderr, "Could not read file.txt\n");
        return 1;
    }

    printf("%s", buffer);
    printf("\nlength = %zu\n", strlen(buffer));
    free(buffer);
    return 0;
}
#endif
