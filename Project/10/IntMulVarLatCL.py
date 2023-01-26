#=========================================================================
# Integer Multiplier Variable-Lateny CL Model
# =========================================================================
# Simple CL model for a variable-latency iterative multiplier. We
# optimistically assume that the number of cycles is equal to the number
# of ones in the b operand.

from .IntMulFixedLatCL import IntMulFixedLatCL

class IntMulVarLatCL( IntMulFixedLatCL ):

  # Override, fixed latency
  def mul_latency( s, a, b ):
    return bin(int(b)).count('1')
