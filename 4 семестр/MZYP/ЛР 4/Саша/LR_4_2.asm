PUBLIC EXIT

SC1 SEGMENT para public 'CODE'
	assume CS:SC1
	
exit proc NEAR
	SUB CL, '0' ;чтоб вычитались цифры, а не asci-коды надо сделать эту операцию
	SUB BL, CL
	
	MOV DL, 10 ;перевод каретки
	MOV AH, 2
	INT 21h
	
	MOV DL, BL
	MOV AH, 2
	int 21h
	 
	mov AH, 4ch
	int 21h 
exit endp
SC1 ENDS
END