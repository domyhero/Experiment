[SECTION .data] ; 以下数据段

strHello db "Hello, world!", 0AH   ; 字节数据，0AH为 '\n'的ASCII码
STRLEN equ $ - strHello            ; $ 表示当前行位置，equ定义了宏 STRLEN 为 $ - strHello，即上面字符串的长度

[SECTION .text] ; 以下代码段 

[GLOBAL _start] ; 声明_start符号对外部可见，ld 链接脚本默认配置_start函数为代码入口

_start:
	mov edx, 14       ; 长度
	mov ecx, strHello ; 指针
	mov ebx, 1        ; fd
	mov eax, 4        ; write(1, strHello, 14)
	int 0x80

	mov ebx, 0        ; exit code
	mov eax, 1        ; exit(0)
	int 0x80

; ----------------------------------------------------------------------------------------------

; 编译链接方法：
; nasm -f elf -o hello.o hello.s
; ld hello.o -o hello

; Linux会有6个寄存器可被用来传递系统调用参数：
; eax (存放系统调用号)、 ebx、ecx、edx、esi及edi来存放这些额外的参数（以字母递增的顺序）。


