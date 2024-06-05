EXTRN EXIT: NEAR ;переход ближний, так как один сегмент

SSTK SEGMENT para STACK 'STACK'
	db 100 dup(0)
SSTK ENDS

SC1 SEGMENT para public 'CODE'
	assume CS:SC1
main:	
	MOV AH, 1 ;считывание первой цифры
	INT 21h
	MOV BL, AL ;в данной задаче хватит и регистров общего назначения, так что цифру помещаем сюда
	
	MOV DL, ' ' ;вывод пробела
	MOV AH, 2
	INT 21h
	
	MOV AH, 1
	INT 21h
	MOV CL, AL
	
	CALL EXIT ;переход в другой файл
SC1 ENDS
END main