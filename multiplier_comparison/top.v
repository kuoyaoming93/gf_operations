module top #( parameter DATA_WIDTH = 32) (
    input gf_option,
    input [DATA_WIDTH-1:0] a,
    input [DATA_WIDTH-1:0] b,
    output [2*DATA_WIDTH-1:0] out,
    output [2*DATA_WIDTH-1:0] out2,
    output [2*DATA_WIDTH-1:0] out3,
    output [2*DATA_WIDTH-1:0] out4
);

    gf_rca_mult #(DATA_WIDTH) dut0(
        .gf_option(gf_option),
        .a(a),
        .b(b),
        .out(out)
    );

    gf_mult #(DATA_WIDTH) dut1(
        .a(a),
        .b(b),
        .out(out2)
    );

    rca_mult #(DATA_WIDTH) dut2(
        .a(a),
        .b(b),
        .out(out3)
    );

    gf_rca_mult_bis #(DATA_WIDTH) dut3(
        .gf_option(gf_option),
        .a(a),
        .b(b),
        .out(out4)
    );

endmodule