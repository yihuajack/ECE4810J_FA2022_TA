#=========================================================================
# Integer Multiplier N-Stage Pipelined RTL Model
#=========================================================================

from pymtl3 import *
from pymtl3.passes.backends.verilog import *
from pymtl3.stdlib import stream
from pymtl3.stdlib.basic_rtl import RegEnRst, RegEn

from .IntMulMsgs import IntMulMsgs

# ''' PROJECT TASK '''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
# Import your partial product step model here. Make sure you unit test it!
# ''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''\/

# ''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''/\

class IntMulNstagePRTL( Component ):

  # Constructor

  def construct( s, nstages=2 ):

    # If translated into Verilog, we use the explicit name

    s.set_metadata( VerilogTranslationPass.explicit_module_name, f'IntMulNstageRTL__nstages_{nstages}' )

    # Interface

    s.recv = stream.ifcs.RecvIfcRTL( IntMulMsgs.req )
    s.send = stream.ifcs.SendIfcRTL( IntMulMsgs.resp )

    # ''' PROJECT TASK '''''''''''''''''''''''''''''''''''''''''''''''''''''''
    # Instantiate the partial product steps here. Your design should be
    # parameterized by the number of pipeline stages given by the nstages
    # parameter.
    # ''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''\/

    # We currently only support power of two number of stages

    assert nstages in [1,2,4,8,16,32]
    nsteps = 32 / nstages

    # TODO: Input registers

    # Instantiate steps

    s.steps = [ IntMulNstageStepRTL() for _ in range(32) ]

    # TODO: Structural composition for first step

    # Pipeline registers

    s.val_preg    = [ RegEnRst(Bits1)  for _ in range(nstages-1) ]
    s.a_preg      = [ RegEn(Bits32) for _ in range(nstages-1) ]
    s.b_preg      = [ RegEn(Bits32) for _ in range(nstages-1) ]
    s.result_preg = [ RegEn(Bits32) for _ in range(nstages-1) ]

    # Structural composition for intermediate steps

    nstage = 0
    for i in range(1,32):

      # TODO: Insert a pipeline register

      if i % nsteps == 0:

        #  print "-- pipe reg --"
        #  print "step = {}".format(i)

        nstage += 1

      # TODO: No pipeline register

      else:

        #  print "step = {}".format(i)

    # Structural composition for last step

    s.send.val //= s.steps[31].out_val
    s.send.msg //= lambda: s.steps[31].out_result & (sext(s.send.val, 32)) # 4-state sim fix

    # Wire resp rdy to req rdy

    s.recv.rdy //= s.send.rdy

    # ''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''/\

  # Line tracing

  def line_trace( s ):

    s.trace = ""

    # ''' PROJECT TASK '''''''''''''''''''''''''''''''''''''''''''''''''''''''
    # Add line tracing code here.
    # ''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''\/

    # ''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''/\

    return s.trace

