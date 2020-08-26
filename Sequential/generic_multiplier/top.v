module top #( parameter DATA_WIDTH = 2) (
    input                           clk,
    input                           resetn,
    input                           enable,
    input [$clog2(DATA_WIDTH):0]    in_width,
    input                           in_a,
    input                           in_b,
    output                          out_mult,
    output                          finish
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

    mult #(DATA_WIDTH) dut0(
        .clk(clk),
        .op_enable(enable),
        .in_width(in_width),
        .in_mult_a(in_mult_a),
        .in_mult_b(in_mult_b),
        .out_mult_result(out_mult_result),
        .op_finish(finish)
    );

endmodule