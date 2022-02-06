// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Mult.asm

// Multiplies R0 and R1 and stores the result in R2.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)
//
// This program only needs to handle arguments that satisfy
// R0 >= 0, R1 >= 0, and R0*R1 < 32768.

// Put your code here.
// sum=0,i=R1
// let sum = sum + R0. Repeat i times.
// If R1 or R0 is zero, R2 is zero.

@R1
D=M
@i
M=D
@sum
M=0

(LOOP)
@i
D=M
@STOP
D;JEQ // if i == 0 goto END

@R0
D=M
@sum
M=D+M // sum = sum + R0

@i
D=M
M=D-1 // i = i - 1
@LOOP
0;JMP

(STOP)
@sum
D=M
@R2
M=D

(END)
@END
0;JMP
