# Give the user some easy overrides for local configuration quirks.
# If you change one of these and it breaks, then you get to keep both pieces.
SHELL = bash
PYTHON = python3

ICARUS_SUFFIX =
IVERILOG = iverilog$(ICARUS_SUFFIX)
VVP = vvp$(ICARUS_SUFFIX)

all: testbench.vvp
	$(VVP) -N $< +vcd

testbench.vvp: ../cl_adder/cl_full_adder.v ../cl_adder/cl_half_adder.v ../multiplier/partial_mult.v ../reduction/reduction.v ../cl_adder/cl_rca_adder.v cl_add.v ../cl_multiplier/cl_rca_mult.v cl_modules.v bit_order_inversion.v top.v testbench.v
	$(IVERILOG) -o $@  $^
	chmod -x $@


clean:
	rm -rf testbench.vvp testbench.vcd


.PHONY: test clean
