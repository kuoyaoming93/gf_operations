// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtop.h for the primary calling header

#include "Vtop.h"
#include "Vtop__Syms.h"

//==========

VL_CTOR_IMP(Vtop) {
    Vtop__Syms* __restrict vlSymsp = __VlSymsp = new Vtop__Syms(this, name());
    Vtop* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Reset internal values
    
    // Reset structure values
    _ctor_var_reset();
}

void Vtop::__Vconfigure(Vtop__Syms* vlSymsp, bool first) {
    if (false && first) {}  // Prevent unused
    this->__VlSymsp = vlSymsp;
    if (false && this->__VlSymsp) {}  // Prevent unused
    Verilated::timeunit(-12);
    Verilated::timeprecision(-12);
}

Vtop::~Vtop() {
    VL_DO_CLEAR(delete __VlSymsp, __VlSymsp = NULL);
}

void Vtop::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vtop::eval\n"); );
    Vtop__Syms* __restrict vlSymsp = this->__VlSymsp;  // Setup global symbol table
    Vtop* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
#ifdef VL_DEBUG
    // Debug assertions
    _eval_debug_assertions();
#endif  // VL_DEBUG
    // Initialize
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) _eval_initial_loop(vlSymsp);
    // Evaluate till stable
    int __VclockLoop = 0;
    QData __Vchange = 1;
    do {
        VL_DEBUG_IF(VL_DBG_MSGF("+ Clock loop\n"););
        _eval(vlSymsp);
        if (VL_UNLIKELY(++__VclockLoop > 100)) {
            // About to fail, so enable debug to see what's not settling.
            // Note you must run make with OPT=-DVL_DEBUG for debug prints.
            int __Vsaved_debug = Verilated::debug();
            Verilated::debug(1);
            __Vchange = _change_request(vlSymsp);
            Verilated::debug(__Vsaved_debug);
            VL_FATAL_MT("top.v", 1, "",
                "Verilated model didn't converge\n"
                "- See DIDNOTCONVERGE in the Verilator manual");
        } else {
            __Vchange = _change_request(vlSymsp);
        }
    } while (VL_UNLIKELY(__Vchange));
}

void Vtop::_eval_initial_loop(Vtop__Syms* __restrict vlSymsp) {
    vlSymsp->__Vm_didInit = true;
    _eval_initial(vlSymsp);
    // Evaluate till stable
    int __VclockLoop = 0;
    QData __Vchange = 1;
    do {
        _eval_settle(vlSymsp);
        _eval(vlSymsp);
        if (VL_UNLIKELY(++__VclockLoop > 100)) {
            // About to fail, so enable debug to see what's not settling.
            // Note you must run make with OPT=-DVL_DEBUG for debug prints.
            int __Vsaved_debug = Verilated::debug();
            Verilated::debug(1);
            __Vchange = _change_request(vlSymsp);
            Verilated::debug(__Vsaved_debug);
            VL_FATAL_MT("top.v", 1, "",
                "Verilated model didn't DC converge\n"
                "- See DIDNOTCONVERGE in the Verilator manual");
        } else {
            __Vchange = _change_request(vlSymsp);
        }
    } while (VL_UNLIKELY(__Vchange));
}

VL_INLINE_OPT void Vtop::_sequent__TOP__1(Vtop__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop::_sequent__TOP__1\n"); );
    Vtop* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->resetn) {
        if (VL_GTS_III(1,32,32, 0x20U, vlTOPp->top__DOT__output0__DOT__counter)) {
            vlTOPp->sum = (1U & (vlTOPp->top__DOT__out_sum_result 
                                 >> (0x1fU & vlTOPp->top__DOT__output0__DOT__counter)));
            vlTOPp->top__DOT__output0__DOT__counter 
                = ((IData)(1U) + vlTOPp->top__DOT__output0__DOT__counter);
        } else {
            vlTOPp->top__DOT__output0__DOT__counter = 0U;
        }
    } else {
        vlTOPp->top__DOT__output0__DOT__counter = 0U;
        vlTOPp->sum = 0U;
    }
    vlTOPp->out_carry = ((IData)(vlTOPp->enable) & 
                         (vlTOPp->top__DOT__dut0__DOT__carry_array 
                          >> 0x1fU));
    if (vlTOPp->resetn) {
        if (VL_GTS_III(1,32,32, 0x20U, vlTOPp->top__DOT__input1__DOT__counter)) {
            vlTOPp->top__DOT__in_sum_b = (((~ ((IData)(1U) 
                                               << (0x1fU 
                                                   & vlTOPp->top__DOT__input1__DOT__counter))) 
                                           & vlTOPp->top__DOT__in_sum_b) 
                                          | ((IData)(vlTOPp->b) 
                                             << (0x1fU 
                                                 & vlTOPp->top__DOT__input1__DOT__counter)));
            vlTOPp->top__DOT__input1__DOT__counter 
                = ((IData)(1U) + vlTOPp->top__DOT__input1__DOT__counter);
        } else {
            vlTOPp->top__DOT__input1__DOT__counter = 0U;
        }
    } else {
        vlTOPp->top__DOT__input1__DOT__counter = 0U;
        vlTOPp->top__DOT__in_sum_b = 0U;
    }
    if (vlTOPp->resetn) {
        if (VL_GTS_III(1,32,32, 0x20U, vlTOPp->top__DOT__input0__DOT__counter)) {
            vlTOPp->top__DOT__in_sum_a = (((~ ((IData)(1U) 
                                               << (0x1fU 
                                                   & vlTOPp->top__DOT__input0__DOT__counter))) 
                                           & vlTOPp->top__DOT__in_sum_a) 
                                          | ((IData)(vlTOPp->a) 
                                             << (0x1fU 
                                                 & vlTOPp->top__DOT__input0__DOT__counter)));
            vlTOPp->top__DOT__input0__DOT__counter 
                = ((IData)(1U) + vlTOPp->top__DOT__input0__DOT__counter);
        } else {
            vlTOPp->top__DOT__input0__DOT__counter = 0U;
        }
    } else {
        vlTOPp->top__DOT__input0__DOT__counter = 0U;
        vlTOPp->top__DOT__in_sum_a = 0U;
    }
    vlTOPp->top__DOT__out_sum_result = ((IData)(vlTOPp->enable)
                                         ? vlTOPp->top__DOT__dut0__DOT__sum
                                         : 0U);
    vlTOPp->top__DOT__dut0__DOT__carry_array = ((0xfffffffeU 
                                                 & vlTOPp->top__DOT__dut0__DOT__carry_array) 
                                                | (1U 
                                                   & (vlTOPp->top__DOT__in_sum_a 
                                                      & vlTOPp->top__DOT__in_sum_b)));
    vlTOPp->top__DOT__dut0__DOT__sum = ((0xfffffffeU 
                                         & vlTOPp->top__DOT__dut0__DOT__sum) 
                                        | (1U & (vlTOPp->top__DOT__in_sum_a 
                                                 ^ vlTOPp->top__DOT__in_sum_b)));
}

