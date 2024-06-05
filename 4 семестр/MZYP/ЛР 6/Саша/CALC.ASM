PUBLIC to_unsign
PUBLIC to_real_numb
PUBLIC to_reverse_code

EXTRN rev_numb: near
EXTRN real_numb: near
EXTRN unsign_len: byte
EXTRN unsign_str: byte
EXTRN len: byte
EXTRN number: byte
EXTRN hex_len: byte
EXTRN hex_str: byte
EXTRN dec_len: byte
EXTRN dec_str: byte

SEGCODE SEGMENT PARA PUBLIC 'CODE'
    ASSUME CS:SEGCODE
to_real_numb proc near
    xor cx, cx

    mov cl, len
    dec cx
    mov si, cx

    mov bx, 1

    to_real_lbl:
        xor ax, ax
        mov al, byte ptr[number + si]
        sub ax, "0"
        mul bx
        add word ptr [real_numb], ax

        mov ax, bx
        mov bx, 2
        mul bx
        mov bx, ax

        dec si

        loop to_real_lbl

    ret

to_real_numb endp


to_reverse_code proc near
    mov ax, word ptr[real_numb]
    mov word ptr[rev_numb], ax
    not word ptr[rev_numb]

    ret
to_reverse_code endp
    

to_unsign proc near
	mov ax, word ptr[real_numb]
	cmp byte ptr[number], "-"
	je rev_ax
	
	back:
	mov si, 15 
    xor dx, dx
    mov bx, 2

    lbl:
        div bx
        mov unsign_str[si], dl
        add unsign_str[si], "0"
		xor dx, dx
        
        inc unsign_len

        dec si
        cmp ax, 0
        jne lbl
        
    ret
	
	rev_ax:
		mov ax, word ptr[rev_numb]
		jmp back

to_unsign endp

to_hex proc near
	mov ax, word ptr[real_numb]
	cmp byte ptr[number], "-"
	je rev_ax
	
	back_main:
	xor cx, cx
	mov si, 3
	xor dx, dx
    mov bx, 16

    to_hex_lbl:
        div bx
        mov hex_str[si], dl

        cmp dl, 9 
        jg hex_char
        add hex_str[si], "0"

        back:
        xor dx, dx
        inc hex_len

        dec si
        cmp ax, 0
        jne to_hex_lbl

    ret

    hex_char:
        add hex_str[si], 55
        jmp back
		
	rev_ax:
		mov ax, word ptr[rev_numb]
		jmp back_main

to_hex endp

to_dec proc near
	mov dec_str[0], "+"
    cmp byte ptr[number], "-"
    je rev_sign

    back:
	mov ax, word ptr[real_numb]
    mov si, 5
    xor dx, dx
    mov bx, 10

    lbl:
        div bx
        mov dec_str[si], dl
        add dec_str[si], "0"
        xor dx, dx
        inc dec_len

        dec si
        cmp ax, 0
        jne lbl

    ret

    rev_sign:
        mov dec_str[0], "-"
        jmp back

to_dec endp

SEGCODE ENDS
END
