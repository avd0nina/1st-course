`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 23.03.2024 13:26:36
// Design Name: 
// Module Name: div_TB
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


module div_TB();

logic clk, reset;
logic [2:0] div;
logic q;

div DUT(.clk(clk), .reset(reset), .div(div), .q(q));

always begin
    clk = 1'b0; #5;
    clk = 1'b1; #5;
end

initial begin 
    reset = 0; div = 3'b000; #10;
    reset = 1; div = 3'b000; #10;
    reset = 0; div = 3'b010; #200;
               div = 3'b011; #200;
               div = 3'b100; #200;
               div = 3'b101; #200;
               div = 3'b110; #200;
               div = 3'b111; #200;
$finish;
end

endmodule
