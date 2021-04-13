`timescale 1 ns / 1 ps

module testbench;

    wire [31:0] sum;
    reg [31:0] a;
    reg [31:0] b;

    initial begin
        if ($test$plusargs("vcd")) begin
			$dumpfile("testbench.vcd");
			$dumpvars(0, testbench);
		end
        a = 0;
        b = 0;

        #5 
        a = 10;
        b = 25;

        #10
        a = 28;
        b = 72;

        #15
        $finish;
    end

    top dut0(
        .a(a),
        .b(b),
        .sum(sum)
    );

endmodule