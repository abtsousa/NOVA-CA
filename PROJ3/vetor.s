					# pseudoconstantes
EXIT = 60


.data					# seccao de dados (variaveis)
vetor:  .int  1, -1, 1, 1, 4, -3, 1234	# um vetor de inteiros
VETORSZ = (. - vetor)/4			# dimensao do vetor

x:      .int 1				# valor a pesquisar no vetor
total:  .int 0				# contagem de v(i) == x

.text					# seccao de codigo
.global _start				# exportar o simbolo _start
					# (inicio do programa)

# rax: resultado da contagem
# rbx: endereco de v(i)
# ecx: dim. do vetor
# edx: valor de v(i)

_start:




fim:	movl	%eax, total 
        mov    %rax,%rdi       # retorna a contagem ah shell
        mov    $EXIT,%rax      # pedir o exit ao sistema
        syscall # chama o sistema
        
