module rca_adder #(
    parameter DATA_WIDTH = 32
)(
    input   [DATA_WIDTH-1:0]    a,
    input   [DATA_WIDTH-1:0]    b,
    input                       ci,
    output  [DATA_WIDTH-1:0]    sum,
    output                      co
);

    wire    [DATA_WIDTH:0] carry_array;

    assign carry_array[0] = ci;
    assign co = carry_array[DATA_WIDTH];

    /* Creo N full adders */
	genvar i;
	generate
		for (i = 0; i < DATA_WIDTH; i = i + 1) begin
            full_adder fa0 (
                .a(a[i]), 
                .b(b[i]),
                .sum(sum[i]),
                .ci(carry_array[i]), 
                .co(carry_array[i+1])
                );
		end
	endgenerate

endmodule