`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 16.02.2024 00:52:02
// Design Name: 
// Module Name: prcoder_TB
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


module prcoder_TB();
logic [7:0] in;
logic [2:0] code;

prcoder DUT(.code(code), .in(in));

initial begin
    in = 0; #10;
    repeat (255) begin
        in = in + 1; #10;
    end
$finish;
end

endmodule
