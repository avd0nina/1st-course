`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 08.03.2024 16:02:19
// Design Name: 
// Module Name: adder_sim
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


module adder16_sim();
    logic [15:0]  a, b;
    logic cin, cout;
    logic [15:0] s;
    adder_16 DUT(.a(a), .b(b), .cin(cin), .cout(cout), .s(s));
    initial begin
        a = 16'b0; b = 16'b0; cin = 0; #10;
        a = 16'b0; b = 16'b0; cin = 1; #10;
        a = 16'b0; b = 16'hffff; cin = 0; #10;
        a = 16'b0; b = 16'hffff; cin = 1; #10;
        a = 16'hffff; b = 16'b0; cin = 0; #10;
        a = 16'hffff; b = 16'b0; cin = 1; #10;
        a = 16'hffff; b = 16'hffff; cin = 0; #10;
        a = 16'hffff; b = 16'hffff; cin = 1; #10;          
//    initial begin        
//        {cin, a, b} = 33'b0; #10;
//        repeat (65535) begin
//            {cin, a, b} = {cin, a, b} + 1; #10;
//        end
    $finish;
    end
endmodule

//module adder_sim();
    
//    logic [3:0] a, b;
//    logic cin, cout;
//    logic [3:0] s;
//    adder DUT(.a(a), .b(b), .cin(cin), .s(s), .cout(cout));
//    initial begin
//        {cin, a, b} = 9'b0; #10;
//        repeat (511) begin
//            {cin, a, b} = {cin, a, b} + 1; #10;
//        end
//    $finish;
//    end
//endmodule
