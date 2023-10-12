DESC_SIZE = 24
OFF_NEXT = 8 
OFF_SIZE = 0
OFF_FREE = 16
.section .text
.global myMalloc, myFree
.extern extend_heap
.extern head

find_block:
# rdi  block size (1st input parameter)
# if (head == NULL) return null;
# else i = head;
# while !(i->free == 1 && i->size >= rdi)
# i = i->next;
# return i;


    push %rbp           # begin stack
    mov  %rsp, %rbp

    mov (head), %rcx     # i = head

    .loop:              # while loop start
    cmp $0, %rcx        # if i == NULL
    jz .ret_null             # goto return
    cmp %rdi, OFF_SIZE(%rcx)  # if i->size < rdi
    jl .reloop            # reloop

    cmpb $1, OFF_FREE(%rcx) # *(rcx+OFF_FREE) = 1 -- cmpb instead of cmp to suppress warning
    jnz .reloop

    mov %rcx, %rax
    jmp .loop_end

    .reloop:
    mov OFF_NEXT(%rcx), %rcx    # i = i->next
    jmp .loop

    .ret_null:
    xor %rax, %rax # %rax = 0
    jmp .loop_end

    .loop_end:
    mov %rbp, %rsp
    pop %rbp
    ret

myMalloc:
#  rdi: size
# call find_block (devolve block)
# if find_block == NULL call extend_heap (devolve block)
# block->free = 0;
# return block
    push %rbp
    mov  %rsp, %rbp
    call find_block
    cmp $0, %rax
    jnz .end
    call extend_heap
    
    .end:
    movb $0, OFF_FREE(%rax) # optimization -- only last byte needs to change
    add $DESC_SIZE, %rax # points to start of Data block

    mov %rbp, %rsp
    pop %rbp
    ret

myFree:
# rdi: address of block user area
# block->free = 1;
    push %rbp
    mov  %rsp, %rbp
    
    sub $DESC_SIZE, %rax # points to start of metadata block
    movb $1, OFF_FREE(%rax) # optimization -- only last byte needs to change

    mov %rbp, %rsp
    pop %rbp
    ret

