# CSAPP 第二次作业

**源代码在github上开源，包括本篇文档，阅读每道题文件夹内的README.md了解编译及使用方法**

https://github.com/dupeiran001/csapp/tree/main/Chapter3_homework

> 本次作业编译的工具链：
>
> gcc version 10.2.0(GCC)
>
> GNU ld (GNU Binutils) 2.35.1
>
> GNU objdump (GNU BInutils) 2.35.1
>
> GNU Make 4.3
>
> Target : x86_64-pc-linux-gnu
>
> Kernel : 5.8.14-arch1-1

[TOC]



------

## P312-3.60

答案：

```C
long loop (long x , int n)
{
  long result = 0;
  long mask;
  for(mask = 1 ; mask != 0 ; mask = (mask<< n) )
      result |= mask&x;
      return result;
}
```

> A.原题中%r8保存着x的值，%ecx中保存n，%eax保存result，%rdx保存mask
>
> B.result初始值为0,mask初始值为1
>
> C.mask的测试条件是mask=0时结束循环
>
> D.mask每次左移n位修改的
>
> E.result按位或上r8修改的
>
> F.见上源码

------

反编译结果：

```assembly
src:     file format elf64-x86-64

Disassembly of section .text:

0000000000000000 <loop>:
   0:	89 f1                	mov    %esi,%ecx
   2:	b8 01 00 00 00       	mov    $0x1,%eax
   7:	ba 00 00 00 00       	mov    $0x0,%edx
   c:	eb 0c                	jmp    1a <loop+0x1a>
   e:	48 89 c6             	mov    %rax,%rsi
  11:	48 21 fe             	and    %rdi,%rsi
  14:	48 09 f2             	or     %rsi,%rdx
  17:	48 d3 e0             	shl    %cl,%rax
  1a:	48 85 c0             	test   %rax,%rax
  1d:	75 ef                	jne    e <loop+0xe>
  1f:	48 89 d0             	mov    %rdx,%rax
  22:	c3                   	retq  
```

原题asm代码反编译结果：

```assembly
asm.o:     file format elf64-x86-64

Disassembly of section .text:

0000000000000000 <loop>:
   0:	89 f1                	mov    %esi,%ecx         //ecx = n
   2:	ba 01 00 00 00       	mov    $0x1,%edx         //edx = 1
   7:	b8 00 00 00 00       	mov    $0x0,%eax         //eax = 0
   c:	eb 0c                	jmp    1a <loop+0x1a>    
   e:	49 89 f8             	mov    %rdi,%r8          //r8  = x
  11:	49 21 d0             	and    %rdx,%r8          //r8  = r8 & rdx
  14:	4c 09 c0             	or     %r8,%rax          //rax = rax | r8
  17:	48 d3 e2             	shl    %cl,%rdx          //rdx = rdx << n & 0xF
  1a:	48 85 d2             	test   %rdx,%rdx
  1d:	75 ef                	jne    e <loop+0xe>
  1f:	f3 c3                	repz retq 
```



注释：

>反编译的结果与原题提供的代码基本一致，但%edx与%eax互换
>
>%rsi代表原题中的%r8，最后两行将%rdx赋值给%rax
>
>故两份代码基本一致，反编译过程通过，符合原题要求



## P313-3.62

答案：

```C
/*Enumerated type creates set of constants numbered 0 and upward */
typedef enum {MODE_A, MODE_B, MODE_C, MODE_D, MODE_E} mode_t;

long switch3(long *p1 , long *p2 , mode_t action)
{
  /* p1 in %rdi , p2 in %rsi , action n %edx */
  long result = 0;
  switch (action)
  {
    case MODE_A:
      result = *p2;
      *p2 = *p1;
      break;
    case MODE_B:
      result = *p2 + *p1;
      *p1 = result;
      break;
    case MODE_C:
      *p1 = 59;
      result = *p2;
      break;
    case MODE_D:
      result = 27;
      *p1 = *p2;
      break;
    case MODE_E:
      result = 27;
      break;
    default :
      result = 12;
  }
  return result;
}

```

------

gcc -S 得到的结果：

```assembly
.file	"src.c"
	.text
	.globl	switch3
	.type	switch3, @function
switch3:
.LFB0:
	.cfi_startproc
	cmpl	$4, %edx
	ja	.L9
	movl	%edx, %edx
	leaq	.L4(%rip), %rcx
	movslq	(%rcx,%rdx,4), %rax
	addq	%rcx, %rax
	jmp	*%rax
	.section	.rodata
	.align 4
	.align 4
.L4:
	.long	.L8-.L4
	.long	.L7-.L4
	.long	.L6-.L4
	.long	.L5-.L4
	.long	.L3-.L4
	.text
.L3:
	movl	$27, %eax
	ret
.L8:
	movq	(%rsi), %rax
	movq	(%rdi), %rdx
	movq	%rdx, (%rsi)
	ret
.L7:
	movq	(%rdi), %rax
	addq	(%rsi), %rax
	movq	%rax, (%rdi)
	ret
.L6:
	movq	$59, (%rdi)
	movq	(%rsi), %rax
	ret
.L5:
	movq	(%rsi), %rax
	movq	%rax, (%rdi)
	movl	$27, %eax
	ret
.L9:
	movl	$12, %eax
	ret
	.cfi_endproc
.LFE0:
	.size	switch3, .-switch3
	.ident	"GCC: (GNU) 10.2.0"
	.section	.note.GNU-stack,"",@progbits
```

注：

> 编译结果的标号与原题不同

## P317-3.65

答案：

> A.%rdx保存A [i] [j] 的指针
>
> B.%rax保存A [j] [i] 的指针
>
> C. M的值等于15

分析：

> 每次%rdx递增8,故机器中long占用8个字节，且%rdx存储的是递增内层数组的指针
>
> 同理%rax存储递增外层数组的指针，每次递增120,故每一行存储120/8=15个long元素



## P320-3.68

答案：

> A = 8
>
> B = 6

分析：

> 由于数据对齐，数组中间存在空余内存，分析后易得：
>
> char array[B] 占用5～8个字节
>
> int t和short s[A] 共占用17～24字节
> 
> 结合int x [A] [B] 占用177～184字节
> 
> |     数据      | 占用字节数 |
> | :-----------: | :--------: |
> | char array[B] |    5～8    |
> |  short s[A]   |   13～20   |
> | int x[A] [B]  |  177～184  |
>
> 当A =  9 ，B = 5   时，符合要求
>

