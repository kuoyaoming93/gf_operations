module gf_half_adder(
    input gf_option,
    input a,
    input b,
    output sum,
    output co
);

assign sum = a ^ b;
assign co = gf_option ? a & b : 1'b0;

endmodule