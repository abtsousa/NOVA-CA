#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {

	FILE *f = fopen("test.txt", "w" );
	if(f==NULL){
		perror(" fopen argv[1]" );
		return 2;
	}

	for(int i=0;i<=255; i++) {
		char c = (char) i;
		fputc(c,f);
	}
	fclose(f);
	return 0;
}
