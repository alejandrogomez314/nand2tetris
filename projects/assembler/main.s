	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 12, 0	sdk_version 12, 0
	.globl	_get                            ## -- Begin function get
	.p2align	4, 0x90
_get:                                   ## @get
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$48, %rsp
	movq	%rdi, -16(%rbp)
	movq	%rsi, -24(%rbp)
	movl	%edx, -28(%rbp)
	movl	$0, -36(%rbp)
	movl	-28(%rbp), %eax
	subl	$1, %eax
	movl	%eax, -40(%rbp)
LBB0_1:                                 ## =>This Inner Loop Header: Depth=1
	movl	-36(%rbp), %eax
	cmpl	-40(%rbp), %eax
	jg	LBB0_9
## %bb.2:                               ##   in Loop: Header=BB0_1 Depth=1
	movl	-36(%rbp), %eax
	addl	-40(%rbp), %eax
	cltd
	movl	$2, %ecx
	idivl	%ecx
	movl	%eax, -44(%rbp)
	movq	-16(%rbp), %rdi
	movq	-24(%rbp), %rax
	movslq	-44(%rbp), %rcx
	shlq	$4, %rcx
	addq	%rcx, %rax
	movq	(%rax), %rsi
	callq	_strcmp
	movl	%eax, -32(%rbp)
	cmpl	$0, %eax
	jge	LBB0_4
## %bb.3:                               ##   in Loop: Header=BB0_1 Depth=1
	movl	-44(%rbp), %eax
	subl	$1, %eax
	movl	%eax, -40(%rbp)
	jmp	LBB0_8
LBB0_4:                                 ##   in Loop: Header=BB0_1 Depth=1
	cmpl	$0, -32(%rbp)
	jle	LBB0_6
