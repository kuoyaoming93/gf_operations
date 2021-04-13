module top (
    input carry_option,
    input [31:0] a,
    input [31:0] b,
    output [31:0] sum,
    output co
);

    cl_cla_adder dut0(
        .carry_option(carry_option),
        .a(a),
        .b(b),
        .sum(sum),
        .co(co)
    );


endmodule