module tb_brain();

logic [13:0] first_digit;
logic [13:0] second_digit;
logic [1:0] operation;
logic [13:0] result;
brain ccc(first_digit, second_digit, operation, result);

initial begin
$display("Running testbench");
first_digit = 1;
second_digit = 0;
operation = 1;
#5
first_digit = 1;
second_digit = 0;
operation = 2;
#5
first_digit = 1;
second_digit = 0;
operation = 0;
#5
first_digit = 10;
second_digit = 5;
operation = 1;
#5
first_digit = 10;
second_digit = 5;
operation = 2;
#5
first_digit = 10;
second_digit = 5;
operation = 0;
#5
$finish;
end

endmodule
