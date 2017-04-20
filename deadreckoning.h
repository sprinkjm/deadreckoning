//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: deadreckoning.h
//
// Code generated for Simulink model 'deadreckoning'.
//
// Model version                  : 1.131
// Simulink Coder version         : 8.10 (R2016a) 10-Feb-2016
// C/C++ source code generated on : Thu Apr 20 15:33:18 2017
//
// Target selection: ert.tlc
// Embedded hardware selection: Generic->Unspecified (assume 32-bit Generic)
// Code generation objectives: Unspecified
// Validation result: Not run
//
#ifndef RTW_HEADER_deadreckoning_h_
#define RTW_HEADER_deadreckoning_h_
#include <string.h>
#include <math.h>
#include <stddef.h>
#ifndef deadreckoning_COMMON_INCLUDES_
# define deadreckoning_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#include "slros_initialize.h"
#endif                                 // deadreckoning_COMMON_INCLUDES_

#include "deadreckoning_types.h"

// Macros for accessing real-time model data structure
#ifndef rtmGetBlkStateChangeFlag
# define rtmGetBlkStateChangeFlag(rtm) ((rtm)->ModelData.blkStateChange)
#endif

#ifndef rtmSetBlkStateChangeFlag
# define rtmSetBlkStateChangeFlag(rtm, val) ((rtm)->ModelData.blkStateChange = (val))
#endif

#ifndef rtmGetContStateDisabled
# define rtmGetContStateDisabled(rtm)  ((rtm)->ModelData.contStateDisabled)
#endif

#ifndef rtmSetContStateDisabled
# define rtmSetContStateDisabled(rtm, val) ((rtm)->ModelData.contStateDisabled = (val))
#endif

#ifndef rtmGetContStates
# define rtmGetContStates(rtm)         ((rtm)->ModelData.contStates)
#endif

#ifndef rtmSetContStates
# define rtmSetContStates(rtm, val)    ((rtm)->ModelData.contStates = (val))
#endif

#ifndef rtmGetDerivCacheNeedsReset
# define rtmGetDerivCacheNeedsReset(rtm) ((rtm)->ModelData.derivCacheNeedsReset)
#endif

#ifndef rtmSetDerivCacheNeedsReset
# define rtmSetDerivCacheNeedsReset(rtm, val) ((rtm)->ModelData.derivCacheNeedsReset = (val))
#endif

#ifndef rtmGetIntgData
# define rtmGetIntgData(rtm)           ((rtm)->ModelData.intgData)
#endif

#ifndef rtmSetIntgData
# define rtmSetIntgData(rtm, val)      ((rtm)->ModelData.intgData = (val))
#endif

#ifndef rtmGetOdeF
# define rtmGetOdeF(rtm)               ((rtm)->ModelData.odeF)
#endif

#ifndef rtmSetOdeF
# define rtmSetOdeF(rtm, val)          ((rtm)->ModelData.odeF = (val))
#endif

#ifndef rtmGetOdeY
# define rtmGetOdeY(rtm)               ((rtm)->ModelData.odeY)
#endif

#ifndef rtmSetOdeY
# define rtmSetOdeY(rtm, val)          ((rtm)->ModelData.odeY = (val))
#endif

#ifndef rtmGetPeriodicContStateIndices
# define rtmGetPeriodicContStateIndices(rtm) ((rtm)->ModelData.periodicContStateIndices)
#endif

#ifndef rtmSetPeriodicContStateIndices
# define rtmSetPeriodicContStateIndices(rtm, val) ((rtm)->ModelData.periodicContStateIndices = (val))
#endif

#ifndef rtmGetPeriodicContStateRanges
# define rtmGetPeriodicContStateRanges(rtm) ((rtm)->ModelData.periodicContStateRanges)
#endif

#ifndef rtmSetPeriodicContStateRanges
# define rtmSetPeriodicContStateRanges(rtm, val) ((rtm)->ModelData.periodicContStateRanges = (val))
#endif

#ifndef rtmGetZCCacheNeedsReset
# define rtmGetZCCacheNeedsReset(rtm)  ((rtm)->ModelData.zCCacheNeedsReset)
#endif

