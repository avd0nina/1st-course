`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 12.05.2024 20:18:28
// Design Name: 
// Module Name: main
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


module main(
    input [7:0] in,
    output logic [6:0] out
    );
    
    always_comb
    if (!in[0])
        out = 7'b1111110;
    else if (in[1])
        out = 7'b0110000;
    else if (!in[2])
        out = 7'b1101101;
    else if (!in[3])
        out = 7'b1111001;
    else if (!in[4])
        out = 7'b0110011;
    else if (!in[5])
        out = 7'b1011011;
    else if (!in[6])
        out = 7'b1011111;
    else   
        out = 7'b0000001;  
    
endmodule

