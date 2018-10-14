        .data
array:                          /* declare an array of 64 bit integers */
        .quad 2,9,9,8,1,1,3,8,6,6

        .text

/* sum(%rdi size, %rsi array)

   sum and array of int64 values whose length is size.
*/
sum:
        xorq %rax, %rax         /* zero the sum */
        xorq %rbx, %rbx         /* zero the loop counter */
.Lloop_start:
        cmpq %rbx, %rdi         /* compare the loop counter to len */
        je .Lloop_end           /* jump $len == %eax */
        /* load the value of the array at index %rbx into %rcx */
        movq (%rsi, %rbx, 8), %rcx
        addq %rcx, %rax         /* increment %rax by %rcx */
        incq %rbx               /* increment %rbx by 1 */
        jmp .Lloop_start        /* jump to the top of the loop */
.Lloop_end:
        ret

        .global _start
_start:
        movq $10, %rdi
        movq $array, %rsi
        call sum
        movq %rax, %rdi
        movl $60, %eax          /* exit syscall marker, exits with value of %rdi */
        syscall
