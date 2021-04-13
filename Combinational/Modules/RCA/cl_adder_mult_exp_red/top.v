module top #( parameter DATA_WIDTH = 32) (
    input sum_funct,
    input exp_funct,
    input red_funct,
    input carry_option,
    input [DATA_WIDTH:0] polyn_red_in,

    input [2*DATA_WIDTH-1:0] reduc_in,
    input [DATA_WIDTH-1:0] a,
    input [DATA_WIDTH-1:0] b,
    output [DATA_WIDTH-1:0] out,
    output [2*DATA_WIDTH-1:0] mult_out
);

    rca_add_mult_exp_red #(DATA_WIDTH) dut0(
        .sum_funct(sum_funct),
        .exp_funct(exp_funct),
        .red_funct(red_funct),
        .carry_option(carry_option),
        .polyn_red_in(polyn_red_in),

        .reduc_in(reduc_in),
        .a(a),
        .b(b),
        .out(out),
        .mult_out(mult_out)
    );

endmodule