void Vtop::_settle__TOP__2(Vtop__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop::_settle__TOP__2\n"); );
    Vtop* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->top__DOT__dut0__DOT__carry_array = ((0xfffffffeU 
                                                 & vlTOPp->top__DOT__dut0__DOT__carry_array) 
                                                | (1U 
                                                   & (vlTOPp->top__DOT__in_sum_a 
                                                      & vlTOPp->top__DOT__in_sum_b)));
    vlTOPp->top__DOT__dut0__DOT__sum = ((0xfffffffeU 
                                         & vlTOPp->top__DOT__dut0__DOT__sum) 
                                        | (1U & (vlTOPp->top__DOT__in_sum_a 
                                                 ^ vlTOPp->top__DOT__in_sum_b)));
    vlTOPp->top__DOT__dut0__DOT____Vcellout__genblk1__BRA__1__KET____DOT__fa0__co 
        = (1U & (((vlTOPp->top__DOT__in_sum_a >> 1U) 
                  & ((vlTOPp->top__DOT__in_sum_b >> 1U) 
                     | vlTOPp->top__DOT__dut0__DOT__carry_array)) 
                 | ((vlTOPp->top__DOT__in_sum_b >> 1U) 
                    & vlTOPp->top__DOT__dut0__DOT__carry_array)));
    vlTOPp->top__DOT__dut0__DOT____Vcellout__genblk1__BRA__2__KET____DOT__fa0__co 
        = (1U & (((vlTOPp->top__DOT__in_sum_a >> 2U) 
                  & ((vlTOPp->top__DOT__in_sum_b >> 2U) 
                     | (vlTOPp->top__DOT__dut0__DOT__carry_array 
                        >> 1U))) | ((vlTOPp->top__DOT__in_sum_b 
                                     >> 2U) & (vlTOPp->top__DOT__dut0__DOT__carry_array 
                                               >> 1U))));
    vlTOPp->top__DOT__dut0__DOT____Vcellout__genblk1__BRA__3__KET____DOT__fa0__co 
        = (1U & (((vlTOPp->top__DOT__in_sum_a >> 3U) 
                  & ((vlTOPp->top__DOT__in_sum_b >> 3U) 
                     | (vlTOPp->top__DOT__dut0__DOT__carry_array 
                        >> 2U))) | ((vlTOPp->top__DOT__in_sum_b 
                                     >> 3U) & (vlTOPp->top__DOT__dut0__DOT__carry_array 
                                               >> 2U))));
    vlTOPp->top__DOT__dut0__DOT____Vcellout__genblk1__BRA__4__KET____DOT__fa0__co 
        = (1U & (((vlTOPp->top__DOT__in_sum_a >> 4U) 
                  & ((vlTOPp->top__DOT__in_sum_b >> 4U) 
                     | (vlTOPp->top__DOT__dut0__DOT__carry_array 
                        >> 3U))) | ((vlTOPp->top__DOT__in_sum_b 
                                     >> 4U) & (vlTOPp->top__DOT__dut0__DOT__carry_array 
                                               >> 3U))));
    vlTOPp->top__DOT__dut0__DOT____Vcellout__genblk1__BRA__5__KET____DOT__fa0__co 
        = (1U & (((vlTOPp->top__DOT__in_sum_a >> 5U) 
                  & ((vlTOPp->top__DOT__in_sum_b >> 5U) 
                     | (vlTOPp->top__DOT__dut0__DOT__carry_array 
                        >> 4U))) | ((vlTOPp->top__DOT__in_sum_b 
                                     >> 5U) & (vlTOPp->top__DOT__dut0__DOT__carry_array 
                                               >> 4U))));
    vlTOPp->top__DOT__dut0__DOT____Vcellout__genblk1__BRA__6__KET____DOT__fa0__co 
        = (1U & (((vlTOPp->top__DOT__in_sum_a >> 6U) 
                  & ((vlTOPp->top__DOT__in_sum_b >> 6U) 
                     | (vlTOPp->top__DOT__dut0__DOT__carry_array 
                        >> 5U))) | ((vlTOPp->top__DOT__in_sum_b 
                                     >> 6U) & (vlTOPp->top__DOT__dut0__DOT__carry_array 
                                               >> 5U))));
    vlTOPp->top__DOT__dut0__DOT____Vcellout__genblk1__BRA__7__KET____DOT__fa0__co 
        = (1U & (((vlTOPp->top__DOT__in_sum_a >> 7U) 
                  & ((vlTOPp->top__DOT__in_sum_b >> 7U) 
                     | (vlTOPp->top__DOT__dut0__DOT__carry_array 
                        >> 6U))) | ((vlTOPp->top__DOT__in_sum_b 
                                     >> 7U) & (vlTOPp->top__DOT__dut0__DOT__carry_array 
                                               >> 6U))));
    vlTOPp->top__DOT__dut0__DOT____Vcellout__genblk1__BRA__8__KET____DOT__fa0__co 
        = (1U & (((vlTOPp->top__DOT__in_sum_a >> 8U) 
                  & ((vlTOPp->top__DOT__in_sum_b >> 8U) 
                     | (vlTOPp->top__DOT__dut0__DOT__carry_array 
                        >> 7U))) | ((vlTOPp->top__DOT__in_sum_b 
                                     >> 8U) & (vlTOPp->top__DOT__dut0__DOT__carry_array 
                                               >> 7U))));
    vlTOPp->top__DOT__dut0__DOT____Vcellout__genblk1__BRA__9__KET____DOT__fa0__co 
        = (1U & (((vlTOPp->top__DOT__in_sum_a >> 9U) 
                  & ((vlTOPp->top__DOT__in_sum_b >> 9U) 
                     | (vlTOPp->top__DOT__dut0__DOT__carry_array 
                        >> 8U))) | ((vlTOPp->top__DOT__in_sum_b 
                                     >> 9U) & (vlTOPp->top__DOT__dut0__DOT__carry_array 
                                               >> 8U))));
    vlTOPp->top__DOT__dut0__DOT____Vcellout__genblk1__BRA__10__KET____DOT__fa0__co 
        = (1U & (((vlTOPp->top__DOT__in_sum_a >> 0xaU) 
                  & ((vlTOPp->top__DOT__in_sum_b >> 0xaU) 
                     | (vlTOPp->top__DOT__dut0__DOT__carry_array 
                        >> 9U))) | ((vlTOPp->top__DOT__in_sum_b 
                                     >> 0xaU) & (vlTOPp->top__DOT__dut0__DOT__carry_array 
                                                 >> 9U))));
    vlTOPp->top__DOT__dut0__DOT____Vcellout__genblk1__BRA__11__KET____DOT__fa0__co 
        = (1U & (((vlTOPp->top__DOT__in_sum_a >> 0xbU) 
                  & ((vlTOPp->top__DOT__in_sum_b >> 0xbU) 
                     | (vlTOPp->top__DOT__dut0__DOT__carry_array 
                        >> 0xaU))) | ((vlTOPp->top__DOT__in_sum_b 
                                       >> 0xbU) & (vlTOPp->top__DOT__dut0__DOT__carry_array 
                                                   >> 0xaU))));
    vlTOPp->top__DOT__dut0__DOT____Vcellout__genblk1__BRA__12__KET____DOT__fa0__co 
        = (1U & (((vlTOPp->top__DOT__in_sum_a >> 0xcU) 
                  & ((vlTOPp->top__DOT__in_sum_b >> 0xcU) 
                     | (vlTOPp->top__DOT__dut0__DOT__carry_array 
                        >> 0xbU))) | ((vlTOPp->top__DOT__in_sum_b 
                                       >> 0xcU) & (vlTOPp->top__DOT__dut0__DOT__carry_array 
                                                   >> 0xbU))));
    vlTOPp->top__DOT__dut0__DOT____Vcellout__genblk1__BRA__13__KET____DOT__fa0__co 
        = (1U & (((vlTOPp->top__DOT__in_sum_a >> 0xdU) 
                  & ((vlTOPp->top__DOT__in_sum_b >> 0xdU) 
                     | (vlTOPp->top__DOT__dut0__DOT__carry_array 
                        >> 0xcU))) | ((vlTOPp->top__DOT__in_sum_b 
                                       >> 0xdU) & (vlTOPp->top__DOT__dut0__DOT__carry_array 
                                                   >> 0xcU))));
    vlTOPp->top__DOT__dut0__DOT____Vcellout__genblk1__BRA__14__KET____DOT__fa0__co 
        = (1U & (((vlTOPp->top__DOT__in_sum_a >> 0xeU) 
                  & ((vlTOPp->top__DOT__in_sum_b >> 0xeU) 
                     | (vlTOPp->top__DOT__dut0__DOT__carry_array 
                        >> 0xdU))) | ((vlTOPp->top__DOT__in_sum_b 
                                       >> 0xeU) & (vlTOPp->top__DOT__dut0__DOT__carry_array 
                                                   >> 0xdU))));
    vlTOPp->top__DOT__dut0__DOT____Vcellout__genblk1__BRA__15__KET____DOT__fa0__co 
        = (1U & (((vlTOPp->top__DOT__in_sum_a >> 0xfU) 
                  & ((vlTOPp->top__DOT__in_sum_b >> 0xfU) 
                     | (vlTOPp->top__DOT__dut0__DOT__carry_array 
                        >> 0xeU))) | ((vlTOPp->top__DOT__in_sum_b 
                                       >> 0xfU) & (vlTOPp->top__DOT__dut0__DOT__carry_array 
                                                   >> 0xeU))));
    vlTOPp->top__DOT__dut0__DOT____Vcellout__genblk1__BRA__16__KET____DOT__fa0__co 
        = (1U & (((vlTOPp->top__DOT__in_sum_a >> 0x10U) 
                  & ((vlTOPp->top__DOT__in_sum_b >> 0x10U) 
                     | (vlTOPp->top__DOT__dut0__DOT__carry_array 
                        >> 0xfU))) | ((vlTOPp->top__DOT__in_sum_b 
                                       >> 0x10U) & 
                                      (vlTOPp->top__DOT__dut0__DOT__carry_array 
                                       >> 0xfU))));
    vlTOPp->top__DOT__dut0__DOT____Vcellout__genblk1__BRA__17__KET____DOT__fa0__co 
        = (1U & (((vlTOPp->top__DOT__in_sum_a >> 0x11U) 
                  & ((vlTOPp->top__DOT__in_sum_b >> 0x11U) 
                     | (vlTOPp->top__DOT__dut0__DOT__carry_array 
                        >> 0x10U))) | ((vlTOPp->top__DOT__in_sum_b 
                                        >> 0x11U) & 
                                       (vlTOPp->top__DOT__dut0__DOT__carry_array 
                                        >> 0x10U))));
    vlTOPp->top__DOT__dut0__DOT____Vcellout__genblk1__BRA__18__KET____DOT__fa0__co 
        = (1U & (((vlTOPp->top__DOT__in_sum_a >> 0x12U) 
                  & ((vlTOPp->top__DOT__in_sum_b >> 0x12U) 
                     | (vlTOPp->top__DOT__dut0__DOT__carry_array 
                        >> 0x11U))) | ((vlTOPp->top__DOT__in_sum_b 
                                        >> 0x12U) & 
                                       (vlTOPp->top__DOT__dut0__DOT__carry_array 
                                        >> 0x11U))));
    vlTOPp->top__DOT__dut0__DOT____Vcellout__genblk1__BRA__19__KET____DOT__fa0__co 
        = (1U & (((vlTOPp->top__DOT__in_sum_a >> 0x13U) 
                  & ((vlTOPp->top__DOT__in_sum_b >> 0x13U) 
                     | (vlTOPp->top__DOT__dut0__DOT__carry_array 
                        >> 0x12U))) | ((vlTOPp->top__DOT__in_sum_b 
                                        >> 0x13U) & 
                                       (vlTOPp->top__DOT__dut0__DOT__carry_array 
                                        >> 0x12U))));
    vlTOPp->top__DOT__dut0__DOT____Vcellout__genblk1__BRA__20__KET____DOT__fa0__co 
        = (1U & (((vlTOPp->top__DOT__in_sum_a >> 0x14U) 
                  & ((vlTOPp->top__DOT__in_sum_b >> 0x14U) 
                     | (vlTOPp->top__DOT__dut0__DOT__carry_array 
                        >> 0x13U))) | ((vlTOPp->top__DOT__in_sum_b 
                                        >> 0x14U) & 
                                       (vlTOPp->top__DOT__dut0__DOT__carry_array 
                                        >> 0x13U))));
    vlTOPp->top__DOT__dut0__DOT____Vcellout__genblk1__BRA__21__KET____DOT__fa0__co 
        = (1U & (((vlTOPp->top__DOT__in_sum_a >> 0x15U) 
                  & ((vlTOPp->top__DOT__in_sum_b >> 0x15U) 
                     | (vlTOPp->top__DOT__dut0__DOT__carry_array 
                        >> 0x14U))) | ((vlTOPp->top__DOT__in_sum_b 
                                        >> 0x15U) & 
                                       (vlTOPp->top__DOT__dut0__DOT__carry_array 
                                        >> 0x14U))));
    vlTOPp->top__DOT__dut0__DOT____Vcellout__genblk1__BRA__22__KET____DOT__fa0__co 
        = (1U & (((vlTOPp->top__DOT__in_sum_a >> 0x16U) 
                  & ((vlTOPp->top__DOT__in_sum_b >> 0x16U) 
                     | (vlTOPp->top__DOT__dut0__DOT__carry_array 
                        >> 0x15U))) | ((vlTOPp->top__DOT__in_sum_b 
                                        >> 0x16U) & 
                                       (vlTOPp->top__DOT__dut0__DOT__carry_array 
                                        >> 0x15U))));
    vlTOPp->top__DOT__dut0__DOT____Vcellout__genblk1__BRA__23__KET____DOT__fa0__co 
        = (1U & (((vlTOPp->top__DOT__in_sum_a >> 0x17U) 
                  & ((vlTOPp->top__DOT__in_sum_b >> 0x17U) 
                     | (vlTOPp->top__DOT__dut0__DOT__carry_array 
                        >> 0x16U))) | ((vlTOPp->top__DOT__in_sum_b 
                                        >> 0x17U) & 
                                       (vlTOPp->top__DOT__dut0__DOT__carry_array 
                                        >> 0x16U))));
    vlTOPp->top__DOT__dut0__DOT____Vcellout__genblk1__BRA__24__KET____DOT__fa0__co 
        = (1U & (((vlTOPp->top__DOT__in_sum_a >> 0x18U) 
                  & ((vlTOPp->top__DOT__in_sum_b >> 0x18U) 
                     | (vlTOPp->top__DOT__dut0__DOT__carry_array 
                        >> 0x17U))) | ((vlTOPp->top__DOT__in_sum_b 
                                        >> 0x18U) & 
                                       (vlTOPp->top__DOT__dut0__DOT__carry_array 
                                        >> 0x17U))));
    vlTOPp->top__DOT__dut0__DOT____Vcellout__genblk1__BRA__25__KET____DOT__fa0__co 
        = (1U & (((vlTOPp->top__DOT__in_sum_a >> 0x19U) 
                  & ((vlTOPp->top__DOT__in_sum_b >> 0x19U) 
                     | (vlTOPp->top__DOT__dut0__DOT__carry_array 
                        >> 0x18U))) | ((vlTOPp->top__DOT__in_sum_b 
                                        >> 0x19U) & 
                                       (vlTOPp->top__DOT__dut0__DOT__carry_array 
                                        >> 0x18U))));
    vlTOPp->top__DOT__dut0__DOT____Vcellout__genblk1__BRA__26__KET____DOT__fa0__co 
        = (1U & (((vlTOPp->top__DOT__in_sum_a >> 0x1aU) 
                  & ((vlTOPp->top__DOT__in_sum_b >> 0x1aU) 
                     | (vlTOPp->top__DOT__dut0__DOT__carry_array 
                        >> 0x19U))) | ((vlTOPp->top__DOT__in_sum_b 
                                        >> 0x1aU) & 
                                       (vlTOPp->top__DOT__dut0__DOT__carry_array 
                                        >> 0x19U))));
    vlTOPp->top__DOT__dut0__DOT____Vcellout__genblk1__BRA__27__KET____DOT__fa0__co 
        = (1U & (((vlTOPp->top__DOT__in_sum_a >> 0x1bU) 
                  & ((vlTOPp->top__DOT__in_sum_b >> 0x1bU) 
                     | (vlTOPp->top__DOT__dut0__DOT__carry_array 
                        >> 0x1aU))) | ((vlTOPp->top__DOT__in_sum_b 
                                        >> 0x1bU) & 
                                       (vlTOPp->top__DOT__dut0__DOT__carry_array 
                                        >> 0x1aU))));
    vlTOPp->top__DOT__dut0__DOT____Vcellout__genblk1__BRA__28__KET____DOT__fa0__co 
        = (1U & (((vlTOPp->top__DOT__in_sum_a >> 0x1cU) 
                  & ((vlTOPp->top__DOT__in_sum_b >> 0x1cU) 
                     | (vlTOPp->top__DOT__dut0__DOT__carry_array 
                        >> 0x1bU))) | ((vlTOPp->top__DOT__in_sum_b 
                                        >> 0x1cU) & 
                                       (vlTOPp->top__DOT__dut0__DOT__carry_array 
                                        >> 0x1bU))));
    vlTOPp->top__DOT__dut0__DOT____Vcellout__genblk1__BRA__29__KET____DOT__fa0__co 
        = (1U & (((vlTOPp->top__DOT__in_sum_a >> 0x1dU) 
                  & ((vlTOPp->top__DOT__in_sum_b >> 0x1dU) 
                     | (vlTOPp->top__DOT__dut0__DOT__carry_array 
                        >> 0x1cU))) | ((vlTOPp->top__DOT__in_sum_b 
                                        >> 0x1dU) & 
                                       (vlTOPp->top__DOT__dut0__DOT__carry_array 
                                        >> 0x1cU))));
    vlTOPp->top__DOT__dut0__DOT____Vcellout__genblk1__BRA__30__KET____DOT__fa0__co 
        = (1U & (((vlTOPp->top__DOT__in_sum_a >> 0x1eU) 
                  & ((vlTOPp->top__DOT__in_sum_b >> 0x1eU) 
                     | (vlTOPp->top__DOT__dut0__DOT__carry_array 
                        >> 0x1dU))) | ((vlTOPp->top__DOT__in_sum_b 
                                        >> 0x1eU) & 
                                       (vlTOPp->top__DOT__dut0__DOT__carry_array 
                                        >> 0x1dU))));
    vlTOPp->top__DOT__dut0__DOT____Vcellout__genblk1__BRA__31__KET____DOT__fa0__co 
        = (1U & (((vlTOPp->top__DOT__in_sum_a >> 0x1fU) 
                  & ((vlTOPp->top__DOT__in_sum_b >> 0x1fU) 
                     | (vlTOPp->top__DOT__dut0__DOT__carry_array 
                        >> 0x1eU))) | ((vlTOPp->top__DOT__in_sum_b 
                                        >> 0x1fU) & 
                                       (vlTOPp->top__DOT__dut0__DOT__carry_array 
                                        >> 0x1eU))));
    vlTOPp->top__DOT__dut0__DOT__sum = ((0xfffffffdU 
                                         & vlTOPp->top__DOT__dut0__DOT__sum) 
                                        | (2U & ((0xfffffffeU 
                                                  & (vlTOPp->top__DOT__in_sum_a 
                                                     ^ vlTOPp->top__DOT__in_sum_b)) 
                                                 ^ 
                                                 (vlTOPp->top__DOT__dut0__DOT__carry_array 
                                                  << 1U))));
    vlTOPp->top__DOT__dut0__DOT__sum = ((0xfffffffbU 
                                         & vlTOPp->top__DOT__dut0__DOT__sum) 
                                        | (4U & ((0xfffffffcU 
                                                  & (vlTOPp->top__DOT__in_sum_a 
                                                     ^ vlTOPp->top__DOT__in_sum_b)) 
                                                 ^ 
                                                 (0xfffffffcU 
                                                  & (vlTOPp->top__DOT__dut0__DOT__carry_array 
                                                     << 1U)))));
    vlTOPp->top__DOT__dut0__DOT__sum = ((0xfffffff7U 
                                         & vlTOPp->top__DOT__dut0__DOT__sum) 
                                        | (8U & ((0xfffffff8U 
                                                  & (vlTOPp->top__DOT__in_sum_a 
                                                     ^ vlTOPp->top__DOT__in_sum_b)) 
                                                 ^ 
                                                 (0xfffffff8U 
                                                  & (vlTOPp->top__DOT__dut0__DOT__carry_array 
                                                     << 1U)))));
    vlTOPp->top__DOT__dut0__DOT__sum = ((0xffffffefU 
                                         & vlTOPp->top__DOT__dut0__DOT__sum) 
                                        | (0x10U & 
                                           ((0xfffffff0U 
                                             & (vlTOPp->top__DOT__in_sum_a 
                                                ^ vlTOPp->top__DOT__in_sum_b)) 
                                            ^ (0xfffffff0U 
                                               & (vlTOPp->top__DOT__dut0__DOT__carry_array 
                                                  << 1U)))));
    vlTOPp->top__DOT__dut0__DOT__sum = ((0xffffffdfU 
                                         & vlTOPp->top__DOT__dut0__DOT__sum) 
                                        | (0x20U & 
                                           ((0xffffffe0U 
                                             & (vlTOPp->top__DOT__in_sum_a 
                                                ^ vlTOPp->top__DOT__in_sum_b)) 
                                            ^ (0xffffffe0U 
                                               & (vlTOPp->top__DOT__dut0__DOT__carry_array 
                                                  << 1U)))));
    vlTOPp->top__DOT__dut0__DOT__sum = ((0xffffffbfU 
                                         & vlTOPp->top__DOT__dut0__DOT__sum) 
                                        | (0x40U & 
                                           ((0xffffffc0U 
                                             & (vlTOPp->top__DOT__in_sum_a 
                                                ^ vlTOPp->top__DOT__in_sum_b)) 
                                            ^ (0xffffffc0U 
                                               & (vlTOPp->top__DOT__dut0__DOT__carry_array 
                                                  << 1U)))));
    vlTOPp->top__DOT__dut0__DOT__sum = ((0xffffff7fU 
                                         & vlTOPp->top__DOT__dut0__DOT__sum) 
                                        | (0x80U & 
                                           ((0xffffff80U 
                                             & (vlTOPp->top__DOT__in_sum_a 
                                                ^ vlTOPp->top__DOT__in_sum_b)) 
                                            ^ (0xffffff80U 
                                               & (vlTOPp->top__DOT__dut0__DOT__carry_array 
                                                  << 1U)))));
    vlTOPp->top__DOT__dut0__DOT__sum = ((0xfffffeffU 
                                         & vlTOPp->top__DOT__dut0__DOT__sum) 
                                        | (0x100U & 
                                           ((0xffffff00U 
                                             & (vlTOPp->top__DOT__in_sum_a 
                                                ^ vlTOPp->top__DOT__in_sum_b)) 
                                            ^ (0xffffff00U 
                                               & (vlTOPp->top__DOT__dut0__DOT__carry_array 
                                                  << 1U)))));
    vlTOPp->top__DOT__dut0__DOT__sum = ((0xfffffdffU 
                                         & vlTOPp->top__DOT__dut0__DOT__sum) 
                                        | (0x200U & 
                                           ((0xfffffe00U 
                                             & (vlTOPp->top__DOT__in_sum_a 
                                                ^ vlTOPp->top__DOT__in_sum_b)) 
                                            ^ (0xfffffe00U 
                                               & (vlTOPp->top__DOT__dut0__DOT__carry_array 
                                                  << 1U)))));
    vlTOPp->top__DOT__dut0__DOT__sum = ((0xfffffbffU 
                                         & vlTOPp->top__DOT__dut0__DOT__sum) 
                                        | (0x400U & 
                                           ((0xfffffc00U 
                                             & (vlTOPp->top__DOT__in_sum_a 
                                                ^ vlTOPp->top__DOT__in_sum_b)) 
                                            ^ (0xfffffc00U 
                                               & (vlTOPp->top__DOT__dut0__DOT__carry_array 
                                                  << 1U)))));
    vlTOPp->top__DOT__dut0__DOT__sum = ((0xfffff7ffU 
                                         & vlTOPp->top__DOT__dut0__DOT__sum) 
                                        | (0x800U & 
                                           ((0xfffff800U 
                                             & (vlTOPp->top__DOT__in_sum_a 
                                                ^ vlTOPp->top__DOT__in_sum_b)) 
                                            ^ (0xfffff800U 
                                               & (vlTOPp->top__DOT__dut0__DOT__carry_array 
                                                  << 1U)))));
    vlTOPp->top__DOT__dut0__DOT__sum = ((0xffffefffU 
                                         & vlTOPp->top__DOT__dut0__DOT__sum) 
                                        | (0x1000U 
                                           & ((0xfffff000U 
                                               & (vlTOPp->top__DOT__in_sum_a 
                                                  ^ vlTOPp->top__DOT__in_sum_b)) 
                                              ^ (0xfffff000U 
                                                 & (vlTOPp->top__DOT__dut0__DOT__carry_array 
                                                    << 1U)))));
    vlTOPp->top__DOT__dut0__DOT__sum = ((0xffffdfffU 
                                         & vlTOPp->top__DOT__dut0__DOT__sum) 
                                        | (0x2000U 
                                           & ((0xffffe000U 
                                               & (vlTOPp->top__DOT__in_sum_a 
                                                  ^ vlTOPp->top__DOT__in_sum_b)) 
                                              ^ (0xffffe000U 
                                                 & (vlTOPp->top__DOT__dut0__DOT__carry_array 
                                                    << 1U)))));
    vlTOPp->top__DOT__dut0__DOT__sum = ((0xffffbfffU 
                                         & vlTOPp->top__DOT__dut0__DOT__sum) 
                                        | (0x4000U 
                                           & ((0xffffc000U 
                                               & (vlTOPp->top__DOT__in_sum_a 
                                                  ^ vlTOPp->top__DOT__in_sum_b)) 
                                              ^ (0xffffc000U 
                                                 & (vlTOPp->top__DOT__dut0__DOT__carry_array 
                                                    << 1U)))));
    vlTOPp->top__DOT__dut0__DOT__sum = ((0xffff7fffU 
                                         & vlTOPp->top__DOT__dut0__DOT__sum) 
                                        | (0x8000U 
                                           & ((0xffff8000U 
                                               & (vlTOPp->top__DOT__in_sum_a 
                                                  ^ vlTOPp->top__DOT__in_sum_b)) 
                                              ^ (0xffff8000U 
                                                 & (vlTOPp->top__DOT__dut0__DOT__carry_array 
                                                    << 1U)))));
    vlTOPp->top__DOT__dut0__DOT__sum = ((0xfffeffffU 
                                         & vlTOPp->top__DOT__dut0__DOT__sum) 
                                        | (0x10000U 
                                           & ((0xffff0000U 
                                               & (vlTOPp->top__DOT__in_sum_a 
                                                  ^ vlTOPp->top__DOT__in_sum_b)) 
                                              ^ (0xffff0000U 
                                                 & (vlTOPp->top__DOT__dut0__DOT__carry_array 
                                                    << 1U)))));
    vlTOPp->top__DOT__dut0__DOT__sum = ((0xfffdffffU 
                                         & vlTOPp->top__DOT__dut0__DOT__sum) 
                                        | (0x20000U 
                                           & ((0xfffe0000U 
                                               & (vlTOPp->top__DOT__in_sum_a 
                                                  ^ vlTOPp->top__DOT__in_sum_b)) 
                                              ^ (0xfffe0000U 
                                                 & (vlTOPp->top__DOT__dut0__DOT__carry_array 
                                                    << 1U)))));
    vlTOPp->top__DOT__dut0__DOT__sum = ((0xfffbffffU 
                                         & vlTOPp->top__DOT__dut0__DOT__sum) 
                                        | (0x40000U 
                                           & ((0xfffc0000U 
                                               & (vlTOPp->top__DOT__in_sum_a 
                                                  ^ vlTOPp->top__DOT__in_sum_b)) 
                                              ^ (0xfffc0000U 
                                                 & (vlTOPp->top__DOT__dut0__DOT__carry_array 
                                                    << 1U)))));
    vlTOPp->top__DOT__dut0__DOT__sum = ((0xfff7ffffU 
                                         & vlTOPp->top__DOT__dut0__DOT__sum) 
                                        | (0x80000U 
                                           & ((0xfff80000U 
                                               & (vlTOPp->top__DOT__in_sum_a 
                                                  ^ vlTOPp->top__DOT__in_sum_b)) 
                                              ^ (0xfff80000U 
                                                 & (vlTOPp->top__DOT__dut0__DOT__carry_array 
                                                    << 1U)))));
    vlTOPp->top__DOT__dut0__DOT__sum = ((0xffefffffU 
                                         & vlTOPp->top__DOT__dut0__DOT__sum) 
                                        | (0x100000U 
                                           & ((0xfff00000U 
                                               & (vlTOPp->top__DOT__in_sum_a 
                                                  ^ vlTOPp->top__DOT__in_sum_b)) 
                                              ^ (0xfff00000U 
                                                 & (vlTOPp->top__DOT__dut0__DOT__carry_array 
                                                    << 1U)))));
    vlTOPp->top__DOT__dut0__DOT__sum = ((0xffdfffffU 
                                         & vlTOPp->top__DOT__dut0__DOT__sum) 
                                        | (0x200000U 
                                           & ((0xffe00000U 
                                               & (vlTOPp->top__DOT__in_sum_a 
                                                  ^ vlTOPp->top__DOT__in_sum_b)) 
                                              ^ (0xffe00000U 
                                                 & (vlTOPp->top__DOT__dut0__DOT__carry_array 
                                                    << 1U)))));
    vlTOPp->top__DOT__dut0__DOT__sum = ((0xffbfffffU 
                                         & vlTOPp->top__DOT__dut0__DOT__sum) 
                                        | (0x400000U 
                                           & ((0xffc00000U 
                                               & (vlTOPp->top__DOT__in_sum_a 
                                                  ^ vlTOPp->top__DOT__in_sum_b)) 
                                              ^ (0xffc00000U 
                                                 & (vlTOPp->top__DOT__dut0__DOT__carry_array 
                                                    << 1U)))));
    vlTOPp->top__DOT__dut0__DOT__sum = ((0xff7fffffU 
                                         & vlTOPp->top__DOT__dut0__DOT__sum) 
                                        | (0x800000U 
                                           & ((0xff800000U 
                                               & (vlTOPp->top__DOT__in_sum_a 
                                                  ^ vlTOPp->top__DOT__in_sum_b)) 
                                              ^ (0xff800000U 
                                                 & (vlTOPp->top__DOT__dut0__DOT__carry_array 
                                                    << 1U)))));
    vlTOPp->top__DOT__dut0__DOT__sum = ((0xfeffffffU 
                                         & vlTOPp->top__DOT__dut0__DOT__sum) 
                                        | (0x1000000U 
                                           & ((0xff000000U 
                                               & (vlTOPp->top__DOT__in_sum_a 
                                                  ^ vlTOPp->top__DOT__in_sum_b)) 
                                              ^ (0xff000000U 
                                                 & (vlTOPp->top__DOT__dut0__DOT__carry_array 
                                                    << 1U)))));
    vlTOPp->top__DOT__dut0__DOT__sum = ((0xfdffffffU 
                                         & vlTOPp->top__DOT__dut0__DOT__sum) 
                                        | (0x2000000U 
                                           & ((0xfe000000U 
                                               & (vlTOPp->top__DOT__in_sum_a 
                                                  ^ vlTOPp->top__DOT__in_sum_b)) 
                                              ^ (0xfe000000U 
                                                 & (vlTOPp->top__DOT__dut0__DOT__carry_array 
                                                    << 1U)))));
    vlTOPp->top__DOT__dut0__DOT__sum = ((0xfbffffffU 
                                         & vlTOPp->top__DOT__dut0__DOT__sum) 
                                        | (0x4000000U 
                                           & ((0xfc000000U 
                                               & (vlTOPp->top__DOT__in_sum_a 
                                                  ^ vlTOPp->top__DOT__in_sum_b)) 
                                              ^ (0xfc000000U 
                                                 & (vlTOPp->top__DOT__dut0__DOT__carry_array 
                                                    << 1U)))));
    vlTOPp->top__DOT__dut0__DOT__sum = ((0xf7ffffffU 
                                         & vlTOPp->top__DOT__dut0__DOT__sum) 
                                        | (0x8000000U 
                                           & ((0xf8000000U 
                                               & (vlTOPp->top__DOT__in_sum_a 
                                                  ^ vlTOPp->top__DOT__in_sum_b)) 
                                              ^ (0xf8000000U 
                                                 & (vlTOPp->top__DOT__dut0__DOT__carry_array 
                                                    << 1U)))));
    vlTOPp->top__DOT__dut0__DOT__sum = ((0xefffffffU 
                                         & vlTOPp->top__DOT__dut0__DOT__sum) 
                                        | (0x10000000U 
                                           & ((0xf0000000U 
                                               & (vlTOPp->top__DOT__in_sum_a 
                                                  ^ vlTOPp->top__DOT__in_sum_b)) 
                                              ^ (0xf0000000U 
                                                 & (vlTOPp->top__DOT__dut0__DOT__carry_array 
                                                    << 1U)))));
    vlTOPp->top__DOT__dut0__DOT__sum = ((0xdfffffffU 
                                         & vlTOPp->top__DOT__dut0__DOT__sum) 
                                        | (0x20000000U 
                                           & ((0xe0000000U 
                                               & (vlTOPp->top__DOT__in_sum_a 
                                                  ^ vlTOPp->top__DOT__in_sum_b)) 
                                              ^ (0xe0000000U 
                                                 & (vlTOPp->top__DOT__dut0__DOT__carry_array 
                                                    << 1U)))));
    vlTOPp->top__DOT__dut0__DOT__sum = ((0xbfffffffU 
                                         & vlTOPp->top__DOT__dut0__DOT__sum) 
                                        | (0x40000000U 
                                           & ((0xc0000000U 
                                               & (vlTOPp->top__DOT__in_sum_a 
                                                  ^ vlTOPp->top__DOT__in_sum_b)) 
                                              ^ (0xc0000000U 
                                                 & (vlTOPp->top__DOT__dut0__DOT__carry_array 
                                                    << 1U)))));
    vlTOPp->top__DOT__dut0__DOT__sum = ((0x7fffffffU 
                                         & vlTOPp->top__DOT__dut0__DOT__sum) 
                                        | (0x80000000U 
                                           & ((0x80000000U 
                                               & (vlTOPp->top__DOT__in_sum_a 
                                                  ^ vlTOPp->top__DOT__in_sum_b)) 
                                              ^ (0x80000000U 
                                                 & (vlTOPp->top__DOT__dut0__DOT__carry_array 
                                                    << 1U)))));
    vlTOPp->top__DOT__dut0__DOT__carry_array = ((0xfffffffdU 
                                                 & vlTOPp->top__DOT__dut0__DOT__carry_array) 
                                                | ((IData)(vlTOPp->top__DOT__dut0__DOT____Vcellout__genblk1__BRA__1__KET____DOT__fa0__co) 
                                                   << 1U));
    vlTOPp->top__DOT__dut0__DOT__carry_array = ((0xfffffffbU 
                                                 & vlTOPp->top__DOT__dut0__DOT__carry_array) 
                                                | ((IData)(vlTOPp->top__DOT__dut0__DOT____Vcellout__genblk1__BRA__2__KET____DOT__fa0__co) 
                                                   << 2U));
    vlTOPp->top__DOT__dut0__DOT__carry_array = ((0xfffffff7U 
                                                 & vlTOPp->top__DOT__dut0__DOT__carry_array) 
                                                | ((IData)(vlTOPp->top__DOT__dut0__DOT____Vcellout__genblk1__BRA__3__KET____DOT__fa0__co) 
                                                   << 3U));
    vlTOPp->top__DOT__dut0__DOT__carry_array = ((0xffffffefU 
                                                 & vlTOPp->top__DOT__dut0__DOT__carry_array) 
                                                | ((IData)(vlTOPp->top__DOT__dut0__DOT____Vcellout__genblk1__BRA__4__KET____DOT__fa0__co) 
                                                   << 4U));
    vlTOPp->top__DOT__dut0__DOT__carry_array = ((0xffffffdfU 
                                                 & vlTOPp->top__DOT__dut0__DOT__carry_array) 
                                                | ((IData)(vlTOPp->top__DOT__dut0__DOT____Vcellout__genblk1__BRA__5__KET____DOT__fa0__co) 
                                                   << 5U));
    vlTOPp->top__DOT__dut0__DOT__carry_array = ((0xffffffbfU 
                                                 & vlTOPp->top__DOT__dut0__DOT__carry_array) 
                                                | ((IData)(vlTOPp->top__DOT__dut0__DOT____Vcellout__genblk1__BRA__6__KET____DOT__fa0__co) 
                                                   << 6U));
    vlTOPp->top__DOT__dut0__DOT__carry_array = ((0xffffff7fU 
                                                 & vlTOPp->top__DOT__dut0__DOT__carry_array) 
                                                | ((IData)(vlTOPp->top__DOT__dut0__DOT____Vcellout__genblk1__BRA__7__KET____DOT__fa0__co) 
                                                   << 7U));
    vlTOPp->top__DOT__dut0__DOT__carry_array = ((0xfffffeffU 
                                                 & vlTOPp->top__DOT__dut0__DOT__carry_array) 
                                                | ((IData)(vlTOPp->top__DOT__dut0__DOT____Vcellout__genblk1__BRA__8__KET____DOT__fa0__co) 
                                                   << 8U));
    vlTOPp->top__DOT__dut0__DOT__carry_array = ((0xfffffdffU 
                                                 & vlTOPp->top__DOT__dut0__DOT__carry_array) 
                                                | ((IData)(vlTOPp->top__DOT__dut0__DOT____Vcellout__genblk1__BRA__9__KET____DOT__fa0__co) 
                                                   << 9U));
    vlTOPp->top__DOT__dut0__DOT__carry_array = ((0xfffffbffU 
                                                 & vlTOPp->top__DOT__dut0__DOT__carry_array) 
                                                | ((IData)(vlTOPp->top__DOT__dut0__DOT____Vcellout__genblk1__BRA__10__KET____DOT__fa0__co) 
                                                   << 0xaU));
    vlTOPp->top__DOT__dut0__DOT__carry_array = ((0xfffff7ffU 
                                                 & vlTOPp->top__DOT__dut0__DOT__carry_array) 
                                                | ((IData)(vlTOPp->top__DOT__dut0__DOT____Vcellout__genblk1__BRA__11__KET____DOT__fa0__co) 
                                                   << 0xbU));
    vlTOPp->top__DOT__dut0__DOT__carry_array = ((0xffffefffU 
                                                 & vlTOPp->top__DOT__dut0__DOT__carry_array) 
                                                | ((IData)(vlTOPp->top__DOT__dut0__DOT____Vcellout__genblk1__BRA__12__KET____DOT__fa0__co) 
                                                   << 0xcU));
    vlTOPp->top__DOT__dut0__DOT__carry_array = ((0xffffdfffU 
                                                 & vlTOPp->top__DOT__dut0__DOT__carry_array) 
                                                | ((IData)(vlTOPp->top__DOT__dut0__DOT____Vcellout__genblk1__BRA__13__KET____DOT__fa0__co) 
                                                   << 0xdU));
    vlTOPp->top__DOT__dut0__DOT__carry_array = ((0xffffbfffU 
                                                 & vlTOPp->top__DOT__dut0__DOT__carry_array) 
                                                | ((IData)(vlTOPp->top__DOT__dut0__DOT____Vcellout__genblk1__BRA__14__KET____DOT__fa0__co) 
                                                   << 0xeU));
    vlTOPp->top__DOT__dut0__DOT__carry_array = ((0xffff7fffU 
                                                 & vlTOPp->top__DOT__dut0__DOT__carry_array) 
                                                | ((IData)(vlTOPp->top__DOT__dut0__DOT____Vcellout__genblk1__BRA__15__KET____DOT__fa0__co) 
                                                   << 0xfU));
    vlTOPp->top__DOT__dut0__DOT__carry_array = ((0xfffeffffU 
                                                 & vlTOPp->top__DOT__dut0__DOT__carry_array) 
                                                | ((IData)(vlTOPp->top__DOT__dut0__DOT____Vcellout__genblk1__BRA__16__KET____DOT__fa0__co) 
                                                   << 0x10U));
    vlTOPp->top__DOT__dut0__DOT__carry_array = ((0xfffdffffU 
                                                 & vlTOPp->top__DOT__dut0__DOT__carry_array) 
                                                | ((IData)(vlTOPp->top__DOT__dut0__DOT____Vcellout__genblk1__BRA__17__KET____DOT__fa0__co) 
                                                   << 0x11U));
    vlTOPp->top__DOT__dut0__DOT__carry_array = ((0xfffbffffU 
                                                 & vlTOPp->top__DOT__dut0__DOT__carry_array) 
                                                | ((IData)(vlTOPp->top__DOT__dut0__DOT____Vcellout__genblk1__BRA__18__KET____DOT__fa0__co) 
                                                   << 0x12U));
    vlTOPp->top__DOT__dut0__DOT__carry_array = ((0xfff7ffffU 
                                                 & vlTOPp->top__DOT__dut0__DOT__carry_array) 
                                                | ((IData)(vlTOPp->top__DOT__dut0__DOT____Vcellout__genblk1__BRA__19__KET____DOT__fa0__co) 
                                                   << 0x13U));
    vlTOPp->top__DOT__dut0__DOT__carry_array = ((0xffefffffU 
                                                 & vlTOPp->top__DOT__dut0__DOT__carry_array) 
                                                | ((IData)(vlTOPp->top__DOT__dut0__DOT____Vcellout__genblk1__BRA__20__KET____DOT__fa0__co) 
                                                   << 0x14U));
    vlTOPp->top__DOT__dut0__DOT__carry_array = ((0xffdfffffU 
                                                 & vlTOPp->top__DOT__dut0__DOT__carry_array) 
                                                | ((IData)(vlTOPp->top__DOT__dut0__DOT____Vcellout__genblk1__BRA__21__KET____DOT__fa0__co) 
                                                   << 0x15U));
    vlTOPp->top__DOT__dut0__DOT__carry_array = ((0xffbfffffU 
                                                 & vlTOPp->top__DOT__dut0__DOT__carry_array) 
                                                | ((IData)(vlTOPp->top__DOT__dut0__DOT____Vcellout__genblk1__BRA__22__KET____DOT__fa0__co) 
                                                   << 0x16U));
    vlTOPp->top__DOT__dut0__DOT__carry_array = ((0xff7fffffU 
                                                 & vlTOPp->top__DOT__dut0__DOT__carry_array) 
                                                | ((IData)(vlTOPp->top__DOT__dut0__DOT____Vcellout__genblk1__BRA__23__KET____DOT__fa0__co) 
                                                   << 0x17U));
    vlTOPp->top__DOT__dut0__DOT__carry_array = ((0xfeffffffU 
                                                 & vlTOPp->top__DOT__dut0__DOT__carry_array) 
                                                | ((IData)(vlTOPp->top__DOT__dut0__DOT____Vcellout__genblk1__BRA__24__KET____DOT__fa0__co) 
                                                   << 0x18U));
    vlTOPp->top__DOT__dut0__DOT__carry_array = ((0xfdffffffU 
                                                 & vlTOPp->top__DOT__dut0__DOT__carry_array) 
                                                | ((IData)(vlTOPp->top__DOT__dut0__DOT____Vcellout__genblk1__BRA__25__KET____DOT__fa0__co) 
                                                   << 0x19U));
    vlTOPp->top__DOT__dut0__DOT__carry_array = ((0xfbffffffU 
                                                 & vlTOPp->top__DOT__dut0__DOT__carry_array) 
                                                | ((IData)(vlTOPp->top__DOT__dut0__DOT____Vcellout__genblk1__BRA__26__KET____DOT__fa0__co) 
                                                   << 0x1aU));
    vlTOPp->top__DOT__dut0__DOT__carry_array = ((0xf7ffffffU 
                                                 & vlTOPp->top__DOT__dut0__DOT__carry_array) 
                                                | ((IData)(vlTOPp->top__DOT__dut0__DOT____Vcellout__genblk1__BRA__27__KET____DOT__fa0__co) 
                                                   << 0x1bU));
    vlTOPp->top__DOT__dut0__DOT__carry_array = ((0xefffffffU 
                                                 & vlTOPp->top__DOT__dut0__DOT__carry_array) 
                                                | ((IData)(vlTOPp->top__DOT__dut0__DOT____Vcellout__genblk1__BRA__28__KET____DOT__fa0__co) 
                                                   << 0x1cU));
    vlTOPp->top__DOT__dut0__DOT__carry_array = ((0xdfffffffU 
                                                 & vlTOPp->top__DOT__dut0__DOT__carry_array) 
                                                | ((IData)(vlTOPp->top__DOT__dut0__DOT____Vcellout__genblk1__BRA__29__KET____DOT__fa0__co) 
                                                   << 0x1dU));
    vlTOPp->top__DOT__dut0__DOT__carry_array = ((0xbfffffffU 
                                                 & vlTOPp->top__DOT__dut0__DOT__carry_array) 
                                                | ((IData)(vlTOPp->top__DOT__dut0__DOT____Vcellout__genblk1__BRA__30__KET____DOT__fa0__co) 
                                                   << 0x1eU));
    vlTOPp->top__DOT__dut0__DOT__carry_array = ((0x7fffffffU 
                                                 & vlTOPp->top__DOT__dut0__DOT__carry_array) 
                                                | ((IData)(vlTOPp->top__DOT__dut0__DOT____Vcellout__genblk1__BRA__31__KET____DOT__fa0__co) 
                                                   << 0x1fU));
}

VL_INLINE_OPT void Vtop::_combo__TOP__3(Vtop__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop::_combo__TOP__3\n"); );
    Vtop* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->top__DOT__dut0__DOT____Vcellout__genblk1__BRA__1__KET____DOT__fa0__co 
        = (1U & (((vlTOPp->top__DOT__in_sum_a >> 1U) 
                  & ((vlTOPp->top__DOT__in_sum_b >> 1U) 
                     | vlTOPp->top__DOT__dut0__DOT__carry_array)) 
                 | ((vlTOPp->top__DOT__in_sum_b >> 1U) 
                    & vlTOPp->top__DOT__dut0__DOT__carry_array)));
    vlTOPp->top__DOT__dut0__DOT____Vcellout__genblk1__BRA__2__KET____DOT__fa0__co 
        = (1U & (((vlTOPp->top__DOT__in_sum_a >> 2U) 
                  & ((vlTOPp->top__DOT__in_sum_b >> 2U) 
                     | (vlTOPp->top__DOT__dut0__DOT__carry_array 
                        >> 1U))) | ((vlTOPp->top__DOT__in_sum_b 
                                     >> 2U) & (vlTOPp->top__DOT__dut0__DOT__carry_array 
                                               >> 1U))));
    vlTOPp->top__DOT__dut0__DOT____Vcellout__genblk1__BRA__3__KET____DOT__fa0__co 
        = (1U & (((vlTOPp->top__DOT__in_sum_a >> 3U) 
                  & ((vlTOPp->top__DOT__in_sum_b >> 3U) 
                     | (vlTOPp->top__DOT__dut0__DOT__carry_array 
                        >> 2U))) | ((vlTOPp->top__DOT__in_sum_b 
                                     >> 3U) & (vlTOPp->top__DOT__dut0__DOT__carry_array 
                                               >> 2U))));
    vlTOPp->top__DOT__dut0__DOT____Vcellout__genblk1__BRA__4__KET____DOT__fa0__co 
        = (1U & (((vlTOPp->top__DOT__in_sum_a >> 4U) 
                  & ((vlTOPp->top__DOT__in_sum_b >> 4U) 
                     | (vlTOPp->top__DOT__dut0__DOT__carry_array 
                        >> 3U))) | ((vlTOPp->top__DOT__in_sum_b 
                                     >> 4U) & (vlTOPp->top__DOT__dut0__DOT__carry_array 
                                               >> 3U))));
    vlTOPp->top__DOT__dut0__DOT____Vcellout__genblk1__BRA__5__KET____DOT__fa0__co 
        = (1U & (((vlTOPp->top__DOT__in_sum_a >> 5U) 
                  & ((vlTOPp->top__DOT__in_sum_b >> 5U) 
                     | (vlTOPp->top__DOT__dut0__DOT__carry_array 
                        >> 4U))) | ((vlTOPp->top__DOT__in_sum_b 
                                     >> 5U) & (vlTOPp->top__DOT__dut0__DOT__carry_array 
                                               >> 4U))));
    vlTOPp->top__DOT__dut0__DOT____Vcellout__genblk1__BRA__6__KET____DOT__fa0__co 
        = (1U & (((vlTOPp->top__DOT__in_sum_a >> 6U) 
                  & ((vlTOPp->top__DOT__in_sum_b >> 6U) 
                     | (vlTOPp->top__DOT__dut0__DOT__carry_array 
                        >> 5U))) | ((vlTOPp->top__DOT__in_sum_b 
                                     >> 6U) & (vlTOPp->top__DOT__dut0__DOT__carry_array 
                                               >> 5U))));
    vlTOPp->top__DOT__dut0__DOT____Vcellout__genblk1__BRA__7__KET____DOT__fa0__co 
        = (1U & (((vlTOPp->top__DOT__in_sum_a >> 7U) 
                  & ((vlTOPp->top__DOT__in_sum_b >> 7U) 
                     | (vlTOPp->top__DOT__dut0__DOT__carry_array 
                        >> 6U))) | ((vlTOPp->top__DOT__in_sum_b 
                                     >> 7U) & (vlTOPp->top__DOT__dut0__DOT__carry_array 
                                               >> 6U))));
    vlTOPp->top__DOT__dut0__DOT____Vcellout__genblk1__BRA__8__KET____DOT__fa0__co 
        = (1U & (((vlTOPp->top__DOT__in_sum_a >> 8U) 
                  & ((vlTOPp->top__DOT__in_sum_b >> 8U) 
                     | (vlTOPp->top__DOT__dut0__DOT__carry_array 
                        >> 7U))) | ((vlTOPp->top__DOT__in_sum_b 
                                     >> 8U) & (vlTOPp->top__DOT__dut0__DOT__carry_array 
                                               >> 7U))));
    vlTOPp->top__DOT__dut0__DOT____Vcellout__genblk1__BRA__9__KET____DOT__fa0__co 
        = (1U & (((vlTOPp->top__DOT__in_sum_a >> 9U) 
                  & ((vlTOPp->top__DOT__in_sum_b >> 9U) 
                     | (vlTOPp->top__DOT__dut0__DOT__carry_array 
                        >> 8U))) | ((vlTOPp->top__DOT__in_sum_b 
                                     >> 9U) & (vlTOPp->top__DOT__dut0__DOT__carry_array 
                                               >> 8U))));
    vlTOPp->top__DOT__dut0__DOT____Vcellout__genblk1__BRA__10__KET____DOT__fa0__co 
        = (1U & (((vlTOPp->top__DOT__in_sum_a >> 0xaU) 
                  & ((vlTOPp->top__DOT__in_sum_b >> 0xaU) 
                     | (vlTOPp->top__DOT__dut0__DOT__carry_array 
                        >> 9U))) | ((vlTOPp->top__DOT__in_sum_b 
                                     >> 0xaU) & (vlTOPp->top__DOT__dut0__DOT__carry_array 
                                                 >> 9U))));
    vlTOPp->top__DOT__dut0__DOT____Vcellout__genblk1__BRA__11__KET____DOT__fa0__co 
        = (1U & (((vlTOPp->top__DOT__in_sum_a >> 0xbU) 
                  & ((vlTOPp->top__DOT__in_sum_b >> 0xbU) 
                     | (vlTOPp->top__DOT__dut0__DOT__carry_array 
                        >> 0xaU))) | ((vlTOPp->top__DOT__in_sum_b 
                                       >> 0xbU) & (vlTOPp->top__DOT__dut0__DOT__carry_array 
                                                   >> 0xaU))));
    vlTOPp->top__DOT__dut0__DOT____Vcellout__genblk1__BRA__12__KET____DOT__fa0__co 
        = (1U & (((vlTOPp->top__DOT__in_sum_a >> 0xcU) 
                  & ((vlTOPp->top__DOT__in_sum_b >> 0xcU) 
                     | (vlTOPp->top__DOT__dut0__DOT__carry_array 
                        >> 0xbU))) | ((vlTOPp->top__DOT__in_sum_b 
                                       >> 0xcU) & (vlTOPp->top__DOT__dut0__DOT__carry_array 
                                                   >> 0xbU))));
    vlTOPp->top__DOT__dut0__DOT____Vcellout__genblk1__BRA__13__KET____DOT__fa0__co 
        = (1U & (((vlTOPp->top__DOT__in_sum_a >> 0xdU) 
                  & ((vlTOPp->top__DOT__in_sum_b >> 0xdU) 
                     | (vlTOPp->top__DOT__dut0__DOT__carry_array 
                        >> 0xcU))) | ((vlTOPp->top__DOT__in_sum_b 
                                       >> 0xdU) & (vlTOPp->top__DOT__dut0__DOT__carry_array 
                                                   >> 0xcU))));
    vlTOPp->top__DOT__dut0__DOT____Vcellout__genblk1__BRA__14__KET____DOT__fa0__co 
        = (1U & (((vlTOPp->top__DOT__in_sum_a >> 0xeU) 
                  & ((vlTOPp->top__DOT__in_sum_b >> 0xeU) 
                     | (vlTOPp->top__DOT__dut0__DOT__carry_array 
                        >> 0xdU))) | ((vlTOPp->top__DOT__in_sum_b 
                                       >> 0xeU) & (vlTOPp->top__DOT__dut0__DOT__carry_array 
                                                   >> 0xdU))));
    vlTOPp->top__DOT__dut0__DOT____Vcellout__genblk1__BRA__15__KET____DOT__fa0__co 
        = (1U & (((vlTOPp->top__DOT__in_sum_a >> 0xfU) 
                  & ((vlTOPp->top__DOT__in_sum_b >> 0xfU) 
                     | (vlTOPp->top__DOT__dut0__DOT__carry_array 
                        >> 0xeU))) | ((vlTOPp->top__DOT__in_sum_b 
                                       >> 0xfU) & (vlTOPp->top__DOT__dut0__DOT__carry_array 
                                                   >> 0xeU))));
    vlTOPp->top__DOT__dut0__DOT____Vcellout__genblk1__BRA__16__KET____DOT__fa0__co 
        = (1U & (((vlTOPp->top__DOT__in_sum_a >> 0x10U) 
                  & ((vlTOPp->top__DOT__in_sum_b >> 0x10U) 
                     | (vlTOPp->top__DOT__dut0__DOT__carry_array 
                        >> 0xfU))) | ((vlTOPp->top__DOT__in_sum_b 
                                       >> 0x10U) & 
                                      (vlTOPp->top__DOT__dut0__DOT__carry_array 
                                       >> 0xfU))));
    vlTOPp->top__DOT__dut0__DOT____Vcellout__genblk1__BRA__17__KET____DOT__fa0__co 
        = (1U & (((vlTOPp->top__DOT__in_sum_a >> 0x11U) 
                  & ((vlTOPp->top__DOT__in_sum_b >> 0x11U) 
                     | (vlTOPp->top__DOT__dut0__DOT__carry_array 
                        >> 0x10U))) | ((vlTOPp->top__DOT__in_sum_b 
                                        >> 0x11U) & 
                                       (vlTOPp->top__DOT__dut0__DOT__carry_array 
                                        >> 0x10U))));
    vlTOPp->top__DOT__dut0__DOT____Vcellout__genblk1__BRA__18__KET____DOT__fa0__co 
        = (1U & (((vlTOPp->top__DOT__in_sum_a >> 0x12U) 
                  & ((vlTOPp->top__DOT__in_sum_b >> 0x12U) 
                     | (vlTOPp->top__DOT__dut0__DOT__carry_array 
                        >> 0x11U))) | ((vlTOPp->top__DOT__in_sum_b 
                                        >> 0x12U) & 
                                       (vlTOPp->top__DOT__dut0__DOT__carry_array 
                                        >> 0x11U))));
    vlTOPp->top__DOT__dut0__DOT____Vcellout__genblk1__BRA__19__KET____DOT__fa0__co 
        = (1U & (((vlTOPp->top__DOT__in_sum_a >> 0x13U) 
                  & ((vlTOPp->top__DOT__in_sum_b >> 0x13U) 
                     | (vlTOPp->top__DOT__dut0__DOT__carry_array 
                        >> 0x12U))) | ((vlTOPp->top__DOT__in_sum_b 
                                        >> 0x13U) & 
                                       (vlTOPp->top__DOT__dut0__DOT__carry_array 
                                        >> 0x12U))));
    vlTOPp->top__DOT__dut0__DOT____Vcellout__genblk1__BRA__20__KET____DOT__fa0__co 
        = (1U & (((vlTOPp->top__DOT__in_sum_a >> 0x14U) 
                  & ((vlTOPp->top__DOT__in_sum_b >> 0x14U) 
                     | (vlTOPp->top__DOT__dut0__DOT__carry_array 
                        >> 0x13U))) | ((vlTOPp->top__DOT__in_sum_b 
                                        >> 0x14U) & 
                                       (vlTOPp->top__DOT__dut0__DOT__carry_array 
                                        >> 0x13U))));
    vlTOPp->top__DOT__dut0__DOT____Vcellout__genblk1__BRA__21__KET____DOT__fa0__co 
        = (1U & (((vlTOPp->top__DOT__in_sum_a >> 0x15U) 
                  & ((vlTOPp->top__DOT__in_sum_b >> 0x15U) 
                     | (vlTOPp->top__DOT__dut0__DOT__carry_array 
                        >> 0x14U))) | ((vlTOPp->top__DOT__in_sum_b 
                                        >> 0x15U) & 
                                       (vlTOPp->top__DOT__dut0__DOT__carry_array 
                                        >> 0x14U))));
    vlTOPp->top__DOT__dut0__DOT____Vcellout__genblk1__BRA__22__KET____DOT__fa0__co 
        = (1U & (((vlTOPp->top__DOT__in_sum_a >> 0x16U) 
                  & ((vlTOPp->top__DOT__in_sum_b >> 0x16U) 
                     | (vlTOPp->top__DOT__dut0__DOT__carry_array 
                        >> 0x15U))) | ((vlTOPp->top__DOT__in_sum_b 
                                        >> 0x16U) & 
                                       (vlTOPp->top__DOT__dut0__DOT__carry_array 
                                        >> 0x15U))));
    vlTOPp->top__DOT__dut0__DOT____Vcellout__genblk1__BRA__23__KET____DOT__fa0__co 
        = (1U & (((vlTOPp->top__DOT__in_sum_a >> 0x17U) 
                  & ((vlTOPp->top__DOT__in_sum_b >> 0x17U) 
                     | (vlTOPp->top__DOT__dut0__DOT__carry_array 
                        >> 0x16U))) | ((vlTOPp->top__DOT__in_sum_b 
                                        >> 0x17U) & 
                                       (vlTOPp->top__DOT__dut0__DOT__carry_array 
                                        >> 0x16U))));
    vlTOPp->top__DOT__dut0__DOT____Vcellout__genblk1__BRA__24__KET____DOT__fa0__co 
        = (1U & (((vlTOPp->top__DOT__in_sum_a >> 0x18U) 
                  & ((vlTOPp->top__DOT__in_sum_b >> 0x18U) 
                     | (vlTOPp->top__DOT__dut0__DOT__carry_array 
                        >> 0x17U))) | ((vlTOPp->top__DOT__in_sum_b 
                                        >> 0x18U) & 
                                       (vlTOPp->top__DOT__dut0__DOT__carry_array 
                                        >> 0x17U))));
    vlTOPp->top__DOT__dut0__DOT____Vcellout__genblk1__BRA__25__KET____DOT__fa0__co 
        = (1U & (((vlTOPp->top__DOT__in_sum_a >> 0x19U) 
                  & ((vlTOPp->top__DOT__in_sum_b >> 0x19U) 
                     | (vlTOPp->top__DOT__dut0__DOT__carry_array 
                        >> 0x18U))) | ((vlTOPp->top__DOT__in_sum_b 
                                        >> 0x19U) & 
                                       (vlTOPp->top__DOT__dut0__DOT__carry_array 
                                        >> 0x18U))));
    vlTOPp->top__DOT__dut0__DOT____Vcellout__genblk1__BRA__26__KET____DOT__fa0__co 
        = (1U & (((vlTOPp->top__DOT__in_sum_a >> 0x1aU) 
                  & ((vlTOPp->top__DOT__in_sum_b >> 0x1aU) 
                     | (vlTOPp->top__DOT__dut0__DOT__carry_array 
                        >> 0x19U))) | ((vlTOPp->top__DOT__in_sum_b 
                                        >> 0x1aU) & 
                                       (vlTOPp->top__DOT__dut0__DOT__carry_array 
                                        >> 0x19U))));
    vlTOPp->top__DOT__dut0__DOT____Vcellout__genblk1__BRA__27__KET____DOT__fa0__co 
        = (1U & (((vlTOPp->top__DOT__in_sum_a >> 0x1bU) 
                  & ((vlTOPp->top__DOT__in_sum_b >> 0x1bU) 
                     | (vlTOPp->top__DOT__dut0__DOT__carry_array 
                        >> 0x1aU))) | ((vlTOPp->top__DOT__in_sum_b 
                                        >> 0x1bU) & 
                                       (vlTOPp->top__DOT__dut0__DOT__carry_array 
                                        >> 0x1aU))));
    vlTOPp->top__DOT__dut0__DOT____Vcellout__genblk1__BRA__28__KET____DOT__fa0__co 
        = (1U & (((vlTOPp->top__DOT__in_sum_a >> 0x1cU) 
                  & ((vlTOPp->top__DOT__in_sum_b >> 0x1cU) 
                     | (vlTOPp->top__DOT__dut0__DOT__carry_array 
                        >> 0x1bU))) | ((vlTOPp->top__DOT__in_sum_b 
                                        >> 0x1cU) & 
                                       (vlTOPp->top__DOT__dut0__DOT__carry_array 
                                        >> 0x1bU))));
    vlTOPp->top__DOT__dut0__DOT____Vcellout__genblk1__BRA__29__KET____DOT__fa0__co 
        = (1U & (((vlTOPp->top__DOT__in_sum_a >> 0x1dU) 
                  & ((vlTOPp->top__DOT__in_sum_b >> 0x1dU) 
                     | (vlTOPp->top__DOT__dut0__DOT__carry_array 
                        >> 0x1cU))) | ((vlTOPp->top__DOT__in_sum_b 
                                        >> 0x1dU) & 
                                       (vlTOPp->top__DOT__dut0__DOT__carry_array 
                                        >> 0x1cU))));
    vlTOPp->top__DOT__dut0__DOT____Vcellout__genblk1__BRA__30__KET____DOT__fa0__co 
        = (1U & (((vlTOPp->top__DOT__in_sum_a >> 0x1eU) 
                  & ((vlTOPp->top__DOT__in_sum_b >> 0x1eU) 
                     | (vlTOPp->top__DOT__dut0__DOT__carry_array 
                        >> 0x1dU))) | ((vlTOPp->top__DOT__in_sum_b 
                                        >> 0x1eU) & 
                                       (vlTOPp->top__DOT__dut0__DOT__carry_array 
                                        >> 0x1dU))));
    vlTOPp->top__DOT__dut0__DOT____Vcellout__genblk1__BRA__31__KET____DOT__fa0__co 
        = (1U & (((vlTOPp->top__DOT__in_sum_a >> 0x1fU) 
                  & ((vlTOPp->top__DOT__in_sum_b >> 0x1fU) 
                     | (vlTOPp->top__DOT__dut0__DOT__carry_array 
                        >> 0x1eU))) | ((vlTOPp->top__DOT__in_sum_b 
                                        >> 0x1fU) & 
                                       (vlTOPp->top__DOT__dut0__DOT__carry_array 
                                        >> 0x1eU))));
    vlTOPp->top__DOT__dut0__DOT__sum = ((0xfffffffdU 
                                         & vlTOPp->top__DOT__dut0__DOT__sum) 
                                        | (2U & ((0xfffffffeU 
                                                  & (vlTOPp->top__DOT__in_sum_a 
                                                     ^ vlTOPp->top__DOT__in_sum_b)) 
                                                 ^ 
                                                 (vlTOPp->top__DOT__dut0__DOT__carry_array 
                                                  << 1U))));
    vlTOPp->top__DOT__dut0__DOT__sum = ((0xfffffffbU 
                                         & vlTOPp->top__DOT__dut0__DOT__sum) 
                                        | (4U & ((0xfffffffcU 
                                                  & (vlTOPp->top__DOT__in_sum_a 
                                                     ^ vlTOPp->top__DOT__in_sum_b)) 
                                                 ^ 
                                                 (0xfffffffcU 
                                                  & (vlTOPp->top__DOT__dut0__DOT__carry_array 
                                                     << 1U)))));
    vlTOPp->top__DOT__dut0__DOT__sum = ((0xfffffff7U 
                                         & vlTOPp->top__DOT__dut0__DOT__sum) 
                                        | (8U & ((0xfffffff8U 
                                                  & (vlTOPp->top__DOT__in_sum_a 
                                                     ^ vlTOPp->top__DOT__in_sum_b)) 
                                                 ^ 
                                                 (0xfffffff8U 
                                                  & (vlTOPp->top__DOT__dut0__DOT__carry_array 
                                                     << 1U)))));
    vlTOPp->top__DOT__dut0__DOT__sum = ((0xffffffefU 
                                         & vlTOPp->top__DOT__dut0__DOT__sum) 
                                        | (0x10U & 
                                           ((0xfffffff0U 
                                             & (vlTOPp->top__DOT__in_sum_a 
                                                ^ vlTOPp->top__DOT__in_sum_b)) 
                                            ^ (0xfffffff0U 
                                               & (vlTOPp->top__DOT__dut0__DOT__carry_array 
                                                  << 1U)))));
    vlTOPp->top__DOT__dut0__DOT__sum = ((0xffffffdfU 
                                         & vlTOPp->top__DOT__dut0__DOT__sum) 
                                        | (0x20U & 
                                           ((0xffffffe0U 
                                             & (vlTOPp->top__DOT__in_sum_a 
                                                ^ vlTOPp->top__DOT__in_sum_b)) 
                                            ^ (0xffffffe0U 
                                               & (vlTOPp->top__DOT__dut0__DOT__carry_array 
                                                  << 1U)))));
    vlTOPp->top__DOT__dut0__DOT__sum = ((0xffffffbfU 
                                         & vlTOPp->top__DOT__dut0__DOT__sum) 
                                        | (0x40U & 
                                           ((0xffffffc0U 
                                             & (vlTOPp->top__DOT__in_sum_a 
                                                ^ vlTOPp->top__DOT__in_sum_b)) 
                                            ^ (0xffffffc0U 
                                               & (vlTOPp->top__DOT__dut0__DOT__carry_array 
                                                  << 1U)))));
    vlTOPp->top__DOT__dut0__DOT__sum = ((0xffffff7fU 
                                         & vlTOPp->top__DOT__dut0__DOT__sum) 
                                        | (0x80U & 
                                           ((0xffffff80U 
                                             & (vlTOPp->top__DOT__in_sum_a 
                                                ^ vlTOPp->top__DOT__in_sum_b)) 
                                            ^ (0xffffff80U 
                                               & (vlTOPp->top__DOT__dut0__DOT__carry_array 
                                                  << 1U)))));
    vlTOPp->top__DOT__dut0__DOT__sum = ((0xfffffeffU 
                                         & vlTOPp->top__DOT__dut0__DOT__sum) 
                                        | (0x100U & 
                                           ((0xffffff00U 
                                             & (vlTOPp->top__DOT__in_sum_a 
                                                ^ vlTOPp->top__DOT__in_sum_b)) 
                                            ^ (0xffffff00U 
                                               & (vlTOPp->top__DOT__dut0__DOT__carry_array 
                                                  << 1U)))));
    vlTOPp->top__DOT__dut0__DOT__sum = ((0xfffffdffU 
                                         & vlTOPp->top__DOT__dut0__DOT__sum) 
                                        | (0x200U & 
                                           ((0xfffffe00U 
                                             & (vlTOPp->top__DOT__in_sum_a 
                                                ^ vlTOPp->top__DOT__in_sum_b)) 
                                            ^ (0xfffffe00U 
                                               & (vlTOPp->top__DOT__dut0__DOT__carry_array 
                                                  << 1U)))));
    vlTOPp->top__DOT__dut0__DOT__sum = ((0xfffffbffU 
                                         & vlTOPp->top__DOT__dut0__DOT__sum) 
                                        | (0x400U & 
                                           ((0xfffffc00U 
                                             & (vlTOPp->top__DOT__in_sum_a 
                                                ^ vlTOPp->top__DOT__in_sum_b)) 
                                            ^ (0xfffffc00U 
                                               & (vlTOPp->top__DOT__dut0__DOT__carry_array 
                                                  << 1U)))));
    vlTOPp->top__DOT__dut0__DOT__sum = ((0xfffff7ffU 
                                         & vlTOPp->top__DOT__dut0__DOT__sum) 
                                        | (0x800U & 
                                           ((0xfffff800U 
                                             & (vlTOPp->top__DOT__in_sum_a 
                                                ^ vlTOPp->top__DOT__in_sum_b)) 
                                            ^ (0xfffff800U 
                                               & (vlTOPp->top__DOT__dut0__DOT__carry_array 
                                                  << 1U)))));
    vlTOPp->top__DOT__dut0__DOT__sum = ((0xffffefffU 
                                         & vlTOPp->top__DOT__dut0__DOT__sum) 
                                        | (0x1000U 
                                           & ((0xfffff000U 
                                               & (vlTOPp->top__DOT__in_sum_a 
                                                  ^ vlTOPp->top__DOT__in_sum_b)) 
                                              ^ (0xfffff000U 
                                                 & (vlTOPp->top__DOT__dut0__DOT__carry_array 
                                                    << 1U)))));
    vlTOPp->top__DOT__dut0__DOT__sum = ((0xffffdfffU 
                                         & vlTOPp->top__DOT__dut0__DOT__sum) 
                                        | (0x2000U 
                                           & ((0xffffe000U 
                                               & (vlTOPp->top__DOT__in_sum_a 
                                                  ^ vlTOPp->top__DOT__in_sum_b)) 
                                              ^ (0xffffe000U 
                                                 & (vlTOPp->top__DOT__dut0__DOT__carry_array 
                                                    << 1U)))));
    vlTOPp->top__DOT__dut0__DOT__sum = ((0xffffbfffU 
                                         & vlTOPp->top__DOT__dut0__DOT__sum) 
                                        | (0x4000U 
                                           & ((0xffffc000U 
                                               & (vlTOPp->top__DOT__in_sum_a 
                                                  ^ vlTOPp->top__DOT__in_sum_b)) 
                                              ^ (0xffffc000U 
                                                 & (vlTOPp->top__DOT__dut0__DOT__carry_array 
                                                    << 1U)))));
    vlTOPp->top__DOT__dut0__DOT__sum = ((0xffff7fffU 
                                         & vlTOPp->top__DOT__dut0__DOT__sum) 
                                        | (0x8000U 
                                           & ((0xffff8000U 
                                               & (vlTOPp->top__DOT__in_sum_a 
                                                  ^ vlTOPp->top__DOT__in_sum_b)) 
                                              ^ (0xffff8000U 
                                                 & (vlTOPp->top__DOT__dut0__DOT__carry_array 
                                                    << 1U)))));
    vlTOPp->top__DOT__dut0__DOT__sum = ((0xfffeffffU 
                                         & vlTOPp->top__DOT__dut0__DOT__sum) 
                                        | (0x10000U 
                                           & ((0xffff0000U 
                                               & (vlTOPp->top__DOT__in_sum_a 
                                                  ^ vlTOPp->top__DOT__in_sum_b)) 
                                              ^ (0xffff0000U 
                                                 & (vlTOPp->top__DOT__dut0__DOT__carry_array 
                                                    << 1U)))));
    vlTOPp->top__DOT__dut0__DOT__sum = ((0xfffdffffU 
                                         & vlTOPp->top__DOT__dut0__DOT__sum) 
                                        | (0x20000U 
                                           & ((0xfffe0000U 
                                               & (vlTOPp->top__DOT__in_sum_a 
                                                  ^ vlTOPp->top__DOT__in_sum_b)) 
                                              ^ (0xfffe0000U 
                                                 & (vlTOPp->top__DOT__dut0__DOT__carry_array 
                                                    << 1U)))));
    vlTOPp->top__DOT__dut0__DOT__sum = ((0xfffbffffU 
                                         & vlTOPp->top__DOT__dut0__DOT__sum) 
                                        | (0x40000U 
                                           & ((0xfffc0000U 
                                               & (vlTOPp->top__DOT__in_sum_a 
                                                  ^ vlTOPp->top__DOT__in_sum_b)) 
                                              ^ (0xfffc0000U 
                                                 & (vlTOPp->top__DOT__dut0__DOT__carry_array 
                                                    << 1U)))));
    vlTOPp->top__DOT__dut0__DOT__sum = ((0xfff7ffffU 
                                         & vlTOPp->top__DOT__dut0__DOT__sum) 
                                        | (0x80000U 
                                           & ((0xfff80000U 
                                               & (vlTOPp->top__DOT__in_sum_a 
                                                  ^ vlTOPp->top__DOT__in_sum_b)) 
                                              ^ (0xfff80000U 
                                                 & (vlTOPp->top__DOT__dut0__DOT__carry_array 
                                                    << 1U)))));
    vlTOPp->top__DOT__dut0__DOT__sum = ((0xffefffffU 
                                         & vlTOPp->top__DOT__dut0__DOT__sum) 
                                        | (0x100000U 
                                           & ((0xfff00000U 
                                               & (vlTOPp->top__DOT__in_sum_a 
                                                  ^ vlTOPp->top__DOT__in_sum_b)) 
                                              ^ (0xfff00000U 
                                                 & (vlTOPp->top__DOT__dut0__DOT__carry_array 
                                                    << 1U)))));
    vlTOPp->top__DOT__dut0__DOT__sum = ((0xffdfffffU 
                                         & vlTOPp->top__DOT__dut0__DOT__sum) 
                                        | (0x200000U 
                                           & ((0xffe00000U 
                                               & (vlTOPp->top__DOT__in_sum_a 
                                                  ^ vlTOPp->top__DOT__in_sum_b)) 
                                              ^ (0xffe00000U 
                                                 & (vlTOPp->top__DOT__dut0__DOT__carry_array 
                                                    << 1U)))));
    vlTOPp->top__DOT__dut0__DOT__sum = ((0xffbfffffU 
                                         & vlTOPp->top__DOT__dut0__DOT__sum) 
                                        | (0x400000U 
                                           & ((0xffc00000U 
                                               & (vlTOPp->top__DOT__in_sum_a 
                                                  ^ vlTOPp->top__DOT__in_sum_b)) 
                                              ^ (0xffc00000U 
                                                 & (vlTOPp->top__DOT__dut0__DOT__carry_array 
                                                    << 1U)))));
    vlTOPp->top__DOT__dut0__DOT__sum = ((0xff7fffffU 
                                         & vlTOPp->top__DOT__dut0__DOT__sum) 
                                        | (0x800000U 
                                           & ((0xff800000U 
                                               & (vlTOPp->top__DOT__in_sum_a 
                                                  ^ vlTOPp->top__DOT__in_sum_b)) 
                                              ^ (0xff800000U 
                                                 & (vlTOPp->top__DOT__dut0__DOT__carry_array 
                                                    << 1U)))));
    vlTOPp->top__DOT__dut0__DOT__sum = ((0xfeffffffU 
                                         & vlTOPp->top__DOT__dut0__DOT__sum) 
                                        | (0x1000000U 
                                           & ((0xff000000U 
                                               & (vlTOPp->top__DOT__in_sum_a 
                                                  ^ vlTOPp->top__DOT__in_sum_b)) 
                                              ^ (0xff000000U 
                                                 & (vlTOPp->top__DOT__dut0__DOT__carry_array 
                                                    << 1U)))));
    vlTOPp->top__DOT__dut0__DOT__sum = ((0xfdffffffU 
                                         & vlTOPp->top__DOT__dut0__DOT__sum) 
                                        | (0x2000000U 
                                           & ((0xfe000000U 
                                               & (vlTOPp->top__DOT__in_sum_a 
                                                  ^ vlTOPp->top__DOT__in_sum_b)) 
                                              ^ (0xfe000000U 
                                                 & (vlTOPp->top__DOT__dut0__DOT__carry_array 
                                                    << 1U)))));
    vlTOPp->top__DOT__dut0__DOT__sum = ((0xfbffffffU 
                                         & vlTOPp->top__DOT__dut0__DOT__sum) 
                                        | (0x4000000U 
                                           & ((0xfc000000U 
                                               & (vlTOPp->top__DOT__in_sum_a 
                                                  ^ vlTOPp->top__DOT__in_sum_b)) 
                                              ^ (0xfc000000U 
                                                 & (vlTOPp->top__DOT__dut0__DOT__carry_array 
                                                    << 1U)))));
    vlTOPp->top__DOT__dut0__DOT__sum = ((0xf7ffffffU 
                                         & vlTOPp->top__DOT__dut0__DOT__sum) 
                                        | (0x8000000U 
                                           & ((0xf8000000U 
                                               & (vlTOPp->top__DOT__in_sum_a 
                                                  ^ vlTOPp->top__DOT__in_sum_b)) 
                                              ^ (0xf8000000U 
                                                 & (vlTOPp->top__DOT__dut0__DOT__carry_array 
                                                    << 1U)))));
    vlTOPp->top__DOT__dut0__DOT__sum = ((0xefffffffU 
                                         & vlTOPp->top__DOT__dut0__DOT__sum) 
                                        | (0x10000000U 
                                           & ((0xf0000000U 
                                               & (vlTOPp->top__DOT__in_sum_a 
                                                  ^ vlTOPp->top__DOT__in_sum_b)) 
                                              ^ (0xf0000000U 
                                                 & (vlTOPp->top__DOT__dut0__DOT__carry_array 
                                                    << 1U)))));
    vlTOPp->top__DOT__dut0__DOT__sum = ((0xdfffffffU 
                                         & vlTOPp->top__DOT__dut0__DOT__sum) 
                                        | (0x20000000U 
                                           & ((0xe0000000U 
                                               & (vlTOPp->top__DOT__in_sum_a 
                                                  ^ vlTOPp->top__DOT__in_sum_b)) 
                                              ^ (0xe0000000U 
                                                 & (vlTOPp->top__DOT__dut0__DOT__carry_array 
                                                    << 1U)))));
    vlTOPp->top__DOT__dut0__DOT__sum = ((0xbfffffffU 
                                         & vlTOPp->top__DOT__dut0__DOT__sum) 
                                        | (0x40000000U 
                                           & ((0xc0000000U 
                                               & (vlTOPp->top__DOT__in_sum_a 
                                                  ^ vlTOPp->top__DOT__in_sum_b)) 
                                              ^ (0xc0000000U 
                                                 & (vlTOPp->top__DOT__dut0__DOT__carry_array 
                                                    << 1U)))));
    vlTOPp->top__DOT__dut0__DOT__sum = ((0x7fffffffU 
                                         & vlTOPp->top__DOT__dut0__DOT__sum) 
                                        | (0x80000000U 
                                           & ((0x80000000U 
                                               & (vlTOPp->top__DOT__in_sum_a 
                                                  ^ vlTOPp->top__DOT__in_sum_b)) 
                                              ^ (0x80000000U 
                                                 & (vlTOPp->top__DOT__dut0__DOT__carry_array 
                                                    << 1U)))));
    vlTOPp->top__DOT__dut0__DOT__carry_array = ((0xfffffffdU 
                                                 & vlTOPp->top__DOT__dut0__DOT__carry_array) 
                                                | ((IData)(vlTOPp->top__DOT__dut0__DOT____Vcellout__genblk1__BRA__1__KET____DOT__fa0__co) 
                                                   << 1U));
    vlTOPp->top__DOT__dut0__DOT__carry_array = ((0xfffffffbU 
                                                 & vlTOPp->top__DOT__dut0__DOT__carry_array) 
                                                | ((IData)(vlTOPp->top__DOT__dut0__DOT____Vcellout__genblk1__BRA__2__KET____DOT__fa0__co) 
                                                   << 2U));
    vlTOPp->top__DOT__dut0__DOT__carry_array = ((0xfffffff7U 
                                                 & vlTOPp->top__DOT__dut0__DOT__carry_array) 
                                                | ((IData)(vlTOPp->top__DOT__dut0__DOT____Vcellout__genblk1__BRA__3__KET____DOT__fa0__co) 
                                                   << 3U));
    vlTOPp->top__DOT__dut0__DOT__carry_array = ((0xffffffefU 
                                                 & vlTOPp->top__DOT__dut0__DOT__carry_array) 
                                                | ((IData)(vlTOPp->top__DOT__dut0__DOT____Vcellout__genblk1__BRA__4__KET____DOT__fa0__co) 
                                                   << 4U));
    vlTOPp->top__DOT__dut0__DOT__carry_array = ((0xffffffdfU 
                                                 & vlTOPp->top__DOT__dut0__DOT__carry_array) 
                                                | ((IData)(vlTOPp->top__DOT__dut0__DOT____Vcellout__genblk1__BRA__5__KET____DOT__fa0__co) 
                                                   << 5U));
    vlTOPp->top__DOT__dut0__DOT__carry_array = ((0xffffffbfU 
                                                 & vlTOPp->top__DOT__dut0__DOT__carry_array) 
                                                | ((IData)(vlTOPp->top__DOT__dut0__DOT____Vcellout__genblk1__BRA__6__KET____DOT__fa0__co) 
                                                   << 6U));
    vlTOPp->top__DOT__dut0__DOT__carry_array = ((0xffffff7fU 
                                                 & vlTOPp->top__DOT__dut0__DOT__carry_array) 
                                                | ((IData)(vlTOPp->top__DOT__dut0__DOT____Vcellout__genblk1__BRA__7__KET____DOT__fa0__co) 
                                                   << 7U));
    vlTOPp->top__DOT__dut0__DOT__carry_array = ((0xfffffeffU 
                                                 & vlTOPp->top__DOT__dut0__DOT__carry_array) 
                                                | ((IData)(vlTOPp->top__DOT__dut0__DOT____Vcellout__genblk1__BRA__8__KET____DOT__fa0__co) 
                                                   << 8U));
    vlTOPp->top__DOT__dut0__DOT__carry_array = ((0xfffffdffU 
                                                 & vlTOPp->top__DOT__dut0__DOT__carry_array) 
                                                | ((IData)(vlTOPp->top__DOT__dut0__DOT____Vcellout__genblk1__BRA__9__KET____DOT__fa0__co) 
                                                   << 9U));
    vlTOPp->top__DOT__dut0__DOT__carry_array = ((0xfffffbffU 
                                                 & vlTOPp->top__DOT__dut0__DOT__carry_array) 
                                                | ((IData)(vlTOPp->top__DOT__dut0__DOT____Vcellout__genblk1__BRA__10__KET____DOT__fa0__co) 
                                                   << 0xaU));
    vlTOPp->top__DOT__dut0__DOT__carry_array = ((0xfffff7ffU 
                                                 & vlTOPp->top__DOT__dut0__DOT__carry_array) 
                                                | ((IData)(vlTOPp->top__DOT__dut0__DOT____Vcellout__genblk1__BRA__11__KET____DOT__fa0__co) 
                                                   << 0xbU));
    vlTOPp->top__DOT__dut0__DOT__carry_array = ((0xffffefffU 
                                                 & vlTOPp->top__DOT__dut0__DOT__carry_array) 
                                                | ((IData)(vlTOPp->top__DOT__dut0__DOT____Vcellout__genblk1__BRA__12__KET____DOT__fa0__co) 
                                                   << 0xcU));
    vlTOPp->top__DOT__dut0__DOT__carry_array = ((0xffffdfffU 
                                                 & vlTOPp->top__DOT__dut0__DOT__carry_array) 
                                                | ((IData)(vlTOPp->top__DOT__dut0__DOT____Vcellout__genblk1__BRA__13__KET____DOT__fa0__co) 
                                                   << 0xdU));
    vlTOPp->top__DOT__dut0__DOT__carry_array = ((0xffffbfffU 
                                                 & vlTOPp->top__DOT__dut0__DOT__carry_array) 
                                                | ((IData)(vlTOPp->top__DOT__dut0__DOT____Vcellout__genblk1__BRA__14__KET____DOT__fa0__co) 
                                                   << 0xeU));
    vlTOPp->top__DOT__dut0__DOT__carry_array = ((0xffff7fffU 
                                                 & vlTOPp->top__DOT__dut0__DOT__carry_array) 
                                                | ((IData)(vlTOPp->top__DOT__dut0__DOT____Vcellout__genblk1__BRA__15__KET____DOT__fa0__co) 
                                                   << 0xfU));
    vlTOPp->top__DOT__dut0__DOT__carry_array = ((0xfffeffffU 
                                                 & vlTOPp->top__DOT__dut0__DOT__carry_array) 
                                                | ((IData)(vlTOPp->top__DOT__dut0__DOT____Vcellout__genblk1__BRA__16__KET____DOT__fa0__co) 
                                                   << 0x10U));
    vlTOPp->top__DOT__dut0__DOT__carry_array = ((0xfffdffffU 
                                                 & vlTOPp->top__DOT__dut0__DOT__carry_array) 
                                                | ((IData)(vlTOPp->top__DOT__dut0__DOT____Vcellout__genblk1__BRA__17__KET____DOT__fa0__co) 
                                                   << 0x11U));
    vlTOPp->top__DOT__dut0__DOT__carry_array = ((0xfffbffffU 
                                                 & vlTOPp->top__DOT__dut0__DOT__carry_array) 
                                                | ((IData)(vlTOPp->top__DOT__dut0__DOT____Vcellout__genblk1__BRA__18__KET____DOT__fa0__co) 
                                                   << 0x12U));
    vlTOPp->top__DOT__dut0__DOT__carry_array = ((0xfff7ffffU 
                                                 & vlTOPp->top__DOT__dut0__DOT__carry_array) 
                                                | ((IData)(vlTOPp->top__DOT__dut0__DOT____Vcellout__genblk1__BRA__19__KET____DOT__fa0__co) 
                                                   << 0x13U));
    vlTOPp->top__DOT__dut0__DOT__carry_array = ((0xffefffffU 
                                                 & vlTOPp->top__DOT__dut0__DOT__carry_array) 
                                                | ((IData)(vlTOPp->top__DOT__dut0__DOT____Vcellout__genblk1__BRA__20__KET____DOT__fa0__co) 
                                                   << 0x14U));
    vlTOPp->top__DOT__dut0__DOT__carry_array = ((0xffdfffffU 
                                                 & vlTOPp->top__DOT__dut0__DOT__carry_array) 
                                                | ((IData)(vlTOPp->top__DOT__dut0__DOT____Vcellout__genblk1__BRA__21__KET____DOT__fa0__co) 
                                                   << 0x15U));
    vlTOPp->top__DOT__dut0__DOT__carry_array = ((0xffbfffffU 
                                                 & vlTOPp->top__DOT__dut0__DOT__carry_array) 
                                                | ((IData)(vlTOPp->top__DOT__dut0__DOT____Vcellout__genblk1__BRA__22__KET____DOT__fa0__co) 
                                                   << 0x16U));
    vlTOPp->top__DOT__dut0__DOT__carry_array = ((0xff7fffffU 
                                                 & vlTOPp->top__DOT__dut0__DOT__carry_array) 
                                                | ((IData)(vlTOPp->top__DOT__dut0__DOT____Vcellout__genblk1__BRA__23__KET____DOT__fa0__co) 
                                                   << 0x17U));
    vlTOPp->top__DOT__dut0__DOT__carry_array = ((0xfeffffffU 
                                                 & vlTOPp->top__DOT__dut0__DOT__carry_array) 
                                                | ((IData)(vlTOPp->top__DOT__dut0__DOT____Vcellout__genblk1__BRA__24__KET____DOT__fa0__co) 
                                                   << 0x18U));
    vlTOPp->top__DOT__dut0__DOT__carry_array = ((0xfdffffffU 
                                                 & vlTOPp->top__DOT__dut0__DOT__carry_array) 
                                                | ((IData)(vlTOPp->top__DOT__dut0__DOT____Vcellout__genblk1__BRA__25__KET____DOT__fa0__co) 
                                                   << 0x19U));
    vlTOPp->top__DOT__dut0__DOT__carry_array = ((0xfbffffffU 
                                                 & vlTOPp->top__DOT__dut0__DOT__carry_array) 
                                                | ((IData)(vlTOPp->top__DOT__dut0__DOT____Vcellout__genblk1__BRA__26__KET____DOT__fa0__co) 
                                                   << 0x1aU));
    vlTOPp->top__DOT__dut0__DOT__carry_array = ((0xf7ffffffU 
                                                 & vlTOPp->top__DOT__dut0__DOT__carry_array) 
                                                | ((IData)(vlTOPp->top__DOT__dut0__DOT____Vcellout__genblk1__BRA__27__KET____DOT__fa0__co) 
                                                   << 0x1bU));
    vlTOPp->top__DOT__dut0__DOT__carry_array = ((0xefffffffU 
                                                 & vlTOPp->top__DOT__dut0__DOT__carry_array) 
                                                | ((IData)(vlTOPp->top__DOT__dut0__DOT____Vcellout__genblk1__BRA__28__KET____DOT__fa0__co) 
                                                   << 0x1cU));
    vlTOPp->top__DOT__dut0__DOT__carry_array = ((0xdfffffffU 
                                                 & vlTOPp->top__DOT__dut0__DOT__carry_array) 
                                                | ((IData)(vlTOPp->top__DOT__dut0__DOT____Vcellout__genblk1__BRA__29__KET____DOT__fa0__co) 
                                                   << 0x1dU));
    vlTOPp->top__DOT__dut0__DOT__carry_array = ((0xbfffffffU 
                                                 & vlTOPp->top__DOT__dut0__DOT__carry_array) 
                                                | ((IData)(vlTOPp->top__DOT__dut0__DOT____Vcellout__genblk1__BRA__30__KET____DOT__fa0__co) 
                                                   << 0x1eU));
    vlTOPp->top__DOT__dut0__DOT__carry_array = ((0x7fffffffU 
                                                 & vlTOPp->top__DOT__dut0__DOT__carry_array) 
                                                | ((IData)(vlTOPp->top__DOT__dut0__DOT____Vcellout__genblk1__BRA__31__KET____DOT__fa0__co) 
                                                   << 0x1fU));
}

void Vtop::_eval(Vtop__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop::_eval\n"); );
    Vtop* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (((IData)(vlTOPp->clk) & (~ (IData)(vlTOPp->__Vclklast__TOP__clk)))) {
        vlTOPp->_sequent__TOP__1(vlSymsp);
    }
    vlTOPp->_combo__TOP__3(vlSymsp);
    // Final
    vlTOPp->__Vclklast__TOP__clk = vlTOPp->clk;
}

void Vtop::_eval_initial(Vtop__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop::_eval_initial\n"); );
    Vtop* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vclklast__TOP__clk = vlTOPp->clk;
}

void Vtop::final() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop::final\n"); );
    // Variables
    Vtop__Syms* __restrict vlSymsp = this->__VlSymsp;
    Vtop* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
}

void Vtop::_eval_settle(Vtop__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop::_eval_settle\n"); );
    Vtop* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->_settle__TOP__2(vlSymsp);
}

VL_INLINE_OPT QData Vtop::_change_request(Vtop__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop::_change_request\n"); );
    Vtop* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    // Change detection
    QData __req = false;  // Logically a bool
    __req |= ((vlTOPp->top__DOT__dut0__DOT__carry_array ^ vlTOPp->__Vchglast__TOP__top__DOT__dut0__DOT__carry_array));
    VL_DEBUG_IF( if(__req && ((vlTOPp->top__DOT__dut0__DOT__carry_array ^ vlTOPp->__Vchglast__TOP__top__DOT__dut0__DOT__carry_array))) VL_DBG_MSGF("        CHANGE: rca_adder.v:15: top.dut0.carry_array\n"); );
    // Final
    vlTOPp->__Vchglast__TOP__top__DOT__dut0__DOT__carry_array 
        = vlTOPp->top__DOT__dut0__DOT__carry_array;
    return __req;
}

#ifdef VL_DEBUG
void Vtop::_eval_debug_assertions() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop::_eval_debug_assertions\n"); );
    // Body
    if (VL_UNLIKELY((clk & 0xfeU))) {
        Verilated::overWidthError("clk");}
    if (VL_UNLIKELY((resetn & 0xfeU))) {
        Verilated::overWidthError("resetn");}
    if (VL_UNLIKELY((enable & 0xfeU))) {
        Verilated::overWidthError("enable");}
    if (VL_UNLIKELY((a & 0xfeU))) {
        Verilated::overWidthError("a");}
    if (VL_UNLIKELY((b & 0xfeU))) {
        Verilated::overWidthError("b");}
}
#endif  // VL_DEBUG

void Vtop::_ctor_var_reset() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop::_ctor_var_reset\n"); );
    // Body
    clk = VL_RAND_RESET_I(1);
    resetn = VL_RAND_RESET_I(1);
    enable = VL_RAND_RESET_I(1);
    a = VL_RAND_RESET_I(1);
    b = VL_RAND_RESET_I(1);
    sum = VL_RAND_RESET_I(1);
    out_carry = VL_RAND_RESET_I(1);
    top__DOT__in_sum_a = VL_RAND_RESET_I(32);
    top__DOT__in_sum_b = VL_RAND_RESET_I(32);
    top__DOT__out_sum_result = VL_RAND_RESET_I(32);
    top__DOT__input0__DOT__counter = VL_RAND_RESET_I(32);
    top__DOT__input1__DOT__counter = VL_RAND_RESET_I(32);
    top__DOT__output0__DOT__counter = VL_RAND_RESET_I(32);
    top__DOT__dut0__DOT__sum = VL_RAND_RESET_I(32);
    top__DOT__dut0__DOT__carry_array = VL_RAND_RESET_I(32);
    top__DOT__dut0__DOT____Vcellout__genblk1__BRA__1__KET____DOT__fa0__co = VL_RAND_RESET_I(1);
    top__DOT__dut0__DOT____Vcellout__genblk1__BRA__2__KET____DOT__fa0__co = VL_RAND_RESET_I(1);
    top__DOT__dut0__DOT____Vcellout__genblk1__BRA__3__KET____DOT__fa0__co = VL_RAND_RESET_I(1);
    top__DOT__dut0__DOT____Vcellout__genblk1__BRA__4__KET____DOT__fa0__co = VL_RAND_RESET_I(1);
    top__DOT__dut0__DOT____Vcellout__genblk1__BRA__5__KET____DOT__fa0__co = VL_RAND_RESET_I(1);
    top__DOT__dut0__DOT____Vcellout__genblk1__BRA__6__KET____DOT__fa0__co = VL_RAND_RESET_I(1);
    top__DOT__dut0__DOT____Vcellout__genblk1__BRA__7__KET____DOT__fa0__co = VL_RAND_RESET_I(1);
    top__DOT__dut0__DOT____Vcellout__genblk1__BRA__8__KET____DOT__fa0__co = VL_RAND_RESET_I(1);
    top__DOT__dut0__DOT____Vcellout__genblk1__BRA__9__KET____DOT__fa0__co = VL_RAND_RESET_I(1);
    top__DOT__dut0__DOT____Vcellout__genblk1__BRA__10__KET____DOT__fa0__co = VL_RAND_RESET_I(1);
    top__DOT__dut0__DOT____Vcellout__genblk1__BRA__11__KET____DOT__fa0__co = VL_RAND_RESET_I(1);
    top__DOT__dut0__DOT____Vcellout__genblk1__BRA__12__KET____DOT__fa0__co = VL_RAND_RESET_I(1);
    top__DOT__dut0__DOT____Vcellout__genblk1__BRA__13__KET____DOT__fa0__co = VL_RAND_RESET_I(1);
    top__DOT__dut0__DOT____Vcellout__genblk1__BRA__14__KET____DOT__fa0__co = VL_RAND_RESET_I(1);
    top__DOT__dut0__DOT____Vcellout__genblk1__BRA__15__KET____DOT__fa0__co = VL_RAND_RESET_I(1);
    top__DOT__dut0__DOT____Vcellout__genblk1__BRA__16__KET____DOT__fa0__co = VL_RAND_RESET_I(1);
    top__DOT__dut0__DOT____Vcellout__genblk1__BRA__17__KET____DOT__fa0__co = VL_RAND_RESET_I(1);
    top__DOT__dut0__DOT____Vcellout__genblk1__BRA__18__KET____DOT__fa0__co = VL_RAND_RESET_I(1);
    top__DOT__dut0__DOT____Vcellout__genblk1__BRA__19__KET____DOT__fa0__co = VL_RAND_RESET_I(1);
    top__DOT__dut0__DOT____Vcellout__genblk1__BRA__20__KET____DOT__fa0__co = VL_RAND_RESET_I(1);
    top__DOT__dut0__DOT____Vcellout__genblk1__BRA__21__KET____DOT__fa0__co = VL_RAND_RESET_I(1);
    top__DOT__dut0__DOT____Vcellout__genblk1__BRA__22__KET____DOT__fa0__co = VL_RAND_RESET_I(1);
    top__DOT__dut0__DOT____Vcellout__genblk1__BRA__23__KET____DOT__fa0__co = VL_RAND_RESET_I(1);
    top__DOT__dut0__DOT____Vcellout__genblk1__BRA__24__KET____DOT__fa0__co = VL_RAND_RESET_I(1);
    top__DOT__dut0__DOT____Vcellout__genblk1__BRA__25__KET____DOT__fa0__co = VL_RAND_RESET_I(1);
    top__DOT__dut0__DOT____Vcellout__genblk1__BRA__26__KET____DOT__fa0__co = VL_RAND_RESET_I(1);
    top__DOT__dut0__DOT____Vcellout__genblk1__BRA__27__KET____DOT__fa0__co = VL_RAND_RESET_I(1);
    top__DOT__dut0__DOT____Vcellout__genblk1__BRA__28__KET____DOT__fa0__co = VL_RAND_RESET_I(1);
    top__DOT__dut0__DOT____Vcellout__genblk1__BRA__29__KET____DOT__fa0__co = VL_RAND_RESET_I(1);
    top__DOT__dut0__DOT____Vcellout__genblk1__BRA__30__KET____DOT__fa0__co = VL_RAND_RESET_I(1);
    top__DOT__dut0__DOT____Vcellout__genblk1__BRA__31__KET____DOT__fa0__co = VL_RAND_RESET_I(1);
    __Vchglast__TOP__top__DOT__dut0__DOT__carry_array = VL_RAND_RESET_I(32);
}
