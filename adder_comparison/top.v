module top (
    input gf_option,
    input [31:0] a,
    input [31:0] b,
    output [31:0] sum,
    output [31:0] sum2,
    output [31:0] sum3
);

    gf_rca_adder gf_add0(
        .gf_option(gf_option),
        .a(a),
        .b(b),
        .sum(sum)
    );

    rca_adder add0 (
        .a(a),
        .b(b),
        .sum(sum2)
    );

    gf_add gf0 (
        .a(a),
        .b(b),
        .sum(sum3)
    );


endmodule