`timescale 1 ns / 1 ps

module testbench;

    localparam DATA_WIDTH = 32;
    wire [DATA_WIDTH-1:0] out;
    wire [2*DATA_WIDTH-1:0] mult_out;
    reg [DATA_WIDTH-1:0] a;
    reg [DATA_WIDTH-1:0] b;
    reg option;
    reg sum_funct;
    reg exp_funct;


    initial begin
        if ($test$plusargs("vcd")) begin
			$dumpfile("testbench.vcd");
			$dumpvars(0, testbench);
		end
        a = 0;
        b = 0;
        option = 1;
        sum_funct = 0;
        exp_funct = 0;

        #10 
        sum_funct = 0;
        exp_funct = 0;
        a = 12;
        b = 10;
        
        #10 
        sum_funct = 1;
        exp_funct = 0;
        a = 12;
        b = 10;

        #10 
        sum_funct = 0;
        exp_funct = 1;
        a = 12;
        b = 10;
        
        #10 
        sum_funct = 1;
        exp_funct = 1;
        a = 12;
        b = 10;

        #10 
        sum_funct = 0;
        exp_funct = 0;
        a = 22;
        b = 78;

        #10 
        sum_funct = 1;
        exp_funct = 0;
        a = 22;
        b = 78;


        #15
        $finish;
    end

    top #(DATA_WIDTH) dut0(
        .sum_funct(sum_funct),
        .exp_funct(exp_funct),
        .carry_option(option),
        .a(a),
        .b(b),
        .out(out),
        .mult_out(mult_out)
    );

endmodule