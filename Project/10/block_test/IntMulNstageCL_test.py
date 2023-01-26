#=========================================================================
# IntMulNstageCL_test
#=========================================================================

import pytest

from pymtl3 import *
from pymtl3.stdlib.test_utils import run_sim
from IntMulNstageCL import IntMulNstageCL

#-------------------------------------------------------------------------
# Reuse tests from fixed-lat CL model
#-------------------------------------------------------------------------

from .IntMulFixedLatCL_test import TestHarness, test_case_table

@pytest.mark.parametrize( **test_case_table )
def test_1stage( test_params ):

  th = TestHarness( IntMulNstageCL( nstages=1 ) )

  th.set_param("top.src.construct",
    msgs=test_params.msgs[::2],
    initial_delay=test_params.src_delay+3,
    interval_delay=test_params.src_delay )

  th.set_param("top.sink.construct",
    msgs=test_params.msgs[1::2],
    initial_delay=test_params.sink_delay+3,
    interval_delay=test_params.sink_delay )

  run_sim( th )

@pytest.mark.parametrize( **test_case_table )
def test_2stage( test_params ):

  th = TestHarness( IntMulNstageCL( nstages=2 ) )

  th.set_param("top.src.construct",
    msgs=test_params.msgs[::2],
    initial_delay=test_params.src_delay+3,
    interval_delay=test_params.src_delay )

  th.set_param("top.sink.construct",
    msgs=test_params.msgs[1::2],
    initial_delay=test_params.sink_delay+3,
    interval_delay=test_params.sink_delay )

  run_sim( th )

@pytest.mark.parametrize( **test_case_table )
def test_4stage( test_params ):

  th = TestHarness( IntMulNstageCL( nstages=4 ) )

  th.set_param("top.src.construct",
    msgs=test_params.msgs[::2],
    initial_delay=test_params.src_delay+3,
    interval_delay=test_params.src_delay )

  th.set_param("top.sink.construct",
    msgs=test_params.msgs[1::2],
    initial_delay=test_params.sink_delay+3,
    interval_delay=test_params.sink_delay )

  run_sim( th )

@pytest.mark.parametrize( **test_case_table )
def test_8stage( test_params ):

  th = TestHarness( IntMulNstageCL( nstages=8 ) )

  th.set_param("top.src.construct",
    msgs=test_params.msgs[::2],
    initial_delay=test_params.src_delay+3,
    interval_delay=test_params.src_delay )

  th.set_param("top.sink.construct",
    msgs=test_params.msgs[1::2],
    initial_delay=test_params.sink_delay+3,
    interval_delay=test_params.sink_delay )

  run_sim( th )
