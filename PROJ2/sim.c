/*
CPU-Mem architecture simulator
AC 2022/23 MIEI FCT/UNL
Adaptado da versão de 2020/21
*/
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define PROMPT "cmd> "  //command line prompt sign
#define MAXSZ  100  //max command line size

#define MAXMEM 4096 // 2^12 34 bit word
#define NoREGS 16

int Mem[MAXMEM];  // simulated memory ( 32 bits/addr)
int Regs[NoREGS];

extern void dorun();



char *trim(char l[]) {
    int first=0;
    int last=strlen(l)-1; // last char at string 'l'

    while ( isspace(l[first]) )  // ignore "spaces" at start
        first++;
    while ( isspace(l[last]) ) // ignore "spaces" at the end
        last--;
    l[last+1]='\0';
    return &(l[first]);
}

char *getarg(char l[]) {
    int i=0;
    while ( !isspace(l[i]) && l[i]!='\0' )
        i++;
    l[i]='\0';
    i++;
    while ( isspace(l[i]) && l[i]!='\0' )
        i++;
    return &(l[i]);
}

int doload(char arg[]) {
    FILE *f = fopen(arg, "r");
    if ( f==NULL ) return 0; // erro
    int addr = 0;
   int word;

    while( fscanf(f, "%x", &word) >0 )  // read next word
        Mem[addr++] = word;
    fclose(f);
    return addr;
}

void dopoke(char arg[]) {
    int addr;
    int val;
    if (sscanf(arg, "%i%i", &addr, &val)!=2 || addr<0 || addr>=MAXMEM)
        printf("invalid arg(s)\n");
    Mem[addr]=val;
}

void dopeek(char arg[]) {
    int addr;
    if (sscanf(arg, "%i", &addr)!=1 || addr>=MAXMEM || addr<0)
        printf("invalid address\n");
    else
        printf("0x%x: 0x%hx\n", addr, Mem[addr]);
}

void dodump(char arg[]) {
    int count;
    if (sscanf(arg, "%i", &count)!=1 || count>=MAXMEM || count<0)
        printf("invalid size\n");
    else {
		for (int i=0; i<NoREGS; i++)
            printf("Reg %x: 0x%08x\n", i, Regs[i]);
	printf("-------------------------\n");
        for (int i=0; i<count; i++)
            printf("0x%x: 0x%08x\n", i, Mem[i]);
	}
}

/*-------------------------------------------------------*/
int main() {
    char line[MAXSZ];

    printf("cpu-AC simulator console\n");
    printf(PROMPT);fflush(stdout);

    while ( fgets(line, MAXSZ, stdin)!=NULL ) {
        char* cmd = trim(line);
        char* arg = getarg(cmd);
        if (strcmp(cmd, "load")==0) {
            int n=doload(arg);
            printf("read %d 32-bit words\n", n);
        }
        else if (strcmp(cmd, "run")==0) {
            dorun();
            //printf("executed %d instructions\n");
        }
        else if (strcmp(cmd, "poke")==0) dopoke(arg);
        else if (strcmp(cmd, "peek")==0) dopeek(arg);
        else if (strcmp(cmd, "dump")==0) dodump(arg);
        else if (strcmp(cmd, "exit")==0) return 0;  // exit program
        else printf("unknown command!\n");
        printf(PROMPT);fflush(stdout);
    }
}

