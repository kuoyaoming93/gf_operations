`timescale 1 ns / 1 ps

module testbench;

    parameter DATA_WIDTH = 32;
    parameter MAX_GF = 16;
    parameter CYCLE = 2;
    parameter NUMBER_TESTS = 5000;
    
    wire [DATA_WIDTH-1:0]       out,comb_out;
    reg [DATA_WIDTH:0]          polyn_red_in;
    reg [$clog2(DATA_WIDTH):0]  polyn_grade;

    reg                         clk,enable;
    wire                        finish;

    reg [DATA_WIDTH:0]          irred_poly_table [0:DATA_WIDTH];

    // CL multiplier registers
    reg [DATA_WIDTH-1:0]        a,b;
    wire [2*DATA_WIDTH-1:0]     cl_mult_out;

    integer i;
    integer counter;

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
    // Clock
    //==================================================
    initial begin
        clk = 0; // Procedural assignment
        forever #(CYCLE/2) clk = ~clk;
    end 

    //==================================================
    // DUT
    //==================================================
    red #(DATA_WIDTH) dut0(
        .clk(clk),
        .op_enable(enable),
        .polyn_grade(polyn_grade),
        .polyn_red_in(polyn_red_in),
        .reduc_in(cl_mult_out),
        .out(out),
        .op_finish(finish)
    );

    red_test #(DATA_WIDTH) dut1(
        .polyn_grade(polyn_grade),
        .polyn_red_in(polyn_red_in),
        .reduc_in(cl_mult_out),
        .out(comb_out)
    );

    cl_rca_mult #(DATA_WIDTH) cl_multiplier0 (
        .carry_option(1'b0),
        .a(a),
        .b(b),
        .out(cl_mult_out)
    );


    initial begin
        if ($test$plusargs("vcd")) begin
			$dumpfile("testbench.vcd");
			$dumpvars(0, testbench);
		end

        // Reset sequential module
        reset();

        @(posedge clk)
        for(i = 0; i<NUMBER_TESTS; i = i+1)
        begin
            reduc_task();
            @(posedge clk)
            while(!finish) begin
                #CYCLE;
            end

            if(out == comb_out)
                counter = counter + 1;
            @(negedge clk)
            enable = 0;
            $display("[Test %0d] \ta = %0d \tb = %0d \t grade = %0d \tout = %0d",i,a,b,polyn_grade,out);
        end

        $display("[%0t] Test result: %0d of %0d tests passed...", $time, counter, NUMBER_TESTS);
        $finish;

        #15
        $finish;
    end

    //==================================================
    // Common Tasks
    //==================================================
    task reset;
        begin
            @(negedge clk)
            enable = 1'b0;
            polyn_grade = 0;
            polyn_red_in = 0;
            counter = 0;
        end
    endtask 
    
    task reduc_task;
        begin
            @(negedge clk)
            enable = 1;
            polyn_grade = $urandom%(MAX_GF-2) + 2;
            a = $urandom%(2**polyn_grade-1);
            b = $urandom%(2**polyn_grade-1);
            polyn_red_in = irred_poly_table[polyn_grade];
        end
    endtask

endmodule