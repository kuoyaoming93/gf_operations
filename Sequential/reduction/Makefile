TEST_SOURCES = testmod/red_test.v testmod/cl_full_adder.v testmod/cl_half_adder.v testmod/cl_rca_adder.v testmod/cl_rca_mult.v testmod/partial_mult.v
RTL_SOURCES = bit_order_inversion.v cl_add.v red.v $(TEST_SOURCES)

ICARUS_SUFFIX =
IVERILOG = iverilog$(ICARUS_SUFFIX)
VVP = vvp$(ICARUS_SUFFIX)

all: testbench.vvp
	$(VVP) -N $< +vcd

testbench.vvp:  testbench.v $(RTL_SOURCES)
	$(IVERILOG) -o $@  $^
	chmod -x $@


clean:
	rm -rf testbench.vvp testbench.vcd


.PHONY: test clean
