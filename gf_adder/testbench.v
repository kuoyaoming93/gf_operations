`timescale 1 ns / 1 ps

module testbench;

    wire [31:0] sum;
    reg [31:0] a;
    reg [31:0] b;
    reg gf_option;
    wire co;

    initial begin
        if ($test$plusargs("vcd")) begin
			$dumpfile("testbench.vcd");
			$dumpvars(0, testbench);
		end
        a = 0;
        b = 0;
        gf_option = 1;

        #10 
        gf_option = 1;
        a = 10;
        b = 25;

        #10 
        gf_option = 0;
        a = 10;
        b = 25;

        #10
        gf_option = 1;
        a = 28;
        b = 72;

        #15
        $finish;
    end

    top dut0(
        .gf_option(gf_option),
        .a(a),
        .b(b),
        .sum(sum),
        .co(co)
    );

endmodule