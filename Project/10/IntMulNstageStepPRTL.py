#=========================================================================
# IntMulNstageStepRTL
#=========================================================================

from pymtl3 import *
from pymtl3.passes.backends.verilog import *
from pymtl3.stdlib.basic_rtl import Mux, LeftLogicalShifter, RightLogicalShifter, Adder

class IntMulNstageStepPRTL( Component ):

  # Constructor

  def construct( s ):

    # If translated into Verilog, we use the explicit name

    s.set_metadata( VerilogTranslationPass.explicit_module_name, 'IntMulNstageStepRTL' )

    #---------------------------------------------------------------------
    # Interface
    #---------------------------------------------------------------------

    s.in_val     = InPort  ()
    s.in_a       = InPort  (32)
    s.in_b       = InPort  (32)
    s.in_result  = InPort  (32)

    s.out_val    = OutPort ()
    s.out_a      = OutPort (32)
    s.out_b      = OutPort (32)
    s.out_result = OutPort (32)

    #---------------------------------------------------------------------
    # Logic
    #---------------------------------------------------------------------

    # TODO: Right shifter
    
    # TODO: Left shifter

    # TODO: Adder

    # TODO: Result mux

    # Connect the valid bits

    s.in_val //= s.out_val

  # Line tracing

  def line_trace( s ):
    return "{}|{}|{}(){}|{}|{}".format(
      s.in_a,  s.in_b,  s.in_result,
      s.out_a, s.out_b, s.out_result
    )

