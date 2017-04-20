//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: deadreckoning.cpp
//
// Code generated for Simulink model 'deadreckoning'.
//
// Model version                  : 1.129
// Simulink Coder version         : 8.10 (R2016a) 10-Feb-2016
// C/C++ source code generated on : Thu Apr 20 15:03:55 2017
//
// Target selection: ert.tlc
// Embedded hardware selection: Generic->Unspecified (assume 32-bit Generic)
// Code generation objectives: Unspecified
// Validation result: Not run
//
#include "deadreckoning.h"
#include "deadreckoning_private.h"
#define deadreckoning_MessageQueueLen  (1)

// Block signals (auto storage)
B_deadreckoning_T deadreckoning_B;

// Continuous states
X_deadreckoning_T deadreckoning_X;

// Periodic continuous states
PeriodicIndX_deadreckoning_T deadreckoning_PeriodicIndX;
PeriodicRngX_deadreckoning_T deadreckoning_PeriodicRngX;

// Block states (auto storage)
DW_deadreckoning_T deadreckoning_DW;

// Real-time model
RT_MODEL_deadreckoning_T deadreckoning_M_;
RT_MODEL_deadreckoning_T *const deadreckoning_M = &deadreckoning_M_;

// State reduction function
void local_stateReduction(real_T* x, int_T* p, int_T n, real_T* r)
{
  int_T i, j;
  for (i = 0, j = 0; i < n; ++i, ++j) {
    int_T k = p[i];
    real_T lb = r[j++];
    real_T xk = x[k]-lb;
    real_T rk = r[j]-lb;
    int_T q = (int_T) floor(xk/rk);
    if (q) {
      x[k] = xk-q*rk+lb;
    }
  }
}

//
// This function updates continuous states using the ODE3 fixed-step
// solver algorithm
//
static void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
{
  // Solver Matrices
  static const real_T rt_ODE3_A[3] = {
    1.0/2.0, 3.0/4.0, 1.0
  };

  static const real_T rt_ODE3_B[3][3] = {
    { 1.0/2.0, 0.0, 0.0 },

    { 0.0, 3.0/4.0, 0.0 },

    { 2.0/9.0, 1.0/3.0, 4.0/9.0 }
  };

  time_T t = rtsiGetT(si);
  time_T tnew = rtsiGetSolverStopTime(si);
  time_T h = rtsiGetStepSize(si);
  real_T *x = rtsiGetContStates(si);
  ODE3_IntgData *id = (ODE3_IntgData *)rtsiGetSolverData(si);
  real_T *y = id->y;
  real_T *f0 = id->f[0];
  real_T *f1 = id->f[1];
  real_T *f2 = id->f[2];
  real_T hB[3];
  int_T i;
  int_T nXc = 3;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);

  // Save the state values at time t in y, we'll use x as ynew.
  (void) memcpy(y, x,
                (uint_T)nXc*sizeof(real_T));

  // Assumes that rtsiSetT and ModelOutputs are up-to-date
  // f0 = f(t,y)
  rtsiSetdX(si, f0);
  deadreckoning_derivatives();

  // f(:,2) = feval(odefile, t + hA(1), y + f*hB(:,1), args(:)(*));
  hB[0] = h * rt_ODE3_B[0][0];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[0]);
  rtsiSetdX(si, f1);
  deadreckoning_step();
  deadreckoning_derivatives();

  // f(:,3) = feval(odefile, t + hA(2), y + f*hB(:,2), args(:)(*));
  for (i = 0; i <= 1; i++) {
    hB[i] = h * rt_ODE3_B[1][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[1]);
  rtsiSetdX(si, f2);
  deadreckoning_step();
  deadreckoning_derivatives();

  // tnew = t + hA(3);
  // ynew = y + f*hB(:,3);
  for (i = 0; i <= 2; i++) {
    hB[i] = h * rt_ODE3_B[2][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1] + f2[i]*hB[2]);
  }

  rtsiSetT(si, tnew);
  local_stateReduction(x, rtsiGetPeriodicContStateIndices(si), 1,
                       rtsiGetPeriodicContStateRanges(si));
  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

