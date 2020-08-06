module rca_add_mult_exp_red #(
    parameter DATA_WIDTH = 32
) (
    input                       sum_funct,          // Modo Suma
    input                       exp_funct,          // Modo Exponencial (al cuadrado)
    input                       red_funct,          // Modo Polinomio de reduccion
    input                       carry_option,       // Carry o Carry-Less

    input [DATA_WIDTH:0]        polyn_red_in,       // Polinomio primitivo
    input [2*DATA_WIDTH-1:0]    reduc_in,           // Polinomio a reducir

    input [DATA_WIDTH-1:0]      a,                  // Entrada 1
    input [DATA_WIDTH-1:0]      b,                  // Entrada 2
    output [DATA_WIDTH-1:0]     out,                // Salida normal
    output [2*DATA_WIDTH-1:0]   mult_out            // Salida para la multiplicacion
);
    //////////////////////////////////////////////////////////
    // Inversion de las entradas - Para reducir el polinomio
    //////////////////////////////////////////////////////////

    wire [2*DATA_WIDTH-1:0]     reduc_in_n;         // Polinomio a reducir invertido
    wire [DATA_WIDTH:0]         polyn_red_in_n;     // Polinomio primitivo invertido

    wire [2*DATA_WIDTH-1:0]     reduc;              // Salidas para la siguiente etapa
    wire [DATA_WIDTH:0]         polyn_red;

    bit_order_inversion #(2*DATA_WIDTH) bit_inv_reduc(
        .a(reduc_in),
        .a_n(reduc_in_n)
    );
    bit_order_inversion #(DATA_WIDTH+1) bit_inv_polym(
        .a(polyn_red_in),
        .a_n(polyn_red_in_n)
    );

    // Invierto o no las entradas dependiendo si es polinomio de reduccion o no
    assign reduc =      red_funct ? reduc_in_n : reduc_in;
    assign polyn_red =  red_funct ? polyn_red_in_n : polyn_red_in;


    //////////////////////////////////////////////////////////
    // Multiplicaciones parciales
    //////////////////////////////////////////////////////////
    
    wire [DATA_WIDTH-1:0]   partial_products      [0:DATA_WIDTH-1];
    wire [DATA_WIDTH-1:0]   partial_multiplier;                    
    
    genvar i;
    generate
		for (i = 0; i < DATA_WIDTH; i = i + 1) begin
            partial_mult #(DATA_WIDTH) pmult0 (
                .a(a),
                .b(partial_multiplier[i]),
                .out(partial_products[i])
            );

            assign partial_multiplier[i] = exp_funct ? a[i] : b[i];
		end
	endgenerate 

    //////////////////////////////////////////////////////////
    // Sumas parciales
    //////////////////////////////////////////////////////////

    wire [DATA_WIDTH:0]     partial_sum [0:DATA_WIDTH-1];
    wire [DATA_WIDTH-1:0]   carry;
    wire [DATA_WIDTH-1:0]   partial_result;

    wire [DATA_WIDTH:0]     a_sum [0:DATA_WIDTH-2];
    wire [DATA_WIDTH:0]     b_sum [0:DATA_WIDTH-2];

    // No hay carry en la primera suma parcial
    assign carry[0] = 1'b0;

    // La primera suma parcial de la multiplicacion es el primer producto parcial
    // La primera suma parcial del modulo de reduccion es el la primera parte del polinomio a reducir
    assign partial_sum[0] = red_funct ? reduc[0 +: (DATA_WIDTH+1)] : {1'b0,partial_products[0]};
    

    /* Creo los N adders de N bits de ancho */
    genvar j;
    generate
        for (j = 0; j < DATA_WIDTH-1; j = j + 1) begin
            cl_rca_adder #(DATA_WIDTH) adder0(
                .carry_option(carry_option),
                .a(a_sum[j][0 +: DATA_WIDTH]),
                .b(b_sum[j][0 +: DATA_WIDTH]),
                .sum(partial_sum[j+1][0 +: DATA_WIDTH]),
                .co(carry[j+1])
            );
            // Suma adicional que necesita el polinomio de reduccion
            assign partial_sum[j+1][DATA_WIDTH] = a_sum[j][DATA_WIDTH] ^ b_sum[j][DATA_WIDTH];

            assign partial_result[j+1] = partial_sum[j+1][0];

            // Asigno las entradas de las sumas parciales
            assign a_sum[j] = red_funct ? ({reduc[DATA_WIDTH+1+j],partial_sum[j][1 +: DATA_WIDTH]}) : ((j==0 && sum_funct) ? {1'b0,a} : {1'b0,carry[j],partial_sum[j][1 +: DATA_WIDTH-1]});  
            assign b_sum[j] = red_funct ? ( a_sum[j][0] ? polyn_red : 0) : ((j==0 && sum_funct) ? {1'b0,b} : {1'b0,partial_products[j+1]});  
            
        end
    endgenerate

    //////////////////////////////////////////////////////////
    // Inversion de las salidas - Para reducir el polinomio
    //////////////////////////////////////////////////////////

    wire [DATA_WIDTH-1:0]       out_poly;       // Salida del polinomio de reduccion

    bit_order_inversion #(DATA_WIDTH) bit_inv_poly_out(
        .a(partial_sum[DATA_WIDTH-1][1 +:DATA_WIDTH]),
        .a_n(out_poly)
    );

    //////////////////////////////////////////////////////////
    // Salidas
    //////////////////////////////////////////////////////////

    /* Multiplicacion */
    assign mult_out = {carry[DATA_WIDTH-1],partial_sum[DATA_WIDTH-1][DATA_WIDTH-1:1],partial_result};
    assign partial_result[0] = partial_products[0][0];

    /* Suma */
    assign out = red_funct ? out_poly : partial_sum[1];


endmodule