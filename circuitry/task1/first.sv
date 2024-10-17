`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 03.02.2024 13:41:08
// Design Name: 
// Module Name: first
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


module first(
    input a,
    input b,
    input cin,
    output s,
    output cout
    );
    assign cout = ((!a)& b & cin) | (a & (!b) & cin) | (a & b & (!cin)) | (a & b & cin);
    assign s = ((!a) & (!b) & cin) | ((!a) & b & (!cin)) | (a & (!b) & (!cin)) | (a & b & cin);
endmodule





