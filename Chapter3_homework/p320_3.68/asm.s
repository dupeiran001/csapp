	.file	"src.c"
	.text
	.globl	setVal
	.type	setVal, @function
setVal:
.LFB0:
	.cfi_startproc
	movslq	8(%rsi), %rax
	addq	32(%rsi), %rax
	movq	%rax, 320(%rdi)
	ret
	.cfi_endproc
.LFE0:
	.size	setVal, .-setVal
	.ident	"GCC: (GNU) 10.2.0"
	.section	.note.GNU-stack,"",@progbits
