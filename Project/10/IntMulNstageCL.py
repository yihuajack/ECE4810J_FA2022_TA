#=========================================================================
# Integer Multiplier N-Stage Pipelined CL Model
#=========================================================================
# Simple CL model for a pipelined integer multiplier with a variable
# number of stages.

from collections import deque

from pymtl3 import *
from pymtl3.stdlib import stream

from .IntMulMsgs import IntMulMsgs

class IntMulNstageCL( Component ):

  # Constructor

  def construct( s, nstages=2 ):

    # Interface

    s.recv = stream.ifcs.RecvIfcRTL(IntMulMsgs.req)
    s.send = stream.ifcs.SendIfcRTL(IntMulMsgs.resp)


    # ''' PROJECT TASK '''''''''''''''''''''''''''''''''''''''''''''''''''''''
    # Define Nstage cycle-level model.
    # ''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''\/

    # Queues

    s.req_q  = stream.RecvQueueAdapter(IntMulMsgs.req) # gives a deq method to call
    s.resp_q = stream.SendQueueAdapter(IntMulMsgs.resp) # gives a send method to call

    s.recv //= s.req_q.recv
    s.send //= s.resp_q.send

    # Member variables

    s.pipe = deque( [None]*(nstages-1) )

    @update_once
    def block():

      if s.resp_q.enq.rdy():

        if s.req_q.deq.rdy():
          msg = s.req_q.deq()
          s.pipe.append( msg.a * msg.b )
        else:
          s.pipe.append( None )

        result = s.pipe.popleft()
        if result is not None:
          s.resp_q.enq( result )

    # '''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''/\

  # Line tracing

  def line_trace( s ):

    s.trace = ""

    # ''' PROJECT TASK ''''''''''''''''''''''''''''''''''''''''''''''''''''''
    # Add line tracing code here.
    # '''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''\/

    s.trace = "{}({}){}".format(
      s.recv,
      ''.join([ ('*' if x is not None else ' ') for x in reversed(s.pipe) ]),
      s.send
    )

    # '''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''/\

    return s.trace
