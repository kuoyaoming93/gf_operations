`timescale 1 ns / 1 ps

module testbench;

    parameter DATA_WIDTH = 32;
    parameter CYCLE = 5.2;
    
    wire    [DATA_WIDTH-1:0]  sum;
    wire                      carry;
    reg     [DATA_WIDTH-1:0]  a;
    reg     [DATA_WIDTH-1:0]  b;
    reg                       clk,enable;

    integer i;

    //==================================================
    // Clock
    //==================================================
    initial begin
        clk = 0; // Procedural assignment
        forever #(CYCLE/2) clk = ~clk;
    end 
    
    //==================================================
    // DUT
    //==================================================
    rca_adder #(DATA_WIDTH) dut0(
        .clk(clk),
        .enable(enable),
        .in_sum_a(a),
        .in_sum_b(b),
        .out_sum_result(sum),
        .out_carry(carry)
    );

    initial begin
		$dumpfile("testbench.vcd");
		$dumpvars(0, testbench);

        a = 0;
        b = 0;

        reset();
        
        @(posedge clk)
        for(i = 0; i<10; i = i+1)
        begin
            suma();
            #(2*CYCLE);
        end
        
        $finish;
    end
    
    //==================================================
    // Common Tasks
    //==================================================
    task reset;
        begin
            @(negedge clk)
            enable <= 1'b0;
            a <= 0;
            b <= 0;
            
            @(negedge clk)
            enable <= 1'b1;
        end
    endtask 
    
    task suma;
    begin
        a <= $urandom%(2**DATA_WIDTH-1); 
        b <= $urandom%(2**DATA_WIDTH-1); 
    end
    endtask

endmodule