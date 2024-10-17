`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 13.04.2024 02:07:07
// Design Name: 
// Module Name: pr_TB
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


module pr_TB();

logic clk, start, ready;
logic [7:0] a, b;
logic [15:0] m;

pr DUT(.a(a), .b(b), .clk(clk), .start(start), .ready(ready), .m(m));

always begin
    clk = 0; #5;
    clk = 1; #5;
end

initial begin
    {a, b} = 16'b0000_0000_0000_0000;   start = 1; #10;
                             start = 0; #120;
    repeat(65535) begin
        {a, b} = {a, b} + 1; start = 1; #10;
                             start = 0; #120;
    end
    #120;
$finish;
end

endmodule
