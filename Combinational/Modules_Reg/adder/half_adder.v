`timescale 1 ns / 1 ps

module half_adder(
    input a,
    input b,
    output sum,
    output co
);

assign sum = a ^ b;
assign co = a & b;

endmodule