//by Afonso Brás Sousa LEI 65263
//and Alexandre Cristóvão LEI 65143
#include <stdio.h>
#include <string.h>

#define MAXC 1024

int main(int argc, char *argv[]) {
    char buffer1[MAXC], buffer2[MAXC];
    int line = 0;
    int error = 0;

    if( argc != 3) {
        printf("Utilização: %s ficheiro1 ficheiro2\n", argv[0]);
        return 0;
    }

    FILE *f1, *f2;

    if( (f1=fopen(argv[1], "r")) == NULL ) {
        perror("Erro no open do ficheiro 1");
        return 1;
    }
    if( (f2=fopen(argv[2], "r")) == NULL) {
        perror("Erro no open do ficheiro 2");
        return 1;
    }

    while ( ( (fgets(buffer1, MAXC, f1)) != NULL ) && ( ( fgets(buffer2, MAXC, f2) != NULL ) ) ) {
        line += 1;
        if (strcmp(buffer1, buffer2) != 0) {
            printf("#%i:\t%s\t%s\n", line, buffer1, buffer2);
            error++;
        }
    }

/* Assuming both files have the same number of lines, this is not needed
    // Checking extra lines on file 1
    while ((fgets(buffer1, MAXC, f1)) != NULL) {
        line += 1;
        printf("%i\n", line);
        error++;
    }

    // Checking extra lines on file 2
    while ((fgets(buffer2, MAXC, f2)) != NULL) {
        line += 1;
        printf("%i\n", line);
        error++;
    }
*/

    if (error==0) {
        printf("OK");
    }

    fclose(f1);
    fclose(f2);
    return 0;
}