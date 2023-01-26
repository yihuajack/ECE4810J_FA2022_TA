//========================================================================
// Integer Multiplier Nstage shift and add step
//========================================================================

`ifndef IMUL_INT_MUL_NSTAGE_STEP_V
`define IMUL_INT_MUL_NSTAGE_STEP_V

`include "vc/muxes.v"
`include "vc/regs.v"
`include "vc/arithmetic.v"

//========================================================================
// Integer Multiplier Nstage Step
//========================================================================

module imul_IntMulNstageStepVRTL
(
  input  logic        in_val,
  input  logic [31:0] in_a,
  input  logic [31:0] in_b,
  input  logic [31:0] in_result,

  output logic        out_val,
  output logic [31:0] out_a,
  output logic [31:0] out_b,
  output logic [31:0] out_result
);

  // TODO: Right shifter

  // TODO: Left shifter

  // TODO: Adder

  logic [31:0] add_out;

  // TODO: Result mux

  // Connect the enid bits

  assign out_val = in_val;

endmodule

`endif /* IMUL_INT_MUL_NSTAGE_STEP_V */

