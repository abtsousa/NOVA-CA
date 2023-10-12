/*
CPU-Mem architecture
AC 2022/23  MIEI FCT/UNL

32 bit instruction
    8 bits instrução 31-24
    12 bits para especificar registos  23-20 op1 19-16 op2 15-12 result
    12 bits para endereços 
*/
#include <stdio.h>
#define NREGS 16

extern int Mem[];
extern int Regs[];

int signExtension20To32(int val) {
    int value = (0x000FFFFF & val);
    int mask = 0x00080000;
    int sign = (mask & val) >> 19;
    if (sign == 1)
        value += 0xFFF00000;
    return value;
}

void dorun(){
    unsigned int pc;  // program counter or intruction pointer
    unsigned int ir;  // instruction register

    unsigned int opcode;
	unsigned int reg1;
	unsigned int reg2;
	unsigned int reg3;
	int val;
	
    unsigned int address;
	unsigned char zero;
	unsigned char positivo;
    
    pc = 0;
    while( 1 ) {
        //	printf("pc = %d\n", pc);
        ir = Mem[pc];                  // FETCH
        opcode = ir >> 24;             // DECODE
        reg1 = (ir & 0x00f00000) >> 20;
        reg2 = (ir & 0x000f0000) >> 16;
        reg3 = (ir & 0x0000f000) >> 12;
        address =  ir & 0x00000fff;
        val = signExtension20To32(ir);
        // printf("DEBUG == pc: %d ir: %x\n", pc, Mem[pc]);
        
        switch( opcode ){              // EXECUTE
            case 0x00:   /* HALT */
                printf("HALT instruction executed\n");
                return;
            
            case 0x01:  /* LDI */
                Regs[reg1] = val;
                pc++;
                break;
            
            case 0x02: /* LOAD */
                Regs[reg1] = Mem[address];
                pc = pc + 1;
                break;
            
            case 0x03: /* STORE */
                Mem[address] = Regs[reg1];
                pc++;
                break;
            
            case 0x04: /* ADD */
                Regs[reg3] = Regs[reg1] + Regs[reg2];
                if (Regs[reg3] == 0) {
                    zero = 1;
                    positivo = 1;
                } else if (Regs[reg3] > 0) {
                    zero = 0;
                    positivo = 1;
                } else {
                    zero = 0;
                    positivo = 0;
                }
                pc++;
                break;
			
            case 0x05: /* SUB */
                Regs[reg3] = Regs[reg1] - Regs[reg2];
                if (Regs[reg3] == 0) {
                    zero = 1;
                    positivo = 1;
                } else if (Regs[reg3] > 0) {
                    zero = 0;
                    positivo = 1;
                } else {
                    zero = 0;
                    positivo = 0;
                }
                pc++;
                break;

            case 0x06: /* CLEAR */
                Regs[reg1] = 0;
                pc++;
                break;
            
            case 0x08: /* JMP */       
                pc = address;
                break;
            
            case 0x09: /* JZ */
                if (zero)
                    pc = address;
                else pc++;
                break;
            
            case 0x0A: /* JNZ */
                if (!zero)
                    pc = address;
                else pc++;
                break;
				
            case 0x0B:  /* JG */
                if (!zero && positivo)
                    pc = address;
                else pc++;
                break;
            
            case 0x0C: /* JGE */
                if (positivo)
                    pc = address;
                else pc++;
                break;
				
            case 0x0D: /* JB */
                if (!zero && !positivo)
                    pc = address;
                else pc++;
                break;
            
            case 0x0E: /* JBE */
                if (zero || !positivo)
                    pc = address;
                else pc++;
                break;
            
            default:
                printf("Invalid instruction!\n");
                return;
        }
    }
}
