`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 09.03.2024 12:43:39
// Design Name: 
// Module Name: shiftreg
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module shiftreg(
    input clk,
    input load,
    input [7:0] d,
    input sin,
    output logic [7:0] q
    );
    
always_ff @(posedge clk)
    if (load == 1'b1)
        q <= d;
    else 
        q <= {q[6:0], sin};
        
endmodule
