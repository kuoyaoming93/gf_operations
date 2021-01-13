`timescale 1 ns / 1 ps

module testbench;

    parameter DATA_WIDTH = 32;
    parameter CYCLE = 2;
    parameter NUMBER_TESTS = 5000;
    
    wire    [2*DATA_WIDTH-1:0]      mult_result, cl_mult_result;
    reg                             carry_option;
    reg     [DATA_WIDTH-1:0]        a, cl_a;
    reg     [DATA_WIDTH-1:0]        b, cl_b;
    reg                             clk,enable;
    reg     [$clog2(DATA_WIDTH):0]  width;
    wire                            finish;

    integer i;
    integer counter;
    
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
    mult #(DATA_WIDTH) dut0(
        .clk(clk),
        .op_enable(enable),
        .in_width(width),
        .in_mult_a(a),
        .in_mult_b(b),
        .out_mult_result(mult_result),
        .op_finish(finish)
    );

    cl_rca_mult #(DATA_WIDTH) test0 (
        .carry_option(carry_option),
        .a(cl_a),
        .b(cl_b),
        .out(cl_mult_result)
    );

    initial begin
		$dumpfile("testbench.vcd");
		$dumpvars(0, testbench);

        //$monitor("Time = %0t \ta = %0d \tb = %0d \t width = %0d \tmult = %0d", $time, a,b,width,mult_result);

        reset();
        
        @(posedge clk)
        for(i = 0; i<NUMBER_TESTS; i = i+1)
        begin
            cl_mult();

            @(posedge clk)
            while(!finish) begin
                #CYCLE;
            end

            if(mult_result == cl_mult_result)
                counter = counter + 1;
            @(negedge clk)
            enable = 0;
            $display("[Test %0d] \ta = %0d \tb = %0d \t width = %0d \tmult = %0d",i,a,b,width,mult_result);
        end

        $display("[%0t] Test result: %0d of %0d tests passed...", $time, counter, NUMBER_TESTS);
        $finish;
    end
    
    //==================================================
    // Common Tasks
    //==================================================
    task reset;
        begin
            @(negedge clk)
            enable = 1'b0;
            a = 0;
            b = 0;
            counter = 0;
        end
    endtask 

    task cl_mult;
        begin
            @(negedge clk)

            width = $urandom%(DATA_WIDTH-2) + 2;
            a = $urandom%(2**width-1); 
            b = $urandom%(2**width-1); 
            cl_a = a;
            cl_b = b;
            enable = 1;
            carry_option = 0;
        end
    endtask

endmodule