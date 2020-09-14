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
            else begin 
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
    // Modulo de multiplicaciones parciales
    //////////////////////////////////////////////////////////

    wire [DATA_WIDTH-1:0]   in_partial_mult_a;
    wire                    in_partial_mult_b;
    wire [DATA_WIDTH-1:0]   partial_products;
    reg [DATA_WIDTH-1:0]    partial_products_reg;
    reg [DATA_WIDTH-1:0]    pp_prev;

    always @(posedge clk) begin
        if(!count) begin
            partial_products_reg    <= 0;
            pp_prev                 <= 0;
        end
        else begin
            partial_products_reg    <= partial_products;
            pp_prev                 <= partial_products_reg;
        end
    end

    assign in_partial_mult_a = poly_red_inv_reg;
    assign in_partial_mult_b = out_adder_reg[0] ? 1 : 0;

    partial_mult #(DATA_WIDTH) pmult0 (
        .a(in_partial_mult_a),
        .b(in_partial_mult_b),
        .out(partial_products)
    );

    //////////////////////////////////////////////////////////
    // Modulo de sumas parciales
    //////////////////////////////////////////////////////////

    // Module connections
    wire [DATA_WIDTH-1:0]   in_adder_a;
    wire [DATA_WIDTH-1:0]   in_adder_b;
    wire [DATA_WIDTH-1:0]   out_adder_sum;
    wire                    out_adder_carry;

    // Registers
    reg [DATA_WIDTH-1:0]    out_adder_reg;
    reg                     out_carry_reg;

    always @(posedge clk) begin
        if (!count_d2) begin
            out_adder_reg       <= 0;
            out_carry_reg       <= 0;
        end else begin
            out_adder_reg               <= out_adder_sum;
            out_carry_reg               <= out_adder_carry;
        end
    end
    
    assign in_adder_a = ;
    assign in_adder_b = ;

    rca_adder #(DATA_WIDTH) adder0(
        .a(in_adder_a),
        .b(in_adder_b),
        .sum(out_adder_sum),
        .co(out_adder_carry)
    );


endmodule
