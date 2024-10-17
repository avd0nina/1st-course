`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 18.04.2024 21:58:31
// Design Name: 
// Module Name: prcssr
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


module prcssr(
    input clk,
    input [3:0] a,
    input [3:0] b,
    output logic [7:0] m
    );
  
//----Memory----------
logic [7:0] ram [255:0];

initial $readmemb ("memory.mem", ram, 0, 255);

always @(posedge clk)
    m <= ram[{a, b}];

endmodule
