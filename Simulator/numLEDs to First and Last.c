#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_CRYSTALS 291

int numLEDs[NUM_CRYSTALS] = {5,5,3,3,5,6,6,7,5,3,6,4,9,4,4,4,6,3,6,6,7,4,4,7,7,4,5,6,8,6,7,7,4,6,4,4,4,4,4,4,5,4,4,4,5,8,9,5,4,6,3,4,4,4,7,5,5,6,6,3,6,5,7,8,5,7,7,4,6,5,5,5,6,6,3,3,3,4,5,7,6,9,3,2,5,8,4,4,4,3,3,4,4,9,6,3,4,9,6,5,6,8,4,3,6,8,5,7,4,6,6,7,5,5,7,5,3,5,7,8,3,4,4,6,7,4,8,9,6,7,4,4,3,7,7,3,8,6,4,6,3,3,6,3,6,4,11,11,10,10,3,6,8,5,7,4,6,6,7,5,5,7,5,3,5,7,8,3,4,4,6,7,4,8,9,6,7,4,4,3,7,7,3,8,6,4,6,3,3,6,3,4,5,5,5,6,6,3,6,6,3,3,4,5,7,6,9,3,2,5,8,4,4,4,3,3,4,4,9,6,3,4,9,6,4,5,4,4,5,5,4,4,4,4,4,4,5,8,9,5,4,6,3,4,4,4,7,5,5,6,6,3,6,5,7,8,5,7,7,9,5,3,3,4,6,6,7,5,3,6,4,9,4,4,4,6,3,6,6,7,4,4,7,7,4,5,6,8,6,7,7};

int main(int argc, char* argv[]) {

    printf("Converting...\n");

    FILE *fF = fopen("firstLED.txt", "w");
    FILE *lF = fopen("lastLED.txt", "w");
    
    int first = 0;
    int last = -1;

    fprintf(fF, "{");
    fprintf(lF, "{");
    for(int i = 0; i < NUM_CRYSTALS; i++) {
        
        last += numLEDs[i];

        fprintf(fF, "%d", first);
        fprintf(lF, "%d", last);
        if(i != NUM_CRYSTALS - 1) {
            fprintf(fF, ",");
            fprintf(lF, ",");
        }

        first += numLEDs[i];
    }
    fprintf(fF, "};\n");
    fprintf(lF, "};\n");

    printf("Done.\n");

    fclose(fF);
    fclose(lF);

    return EXIT_SUCCESS;
}