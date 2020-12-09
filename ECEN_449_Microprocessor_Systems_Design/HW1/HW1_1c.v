`timescale 1ns / 1ps

module HW1_1c(e, f, a, b, c, d);
    input a, b, c, d;					//define inputs
    output e, f;						//define outputs
    
    assign e = ~a | ((a & b) | c);		//dataflow for output e. Not a or z
    assign f = ~(d & ((a & b) | c)); 	//dataflow for output f. D nand z

endmodule

