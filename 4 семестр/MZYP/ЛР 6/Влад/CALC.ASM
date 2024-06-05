PUBLIC to_real_numb
PUBLIC to_bin

EXTRN real_numb: near
EXTRN len: byte
EXTRN number: byte
EXTRN bin_str: byte
EXTRN hex_str: byte

SEGCODE SEGMENT PARA PUBLIC 'CODE'
    ASSUME CS:SEGCODE
to_real_numb proc near
    xor cx, cx

    mov cl, len
    mov si, cx
	dec si

    mov bx, 1

    to_real_lbl:
        xor ax, ax
        mov al, byte ptr[number + si]
        sub ax, "0"
        mul bx
        add word ptr[real_numb], ax	
		
        mov ax, bx
        mov bx, 8
        mul bx
        mov bx, ax

        dec si

        loop to_real_lbl

    ret

to_real_numb endp


to_bin proc near
    mov ax, word ptr[real_numb]
	
	mov bin_str[0], "-"
	cmp ax, 32767
	jbe give_plus
	

    back:
	mov si, 16
    xor dx, dx
    mov bx, 2

    lbl:
        div bx
        mov bin_str[si], dl
        add bin_str[si], "0"
        xor dx, dx

        dec si
        cmp ax, 0
        jne lbl

    ret

	give_plus:
		mov bin_str[0], "+"
		jmp back
		
to_bin endp

to_hex proc near
    mov ax, word ptr[real_numb]
	
	mov si, 3
    xor dx, dx
    mov bx, 16

    lbl:
        div bx
        mov hex_str[si], dl
		cmp dl, 9 
        jg hex_char
        add hex_str[si], "0"
		
		back:
        xor dx, dx

        dec si
        cmp ax, 0
        jne lbl

    ret

	hex_char:
        add hex_str[si], 55
        jmp back
		
to_hex endp

SEGCODE ENDS
END
