module red_test #(
    parameter DATA_WIDTH = 10
) (
    input clk,
    input enable,
    input [$clog2(DATA_WIDTH):0]    polyn_grade,        // Orden del polinomio a reducir
    input [DATA_WIDTH:0]            polyn_red_in,       // Polinomio primitivo
    input [2*DATA_WIDTH-1:0]        reduc_in,           // Polinomio a reducir
    output [DATA_WIDTH-1:0]         out                 // Salida normal
);
    reg [$clog2(DATA_WIDTH):0]  in_polyn_grade;
    reg [DATA_WIDTH:0]          in_polyn_red;
    reg [2*DATA_WIDTH-1:0]      in_reduc;

    /* Registrar las salidas */
    always @(posedge clk) begin
        if(!enable) begin
            in_polyn_grade  <= 0;
            in_polyn_red    <= 0;
            in_reduc        <= 0;
        end else begin 
            in_polyn_grade  <= polyn_grade;
            in_polyn_red    <= polyn_red_in;
            in_reduc        <= reduc_in;
        end
    end 

    //////////////////////////////////////////////////////////
    // Generacion de los operandos
    //////////////////////////////////////////////////////////

    wire [DATA_WIDTH:0]         polyn_red_op [0:DATA_WIDTH];
    wire [2*DATA_WIDTH-1:0]     reduc_op [0:DATA_WIDTH];

    wire [2*DATA_WIDTH-1:0]     reduc;              // Salidas para la siguiente etapa
    wire [DATA_WIDTH:0]         polyn_red;

    /* Creo N conexiones, customizando para operar con cualquier grado de polinomio primitivo */
    genvar i;
    generate
        for (i = 0; i <= DATA_WIDTH; i = i + 1) begin
            assign polyn_red_op[i] =    (i > 1) ? {in_polyn_red[i:0],{DATA_WIDTH-i{1'b0}}} : 'b0;
            assign reduc_op[i] =        (i > 1) ? {in_reduc[(2*i)-1:0],{(2*(DATA_WIDTH-i)){1'b0}}} : 'b0;
        end
    endgenerate

    assign polyn_red = polyn_red_op[in_polyn_grade];
    assign reduc = reduc_op[in_polyn_grade];

    //////////////////////////////////////////////////////////
    // Sumas parciales
    //////////////////////////////////////////////////////////

    wire [DATA_WIDTH:0]     partial_sum [0:DATA_WIDTH-1];

    wire [DATA_WIDTH:0]     a_sum [0:DATA_WIDTH-2];
    wire [DATA_WIDTH:0]     b_sum [0:DATA_WIDTH-2];

    // La primera suma parcial del modulo de reduccion es el la primera parte del polinomio a reducir
    assign partial_sum[0] = reduc[2*DATA_WIDTH-1:2*DATA_WIDTH-1-DATA_WIDTH];
    

    /* Creo los N adders de N bits de ancho */
    generate
        for (i = 0; i < DATA_WIDTH-1; i = i + 1) begin      // 0 a 3
            cl_add #(DATA_WIDTH+1) adder0(
                .a(a_sum[i]),
                .b(b_sum[i]),
                .sum(partial_sum[i+1])                      // 0 a 4
            );

            // Asigno las entradas de las sumas parciales
            assign a_sum[i] = {partial_sum[i][DATA_WIDTH-1:0],reduc[DATA_WIDTH-2-i]};  
            assign b_sum[i] = a_sum[i][DATA_WIDTH] ? polyn_red : 0;  
            
        end
    endgenerate

    //////////////////////////////////////////////////////////
    // Selecciono la salida correcta
    //////////////////////////////////////////////////////////

    wire [DATA_WIDTH-1:0] poly_mux_out;
    wire [DATA_WIDTH-1:0] poly_out [0:DATA_WIDTH];

    generate
        for (i = 0; i <= DATA_WIDTH; i = i + 1) begin           // 0 a 5
            assign poly_out[i] = (i > 1) ? {{DATA_WIDTH-i{1'b0}},partial_sum[i-1][DATA_WIDTH-1:DATA_WIDTH-i]} : 'b0;
        end
    endgenerate

    assign poly_mux_out = poly_out[in_polyn_grade];

    //////////////////////////////////////////////////////////
    // Salidas
    //////////////////////////////////////////////////////////

    /* Registrar las salidas */
    always @(posedge clk) begin
        if(!enable) begin
            out  <= 0;
        end else begin 
            out  <= poly_mux_out;
        end
    end 

endmodule