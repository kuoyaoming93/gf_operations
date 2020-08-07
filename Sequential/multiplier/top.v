module top #( parameter DATA_WIDTH = 32) (
    input                           clk,
    input                           resetn,
    input                           in_a,
    input                           in_b,
    output                          out_mult
);

    wire [DATA_WIDTH-1:0] in_mult_a;
    wire [DATA_WIDTH-1:0] in_mult_b;
    wire [2*DATA_WIDTH-1:0] out_mult_result;

    input_regs #(DATA_WIDTH) input0 (
        .clk(clk),
        .resetn(resetn),
        .in_serial(in_a),
        .out_parallel(in_mult_a)
    );

    input_regs #(DATA_WIDTH) input1 (
        .clk(clk),
        .resetn(resetn),
        .in_serial(in_b),
        .out_parallel(in_mult_b)
    );

    output_regs #(2*DATA_WIDTH) output0 (
        .clk(clk),
        .resetn(resetn),
        .in_parallel(out_mult_result),
        .out_serial(out_mult)
    );

    rca_mult #(DATA_WIDTH) dut0(
        .clk(clk),
        .enable(1'b1),
        .in_mult_a(in_mult_a),
        .in_mult_b(in_mult_b),
        .out_mult_result(out_mult_result)
    );

endmodule