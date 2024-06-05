PUBLIC read_numb

PUBLIC number
PUBLIC len
PUBLIC real_numb
PUBLIC bin_str
PUBLIC hex_str

EXTRN newline: near
EXTRN to_real_numb: near
EXTRN to_bin: near
EXTRN to_hex: near

SEGDATA SEGMENT PARA PUBLIC 'DATA'
    max_size   db 7
    len        db 0
    number     db 8 DUP ("$")

    bin_str    db 17 DUP ("0")
               db "$" 
    
    hex_str    db 4 DUP ("0")
               db "$"

    real_numb  dw 0

    ent_msg  db "Enter number: $"
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
    call to_bin
    call to_hex
    call newline
    
    ret

read_numb endp


init_data proc near
    mov len, 0
    mov word ptr[real_numb], 0

    mov ax, seg number
    mov es, ax
    mov di, offset number
    mov al, "$"
    mov cx, 7
    rep stosb


    mov ax, seg bin_str
    mov es, ax
    mov di, offset bin_str
    mov al, "0"
    mov cx, 17
    rep stosb

    mov ax, seg hex_str
    mov es, ax
    mov di, offset hex_str
    mov al, "0"
    mov cx, 4
    rep stosb

    ret

init_data endp

SEGCODE ENDS
END