## %bb.5:                               ##   in Loop: Header=BB0_1 Depth=1
	movl	-44(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -36(%rbp)
	jmp	LBB0_7
LBB0_6:
	movq	-24(%rbp), %rax
	movslq	-44(%rbp), %rcx
	shlq	$4, %rcx
	addq	%rcx, %rax
	movl	8(%rax), %eax
	movl	%eax, -4(%rbp)
	jmp	LBB0_10
LBB0_7:                                 ##   in Loop: Header=BB0_1 Depth=1
	jmp	LBB0_8
LBB0_8:                                 ##   in Loop: Header=BB0_1 Depth=1
	jmp	LBB0_1
LBB0_9:
	movl	$-1, -4(%rbp)
LBB0_10:
	movl	-4(%rbp), %eax
	addq	$48, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	_talloc                         ## -- Begin function talloc
	.p2align	4, 0x90
_talloc:                                ## @talloc
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	movl	$32, %edi
	callq	_malloc
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	_insert                         ## -- Begin function insert
	.p2align	4, 0x90
_insert:                                ## @insert
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$32, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movl	%edx, -20(%rbp)
	cmpq	$0, -8(%rbp)
	jne	LBB2_2
## %bb.1:
	callq	_talloc
	movq	%rax, -8(%rbp)
	movq	-16(%rbp), %rdi
	callq	_strdup
	movq	%rax, %rcx
	movq	-8(%rbp), %rax
	movq	%rcx, (%rax)
	movl	-20(%rbp), %ecx
	movq	-8(%rbp), %rax
	movl	%ecx, 8(%rax)
	movq	-8(%rbp), %rax
	movq	$0, 24(%rax)
	movq	-8(%rbp), %rax
	movq	$0, 16(%rax)
	jmp	LBB2_9
LBB2_2:
	movq	-16(%rbp), %rdi
	movq	-8(%rbp), %rax
	movq	(%rax), %rsi
	callq	_strcmp
	movl	%eax, -24(%rbp)
	cmpl	$0, %eax
	jne	LBB2_4
## %bb.3:
	leaq	L_.str.61(%rip), %rdi
	movb	$0, %al
	callq	_printf
	jmp	LBB2_9
LBB2_4:
	cmpl	$0, -24(%rbp)
	jge	LBB2_6
## %bb.5:
	movq	-8(%rbp), %rax
	movq	16(%rax), %rdi
	movq	-16(%rbp), %rsi
	movl	-20(%rbp), %edx
	callq	_insert
	jmp	LBB2_7
LBB2_6:
	movq	-8(%rbp), %rax
	movq	24(%rax), %rdi
	movq	-16(%rbp), %rsi
	movl	-20(%rbp), %edx
	callq	_insert
LBB2_7:
	jmp	LBB2_8
LBB2_8:
	jmp	LBB2_9
LBB2_9:
	addq	$32, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	_treeprint                      ## -- Begin function treeprint
	.p2align	4, 0x90
_treeprint:                             ## @treeprint
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	cmpq	$0, -8(%rbp)
	je	LBB3_2
## %bb.1:
	movq	-8(%rbp), %rax
	movq	16(%rax), %rdi
	callq	_treeprint
	movq	-8(%rbp), %rax
	movq	(%rax), %rsi
	movq	-8(%rbp), %rax
	movl	8(%rax), %edx
	leaq	L_.str.62(%rip), %rdi
	movb	$0, %al
	callq	_printf
	movq	-8(%rbp), %rax
	movq	24(%rax), %rdi
	callq	_treeprint
LBB3_2:
	addq	$16, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	_populate_predefined_variables  ## -- Begin function populate_predefined_variables
	.p2align	4, 0x90
_populate_predefined_variables:         ## @populate_predefined_variables
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$16, %rsp
	xorl	%edx, %edx
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rdi
	leaq	L_.str.3(%rip), %rsi
	callq	_insert
	movq	-8(%rbp), %rdi
	leaq	L_.str.4(%rip), %rsi
	movl	$1, %edx
	callq	_insert
	movq	-8(%rbp), %rdi
	leaq	L_.str.5(%rip), %rsi
	movl	$2, %edx
	callq	_insert
	movq	-8(%rbp), %rdi
	leaq	L_.str.6(%rip), %rsi
	movl	$3, %edx
	callq	_insert
	movq	-8(%rbp), %rdi
	leaq	L_.str.7(%rip), %rsi
	movl	$4, %edx
	callq	_insert
	movq	-8(%rbp), %rdi
	leaq	L_.str.8(%rip), %rsi
	movl	$5, %edx
	callq	_insert
	movq	-8(%rbp), %rdi
	leaq	L_.str.9(%rip), %rsi
	movl	$6, %edx
	callq	_insert
	movq	-8(%rbp), %rdi
	leaq	L_.str.10(%rip), %rsi
	movl	$7, %edx
	callq	_insert
	movq	-8(%rbp), %rdi
	leaq	L_.str.11(%rip), %rsi
	movl	$8, %edx
	callq	_insert
	movq	-8(%rbp), %rdi
	leaq	L_.str.12(%rip), %rsi
	movl	$9, %edx
	callq	_insert
	movq	-8(%rbp), %rdi
	leaq	L_.str.13(%rip), %rsi
	movl	$10, %edx
	callq	_insert
	movq	-8(%rbp), %rdi
	leaq	L_.str.14(%rip), %rsi
	movl	$11, %edx
	callq	_insert
	movq	-8(%rbp), %rdi
	leaq	L_.str.15(%rip), %rsi
	movl	$12, %edx
	callq	_insert
	movq	-8(%rbp), %rdi
	leaq	L_.str.16(%rip), %rsi
	movl	$13, %edx
	callq	_insert
	movq	-8(%rbp), %rdi
	leaq	L_.str.17(%rip), %rsi
	movl	$14, %edx
	callq	_insert
	movq	-8(%rbp), %rdi
	leaq	L_.str.18(%rip), %rsi
	movl	$15, %edx
	callq	_insert
	movq	-8(%rbp), %rdi
	leaq	L_.str(%rip), %rsi
	movl	$2, %edx
	callq	_insert
	movq	-8(%rbp), %rdi
	leaq	L_.str.1(%rip), %rsi
	movl	$24576, %edx                    ## imm = 0x6000
	callq	_insert
	movq	-8(%rbp), %rdi
	leaq	L_.str.2(%rip), %rsi
	movl	$1, %edx
	callq	_insert
	movq	-8(%rbp), %rdi
	leaq	L_.str.19(%rip), %rsi
	movl	$16384, %edx                    ## imm = 0x4000
	callq	_insert
	xorl	%edx, %edx
	movq	-8(%rbp), %rdi
	leaq	L_.str.20(%rip), %rsi
	callq	_insert
	movq	-8(%rbp), %rdi
	leaq	L_.str.21(%rip), %rsi
	movl	$4, %edx
	callq	_insert
	movq	-8(%rbp), %rdi
	leaq	L_.str.22(%rip), %rsi
	movl	$3, %edx
	callq	_insert
	movq	-8(%rbp), %rdi
	callq	_treeprint
	movq	-8(%rbp), %rax
	addq	$16, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	_main                           ## -- Begin function main
	.p2align	4, 0x90
_main:                                  ## @main
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$32, %rsp
	movl	$0, -4(%rbp)
	movl	%edi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	$0, -24(%rbp)
	movq	-24(%rbp), %rdi
	callq	_populate_predefined_variables
	movq	%rax, -24(%rbp)
	movq	-24(%rbp), %rdi
	callq	_treeprint
	xorl	%eax, %eax
	addq	$32, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.section	__TEXT,__cstring,cstring_literals
L_.str:                                 ## @.str
	.asciz	"ARG"

L_.str.1:                               ## @.str.1
	.asciz	"KBD"

L_.str.2:                               ## @.str.2
	.asciz	"LCL"

L_.str.3:                               ## @.str.3
	.asciz	"R0"

L_.str.4:                               ## @.str.4
	.asciz	"R1"

L_.str.5:                               ## @.str.5
	.asciz	"R2"

L_.str.6:                               ## @.str.6
	.asciz	"R3"

L_.str.7:                               ## @.str.7
	.asciz	"R4"

L_.str.8:                               ## @.str.8
	.asciz	"R5"

L_.str.9:                               ## @.str.9
	.asciz	"R6"

L_.str.10:                              ## @.str.10
	.asciz	"R7"

L_.str.11:                              ## @.str.11
	.asciz	"R8"

L_.str.12:                              ## @.str.12
	.asciz	"R9"

L_.str.13:                              ## @.str.13
	.asciz	"R10"

L_.str.14:                              ## @.str.14
	.asciz	"R11"

L_.str.15:                              ## @.str.15
	.asciz	"R12"

L_.str.16:                              ## @.str.16
	.asciz	"R13"

L_.str.17:                              ## @.str.17
	.asciz	"R14"

L_.str.18:                              ## @.str.18
	.asciz	"R15"

L_.str.19:                              ## @.str.19
	.asciz	"SCREEN"

L_.str.20:                              ## @.str.20
	.asciz	"SP"

L_.str.21:                              ## @.str.21
	.asciz	"THAT"

L_.str.22:                              ## @.str.22
	.asciz	"THIS"

	.section	__DATA,__data
	.globl	_predefinedSymbols              ## @predefinedSymbols
	.p2align	4
_predefinedSymbols:
	.quad	L_.str
	.long	2                               ## 0x2
	.space	4
	.quad	L_.str.1
	.long	24576                           ## 0x6000
	.space	4
	.quad	L_.str.2
	.long	1                               ## 0x1
	.space	4
	.quad	L_.str.3
	.long	0                               ## 0x0
	.space	4
	.quad	L_.str.4
	.long	1                               ## 0x1
	.space	4
	.quad	L_.str.5
	.long	2                               ## 0x2
	.space	4
	.quad	L_.str.6
	.long	3                               ## 0x3
	.space	4
	.quad	L_.str.7
	.long	4                               ## 0x4
	.space	4
	.quad	L_.str.8
	.long	5                               ## 0x5
	.space	4
	.quad	L_.str.9
	.long	6                               ## 0x6
	.space	4
	.quad	L_.str.10
	.long	7                               ## 0x7
	.space	4
	.quad	L_.str.11
	.long	8                               ## 0x8
	.space	4
	.quad	L_.str.12
	.long	9                               ## 0x9
	.space	4
	.quad	L_.str.13
	.long	10                              ## 0xa
	.space	4
	.quad	L_.str.14
	.long	11                              ## 0xb
	.space	4
	.quad	L_.str.15
	.long	12                              ## 0xc
	.space	4
	.quad	L_.str.16
	.long	13                              ## 0xd
	.space	4
	.quad	L_.str.17
	.long	14                              ## 0xe
	.space	4
	.quad	L_.str.18
	.long	15                              ## 0xf
	.space	4
	.quad	L_.str.19
	.long	16384                           ## 0x4000
	.space	4
	.quad	L_.str.20
	.long	0                               ## 0x0
	.space	4
	.quad	L_.str.21
	.long	4                               ## 0x4
	.space	4
	.quad	L_.str.22
	.long	3                               ## 0x3
	.space	4

	.section	__TEXT,__cstring,cstring_literals
L_.str.23:                              ## @.str.23
	.asciz	"A"

L_.str.24:                              ## @.str.24
	.asciz	"AD"

L_.str.25:                              ## @.str.25
	.asciz	"AM"

L_.str.26:                              ## @.str.26
	.asciz	"AMD"

L_.str.27:                              ## @.str.27
	.asciz	"D"

L_.str.28:                              ## @.str.28
	.asciz	"M"

L_.str.29:                              ## @.str.29
	.asciz	"MD"

	.section	__DATA,__data
	.globl	_destination                    ## @destination
	.p2align	4
_destination:
	.quad	L_.str.23
	.long	4                               ## 0x4
	.space	4
	.quad	L_.str.24
	.long	6                               ## 0x6
	.space	4
	.quad	L_.str.25
	.long	5                               ## 0x5
	.space	4
	.quad	L_.str.26
	.long	7                               ## 0x7
	.space	4
	.quad	L_.str.27
	.long	2                               ## 0x2
	.space	4
	.quad	L_.str.28
	.long	1                               ## 0x1
	.space	4
	.quad	L_.str.29
	.long	3                               ## 0x3
	.space	4

	.section	__TEXT,__cstring,cstring_literals
L_.str.30:                              ## @.str.30
	.asciz	"JEQ"

L_.str.31:                              ## @.str.31
	.asciz	"JGE"

L_.str.32:                              ## @.str.32
	.asciz	"JGT"

L_.str.33:                              ## @.str.33
	.asciz	"JLE"

L_.str.34:                              ## @.str.34
	.asciz	"JLT"

L_.str.35:                              ## @.str.35
	.asciz	"JMP"

L_.str.36:                              ## @.str.36
	.asciz	"JNE"

	.section	__DATA,__data
	.globl	_jump                           ## @jump
	.p2align	4
_jump:
	.quad	L_.str.30
	.long	2                               ## 0x2
	.space	4
	.quad	L_.str.31
	.long	3                               ## 0x3
	.space	4
	.quad	L_.str.32
	.long	1                               ## 0x1
	.space	4
	.quad	L_.str.33
	.long	6                               ## 0x6
	.space	4
	.quad	L_.str.34
	.long	4                               ## 0x4
	.space	4
	.quad	L_.str.35
	.long	7                               ## 0x7
	.space	4
	.quad	L_.str.36
	.long	5                               ## 0x5
	.space	4

	.section	__TEXT,__cstring,cstring_literals
L_.str.37:                              ## @.str.37
	.asciz	"!A"

L_.str.38:                              ## @.str.38
	.asciz	"!D"

L_.str.39:                              ## @.str.39
	.asciz	"0"

L_.str.40:                              ## @.str.40
	.asciz	"-1"

L_.str.41:                              ## @.str.41
	.asciz	"-A"

L_.str.42:                              ## @.str.42
	.asciz	"-D"

L_.str.43:                              ## @.str.43
	.asciz	"1"

L_.str.44:                              ## @.str.44
	.asciz	"A+1"

L_.str.45:                              ## @.str.45
	.asciz	"A-1"

L_.str.46:                              ## @.str.46
	.asciz	"A-D"

L_.str.47:                              ## @.str.47
	.asciz	"D&A"

L_.str.48:                              ## @.str.48
	.asciz	"D+1"

L_.str.49:                              ## @.str.49
	.asciz	"D+A"

L_.str.50:                              ## @.str.50
	.asciz	"D-A"

L_.str.51:                              ## @.str.51
	.asciz	"D|A"

	.section	__DATA,__data
	.globl	_comp0                          ## @comp0
	.p2align	4
_comp0:
	.quad	L_.str.37
	.long	49                              ## 0x31
	.space	4
	.quad	L_.str.38
	.long	13                              ## 0xd
	.space	4
	.quad	L_.str.39
	.long	42                              ## 0x2a
	.space	4
	.quad	L_.str.40
	.long	50                              ## 0x32
	.space	4
	.quad	L_.str.41
	.long	51                              ## 0x33
	.space	4
	.quad	L_.str.42
	.long	15                              ## 0xf
	.space	4
	.quad	L_.str.43
	.long	63                              ## 0x3f
	.space	4
	.quad	L_.str.23
	.long	48                              ## 0x30
	.space	4
	.quad	L_.str.44
	.long	55                              ## 0x37
	.space	4
	.quad	L_.str.45
	.long	50                              ## 0x32
	.space	4
	.quad	L_.str.46
	.long	7                               ## 0x7
	.space	4
	.quad	L_.str.27
	.long	12                              ## 0xc
	.space	4
	.quad	L_.str.47
	.long	0                               ## 0x0
	.space	4
	.quad	L_.str.48
	.long	31                              ## 0x1f
	.space	4
	.quad	L_.str.49
	.long	2                               ## 0x2
	.space	4
	.quad	L_.str.50
	.long	19                              ## 0x13
	.space	4
	.quad	L_.str.51
	.long	21                              ## 0x15
	.space	4

	.section	__TEXT,__cstring,cstring_literals
L_.str.52:                              ## @.str.52
	.asciz	"!M"

L_.str.53:                              ## @.str.53
	.asciz	"-M"

L_.str.54:                              ## @.str.54
	.asciz	"M+1"

L_.str.55:                              ## @.str.55
	.asciz	"M-1"

L_.str.56:                              ## @.str.56
	.asciz	"M-D"

L_.str.57:                              ## @.str.57
	.asciz	"D&M"

L_.str.58:                              ## @.str.58
	.asciz	"D+M"

L_.str.59:                              ## @.str.59
	.asciz	"D-M"

L_.str.60:                              ## @.str.60
	.asciz	"D|M"

	.section	__DATA,__data
	.globl	_comp1                          ## @comp1
	.p2align	4
_comp1:
	.quad	L_.str.52
	.long	49                              ## 0x31
	.space	4
	.quad	L_.str.53
	.long	51                              ## 0x33
	.space	4
	.quad	L_.str.28
	.long	48                              ## 0x30
	.space	4
	.quad	L_.str.54
	.long	55                              ## 0x37
	.space	4
	.quad	L_.str.55
	.long	50                              ## 0x32
	.space	4
	.quad	L_.str.56
	.long	7                               ## 0x7
	.space	4
	.quad	L_.str.57
	.long	0                               ## 0x0
	.space	4
	.quad	L_.str.58
	.long	2                               ## 0x2
	.space	4
	.quad	L_.str.59
	.long	19                              ## 0x13
	.space	4
	.quad	L_.str.60
	.long	21                              ## 0x15
	.space	4

	.section	__TEXT,__cstring,cstring_literals
L_.str.61:                              ## @.str.61
	.asciz	"Element already inserted\n"

L_.str.62:                              ## @.str.62
	.asciz	"%s - %d\n"

.subsections_via_symbols
