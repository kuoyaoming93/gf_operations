`timescale 1 ns / 1 ps

module testbench;

    localparam DATA_WIDTH = 64;
    wire [DATA_WIDTH-1:0] out;
    reg [DATA_WIDTH:0] polyn_red_in;
    reg [2*DATA_WIDTH-1:0] reduc_in;
    reg [$clog2(DATA_WIDTH):0]    polyn_grade;



    initial begin
        if ($test$plusargs("vcd")) begin
			$dumpfile("testbench.vcd");
			$dumpvars(0, testbench);
		end
        polyn_red_in = 0;
        reduc_in = 0;
        polyn_grade = 0;

        #10 
        polyn_grade = 4;
        polyn_red_in = 19;
        reduc_in = 90;

        #10 
        polyn_grade = 3;
        polyn_red_in = 11;
        reduc_in = 27;

        #10 
        polyn_grade = 2;
        polyn_red_in = 6;
        reduc_in = 7;

        #15
        $finish;
    end

    top #(DATA_WIDTH) dut0(
        .polyn_grade(polyn_grade),
        .polyn_red_in(polyn_red_in),
        .reduc_in(reduc_in),
        .out(out)
    );

endmodule