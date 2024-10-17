`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 13.04.2024 02:06:04
// Design Name: 
// Module Name: pr
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


module pr(
    input [7:0] a,
    input [7:0] b,
    input clk,
    input start,
    output logic ready,
    output logic [15:0] m
    );

logic [7:0] b_r, a_r;
logic [8:0] s;
logic [7:0] mh_r, ml_r;

enum logic [16:0] {idle, st0, st1, st2, st3, st4, st5, st6, st7} state = idle;

always_ff @(posedge clk)
    case (state)
        idle: if(start == 1'b0)
                    state <= idle;
              else
                    state <= st0;
        st0:        state <= st1;
        st1:        state <= st2;
        st2:        state <= st3;
        st3:        state <= st4;
        st4:        state <= st5;
        st5:        state <= st6;
        st6:        state <= st7;
        st7:        if (start == 1'b0)
                        state <= idle;
                    else
                        state <= st0;
    endcase;

always_ff @(posedge clk)
    ready <= (state == st7);

always_ff @(posedge clk)
    if (start) begin
        b_r <= b;
        a_r <= a;
    end else begin
        a_r <= {1'b0, a_r[7:1]};
    end

assign s = ((state == st0) ? 9'b0000_0000_0 : {1'b0, s[8:1]}) + ({8{a_r[0]}} & b_r);

always_ff @(posedge clk) begin
    mh_r <= s[8:1];
    ml_r <= {s[0], ml_r[7:1]};
end

assign m = {mh_r, ml_r};


endmodule

