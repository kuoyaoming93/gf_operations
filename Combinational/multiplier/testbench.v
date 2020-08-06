`timescale 1 ns / 1 ps

module testbench;

    localparam DATA_WIDTH = 4;
    wire [2*DATA_WIDTH-1:0] out;
    reg [DATA_WIDTH-1:0] a;
    reg [DATA_WIDTH-1:0] b;

    initial begin
        if ($test$plusargs("vcd")) begin
			$dumpfile("testbench.vcd");
			$dumpvars(0, testbench);
		end
        a = 0;
        b = 0;

        #10 
        a = 12;
        b = 10;

        #10
        a = 5;
        b = 9;

        #10
        a = 15;
        b = 13;

        #15
        $finish;
    end

    top #(DATA_WIDTH) dut0(
        .a(a),
        .b(b),
        .out(out)
    );

endmodule