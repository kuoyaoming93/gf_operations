module output_regs #(
    parameter DATA_WIDTH = 32
)(
    input                       clk,
    input                       resetn,
    input [DATA_WIDTH-1:0]      in_parallel,
    output reg                  out_serial
);
    integer counter;

    always @(posedge clk) begin
        if(!resetn) begin
            out_serial      <= 0;
            counter         <= 0;
        end else begin
            if (counter < DATA_WIDTH) begin
                out_serial      <= in_parallel[counter];
                counter         <= counter + 1;
            end else begin
                counter         <= 0;
            end
        end
    end

endmodule