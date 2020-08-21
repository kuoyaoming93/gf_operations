RTL_SOURCES = rca_adder.v full_adder.v half_adder.v ../utils/input_regs.v ../utils/output_regs.v

ICARUS_SUFFIX =
IVERILOG = iverilog$(ICARUS_SUFFIX)
VVP = vvp$(ICARUS_SUFFIX)

VERI = verilator
VERI_FLAGS = -Wall -cc --trace -Wno-STMTDLY -Wno-UNUSED -Wno-INFINITELOOP -Wno-UNOPTFLAT
VERI_TOP = testbench

all: testbench.vvp
	$(VVP) -N $< +vcd

testbench.vvp: testbench.v $(RTL_SOURCES)
	$(IVERILOG) -o $@  $^
	chmod -x $@

top: top.vvp
	$(VVP) -N $<

top.vvp: top.v $(RTL_SOURCES)
	$(IVERILOG) -o $@  $^
	chmod -x $@

clean:
	rm -rf *.vvp *.vcd obj_dir


.PHONY: test top clean
