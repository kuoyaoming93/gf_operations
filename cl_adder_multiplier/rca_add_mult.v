module rca_add_mult #(
    parameter DATA_WIDTH = 32
) (
    input sum_funct,
    input carry_option,
    input [DATA_WIDTH-1:0] a,
    input [DATA_WIDTH-1:0] b,
    output [DATA_WIDTH-1:0] out,
    output [2*DATA_WIDTH-1:0] mult_out
    );


    //////////////////////////////////////////////////////////
    // Multiplicaciones parciales
    //////////////////////////////////////////////////////////
    
    wire [DATA_WIDTH-1:0]   partial_products [0:DATA_WIDTH-1];

    genvar i;
    generate
		for (i = 0; i < DATA_WIDTH; i = i + 1) begin
            partial_mult #(DATA_WIDTH) pmult0 (
                .a(a),
                .b(b[i]),
                .out(partial_products[i])
            );
		end
	endgenerate


    //////////////////////////////////////////////////////////
    // Sumas parciales
    //////////////////////////////////////////////////////////

    wire [DATA_WIDTH-1:0]   partial_sum [0:DATA_WIDTH-1];
    wire [DATA_WIDTH-1:0]   carry;
    wire [DATA_WIDTH-1:0]   partial_result;

    wire [DATA_WIDTH-1:0]   a_sum[0:DATA_WIDTH-2];
    wire [DATA_WIDTH-1:0]   b_sum[0:DATA_WIDTH-2];

    // No hay carry en la primera suma parcial
    assign carry[0] = 1'b0;
    // La primera suma parcial de la multiplicacion es el primer producto parcial
    assign partial_sum[0] = partial_products[0];
    

    /* Creo los N adders de N bits de ancho */
    genvar j;
    generate
        for (j = 0; j < DATA_WIDTH-1; j = j + 1) begin
            cl_rca_adder #(DATA_WIDTH) adder0(
                .carry_option(carry_option),
                .a(a_sum[j]),
                .b(b_sum[j]),
                .sum(partial_sum[j+1]),
                .co(carry[j+1])
            );
            assign partial_result[j+1] = partial_sum[j+1][0];

            // Asigno las entradas de las sumas parciales
            assign a_sum[j] = (j==0 && sum_funct) ? a : {carry[j],partial_sum[j][1 +: DATA_WIDTH-1]};  
            assign b_sum[j] = (j==0 && sum_funct) ? b : partial_products[j+1];  
            
        end
    endgenerate

    //////////////////////////////////////////////////////////
    // Salidas
    //////////////////////////////////////////////////////////

    /* Multiplicacion */
    assign mult_out = {carry[DATA_WIDTH-1],partial_sum[DATA_WIDTH-1][DATA_WIDTH-1:1],partial_result};
    assign partial_result[0] = partial_products[0][0];

    /* Suma */
    assign out = partial_sum[1];

endmodule