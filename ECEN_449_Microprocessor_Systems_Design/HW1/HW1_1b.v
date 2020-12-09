`timescale 1ns / 1ps

module HW1_1b(e, f, a, b, c, d);
    input a, b, c, d;		//define inputs
    output e, f;			//define outputs
    wire x, y, z;			//intermediate wires
    
    not NOT2(x, a);			//assign x wire
    and AND2(y, a, b);		//assign y wire
    or OR2(z, y, c);		//assign z wire
    or OR1(e, x, z);		//assign e output
    nand NAND2(f, z, d);	//assign f output   
    
endmodule

