# Give the user some easy overrides for local configuration quirks.
# If you change one of these and it breaks, then you get to keep both pieces.
SHELL = bash
PYTHON = python3

ICARUS_SUFFIX =
IVERILOG = iverilog$(ICARUS_SUFFIX)
VVP = vvp$(ICARUS_SUFFIX)

all: testbench.vvp
	$(VVP) -N $< +vcd

testbench.vvp: ../../Modules/cl_adder/cl_full_adder.v ../../Modules/cl_adder/cl_half_adder.v ../multiplier/partial_mult.v ../../Modules/reduction/reduction.v ../../Modules/cl_adder/cl_rca_adder.v cl_add.v ../../Modules/cl_multiplier/cl_rca_mult.v cl_modules.v bit_order_inversion.v ../utils/input_regs.v ../utils/output_regs.v top.v
	$(IVERILOG) -o $@  $^
	chmod -x $@


clean:
	rm -rf testbench.vvp testbench.vcd


.PHONY: test clean
