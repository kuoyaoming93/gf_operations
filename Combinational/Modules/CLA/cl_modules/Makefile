# Give the user some easy overrides for local configuration quirks.
# If you change one of these and it breaks, then you get to keep both pieces.
SHELL = bash
PYTHON = python3

ICARUS_SUFFIX =
IVERILOG = iverilog$(ICARUS_SUFFIX)
VVP = vvp$(ICARUS_SUFFIX)

all: testbench.vvp
	$(VVP) -N $< +vcd

testbench.vvp: full_adder.v partial_mult.v cl_cla_adder.v cl_modules.v bit_order_inversion.v red_test.v top.v testbench.v cl_add.v ../../RCA/cl_multiplier/cl_rca_mult.v ../../RCA/cl_adder/cl_rca_adder.v ../../RCA/cl_adder/cl_full_adder.v ../../RCA/cl_adder/cl_half_adder.v  
	$(IVERILOG) -o $@  $^
	chmod -x $@


clean:
	rm -rf testbench.vvp testbench.vcd


.PHONY: test clean
