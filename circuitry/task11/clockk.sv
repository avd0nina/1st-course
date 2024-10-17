`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 12.05.2024 20:26:27
// Design Name: 
// Module Name: clockk
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


module digits(
    input [3:0] cnt,
    output logic [6:0] Out
);

always_comb begin
    case(cnt)
    4'b0000: Out = 7'b1111110;
    4'b0001: Out = 7'b0110000;
    4'b0010: Out = 7'b1101101;
    4'b0011: Out = 7'b1111001;
    4'b0100: Out = 7'b0110011;
    4'b0101: Out = 7'b1011011;
    4'b0110: Out = 7'b1011111;
    4'b0111: Out = 7'b1110000;
    4'b1000: Out = 7'b1111111;
    4'b1001: Out = 7'b1111011;
    default: Out = 7'b1111111;
   
    endcase
    end
    
endmodule


module clock(
    input  clk,  
    input  In,  
    output [6:0] Dig0,      
    output [6:0] Dig1,   
    output [6:0] Dig2,   
    output [6:0] Dig3    
    
);

logic [3:0] sec1 = 0;
logic [3:0] sec2 = 0;  
logic [3:0] min1 = 0;
logic [3:0] min2 = 0;

logic [23:0] count;  
logic vb = 0;

always_comb
    if(!In) begin
        if (vb == 0)
            vb <= 1;
        else
            vb <= 0;
    end
always @(posedge clk) begin
    
    if(vb)// begin
        count <= count + 1;
      
    if (count == 11999999) begin 
        count <= 0;
        sec1 <= sec1 + 1;
        if (sec1 == 9) begin
            sec1 <= 4'b0000;
            sec2 <= sec2 + 1;
            if (sec2 == 5) begin
                sec2 <= 4'b0000;
                min1 <= min1 + 1;
                if (min1 == 9) begin
                    min1 <= 4'b0000;
                    min2 <= min2 + 1;
                    if(min2 == 5) begin
                        min2 <= 4'b0000;
                    end 
                end        
            end
        end
    end
end


digits S1(.cnt(sec1), .Out(Dig3)); 
digits S2(.cnt(sec2), .Out(Dig2)); 
digits S3(.cnt(min1), .Out(Dig1)); 
digits S4(.cnt(min2), .Out(Dig0));    

endmodule
