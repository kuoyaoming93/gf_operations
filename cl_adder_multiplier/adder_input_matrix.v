module adder_input_matrix #(
    parameter DATA_WIDTH = 32
)(
    input sum_funct,
    input [DATA_WIDTH-1:0]   partial_sum [0:DATA_WIDTH-1],
    input [DATA_WIDTH-1:0]   carry,
    input [DATA_WIDTH-1:0]   partial_result,

    input [DATA_WIDTH-1:0] a,
    input [DATA_WIDTH-1:0] b,
    output reg [DATA_WIDTH-1:0] a_sum [0:DATA_WIDTH-2],
    output reg [DATA_WIDTH-1:0] b_sum [0:DATA_WIDTH-2]
);


    integer i;
    always @* begin
        for (i = 1; i < DATA_WIDTH-1; i = i+1) begin
            // Asigno la entrada de las sumas parciales 
            a_sum[i] <= {carry[i],partial_sum[i][1 +: DATA_WIDTH-1]};  
            b_sum[i] <= partial_products[i+1];  
        end
    end

    always @* begin
        if(sum_funct) begin
            a_sum[0] <= a;
            b_sum[0] <= b;
        end else begin
            a_sum[0] <= {carry[0],partial_sum[0][1 +: DATA_WIDTH-1]}; 
            b_sum[0] <= partial_products[1]; 
        end

    end



endmodule