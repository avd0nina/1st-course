`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 08.03.2024 16:01:38
// Design Name: 
// Module Name: adder
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


module adder_16(
    input [15:0] a,
    input [15:0] b,
    input cin,
    output cout,
    output [15:0] s
    );
    
    logic [3:0] p, g;
    logic [4:0] c;
    assign cout = c[4];
    cla m0(.p(p), .g(g), .cin(cin), .c(c[4:0]));
    genvar i;
    generate for (i = 0; i < 4; i = i + 1)
        begin: label
            adder M(.a(a[4*i+3 : 4*i]), .b(b[4*i+3 : 4*i]), 
                    .cin(c[i]), .p_g(p[i]), .g_g(g[i]), 
                    .cout(cout), .s(s[4*i+3 : 4*i]));
        end
    endgenerate
    
endmodule

module adder(
    input [3:0] a,
    input [3:0] b,
    input cin,
    output p_g,
    output g_g,
    output cout,
    output [3:0] s
    );
    logic [3:0] p, g;
    logic [4:0] c;
    assign cout = c[4];
    cla m0(.p(p), .g(g), .cin(cin), .c(c[4:0]), 
           .p_g(p_g), .g_g(g_g));
    genvar i;
    generate for (i = 0; i < 4; i = i + 1)
        begin: label
            assign p[i] = a[i] ^ b[i];
            assign g[i] = a[i] & b[i];
            assign s[i] = a[i] ^ b[i] ^ c[i];
        end
    endgenerate
    
endmodule

module cla(
    input [3:0] p,
    input [3:0] g,
    input cin,
    output p_g,
    output g_g,
    output [4:0] c
    );
    assign c[0] = cin;
    
    assign c[1] = g[0]
                | p[0] & cin;
                
    assign c[2] = g[1]
                | p[1] & g[0]
                | p[1] & p[0] & cin;
    
    assign c[3]  = g[2]
                 | p[2] & g[1]
                 | p[2] & p [1] & g[0]
                 | p[2] & p [1] & p[0] & cin;
                 
    assign c[4] = g[3] 
                | p[3] & g[2]
                | p[3] & p[2] & g[1]
                | p[3] & p[2] & p[1] & g[0] 
                | p[3] & p[2] & p[1] & p[0] & cin;
    assign p_g = p[3] & p[2] & p[1] & p[0];
    assign g_g = g[3] 
               | p[3] & g[2]
               | p[3] & p[2] & g[1]
               | p[3] & p[2] & p[1] & g[0];
    

endmodule
