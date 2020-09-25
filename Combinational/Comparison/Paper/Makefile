SHIFT_REG = utils/input_regs.v utils/output_regs.v
ADDER = adder/full_adder.v adder/half_adder.v adder/rca_adder.v
CL_MULT = cl_mult/cl_full_adder.v cl_mult/cl_half_adder.v cl_mult/cl_rca_adder.v cl_mult/partial_mult.v cl_mult/cl_rca_mult.v
REDUC = reduction/cl_add.v reduction/red_test.v
COMP = complete/cl_modules.v complete/bit_order_inversion.v

RTL_SOURCES = $(SHIFT_REG) $(ADDER) $(CL_MULT) $(REDUC) $(COMP)

ICARUS_SUFFIX =
IVERILOG = iverilog$(ICARUS_SUFFIX)
VVP = vvp$(ICARUS_SUFFIX)

all: testbench.vvp
	$(VVP) -N $<
	#$(VVP) -N $< +vcd

testbench.vvp: $(RTL_SOURCES) top.v
	$(IVERILOG) -o $@  $^
	chmod -x $@


clean:
	rm -rf testbench.vvp testbench.vcd


.PHONY: test clean
