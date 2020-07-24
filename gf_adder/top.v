module top (
    input gf_option,
    input [31:0] a,
    input [31:0] b,
    output [31:0] sum,
    output co
);

    gf_rca_adder dut0(
        .gf_option(gf_option),
        .a(a),
        .b(b),
        .sum(sum),
        .co(co)
    );


endmodule