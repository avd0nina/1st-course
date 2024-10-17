module brain(
    input logic [13:0] first_digit,
    input logic [13:0] second_digit,
    input logic [1:0] operation,
    output logic [13:0] result
);

logic [13:0] mul_result;
logic [13:0] sum_result;
logic [13:0] sub_result;

multi mul_mod(
    .first_num(first_digit),
    .second_num(second_digit),
    .result(mul_result)
);

sum sum_mod(
    .first_num(first_digit),
    .second_num(second_digit),
    .result(sum_result)
);

subb sub_mod(
    .first_num(first_digit),
    .second_num(second_digit),
    .result(sub_result)
);

always @* begin
    result = 0;
    
    case (operation)
        2'b00: result = mul_result;
        2'b01: result = sum_result;
        2'b10: result = sub_result;
    endcase
end

endmodule
