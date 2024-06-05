STACKSEG SEGMENT PARA STACK 'STACK'
    DB 100 DUP(0)
STACKSEG ENDS

DATASEG SEGMENT PARA 'DATA'
    RMSG DB 'Enter the number of matrix rows: $'
    CMSG DB 'Enter the number of matrix columns: $'
    MMSG DB 'Enter matrix:$'
    RESMSG DB 'Resulting matrix:$'
    
	DECR DB 0
    ROWS DB 0
    COLS DB 0

    MATRIX DB 9 * 9 DUP(0)
	
	MAXNUMBER DW 0

DATASEG ENDS

CODESEG SEGMENT PARA 'CODE'
    ASSUME CS:CODESEG, DS:DATASEG, ES:DATASEG, SS:STACKSEG

	NEWLINE:
		MOV AH, 2
		MOV DL, 13
		INT 21H
		MOV DL, 10
		INT 21H
		RET

	PRINTSPACE:
		MOV AH, 2
		MOV DL, ' '
		INT 21H
		RET

	MAIN:
		MOV AX, DATASEG 
		MOV DS, AX

		MOV AH, 9 ;вывод сообщения
		MOV DX, OFFSET RMSG
		INT 21H

		MOV AH, 1 ;считывание количества строк
		INT 21H
		MOV ROWS, AL
		SUB ROWS, '0'
		CALL NEWLINE

		MOV AH, 9
		MOV DX, OFFSET CMSG
		INT 21H

		MOV AH, 1
		INT 21H
		MOV COLS, AL
		SUB COLS, '0'
		CALL NEWLINE

		MOV AH, 9
		MOV DX, OFFSET MMSG
		INT 21H
		CALL NEWLINE

		; Ввод матрицы
		MOV SI, 0 ;SI - регист, который будет отвечать за строки
		MOV CL, ROWS ;CL - регистр, отвечающий за цикл, сейчас количество строк
		INROOWLOOP:
			MOV DECR, CL ;сохраненийе регистра CL, который отвечает за проход по строкам
		
		
			MOV BX, 0 ;BX - регист, который будет отвечать за столбцы
			MOV CL, COLS ;установка решистра для прохода по строкам
			INCOLUMNLOOP:
				MOV AH, 1
				INT 21H
	
				MOV MATRIX[SI][BX], AL ;раскроется в SI+BX (номер строки + номер столбца как в си)
				INC BX ;увеличение номера столбца на 1
				
				CALL PRINTSPACE
				
				LOOP INCOLUMNLOOP	


			CALL NEWLINE
	
			MOV CL, DECR ;восстанавливаем занчение регистра
			ADD SI, 9 ;так как столбцов выделено 9, то надо увеличить значение SI на этот сдвиг
			
			LOOP INROOWLOOP
		
		;BX - номер строки (со смещением не забывай), SI - номер столбца
		MOV SI, 0 
		MOV CL, COLS 
		PROCROOWLOOP:
			MOV DECR, CL 
			
			MOV AL, 0
		
			MOV BX, 0 
			MOV CL, ROWS 
			PROCCOLUMNLOOP:
				
				CMP AL, MATRIX[BX][SI]
				JL FINDMAX
				JGE SAVE
				
				FINDMAX:
					MOV AL, MATRIX[BX][SI]
					MOV MAXNUMBER, BX
					
				SAVE:
				ADD BX, 9 
				
				LOOP PROCCOLUMNLOOP	
			
			MOV BX, MAXNUMBER
			MOV AL, MATRIX[0][SI]
			MOV DL, MATRIX[BX][SI]
			MOV MATRIX[BX][SI], AL
			MOV MATRIX[0][SI], DL 
	
			MOV CL, DECR 
			INC SI 
			
			LOOP PROCROOWLOOP
		
		
		
		
		
		CALL NEWLINE
		MOV AH, 9 
		MOV DX, OFFSET RESMSG
		INT 21H
		CALL NEWLINE
	
		
		
		; Вывод матрицы
		MOV SI, 0 
		MOV CL, ROWS 
		OUTROOWLOOP:
			MOV DECR, CL 
		
		
			MOV BX, 0 
			MOV CL, COLS 
			OUTCOLUMNLOOP:

				MOV DL, MATRIX[SI][BX]
				INC BX 
				
				MOV AH, 2
				INT 21H
				
				CALL PRINTSPACE
				
				LOOP OUTCOLUMNLOOP	


			CALL NEWLINE
	
			MOV CL, DECR 
			ADD SI, 9
			
			LOOP OUTROOWLOOP
		 

		MOV AX, 4C00H
		INT 21H
CODESEG ENDS
END MAIN

CMP MATRIX[SI][BX], '0'
				JE EXCHAHGE
				JNE SAVE
				
				EXCHAHGE: 
					MOV DI, 0
					
					MOV CL, ROWS
					EXCHAGELOOP:
						MOV AL, MATRIX[DI][BX]
						MOV MATRIX[SI][BX], AL
						
						ADD DI, 9
					
					LOOP EXCHAGELOOP
					
					MOV CL, 0
					
				SAVE: