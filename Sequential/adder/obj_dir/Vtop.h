// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Primary design header
//
// This header should be included by all source files instantiating the design.
// The class here is then constructed to instantiate the design.
// See the Verilator manual for examples.

#ifndef _VTOP_H_
#define _VTOP_H_  // guard

#include "verilated.h"

//==========

class Vtop__Syms;

//----------

VL_MODULE(Vtop) {
  public:
    
    // PORTS
    // The application code writes and reads these signals to
    // propagate new values into/out from the Verilated model.
    VL_IN8(clk,0,0);
    VL_IN8(resetn,0,0);
    VL_IN8(enable,0,0);
    VL_IN8(a,0,0);
    VL_IN8(b,0,0);
    VL_OUT8(sum,0,0);
    VL_OUT8(out_carry,0,0);
    
    // LOCAL SIGNALS
    // Internals; generally not touched by application code
    IData/*31:0*/ top__DOT__in_sum_a;
    IData/*31:0*/ top__DOT__in_sum_b;
    IData/*31:0*/ top__DOT__out_sum_result;
    IData/*31:0*/ top__DOT__input0__DOT__counter;
    IData/*31:0*/ top__DOT__input1__DOT__counter;
    IData/*31:0*/ top__DOT__output0__DOT__counter;
    IData/*31:0*/ top__DOT__dut0__DOT__sum;
    IData/*31:0*/ top__DOT__dut0__DOT__carry_array;
    
    // LOCAL VARIABLES
    // Internals; generally not touched by application code
    CData/*0:0*/ top__DOT__dut0__DOT____Vcellout__genblk1__BRA__1__KET____DOT__fa0__co;
    CData/*0:0*/ top__DOT__dut0__DOT____Vcellout__genblk1__BRA__2__KET____DOT__fa0__co;
    CData/*0:0*/ top__DOT__dut0__DOT____Vcellout__genblk1__BRA__3__KET____DOT__fa0__co;
    CData/*0:0*/ top__DOT__dut0__DOT____Vcellout__genblk1__BRA__4__KET____DOT__fa0__co;
    CData/*0:0*/ top__DOT__dut0__DOT____Vcellout__genblk1__BRA__5__KET____DOT__fa0__co;
    CData/*0:0*/ top__DOT__dut0__DOT____Vcellout__genblk1__BRA__6__KET____DOT__fa0__co;
    CData/*0:0*/ top__DOT__dut0__DOT____Vcellout__genblk1__BRA__7__KET____DOT__fa0__co;
    CData/*0:0*/ top__DOT__dut0__DOT____Vcellout__genblk1__BRA__8__KET____DOT__fa0__co;
    CData/*0:0*/ top__DOT__dut0__DOT____Vcellout__genblk1__BRA__9__KET____DOT__fa0__co;
    CData/*0:0*/ top__DOT__dut0__DOT____Vcellout__genblk1__BRA__10__KET____DOT__fa0__co;
    CData/*0:0*/ top__DOT__dut0__DOT____Vcellout__genblk1__BRA__11__KET____DOT__fa0__co;
    CData/*0:0*/ top__DOT__dut0__DOT____Vcellout__genblk1__BRA__12__KET____DOT__fa0__co;
    CData/*0:0*/ top__DOT__dut0__DOT____Vcellout__genblk1__BRA__13__KET____DOT__fa0__co;
    CData/*0:0*/ top__DOT__dut0__DOT____Vcellout__genblk1__BRA__14__KET____DOT__fa0__co;
    CData/*0:0*/ top__DOT__dut0__DOT____Vcellout__genblk1__BRA__15__KET____DOT__fa0__co;
    CData/*0:0*/ top__DOT__dut0__DOT____Vcellout__genblk1__BRA__16__KET____DOT__fa0__co;
    CData/*0:0*/ top__DOT__dut0__DOT____Vcellout__genblk1__BRA__17__KET____DOT__fa0__co;
    CData/*0:0*/ top__DOT__dut0__DOT____Vcellout__genblk1__BRA__18__KET____DOT__fa0__co;
    CData/*0:0*/ top__DOT__dut0__DOT____Vcellout__genblk1__BRA__19__KET____DOT__fa0__co;
    CData/*0:0*/ top__DOT__dut0__DOT____Vcellout__genblk1__BRA__20__KET____DOT__fa0__co;
    CData/*0:0*/ top__DOT__dut0__DOT____Vcellout__genblk1__BRA__21__KET____DOT__fa0__co;
    CData/*0:0*/ top__DOT__dut0__DOT____Vcellout__genblk1__BRA__22__KET____DOT__fa0__co;
    CData/*0:0*/ top__DOT__dut0__DOT____Vcellout__genblk1__BRA__23__KET____DOT__fa0__co;
    CData/*0:0*/ top__DOT__dut0__DOT____Vcellout__genblk1__BRA__24__KET____DOT__fa0__co;
    CData/*0:0*/ top__DOT__dut0__DOT____Vcellout__genblk1__BRA__25__KET____DOT__fa0__co;
    CData/*0:0*/ top__DOT__dut0__DOT____Vcellout__genblk1__BRA__26__KET____DOT__fa0__co;
    CData/*0:0*/ top__DOT__dut0__DOT____Vcellout__genblk1__BRA__27__KET____DOT__fa0__co;
    CData/*0:0*/ top__DOT__dut0__DOT____Vcellout__genblk1__BRA__28__KET____DOT__fa0__co;
    CData/*0:0*/ top__DOT__dut0__DOT____Vcellout__genblk1__BRA__29__KET____DOT__fa0__co;
    CData/*0:0*/ top__DOT__dut0__DOT____Vcellout__genblk1__BRA__30__KET____DOT__fa0__co;
    CData/*0:0*/ top__DOT__dut0__DOT____Vcellout__genblk1__BRA__31__KET____DOT__fa0__co;
    CData/*0:0*/ __Vclklast__TOP__clk;
    IData/*31:0*/ __Vchglast__TOP__top__DOT__dut0__DOT__carry_array;
    
    // INTERNAL VARIABLES
    // Internals; generally not touched by application code
    Vtop__Syms* __VlSymsp;  // Symbol table
    
    // CONSTRUCTORS
  private:
    VL_UNCOPYABLE(Vtop);  ///< Copying not allowed
  public:
    /// Construct the model; called by application code
    /// The special name  may be used to make a wrapper with a
    /// single model invisible with respect to DPI scope names.
    Vtop(const char* name = "TOP");
    /// Destroy the model; called (often implicitly) by application code
    ~Vtop();
    
    // API METHODS
    /// Evaluate the model.  Application must call when inputs change.
    void eval() { eval_step(); }
    /// Evaluate when calling multiple units/models per time step.
    void eval_step();
    /// Evaluate at end of a timestep for tracing, when using eval_step().
    /// Application must call after all eval() and before time changes.
    void eval_end_step() {}
    /// Simulation complete, run final blocks.  Application must call on completion.
    void final();
    
    // INTERNAL METHODS
  private:
    static void _eval_initial_loop(Vtop__Syms* __restrict vlSymsp);
  public:
    void __Vconfigure(Vtop__Syms* symsp, bool first);
  private:
    static QData _change_request(Vtop__Syms* __restrict vlSymsp);
  public:
    static void _combo__TOP__3(Vtop__Syms* __restrict vlSymsp);
  private:
    void _ctor_var_reset() VL_ATTR_COLD;
  public:
    static void _eval(Vtop__Syms* __restrict vlSymsp);
  private:
#ifdef VL_DEBUG
    void _eval_debug_assertions();
#endif  // VL_DEBUG
  public:
    static void _eval_initial(Vtop__Syms* __restrict vlSymsp) VL_ATTR_COLD;
    static void _eval_settle(Vtop__Syms* __restrict vlSymsp) VL_ATTR_COLD;
    static void _sequent__TOP__1(Vtop__Syms* __restrict vlSymsp);
    static void _settle__TOP__2(Vtop__Syms* __restrict vlSymsp) VL_ATTR_COLD;
} VL_ATTR_ALIGNED(VL_CACHE_LINE_BYTES);

//----------


#endif  // guard
