RTL_SOURCES = ../adder/full_adder.v ../adder/half_adder.v partial_mult.v ../adder/rca_adder.v rca_mult.v ../utils/input_regs.v ../utils/output_regs.v

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
