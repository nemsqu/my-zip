#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){
    // check number of parameters
    if(argc == 1){
        printf("my-zip: file1 [file2 ...]\n");
        exit(1);
    }

    FILE *pfile, *poutput = stdout;
    char *buffer = NULL;
    size_t len = 0, read;

    // check if output should be directed to a file
    for(int i=1; i<argc; i++){
        if(strcmp(argv[i], ">") == 0) {
            i++;
            if((poutput = fopen(argv[i], "wb")) == NULL){
                printf("my-zip: cannot open file\n");
                exit(1);    
            }
            continue;
        }
        // there should not be more parameters after output file
        if(poutput != stdout){
            printf("Only one output file allowed.\n");
            exit(1);
        }
    }

    int amount = 0;
    char character;
    // loop through files
    for(int i=1; i < argc; i++){
        if(strcmp(argv[i], ">") == 0) {
            // no more input files
            break;
        }
        if((pfile = fopen(argv[i], "r")) == NULL){
            printf("my-zip: cannot open file\n");
            exit(1);
        }
        // read the contents
        while((read = getline(&buffer, &len, pfile)) != -1){
            // iterate through the line character by character
            for(int j = 0; j < read; j++){
                if (character == buffer[j]){
                    // same character as previous, increase amount
                    amount++;
                } else {
                    // a new character after previous character
                    if(amount != 0){
                        // write amount in binary
                        if(fwrite(&amount, sizeof(int), 1, poutput) != 1){
                            printf("Error while writing data.\n");
                            exit(1);
                        }
                        // write character in ASCII
                        fprintf(poutput, "%c", character);
                        amount = 1;
                        character = buffer[j];
                    }
                    else {
                        // no previous character
                        character = buffer[j];
                        amount++;
                    }

                }

            }
        }
        fclose(pfile);
    }
    // last character was not yet written
    if(amount != 0){
        fwrite(&amount, sizeof(int), 1, poutput);
        fwrite(&character, sizeof(character), 1, poutput);
    }
    if(poutput != stdout){
        fclose(poutput);
    }
    return 0;
}