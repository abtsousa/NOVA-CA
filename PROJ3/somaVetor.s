					# pseudoconstantes
EXIT = 60


.data					# seccao de dados (variaveis)
vetor:  .int  1, -1, 1, 1, 4, -3, 200	# um vetor de inteiros
VETORSZ = (. - vetor)/4			# dimensao do vetor

.text					# seccao de codigo
.global _start				# exportar o simbolo _start
					# (inicio do programa)

# rax: resultado da soma
# rbx: endereco de v(i)
# ecx: dim. do vetor


_start:



fim:
        mov    %rax,%rdi       # retorna o total ah shell
        mov    $EXIT,%rax      # pedir o exit ao sistema
        syscall  # chama o sistema
