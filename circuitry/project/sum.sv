module sum(
    input logic [13:0] first_num,
    input logic [13:0] second_num,
    output logic [13:0] result
);

reg [14:0] carry;

always @* begin
    result = 0;
    carry = 0;
    
    for (integer i = 0; i < 14; i++) begin
        result[i] = first_num[i] ^ second_num[i] ^ carry;
        carry = (first_num[i] & second_num[i]) | (carry & (first_num[i] ^ second_num[i]));
    end
end

endmodule
