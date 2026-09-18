/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: FCS.h
 *
 * Code generated for Simulink model 'FCS'.
 *
 * Model version                  : 1.85
 * Simulink Coder version         : 25.2 (R2025b) 28-Jul-2025
 * C/C++ source code generated on : Fri Sep 18 14:34:00 2026
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-M
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. RAM efficiency
 * Validation result: Not run
 */

#ifndef FCS_h_
#define FCS_h_
#ifndef FCS_COMMON_INCLUDES_
#define FCS_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#include "math.h"
#endif                                 /* FCS_COMMON_INCLUDES_ */

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

#define FCS_M                          (rtM)

/* Forward declaration for rtModel */
typedef struct tag_RTM RT_MODEL;

/* Block signals and states (default storage) for system '<S277>/MeasurementUpdate' */
typedef struct {
  boolean_T MeasurementUpdate_MODE;    /* '<S277>/MeasurementUpdate' */
} DW_MeasurementUpdate;

/* Block signals and states (default storage) for system '<S284>/Enabled Subsystem' */
typedef struct {
  boolean_T EnabledSubsystem_MODE;     /* '<S284>/Enabled Subsystem' */
} DW_EnabledSubsystem;

/* Block signals and states (default storage) for system '<Root>' */
typedef struct {
  DW_EnabledSubsystem EnabledSubsystem_f;/* '<S339>/Enabled Subsystem' */
  DW_MeasurementUpdate MeasurementUpdate_k;/* '<S332>/MeasurementUpdate' */
  DW_EnabledSubsystem EnabledSubsystem_k;/* '<S284>/Enabled Subsystem' */
  DW_MeasurementUpdate MeasurementUpdate_gu;/* '<S277>/MeasurementUpdate' */
  real32_T Product2[2];                /* '<S365>/Product2' */
  real32_T Product3[2];                /* '<S363>/Product3' */
  real32_T Product2_g[2];              /* '<S310>/Product2' */
  real32_T Product3_p[2];              /* '<S308>/Product3' */
  real32_T MemoryX_DSTATE[2];          /* '<S311>/MemoryX' */
  real32_T MemoryX_DSTATE_k[2];        /* '<S256>/MemoryX' */
  real32_T Integrator_DSTATE[2];       /* '<S51>/Integrator' */
  real32_T Filter_DSTATE[2];           /* '<S46>/Filter' */
  real32_T Integrator_DSTATE_f[2];     /* '<S109>/Integrator' */
  real32_T UD_DSTATE[2];               /* '<S102>/UD' */
  real32_T PrevY[2];                   /* '<S7>/Rate Limiter' */
  real32_T DiscreteTransferFcn_states; /* '<S369>/Discrete Transfer Fcn' */
  real32_T DiscreteTransferFcn_states_i;/* '<S370>/Discrete Transfer Fcn' */
  real32_T DiscreteTransferFcn_states_l;/* '<S371>/Discrete Transfer Fcn' */
  real32_T Integrator1_DSTATE;         /* '<S255>/Integrator1' */
  real32_T DiscreteTransferFcn_states_lr;/* '<S368>/Discrete Transfer Fcn' */
  real32_T DiscreteTransferFcn_states_n;/* '<S366>/Discrete Transfer Fcn' */
  real32_T DiscreteTransferFcn_states_o;/* '<S367>/Discrete Transfer Fcn' */
  real32_T Integrator_DSTATE_m;        /* '<S167>/Integrator' */
  real32_T Filter_DSTATE_a;            /* '<S162>/Filter' */
  real32_T Integrator5_DSTATE;         /* '<S196>/Integrator5' */
  real32_T Integrator1_DSTATE_e;       /* '<S196>/Integrator1' */
  real32_T DiscreteTransferFcn_states_nk;/* '<S190>/Discrete Transfer Fcn' */
  real32_T PrevY_l;                    /* '<S8>/Rate Limiter1' */
  boolean_T icLoad;                    /* '<S311>/MemoryX' */
  boolean_T icLoad_d;                  /* '<S256>/MemoryX' */
  boolean_T EnabledSubsystem_MODE;     /* '<S226>/Enabled Subsystem' */
  boolean_T MeasurementUpdate_MODE;    /* '<S219>/MeasurementUpdate' */
} DW;

/* Invariant block signals (default storage) */
typedef struct {
  const real32_T Conversion[2];        /* '<S300>/Conversion' */
  const real32_T Conversion_l[2];      /* '<S301>/Conversion' */
  const real32_T Conversion_j[4];      /* '<S303>/Conversion' */
  const real32_T Conversion_b[2];      /* '<S355>/Conversion' */
  const real32_T Conversion_a[2];      /* '<S356>/Conversion' */
  const real32_T Conversion_d[4];      /* '<S358>/Conversion' */
} ConstB;

/* Constant parameters (default storage) */
typedef struct {
  /* Pooled Parameter (Expression: )
   * Referenced by:
   *   '<S256>/C'
   *   '<S311>/C'
   */
  real32_T pooled11[2];

  /* Computed Parameter: Multiply_Gain
   * Referenced by: '<S5>/Multiply'
   */
  real32_T Multiply_Gain[16];
} ConstP;

/* External inputs (root inport signals with default storage) */
typedef struct {
  boolean_T controlModePosVSOrient;    /* '<Root>/controlModePosVSOrient' */
  real32_T pos_ref[3];                 /* '<Root>/pos_ref' */
  boolean_T takeoff_flag;              /* '<Root>/takeoff_flag' */
  real32_T orient_ref[4];              /* '<Root>/orient_ref' */
  real32_T live_time_ticks;            /* '<Root>/live_time_ticks' */
  real32_T kill_switch;                /* '<Root>/kill_switch' */
  real32_T timestamp_ms;               /* '<Root>/timestamp_ms' */
  real32_T status;                     /* '<Root>/status' */
  real32_T axayaz_s[3];                /* '<Root>/axayaz_s' */
  real32_T pqr_sf[3];                  /* '<Root>/pqr_sf' */
  real32_T mxmymz_s[3];                /* '<Root>/mxmymz_s' */
  real32_T altitude_s;                 /* '<Root>/altitude_s' */
  real32_T pressure_s;                 /* '<Root>/pressure_s' */
  real32_T temp_s;                     /* '<Root>/temp_s' */
  real32_T vbat_s;                     /* '<Root>/vbat_s' */
} ExtU;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real32_T FCSb[4];                    /* '<Root>/FCSb' */
  real32_T emergency;                  /* '<Root>/emergency' */
  real32_T xyz_s[3];                   /* '<Root>/xyz_s' */
  real32_T dxdydz_s[3];                /* '<Root>/dxdydz_s' */
  real32_T rollpitchyaw_s[3];          /* '<Root>/rollpitchyaw_s' */
  real32_T pqr_s[3];                   /* '<Root>/pqr_s' */
} ExtY;

/* Real-time Model Data Structure */
struct tag_RTM {
  const char_T * volatile errorStatus;
};

/* Block signals and states (default storage) */
extern DW rtDW;

/* External inputs (root inport signals with default storage) */
extern ExtU rtU;

/* External outputs (root outports fed by signals with default storage) */
extern ExtY rtY;
extern const ConstB rtConstB;          /* constant block i/o */

/* Constant parameters (default storage) */
extern const ConstP rtConstP;

/* Model entry point functions */
extern void FCS_initialize(void);
extern void FCS_step(void);

