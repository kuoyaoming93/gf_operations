RTL_SOURCES = bit_order_inversion.v cl_add.v ../utils/input_regs.v ../utils/output_regs.v reduction.v top.v

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
