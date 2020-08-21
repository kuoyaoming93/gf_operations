module top #(
    parameter DATA_WIDTH = 32
) (
    input clk,
    input resetn,
    input enable,
    input a,
    input b,
    output sum,
    output out_carry
);
    wire [DATA_WIDTH-1:0] in_sum_a;
    wire [DATA_WIDTH-1:0] in_sum_b;
    wire [DATA_WIDTH-1:0] out_sum_result;

    input_regs #(DATA_WIDTH) input0 (
        .clk(clk),
        .resetn(resetn),
        .in_serial(a),
        .out_parallel(in_sum_a)
    );

    input_regs #(DATA_WIDTH) input1 (
        .clk(clk),
        .resetn(resetn),
        .in_serial(b),
        .out_parallel(in_sum_b)
    );

    output_regs #(DATA_WIDTH) output0 (
        .clk(clk),
        .resetn(resetn),
        .in_parallel(out_sum_result),
        .out_serial(sum)
    );

    rca_adder #(DATA_WIDTH) dut0 (
        .clk(clk),
        .enable(enable),
        .in_sum_a(in_sum_a),
        .in_sum_b(in_sum_b),
        .out_sum_result(out_sum_result),
        .out_carry(out_carry)
    );

endmodule