/* Real-time Model object */
extern RT_MODEL *const rtM;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S5>/Matrix Multiply' : Unused code path elimination
 * Block '<S5>/Reshape' : Unused code path elimination
 * Block '<S5>/Scope' : Unused code path elimination
 * Block '<S5>/Scope1' : Unused code path elimination
 * Block '<S5>/Scope2' : Unused code path elimination
 * Block '<S5>/Scope3' : Unused code path elimination
 * Block '<S5>/TorqueTotalThrustToThrustPerMotor' : Unused code path elimination
 * Block '<S5>/Transpose' : Unused code path elimination
 * Block '<S2>/Scope' : Unused code path elimination
 * Block '<S2>/Scope1' : Unused code path elimination
 * Block '<S2>/Scope2' : Unused code path elimination
 * Block '<S2>/Scope3' : Unused code path elimination
 * Block '<S2>/Scope4' : Unused code path elimination
 * Block '<S2>/Scope5' : Unused code path elimination
 * Block '<S2>/Scope6' : Unused code path elimination
 * Block '<S6>/AND' : Unused code path elimination
 * Block '<S6>/Abs' : Unused code path elimination
 * Block '<S9>/Compare' : Unused code path elimination
 * Block '<S9>/Constant' : Unused code path elimination
 * Block '<S10>/Compare' : Unused code path elimination
 * Block '<S10>/Constant' : Unused code path elimination
 * Block '<S6>/Constant' : Unused code path elimination
 * Block '<S6>/Constant2' : Unused code path elimination
 * Block '<S11>/Data Type Duplicate' : Unused code path elimination
 * Block '<S11>/Diff' : Unused code path elimination
 * Block '<S11>/TSamp' : Unused code path elimination
 * Block '<S11>/UD' : Unused code path elimination
 * Block '<S6>/Gain1' : Unused code path elimination
 * Block '<S6>/Gain5' : Unused code path elimination
 * Block '<S6>/Gain6' : Unused code path elimination
 * Block '<S6>/Integrator2' : Unused code path elimination
 * Block '<S6>/NOT' : Unused code path elimination
 * Block '<S6>/Rate Limiter1' : Unused code path elimination
 * Block '<S12>/Logic' : Unused code path elimination
 * Block '<S12>/Memory' : Unused code path elimination
 * Block '<S6>/Saturation1' : Unused code path elimination
 * Block '<S6>/Scope' : Unused code path elimination
 * Block '<S6>/Sum1' : Unused code path elimination
 * Block '<S6>/Sum3' : Unused code path elimination
 * Block '<S6>/Sum4' : Unused code path elimination
 * Block '<S6>/Switch' : Unused code path elimination
 * Block '<S6>/Switch2' : Unused code path elimination
 * Block '<S6>/Switch3' : Unused code path elimination
 * Block '<S6>/Unit Delay' : Unused code path elimination
 * Block '<S102>/DTDup' : Unused code path elimination
 * Block '<S7>/Scope' : Unused code path elimination
 * Block '<S8>/Discrete-Time Integrator' : Unused code path elimination
 * Block '<S8>/Scope' : Unused code path elimination
 * Block '<S3>/Scope' : Unused code path elimination
 * Block '<S187>/Scope' : Unused code path elimination
 * Block '<S187>/Scope1' : Unused code path elimination
 * Block '<S187>/Scope2' : Unused code path elimination
 * Block '<S194>/Constant' : Unused code path elimination
 * Block '<S194>/Scope' : Unused code path elimination
 * Block '<S194>/Scope1' : Unused code path elimination
 * Block '<S195>/Scope' : Unused code path elimination
 * Block '<S196>/Integrator2' : Unused code path elimination
 * Block '<S196>/Integrator4' : Unused code path elimination
 * Block '<S198>/A' : Unused code path elimination
 * Block '<S198>/B' : Unused code path elimination
 * Block '<S198>/C' : Unused code path elimination
 * Block '<S242>/Conversion' : Unused code path elimination
 * Block '<S242>/Data Type Duplicate' : Unused code path elimination
 * Block '<S243>/Conversion' : Unused code path elimination
 * Block '<S243>/Data Type Duplicate' : Unused code path elimination
 * Block '<S244>/Conversion' : Unused code path elimination
 * Block '<S244>/Data Type Duplicate' : Unused code path elimination
 * Block '<S245>/Data Type Duplicate' : Unused code path elimination
 * Block '<S199>/KalmanGainL' : Unused code path elimination
 * Block '<S199>/KalmanGainM' : Unused code path elimination
 * Block '<S198>/D' : Unused code path elimination
 * Block '<S202>/Data Type Duplicate' : Unused code path elimination
 * Block '<S203>/Data Type Duplicate' : Unused code path elimination
 * Block '<S204>/Data Type Duplicate' : Unused code path elimination
 * Block '<S205>/Data Type Duplicate' : Unused code path elimination
 * Block '<S207>/Data Type Duplicate' : Unused code path elimination
 * Block '<S208>/Data Type Duplicate' : Unused code path elimination
 * Block '<S209>/Data Type Duplicate' : Unused code path elimination
 * Block '<S210>/Conversion' : Unused code path elimination
 * Block '<S210>/Data Type Duplicate' : Unused code path elimination
 * Block '<S211>/Data Type Duplicate' : Unused code path elimination
 * Block '<S212>/Data Type Duplicate' : Unused code path elimination
 * Block '<S213>/Data Type Duplicate' : Unused code path elimination
 * Block '<S215>/Conversion' : Unused code path elimination
 * Block '<S215>/Data Type Duplicate' : Unused code path elimination
 * Block '<S216>/Data Type Duplicate' : Unused code path elimination
 * Block '<S198>/G' : Unused code path elimination
 * Block '<S198>/H' : Unused code path elimination
 * Block '<S198>/MemoryX' : Unused code path elimination
 * Block '<S198>/N' : Unused code path elimination
 * Block '<S219>/A[k]*xhat[k|k-1]' : Unused code path elimination
 * Block '<S219>/Add' : Unused code path elimination
 * Block '<S219>/B[k]*u[k]' : Unused code path elimination
 * Block '<S250>/Add1' : Unused code path elimination
 * Block '<S250>/C[k]*xhat[k|k-1]' : Unused code path elimination
 * Block '<S250>/D[k]*u[k]' : Unused code path elimination
 * Block '<S250>/Product3' : Unused code path elimination
 * Block '<S250>/Sum' : Unused code path elimination
 * Block '<S219>/Reshape' : Unused code path elimination
 * Block '<S198>/P0' : Unused code path elimination
 * Block '<S198>/Q' : Unused code path elimination
 * Block '<S198>/R' : Unused code path elimination
 * Block '<S198>/ReshapeX0' : Unused code path elimination
 * Block '<S198>/Reshapeu' : Unused code path elimination
 * Block '<S198>/Reshapexhat' : Unused code path elimination
 * Block '<S198>/Reshapey' : Unused code path elimination
 * Block '<S226>/Add' : Unused code path elimination
 * Block '<S252>/Add1' : Unused code path elimination
 * Block '<S252>/Product' : Unused code path elimination
 * Block '<S252>/Product2' : Unused code path elimination
 * Block '<S198>/X0' : Unused code path elimination
 * Block '<S240>/CheckSignalProperties' : Unused code path elimination
 * Block '<S241>/CheckSignalProperties' : Unused code path elimination
 * Block '<S197>/Rate Transition' : Unused code path elimination
 * Block '<S197>/Scope' : Unused code path elimination
 * Block '<S197>/Scope1' : Unused code path elimination
 * Block '<S300>/Data Type Duplicate' : Unused code path elimination
 * Block '<S301>/Data Type Duplicate' : Unused code path elimination
 * Block '<S302>/Conversion' : Unused code path elimination
 * Block '<S302>/Data Type Duplicate' : Unused code path elimination
 * Block '<S303>/Data Type Duplicate' : Unused code path elimination
 * Block '<S260>/Data Type Duplicate' : Unused code path elimination
 * Block '<S261>/Data Type Duplicate' : Unused code path elimination
 * Block '<S262>/Data Type Duplicate' : Unused code path elimination
 * Block '<S263>/Data Type Duplicate' : Unused code path elimination
 * Block '<S265>/Data Type Duplicate' : Unused code path elimination
 * Block '<S266>/Data Type Duplicate' : Unused code path elimination
 * Block '<S267>/Data Type Duplicate' : Unused code path elimination
 * Block '<S268>/Conversion' : Unused code path elimination
 * Block '<S268>/Data Type Duplicate' : Unused code path elimination
 * Block '<S269>/Data Type Duplicate' : Unused code path elimination
 * Block '<S270>/Data Type Duplicate' : Unused code path elimination
 * Block '<S271>/Data Type Duplicate' : Unused code path elimination
 * Block '<S273>/Data Type Duplicate' : Unused code path elimination
 * Block '<S274>/Data Type Duplicate' : Unused code path elimination
 * Block '<S256>/G' : Unused code path elimination
 * Block '<S256>/H' : Unused code path elimination
 * Block '<S256>/N' : Unused code path elimination
 * Block '<S256>/P0' : Unused code path elimination
 * Block '<S256>/Q' : Unused code path elimination
 * Block '<S256>/R' : Unused code path elimination
 * Block '<S298>/CheckSignalProperties' : Unused code path elimination
 * Block '<S298>/Data Type Conversion3' : Unused code path elimination
 * Block '<S299>/CheckSignalProperties' : Unused code path elimination
 * Block '<S253>/Scope' : Unused code path elimination
 * Block '<S253>/Scope1' : Unused code path elimination
 * Block '<S253>/Scope2' : Unused code path elimination
 * Block '<S253>/Scope3' : Unused code path elimination
 * Block '<S355>/Data Type Duplicate' : Unused code path elimination
 * Block '<S356>/Data Type Duplicate' : Unused code path elimination
 * Block '<S357>/Conversion' : Unused code path elimination
 * Block '<S357>/Data Type Duplicate' : Unused code path elimination
 * Block '<S358>/Data Type Duplicate' : Unused code path elimination
 * Block '<S315>/Data Type Duplicate' : Unused code path elimination
 * Block '<S316>/Data Type Duplicate' : Unused code path elimination
 * Block '<S317>/Data Type Duplicate' : Unused code path elimination
 * Block '<S318>/Data Type Duplicate' : Unused code path elimination
 * Block '<S320>/Data Type Duplicate' : Unused code path elimination
 * Block '<S321>/Data Type Duplicate' : Unused code path elimination
 * Block '<S322>/Data Type Duplicate' : Unused code path elimination
 * Block '<S323>/Conversion' : Unused code path elimination
 * Block '<S323>/Data Type Duplicate' : Unused code path elimination
 * Block '<S324>/Data Type Duplicate' : Unused code path elimination
 * Block '<S325>/Data Type Duplicate' : Unused code path elimination
 * Block '<S326>/Data Type Duplicate' : Unused code path elimination
 * Block '<S328>/Data Type Duplicate' : Unused code path elimination
 * Block '<S329>/Data Type Duplicate' : Unused code path elimination
 * Block '<S311>/G' : Unused code path elimination
 * Block '<S311>/H' : Unused code path elimination
 * Block '<S311>/N' : Unused code path elimination
 * Block '<S311>/P0' : Unused code path elimination
 * Block '<S311>/Q' : Unused code path elimination
 * Block '<S311>/R' : Unused code path elimination
 * Block '<S353>/CheckSignalProperties' : Unused code path elimination
 * Block '<S353>/Data Type Conversion3' : Unused code path elimination
 * Block '<S354>/CheckSignalProperties' : Unused code path elimination
 * Block '<S254>/Scope' : Unused code path elimination
 * Block '<S254>/Scope2' : Unused code path elimination
 * Block '<S255>/Scope' : Unused code path elimination
 * Block '<S255>/Scope1' : Unused code path elimination
 * Block '<S189>/Discrete Transfer Fcn' : Unused code path elimination
 * Block '<S191>/Discrete Transfer Fcn' : Unused code path elimination
 * Block '<S4>/Constant' : Unused code path elimination
 * Block '<S4>/Gain3' : Unused code path elimination
 * Block '<S4>/Sum' : Unused code path elimination
 * Block '<S124>/Setpoint Weighting (Proportional)' : Eliminated nontunable gain of 1
 * Block '<S182>/Setpoint Weighting (Proportional)' : Eliminated nontunable gain of 1
 * Block '<S3>/Data Type Conversion1' : Eliminate redundant data type conversion
 * Block '<S3>/Data Type Conversion3' : Eliminate redundant data type conversion
 * Block '<S187>/Data Type Conversion3' : Eliminate redundant data type conversion
 * Block '<S245>/Conversion' : Eliminate redundant data type conversion
 * Block '<S253>/Data Type Conversion3' : Eliminate redundant data type conversion
 * Block '<S273>/Conversion' : Eliminate redundant data type conversion
 * Block '<S277>/Reshape' : Reshape block reduction
 * Block '<S256>/ReshapeX0' : Reshape block reduction
 * Block '<S256>/Reshapeu' : Reshape block reduction
 * Block '<S256>/Reshapexhat' : Reshape block reduction
 * Block '<S256>/Reshapey' : Reshape block reduction
 * Block '<S253>/Rate Transition' : Eliminated since input and output rates are identical
 * Block '<S253>/Rate Transition1' : Eliminated since input and output rates are identical
 * Block '<S254>/Data Type Conversion3' : Eliminate redundant data type conversion
 * Block '<S328>/Conversion' : Eliminate redundant data type conversion
 * Block '<S332>/Reshape' : Reshape block reduction
 * Block '<S311>/ReshapeX0' : Reshape block reduction
 * Block '<S311>/Reshapeu' : Reshape block reduction
 * Block '<S311>/Reshapexhat' : Reshape block reduction
 * Block '<S311>/Reshapey' : Reshape block reduction
 * Block '<S254>/Rate Transition' : Eliminated since input and output rates are identical
 * Block '<S254>/Rate Transition1' : Eliminated since input and output rates are identical
 */

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Note that this particular code originates from a subsystem build,
 * and has its own system numbers different from the parent model.
 * Refer to the system hierarchy for this subsystem below, and use the
 * MATLAB hilite_system command to trace the generated code back
 * to the parent model.  For example,
 *
 * hilite_system('softMBD/FCS')    - opens subsystem softMBD/FCS
 * hilite_system('softMBD/FCS/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'softMBD'
 * '<S1>'   : 'softMBD/FCS'
 * '<S2>'   : 'softMBD/FCS/Controller'
 * '<S3>'   : 'softMBD/FCS/filters'
 * '<S4>'   : 'softMBD/FCS/value scaling'
 * '<S5>'   : 'softMBD/FCS/Controller/Mixer'
 * '<S6>'   : 'softMBD/FCS/Controller/Thrust_controller'
 * '<S7>'   : 'softMBD/FCS/Controller/roll_pitch_controller'
 * '<S8>'   : 'softMBD/FCS/Controller/tau_contorller'
 * '<S9>'   : 'softMBD/FCS/Controller/Thrust_controller/Compare To Constant'
 * '<S10>'  : 'softMBD/FCS/Controller/Thrust_controller/Compare To Constant1'
 * '<S11>'  : 'softMBD/FCS/Controller/Thrust_controller/Discrete Derivative'
 * '<S12>'  : 'softMBD/FCS/Controller/Thrust_controller/S-R Flip-Flop'
 * '<S13>'  : 'softMBD/FCS/Controller/roll_pitch_controller/Compare To Constant'
 * '<S14>'  : 'softMBD/FCS/Controller/roll_pitch_controller/Compare To Constant1'
 * '<S15>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller'
 * '<S16>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller (2DOF)'
 * '<S17>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller/Anti-windup'
 * '<S18>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller/D Gain'
 * '<S19>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller/External Derivative'
 * '<S20>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller/Filter'
 * '<S21>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller/Filter ICs'
 * '<S22>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller/I Gain'
 * '<S23>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller/Ideal P Gain'
 * '<S24>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller/Ideal P Gain Fdbk'
 * '<S25>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller/Integrator'
 * '<S26>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller/Integrator ICs'
 * '<S27>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller/N Copy'
 * '<S28>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller/N Gain'
 * '<S29>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller/P Copy'
 * '<S30>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller/Parallel P Gain'
 * '<S31>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller/Reset Signal'
 * '<S32>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller/Saturation'
 * '<S33>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller/Saturation Fdbk'
 * '<S34>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller/Sum'
 * '<S35>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller/Sum Fdbk'
 * '<S36>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller/Tracking Mode'
 * '<S37>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller/Tracking Mode Sum'
 * '<S38>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller/Tsamp - Integral'
 * '<S39>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller/Tsamp - Ngain'
 * '<S40>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller/postSat Signal'
 * '<S41>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller/preInt Signal'
 * '<S42>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller/preSat Signal'
 * '<S43>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller/Anti-windup/Passthrough'
 * '<S44>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller/D Gain/Internal Parameters'
 * '<S45>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller/External Derivative/Error'
 * '<S46>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller/Filter/Disc. Forward Euler Filter'
 * '<S47>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller/Filter ICs/Internal IC - Filter'
 * '<S48>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller/I Gain/Internal Parameters'
 * '<S49>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller/Ideal P Gain/Passthrough'
 * '<S50>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller/Ideal P Gain Fdbk/Disabled'
 * '<S51>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller/Integrator/Discrete'
 * '<S52>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller/Integrator ICs/Internal IC'
 * '<S53>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller/N Copy/Disabled'
 * '<S54>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller/N Gain/Internal Parameters'
 * '<S55>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller/P Copy/Disabled'
 * '<S56>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller/Parallel P Gain/Internal Parameters'
 * '<S57>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller/Reset Signal/Disabled'
 * '<S58>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller/Saturation/Passthrough'
 * '<S59>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller/Saturation Fdbk/Disabled'
 * '<S60>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller/Sum/Sum_PID'
 * '<S61>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller/Sum Fdbk/Disabled'
 * '<S62>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller/Tracking Mode/Disabled'
 * '<S63>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller/Tracking Mode Sum/Passthrough'
 * '<S64>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller/Tsamp - Integral/TsSignalSpecification'
 * '<S65>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller/Tsamp - Ngain/Passthrough'
 * '<S66>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller/postSat Signal/Forward_Path'
 * '<S67>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller/preInt Signal/Internal PreInt'
 * '<S68>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller/preSat Signal/Forward_Path'
 * '<S69>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller (2DOF)/Anti-windup'
 * '<S70>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller (2DOF)/D Gain'
 * '<S71>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller (2DOF)/External Derivative'
 * '<S72>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller (2DOF)/Filter'
 * '<S73>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller (2DOF)/Filter ICs'
 * '<S74>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller (2DOF)/I Gain'
 * '<S75>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller (2DOF)/Ideal P Gain'
 * '<S76>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller (2DOF)/Ideal P Gain Fdbk'
 * '<S77>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller (2DOF)/Integrator'
 * '<S78>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller (2DOF)/Integrator ICs'
 * '<S79>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller (2DOF)/N Copy'
 * '<S80>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller (2DOF)/N Gain'
 * '<S81>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller (2DOF)/P Copy'
 * '<S82>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller (2DOF)/Parallel P Gain'
 * '<S83>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller (2DOF)/Reset Signal'
 * '<S84>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller (2DOF)/Saturation'
 * '<S85>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller (2DOF)/Saturation Fdbk'
 * '<S86>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller (2DOF)/Sum'
 * '<S87>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller (2DOF)/Sum Fdbk'
 * '<S88>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller (2DOF)/Tracking Mode'
 * '<S89>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller (2DOF)/Tracking Mode Sum'
 * '<S90>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller (2DOF)/Tsamp - Integral'
 * '<S91>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller (2DOF)/Tsamp - Ngain'
 * '<S92>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller (2DOF)/b Gain'
 * '<S93>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller (2DOF)/c Gain'
 * '<S94>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller (2DOF)/postSat Signal'
 * '<S95>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller (2DOF)/preInt Signal'
 * '<S96>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller (2DOF)/preSat Signal'
 * '<S97>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller (2DOF)/Anti-windup/Disc. Clamping Parallel'
 * '<S98>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller (2DOF)/Anti-windup/Disc. Clamping Parallel/Dead Zone'
 * '<S99>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller (2DOF)/Anti-windup/Disc. Clamping Parallel/Dead Zone/Enabled'
 * '<S100>' : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller (2DOF)/D Gain/Internal Parameters'
 * '<S101>' : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller (2DOF)/External Derivative/Error'
 * '<S102>' : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller (2DOF)/Filter/Differentiator'
 * '<S103>' : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller (2DOF)/Filter/Differentiator/Tsamp'
 * '<S104>' : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller (2DOF)/Filter/Differentiator/Tsamp/Internal Ts'
 * '<S105>' : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller (2DOF)/Filter ICs/Internal IC - Differentiator'
 * '<S106>' : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller (2DOF)/I Gain/Internal Parameters'
 * '<S107>' : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller (2DOF)/Ideal P Gain/Passthrough'
 * '<S108>' : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller (2DOF)/Ideal P Gain Fdbk/Disabled'
 * '<S109>' : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller (2DOF)/Integrator/Discrete'
 * '<S110>' : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller (2DOF)/Integrator ICs/Internal IC'
 * '<S111>' : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller (2DOF)/N Copy/Disabled wSignal Specification'
 * '<S112>' : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller (2DOF)/N Gain/Passthrough'
 * '<S113>' : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller (2DOF)/P Copy/Disabled'
 * '<S114>' : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller (2DOF)/Parallel P Gain/Internal Parameters'
 * '<S115>' : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller (2DOF)/Reset Signal/Disabled'
 * '<S116>' : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller (2DOF)/Saturation/Enabled'
 * '<S117>' : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller (2DOF)/Saturation Fdbk/Disabled'
 * '<S118>' : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller (2DOF)/Sum/Sum_PID'
 * '<S119>' : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller (2DOF)/Sum Fdbk/Disabled'
 * '<S120>' : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller (2DOF)/Tracking Mode/Disabled'
 * '<S121>' : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller (2DOF)/Tracking Mode Sum/Passthrough'
 * '<S122>' : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller (2DOF)/Tsamp - Integral/TsSignalSpecification'
 * '<S123>' : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller (2DOF)/Tsamp - Ngain/Passthrough'
 * '<S124>' : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller (2DOF)/b Gain/Internal Parameters'
 * '<S125>' : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller (2DOF)/c Gain/Internal Parameters'
 * '<S126>' : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller (2DOF)/postSat Signal/Forward_Path'
 * '<S127>' : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller (2DOF)/preInt Signal/Internal PreInt'
 * '<S128>' : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller (2DOF)/preSat Signal/Forward_Path'
 * '<S129>' : 'softMBD/FCS/Controller/tau_contorller/Compare To Constant'
 * '<S130>' : 'softMBD/FCS/Controller/tau_contorller/PID Controller (2DOF)'
 * '<S131>' : 'softMBD/FCS/Controller/tau_contorller/PID Controller (2DOF)/Anti-windup'
 * '<S132>' : 'softMBD/FCS/Controller/tau_contorller/PID Controller (2DOF)/D Gain'
 * '<S133>' : 'softMBD/FCS/Controller/tau_contorller/PID Controller (2DOF)/External Derivative'
 * '<S134>' : 'softMBD/FCS/Controller/tau_contorller/PID Controller (2DOF)/Filter'
 * '<S135>' : 'softMBD/FCS/Controller/tau_contorller/PID Controller (2DOF)/Filter ICs'
 * '<S136>' : 'softMBD/FCS/Controller/tau_contorller/PID Controller (2DOF)/I Gain'
 * '<S137>' : 'softMBD/FCS/Controller/tau_contorller/PID Controller (2DOF)/Ideal P Gain'
 * '<S138>' : 'softMBD/FCS/Controller/tau_contorller/PID Controller (2DOF)/Ideal P Gain Fdbk'
 * '<S139>' : 'softMBD/FCS/Controller/tau_contorller/PID Controller (2DOF)/Integrator'
 * '<S140>' : 'softMBD/FCS/Controller/tau_contorller/PID Controller (2DOF)/Integrator ICs'
 * '<S141>' : 'softMBD/FCS/Controller/tau_contorller/PID Controller (2DOF)/N Copy'
 * '<S142>' : 'softMBD/FCS/Controller/tau_contorller/PID Controller (2DOF)/N Gain'
 * '<S143>' : 'softMBD/FCS/Controller/tau_contorller/PID Controller (2DOF)/P Copy'
 * '<S144>' : 'softMBD/FCS/Controller/tau_contorller/PID Controller (2DOF)/Parallel P Gain'
 * '<S145>' : 'softMBD/FCS/Controller/tau_contorller/PID Controller (2DOF)/Reset Signal'
 * '<S146>' : 'softMBD/FCS/Controller/tau_contorller/PID Controller (2DOF)/Saturation'
 * '<S147>' : 'softMBD/FCS/Controller/tau_contorller/PID Controller (2DOF)/Saturation Fdbk'
 * '<S148>' : 'softMBD/FCS/Controller/tau_contorller/PID Controller (2DOF)/Sum'
 * '<S149>' : 'softMBD/FCS/Controller/tau_contorller/PID Controller (2DOF)/Sum Fdbk'
 * '<S150>' : 'softMBD/FCS/Controller/tau_contorller/PID Controller (2DOF)/Tracking Mode'
 * '<S151>' : 'softMBD/FCS/Controller/tau_contorller/PID Controller (2DOF)/Tracking Mode Sum'
 * '<S152>' : 'softMBD/FCS/Controller/tau_contorller/PID Controller (2DOF)/Tsamp - Integral'
 * '<S153>' : 'softMBD/FCS/Controller/tau_contorller/PID Controller (2DOF)/Tsamp - Ngain'
 * '<S154>' : 'softMBD/FCS/Controller/tau_contorller/PID Controller (2DOF)/b Gain'
 * '<S155>' : 'softMBD/FCS/Controller/tau_contorller/PID Controller (2DOF)/c Gain'
 * '<S156>' : 'softMBD/FCS/Controller/tau_contorller/PID Controller (2DOF)/postSat Signal'
 * '<S157>' : 'softMBD/FCS/Controller/tau_contorller/PID Controller (2DOF)/preInt Signal'
 * '<S158>' : 'softMBD/FCS/Controller/tau_contorller/PID Controller (2DOF)/preSat Signal'
 * '<S159>' : 'softMBD/FCS/Controller/tau_contorller/PID Controller (2DOF)/Anti-windup/Passthrough'
 * '<S160>' : 'softMBD/FCS/Controller/tau_contorller/PID Controller (2DOF)/D Gain/Internal Parameters'
 * '<S161>' : 'softMBD/FCS/Controller/tau_contorller/PID Controller (2DOF)/External Derivative/Error'
 * '<S162>' : 'softMBD/FCS/Controller/tau_contorller/PID Controller (2DOF)/Filter/Disc. Forward Euler Filter'
 * '<S163>' : 'softMBD/FCS/Controller/tau_contorller/PID Controller (2DOF)/Filter ICs/Internal IC - Filter'
 * '<S164>' : 'softMBD/FCS/Controller/tau_contorller/PID Controller (2DOF)/I Gain/Internal Parameters'
 * '<S165>' : 'softMBD/FCS/Controller/tau_contorller/PID Controller (2DOF)/Ideal P Gain/Passthrough'
 * '<S166>' : 'softMBD/FCS/Controller/tau_contorller/PID Controller (2DOF)/Ideal P Gain Fdbk/Disabled'
 * '<S167>' : 'softMBD/FCS/Controller/tau_contorller/PID Controller (2DOF)/Integrator/Discrete'
 * '<S168>' : 'softMBD/FCS/Controller/tau_contorller/PID Controller (2DOF)/Integrator ICs/Internal IC'
 * '<S169>' : 'softMBD/FCS/Controller/tau_contorller/PID Controller (2DOF)/N Copy/Disabled'
 * '<S170>' : 'softMBD/FCS/Controller/tau_contorller/PID Controller (2DOF)/N Gain/Internal Parameters'
 * '<S171>' : 'softMBD/FCS/Controller/tau_contorller/PID Controller (2DOF)/P Copy/Disabled'
 * '<S172>' : 'softMBD/FCS/Controller/tau_contorller/PID Controller (2DOF)/Parallel P Gain/Internal Parameters'
 * '<S173>' : 'softMBD/FCS/Controller/tau_contorller/PID Controller (2DOF)/Reset Signal/Disabled'
 * '<S174>' : 'softMBD/FCS/Controller/tau_contorller/PID Controller (2DOF)/Saturation/Passthrough'
 * '<S175>' : 'softMBD/FCS/Controller/tau_contorller/PID Controller (2DOF)/Saturation Fdbk/Disabled'
 * '<S176>' : 'softMBD/FCS/Controller/tau_contorller/PID Controller (2DOF)/Sum/Sum_PID'
 * '<S177>' : 'softMBD/FCS/Controller/tau_contorller/PID Controller (2DOF)/Sum Fdbk/Disabled'
 * '<S178>' : 'softMBD/FCS/Controller/tau_contorller/PID Controller (2DOF)/Tracking Mode/Disabled'
 * '<S179>' : 'softMBD/FCS/Controller/tau_contorller/PID Controller (2DOF)/Tracking Mode Sum/Passthrough'
 * '<S180>' : 'softMBD/FCS/Controller/tau_contorller/PID Controller (2DOF)/Tsamp - Integral/TsSignalSpecification'
 * '<S181>' : 'softMBD/FCS/Controller/tau_contorller/PID Controller (2DOF)/Tsamp - Ngain/Passthrough'
 * '<S182>' : 'softMBD/FCS/Controller/tau_contorller/PID Controller (2DOF)/b Gain/Internal Parameters'
 * '<S183>' : 'softMBD/FCS/Controller/tau_contorller/PID Controller (2DOF)/c Gain/Internal Parameters'
 * '<S184>' : 'softMBD/FCS/Controller/tau_contorller/PID Controller (2DOF)/postSat Signal/Forward_Path'
 * '<S185>' : 'softMBD/FCS/Controller/tau_contorller/PID Controller (2DOF)/preInt Signal/Internal PreInt'
 * '<S186>' : 'softMBD/FCS/Controller/tau_contorller/PID Controller (2DOF)/preSat Signal/Forward_Path'
 * '<S187>' : 'softMBD/FCS/filters/Subsystem'
 * '<S188>' : 'softMBD/FCS/filters/Subsystem1'
 * '<S189>' : 'softMBD/FCS/filters/Transfer Fcn'
 * '<S190>' : 'softMBD/FCS/filters/Transfer Fcn1'
 * '<S191>' : 'softMBD/FCS/filters/Transfer Fcn2'
 * '<S192>' : 'softMBD/FCS/filters/pqr_LPF'
 * '<S193>' : 'softMBD/FCS/filters/pqr_LPF1'
 * '<S194>' : 'softMBD/FCS/filters/Subsystem/body2earth'
 * '<S195>' : 'softMBD/FCS/filters/Subsystem/x,y,z,dy,dy,dz'
 * '<S196>' : 'softMBD/FCS/filters/Subsystem/x,y,z,dy,dy,dz/x.y.dx.dy'
 * '<S197>' : 'softMBD/FCS/filters/Subsystem/x,y,z,dy,dy,dz/z,dz'
 * '<S198>' : 'softMBD/FCS/filters/Subsystem/x,y,z,dy,dy,dz/z,dz/Kalman Filter1'
 * '<S199>' : 'softMBD/FCS/filters/Subsystem/x,y,z,dy,dy,dz/z,dz/Kalman Filter1/CalculatePL'
 * '<S200>' : 'softMBD/FCS/filters/Subsystem/x,y,z,dy,dy,dz/z,dz/Kalman Filter1/CalculateYhat'
 * '<S201>' : 'softMBD/FCS/filters/Subsystem/x,y,z,dy,dy,dz/z,dz/Kalman Filter1/CovarianceOutputConfigurator'
 * '<S202>' : 'softMBD/FCS/filters/Subsystem/x,y,z,dy,dy,dz/z,dz/Kalman Filter1/DataTypeConversionA'
 * '<S203>' : 'softMBD/FCS/filters/Subsystem/x,y,z,dy,dy,dz/z,dz/Kalman Filter1/DataTypeConversionB'
 * '<S204>' : 'softMBD/FCS/filters/Subsystem/x,y,z,dy,dy,dz/z,dz/Kalman Filter1/DataTypeConversionC'
 * '<S205>' : 'softMBD/FCS/filters/Subsystem/x,y,z,dy,dy,dz/z,dz/Kalman Filter1/DataTypeConversionD'
 * '<S206>' : 'softMBD/FCS/filters/Subsystem/x,y,z,dy,dy,dz/z,dz/Kalman Filter1/DataTypeConversionEnable'
 * '<S207>' : 'softMBD/FCS/filters/Subsystem/x,y,z,dy,dy,dz/z,dz/Kalman Filter1/DataTypeConversionG'
 * '<S208>' : 'softMBD/FCS/filters/Subsystem/x,y,z,dy,dy,dz/z,dz/Kalman Filter1/DataTypeConversionH'
 * '<S209>' : 'softMBD/FCS/filters/Subsystem/x,y,z,dy,dy,dz/z,dz/Kalman Filter1/DataTypeConversionN'
 * '<S210>' : 'softMBD/FCS/filters/Subsystem/x,y,z,dy,dy,dz/z,dz/Kalman Filter1/DataTypeConversionP'
 * '<S211>' : 'softMBD/FCS/filters/Subsystem/x,y,z,dy,dy,dz/z,dz/Kalman Filter1/DataTypeConversionP0'
 * '<S212>' : 'softMBD/FCS/filters/Subsystem/x,y,z,dy,dy,dz/z,dz/Kalman Filter1/DataTypeConversionQ'
 * '<S213>' : 'softMBD/FCS/filters/Subsystem/x,y,z,dy,dy,dz/z,dz/Kalman Filter1/DataTypeConversionR'
 * '<S214>' : 'softMBD/FCS/filters/Subsystem/x,y,z,dy,dy,dz/z,dz/Kalman Filter1/DataTypeConversionReset'
 * '<S215>' : 'softMBD/FCS/filters/Subsystem/x,y,z,dy,dy,dz/z,dz/Kalman Filter1/DataTypeConversionX'
 * '<S216>' : 'softMBD/FCS/filters/Subsystem/x,y,z,dy,dy,dz/z,dz/Kalman Filter1/DataTypeConversionX0'
 * '<S217>' : 'softMBD/FCS/filters/Subsystem/x,y,z,dy,dy,dz/z,dz/Kalman Filter1/DataTypeConversionu'
 * '<S218>' : 'softMBD/FCS/filters/Subsystem/x,y,z,dy,dy,dz/z,dz/Kalman Filter1/MemoryP'
 * '<S219>' : 'softMBD/FCS/filters/Subsystem/x,y,z,dy,dy,dz/z,dz/Kalman Filter1/Observer'
 * '<S220>' : 'softMBD/FCS/filters/Subsystem/x,y,z,dy,dy,dz/z,dz/Kalman Filter1/ReducedQRN'
 * '<S221>' : 'softMBD/FCS/filters/Subsystem/x,y,z,dy,dy,dz/z,dz/Kalman Filter1/Reset'
 * '<S222>' : 'softMBD/FCS/filters/Subsystem/x,y,z,dy,dy,dz/z,dz/Kalman Filter1/Reshapeyhat'
 * '<S223>' : 'softMBD/FCS/filters/Subsystem/x,y,z,dy,dy,dz/z,dz/Kalman Filter1/ScalarExpansionP0'
 * '<S224>' : 'softMBD/FCS/filters/Subsystem/x,y,z,dy,dy,dz/z,dz/Kalman Filter1/ScalarExpansionQ'
 * '<S225>' : 'softMBD/FCS/filters/Subsystem/x,y,z,dy,dy,dz/z,dz/Kalman Filter1/ScalarExpansionR'
 * '<S226>' : 'softMBD/FCS/filters/Subsystem/x,y,z,dy,dy,dz/z,dz/Kalman Filter1/UseCurrentEstimator'
 * '<S227>' : 'softMBD/FCS/filters/Subsystem/x,y,z,dy,dy,dz/z,dz/Kalman Filter1/checkA'
 * '<S228>' : 'softMBD/FCS/filters/Subsystem/x,y,z,dy,dy,dz/z,dz/Kalman Filter1/checkB'
 * '<S229>' : 'softMBD/FCS/filters/Subsystem/x,y,z,dy,dy,dz/z,dz/Kalman Filter1/checkC'
 * '<S230>' : 'softMBD/FCS/filters/Subsystem/x,y,z,dy,dy,dz/z,dz/Kalman Filter1/checkD'
 * '<S231>' : 'softMBD/FCS/filters/Subsystem/x,y,z,dy,dy,dz/z,dz/Kalman Filter1/checkEnable'
 * '<S232>' : 'softMBD/FCS/filters/Subsystem/x,y,z,dy,dy,dz/z,dz/Kalman Filter1/checkG'
 * '<S233>' : 'softMBD/FCS/filters/Subsystem/x,y,z,dy,dy,dz/z,dz/Kalman Filter1/checkH'
 * '<S234>' : 'softMBD/FCS/filters/Subsystem/x,y,z,dy,dy,dz/z,dz/Kalman Filter1/checkN'
 * '<S235>' : 'softMBD/FCS/filters/Subsystem/x,y,z,dy,dy,dz/z,dz/Kalman Filter1/checkP0'
 * '<S236>' : 'softMBD/FCS/filters/Subsystem/x,y,z,dy,dy,dz/z,dz/Kalman Filter1/checkQ'
 * '<S237>' : 'softMBD/FCS/filters/Subsystem/x,y,z,dy,dy,dz/z,dz/Kalman Filter1/checkR'
 * '<S238>' : 'softMBD/FCS/filters/Subsystem/x,y,z,dy,dy,dz/z,dz/Kalman Filter1/checkReset'
 * '<S239>' : 'softMBD/FCS/filters/Subsystem/x,y,z,dy,dy,dz/z,dz/Kalman Filter1/checkX0'
 * '<S240>' : 'softMBD/FCS/filters/Subsystem/x,y,z,dy,dy,dz/z,dz/Kalman Filter1/checku'
 * '<S241>' : 'softMBD/FCS/filters/Subsystem/x,y,z,dy,dy,dz/z,dz/Kalman Filter1/checky'
 * '<S242>' : 'softMBD/FCS/filters/Subsystem/x,y,z,dy,dy,dz/z,dz/Kalman Filter1/CalculatePL/DataTypeConversionL'
 * '<S243>' : 'softMBD/FCS/filters/Subsystem/x,y,z,dy,dy,dz/z,dz/Kalman Filter1/CalculatePL/DataTypeConversionM'
 * '<S244>' : 'softMBD/FCS/filters/Subsystem/x,y,z,dy,dy,dz/z,dz/Kalman Filter1/CalculatePL/DataTypeConversionP'
 * '<S245>' : 'softMBD/FCS/filters/Subsystem/x,y,z,dy,dy,dz/z,dz/Kalman Filter1/CalculatePL/DataTypeConversionZ'
 * '<S246>' : 'softMBD/FCS/filters/Subsystem/x,y,z,dy,dy,dz/z,dz/Kalman Filter1/CalculatePL/Ground'
 * '<S247>' : 'softMBD/FCS/filters/Subsystem/x,y,z,dy,dy,dz/z,dz/Kalman Filter1/CalculateYhat/Ground'
 * '<S248>' : 'softMBD/FCS/filters/Subsystem/x,y,z,dy,dy,dz/z,dz/Kalman Filter1/CovarianceOutputConfigurator/decideOutput'
 * '<S249>' : 'softMBD/FCS/filters/Subsystem/x,y,z,dy,dy,dz/z,dz/Kalman Filter1/CovarianceOutputConfigurator/decideOutput/SqrtUsedFcn'
 * '<S250>' : 'softMBD/FCS/filters/Subsystem/x,y,z,dy,dy,dz/z,dz/Kalman Filter1/Observer/MeasurementUpdate'
 * '<S251>' : 'softMBD/FCS/filters/Subsystem/x,y,z,dy,dy,dz/z,dz/Kalman Filter1/ReducedQRN/Ground'
 * '<S252>' : 'softMBD/FCS/filters/Subsystem/x,y,z,dy,dy,dz/z,dz/Kalman Filter1/UseCurrentEstimator/Enabled Subsystem'
 * '<S253>' : 'softMBD/FCS/filters/Subsystem1/pitch_kalman'
 * '<S254>' : 'softMBD/FCS/filters/Subsystem1/roll_kalman'
 * '<S255>' : 'softMBD/FCS/filters/Subsystem1/yaw_filter'
 * '<S256>' : 'softMBD/FCS/filters/Subsystem1/pitch_kalman/Kalman Filter2'
 * '<S257>' : 'softMBD/FCS/filters/Subsystem1/pitch_kalman/Kalman Filter2/CalculatePL'
 * '<S258>' : 'softMBD/FCS/filters/Subsystem1/pitch_kalman/Kalman Filter2/CalculateYhat'
 * '<S259>' : 'softMBD/FCS/filters/Subsystem1/pitch_kalman/Kalman Filter2/CovarianceOutputConfigurator'
 * '<S260>' : 'softMBD/FCS/filters/Subsystem1/pitch_kalman/Kalman Filter2/DataTypeConversionA'
 * '<S261>' : 'softMBD/FCS/filters/Subsystem1/pitch_kalman/Kalman Filter2/DataTypeConversionB'
 * '<S262>' : 'softMBD/FCS/filters/Subsystem1/pitch_kalman/Kalman Filter2/DataTypeConversionC'
 * '<S263>' : 'softMBD/FCS/filters/Subsystem1/pitch_kalman/Kalman Filter2/DataTypeConversionD'
 * '<S264>' : 'softMBD/FCS/filters/Subsystem1/pitch_kalman/Kalman Filter2/DataTypeConversionEnable'
 * '<S265>' : 'softMBD/FCS/filters/Subsystem1/pitch_kalman/Kalman Filter2/DataTypeConversionG'
 * '<S266>' : 'softMBD/FCS/filters/Subsystem1/pitch_kalman/Kalman Filter2/DataTypeConversionH'
 * '<S267>' : 'softMBD/FCS/filters/Subsystem1/pitch_kalman/Kalman Filter2/DataTypeConversionN'
 * '<S268>' : 'softMBD/FCS/filters/Subsystem1/pitch_kalman/Kalman Filter2/DataTypeConversionP'
 * '<S269>' : 'softMBD/FCS/filters/Subsystem1/pitch_kalman/Kalman Filter2/DataTypeConversionP0'
 * '<S270>' : 'softMBD/FCS/filters/Subsystem1/pitch_kalman/Kalman Filter2/DataTypeConversionQ'
 * '<S271>' : 'softMBD/FCS/filters/Subsystem1/pitch_kalman/Kalman Filter2/DataTypeConversionR'
 * '<S272>' : 'softMBD/FCS/filters/Subsystem1/pitch_kalman/Kalman Filter2/DataTypeConversionReset'
 * '<S273>' : 'softMBD/FCS/filters/Subsystem1/pitch_kalman/Kalman Filter2/DataTypeConversionX'
 * '<S274>' : 'softMBD/FCS/filters/Subsystem1/pitch_kalman/Kalman Filter2/DataTypeConversionX0'
 * '<S275>' : 'softMBD/FCS/filters/Subsystem1/pitch_kalman/Kalman Filter2/DataTypeConversionu'
 * '<S276>' : 'softMBD/FCS/filters/Subsystem1/pitch_kalman/Kalman Filter2/MemoryP'
 * '<S277>' : 'softMBD/FCS/filters/Subsystem1/pitch_kalman/Kalman Filter2/Observer'
 * '<S278>' : 'softMBD/FCS/filters/Subsystem1/pitch_kalman/Kalman Filter2/ReducedQRN'
 * '<S279>' : 'softMBD/FCS/filters/Subsystem1/pitch_kalman/Kalman Filter2/Reset'
 * '<S280>' : 'softMBD/FCS/filters/Subsystem1/pitch_kalman/Kalman Filter2/Reshapeyhat'
 * '<S281>' : 'softMBD/FCS/filters/Subsystem1/pitch_kalman/Kalman Filter2/ScalarExpansionP0'
 * '<S282>' : 'softMBD/FCS/filters/Subsystem1/pitch_kalman/Kalman Filter2/ScalarExpansionQ'
 * '<S283>' : 'softMBD/FCS/filters/Subsystem1/pitch_kalman/Kalman Filter2/ScalarExpansionR'
 * '<S284>' : 'softMBD/FCS/filters/Subsystem1/pitch_kalman/Kalman Filter2/UseCurrentEstimator'
 * '<S285>' : 'softMBD/FCS/filters/Subsystem1/pitch_kalman/Kalman Filter2/checkA'
 * '<S286>' : 'softMBD/FCS/filters/Subsystem1/pitch_kalman/Kalman Filter2/checkB'
 * '<S287>' : 'softMBD/FCS/filters/Subsystem1/pitch_kalman/Kalman Filter2/checkC'
 * '<S288>' : 'softMBD/FCS/filters/Subsystem1/pitch_kalman/Kalman Filter2/checkD'
 * '<S289>' : 'softMBD/FCS/filters/Subsystem1/pitch_kalman/Kalman Filter2/checkEnable'
 * '<S290>' : 'softMBD/FCS/filters/Subsystem1/pitch_kalman/Kalman Filter2/checkG'
 * '<S291>' : 'softMBD/FCS/filters/Subsystem1/pitch_kalman/Kalman Filter2/checkH'
 * '<S292>' : 'softMBD/FCS/filters/Subsystem1/pitch_kalman/Kalman Filter2/checkN'
 * '<S293>' : 'softMBD/FCS/filters/Subsystem1/pitch_kalman/Kalman Filter2/checkP0'
 * '<S294>' : 'softMBD/FCS/filters/Subsystem1/pitch_kalman/Kalman Filter2/checkQ'
 * '<S295>' : 'softMBD/FCS/filters/Subsystem1/pitch_kalman/Kalman Filter2/checkR'
 * '<S296>' : 'softMBD/FCS/filters/Subsystem1/pitch_kalman/Kalman Filter2/checkReset'
 * '<S297>' : 'softMBD/FCS/filters/Subsystem1/pitch_kalman/Kalman Filter2/checkX0'
 * '<S298>' : 'softMBD/FCS/filters/Subsystem1/pitch_kalman/Kalman Filter2/checku'
 * '<S299>' : 'softMBD/FCS/filters/Subsystem1/pitch_kalman/Kalman Filter2/checky'
 * '<S300>' : 'softMBD/FCS/filters/Subsystem1/pitch_kalman/Kalman Filter2/CalculatePL/DataTypeConversionL'
 * '<S301>' : 'softMBD/FCS/filters/Subsystem1/pitch_kalman/Kalman Filter2/CalculatePL/DataTypeConversionM'
 * '<S302>' : 'softMBD/FCS/filters/Subsystem1/pitch_kalman/Kalman Filter2/CalculatePL/DataTypeConversionP'
 * '<S303>' : 'softMBD/FCS/filters/Subsystem1/pitch_kalman/Kalman Filter2/CalculatePL/DataTypeConversionZ'
 * '<S304>' : 'softMBD/FCS/filters/Subsystem1/pitch_kalman/Kalman Filter2/CalculatePL/Ground'
 * '<S305>' : 'softMBD/FCS/filters/Subsystem1/pitch_kalman/Kalman Filter2/CalculateYhat/Ground'
 * '<S306>' : 'softMBD/FCS/filters/Subsystem1/pitch_kalman/Kalman Filter2/CovarianceOutputConfigurator/decideOutput'
 * '<S307>' : 'softMBD/FCS/filters/Subsystem1/pitch_kalman/Kalman Filter2/CovarianceOutputConfigurator/decideOutput/SqrtUsedFcn'
 * '<S308>' : 'softMBD/FCS/filters/Subsystem1/pitch_kalman/Kalman Filter2/Observer/MeasurementUpdate'
 * '<S309>' : 'softMBD/FCS/filters/Subsystem1/pitch_kalman/Kalman Filter2/ReducedQRN/Ground'
 * '<S310>' : 'softMBD/FCS/filters/Subsystem1/pitch_kalman/Kalman Filter2/UseCurrentEstimator/Enabled Subsystem'
 * '<S311>' : 'softMBD/FCS/filters/Subsystem1/roll_kalman/Kalman Filter1'
 * '<S312>' : 'softMBD/FCS/filters/Subsystem1/roll_kalman/Kalman Filter1/CalculatePL'
 * '<S313>' : 'softMBD/FCS/filters/Subsystem1/roll_kalman/Kalman Filter1/CalculateYhat'
 * '<S314>' : 'softMBD/FCS/filters/Subsystem1/roll_kalman/Kalman Filter1/CovarianceOutputConfigurator'
 * '<S315>' : 'softMBD/FCS/filters/Subsystem1/roll_kalman/Kalman Filter1/DataTypeConversionA'
 * '<S316>' : 'softMBD/FCS/filters/Subsystem1/roll_kalman/Kalman Filter1/DataTypeConversionB'
 * '<S317>' : 'softMBD/FCS/filters/Subsystem1/roll_kalman/Kalman Filter1/DataTypeConversionC'
 * '<S318>' : 'softMBD/FCS/filters/Subsystem1/roll_kalman/Kalman Filter1/DataTypeConversionD'
 * '<S319>' : 'softMBD/FCS/filters/Subsystem1/roll_kalman/Kalman Filter1/DataTypeConversionEnable'
 * '<S320>' : 'softMBD/FCS/filters/Subsystem1/roll_kalman/Kalman Filter1/DataTypeConversionG'
 * '<S321>' : 'softMBD/FCS/filters/Subsystem1/roll_kalman/Kalman Filter1/DataTypeConversionH'
 * '<S322>' : 'softMBD/FCS/filters/Subsystem1/roll_kalman/Kalman Filter1/DataTypeConversionN'
 * '<S323>' : 'softMBD/FCS/filters/Subsystem1/roll_kalman/Kalman Filter1/DataTypeConversionP'
 * '<S324>' : 'softMBD/FCS/filters/Subsystem1/roll_kalman/Kalman Filter1/DataTypeConversionP0'
 * '<S325>' : 'softMBD/FCS/filters/Subsystem1/roll_kalman/Kalman Filter1/DataTypeConversionQ'
 * '<S326>' : 'softMBD/FCS/filters/Subsystem1/roll_kalman/Kalman Filter1/DataTypeConversionR'
 * '<S327>' : 'softMBD/FCS/filters/Subsystem1/roll_kalman/Kalman Filter1/DataTypeConversionReset'
 * '<S328>' : 'softMBD/FCS/filters/Subsystem1/roll_kalman/Kalman Filter1/DataTypeConversionX'
 * '<S329>' : 'softMBD/FCS/filters/Subsystem1/roll_kalman/Kalman Filter1/DataTypeConversionX0'
 * '<S330>' : 'softMBD/FCS/filters/Subsystem1/roll_kalman/Kalman Filter1/DataTypeConversionu'
 * '<S331>' : 'softMBD/FCS/filters/Subsystem1/roll_kalman/Kalman Filter1/MemoryP'
 * '<S332>' : 'softMBD/FCS/filters/Subsystem1/roll_kalman/Kalman Filter1/Observer'
 * '<S333>' : 'softMBD/FCS/filters/Subsystem1/roll_kalman/Kalman Filter1/ReducedQRN'
 * '<S334>' : 'softMBD/FCS/filters/Subsystem1/roll_kalman/Kalman Filter1/Reset'
 * '<S335>' : 'softMBD/FCS/filters/Subsystem1/roll_kalman/Kalman Filter1/Reshapeyhat'
 * '<S336>' : 'softMBD/FCS/filters/Subsystem1/roll_kalman/Kalman Filter1/ScalarExpansionP0'
 * '<S337>' : 'softMBD/FCS/filters/Subsystem1/roll_kalman/Kalman Filter1/ScalarExpansionQ'
 * '<S338>' : 'softMBD/FCS/filters/Subsystem1/roll_kalman/Kalman Filter1/ScalarExpansionR'
 * '<S339>' : 'softMBD/FCS/filters/Subsystem1/roll_kalman/Kalman Filter1/UseCurrentEstimator'
 * '<S340>' : 'softMBD/FCS/filters/Subsystem1/roll_kalman/Kalman Filter1/checkA'
 * '<S341>' : 'softMBD/FCS/filters/Subsystem1/roll_kalman/Kalman Filter1/checkB'
 * '<S342>' : 'softMBD/FCS/filters/Subsystem1/roll_kalman/Kalman Filter1/checkC'
 * '<S343>' : 'softMBD/FCS/filters/Subsystem1/roll_kalman/Kalman Filter1/checkD'
 * '<S344>' : 'softMBD/FCS/filters/Subsystem1/roll_kalman/Kalman Filter1/checkEnable'
 * '<S345>' : 'softMBD/FCS/filters/Subsystem1/roll_kalman/Kalman Filter1/checkG'
 * '<S346>' : 'softMBD/FCS/filters/Subsystem1/roll_kalman/Kalman Filter1/checkH'
 * '<S347>' : 'softMBD/FCS/filters/Subsystem1/roll_kalman/Kalman Filter1/checkN'
 * '<S348>' : 'softMBD/FCS/filters/Subsystem1/roll_kalman/Kalman Filter1/checkP0'
 * '<S349>' : 'softMBD/FCS/filters/Subsystem1/roll_kalman/Kalman Filter1/checkQ'
 * '<S350>' : 'softMBD/FCS/filters/Subsystem1/roll_kalman/Kalman Filter1/checkR'
 * '<S351>' : 'softMBD/FCS/filters/Subsystem1/roll_kalman/Kalman Filter1/checkReset'
 * '<S352>' : 'softMBD/FCS/filters/Subsystem1/roll_kalman/Kalman Filter1/checkX0'
 * '<S353>' : 'softMBD/FCS/filters/Subsystem1/roll_kalman/Kalman Filter1/checku'
 * '<S354>' : 'softMBD/FCS/filters/Subsystem1/roll_kalman/Kalman Filter1/checky'
 * '<S355>' : 'softMBD/FCS/filters/Subsystem1/roll_kalman/Kalman Filter1/CalculatePL/DataTypeConversionL'
 * '<S356>' : 'softMBD/FCS/filters/Subsystem1/roll_kalman/Kalman Filter1/CalculatePL/DataTypeConversionM'
 * '<S357>' : 'softMBD/FCS/filters/Subsystem1/roll_kalman/Kalman Filter1/CalculatePL/DataTypeConversionP'
 * '<S358>' : 'softMBD/FCS/filters/Subsystem1/roll_kalman/Kalman Filter1/CalculatePL/DataTypeConversionZ'
 * '<S359>' : 'softMBD/FCS/filters/Subsystem1/roll_kalman/Kalman Filter1/CalculatePL/Ground'
 * '<S360>' : 'softMBD/FCS/filters/Subsystem1/roll_kalman/Kalman Filter1/CalculateYhat/Ground'
 * '<S361>' : 'softMBD/FCS/filters/Subsystem1/roll_kalman/Kalman Filter1/CovarianceOutputConfigurator/decideOutput'
 * '<S362>' : 'softMBD/FCS/filters/Subsystem1/roll_kalman/Kalman Filter1/CovarianceOutputConfigurator/decideOutput/SqrtUsedFcn'
 * '<S363>' : 'softMBD/FCS/filters/Subsystem1/roll_kalman/Kalman Filter1/Observer/MeasurementUpdate'
 * '<S364>' : 'softMBD/FCS/filters/Subsystem1/roll_kalman/Kalman Filter1/ReducedQRN/Ground'
 * '<S365>' : 'softMBD/FCS/filters/Subsystem1/roll_kalman/Kalman Filter1/UseCurrentEstimator/Enabled Subsystem'
 * '<S366>' : 'softMBD/FCS/filters/pqr_LPF/Transfer Fcn1'
 * '<S367>' : 'softMBD/FCS/filters/pqr_LPF/Transfer Fcn2'
 * '<S368>' : 'softMBD/FCS/filters/pqr_LPF/Transfer Fcn3'
 * '<S369>' : 'softMBD/FCS/filters/pqr_LPF1/Transfer Fcn1'
 * '<S370>' : 'softMBD/FCS/filters/pqr_LPF1/Transfer Fcn2'
 * '<S371>' : 'softMBD/FCS/filters/pqr_LPF1/Transfer Fcn3'
 */
#endif                                 /* FCS_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
