`timescale 1ns / 1ps

module HW1_1d(e, f, a, b, c, d);
    input a, b, c, d;					//define inputs
    output e, f;						//define outputs
    reg e, f;							//make output reg to be assigned in always block
    
    always@(a or b or c or d)			//sensitive to change of inputs
    begin
        e = ~a | ((a & b) | c);			//assign output e. Not A or Z
        f = ~(d & ((a & b) | c));		//assign output f. D nand z
    end    

endmodule

