`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 22.02.2024 21:09:31
// Design Name: 
// Module Name: shift
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


module muxer(
    input [7:0] in,
    input [2:0] sel,
    output logic q
    );
assign q = !sel[2] & !sel[1] & !sel[0] & in[0] |
           !sel[2] & !sel[1] & sel[0] & in[1] | 
           !sel[2] & sel[1] & !sel[0] & in[2] | 
           !sel[2] & sel[1] & sel[0] & in[3] | 
            sel[2] & !sel[1] & !sel[0] & in[4] | 
            sel[2] & !sel[1] & sel[0] & in[5] | 
            sel[2] & sel[1] & !sel[0] & in[6] | 
            sel[2] & sel[1] & sel[0] & in[7];   

endmodule

module shift(
    input [7:0] in,
    input [2:0] shift,
    output logic [7:0] q
    );
    
logic [23:0] sh;

assign sh[2:0] = shift;                                         
assign sh[5:3] = (sh[2:0] == 3'b111) ? 0 : sh[2:0] + 1;                                       
assign sh[8:6] = (sh[5:3] == 3'b111) ? 0 : sh[5:3] + 1;         
assign sh[11:9] = (sh[8:6] == 3'b111) ? 0 : sh[8:6] + 1;        
assign sh[14:12] = (sh[11:9] == 3'b111) ? 0 : sh[11:9] + 1;     
assign sh[17:15] = (sh[14:12] == 3'b111) ? 0 : sh[14:12] + 1;   
assign sh[20:18] = (sh[17:15] == 3'b111) ? 0 : sh[17:15] + 1;   
assign sh[23:21] = (sh[20:18] == 3'b111) ? 0 : sh[20:18] + 1;   



muxer M0(.in(in), .sel(sh[2:0]), .q(q[0]));
muxer M1(.in(in), .sel(sh[5:3]), .q(q[1]));
muxer M2(.in(in), .sel(sh[8:6]), .q(q[2]));
muxer M3(.in(in), .sel(sh[11:9]), .q(q[3]));
muxer M4(.in(in), .sel(sh[14:12]), .q(q[4]));
muxer M5(.in(in), .sel(sh[17:15]), .q(q[5]));
muxer M6(.in(in), .sel(sh[20:18]), .q(q[6]));
muxer M7(.in(in), .sel(sh[23:21]), .q(q[7]));

endmodule
