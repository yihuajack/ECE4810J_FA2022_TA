#=========================================================================
# IntMulMsgs
#=========================================================================

from pymtl3 import *

# Hardcode to Bits32 for imul
@bitstruct
class IntMulReqMsg:
  a: Bits32
  b: Bits32

class IntMulMsgs:
  req = IntMulReqMsg
  resp = Bits32
