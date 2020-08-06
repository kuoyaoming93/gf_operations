# Give the user some easy overrides for local configuration quirks.
# If you change one of these and it breaks, then you get to keep both pieces.
SHELL = bash
PYTHON = python3

ICARUS_SUFFIX =
IVERILOG = iverilog$(ICARUS_SUFFIX)
VVP = vvp$(ICARUS_SUFFIX)

all: testbench.vvp
	$(VVP) -N $< +vcd

testbench.vvp: testbench.v ../../Modules/cl_adder/cl_full_adder.v ../../Modules/cl_adder/cl_half_adder.v ../../Modules/multiplier/partial_mult.v ../../Modules/cl_adder/cl_rca_adder.v ../../Modules/cl_multiplier/cl_rca_mult.v cl_mult.v ../adder_comparison/cl_add.v ../../Modules/adder/half_adder.v ../../Modules/adder/full_adder.v ../../Modules/adder/rca_adder.v ../../Modules/multiplier/rca_mult.v top.v
	$(IVERILOG) -o $@  $^
	chmod -x $@


clean:
	rm -rf testbench.vvp testbench.vcd


.PHONY: test clean
