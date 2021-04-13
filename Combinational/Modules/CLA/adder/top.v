module top #( parameter DATA_WIDTH = 32)(
    input [DATA_WIDTH-1:0]    a,
    input [DATA_WIDTH-1:0]    b,
    output [DATA_WIDTH-1:0]   sum
);

    cla_adder #(DATA_WIDTH) dut0(
        .a(a),
        .b(b),
        .sum(sum)
    );

endmodule