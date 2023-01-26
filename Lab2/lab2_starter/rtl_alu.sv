`timescale 1ns/100ps

// RISCV ISA SPEC
`define XLEN 32

//
// ALU function code input
// probably want to leave these alone
//
typedef enum logic [4:0] {
	ALU_ADD     = 5'h00,
	ALU_SUB     = 5'h01,
	ALU_SLT     = 5'h02,
	ALU_SLTU    = 5'h03,
	ALU_AND     = 5'h04,
	ALU_OR      = 5'h05,
	ALU_XOR     = 5'h06,
	ALU_SLL     = 5'h07,
	ALU_SRL     = 5'h08,
	ALU_SRA     = 5'h09,
	ALU_MUL     = 5'h0a,
	ALU_MULH    = 5'h0b,
	ALU_MULHSU  = 5'h0c,
	ALU_MULHU   = 5'h0d,
	ALU_DIV     = 5'h0e,
	ALU_DIVU    = 5'h0f,
	ALU_REM     = 5'h10,
	ALU_REMU    = 5'h11
} ALU_FUNC;

//
// The ALU
//
// given the command code CMD and proper operands A and B, compute the
// result of the instruction
//
module rtl_alu(
    input clk,
	input [`XLEN-1:0] opa,
	input [`XLEN-1:0] opb,
	ALU_FUNC     func,

	output logic [`XLEN-1:0] result
);
	wire signed [`XLEN-1:0] signed_opa, signed_opb;
	wire signed [2*`XLEN-1:0] signed_mul, mixed_mul, signed_div, signed_rem;
	wire        [2*`XLEN-1:0] unsigned_mul, unsigned_div, unsigned_rem;
    // TODO: Complete ALU logic

endmodule // alu

`define PIPESTAGE 8
`define BIT_WIDTH 8

// This is an 8 stage (9 depending on how you look at it) pipelined 
// multiplier that multiplies 2 64-bit integers and returns the low 64 bits 
// of the result.  This is not an ideal multiplier but is sufficient to 
// allow a faster clock period than straight *
// This module instantiates 8 pipeline stages as an array of submodules.
module mult(
	input clock, reset,
	input [`XLEN:0] mcand, mplier,
	input start,

	output [2*`XLEN:0] product,
	output done
);
	logic [2*`XLEN:0] mcand_out, mplier_out;
	logic [((`PIPESTAGE-1)*2*`XLEN)-1:0] internal_products, internal_mcands, internal_mpliers;
	logic [`PIPESTAGE-2:0] internal_dones;
	// TODO: instantiation of mult_stage

endmodule

module mult_stage(
	input clock, reset, start,
	input [2*`XLEN-1:0] product_in, mplier_in, mcand_in,

	output logic done,
	output logic [2*`XLEN-1:0] product_out, mplier_out, mcand_out
);
	logic [2*`XLEN-1:0] prod_in_reg, partial_prod_reg;
	logic [2*`XLEN-1:0] partial_product, next_mplier, next_mcand;
	// TODO: combinational logics

	// synopsys sync_set_reset "reset"
	always_ff @(posedge clock) begin
		prod_in_reg      <= product_in;
		partial_prod_reg <= partial_product;
		mplier_out       <= next_mplier;
		mcand_out        <= next_mcand;
	end

	// synopsys sync_set_reset "reset"
	always_ff @(posedge clock) begin
		if(reset)
			done <= 1'b0;
		else
			done <= start;
	end
endmodule

module div(
	input clock, reset,
    input [`XLEN-1:0] dividend, divisor,
	input start,

    output [`XLEN-1:0] quotient, remainder,
    output done
);
    logic             dones     [`XLEN:0];
    logic [`XLEN-1:0] dividends [`XLEN:0];  
    logic [`XLEN-1:0] divisors  [`XLEN:0];
    logic [`XLEN-1:0] quotients [`XLEN:0];     

    always_comb begin
        dones[0]     = start;    
        dividends[0] = dividend;
        divisors[0]  = divisor;
        quotients[0] = 0;
    end
	// TODO

    assign quotient = quotients[`XLEN];
    assign remainder = dividends[`XLEN];
    assign done = dones[`XLEN];
endmodule