#ifndef rtmSetZCCacheNeedsReset
# define rtmSetZCCacheNeedsReset(rtm, val) ((rtm)->ModelData.zCCacheNeedsReset = (val))
#endif

#ifndef rtmGetdX
# define rtmGetdX(rtm)                 ((rtm)->ModelData.derivs)
#endif

#ifndef rtmSetdX
# define rtmSetdX(rtm, val)            ((rtm)->ModelData.derivs = (val))
#endif

#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

#ifndef rtmGetStopRequested
# define rtmGetStopRequested(rtm)      ((rtm)->Timing.stopRequestedFlag)
#endif

#ifndef rtmSetStopRequested
# define rtmSetStopRequested(rtm, val) ((rtm)->Timing.stopRequestedFlag = (val))
#endif

#ifndef rtmGetStopRequestedPtr
# define rtmGetStopRequestedPtr(rtm)   (&((rtm)->Timing.stopRequestedFlag))
#endif

#ifndef rtmGetT
# define rtmGetT(rtm)                  (rtmGetTPtr((rtm))[0])
#endif

// Block signals (auto storage)
typedef struct {
  SL_Bus_deadreckoning_sensor_msgs_LaserScan In1;// '<S15>/In1'
  SL_Bus_deadreckoning_sensor_msgs_LaserScan varargout_2;
  SL_Bus_deadreckoning_nav_msgs_Odometry outputMsg;// '<Root>/odometry_header'
  SL_Bus_deadreckoning_nav_msgs_Odometry BusAssignment;// '<Root>/Bus Assignment' 
  SL_Bus_deadreckoning_geometry_msgs_Twist In1_m;// '<S12>/In1'
  SL_Bus_deadreckoning_geometry_msgs_Twist varargout_2_m;
  SL_Bus_deadreckoning_geometry_msgs_Wrench In1_c;// '<S14>/In1'
  SL_Bus_deadreckoning_geometry_msgs_Wrench varargout_2_c;
  char_T cv0[31];
  real_T thetadotvelsinsteering1L;     // '<Root>/thetadot = vel*sin(steering)*(1//L)' 
  real_T xdotvelcosheading;            // '<Root>/xdot = vel * cos (heading) '
  real_T ydotvelsinheading;            // '<Root>/ydot = vel * sin (heading)'
  uint32_T Output;                     // '<S2>/Output'
} B_deadreckoning_T;

// Block states (auto storage) for system '<Root>'
typedef struct {
  void *SourceBlock_PWORK;             // '<S8>/SourceBlock'
  void *SourceBlock_PWORK_d;           // '<S7>/SourceBlock'
  void *SourceBlock_PWORK_f;           // '<S5>/SourceBlock'
  void *SinkBlock_PWORK;               // '<S3>/SinkBlock'
  uint32_T Output_DSTATE;              // '<S2>/Output'
  robotics_slros_internal_block_T obj; // '<S3>/SinkBlock'
  robotics_slros_internal_blo_f_T obj_o;// '<S8>/SourceBlock'
  robotics_slros_internal_blo_f_T obj_n;// '<S7>/SourceBlock'
  robotics_slros_internal_blo_f_T obj_nf;// '<S5>/SourceBlock'
} DW_deadreckoning_T;

// Continuous states (auto storage)
typedef struct {
  real_T Integrator_CSTATE;            // '<Root>/Integrator'
  real_T Integrator1_CSTATE;           // '<Root>/Integrator1'
  real_T Integrator2_CSTATE;           // '<Root>/Integrator2'
} X_deadreckoning_T;

// Periodic continuous state vector (global)
typedef int_T PeriodicIndX_deadreckoning_T[1];
typedef real_T PeriodicRngX_deadreckoning_T[2];

// State derivatives (auto storage)
typedef struct {
  real_T Integrator_CSTATE;            // '<Root>/Integrator'
  real_T Integrator1_CSTATE;           // '<Root>/Integrator1'
  real_T Integrator2_CSTATE;           // '<Root>/Integrator2'
} XDot_deadreckoning_T;

