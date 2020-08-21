module reduction #(
    parameter DATA_WIDTH = 4
) (
    input clk,
    input enable,
    input [$clog2(DATA_WIDTH):0]    polyn_grade,        // Orden del polinomio a reducir
    input [DATA_WIDTH:0]            polyn_red_in,       // Polinomio primitivo
    input [2*DATA_WIDTH-1:0]        reduc_in,           // Polinomio a reducir
    output reg [DATA_WIDTH-1:0]     out                 // Salida normal
);
    //////////////////////////////////////////////////////////
    // Generacion de los operandos
    //////////////////////////////////////////////////////////

    wire [DATA_WIDTH:0]         polyn_red_op [0:DATA_WIDTH];
    wire [DATA_WIDTH:0]         polyn_red_op_out;
    wire [2*DATA_WIDTH-1:0]     reduc_op [0:DATA_WIDTH];
    wire [2*DATA_WIDTH-1:0]     reduc_op_out;

    /* Creo N conexiones, customizando para operar con cualquier grado de polinomio primitivo */
    genvar i;
    generate
        for (i = 0; i <= DATA_WIDTH; i = i + 1) begin
            assign polyn_red_op[i] =    (i > 1) ? {polyn_red_in[i:0],{DATA_WIDTH-i{1'b0}}} : 'b0;
            assign reduc_op[i] =        (i > 1) ? {reduc_in[(2*i)-1:0],{(2*(DATA_WIDTH-i)){1'b0}}} : 'b0;
        end
    endgenerate

    assign polyn_red_op_out = polyn_red_op[polyn_grade];
    assign reduc_op_out = reduc_op[polyn_grade];

    //////////////////////////////////////////////////////////
    // Inversion de las entradas - Para reducir el polinomio
    //////////////////////////////////////////////////////////

    wire [2*DATA_WIDTH-1:0]     reduc_in_n;         // Polinomio a reducir invertido
    wire [DATA_WIDTH:0]         polyn_red_in_n;     // Polinomio primitivo invertido

    wire [2*DATA_WIDTH-1:0]     reduc;              // Salidas para la siguiente etapa
    wire [DATA_WIDTH:0]         polyn_red;

    bit_order_inversion #(2*DATA_WIDTH) bit_inv_reduc(
        .a(reduc_op_out),
        .a_n(reduc_in_n)
    );
    bit_order_inversion #(DATA_WIDTH+1) bit_inv_polym(
        .a(polyn_red_op_out),
        .a_n(polyn_red_in_n)
    );

    // Invierto o no las entradas dependiendo si es polinomio de reduccion o no
    assign reduc =      reduc_in_n;
    assign polyn_red =  polyn_red_in_n;

    //////////////////////////////////////////////////////////
    // Sumas parciales
    //////////////////////////////////////////////////////////

    wire [DATA_WIDTH:0]     partial_sum [0:DATA_WIDTH-1];

    wire [DATA_WIDTH:0]     a_sum [0:DATA_WIDTH-2];
    wire [DATA_WIDTH:0]     b_sum [0:DATA_WIDTH-2];

    // La primera suma parcial del modulo de reduccion es el la primera parte del polinomio a reducir
    assign partial_sum[0] = reduc[0 +: (DATA_WIDTH+1)];
    

    /* Creo los N adders de N bits de ancho */
    generate
        for (i = 0; i < DATA_WIDTH-1; i = i + 1) begin      // 0 a 3
            cl_add #(DATA_WIDTH+1) adder0(
                .a(a_sum[i]),
                .b(b_sum[i]),
                .sum(partial_sum[i+1])                      // 0 a 4
            );

            // Asigno las entradas de las sumas parciales
            assign a_sum[i] = {reduc[DATA_WIDTH+1+i],partial_sum[i][1 +: DATA_WIDTH]};  
            assign b_sum[i] = a_sum[i][0] ? polyn_red : 0;  
            
        end
    endgenerate

    //////////////////////////////////////////////////////////
    // Selecciono la salida correcta
    //////////////////////////////////////////////////////////

    wire [DATA_WIDTH-1:0] poly_mux_out;
    wire [DATA_WIDTH-1:0] poly_out [0:DATA_WIDTH];

    generate
        for (i = 0; i <= DATA_WIDTH; i = i + 1) begin           // 0 a 5
            assign poly_out[i] = (i > 1) ? {partial_sum[i-1][i:1],{DATA_WIDTH-i{1'b0}}} : 'b0;
        end
    endgenerate

    assign poly_mux_out = poly_out[polyn_grade];

    //////////////////////////////////////////////////////////
    // Inversion de las salidas - Para reducir el polinomio
    //////////////////////////////////////////////////////////

    wire [DATA_WIDTH-1:0]       out_poly;       // Salida del polinomio de reduccion

    bit_order_inversion #(DATA_WIDTH) bit_inv_poly_out(
        .a(poly_mux_out),
        .a_n(out_poly)
    );

    //////////////////////////////////////////////////////////
    // Salidas
    //////////////////////////////////////////////////////////

    /* Registrar las salidas */
    always @(posedge clk) begin
        if(!enable) begin
            out  <= 0;
        end else begin 
            out  <= out_poly;
        end
    end 

endmodule