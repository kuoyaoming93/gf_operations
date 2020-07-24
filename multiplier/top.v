module top #( parameter DATA_WIDTH = 32) (
    input [DATA_WIDTH-1:0] a,
    input [DATA_WIDTH-1:0] b,
    output [2*DATA_WIDTH-1:0] out
);

    rca_mult #(DATA_WIDTH) dut0(
        .a(a),
        .b(b),
        .out(out)
    );

endmodule