// State disabled
typedef struct {
  boolean_T Integrator_CSTATE;         // '<Root>/Integrator'
  boolean_T Integrator1_CSTATE;        // '<Root>/Integrator1'
  boolean_T Integrator2_CSTATE;        // '<Root>/Integrator2'
} XDis_deadreckoning_T;

#ifndef ODE3_INTG
#define ODE3_INTG

// ODE3 Integration Data
typedef struct {
  real_T *y;                           // output
  real_T *f[3];                        // derivatives
} ODE3_IntgData;

#endif

// Parameters (auto storage)
struct P_deadreckoning_T_ {
  uint32_T WrapToZero_Threshold;       // Mask Parameter: WrapToZero_Threshold
                                       //  Referenced by: '<S11>/FixPt Switch'

  SL_Bus_deadreckoning_sensor_msgs_LaserScan Out1_Y0;// Computed Parameter: Out1_Y0
                                                     //  Referenced by: '<S15>/Out1'

  SL_Bus_deadreckoning_sensor_msgs_LaserScan Constant_Value;// Computed Parameter: Constant_Value
                                                            //  Referenced by: '<S8>/Constant'

  SL_Bus_deadreckoning_nav_msgs_Odometry Constant_Value_k;// Computed Parameter: Constant_Value_k
                                                          //  Referenced by: '<S1>/Constant'

  SL_Bus_deadreckoning_geometry_msgs_Twist Out1_Y0_f;// Computed Parameter: Out1_Y0_f
                                                     //  Referenced by: '<S12>/Out1'

  SL_Bus_deadreckoning_geometry_msgs_Twist Constant_Value_d;// Computed Parameter: Constant_Value_d
                                                            //  Referenced by: '<S5>/Constant'

  SL_Bus_deadreckoning_geometry_msgs_Wrench Out1_Y0_d;// Computed Parameter: Out1_Y0_d
                                                      //  Referenced by: '<S14>/Out1'

  SL_Bus_deadreckoning_geometry_msgs_Wrench Constant_Value_g;// Computed Parameter: Constant_Value_g
                                                             //  Referenced by: '<S7>/Constant'

  real_T Integrator_IC;                // Expression: 0
                                       //  Referenced by: '<Root>/Integrator'

  real_T Integrator1_IC;               // Expression: 0
                                       //  Referenced by: '<Root>/Integrator1'

  real_T Altitude_Value;               // Expression: 0
                                       //  Referenced by: '<Root>/Altitude'

  real_T Integrator2_IC;               // Expression: 0
                                       //  Referenced by: '<Root>/Integrator2'

  real_T Integrator2_WrappedStateUpperVa;// Expression: pi
                                         //  Referenced by: '<Root>/Integrator2'

  real_T Integrator2_WrappedStateLowerVa;// Expression: -pi
                                         //  Referenced by: '<Root>/Integrator2'

  real_T Constant1_Value;              // Expression: 0
                                       //  Referenced by: '<Root>/Constant1'

  real_T Constant2_Value;              // Expression: 0
                                       //  Referenced by: '<Root>/Constant2'

  real_T u2_Gain;                      // Expression: 0.5
                                       //  Referenced by: '<S4>/1//2'

  real_T Constant_Value_h;             // Expression: 34*pi/180
                                       //  Referenced by: '<Root>/Constant'

  uint32_T Constant_Value_m;           // Computed Parameter: Constant_Value_m
                                       //  Referenced by: '<S11>/Constant'

  uint32_T Output_InitialCondition;    // Computed Parameter: Output_InitialCondition
                                       //  Referenced by: '<S2>/Output'

  uint32_T FixPtConstant_Value;        // Computed Parameter: FixPtConstant_Value
                                       //  Referenced by: '<S10>/FixPt Constant'

};

// Real-time Model Data Structure
struct tag_RTM_deadreckoning_T {
  const char_T *errorStatus;
  RTWSolverInfo solverInfo;

  //
  //  ModelData:
  //  The following substructure contains information regarding
  //  the data used in the model.

