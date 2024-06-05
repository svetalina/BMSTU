PUBLIC print_unsign
PUBLIC print_bin
PUBLIC print_unsign
PUBLIC newline

EXTRN real_numb: near
EXTRN number: near
EXTRN bin_str: byte
EXTRN hex_str: byte

SEGDATA SEGMENT PARA PUBLIC 'DATA'
    unsign_msg  db "Unsigned number:",      10, 13, "$"        
    bin_msg     db "Signed binary:",        10, 13, "$"
    hex_msg     db "Signed hexadecimal:",   10, 13, "$"
SEGDATA ENDS

SEGCODE SEGMENT PARA PUBLIC 'CODE'
    ASSUME CS:SEGCODE, DS:SEGDATA
print_unsign proc near
    call newline

    mov ah, 9
    mov dx, offset unsign_msg
    int 21h

    mov dx, offset number
    int 21h

    call newline
    ret

print_unsign endp

print_bin proc near
    call newline

    mov ah, 9
    mov dx, offset bin_msg
    int 21h

    mov dx, offset bin_str
    int 21h

    call newline
    ret

print_bin endp


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
