module top (
    input [31:0]    a,
    input [31:0]    b,
    output [31:0]   sum,
    output [31:0]   sum2
);

    rca_adder dut0(
        .a(a),
        .b(b),
        .sum(sum)
    );

    normal_adder dut1(
        .a(a),
        .b(b),
        .sum(sum2)
    );

endmodule