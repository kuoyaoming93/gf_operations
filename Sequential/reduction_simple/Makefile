RTL_SOURCES = bit_order_inversion.v cl_add.v partial_mult.v red.v red_test.v cl_full_adder.v cl_half_adder.v cl_rca_adder.v cl_rca_mult.v

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
