module top (
    input carry_option,
    input [31:0] a,
    input [31:0] b,
    output [31:0] sum,
    output [31:0] sum2,
    output [31:0] sum3
);

    cl_rca_adder cl_add0(
        .carry_option(carry_option),
        .a(a),
        .b(b),
        .sum(sum)
    );

    rca_adder add0 (
        .a(a),
        .b(b),
        .sum(sum2)
    );

    cl_add gf0 (
        .a(a),
        .b(b),
        .sum(sum3)
    );


endmodule