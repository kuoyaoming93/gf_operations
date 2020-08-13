module top #( parameter DATA_WIDTH = 32) (
    input [$clog2(DATA_WIDTH):0]    polyn_grade,
    input [DATA_WIDTH:0] polyn_red_in,
    input [2*DATA_WIDTH-1:0] reduc_in,
    output [DATA_WIDTH-1:0] out
);

    reduction #(DATA_WIDTH) dut0(
        .polyn_grade(polyn_grade),
        .polyn_red_in(polyn_red_in),
        .reduc_in(reduc_in),
        .out(out)
    );

endmodule