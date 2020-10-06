module input_regs #(
    parameter DATA_WIDTH = 32
)(
    input                       clk,
    input                       resetn,
    input                       in_serial,
    output reg [DATA_WIDTH-1:0] out_parallel
);
    integer counter;

    always @(posedge clk) begin
        if(!resetn) begin
            out_parallel    <= 0;
            counter         <= 0;
        end else begin
            if (counter < DATA_WIDTH) begin
                out_parallel[counter]   <= in_serial;
                counter                 <= counter + 1;
            end else begin
                counter                 <= 0;
            end
        end
    end

endmodule