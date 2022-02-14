// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Fill.asm

// Runs an infinite loop that listens to the keyboard input.
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel;
// the screen should remain fully black as long as the key is pressed. 
// When no key is pressed, the program clears the screen, i.e. writes
// "white" in every pixel;
// the screen should remain fully clear as long as no key is pressed.

// Put your code here.
(LOOP)
  @KBD
  D=M

  @ON
  D;JGT

  @OFF
  0;JMP

(ON)
  @R0
  M=-1

  @DRAW
  0;JMP

(OFF)
  @R0
  M=0

  @DRAW
  0;JMP

(DRAW)
  // Draw every single bit in screen memory address space
  @8191 // total number of screen address bits
  D=A
  @R1
  M=D

  (NEXT)
    // calculate the position
    @R1
    D=M
    @pos
    M=D
    @SCREEN
    D=A
    @pos
    M=M+D //Add base screen address to curr position

    // Draw the value at pos' current address
    @R0
    D=M
    @pos
    A=M
    M=D

    // Decrement the counter
    @R1
    D=M-1
    M=D

    @NEXT
    D;JGE

  // Loop back around
  @LOOP
  0;JMP

