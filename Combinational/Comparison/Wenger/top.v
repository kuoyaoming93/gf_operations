module top #( parameter DATA_WIDTH = 32) (
    input clk,
    input enable,
    input resetn,

    input carry_option,
    input sum_funct,
    input exp_funct,
    input red_funct,
    
    input in_a,
    input in_b,

    input polyn_grade,
    input polyn_red_in,   
    input reduc_in,

    output out_sum,
    output out_mult_result,
    output out_poly,
    output out_poly_c,
    output out_sum_c,
    output out_carry_c,
    output out_mult_result_c
);

    wire [DATA_WIDTH-1:0]           in_a_p;
    wire [DATA_WIDTH-1:0]           in_b_p;
    wire [DATA_WIDTH-1:0]           out_sum_p;
    wire [2*DATA_WIDTH-1:0]         out_mult_p;

    wire [$clog2(DATA_WIDTH):0]     polyn_grade_p;
    wire [DATA_WIDTH:0]             polyn_red_in_p;       
    wire [2*DATA_WIDTH-1:0]         reduc_in_p;           
    wire [DATA_WIDTH-1:0]           out_poly_p;         

    wire [DATA_WIDTH-1:0]           out_sum_c_p; 
    wire [DATA_WIDTH-1:0]           out_poly_c_p;     
    wire [2*DATA_WIDTH-1:0]         out_mult_c_p;

    //==================================================
    // Shift Registers
    //==================================================

    input_regs #(DATA_WIDTH) input0 (
        .clk(clk),
        .resetn(resetn),
        .in_serial(in_a),
        .out_parallel(in_a_p)
    );

    input_regs #(DATA_WIDTH) input1 (
        .clk(clk),
        .resetn(resetn),
        .in_serial(in_b),
        .out_parallel(in_b_p)
    );

    input_regs #($clog2(DATA_WIDTH)+1) input2 (
        .clk(clk),
        .resetn(resetn),
        .in_serial(polyn_grade),
        .out_parallel(polyn_grade_p)
    );

    input_regs #(DATA_WIDTH+1) input3 (
        .clk(clk),
        .resetn(resetn),
        .in_serial(polyn_red_in),
        .out_parallel(polyn_red_in_p)
    );

    input_regs #(2*DATA_WIDTH) input4 (
        .clk(clk),
        .resetn(resetn),
        .in_serial(reduc_in),
        .out_parallel(reduc_in_p)
    ); 

    output_regs #(DATA_WIDTH) output0 (
        .clk(clk),
        .resetn(resetn),
        .in_parallel(out_sum_p),
        .out_serial(out_sum)
    );

    output_regs #(2*DATA_WIDTH) output1 (
        .clk(clk),
        .resetn(resetn),
        .in_parallel(out_mult_p),
        .out_serial(out_mult_result)
    );

    output_regs #(DATA_WIDTH) output2 (
        .clk(clk),
        .resetn(resetn),
        .in_parallel(out_poly_p),
        .out_serial(out_poly)
    );

    output_regs #(DATA_WIDTH) output3 (
        .clk(clk),
        .resetn(resetn),
        .in_parallel(out_sum_c_p),
        .out_serial(out_sum_c)
    );

    output_regs #(DATA_WIDTH) output4 (
        .clk(clk),
        .resetn(resetn),
        .in_parallel(out_poly_c_p),
        .out_serial(out_poly_c)
    );

    output_regs #(2*DATA_WIDTH) output5 (
        .clk(clk),
        .resetn(resetn),
        .in_parallel(out_mult_c_p),
        .out_serial(out_mult_result_c)
    );

    //==================================================
    // Modules
    //==================================================

    rca_adder #(DATA_WIDTH) adder0 (
        .clk(clk),
        .enable(enable),
        .in_sum_a(in_a_p),
        .in_sum_b(in_b_p),
        .out_sum_result(out_sum_p),
        .out_carry(out_carry_p)
    );

    cl_rca_mult #(DATA_WIDTH) cl_mult0 (
        .clk(clk),
        .enable(enable),
        .carry_option(carry_option),
        .in_mult_a(in_a_p),
        .in_mult_b(in_b_p),
        .out_mult_result(out_mult_p)
    );

    red_test #(DATA_WIDTH) red0 (
        .clk(clk),
        .enable(enable),
        .polyn_grade(polyn_grade_p),
        .polyn_red_in(polyn_red_in_p),
        .reduc_in(reduc_in_p),
        .out(out_poly_p)
    );

    cl_modules #(DATA_WIDTH) comp0 (
        .clk(clk),
        .enable(enable),
        .sum_funct(sum_funct),
        .exp_funct(exp_funct),
        .red_funct(red_funct),
        .carry_option(carry_option),
    
        .polyn_grade(polyn_grade_p),
        .polyn_red_in(polyn_red_in_p),
        .reduc_in(reduc_in_p),
        
        .in_a(in_a_p),
        .in_b(in_b_p),

        .out(out_sum_c_p),
        .out_poly(out_poly_c_p),
        .sum_carry_out(out_carry_c),
        .mult_out(out_mult_c_p)
    );

endmodule