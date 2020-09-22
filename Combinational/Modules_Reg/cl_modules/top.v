module top #( parameter DATA_WIDTH = 32) (
    input clk,
    input enable,
    input resetn,
    
    input sum_funct,
    input exp_funct,
    input red_funct,
    input carry_option,
    input grade_in, 
    input poly_red_in,
    input red_in,
    input in_a,
    input in_b,
    output out,
    output out_mult,
    output [DATA_WIDTH-1:0]     out_poly,         
    output                      sum_carry_out    
);

    wire [DATA_WIDTH-1:0] in_a_parallel;
    wire [DATA_WIDTH-1:0] in_b_parallel;
    wire [2*DATA_WIDTH-1:0] out_mult_result;

    wire [$clog2(DATA_WIDTH):0]     polyn_grade;
    wire [DATA_WIDTH:0]             polyn_red_in;
    wire [2*DATA_WIDTH-1:0]         reduc_in;
    wire [DATA_WIDTH-1:0]           result_out;

    input_regs #(DATA_WIDTH) input0 (
        .clk(clk),
        .resetn(resetn),
        .in_serial(in_a),
        .out_parallel(in_a_parallel)
    );

    input_regs #(DATA_WIDTH) input1 (
        .clk(clk),
        .resetn(resetn),
        .in_serial(in_b),
        .out_parallel(in_b_parallel)
    );

    input_regs #($clog2(DATA_WIDTH)+1) input2 (
        .clk(clk),
        .resetn(resetn),
        .in_serial(grade_in),
        .out_parallel(polyn_grade)
    );

    input_regs #(DATA_WIDTH+1) input3 (
        .clk(clk),
        .resetn(resetn),
        .in_serial(poly_red_in),
        .out_parallel(polyn_red_in)
    );

    input_regs #(2*DATA_WIDTH) input4 (
        .clk(clk),
        .resetn(resetn),
        .in_serial(red_in),
        .out_parallel(reduc_in)
    );

    output_regs #(2*DATA_WIDTH) output0 (
        .clk(clk),
        .resetn(resetn),
        .in_parallel(out_mult_result),
        .out_serial(out_mult)
    );

    output_regs #(DATA_WIDTH) output1 (
        .clk(clk),
        .resetn(resetn),
        .in_parallel(result_out),
        .out_serial(out)
    );

    cl_modules #(DATA_WIDTH) dut0(
        .clk(clk),
        .enable(enable),
        .sum_funct(sum_funct),
        .exp_funct(exp_funct),
        .red_funct(red_funct),
        .carry_option(carry_option),

        .polyn_grade(polyn_grade),
        .polyn_red_in(polyn_red_in),
        .reduc_in(reduc_in),
        
        .in_a(in_a_parallel),
        .in_b(in_b_parallel),
        .out(result_out),
        .mult_out(out_mult_result),
        .out_poly(out_poly),
        .sum_carry_out(sum_carry_out)
    );

endmodule