  struct {
    X_deadreckoning_T *contStates;
    int_T *periodicContStateIndices;
    real_T *periodicContStateRanges;
    real_T *derivs;
    boolean_T *contStateDisabled;
    boolean_T zCCacheNeedsReset;
    boolean_T derivCacheNeedsReset;
    boolean_T blkStateChange;
    real_T odeY[3];
    real_T odeF[3][3];
    ODE3_IntgData intgData;
  } ModelData;

  //
  //  Sizes:
  //  The following substructure contains sizes information
  //  for many of the model attributes such as inputs, outputs,
  //  dwork, sample times, etc.

  struct {
    int_T numContStates;
    int_T numPeriodicContStates;
    int_T numSampTimes;
  } Sizes;

  //
  //  Timing:
  //  The following substructure contains information regarding
  //  the timing information for the model.

  struct {
    uint32_T clockTick0;
    uint32_T clockTickH0;
    time_T stepSize0;
    uint32_T clockTick1;
    uint32_T clockTickH1;
    SimTimeStep simTimeStep;
    boolean_T stopRequestedFlag;
    time_T *t;
    time_T tArray[2];
  } Timing;
};

// Block parameters (auto storage)
#ifdef __cplusplus

extern "C" {

#endif

  extern P_deadreckoning_T deadreckoning_P;

#ifdef __cplusplus

}
#endif

// Block signals (auto storage)
extern B_deadreckoning_T deadreckoning_B;

// Continuous states (auto storage)
extern X_deadreckoning_T deadreckoning_X;

// Block states (auto storage)
extern DW_deadreckoning_T deadreckoning_DW;

#ifdef __cplusplus

extern "C" {

#endif

#ifdef __cplusplus

}
#endif

#ifdef __cplusplus

extern "C" {

#endif

  // Model entry point functions
  extern void deadreckoning_initialize(void);
  extern void deadreckoning_step(void);
  extern void deadreckoning_terminate(void);

#ifdef __cplusplus

}
#endif

// Real-time Model object
#ifdef __cplusplus

extern "C" {

#endif

  extern RT_MODEL_deadreckoning_T *const deadreckoning_M;

#ifdef __cplusplus

}
#endif

//-
//  These blocks were eliminated from the model due to optimizations:
//
//  Block '<S2>/FixPt Data Type Propagation' : Unused code path elimination
//  Block '<S10>/FixPt Data Type Duplicate' : Unused code path elimination
//  Block '<S11>/FixPt Data Type Duplicate1' : Unused code path elimination
//  Block '<Root>/Scope' : Unused code path elimination


//-
//  The generated code includes comments that allow you to trace directly
//  back to the appropriate location in the model.  The basic format
//  is <system>/block_name, where system is the system number (uniquely
//  assigned by Simulink) and block_name is the name of the block.
//
//  Use the MATLAB hilite_system command to trace the generated code back
//  to the model.  For example,
//
//  hilite_system('<S3>')    - opens system 3
//  hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
//
//  Here is the system hierarchy for this model
//
//  '<Root>' : 'deadreckoning'
//  '<S1>'   : 'deadreckoning/Blank Message'
//  '<S2>'   : 'deadreckoning/Counter Free-Running'
//  '<S3>'   : 'deadreckoning/Publish'
//  '<S4>'   : 'deadreckoning/Rotation Angles to Quaternions'
//  '<S5>'   : 'deadreckoning/Subscribe'
//  '<S6>'   : 'deadreckoning/Subscribe2'
//  '<S7>'   : 'deadreckoning/Subscribe3'
//  '<S8>'   : 'deadreckoning/Subscribe4'
//  '<S9>'   : 'deadreckoning/odometry_header'
//  '<S10>'  : 'deadreckoning/Counter Free-Running/Increment Real World'
//  '<S11>'  : 'deadreckoning/Counter Free-Running/Wrap To Zero'
//  '<S12>'  : 'deadreckoning/Subscribe/Enabled Subsystem'
//  '<S13>'  : 'deadreckoning/Subscribe2/Enabled Subsystem'
//  '<S14>'  : 'deadreckoning/Subscribe3/Enabled Subsystem'
//  '<S15>'  : 'deadreckoning/Subscribe4/Enabled Subsystem'

#endif                                 // RTW_HEADER_deadreckoning_h_

//
// File trailer for generated code.
//
// [EOF]
//
