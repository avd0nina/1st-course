`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 18.04.2024 21:59:24
// Design Name: 
// Module Name: prcssr_sim
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


module prcssr_sim();
logic clk;
logic [3:0] a;
logic [3:0] b;
logic [7:0] m;

prcssr DUT(.clk(clk), .a(a), .b(b), .m(m));

parameter PERIOD = 10;

always begin
    clk = 1'b0; #(PERIOD/2);
    clk = 1'b1; #(PERIOD/2);
end

initial begin
    {a, b} = 8'b0000_0000; #PERIOD;
    repeat (255) begin
        {a, b} = {a, b} + 1; #PERIOD;
    end
$finish;
end

endmodule
