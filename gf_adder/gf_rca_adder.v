module gf_rca_adder #(
    parameter DATA_WIDTH = 32
)(
    input                       gf_option,
    input   [DATA_WIDTH-1:0]    a,
    input   [DATA_WIDTH-1:0]    b,
    output  [DATA_WIDTH-1:0]    sum,
    output                      co
);

    wire    [DATA_WIDTH-1:0] carry_array;

    assign co = carry_array[DATA_WIDTH-1];

    /* Creo un half adder */
    gf_half_adder ha0 (
        .gf_option(gf_option),
        .a(a[0]), 
        .b(b[0]),
        .sum(sum[0]),
        .co(carry_array[0])
    );

    /* Creo N-1 full adders */
	genvar i;
	generate
		for (i = 1; i < DATA_WIDTH; i = i + 1) begin
            gf_full_adder fa0 (
                .gf_option(gf_option),
                .a(a[i]), 
                .b(b[i]),
                .sum(sum[i]),
                .ci(carry_array[i-1]), 
                .co(carry_array[i])
                );
		end
	endgenerate

endmodule

