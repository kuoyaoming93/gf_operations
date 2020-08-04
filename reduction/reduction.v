module reduction #(
    parameter DATA_WIDTH = 32
) (
    input [DATA_WIDTH:0]        polyn_red_in,       // Polinomio primitivo
    input [2*DATA_WIDTH-1:0]    reduc_in,           // Polinomio a reducir
    output [DATA_WIDTH-1:0]     out                 // Salida normal
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
    assign reduc =      reduc_in_n;
    assign polyn_red =  polyn_red_in_n;

    //////////////////////////////////////////////////////////
    // Sumas parciales
    //////////////////////////////////////////////////////////

    wire [DATA_WIDTH:0]     partial_sum [0:DATA_WIDTH-1];
    wire [DATA_WIDTH-1:0]   partial_result;

    wire [DATA_WIDTH:0]     a_sum [0:DATA_WIDTH-2];
    wire [DATA_WIDTH:0]     b_sum [0:DATA_WIDTH-2];

    // La primera suma parcial del modulo de reduccion es el la primera parte del polinomio a reducir
    assign partial_sum[0] = reduc[0 +: (DATA_WIDTH+1)];
    

    /* Creo los N adders de N bits de ancho */
    genvar j;
    generate
        for (j = 0; j < DATA_WIDTH-1; j = j + 1) begin
            cl_add #(DATA_WIDTH) adder0(
                .a(a_sum[j][0 +: DATA_WIDTH]),
                .b(b_sum[j][0 +: DATA_WIDTH]),
                .sum(partial_sum[j+1][0 +: DATA_WIDTH])
            );
            // Suma adicional que necesita el polinomio de reduccion
            assign partial_sum[j+1][DATA_WIDTH] = a_sum[j][DATA_WIDTH] ^ b_sum[j][DATA_WIDTH];

            assign partial_result[j+1] = partial_sum[j+1][0];

            // Asigno las entradas de las sumas parciales
            assign a_sum[j] = {reduc[DATA_WIDTH+1+j],partial_sum[j][1 +: DATA_WIDTH]};  
            assign b_sum[j] = a_sum[j][0] ? polyn_red : 0;  
            
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

    assign out = out_poly;

endmodule