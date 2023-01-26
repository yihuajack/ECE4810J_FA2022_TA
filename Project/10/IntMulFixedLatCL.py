#=========================================================================
# Integer Multiplier Fixed-Lateny CL Model
#=========================================================================
# Simple CL model for a fixed-latency iterative multiplier which is
# assumed to take 32 cycles.

from pymtl3 import *
from pymtl3.stdlib import stream

from .IntMulMsgs import IntMulMsgs

class IntMulFixedLatCL( Component ):

  def mul_latency( s, a, b ):
    return 32

  # Constructor

  def construct( s ):

    # Interface

    s.recv = stream.ifcs.RecvIfcRTL(IntMulMsgs.req)
    s.send = stream.ifcs.SendIfcRTL(IntMulMsgs.resp)

    # Queues

    s.req_q  = stream.RecvQueueAdapter(IntMulMsgs.req) # gives a deq method to call
    s.resp_q = stream.SendQueueAdapter(IntMulMsgs.resp) # gives a send method to call

    s.recv //= s.req_q.recv
    s.send //= s.resp_q.send

    # Member variables

    s.result   = None
    s.counter  = 0

    # Update block

    @update_once
    def block():

      if s.result is not None:
        if s.counter > 0:
          s.counter -= 1
        elif s.resp_q.enq.rdy():
          s.resp_q.enq( s.result )
          s.result = None

      elif s.req_q.deq.rdy():
        msg = s.req_q.deq()
        s.result = msg.a * msg.b
        s.counter = s.mul_latency( msg.a, msg.b )

  # Line tracing

  def line_trace( s ):
    return f"({s.counter:2})"
