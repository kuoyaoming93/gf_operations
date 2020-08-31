`timescale 1 ns / 1 ps

module testbench;

    parameter DATA_WIDTH = 32;
    parameter NUMBER_TESTS = 50;
    parameter DELAY = 10;

    // Input / Outputs
    reg [DATA_WIDTH-1:0] a;
    reg [DATA_WIDTH-1:0] b;
    wire [DATA_WIDTH-1:0] out;
    wire [DATA_WIDTH-1:0] cl_sum;
    wire [2*DATA_WIDTH-1:0] mult_out;
    wire [2*DATA_WIDTH-1:0] cl_mult_out;
    wire [DATA_WIDTH-1:0] reduc_out;

    // Polynomial reduction inputs
    reg [DATA_WIDTH:0] polyn_red_in;
    reg [2*DATA_WIDTH-1:0] reduc_in;
    reg [$clog2(DATA_WIDTH):0] polyn_grade;
    
    // Module functions
    reg carry_option;
    reg sum_funct;
    reg exp_funct;
    reg red_funct;

    integer counter,i;

    initial begin
        if ($test$plusargs("vcd")) begin
			$dumpfile("testbench.vcd");
			$dumpvars(0, testbench);
		end

        // Reset
        reset();

        // Tests
        add_test();
        cl_add_test();
        mult_test();
        cl_mult_test();
        exp_test();
        red_test();

        $finish;
    end

    //////////////////////////////////////////////////////////
    // Tareas
    //////////////////////////////////////////////////////////

    task add_test;
        begin
            counter = 0;
            for(i = 0; i<NUMBER_TESTS; i = i+1)
            begin
                add();
                #DELAY
                if(out == a+b)
                    counter = counter + 1;
            end
            $display("[%0t] ADD result: \t\t%0d of %0d tests passed...", $time, counter, NUMBER_TESTS);
        end
    endtask

    task cl_add_test;
        begin
            counter = 0;
            for(i = 0; i<NUMBER_TESTS; i = i+1)
            begin
                cl_add_task();
                #DELAY
                if(out == cl_sum)
                    counter = counter + 1;
            end
            $display("[%0t] CL_ADD result: \t%0d of %0d tests passed...", $time, counter, NUMBER_TESTS);
        end
    endtask

    task mult_test;
        begin
            counter = 0;
            for(i = 0; i<NUMBER_TESTS; i = i+1)
            begin
                mult();
                #DELAY
                if(mult_out == a*b)
                    counter = counter + 1;
            end
            $display("[%0t] MULT result: \t\t%0d of %0d tests passed...", $time, counter, NUMBER_TESTS);
        end
    endtask

    task cl_mult_test;
        begin
            counter = 0;
            for(i = 0; i<NUMBER_TESTS; i = i+1)
            begin
                cl_mult();
                #DELAY
                if(mult_out == cl_mult_out)
                    counter = counter + 1;
            end
            $display("[%0t] CL_MULT result: \t%0d of %0d tests passed...", $time, counter, NUMBER_TESTS);
        end
    endtask

    task exp_test;
        begin
            counter = 0;
            for(i = 0; i<NUMBER_TESTS; i = i+1)
            begin
                exp();
                #DELAY
                if(mult_out == a*a)
                    counter = counter + 1;
            end
            $display("[%0t] EXP result: \t\t%0d of %0d tests passed...", $time, counter, NUMBER_TESTS);
        end
    endtask

    task red_test;
        begin
            counter = 0;
            for(i = 0; i<NUMBER_TESTS; i = i+1)
            begin
                reduc();
                #DELAY
                if(out == reduc_out)
                    counter = counter + 1;
            end
            $display("[%0t] RED result: \t\t%0d of %0d tests passed...", $time, counter, NUMBER_TESTS);
        end
    endtask

    task reset;
        begin
            carry_option = 0; 
            sum_funct = 0;
            exp_funct = 0;
            red_funct = 0;

            polyn_grade = 0;
            polyn_red_in = 0;
            reduc_in = 0;

            a = 0; 
            b = 0; 
        end
    endtask

    task add;
        begin
            carry_option = 1; 
            sum_funct = 1;
            exp_funct = 0;
            red_funct = 0;

            a = $urandom%(2**DATA_WIDTH-1); 
            b = $urandom%(2**DATA_WIDTH-1);            
        end
    endtask

    task cl_add_task;
        begin
            carry_option = 0; 
            sum_funct = 1;
            exp_funct = 0;
            red_funct = 0;

            a = $urandom%(2**DATA_WIDTH-1); 
            b = $urandom%(2**DATA_WIDTH-1);            
        end
    endtask

    task mult;
        begin
            carry_option = 1; 
            sum_funct = 0;
            exp_funct = 0;
            red_funct = 0;

            a = $urandom%(2**DATA_WIDTH-1); 
            b = $urandom%(2**DATA_WIDTH-1);            
        end
    endtask

    task cl_mult;
        begin
            carry_option = 0; 
            sum_funct = 0;
            exp_funct = 0;
            red_funct = 0;

            a = $urandom%(2**DATA_WIDTH-1); 
            b = $urandom%(2**DATA_WIDTH-1);            
        end
    endtask

    task exp;
        begin
            carry_option = 1; 
            sum_funct = 0;
            exp_funct = 1;
            red_funct = 0;

            a = $urandom%(2**DATA_WIDTH-1); 
            b = $urandom%(2**DATA_WIDTH-1);            
        end
    endtask

    task reduc;
        begin
            carry_option = 0; 
            sum_funct = 0;
            exp_funct = 0;
            red_funct = 1;

            polyn_grade = $urandom%(DATA_WIDTH-2) + 2;
            polyn_red_in =  $urandom%(2**(polyn_grade+1)-1);
            reduc_in =      $urandom%(2**(2*polyn_grade)-1);
        end
    endtask

    //////////////////////////////////////////////////////////
    // Instanciacion de los modulos
    //////////////////////////////////////////////////////////

    cl_modules #(DATA_WIDTH) dut0(
        .sum_funct(sum_funct),
        .exp_funct(exp_funct),
        .red_funct(red_funct),
        .carry_option(carry_option),

        .polyn_grade(polyn_grade),
        .polyn_red_in(polyn_red_in),
        .reduc_in(reduc_in),

        .a(a),
        .b(b),

        .out(out),
        .mult_out(mult_out)
    );

    cl_add #(DATA_WIDTH) dut1(
        .a(a),
        .b(b),
        .sum(cl_sum)
    );

    cl_rca_mult #(DATA_WIDTH) dut2(
        .carry_option(carry_option),
        .a(a),
        .b(b),
        .out(cl_mult_out)
    );

    reduction #(DATA_WIDTH) dut3(
        .polyn_grade(polyn_grade),
        .polyn_red_in(polyn_red_in),
        .reduc_in(reduc_in),
        .out(reduc_out)
    );

endmodule