module gf_full_adder(
    input gf_option,
    input a,
    input b,
    input ci,
    output sum,
    output co
);

assign sum = a ^ b ^ ci;
assign co = gf_option ? (a & b) | (a & ci) | (b & ci) : 1'b0;

endmodule