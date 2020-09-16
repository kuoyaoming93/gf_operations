module red #(
    parameter DATA_WIDTH = 4
) (
    input clk,
    input op_enable,
    input [$clog2(DATA_WIDTH):0]    polyn_grade,        // Orden del polinomio a reducir
    input [DATA_WIDTH:0]            polyn_red_in,       // Polinomio primitivo
    input [2*DATA_WIDTH-1:0]        reduc_in,           // Polinomio a reducir
    output [DATA_WIDTH-1:0]         out,                // Salida normal
    output reg                      op_finish
);

    reg [$clog2(DATA_WIDTH):0] count, count_d1, count_d2;

    always @(posedge clk) begin
        if(!op_enable) begin
            count       <= 0;
            count_d1    <= 0;
            count_d2    <= 0;
        end
        else begin
            if(count < DATA_WIDTH) begin
                count       <= count + 1;    
            end
            count_d1    <= count;
            count_d2    <= count_d1;
        end
    end

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

    
    // Registro las salidas para esta etapa
    reg [DATA_WIDTH:0]         poly_red_reg;
    reg [2*DATA_WIDTH-1:0]     reduc_reg;

    always @(posedge clk) begin
        if(!op_enable) begin
            poly_red_reg    <= 0;
            reduc_reg       <= 0;
        end else begin
            poly_red_reg    <= polyn_red_op_out;
            reduc_reg       <= reduc_op_out;
        end
    end

    //////////////////////////////////////////////////////////
    // Inversion de las entradas - Para reducir el polinomio
    //////////////////////////////////////////////////////////

    wire [2*DATA_WIDTH-1:0]     reduc_in_n;         // Polinomio a reducir invertido
    wire [DATA_WIDTH:0]         polyn_red_in_n;     // Polinomio primitivo invertido

    bit_order_inversion #(2*DATA_WIDTH) bit_inv_reduc(
        .a(reduc_reg),
        .a_n(reduc_in_n)
    );
    bit_order_inversion #(DATA_WIDTH+1) bit_inv_polym(
        .a(poly_red_reg),
        .a_n(polyn_red_in_n)
    );

    // Registro las salidas para esta etapa
    reg [DATA_WIDTH:0]         poly_red_inv_reg;
    reg [2*DATA_WIDTH-1:0]     reduc_inv_reg;

    always @(posedge clk) begin
        if(!op_enable) begin
            poly_red_inv_reg    <= 0;
            reduc_inv_reg       <= 0;
        end else begin
            poly_red_inv_reg    <= polyn_red_in_n;
            reduc_inv_reg       <= reduc_in_n;
        end
    end

    //////////////////////////////////////////////////////////
    // Modulo de sumas parciales
    //////////////////////////////////////////////////////////

    // Module connections
    wire [DATA_WIDTH:0]     in_adder_a;
    wire [DATA_WIDTH:0]     in_adder_b;
    wire [DATA_WIDTH:0]     out_adder_sum;
    wire                    bit_selector;

    // Registers
    reg [DATA_WIDTH:0]      out_adder_reg;
    reg [DATA_WIDTH:0]      partial_sum_reg;

    always @(posedge clk) begin
        if (!count_d1) begin
            out_adder_reg       <= 0;
            partial_sum_reg     <= 0;
        end else begin
            out_adder_reg       <= out_adder_sum;
            if(count_d2 == polyn_grade-1)
                partial_sum_reg <= out_adder_sum;
        end
    end
    
    assign in_adder_a = (count_d1==1) ? (reduc_inv_reg[0 +: (DATA_WIDTH+1)]) : ({reduc_inv_reg[DATA_WIDTH-1+count_d1],out_adder_reg[1 +: DATA_WIDTH]});
    assign bit_selector = (count_d1 == 1) ? (reduc_inv_reg[0]) : (out_adder_reg[1]);
    assign in_adder_b = bit_selector ? poly_red_inv_reg : 0;

    cl_add #(DATA_WIDTH+1) adder0(
        .a(in_adder_a),
        .b(in_adder_b),
        .sum(out_adder_sum)
    );  

    //////////////////////////////////////////////////////////
    // Selecciono la salida correcta
    //////////////////////////////////////////////////////////

    wire [DATA_WIDTH-1:0] poly_mux_out;
    wire [DATA_WIDTH-1:0] poly_out [0:DATA_WIDTH];

    generate
        for (i = 0; i <= DATA_WIDTH; i = i + 1) begin           // 0 a 5
            assign poly_out[i] = (i > 1) ? {partial_sum_reg[i:1],{DATA_WIDTH-i{1'b0}}} : 'b0;
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

    assign out = out_poly;

endmodule
