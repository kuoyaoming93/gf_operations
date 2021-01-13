RTL_SOURCES = cl_add.v partial_mult.v mult.v testmod/cl_full_adder.v testmod/cl_half_adder.v testmod/cl_rca_adder.v testmod/cl_rca_mult.v

ICARUS_SUFFIX =
IVERILOG = iverilog$(ICARUS_SUFFIX)
VVP = vvp$(ICARUS_SUFFIX)

all: testbench.vvp
	$(VVP) -N $< +vcd

testbench.vvp: testbench.v $(RTL_SOURCES)
	$(IVERILOG) -o $@  $^
	chmod -x $@


clean:
	rm -rf testbench.vvp testbench.vcd


.PHONY: test clean
