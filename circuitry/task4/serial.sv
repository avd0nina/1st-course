`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 08.03.2024 16:05:33
// Design Name: 
// Module Name: serial
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


module serial(
    input [1:0] a,
    input [1:0] b,
    output greater,
    output less
    );
assign greater = a[1] & !b[1]
        | a[1] & b[1] & a[0] & !b[0]
        | !a[1] & !b[1] & a[0] & !b[0];
assign less = !a[1] & b[1]
        | a[1] & b[1] & !a[0] & b[0]
        | !a[1] & !b[1] & !a[0] & b[0];
        
endmodule
module compare(
    input [7:0] a,
    input [7:0] b,
    output GREATER,
    output LESS
);

logic [5:0] g, l;
//serial CMP0(.a(a[1:0]), .b(b[1:0]), .greater(g[0]), .less(l[0]));
//serial CMP1(.a(a[3:2]), .b(b[3:2]), .greater(g[1]), .less(l[1]));
//serial CMP2(.a(a[5:4]), .b(b[5:4]), .greater(g[2]), .less(l[2]));
//serial CMP3(.a(a[7:6]), .b(b[7:6]), .greater(g[3]), .less(l[3]));
//serial CMP4(.a(g[1:0]), .b(l[1:0]), .greater(g[4]), .less(l[4]));
//serial CMP5(.a(g[3:2]), .b(l[3:2]), .greater(g[5]), .less(l[5]));
//serial CMP6(.a(g[5:4]), .b(l[5:4]), .greater(GREATER), .less(LESS));

//serial CMP0(.a(a[1:0]), .b(b[1:0]), .greater(g[0]), .less(l[0]));
//serial CMP1(.a({a[2], g[0]}), .b({b[2], l[0]}), .greater(g[1]), .less(l[1]));
//serial CMP2(.a({a[3], g[1]}), .b({b[3], l[1]}), .greater(g[2]), .less(l[2]));
//serial CMP3(.a({a[4], g[2]}), .b({b[4], l[2]}), .greater(g[3]), .less(l[3]));
//serial CMP4(.a({a[5], g[3]}), .b({b[5], l[3]}), .greater(g[4]), .less(l[4]));
//serial CMP5(.a({a[6], g[4]}), .b({b[6], l[4]}), .greater(g[5]), .less(l[5]));
//serial CMP6(.a({a[7], g[5]}), .b({b[7], l[5]}), .greater(GREATER), .less(LESS));

//serial CMP6(.a(a[1:0]), .b(b[1:0]), .greater(g[0]), .less(l[0]));

//genvar i;
//generate
//    for(i = 0; i < 4; i = i+1)
//    begin: label1
//        serial CMP(.a(a[i^2+1:i^2]), .b(b[i^2+1:i^2]), .greater(g[i]), .less(l[i]));
//    end
//endgenerate

//generate
//    for(i = 0; i < 2; i = i+1)
//    begin: label2
//        serial CMP(.a(g[i^2+1:i^2]), .b(l[i^2+1:i^2]), .greater(g[i+4]), .less(l[i+4]));
//    end
//endgenerate

//serial CMP0(.a(a[5:4]), .b(b[5:4]), .greater(g[0]), .less(l[0]));

serial CMP0(.a(a[1:0]), .b(b[1:0]), .greater(g[0]), .less(l[0]));
genvar i; 
generate 
    for(i = 0; i < 5; i = i+1) 
    begin: label 
        logic greater_i, less_i; 
        serial CMP(.a({a[i+2], g[i]}), .b({b[i+2], l[i]}), .greater(greater_i), .less(less_i)); 
        assign g[i+1] = greater_i; 
        assign l[i+1] = less_i; 
    end 
endgenerate

serial CMP2(.a({a[7], g[5]}), .b({b[7], l[5]}), .greater(GREATER), .less(LESS));
endmodule
