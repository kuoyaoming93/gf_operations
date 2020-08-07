`timescale 1 ns / 1 ps

module testbench;

    wire    [31:0]  sum;
    wire            carry;
    reg     [31:0]  a;
    reg     [31:0]  b;
    reg             clk,resetn;

    parameter DATA_WIDTH = 4;
    parameter CYCLE = 2;

    initial begin 
        clk <= 0; // Procedural assignment
        forever #(CYCLE/2) clk = ~clk;
    end

    initial begin
        if ($test$plusargs("vcd")) begin
			$dumpfile("testbench.vcd");
			$dumpvars(0, testbench);
		end
        a = 0;
        b = 0;
        resetn = 0;

        #(10*CYCLE)
        resetn = 1;

        #(50*CYCLE)
        suma();

        #(50*CYCLE)
        suma();

        #(50*CYCLE)
        $finish;
    end

    rca_adder dut0(
        .clk(clk),
        .resetn(resetn),
        .in_sum_a(a),
        .in_sum_b(b),
        .out_sum_result(sum)
    );

endmodule