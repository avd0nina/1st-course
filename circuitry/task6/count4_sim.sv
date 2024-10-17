`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 21.03.2024 03:15:34
// Design Name: 
// Module Name: count4_sim
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


module count4_sim();
logic [3:0] q;
logic clk;
logic lever;

count4 DUT(.q(q), .clk(clk), .lever(lever));

always begin
    clk = 0; #5;
    clk = 1; #5;
end

initial begin
    lever = 1; #200;
    lever = 0; #200;
$finish;
end
endmodule
