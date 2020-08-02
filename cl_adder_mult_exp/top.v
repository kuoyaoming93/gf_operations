module top #( parameter DATA_WIDTH = 32) (
    input sum_funct,
    input exp_funct,
    input carry_option,
    input [DATA_WIDTH-1:0] a,
    input [DATA_WIDTH-1:0] b,
    output [DATA_WIDTH-1:0] out,
    output [2*DATA_WIDTH-1:0] mult_out
);

    rca_add_mult_exp #(DATA_WIDTH) dut0(
        .sum_funct(sum_funct),
        .exp_funct(exp_funct),
        .carry_option(carry_option),
        .a(a),
        .b(b),
        .out(out),
        .mult_out(mult_out)
    );

endmodule