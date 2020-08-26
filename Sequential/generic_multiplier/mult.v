module mult #(
    parameter DATA_WIDTH = 32
)(
    input clk,
    input op_enable,
    input [$clog2(DATA_WIDTH):0]    in_width,
    input [DATA_WIDTH-1:0]          in_mult_a,
    input [DATA_WIDTH-1:0]          in_mult_b,
    output reg [2*DATA_WIDTH-1:0]   out_mult_result,
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

    assign in_partial_mult_a = in_mult_a;
    assign in_partial_mult_b = count ? in_mult_b[count-1] : 0;

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
    reg [DATA_WIDTH-1:0]    partial_result;
    reg                     out_carry_reg;
    reg [DATA_WIDTH-1:0]    partial_sum;
    reg                     partial_carry;

    always @(posedge clk) begin
        if (!count_d2) begin
            out_adder_reg       <= 0;
            out_carry_reg       <= 0;
            partial_result      <= 0;
            partial_sum         <= 0;
            partial_carry       <= 0;
        end else begin
            out_adder_reg               <= out_adder_sum;
            out_carry_reg               <= out_adder_carry;
            partial_result[count_d2]    <= out_adder_sum[0];
            
            if (count_d2 == 1)
                partial_result[0]       <= pp_prev[0];
            if (count_d2 == in_width-1) begin
                partial_sum             <= out_adder_sum;
                partial_carry           <= out_adder_carry;
            end
        end
    end

    wire [DATA_WIDTH-2:0] adder_mux; 
    assign adder_mux = (count_d2 ==1) ? pp_prev[DATA_WIDTH-1:1] : out_adder_reg[DATA_WIDTH-1:1];
    
    assign in_adder_a = {out_carry_reg,adder_mux};
    assign in_adder_b = partial_products_reg;

    rca_adder #(DATA_WIDTH) adder0(
        .a(in_adder_a),
        .b(in_adder_b),
        .sum(out_adder_sum),
        .co(out_adder_carry)
    );

    //////////////////////////////////////////////////////////
    // Selecciono la salida correcta
    //////////////////////////////////////////////////////////

    wire [2*DATA_WIDTH-1:0] mult_mux_out;
    wire [2*DATA_WIDTH-1:0] mult_out [0:DATA_WIDTH];

    genvar i;
    generate
        for (i = 0; i <= DATA_WIDTH; i = i + 1) begin           
            assign mult_out[i] = (i > 1) ? {partial_carry,{DATA_WIDTH-i{1'b0}},partial_sum[DATA_WIDTH-1:1],partial_result[i-1:0]} : 'b0;
        end
    endgenerate
    //assign mult_out[DATA_WIDTH] = {partial_carry,partial_sum[DATA_WIDTH-1:1],partial_result};
    assign mult_mux_out = mult_out[in_width];


    //////////////////////////////////////////////////////////
    // Salidas
    //////////////////////////////////////////////////////////

    always @(posedge clk) begin
        if (!op_enable) begin
            out_mult_result <= 0;
            op_finish       <= 0;
        end else begin
            out_mult_result <= mult_mux_out;
            if(count_d2 >= in_width) begin
                op_finish <= 1;
            end
        end
    end

endmodule