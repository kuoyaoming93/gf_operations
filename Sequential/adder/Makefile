# Give the user some easy overrides for local configuration quirks.
# If you change one of these and it breaks, then you get to keep both pieces.
SHELL = bash
PYTHON = python3

ICARUS_SUFFIX =
IVERILOG = iverilog$(ICARUS_SUFFIX)
VVP = vvp$(ICARUS_SUFFIX)

test: testbench.vvp
	$(VVP) -N $< +vcd

testbench.vvp: testbench.v rca_adder.v full_adder.v half_adder.v normal_adder.v 
	$(IVERILOG) -o $@  $^
	chmod -x $@

top: top.vvp
	$(VVP) -N $<

top.vvp: rca_adder.v full_adder.v half_adder.v normal_adder.v ../utils/input_regs.v ../utils/output_regs.v top.v
	$(IVERILOG) -o $@  $^
	chmod -x $@

clean:
	rm -rf *.vvp *.vcd


.PHONY: test top clean
