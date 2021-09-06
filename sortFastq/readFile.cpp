#include <stdio.h>
#include <limits.h>
#include <string.h>

// functions
// hoare
// void partition(char *str, char *left, char *right)
// {
//     char *pivot = str[0];
//     char *l = left;
//     char *r = right;
//     while (l <= r)
//     {
//         while (str[l] < pivot)
//             l++;
//             swap(str[l], str[r]);
//     }
// }

// void quickSort(char *arr, int low, int high)
// {
//     if (low < high)
//     {
//         int pi = partition(arr, low, high);
//         quickSort(arr, low, pi - 1);
//         quickSort(arr, pi + 1, high);
//     }



int main()
{
    // initialize variables
    FILE *fp;
    FILE *out_fp;
    int sequence_size = 500;
    char buff[sequence_size];
    char dest[500] = "test";
    // input file
    fp = fopen("test.fastq", "r");
    // output file
    out_fp = fopen("test_output.fastq", "w+");
    int count = 1;

    // get number of line and seq size
    fgets(buff, INT_MAX, (FILE *)fp);
    int header_size = strlen(buff);
    while (fgets(buff, INT_MAX, (FILE *)fp))
    {
        count++;
        buff[strcspn(buff, "\n")] = 0;
        // printf("%i\n", count);
    }
    int line_number = count;
    int chunk_count = count / 4;
    // declare array for storage
    int seq_size = strlen(buff);


    char header[chunk_count][header_size];
    char seq[chunk_count][seq_size];
    char quality[chunk_count][seq_size];

    fclose(fp);
    fp = fopen("test.fastq", "r");
    count = 0;
    chunk_count = count / 4;
    while (fgets(buff, INT_MAX, (FILE *)fp))
    {
        chunk_count = count / 4;

        buff[strcspn(buff, "\n")] = 0;

        if (count % 4 == 0) // header
        {
            strcpy(header[chunk_count], buff);
        }
        else if (count % 4 == 1) // sequence
        {
            strcpy(seq[chunk_count], buff);
        }
        else if (count % 4 == 3) // quality
        {
            strcpy(quality[chunk_count], buff);
        }
        count++;
    }
    fclose(fp);
    // for (int i = 0; i <= chunk_count; i++)
    // {
    //     printf("%s\n", header[i]);
    //     printf("%s\n", seq[i]);
    //     printf("%s\n", quality[i]);
    // }

    // sort implementation


    // check value to avoid worst case
    int low = 0;

    int high = chunk_count;

   /* Intializes random number generator */
   srand((unsigned) time(&t));

   /* Print 5 random numbers from 0 to 49 */
   for( i = 0 ; i < n ; i++ ) {
      printf("%d\n", rand() % 50);
   }
   

    // time to sort
    quickSort(seq, low, high);



    // reconstruct the file with sorted index
    // write file snippet
    fprintf(out_fp, "%s", buff);

    fclose(out_fp);
    return 0;
}