// Model step function
void deadreckoning_step(void)
{
  // local block i/o variables
  uint32_T rtb_FixPtSwitch;
  static const uint8_T b[15] = { 99U, 97U, 116U, 118U, 101U, 104U, 105U, 99U,
    108U, 101U, 47U, 111U, 100U, 111U, 109U };

  static const uint8_T c[20] = { 99U, 97U, 116U, 118U, 101U, 104U, 105U, 99U,
    108U, 101U, 47U, 98U, 97U, 115U, 101U, 95U, 108U, 105U, 110U, 107U };

  boolean_T varargout_1;
  real_T rtb_Fromsteeringpercenttosteeri;
  uint32_T rtb_FixPtSum1;
  int32_T i;
  real_T rtb_sincos_o1_idx_0;
  real_T rtb_sincos_o1_idx_1;
  real_T rtb_sincos_o1_idx_2;
  real_T rtb_sincos_o2_idx_0;
  real_T rtb_sincos_o2_idx_1;
  if (rtmIsMajorTimeStep(deadreckoning_M)) {
    // set solver stop time
    if (!(deadreckoning_M->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&deadreckoning_M->solverInfo,
                            ((deadreckoning_M->Timing.clockTickH0 + 1) *
        deadreckoning_M->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&deadreckoning_M->solverInfo,
                            ((deadreckoning_M->Timing.clockTick0 + 1) *
        deadreckoning_M->Timing.stepSize0 + deadreckoning_M->Timing.clockTickH0 *
        deadreckoning_M->Timing.stepSize0 * 4294967296.0));
    }
  }                                    // end MajorTimeStep

  // Update absolute time of base rate at minor time step
  if (rtmIsMinorTimeStep(deadreckoning_M)) {
    deadreckoning_M->Timing.t[0] = rtsiGetT(&deadreckoning_M->solverInfo);
  }

  // Gain: '<S4>/1//2' incorporates:
  //   Constant: '<Root>/Constant1'
  //   Constant: '<Root>/Constant2'
  //   Integrator: '<Root>/Integrator2'

  rtb_sincos_o1_idx_0 = deadreckoning_P.u2_Gain *
    deadreckoning_X.Integrator2_CSTATE;
  rtb_sincos_o1_idx_1 = deadreckoning_P.u2_Gain *
    deadreckoning_P.Constant1_Value;
  rtb_sincos_o1_idx_2 = deadreckoning_P.u2_Gain *
    deadreckoning_P.Constant2_Value;

  // Trigonometry: '<S4>/sincos'
  rtb_sincos_o2_idx_0 = cos(rtb_sincos_o1_idx_0);
  rtb_sincos_o1_idx_0 = sin(rtb_sincos_o1_idx_0);
  rtb_sincos_o2_idx_1 = cos(rtb_sincos_o1_idx_1);
  rtb_sincos_o1_idx_1 = sin(rtb_sincos_o1_idx_1);
  rtb_Fromsteeringpercenttosteeri = cos(rtb_sincos_o1_idx_2);
  rtb_sincos_o1_idx_2 = sin(rtb_sincos_o1_idx_2);
  if (rtmIsMajorTimeStep(deadreckoning_M)) {
    // MATLAB Function: '<Root>/odometry_header' incorporates:
    //   Constant: '<S1>/Constant'

    //  set our output to be a copy of the input (blankMsg)
    // MATLAB Function 'odometry_header': '<S9>:1'
    // '<S9>:1:5' outputMsg = blankMsg;
    deadreckoning_B.outputMsg = deadreckoning_P.Constant_Value;

    //  set the frame to be relative to our base of 0. If you want to use data
    //  coming from another detection, then you can set the /detections to be in 
    //  the frame of that specific sensor
    // '<S9>:1:10' str = 'catvehicle/odom';
    // '<S9>:1:11' strLength = length(str);
    //  initialize the header and set its values
    // '<S9>:1:13' outputMsg.Header.FrameId(1:strLength) = str;
    for (i = 0; i < 15; i++) {
      deadreckoning_B.outputMsg.Header.FrameId[i] = b[i];
    }

    // '<S9>:1:14' outputMsg.Header.FrameId_SL_Info.CurrentLength = uint32(strLength); 
    deadreckoning_B.outputMsg.Header.FrameId_SL_Info.CurrentLength = 15U;

    // '<S9>:1:15' strChild = 'catvehicle/base_link';
    // '<S9>:1:16' strChildLength = length(strChild);
    //  initialize the header and set its values
    // '<S9>:1:18' outputMsg.ChildFrameId(1:strChildLength) = strChild;
    for (i = 0; i < 20; i++) {
      deadreckoning_B.outputMsg.ChildFrameId[i] = c[i];
    }

    // '<S9>:1:19' outputMsg.ChildFrameId_SL_Info.CurrentLength = uint32(strChildLength); 
    deadreckoning_B.outputMsg.ChildFrameId_SL_Info.CurrentLength = 20U;

    // End of MATLAB Function: '<Root>/odometry_header'

    // Outputs for Atomic SubSystem: '<Root>/Subscribe4'
    // Start for MATLABSystem: '<S8>/SourceBlock' incorporates:
    //   Inport: '<S15>/In1'
    //   MATLABSystem: '<S8>/SourceBlock'

    varargout_1 = Sub_deadreckoning_127.getLatestMessage
      (&deadreckoning_B.varargout_2_c);

    // Outputs for Enabled SubSystem: '<S8>/Enabled Subsystem' incorporates:
    //   EnablePort: '<S15>/Enable'

    if (varargout_1) {
      deadreckoning_B.In1_h = deadreckoning_B.varargout_2_c;
    }

    // End of Start for MATLABSystem: '<S8>/SourceBlock'
    // End of Outputs for SubSystem: '<S8>/Enabled Subsystem'
    // End of Outputs for SubSystem: '<Root>/Subscribe4'

    // UnitDelay: '<S2>/Output'
    deadreckoning_B.Output = deadreckoning_DW.Output_DSTATE;
  }

  // BusAssignment: '<Root>/Bus Assignment' incorporates:
  //   Constant: '<Root>/Altitude'
  //   Fcn: '<S4>/q0'
  //   Fcn: '<S4>/q1'
  //   Fcn: '<S4>/q2'
  //   Fcn: '<S4>/q3'
  //   Integrator: '<Root>/Integrator'
  //   Integrator: '<Root>/Integrator1'
  //   Trigonometry: '<S4>/sincos'

  deadreckoning_B.BusAssignment = deadreckoning_B.outputMsg;
  deadreckoning_B.BusAssignment.Pose.Pose.Position.X =
    deadreckoning_X.Integrator_CSTATE;
  deadreckoning_B.BusAssignment.Pose.Pose.Position.Y =
    deadreckoning_X.Integrator1_CSTATE;
  deadreckoning_B.BusAssignment.Pose.Pose.Position.Z =
    deadreckoning_P.Altitude_Value;
  deadreckoning_B.BusAssignment.Pose.Pose.Orientation.X = rtb_sincos_o2_idx_0 *
    rtb_sincos_o2_idx_1 * rtb_sincos_o1_idx_2 - rtb_sincos_o1_idx_0 *
    rtb_sincos_o1_idx_1 * rtb_Fromsteeringpercenttosteeri;
  deadreckoning_B.BusAssignment.Pose.Pose.Orientation.Y = rtb_sincos_o2_idx_0 *
    rtb_sincos_o1_idx_1 * rtb_Fromsteeringpercenttosteeri + rtb_sincos_o1_idx_0 *
    rtb_sincos_o2_idx_1 * rtb_sincos_o1_idx_2;
  deadreckoning_B.BusAssignment.Pose.Pose.Orientation.Z = rtb_sincos_o1_idx_0 *
    rtb_sincos_o2_idx_1 * rtb_Fromsteeringpercenttosteeri - rtb_sincos_o2_idx_0 *
    rtb_sincos_o1_idx_1 * rtb_sincos_o1_idx_2;
  deadreckoning_B.BusAssignment.Pose.Pose.Orientation.W = rtb_sincos_o2_idx_0 *
    rtb_sincos_o2_idx_1 * rtb_Fromsteeringpercenttosteeri + rtb_sincos_o1_idx_0 *
    rtb_sincos_o1_idx_1 * rtb_sincos_o1_idx_2;
  deadreckoning_B.BusAssignment.Header.Stamp = deadreckoning_B.In1_h.Clock_;
  deadreckoning_B.BusAssignment.Header.Seq = deadreckoning_B.Output;

  // Outputs for Atomic SubSystem: '<Root>/Publish'
  // Start for MATLABSystem: '<S3>/SinkBlock' incorporates:
  //   MATLABSystem: '<S3>/SinkBlock'

  Pub_deadreckoning_79.publish(&deadreckoning_B.BusAssignment);

  // End of Outputs for SubSystem: '<Root>/Publish'
  if (rtmIsMajorTimeStep(deadreckoning_M)) {
    // Sum: '<S10>/FixPt Sum1' incorporates:
    //   Constant: '<S10>/FixPt Constant'

    rtb_FixPtSum1 = deadreckoning_B.Output + deadreckoning_P.FixPtConstant_Value;

    // Switch: '<S11>/FixPt Switch' incorporates:
    //   Constant: '<S11>/Constant'

    if (rtb_FixPtSum1 > deadreckoning_P.WrapToZero_Threshold) {
      rtb_FixPtSwitch = deadreckoning_P.Constant_Value_m;
    } else {
      rtb_FixPtSwitch = rtb_FixPtSum1;
    }

    // End of Switch: '<S11>/FixPt Switch'

    // Outputs for Atomic SubSystem: '<Root>/Subscribe3'
    // Start for MATLABSystem: '<S7>/SourceBlock' incorporates:
    //   Inport: '<S14>/In1'
    //   MATLABSystem: '<S7>/SourceBlock'

    varargout_1 = Sub_deadreckoning_121.getLatestMessage
      (&deadreckoning_B.varargout_2_m);

    // Outputs for Enabled SubSystem: '<S7>/Enabled Subsystem' incorporates:
    //   EnablePort: '<S14>/Enable'

    if (varargout_1) {
      deadreckoning_B.In1_c = deadreckoning_B.varargout_2_m;
    }

    // End of Start for MATLABSystem: '<S7>/SourceBlock'
    // End of Outputs for SubSystem: '<S7>/Enabled Subsystem'
    // End of Outputs for SubSystem: '<Root>/Subscribe3'

    // Outputs for Atomic SubSystem: '<Root>/Subscribe'
    // Start for MATLABSystem: '<S5>/SourceBlock' incorporates:
    //   Inport: '<S12>/In1'
    //   MATLABSystem: '<S5>/SourceBlock'

    varargout_1 = Sub_deadreckoning_1.getLatestMessage
      (&deadreckoning_B.varargout_2);

    // Outputs for Enabled SubSystem: '<S5>/Enabled Subsystem' incorporates:
    //   EnablePort: '<S12>/Enable'

    if (varargout_1) {
      deadreckoning_B.In1 = deadreckoning_B.varargout_2;
    }

    // End of Start for MATLABSystem: '<S5>/SourceBlock'
    // End of Outputs for SubSystem: '<S5>/Enabled Subsystem'
    // End of Outputs for SubSystem: '<Root>/Subscribe'

    // Fcn: '<Root>/thetadot = vel*sin(steering)*(1//L)' incorporates:
    //   Constant: '<Root>/Constant'
    //   Fcn: '<Root>/From steering percent to steering angle'

    deadreckoning_B.thetadotvelsinsteering1L = sin
      (-deadreckoning_B.In1_c.Torque.Z * deadreckoning_P.Constant_Value_h /
       100.0) * deadreckoning_B.In1.Linear.X / 2.62;
  }

  // Fcn: '<Root>/xdot = vel * cos (heading) ' incorporates:
  //   Integrator: '<Root>/Integrator2'

  deadreckoning_B.xdotvelcosheading = deadreckoning_B.In1.Linear.X * cos
    (deadreckoning_X.Integrator2_CSTATE);

  // Fcn: '<Root>/ydot = vel * sin (heading)' incorporates:
  //   Integrator: '<Root>/Integrator2'

  deadreckoning_B.ydotvelsinheading = deadreckoning_B.In1.Linear.X * sin
    (deadreckoning_X.Integrator2_CSTATE);
  if (rtmIsMajorTimeStep(deadreckoning_M)) {
    if (rtmIsMajorTimeStep(deadreckoning_M)) {
      // Update for UnitDelay: '<S2>/Output'
      deadreckoning_DW.Output_DSTATE = rtb_FixPtSwitch;
    }
  }                                    // end MajorTimeStep

  if (rtmIsMajorTimeStep(deadreckoning_M)) {
    rt_ertODEUpdateContinuousStates(&deadreckoning_M->solverInfo);

    // Update absolute time for base rate
    // The "clockTick0" counts the number of times the code of this task has
    //  been executed. The absolute time is the multiplication of "clockTick0"
    //  and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
    //  overflow during the application lifespan selected.
    //  Timer of this task consists of two 32 bit unsigned integers.
    //  The two integers represent the low bits Timing.clockTick0 and the high bits
    //  Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.

    if (!(++deadreckoning_M->Timing.clockTick0)) {
      ++deadreckoning_M->Timing.clockTickH0;
    }

    deadreckoning_M->Timing.t[0] = rtsiGetSolverStopTime
      (&deadreckoning_M->solverInfo);

    {
      // Update absolute timer for sample time: [0.05s, 0.0s]
      // The "clockTick1" counts the number of times the code of this task has
      //  been executed. The resolution of this integer timer is 0.05, which is the step size
      //  of the task. Size of "clockTick1" ensures timer will not overflow during the
      //  application lifespan selected.
      //  Timer of this task consists of two 32 bit unsigned integers.
      //  The two integers represent the low bits Timing.clockTick1 and the high bits
      //  Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.

      deadreckoning_M->Timing.clockTick1++;
      if (!deadreckoning_M->Timing.clockTick1) {
        deadreckoning_M->Timing.clockTickH1++;
      }
    }
  }                                    // end MajorTimeStep
}

// Derivatives for root system: '<Root>'
void deadreckoning_derivatives(void)
{
  XDot_deadreckoning_T *_rtXdot;
  _rtXdot = ((XDot_deadreckoning_T *) deadreckoning_M->ModelData.derivs);

  // Derivatives for Integrator: '<Root>/Integrator'
  _rtXdot->Integrator_CSTATE = deadreckoning_B.xdotvelcosheading;

  // Derivatives for Integrator: '<Root>/Integrator1'
  _rtXdot->Integrator1_CSTATE = deadreckoning_B.ydotvelsinheading;

  // Derivatives for Integrator: '<Root>/Integrator2'
  _rtXdot->Integrator2_CSTATE = deadreckoning_B.thetadotvelsinsteering1L;
}

// Model initialize function
void deadreckoning_initialize(void)
{
  // Registration code

  // initialize real-time model
  (void) memset((void *)deadreckoning_M, 0,
                sizeof(RT_MODEL_deadreckoning_T));

  {
    // Setup solver object
    rtsiSetSimTimeStepPtr(&deadreckoning_M->solverInfo,
                          &deadreckoning_M->Timing.simTimeStep);
    rtsiSetTPtr(&deadreckoning_M->solverInfo, &rtmGetTPtr(deadreckoning_M));
    rtsiSetStepSizePtr(&deadreckoning_M->solverInfo,
                       &deadreckoning_M->Timing.stepSize0);
    rtsiSetdXPtr(&deadreckoning_M->solverInfo,
                 &deadreckoning_M->ModelData.derivs);
    rtsiSetContStatesPtr(&deadreckoning_M->solverInfo, (real_T **)
                         &deadreckoning_M->ModelData.contStates);
    rtsiSetNumContStatesPtr(&deadreckoning_M->solverInfo,
      &deadreckoning_M->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&deadreckoning_M->solverInfo,
      &deadreckoning_M->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&deadreckoning_M->solverInfo,
      &deadreckoning_M->ModelData.periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&deadreckoning_M->solverInfo,
      &deadreckoning_M->ModelData.periodicContStateRanges);
    rtsiSetErrorStatusPtr(&deadreckoning_M->solverInfo, (&rtmGetErrorStatus
      (deadreckoning_M)));
    rtsiSetRTModelPtr(&deadreckoning_M->solverInfo, deadreckoning_M);
  }

  rtsiSetSimTimeStep(&deadreckoning_M->solverInfo, MAJOR_TIME_STEP);
  deadreckoning_M->ModelData.intgData.y = deadreckoning_M->ModelData.odeY;
  deadreckoning_M->ModelData.intgData.f[0] = deadreckoning_M->ModelData.odeF[0];
  deadreckoning_M->ModelData.intgData.f[1] = deadreckoning_M->ModelData.odeF[1];
  deadreckoning_M->ModelData.intgData.f[2] = deadreckoning_M->ModelData.odeF[2];
  deadreckoning_M->ModelData.contStates = ((X_deadreckoning_T *)
    &deadreckoning_X);
  deadreckoning_M->ModelData.periodicContStateIndices = ((int_T*)
    deadreckoning_PeriodicIndX);
  deadreckoning_M->ModelData.periodicContStateRanges = ((real_T*)
    deadreckoning_PeriodicRngX);
  rtsiSetSolverData(&deadreckoning_M->solverInfo, (void *)
                    &deadreckoning_M->ModelData.intgData);
  rtsiSetSolverName(&deadreckoning_M->solverInfo,"ode3");
  rtmSetTPtr(deadreckoning_M, &deadreckoning_M->Timing.tArray[0]);
  deadreckoning_M->Timing.stepSize0 = 0.05;

  // block I/O
  (void) memset(((void *) &deadreckoning_B), 0,
                sizeof(B_deadreckoning_T));

  // states (continuous)
  {
    (void) memset((void *)&deadreckoning_X, 0,
                  sizeof(X_deadreckoning_T));
  }

  // Periodic continuous states
  {
    (void) memset((void*) deadreckoning_PeriodicIndX, 0,
                  1*sizeof(int_T));
    (void) memset((void*) deadreckoning_PeriodicRngX, 0,
                  2*sizeof(real_T));
  }

  // states (dwork)
  (void) memset((void *)&deadreckoning_DW, 0,
                sizeof(DW_deadreckoning_T));

  {
    static const char_T tmp[15] = { '/', 'c', 'a', 't', 'v', 'e', 'h', 'i', 'c',
      'l', 'e', '/', 'v', 'e', 'l' };

    static const char_T tmp_0[20] = { '/', 'c', 'a', 't', 'v', 'e', 'h', 'i',
      'c', 'l', 'e', '/', 's', 't', 'e', 'e', 'r', 'i', 'n', 'g' };

    static const char_T tmp_1[30] = { '/', 'c', 'a', 't', 'v', 'e', 'h', 'i',
      'c', 'l', 'e', '/', 'o', 'd', 'o', 'm', '_', 'd', 'e', 'a', 'd', 'r', 'e',
      'c', 'k', 'o', 'n', 'i', 'n', 'g' };

    static const char_T tmp_2[6] = { '/', 'c', 'l', 'o', 'c', 'k' };

    char_T tmp_3[16];
    char_T tmp_4[21];
    char_T tmp_5[7];
    int32_T i;

    // Start for Atomic SubSystem: '<Root>/Subscribe4'
    // Start for MATLABSystem: '<S8>/SourceBlock'
    deadreckoning_DW.obj_o.isInitialized = 0;
    deadreckoning_DW.obj_o.isInitialized = 1;
    for (i = 0; i < 6; i++) {
      tmp_5[i] = tmp_2[i];
    }

    tmp_5[6] = '\x00';
    Sub_deadreckoning_127.createSubscriber(tmp_5, deadreckoning_MessageQueueLen);

    // End of Start for MATLABSystem: '<S8>/SourceBlock'
    // End of Start for SubSystem: '<Root>/Subscribe4'

    // Start for Atomic SubSystem: '<Root>/Publish'
    // Start for MATLABSystem: '<S3>/SinkBlock'
    deadreckoning_DW.obj.isInitialized = 0;
    deadreckoning_DW.obj.isInitialized = 1;
    for (i = 0; i < 30; i++) {
      deadreckoning_B.cv0[i] = tmp_1[i];
    }

    deadreckoning_B.cv0[30] = '\x00';
    Pub_deadreckoning_79.createPublisher(deadreckoning_B.cv0,
      deadreckoning_MessageQueueLen);

    // End of Start for MATLABSystem: '<S3>/SinkBlock'
    // End of Start for SubSystem: '<Root>/Publish'

    // Start for Atomic SubSystem: '<Root>/Subscribe3'
    // Start for MATLABSystem: '<S7>/SourceBlock'
    deadreckoning_DW.obj_n.isInitialized = 0;
    deadreckoning_DW.obj_n.isInitialized = 1;
    for (i = 0; i < 20; i++) {
      tmp_4[i] = tmp_0[i];
    }

    tmp_4[20] = '\x00';
    Sub_deadreckoning_121.createSubscriber(tmp_4, deadreckoning_MessageQueueLen);

    // End of Start for MATLABSystem: '<S7>/SourceBlock'
    // End of Start for SubSystem: '<Root>/Subscribe3'

    // Start for Atomic SubSystem: '<Root>/Subscribe'
    // Start for MATLABSystem: '<S5>/SourceBlock'
    deadreckoning_DW.obj_nf.isInitialized = 0;
    deadreckoning_DW.obj_nf.isInitialized = 1;
    for (i = 0; i < 15; i++) {
      tmp_3[i] = tmp[i];
    }

    tmp_3[15] = '\x00';
    Sub_deadreckoning_1.createSubscriber(tmp_3, deadreckoning_MessageQueueLen);

    // End of Start for MATLABSystem: '<S5>/SourceBlock'
    // End of Start for SubSystem: '<Root>/Subscribe'

    // InitializeConditions for Integrator: '<Root>/Integrator'
    deadreckoning_X.Integrator_CSTATE = deadreckoning_P.Integrator_IC;

    // InitializeConditions for Integrator: '<Root>/Integrator1'
    deadreckoning_X.Integrator1_CSTATE = deadreckoning_P.Integrator1_IC;

    // InitializeConditions for Integrator: '<Root>/Integrator2'
    deadreckoning_X.Integrator2_CSTATE = deadreckoning_P.Integrator2_IC;

    // InitializeConditions for UnitDelay: '<S2>/Output'
    deadreckoning_DW.Output_DSTATE = deadreckoning_P.Output_InitialCondition;

    // SystemInitialize for Atomic SubSystem: '<Root>/Subscribe4'
    // SystemInitialize for Enabled SubSystem: '<S8>/Enabled Subsystem'
    // SystemInitialize for Outport: '<S15>/Out1'
    deadreckoning_B.In1_h = deadreckoning_P.Out1_Y0_a;

    // End of SystemInitialize for SubSystem: '<S8>/Enabled Subsystem'
    // End of SystemInitialize for SubSystem: '<Root>/Subscribe4'

    // SystemInitialize for Atomic SubSystem: '<Root>/Subscribe3'
    // SystemInitialize for Enabled SubSystem: '<S7>/Enabled Subsystem'
    // SystemInitialize for Outport: '<S14>/Out1'
    deadreckoning_B.In1_c = deadreckoning_P.Out1_Y0_d;

    // End of SystemInitialize for SubSystem: '<S7>/Enabled Subsystem'
    // End of SystemInitialize for SubSystem: '<Root>/Subscribe3'

    // SystemInitialize for Atomic SubSystem: '<Root>/Subscribe'
    // SystemInitialize for Enabled SubSystem: '<S5>/Enabled Subsystem'
    // SystemInitialize for Outport: '<S12>/Out1'
    deadreckoning_B.In1 = deadreckoning_P.Out1_Y0;

    // End of SystemInitialize for SubSystem: '<S5>/Enabled Subsystem'
    // End of SystemInitialize for SubSystem: '<Root>/Subscribe'

    // InitializeConditions for root-level periodic continuous states
    {
      int_T rootPeriodicContStateIndices[1] = { 2 };

      real_T rootPeriodicContStateRanges[2] = { -3.1415926535897931,
        3.1415926535897931 };

      (void) memcpy((void*) deadreckoning_PeriodicIndX,
                    rootPeriodicContStateIndices,
                    1*sizeof(int_T));
      (void) memcpy((void*) deadreckoning_PeriodicRngX,
                    rootPeriodicContStateRanges,
                    2*sizeof(real_T));
    }
  }
}

// Model terminate function
void deadreckoning_terminate(void)
{
  // Terminate for Atomic SubSystem: '<Root>/Subscribe4'
  // Start for MATLABSystem: '<S8>/SourceBlock' incorporates:
  //   Terminate for MATLABSystem: '<S8>/SourceBlock'

  if (deadreckoning_DW.obj_o.isInitialized == 1) {
    deadreckoning_DW.obj_o.isInitialized = 2;
  }

  // End of Start for MATLABSystem: '<S8>/SourceBlock'
  // End of Terminate for SubSystem: '<Root>/Subscribe4'

  // Terminate for Atomic SubSystem: '<Root>/Publish'
  // Start for MATLABSystem: '<S3>/SinkBlock' incorporates:
  //   Terminate for MATLABSystem: '<S3>/SinkBlock'

  if (deadreckoning_DW.obj.isInitialized == 1) {
    deadreckoning_DW.obj.isInitialized = 2;
  }

  // End of Start for MATLABSystem: '<S3>/SinkBlock'
  // End of Terminate for SubSystem: '<Root>/Publish'

  // Terminate for Atomic SubSystem: '<Root>/Subscribe3'
  // Start for MATLABSystem: '<S7>/SourceBlock' incorporates:
  //   Terminate for MATLABSystem: '<S7>/SourceBlock'

  if (deadreckoning_DW.obj_n.isInitialized == 1) {
    deadreckoning_DW.obj_n.isInitialized = 2;
  }

  // End of Start for MATLABSystem: '<S7>/SourceBlock'
  // End of Terminate for SubSystem: '<Root>/Subscribe3'

  // Terminate for Atomic SubSystem: '<Root>/Subscribe'
  // Start for MATLABSystem: '<S5>/SourceBlock' incorporates:
  //   Terminate for MATLABSystem: '<S5>/SourceBlock'

  if (deadreckoning_DW.obj_nf.isInitialized == 1) {
    deadreckoning_DW.obj_nf.isInitialized = 2;
  }

  // End of Start for MATLABSystem: '<S5>/SourceBlock'
  // End of Terminate for SubSystem: '<Root>/Subscribe'
}

//
// File trailer for generated code.
//
// [EOF]
//
