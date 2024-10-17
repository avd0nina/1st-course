module subb(
    input logic [13:0] first_num,
    input logic [13:0] second_num,
    output logic [13:0] result
);

reg [14:0] borrow;

always @* begin
    result = 0;
    borrow = 0;

    for (integer i = 0; i < 14; i++) begin
        result[i] = first_num[i] ^ second_num[i] ^ borrow;
        borrow = (~first_num[i] & second_num[i]) | (~first_num[i] & borrow) | (second_num[i] & borrow);
    end
end

endmodule
