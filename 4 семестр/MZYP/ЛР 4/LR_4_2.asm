EXTRN X: byte
PUBLIC exit

SC2 SEGMENT para public 'CODE'
	assume CS:SC2
	
exit proc far
	mov ah, 8
	int 21h
	
	mov X, al
	 
	ret
exit endp
SC2 ENDS
END