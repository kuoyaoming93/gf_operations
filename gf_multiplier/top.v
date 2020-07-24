module top #( parameter DATA_WIDTH = 32) (
    input gf_option,
    input [DATA_WIDTH-1:0] a,
    input [DATA_WIDTH-1:0] b,
    output [2*DATA_WIDTH-1:0] out
);

    gf_rca_mult #(DATA_WIDTH) dut0(
        .gf_option(gf_option),
        .a(a),
        .b(b),
        .out(out)
    );

endmodule