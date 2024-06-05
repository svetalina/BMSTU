PUBLIC X
EXTRN exit: far

SSTK SEGMENT para STACK 'STACK'
	db 100 dup(0)
SSTK ENDS

SD1 SEGMENT para public 'DATA'
	X db 'X'
SD1 ENDS

SC1 SEGMENT para public 'CODE'
	assume CS:SC1, DS:SD1
main:	
	call exit
	
	mov dl, X
	mov ah, 2
	int 21h
	
	mov ah,4ch
	int 21h 
SC1 ENDS
END main