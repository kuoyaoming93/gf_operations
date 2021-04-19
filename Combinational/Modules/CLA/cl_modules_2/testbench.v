`timescale 1 ns / 1 ps

module testbench;

    parameter DATA_WIDTH = 32;
    parameter NUMBER_TESTS = 1000;
    parameter DELAY = 10;
    parameter MAX_GF = 16;

    // Input / Outputs
    reg [$clog2(DATA_WIDTH):0] width;
    reg [DATA_WIDTH-1:0] a, cl_a;
    reg [DATA_WIDTH-1:0] b, cl_b;
    reg [DATA_WIDTH:0] polyn_red_in;

    wire    [2*DATA_WIDTH-1:0]      mult_result,cl_mult_result;
    wire    [DATA_WIDTH-1:0]        add_result,comb_out,out_poly;

    wire                            carry;

    // Polynomial reduction inputs
    
    reg [2*DATA_WIDTH-1:0] reduc_in;
    
    
    // Module functions
    reg carry_option;
    reg red_funct;

    reg [DATA_WIDTH:0]              irred_poly_table [0:DATA_WIDTH];

    integer counter,i;
    integer rand_funct;

    //==================================================
    // Irreducible polynomial table init
    //==================================================
    initial begin
        irred_poly_table[0]     = 0;
        irred_poly_table[1]     = 0;
        irred_poly_table[2]     = 7;
        irred_poly_table[3]     = 11;
        irred_poly_table[4]     = 19;
        irred_poly_table[5]     = 37;
        irred_poly_table[6]     = 67;
        irred_poly_table[7]     = 137;
        irred_poly_table[8]     = 285;
        irred_poly_table[9]     = 529;
        irred_poly_table[10]    = 1033;
        irred_poly_table[11]    = 2053;
        irred_poly_table[12]    = 4179;
        irred_poly_table[13]    = 8219;
        irred_poly_table[14]    = 17475;
        irred_poly_table[15]    = 32771;
        irred_poly_table[16]    = 69643;
    end

    //==================================================
    // Main
    //==================================================
    initial begin
        if ($test$plusargs("vcd")) begin
			$dumpfile("testbench.vcd");
			$dumpvars(0, testbench);
		end

        // Reset
        reset();

        for(i = 0; i<NUMBER_TESTS; i = i+1)
        begin
            rand_funct = $urandom%(3); 
            if(rand_funct == 0) 
                mult();
            if(rand_funct == 1) 
                cl_mult();
            if(rand_funct == 2) 
                reduc();
            
            #DELAY;

            if(mult_result == (a*b) && rand_funct == 0)
                counter = counter + 1;
            if(mult_result == cl_mult_result && rand_funct == 1)
                counter = counter + 1;
            if(comb_out == out_poly && rand_funct == 2)
                counter = counter + 1;    

            if(rand_funct == 0) 
                $display("[Test %0d] MULT \ta = %0d \tb = %0d \t width = %0d \tmult = %0d",i,a,b,width,mult_result);
            if(rand_funct == 1) 
                $display("[Test %0d] CL MULT \ta = %0d \tb = %0d \t width = %0d \tmult = %0d",i,a,b,width,mult_result);
            if(rand_funct == 2)
                $display("[Test %0d] RED \ta = %0d \tb = %0d \t grade = %0d \tout = %0d",i,cl_a,cl_b,width,out_poly);
            #DELAY;
        end

        $display("[%0t] Test result: %0d of %0d tests passed...", $time, counter, NUMBER_TESTS);
        $finish;
    end

    //////////////////////////////////////////////////////////
    // Tareas
    //////////////////////////////////////////////////////////

    task reset;
        begin
            carry_option = 0; 
            red_funct = 0;

            width = 0;
            polyn_red_in = 0;
            reduc_in = 0;

            a = 0; 
            b = 0; 

            counter = 0;
        end
    endtask

    task mult;
        begin
            carry_option = 1; 
            red_funct = 0;

            a = $urandom%(2**DATA_WIDTH-1); 
            b = $urandom%(2**DATA_WIDTH-1);            
        end
    endtask

    task cl_mult;
        begin
            carry_option = 0; 
            red_funct = 0;

            a = $urandom%(2**DATA_WIDTH-1); 
            b = $urandom%(2**DATA_WIDTH-1);          
            cl_a = a;
            cl_b = b;  
        end
    endtask

    task reduc;
        begin
            carry_option = 0; 
            red_funct = 1;

            width = $urandom%(MAX_GF-2) + 2;
            cl_a = $urandom%(2**width-1);
            cl_b = $urandom%(2**width-1);
            reduc_in =      $urandom%(2**(2*width)-1);
            polyn_red_in = irred_poly_table[width];
        end
    endtask

    //////////////////////////////////////////////////////////
    // Instanciacion de los modulos
    //////////////////////////////////////////////////////////

    cl_modules #(DATA_WIDTH) dut0(
        .red_funct(red_funct),
        .carry_option(carry_option),

        .polyn_grade(width),
        .polyn_red_in(polyn_red_in),
        .reduc_in(cl_mult_result),

        .a(a),
        .b(b),

        .out(add_result),
        .out_poly(out_poly),
        .mult_out(mult_result)
    );

    cl_rca_mult #(DATA_WIDTH) dut2(
        .carry_option(carry_option),
        .a(cl_a),
        .b(cl_b),
        .out(cl_mult_result)
    );

    red_test #(DATA_WIDTH) test1 (
        .polyn_grade(width),
        .polyn_red_in(polyn_red_in),
        .reduc_in(cl_mult_result),
        .out(comb_out)
    );


endmodule