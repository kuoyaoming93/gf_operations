`timescale 1 ns / 1 ps

module testbench;

    localparam DATA_WIDTH = 4;
    wire [2*DATA_WIDTH-1:0] out;
    wire [2*DATA_WIDTH-1:0] out2;
    wire [2*DATA_WIDTH-1:0] out3;
    wire [2*DATA_WIDTH-1:0] out4;
    reg [DATA_WIDTH-1:0] a;
    reg [DATA_WIDTH-1:0] b;
    reg option;

    initial begin
        if ($test$plusargs("vcd")) begin
			$dumpfile("testbench.vcd");
			$dumpvars(0, testbench);
		end
        a = 0;
        b = 0;
        option = 0;

        #10 
        a = 12;
        b = 10;

        #10
        a = 5;
        b = 9;

        #10
        a = 15;
        b = 13;

        #10
        option = 1;
        a = 15;
        b = 13;

        #15
        $finish;
    end

    top #(DATA_WIDTH) dut0(
        .gf_option(option),
        .a(a),
        .b(b),
        .out(out),
        .out2(out2),
        .out3(out3),
        .out4(out4)
    );

endmodule