module top #( parameter DATA_WIDTH = 32) (
    input clk,
    input resetn,
    input enable,
    input grade_in,
    input poly_red_in,
    input red_in,
    output out
);

    wire [$clog2(DATA_WIDTH):0]     polyn_grade;
    wire [DATA_WIDTH:0]             polyn_red_in;
    wire [2*DATA_WIDTH-1:0]         reduc_in;
    wire [DATA_WIDTH-1:0]           result_out;

    input_regs #($clog2(DATA_WIDTH)+1) input0 (
        .clk(clk),
        .resetn(resetn),
        .in_serial(grade_in),
        .out_parallel(polyn_grade)
    );

    input_regs #(DATA_WIDTH+1) input1 (
        .clk(clk),
        .resetn(resetn),
        .in_serial(poly_red_in),
        .out_parallel(polyn_red_in)
    );

    input_regs #(2*DATA_WIDTH) input2 (
        .clk(clk),
        .resetn(resetn),
        .in_serial(red_in),
        .out_parallel(reduc_in)
    );

    output_regs #(DATA_WIDTH) output0 (
        .clk(clk),
        .resetn(resetn),
        .in_parallel(result_out),
        .out_serial(out)
    );

    reduction #(DATA_WIDTH) dut0(
        .clk(clk),
        .enable(enable),
        .polyn_grade(polyn_grade),
        .polyn_red_in(polyn_red_in),
        .reduc_in(reduc_in),
        .out(result_out)
    );

endmodule