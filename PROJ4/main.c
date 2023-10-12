#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

extern void searchStrings( void* mem, int size);


int main(int argc, char *argv[]){
	struct stat statbuf;
	if(argc !=2){
		printf(" Usage: %s <executable file>", argv[0]);
		return 1;
	}
		
	FILE *f = fopen(argv[1], "r" );
	if(f==NULL){
		perror(" fopen argv[1]" );
		return 2;
	}
	int res = stat(argv[1], &statbuf);
	if(res!=0){
		perror(" stat argv[1]" );
		return 2;
	}	
	size_t fileSize =  statbuf.st_size;
	void *contents = malloc(fileSize);
	size_t nRead = fread( contents, 1, fileSize, f);
	if(nRead!=fileSize){
		perror(" Reading argv[1]");
		return 3;
	}	
	searchStrings( contents, fileSize );
	fclose(f);
	return 0;
}
