`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 08.03.2024 16:06:24
// Design Name: 
// Module Name: cmp_sim
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


module cmp_sim();
    logic [7:0] a,b;
    logic GREATER, LESS;
compare DUT(.a(a), .b(b), .GREATER(GREATER), .LESS(LESS));

initial begin
    $monitor($time, " a = %b, b = %b, GREATER = %b, LESS = %b", a, b, GREATER, LESS);
    {a, b} = 16'b0000_0000_0000_0000; #10;
    repeat (65535) begin
        {a, b} = {a, b} + 1; #10;
    end   
$finish;
end  
endmodule
