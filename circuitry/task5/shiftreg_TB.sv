`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 09.03.2024 12:57:27
// Design Name: 
// Module Name: shiftreg_TB
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


module shiftreg_TB();
logic [7:0] d, q;
logic clk, load, sin;

shiftreg DUT(.clk(clk), .load(load), .sin(sin), .d(d), .q(q));

always begin
    clk = 0; #5;
    clk = 1; #5;
end

initial begin
    load = 1; d = 8'haa;sin = 0; #10;
    load = 0;           sin = 0; #10;
                        sin = 1; #10;
                        sin = 0; #10;
                        sin = 1; #10;
                        sin = 0; #10;
                        sin = 1; #10;
                        sin = 0; #10;
                        sin = 1; #10;
$finish;
end

endmodule
