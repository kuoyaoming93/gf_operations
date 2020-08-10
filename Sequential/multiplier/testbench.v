`timescale 1 ns / 1 ps

module testbench;

    parameter DATA_WIDTH = 32;
    parameter CYCLE = 5.2;
    parameter NUMBER_TESTS = 50;
    
    wire    [2*DATA_WIDTH-1:0]      mult_result;
    reg     [DATA_WIDTH-1:0]        a;
    reg     [DATA_WIDTH-1:0]        b;
    reg                             clk,enable;

    integer i;
    integer counter;
    reg [2*DATA_WIDTH-1:0] result;

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
    rca_mult #(DATA_WIDTH) dut0(
        .clk(clk),
        .enable(enable),
        .in_mult_a(a),
        .in_mult_b(b),
        .out_mult_result(mult_result)
    );

    initial begin
		$dumpfile("testbench.vcd");
		$dumpvars(0, testbench);

        $monitor("Time = %0t \ta = %0d \tb = %0d \tmult = %0d", $time, a,b,mult_result);

        a = 0;
        b = 0;
        counter = 0;

        reset();
        
        @(posedge clk)
        for(i = 0; i<NUMBER_TESTS; i = i+1)
        begin
            mult();
            #((DATA_WIDTH+1)*CYCLE);
            if(mult_result == (a*b))
                counter = counter + 1;
        end

        $monitor("[%0t] Test result: %0d of %0d tests passed...", $time, counter, NUMBER_TESTS);
        
        $finish;
    end
    
    //==================================================
    // Common Tasks
    //==================================================
    task reset;
        begin
            @(negedge clk)
            enable <= 1'b0;
            a <= 0;
            b <= 0;
            
            @(negedge clk)
            enable <= 1'b1;
        end
    endtask 
    
    task mult;
    begin
        a <= $urandom%(2**DATA_WIDTH-1); 
        b <= $urandom%(2**DATA_WIDTH-1); 
    end
    endtask

endmodule