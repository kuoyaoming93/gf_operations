`timescale 1 ns / 1 ps

module cl_rca_mult #(
    parameter DATA_WIDTH = 32
) (
    input                           clk,
    input                           enable,
    input [DATA_WIDTH-1:0]          in_mult_a,
    input [DATA_WIDTH-1:0]          in_mult_b,
    output reg [2*DATA_WIDTH-1:0]   out_mult_result
    );

    wire [DATA_WIDTH-1:0]   partial_products [0:DATA_WIDTH-1];
    wire [DATA_WIDTH-1:0]   partial_sum [0:DATA_WIDTH-1];
    wire [DATA_WIDTH-1:0]   partial_result;
    wire [2*DATA_WIDTH-1:0] out;

    /* Creo las multiplicaciones parciales */
    genvar i;
    generate
		for (i = 0; i < DATA_WIDTH; i = i + 1) begin
            partial_mult #(DATA_WIDTH) pmult0 (
                .a(in_mult_a),
                .b(in_mult_b[i]),
                .out(partial_products[i])
            );
		end
	endgenerate

    assign partial_sum[0] = partial_products[0];

    /* Creo los N adders de N bits de ancho */
    genvar j;
    generate
        for (j = 0; j < DATA_WIDTH-1; j = j + 1) begin
            cl_add #(DATA_WIDTH) adder0(
                .a({1'b0,partial_sum[j][1 +: DATA_WIDTH-1]}),
                .b(partial_products[j+1]),
                .sum(partial_sum[j+1])
            );
            assign partial_result[j+1] = partial_sum[j+1][0];
        end
    endgenerate

    
    assign out = {1'b0,partial_sum[DATA_WIDTH-1][DATA_WIDTH-1:1],partial_result};
    assign partial_result[0] = partial_products[0][0];

    /* Registrar las salidas */
    always @(posedge clk) begin
        if(!enable) begin
            out_mult_result  <= 0;
        end else begin 
            out_mult_result  <= out;
        end
    end 

endmodule