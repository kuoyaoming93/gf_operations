module top #(
    parameter DATA_WIDTH = 32
) (
    input clk,
    input resetn,
    input dummy
);
    wire    [DATA_WIDTH-1:0]    in_sum_a;
    wire    [DATA_WIDTH-1:0]    in_sum_b;
    wire    [DATA_WIDTH-1:0]    out_sum_result;

    rca_adder dut0(
        .clk(clk),
        .resetn(resetn),
        .in_sum_a(in_sum_a),
        .in_sum_b(in_sum_b),
        .out_sum_result(out_sum_result)
    );

endmodule

