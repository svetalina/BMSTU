PUBLIC print_sign
PUBLIC print_hex
PUBLIC print_dec
PUBLIC print_unsign
PUBLIC newline

EXTRN real_numb: near
EXTRN number: near
EXTRN hex_len: byte
EXTRN hex_str: byte
EXTRN dec_str: byte
EXTRN dec_len: byte
EXTRN unsign_len: byte
EXTRN unsign_str: near

SEGDATA SEGMENT PARA PUBLIC 'DATA'
    sign_msg   db "Signed number:",      10, 13, "$"        
    unsign_msg db "Unsigned number:",    10, 13, "$"
    hex_msg    db "Unsigned hexadecimal:",    10, 13, "$"
    dec_msg    db "Signed decimal:", 10, 13, "$"
SEGDATA ENDS

SEGCODE SEGMENT PARA PUBLIC 'CODE'
    ASSUME CS:SEGCODE, DS:SEGDATA
print_sign proc near
    call newline

    mov ah, 9
    mov dx, offset sign_msg
    int 21h

    mov dx, offset number
    int 21h

    call newline
    ret

print_sign endp


print_unsign proc near
   call newline

    mov ah, 9
    mov dx, offset unsign_msg
    int 21h

    mov dx, offset unsign_str
    int 21h

    call newline
    ret

print_unsign endp


print_hex proc near
    call newline

    mov ah, 9
    mov dx, offset hex_msg
    int 21h

    mov dx, offset hex_str
    int 21h

    call newline
    ret

print_hex endp


print_dec proc near
    call newline
    
    mov ah, 9
    mov dx, offset dec_msg
    int 21h

    mov dx, offset dec_str
    int 21h

    call newline
    ret

print_dec endp


newline proc near
    mov ah, 2
    mov dl, 10
    int 21h
    mov dl, 13
    int 21h

    ret
newline endp

SEGCODE ENDS
END
