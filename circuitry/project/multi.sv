module multi(
    input logic [13:0] first_num,
    input logic [13:0] second_num,
    output logic [13:0] result
);

always @* begin
    result = 14'h0;

    for (integer i = 0; i < 16; i = i + 1) begin
        if (second_num[i] == 1) begin
            result = result + (first_num << i);
        end
    end
end

endmodule
