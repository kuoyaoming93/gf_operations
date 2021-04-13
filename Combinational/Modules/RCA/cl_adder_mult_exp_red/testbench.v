`timescale 1 ns / 1 ps

module testbench;

    localparam DATA_WIDTH = 4;
    wire [DATA_WIDTH-1:0] out;
    wire [2*DATA_WIDTH-1:0] mult_out;
    reg [DATA_WIDTH-1:0] a;
    reg [DATA_WIDTH-1:0] b;
    reg option;
    reg sum_funct;
    reg exp_funct;
    reg red_funct;
    reg [DATA_WIDTH:0] polyn_red_in;
    reg [2*DATA_WIDTH-1:0] reduc_in;



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
        polyn_red_in = 0;
        reduc_in = 0;
        red_funct = 0;

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

        #10 
        sum_funct = 0;
        exp_funct = 0;
        red_funct = 1;
        option = 0;
        a = 0;
        b = 0;
        polyn_red_in = 19;
        reduc_in = 90;


        #15
        $finish;
    end

    top #(DATA_WIDTH) dut0(
        .sum_funct(sum_funct),
        .exp_funct(exp_funct),
        .red_funct(red_funct),
        .carry_option(option),
        .polyn_red_in(polyn_red_in),
        .reduc_in(reduc_in),
        .a(a),
        .b(b),
        .out(out),
        .mult_out(mult_out)
    );

endmodule