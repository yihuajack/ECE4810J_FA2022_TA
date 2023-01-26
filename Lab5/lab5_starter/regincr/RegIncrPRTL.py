#=========================================================================
# RegIncrPRTL
#=========================================================================
# This is a simple model for a registered incrementer. An eight-bit value
# is read from the input port, registered, incremented by one, and
# finally written to the output port.

from pymtl3 import *
from pymtl3.passes.backends.verilog import *

class RegIncrPRTL( Component ):

  # Constructor

  def construct( s ):

    # If translated into Verilog, we use the explicit name

    s.set_metadata( VerilogTranslationPass.explicit_module_name,
                    'RegIncrRTL' )

    # Port-based interface

    s.in_ = InPort  ( Bits8 )
    s.out = OutPort ( Bits8 )

    # Sequential logic

    s.reg_out = Wire( 8 )

    @update_ff
    def block1():
      if s.reset:
        s.reg_out <<= 0
      else:
        s.reg_out <<= s.in_

    # ''' SECTION TASK '''''''''''''''''''''''''''''''''''''''''''''''''''
    # This model is incomplete. Uncomment the combinational concurrent
    # block and connection statement to model the incrementer logic.
    # ''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''


  def line_trace( s ):
    return f"{s.in_} ({s.reg_out}) {s.out}"

