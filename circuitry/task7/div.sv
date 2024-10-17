`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 23.03.2024 13:01:38
// Design Name: 
// Module Name: div
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


module div(
    input clk,
    input reset,
    input [2:0] div,
    output logic q
    );
   
enum logic [2:0] { st0, st1, st2, st3, st4, st5, st6 } state;

always_ff @(posedge reset or posedge clk) begin
    if (reset)
        state <= st0;
    else
        case (state)
        st0: state <= st1;
        st1: if (div == 3'b010)
               state <= st0;
             else
                state <= st2;
        st2: if (div == 3'b011)
                state <= st0;
             else
                state <= st3;
        st3: if (div == 3'b100)
                state <= st0;
             else
                state <= st4;
        st4: if (div == 3'b101)
                state <= st0;
             else
                state <= st5;
        st5: if (div == 3'b110)
                state <= st0;
             else
                state <= st6;
        st6: state <= st0;
        endcase
        
  case(div)
               3'b100: assign q = ((state == st0) || (state == st1));
               3'b101: assign q = ((state == st0) || (state == st1));
               3'b110: assign q = ((state == st0) || (state == st1) || (state == st2));
               default: assign q = (state == st0);
               endcase      
end           
endmodule
