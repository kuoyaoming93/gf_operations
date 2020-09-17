`timescale 1 ns / 1 ps

module testbench;

    localparam DATA_WIDTH = 10;
    parameter CYCLE = 2;
    parameter NUMBER_TESTS = 5000;
    
    wire [DATA_WIDTH-1:0] out,comb_out;
    reg [DATA_WIDTH:0] polyn_red_in;
    reg [2*DATA_WIDTH-1:0] reduc_in;
    reg [$clog2(DATA_WIDTH):0]    polyn_grade;

    reg                             clk,enable;
    wire                            finish;

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
        .reduc_in(reduc_in),
        .out(out),
        .op_finish(finish)
    );

    red_test #(DATA_WIDTH) dut1(
        .polyn_grade(polyn_grade),
        .polyn_red_in(polyn_red_in),
        .reduc_in(reduc_in),
        .out(comb_out)
    );


    initial begin
        if ($test$plusargs("vcd")) begin
			$dumpfile("testbench.vcd");
			$dumpvars(0, testbench);
		end

        
        reset();

        @(negedge clk)
        polyn_grade = 4;
        polyn_red_in = 19;
        reduc_in = 90;
        enable = 1;

        #(20*CYCLE);
        @(negedge clk)
        enable = 0;

        @(negedge clk)
        polyn_grade = 3;
        polyn_red_in = 11;
        reduc_in = 27;
        enable = 1;

        #(20*CYCLE);
        @(negedge clk)
        enable = 0;

        @(negedge clk)
        polyn_grade = 2;
        polyn_red_in = 6;
        reduc_in = 7;
        enable = 1;

        #(20*CYCLE);
        @(negedge clk)
        enable = 0;

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
            reduc_in = 0;
        end
    endtask 
    


endmodule