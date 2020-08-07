# Give the user some easy overrides for local configuration quirks.
# If you change one of these and it breaks, then you get to keep both pieces.
SHELL = bash
PYTHON = python3

ICARUS_SUFFIX =
IVERILOG = iverilog$(ICARUS_SUFFIX)
VVP = vvp$(ICARUS_SUFFIX)

all: testbench.vvp
	$(VVP) -N $< +vcd

testbench.vvp: ../adder/full_adder.v ../adder/half_adder.v partial_mult.v ../adder/rca_adder.v rca_mult.v ../utils/input_regs.v ../utils/output_regs.v top.v
	$(IVERILOG) -o $@  $^
	chmod -x $@


clean:
	rm -rf testbench.vvp testbench.vcd


.PHONY: test clean
