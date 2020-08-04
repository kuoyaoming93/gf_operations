`timescale 1 ns / 1 ps

module testbench;

    localparam DATA_WIDTH = 4;
    wire [DATA_WIDTH-1:0] out;
    reg [DATA_WIDTH:0] polyn_red_in;
    reg [2*DATA_WIDTH-1:0] reduc_in;



    initial begin
        if ($test$plusargs("vcd")) begin
			$dumpfile("testbench.vcd");
			$dumpvars(0, testbench);
		end
        polyn_red_in = 0;
        reduc_in = 0;

        #10 
        polyn_red_in = 19;
        reduc_in = 90;


        #15
        $finish;
    end

    top #(DATA_WIDTH) dut0(
        .polyn_red_in(polyn_red_in),
        .reduc_in(reduc_in),
        .out(out)
    );

endmodule