`timescale 1 ns / 1 ps

module testbench;

    wire [31:0] sum,sum2,sum3;
    reg [31:0] a;
    reg [31:0] b;
    reg carry_option;

    initial begin
        if ($test$plusargs("vcd")) begin
			$dumpfile("testbench.vcd");
			$dumpvars(0, testbench);
		end
        a = 0;
        b = 0;
        carry_option = 1;

        #10 
        carry_option = 1;
        a = 10;
        b = 25;

        #10 
        carry_option = 0;
        a = 10;
        b = 25;

        #10
        carry_option = 1;
        a = 28;
        b = 72;

        #15
        $finish;
    end

    top dut0(
        .carry_option(carry_option),
        .a(a),
        .b(b),
        .sum(sum),
        .sum2(sum2),
        .sum3(sum3)
    );

endmodule