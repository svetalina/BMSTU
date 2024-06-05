PUBLIC read_numb

PUBLIC number
PUBLIC len
PUBLIC real_numb
PUBLIC rev_numb
PUBLIC unsign_len
PUBLIC unsign_str
PUBLIC hex_len
PUBLIC hex_str
PUBLIC dec_len
PUBLIC dec_str

EXTRN newline: near
EXTRN to_real_numb: near
EXTRN to_reverse_code: near
EXTRN to_unsign: near
EXTRN to_hex: near
EXTRN to_dec: near

SEGDATA SEGMENT PARA PUBLIC 'DATA'
    max_size   db 18
    len        db 0
    number     db 19 DUP ("$")

    unsign_len db 0
    unsign_str db 16 DUP ("0")
			   db "$"
	
    hex_len    db 0
    hex_str    db 4 DUP ("0")
               db "$" 
	
	dec_len    db 0
    dec_str    db 6 DUP ("0")
               db "$"

    real_numb  dw 0
    rev_numb   dw 0

    ent_msg  db "Enter number (with sign): $"
SEGDATA ENDS

SEGCODE SEGMENT PARA PUBLIC 'CODE'
    ASSUME CS:SEGCODE, DS:SEGDATA
read_numb proc near
    call init_data
    call newline

    mov ah, 9
    mov dx, offset ent_msg
    int 21h

    mov ah, 0AH
    mov dx, offset max_size
    int 21h

    call to_real_numb
    call to_reverse_code
    call to_unsign
    call to_hex
    call to_dec
    call newline
    
    ret

read_numb endp


init_data proc near
    mov len, 0
    mov unsign_len, 0
    mov hex_len, 0
    mov dec_len, 0
    mov word ptr[real_numb], 0
    mov word ptr[rev_numb], 0

    mov ax, seg number
    mov es, ax
    mov di, offset number
    mov al, "$"
    mov cx, 18
    rep stosb

    mov ax, seg unsign_str
    mov es, ax
    mov di, offset unsign_str
    mov al, "0"
    mov cx, 16
    rep stosb

    mov ax, seg hex_str
    mov es, ax
    mov di, offset hex_str
    mov al, "0"
    mov cx, 4
    rep stosb

    mov ax, seg dec_str
    mov es, ax
    mov di, offset dec_str
    mov al, "0"
    mov cx, 6
    rep stosb

    ret

init_data endp

SEGCODE ENDS
END
