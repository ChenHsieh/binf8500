#include <stdio.h>
#include <string.h>
#include <limits.h>
int main()
{
    FILE *fp;
    fp = fopen("test.fastq", "r");
    char buff[255];
    int count = 0;

    char destination[] = {};
    char source[] = "World!";

    while (fgets(buff, INT_MAX, (FILE *)fp))

    {
        printf("buffer: %s\n", buff);
        strcat(destination, buff);
    }
    printf("Concatenated String: %s\n", destination);
    return 0;
}