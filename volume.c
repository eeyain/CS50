// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");                          //read input
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");                         //write output
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);                               //atof() converts a string to a float

    uint8_t bytes[HEADER_SIZE];                                     //array of bytes that will store the .wav header file
    int16_t buffer;                                                 //buffer variable that will store a sample of a .wav file
                                                                    //uint8_t represents an unsigned 8-bit integer, int16_t represents a signed 16-bit integer value
    int16_t output_buffer;

    //assume that the input file is a wav file. Vetting of the input file will not be conducted
    fread(bytes, sizeof(uint8_t), HEADER_SIZE, input);
    fwrite(bytes, sizeof(uint8_t), HEADER_SIZE, output);               //copy input's header file to output

    while(fread(&buffer, sizeof(int16_t), 1, input))                //this loop will run as long as there is a sample to copy
    {                                                               //i.e. if there's stuff to copy, fread() will return >0, which is a true condition
        output_buffer = factor * buffer;                            //to increase/decrease the volume of a sample, multiply it by a factor
        fwrite(&output_buffer, sizeof(int16_t), 1, output);
    }

    // Close files
    fclose(input);
    fclose(output);
}
