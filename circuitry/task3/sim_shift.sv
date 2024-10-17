`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 22.02.2024 21:11:15
// Design Name: 
// Module Name: sim_shift
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


module sim_shift();
logic [7:0] in;
logic [2:0] shift;
logic [7:0] q;

shift DUT(.in(in), .shift(shift), .q(q));

initial begin
    in = 8'b00000001; shift = 0; #10;
    repeat (7) begin
        shift = shift + 1; #10; 
    end    
    repeat (7) begin
        in = in << 1; shift = 0; #10;
        repeat (7) begin
            shift = shift + 1; #10;
        end
    end    
$finish;
end
endmodule