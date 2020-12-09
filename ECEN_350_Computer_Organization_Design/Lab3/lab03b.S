.section .text
.globl lab03b

lab03b:
	MOVZ X1, #10		//make X1 = 10
	ADD X0, XZR, XZR	//make X0 = 0
	ADRP X3, UIN
	ADD X3, X3, :lo12:UIN//get address of UIN variable
	LDUR X4, [X3, 0] 	//load data from UIN's address

loop:
	SUB X2, X1, X0		//10-i
	CBZ X2, endloop		//i<10
	SUB X4, X4, #1		//UIN = UIN-1
	ADD X0, X0, #1		//i++
B loop

endloop:
	STUR X4, [X3, 0]  //put data of UIN back into it's address
	BR X30				//return back to main

.section .data
	UIN: .word 0x0028
