EXIT  = 60		# usando simbolos para constantes
WRITE = 1

.data			# seccao de dados
msg: .ascii  "Hello, world!\n"
msglen = (. - msg)	# simbolo msglen representa o tamanho do vetor

.text			# seccao de codigo
.global _start		# exportar o simbolo _start (inicio do programa)

_start: 
	mov    $msglen,%rdx	# comprimento da mensagem
        mov    $msg,%rsi	# endereço da mensagem
        mov    $1,%rdi	# escreve no stdout
        mov    $WRITE,%eax		# pedir write ao sistema
        syscall		# chama o sistema

        movq    $0,%rdi
        movq   $EXIT,%rax		# pedir o exit ao sistema
        syscall		# chama o sistema
