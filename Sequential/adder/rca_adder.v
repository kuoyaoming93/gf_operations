module rca_adder #(
    parameter DATA_WIDTH = 32
)(
    input                           clk,
    input                           resetn,
    input       [DATA_WIDTH-1:0]    in_sum_a,
    input       [DATA_WIDTH-1:0]    in_sum_b,
    output reg  [DATA_WIDTH-1:0]    out_sum_result,
    output reg                      out_carry
);

    reg     [DATA_WIDTH-1:0]    sum_a;
    reg     [DATA_WIDTH-1:0]    sum_b;
    wire    [DATA_WIDTH-1:0]    sum;
    wire                        co;

    wire    [DATA_WIDTH-1:0]    carry_array;
    

    assign co = carry_array[DATA_WIDTH-1];

    /* Creo un half adder */
    half_adder ha0 (
        .a(sum_a[0]), 
        .b(sum_b[0]),
        .sum(sum[0]),
        .co(carry_array[0])
    );

    /* Creo N-1 full adders */
	genvar i;
	generate
		for (i = 1; i < DATA_WIDTH; i = i + 1) begin
            full_adder fa0 (
                .a(sum_a[i]), 
                .b(sum_b[i]),
                .sum(sum[i]),
                .ci(carry_array[i-1]), 
                .co(carry_array[i])
                );
		end
	endgenerate

    /* Registrar las salidas */
    always @(posedge clk) begin
        if(!resetn) begin
            sum_a           <= 0;
            sum_b           <= 0;
            out_sum_result  <= 0;
            out_carry       <= 0;
        end else begin 
            sum_a           <= in_sum_a;
            sum_b           <= in_sum_b;
            out_sum_result  <= sum;
            out_carry       <= co;
        end
    end 
endmodule