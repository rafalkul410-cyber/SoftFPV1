/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: FCS.h
 *
 * Code generated for Simulink model 'FCS'.
 *
 * Model version                  : 1.24
 * Simulink Coder version         : 25.2 (R2025b) 28-Jul-2025
 * C/C++ source code generated on : Fri Aug 28 11:05:10 2026
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

/* Block signals and states (default storage) for system '<S204>/MeasurementUpdate' */
typedef struct {
  boolean_T MeasurementUpdate_MODE;    /* '<S204>/MeasurementUpdate' */
} DW_MeasurementUpdate;

/* Block signals and states (default storage) for system '<S211>/Enabled Subsystem' */
typedef struct {
  boolean_T EnabledSubsystem_MODE;     /* '<S211>/Enabled Subsystem' */
} DW_EnabledSubsystem;

/* Block signals and states (default storage) for system '<Root>' */
typedef struct {
  DW_EnabledSubsystem EnabledSubsystem_i;/* '<S324>/Enabled Subsystem' */
  DW_MeasurementUpdate MeasurementUpdate_e;/* '<S317>/MeasurementUpdate' */
  DW_EnabledSubsystem EnabledSubsystem_p;/* '<S269>/Enabled Subsystem' */
  DW_MeasurementUpdate MeasurementUpdate_p;/* '<S262>/MeasurementUpdate' */
  DW_EnabledSubsystem EnabledSubsystem_e;/* '<S211>/Enabled Subsystem' */
  DW_MeasurementUpdate MeasurementUpdate_g;/* '<S204>/MeasurementUpdate' */
  real32_T Product2[2];                /* '<S350>/Product2' */
  real32_T Product3[2];                /* '<S348>/Product3' */
  real32_T Product2_d[2];              /* '<S295>/Product2' */
  real32_T Product3_m[2];              /* '<S293>/Product3' */
  real32_T Product2_b[2];              /* '<S237>/Product2' */
  real32_T Product3_a[2];              /* '<S235>/Product3' */
  real32_T MemoryX_DSTATE[2];          /* '<S296>/MemoryX' */
  real32_T MemoryX_DSTATE_m[2];        /* '<S241>/MemoryX' */
  real32_T MemoryX_DSTATE_h[2];        /* '<S183>/MemoryX' */
  real32_T Integrator_DSTATE_n[2];     /* '<S45>/Integrator' */
  real32_T Filter_DSTATE_j[2];         /* '<S40>/Filter' */
  real32_T Integrator_DSTATE_b[2];     /* '<S99>/Integrator' */
  real32_T Filter_DSTATE_e[2];         /* '<S94>/Filter' */
  real32_T PrevY_g[2];                 /* '<S2>/Rate Limiter' */
  real32_T DiscreteTransferFcn_states; /* '<S354>/Discrete Transfer Fcn' */
  real32_T DiscreteTransferFcn_states_l;/* '<S355>/Discrete Transfer Fcn' */
  real32_T DiscreteTransferFcn_states_o;/* '<S356>/Discrete Transfer Fcn' */
  real32_T Integrator1_DSTATE;         /* '<S240>/Integrator1' */
  real32_T DiscreteTransferFcn_states_f;/* '<S175>/Discrete Transfer Fcn' */
  real32_T UnitDelay_DSTATE;           /* '<S6>/Unit Delay' */
  real32_T Integrator2_DSTATE;         /* '<S6>/Integrator2' */
  real32_T DiscreteTransferFcn_states_ll;/* '<S352>/Discrete Transfer Fcn' */
  real32_T Integrator_DSTATE;          /* '<S154>/Integrator' */
  real32_T Filter_DSTATE;              /* '<S149>/Filter' */
  real32_T DiscreteTransferFcn_states_n;/* '<S353>/Discrete Transfer Fcn' */
  real32_T DiscreteTransferFcn_states_nu;/* '<S351>/Discrete Transfer Fcn' */
  real32_T Integrator5_DSTATE;         /* '<S181>/Integrator5' */
  real32_T Integrator1_DSTATE_p;       /* '<S181>/Integrator1' */
  real32_T Integrator4_DSTATE;         /* '<S181>/Integrator4' */
  real32_T Integrator2_DSTATE_g;       /* '<S181>/Integrator2' */
  real32_T PrevY;                      /* '<S6>/Rate Limiter' */
  real32_T PrevY_l;                    /* '<S2>/Rate Limiter1' */
  int8_T Integrator2_PrevResetState;   /* '<S6>/Integrator2' */
  boolean_T icLoad;                    /* '<S296>/MemoryX' */
  boolean_T icLoad_e;                  /* '<S241>/MemoryX' */
  boolean_T icLoad_h;                  /* '<S183>/MemoryX' */
} DW;

/* Invariant block signals (default storage) */
typedef struct {
  const real32_T Conversion[2];        /* '<S227>/Conversion' */
  const real32_T Conversion_n[2];      /* '<S228>/Conversion' */
  const real32_T Conversion_e[4];      /* '<S230>/Conversion' */
  const real32_T Conversion_i[2];      /* '<S285>/Conversion' */
  const real32_T Conversion_p[2];      /* '<S286>/Conversion' */
  const real32_T Conversion_o[4];      /* '<S288>/Conversion' */
  const real32_T Conversion_g[2];      /* '<S340>/Conversion' */
  const real32_T Conversion_b[2];      /* '<S341>/Conversion' */
  const real32_T Conversion_d[4];      /* '<S343>/Conversion' */
} ConstB;

/* Constant parameters (default storage) */
typedef struct {
  /* Computed Parameter: TorqueTotalThrustToThrustPerMot
   * Referenced by: '<S5>/TorqueTotalThrustToThrustPerMotor'
   */
  real32_T TorqueTotalThrustToThrustPerMot[16];

  /* Computed Parameter: Constant_Value_j
   * Referenced by: '<S179>/Constant'
   */
  real32_T Constant_Value_j[3];

  /* Pooled Parameter (Expression: )
   * Referenced by:
   *   '<S241>/C'
   *   '<S296>/C'
   *   '<S183>/C'
   */
  real32_T pooled8[2];
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
 * Block '<S227>/Data Type Duplicate' : Unused code path elimination
 * Block '<S228>/Data Type Duplicate' : Unused code path elimination
 * Block '<S229>/Conversion' : Unused code path elimination
 * Block '<S229>/Data Type Duplicate' : Unused code path elimination
 * Block '<S230>/Data Type Duplicate' : Unused code path elimination
 * Block '<S187>/Data Type Duplicate' : Unused code path elimination
 * Block '<S188>/Data Type Duplicate' : Unused code path elimination
 * Block '<S189>/Data Type Duplicate' : Unused code path elimination
 * Block '<S190>/Data Type Duplicate' : Unused code path elimination
 * Block '<S192>/Data Type Duplicate' : Unused code path elimination
 * Block '<S193>/Data Type Duplicate' : Unused code path elimination
 * Block '<S194>/Data Type Duplicate' : Unused code path elimination
 * Block '<S195>/Conversion' : Unused code path elimination
 * Block '<S195>/Data Type Duplicate' : Unused code path elimination
 * Block '<S196>/Data Type Duplicate' : Unused code path elimination
 * Block '<S197>/Data Type Duplicate' : Unused code path elimination
 * Block '<S198>/Data Type Duplicate' : Unused code path elimination
 * Block '<S200>/Data Type Duplicate' : Unused code path elimination
 * Block '<S201>/Data Type Duplicate' : Unused code path elimination
 * Block '<S183>/G' : Unused code path elimination
 * Block '<S183>/H' : Unused code path elimination
 * Block '<S183>/N' : Unused code path elimination
 * Block '<S183>/P0' : Unused code path elimination
 * Block '<S183>/Q' : Unused code path elimination
 * Block '<S183>/R' : Unused code path elimination
 * Block '<S225>/CheckSignalProperties' : Unused code path elimination
 * Block '<S226>/CheckSignalProperties' : Unused code path elimination
 * Block '<S285>/Data Type Duplicate' : Unused code path elimination
 * Block '<S286>/Data Type Duplicate' : Unused code path elimination
 * Block '<S287>/Conversion' : Unused code path elimination
 * Block '<S287>/Data Type Duplicate' : Unused code path elimination
 * Block '<S288>/Data Type Duplicate' : Unused code path elimination
 * Block '<S245>/Data Type Duplicate' : Unused code path elimination
 * Block '<S246>/Data Type Duplicate' : Unused code path elimination
 * Block '<S247>/Data Type Duplicate' : Unused code path elimination
 * Block '<S248>/Data Type Duplicate' : Unused code path elimination
 * Block '<S250>/Data Type Duplicate' : Unused code path elimination
 * Block '<S251>/Data Type Duplicate' : Unused code path elimination
 * Block '<S252>/Data Type Duplicate' : Unused code path elimination
 * Block '<S253>/Conversion' : Unused code path elimination
 * Block '<S253>/Data Type Duplicate' : Unused code path elimination
 * Block '<S254>/Data Type Duplicate' : Unused code path elimination
 * Block '<S255>/Data Type Duplicate' : Unused code path elimination
 * Block '<S256>/Data Type Duplicate' : Unused code path elimination
 * Block '<S258>/Data Type Duplicate' : Unused code path elimination
 * Block '<S259>/Data Type Duplicate' : Unused code path elimination
 * Block '<S241>/G' : Unused code path elimination
 * Block '<S241>/H' : Unused code path elimination
 * Block '<S241>/N' : Unused code path elimination
 * Block '<S241>/P0' : Unused code path elimination
 * Block '<S241>/Q' : Unused code path elimination
 * Block '<S241>/R' : Unused code path elimination
 * Block '<S283>/CheckSignalProperties' : Unused code path elimination
 * Block '<S284>/CheckSignalProperties' : Unused code path elimination
 * Block '<S340>/Data Type Duplicate' : Unused code path elimination
 * Block '<S341>/Data Type Duplicate' : Unused code path elimination
 * Block '<S342>/Conversion' : Unused code path elimination
 * Block '<S342>/Data Type Duplicate' : Unused code path elimination
 * Block '<S343>/Data Type Duplicate' : Unused code path elimination
 * Block '<S300>/Data Type Duplicate' : Unused code path elimination
 * Block '<S301>/Data Type Duplicate' : Unused code path elimination
 * Block '<S302>/Data Type Duplicate' : Unused code path elimination
 * Block '<S303>/Data Type Duplicate' : Unused code path elimination
 * Block '<S305>/Data Type Duplicate' : Unused code path elimination
 * Block '<S306>/Data Type Duplicate' : Unused code path elimination
 * Block '<S307>/Data Type Duplicate' : Unused code path elimination
 * Block '<S308>/Conversion' : Unused code path elimination
 * Block '<S308>/Data Type Duplicate' : Unused code path elimination
 * Block '<S309>/Data Type Duplicate' : Unused code path elimination
 * Block '<S310>/Data Type Duplicate' : Unused code path elimination
 * Block '<S311>/Data Type Duplicate' : Unused code path elimination
 * Block '<S313>/Data Type Duplicate' : Unused code path elimination
 * Block '<S314>/Data Type Duplicate' : Unused code path elimination
 * Block '<S296>/G' : Unused code path elimination
 * Block '<S296>/H' : Unused code path elimination
 * Block '<S296>/N' : Unused code path elimination
 * Block '<S296>/P0' : Unused code path elimination
 * Block '<S296>/Q' : Unused code path elimination
 * Block '<S296>/R' : Unused code path elimination
 * Block '<S338>/CheckSignalProperties' : Unused code path elimination
 * Block '<S338>/Data Type Conversion3' : Unused code path elimination
 * Block '<S339>/CheckSignalProperties' : Unused code path elimination
 * Block '<S174>/Discrete Transfer Fcn' : Unused code path elimination
 * Block '<S176>/Discrete Transfer Fcn' : Unused code path elimination
 * Block '<S172>/Data Type Conversion3' : Eliminate redundant data type conversion
 * Block '<S200>/Conversion' : Eliminate redundant data type conversion
 * Block '<S204>/Reshape' : Reshape block reduction
 * Block '<S183>/ReshapeX0' : Reshape block reduction
 * Block '<S183>/Reshapeu' : Reshape block reduction
 * Block '<S183>/Reshapexhat' : Reshape block reduction
 * Block '<S183>/Reshapey' : Reshape block reduction
 * Block '<S182>/Rate Transition' : Eliminated since input and output rates are identical
 * Block '<S182>/Rate Transition1' : Eliminated since input and output rates are identical
 * Block '<S238>/Data Type Conversion3' : Eliminate redundant data type conversion
 * Block '<S258>/Conversion' : Eliminate redundant data type conversion
 * Block '<S262>/Reshape' : Reshape block reduction
 * Block '<S241>/ReshapeX0' : Reshape block reduction
 * Block '<S241>/Reshapeu' : Reshape block reduction
 * Block '<S241>/Reshapexhat' : Reshape block reduction
 * Block '<S241>/Reshapey' : Reshape block reduction
 * Block '<S238>/Rate Transition' : Eliminated since input and output rates are identical
 * Block '<S238>/Rate Transition1' : Eliminated since input and output rates are identical
 * Block '<S239>/Data Type Conversion3' : Eliminate redundant data type conversion
 * Block '<S313>/Conversion' : Eliminate redundant data type conversion
 * Block '<S317>/Reshape' : Reshape block reduction
 * Block '<S296>/ReshapeX0' : Reshape block reduction
 * Block '<S296>/Reshapeu' : Reshape block reduction
 * Block '<S296>/Reshapexhat' : Reshape block reduction
 * Block '<S296>/Reshapey' : Reshape block reduction
 * Block '<S239>/Rate Transition' : Eliminated since input and output rates are identical
 * Block '<S239>/Rate Transition1' : Eliminated since input and output rates are identical
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
 * '<S9>'   : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller'
 * '<S10>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller2'
 * '<S11>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller/Anti-windup'
 * '<S12>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller/D Gain'
 * '<S13>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller/External Derivative'
 * '<S14>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller/Filter'
 * '<S15>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller/Filter ICs'
 * '<S16>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller/I Gain'
 * '<S17>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller/Ideal P Gain'
 * '<S18>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller/Ideal P Gain Fdbk'
 * '<S19>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller/Integrator'
 * '<S20>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller/Integrator ICs'
 * '<S21>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller/N Copy'
 * '<S22>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller/N Gain'
 * '<S23>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller/P Copy'
 * '<S24>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller/Parallel P Gain'
 * '<S25>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller/Reset Signal'
 * '<S26>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller/Saturation'
 * '<S27>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller/Saturation Fdbk'
 * '<S28>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller/Sum'
 * '<S29>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller/Sum Fdbk'
 * '<S30>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller/Tracking Mode'
 * '<S31>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller/Tracking Mode Sum'
 * '<S32>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller/Tsamp - Integral'
 * '<S33>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller/Tsamp - Ngain'
 * '<S34>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller/postSat Signal'
 * '<S35>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller/preInt Signal'
 * '<S36>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller/preSat Signal'
 * '<S37>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller/Anti-windup/Passthrough'
 * '<S38>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller/D Gain/Internal Parameters'
 * '<S39>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller/External Derivative/Error'
 * '<S40>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller/Filter/Disc. Forward Euler Filter'
 * '<S41>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller/Filter ICs/Internal IC - Filter'
 * '<S42>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller/I Gain/Internal Parameters'
 * '<S43>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller/Ideal P Gain/Passthrough'
 * '<S44>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller/Ideal P Gain Fdbk/Disabled'
 * '<S45>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller/Integrator/Discrete'
 * '<S46>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller/Integrator ICs/Internal IC'
 * '<S47>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller/N Copy/Disabled'
 * '<S48>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller/N Gain/Internal Parameters'
 * '<S49>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller/P Copy/Disabled'
 * '<S50>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller/Parallel P Gain/Internal Parameters'
 * '<S51>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller/Reset Signal/Disabled'
 * '<S52>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller/Saturation/Passthrough'
 * '<S53>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller/Saturation Fdbk/Disabled'
 * '<S54>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller/Sum/Sum_PID'
 * '<S55>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller/Sum Fdbk/Disabled'
 * '<S56>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller/Tracking Mode/Disabled'
 * '<S57>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller/Tracking Mode Sum/Passthrough'
 * '<S58>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller/Tsamp - Integral/TsSignalSpecification'
 * '<S59>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller/Tsamp - Ngain/Passthrough'
 * '<S60>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller/postSat Signal/Forward_Path'
 * '<S61>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller/preInt Signal/Internal PreInt'
 * '<S62>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller/preSat Signal/Forward_Path'
 * '<S63>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller2/Anti-windup'
 * '<S64>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller2/D Gain'
 * '<S65>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller2/External Derivative'
 * '<S66>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller2/Filter'
 * '<S67>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller2/Filter ICs'
 * '<S68>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller2/I Gain'
 * '<S69>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller2/Ideal P Gain'
 * '<S70>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller2/Ideal P Gain Fdbk'
 * '<S71>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller2/Integrator'
 * '<S72>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller2/Integrator ICs'
 * '<S73>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller2/N Copy'
 * '<S74>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller2/N Gain'
 * '<S75>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller2/P Copy'
 * '<S76>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller2/Parallel P Gain'
 * '<S77>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller2/Reset Signal'
 * '<S78>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller2/Saturation'
 * '<S79>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller2/Saturation Fdbk'
 * '<S80>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller2/Sum'
 * '<S81>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller2/Sum Fdbk'
 * '<S82>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller2/Tracking Mode'
 * '<S83>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller2/Tracking Mode Sum'
 * '<S84>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller2/Tsamp - Integral'
 * '<S85>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller2/Tsamp - Ngain'
 * '<S86>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller2/postSat Signal'
 * '<S87>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller2/preInt Signal'
 * '<S88>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller2/preSat Signal'
 * '<S89>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller2/Anti-windup/Disc. Clamping Parallel'
 * '<S90>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller2/Anti-windup/Disc. Clamping Parallel/Dead Zone'
 * '<S91>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller2/Anti-windup/Disc. Clamping Parallel/Dead Zone/Enabled'
 * '<S92>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller2/D Gain/Internal Parameters'
 * '<S93>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller2/External Derivative/Error'
 * '<S94>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller2/Filter/Disc. Forward Euler Filter'
 * '<S95>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller2/Filter ICs/Internal IC - Filter'
 * '<S96>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller2/I Gain/Internal Parameters'
 * '<S97>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller2/Ideal P Gain/Passthrough'
 * '<S98>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller2/Ideal P Gain Fdbk/Disabled'
 * '<S99>'  : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller2/Integrator/Discrete'
 * '<S100>' : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller2/Integrator ICs/Internal IC'
 * '<S101>' : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller2/N Copy/Disabled'
 * '<S102>' : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller2/N Gain/Internal Parameters'
 * '<S103>' : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller2/P Copy/Disabled'
 * '<S104>' : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller2/Parallel P Gain/Internal Parameters'
 * '<S105>' : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller2/Reset Signal/Disabled'
 * '<S106>' : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller2/Saturation/Enabled'
 * '<S107>' : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller2/Saturation Fdbk/Disabled'
 * '<S108>' : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller2/Sum/Sum_PID'
 * '<S109>' : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller2/Sum Fdbk/Disabled'
 * '<S110>' : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller2/Tracking Mode/Disabled'
 * '<S111>' : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller2/Tracking Mode Sum/Passthrough'
 * '<S112>' : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller2/Tsamp - Integral/TsSignalSpecification'
 * '<S113>' : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller2/Tsamp - Ngain/Passthrough'
 * '<S114>' : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller2/postSat Signal/Forward_Path'
 * '<S115>' : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller2/preInt Signal/Internal PreInt'
 * '<S116>' : 'softMBD/FCS/Controller/roll_pitch_controller/PID Controller2/preSat Signal/Forward_Path'
 * '<S117>' : 'softMBD/FCS/Controller/tau_contorller/PID Controller'
 * '<S118>' : 'softMBD/FCS/Controller/tau_contorller/PID Controller/Anti-windup'
 * '<S119>' : 'softMBD/FCS/Controller/tau_contorller/PID Controller/D Gain'
 * '<S120>' : 'softMBD/FCS/Controller/tau_contorller/PID Controller/External Derivative'
 * '<S121>' : 'softMBD/FCS/Controller/tau_contorller/PID Controller/Filter'
 * '<S122>' : 'softMBD/FCS/Controller/tau_contorller/PID Controller/Filter ICs'
 * '<S123>' : 'softMBD/FCS/Controller/tau_contorller/PID Controller/I Gain'
 * '<S124>' : 'softMBD/FCS/Controller/tau_contorller/PID Controller/Ideal P Gain'
 * '<S125>' : 'softMBD/FCS/Controller/tau_contorller/PID Controller/Ideal P Gain Fdbk'
 * '<S126>' : 'softMBD/FCS/Controller/tau_contorller/PID Controller/Integrator'
 * '<S127>' : 'softMBD/FCS/Controller/tau_contorller/PID Controller/Integrator ICs'
 * '<S128>' : 'softMBD/FCS/Controller/tau_contorller/PID Controller/N Copy'
 * '<S129>' : 'softMBD/FCS/Controller/tau_contorller/PID Controller/N Gain'
 * '<S130>' : 'softMBD/FCS/Controller/tau_contorller/PID Controller/P Copy'
 * '<S131>' : 'softMBD/FCS/Controller/tau_contorller/PID Controller/Parallel P Gain'
 * '<S132>' : 'softMBD/FCS/Controller/tau_contorller/PID Controller/Reset Signal'
 * '<S133>' : 'softMBD/FCS/Controller/tau_contorller/PID Controller/Saturation'
 * '<S134>' : 'softMBD/FCS/Controller/tau_contorller/PID Controller/Saturation Fdbk'
 * '<S135>' : 'softMBD/FCS/Controller/tau_contorller/PID Controller/Sum'
 * '<S136>' : 'softMBD/FCS/Controller/tau_contorller/PID Controller/Sum Fdbk'
 * '<S137>' : 'softMBD/FCS/Controller/tau_contorller/PID Controller/Tracking Mode'
 * '<S138>' : 'softMBD/FCS/Controller/tau_contorller/PID Controller/Tracking Mode Sum'
 * '<S139>' : 'softMBD/FCS/Controller/tau_contorller/PID Controller/Tsamp - Integral'
 * '<S140>' : 'softMBD/FCS/Controller/tau_contorller/PID Controller/Tsamp - Ngain'
 * '<S141>' : 'softMBD/FCS/Controller/tau_contorller/PID Controller/postSat Signal'
 * '<S142>' : 'softMBD/FCS/Controller/tau_contorller/PID Controller/preInt Signal'
 * '<S143>' : 'softMBD/FCS/Controller/tau_contorller/PID Controller/preSat Signal'
 * '<S144>' : 'softMBD/FCS/Controller/tau_contorller/PID Controller/Anti-windup/Disc. Clamping Parallel'
 * '<S145>' : 'softMBD/FCS/Controller/tau_contorller/PID Controller/Anti-windup/Disc. Clamping Parallel/Dead Zone'
 * '<S146>' : 'softMBD/FCS/Controller/tau_contorller/PID Controller/Anti-windup/Disc. Clamping Parallel/Dead Zone/Enabled'
 * '<S147>' : 'softMBD/FCS/Controller/tau_contorller/PID Controller/D Gain/Internal Parameters'
 * '<S148>' : 'softMBD/FCS/Controller/tau_contorller/PID Controller/External Derivative/Error'
 * '<S149>' : 'softMBD/FCS/Controller/tau_contorller/PID Controller/Filter/Disc. Forward Euler Filter'
 * '<S150>' : 'softMBD/FCS/Controller/tau_contorller/PID Controller/Filter ICs/Internal IC - Filter'
 * '<S151>' : 'softMBD/FCS/Controller/tau_contorller/PID Controller/I Gain/Internal Parameters'
 * '<S152>' : 'softMBD/FCS/Controller/tau_contorller/PID Controller/Ideal P Gain/Passthrough'
 * '<S153>' : 'softMBD/FCS/Controller/tau_contorller/PID Controller/Ideal P Gain Fdbk/Disabled'
 * '<S154>' : 'softMBD/FCS/Controller/tau_contorller/PID Controller/Integrator/Discrete'
 * '<S155>' : 'softMBD/FCS/Controller/tau_contorller/PID Controller/Integrator ICs/Internal IC'
 * '<S156>' : 'softMBD/FCS/Controller/tau_contorller/PID Controller/N Copy/Disabled'
 * '<S157>' : 'softMBD/FCS/Controller/tau_contorller/PID Controller/N Gain/Internal Parameters'
 * '<S158>' : 'softMBD/FCS/Controller/tau_contorller/PID Controller/P Copy/Disabled'
 * '<S159>' : 'softMBD/FCS/Controller/tau_contorller/PID Controller/Parallel P Gain/Internal Parameters'
 * '<S160>' : 'softMBD/FCS/Controller/tau_contorller/PID Controller/Reset Signal/Disabled'
 * '<S161>' : 'softMBD/FCS/Controller/tau_contorller/PID Controller/Saturation/Enabled'
 * '<S162>' : 'softMBD/FCS/Controller/tau_contorller/PID Controller/Saturation Fdbk/Disabled'
 * '<S163>' : 'softMBD/FCS/Controller/tau_contorller/PID Controller/Sum/Sum_PID'
 * '<S164>' : 'softMBD/FCS/Controller/tau_contorller/PID Controller/Sum Fdbk/Disabled'
 * '<S165>' : 'softMBD/FCS/Controller/tau_contorller/PID Controller/Tracking Mode/Disabled'
 * '<S166>' : 'softMBD/FCS/Controller/tau_contorller/PID Controller/Tracking Mode Sum/Passthrough'
 * '<S167>' : 'softMBD/FCS/Controller/tau_contorller/PID Controller/Tsamp - Integral/TsSignalSpecification'
 * '<S168>' : 'softMBD/FCS/Controller/tau_contorller/PID Controller/Tsamp - Ngain/Passthrough'
 * '<S169>' : 'softMBD/FCS/Controller/tau_contorller/PID Controller/postSat Signal/Forward_Path'
 * '<S170>' : 'softMBD/FCS/Controller/tau_contorller/PID Controller/preInt Signal/Internal PreInt'
 * '<S171>' : 'softMBD/FCS/Controller/tau_contorller/PID Controller/preSat Signal/Forward_Path'
 * '<S172>' : 'softMBD/FCS/filters/Subsystem'
 * '<S173>' : 'softMBD/FCS/filters/Subsystem1'
 * '<S174>' : 'softMBD/FCS/filters/Transfer Fcn'
 * '<S175>' : 'softMBD/FCS/filters/Transfer Fcn1'
 * '<S176>' : 'softMBD/FCS/filters/Transfer Fcn2'
 * '<S177>' : 'softMBD/FCS/filters/pqr_LPF'
 * '<S178>' : 'softMBD/FCS/filters/pqr_LPF1'
 * '<S179>' : 'softMBD/FCS/filters/Subsystem/body2earth'
 * '<S180>' : 'softMBD/FCS/filters/Subsystem/x,y,z,dy,dy,dz'
 * '<S181>' : 'softMBD/FCS/filters/Subsystem/x,y,z,dy,dy,dz/x.y.dx.dy'
 * '<S182>' : 'softMBD/FCS/filters/Subsystem/x,y,z,dy,dy,dz/z,dz'
 * '<S183>' : 'softMBD/FCS/filters/Subsystem/x,y,z,dy,dy,dz/z,dz/Kalman Filter1'
 * '<S184>' : 'softMBD/FCS/filters/Subsystem/x,y,z,dy,dy,dz/z,dz/Kalman Filter1/CalculatePL'
 * '<S185>' : 'softMBD/FCS/filters/Subsystem/x,y,z,dy,dy,dz/z,dz/Kalman Filter1/CalculateYhat'
 * '<S186>' : 'softMBD/FCS/filters/Subsystem/x,y,z,dy,dy,dz/z,dz/Kalman Filter1/CovarianceOutputConfigurator'
 * '<S187>' : 'softMBD/FCS/filters/Subsystem/x,y,z,dy,dy,dz/z,dz/Kalman Filter1/DataTypeConversionA'
 * '<S188>' : 'softMBD/FCS/filters/Subsystem/x,y,z,dy,dy,dz/z,dz/Kalman Filter1/DataTypeConversionB'
 * '<S189>' : 'softMBD/FCS/filters/Subsystem/x,y,z,dy,dy,dz/z,dz/Kalman Filter1/DataTypeConversionC'
 * '<S190>' : 'softMBD/FCS/filters/Subsystem/x,y,z,dy,dy,dz/z,dz/Kalman Filter1/DataTypeConversionD'
 * '<S191>' : 'softMBD/FCS/filters/Subsystem/x,y,z,dy,dy,dz/z,dz/Kalman Filter1/DataTypeConversionEnable'
 * '<S192>' : 'softMBD/FCS/filters/Subsystem/x,y,z,dy,dy,dz/z,dz/Kalman Filter1/DataTypeConversionG'
 * '<S193>' : 'softMBD/FCS/filters/Subsystem/x,y,z,dy,dy,dz/z,dz/Kalman Filter1/DataTypeConversionH'
 * '<S194>' : 'softMBD/FCS/filters/Subsystem/x,y,z,dy,dy,dz/z,dz/Kalman Filter1/DataTypeConversionN'
 * '<S195>' : 'softMBD/FCS/filters/Subsystem/x,y,z,dy,dy,dz/z,dz/Kalman Filter1/DataTypeConversionP'
 * '<S196>' : 'softMBD/FCS/filters/Subsystem/x,y,z,dy,dy,dz/z,dz/Kalman Filter1/DataTypeConversionP0'
 * '<S197>' : 'softMBD/FCS/filters/Subsystem/x,y,z,dy,dy,dz/z,dz/Kalman Filter1/DataTypeConversionQ'
 * '<S198>' : 'softMBD/FCS/filters/Subsystem/x,y,z,dy,dy,dz/z,dz/Kalman Filter1/DataTypeConversionR'
 * '<S199>' : 'softMBD/FCS/filters/Subsystem/x,y,z,dy,dy,dz/z,dz/Kalman Filter1/DataTypeConversionReset'
 * '<S200>' : 'softMBD/FCS/filters/Subsystem/x,y,z,dy,dy,dz/z,dz/Kalman Filter1/DataTypeConversionX'
 * '<S201>' : 'softMBD/FCS/filters/Subsystem/x,y,z,dy,dy,dz/z,dz/Kalman Filter1/DataTypeConversionX0'
 * '<S202>' : 'softMBD/FCS/filters/Subsystem/x,y,z,dy,dy,dz/z,dz/Kalman Filter1/DataTypeConversionu'
 * '<S203>' : 'softMBD/FCS/filters/Subsystem/x,y,z,dy,dy,dz/z,dz/Kalman Filter1/MemoryP'
 * '<S204>' : 'softMBD/FCS/filters/Subsystem/x,y,z,dy,dy,dz/z,dz/Kalman Filter1/Observer'
 * '<S205>' : 'softMBD/FCS/filters/Subsystem/x,y,z,dy,dy,dz/z,dz/Kalman Filter1/ReducedQRN'
 * '<S206>' : 'softMBD/FCS/filters/Subsystem/x,y,z,dy,dy,dz/z,dz/Kalman Filter1/Reset'
 * '<S207>' : 'softMBD/FCS/filters/Subsystem/x,y,z,dy,dy,dz/z,dz/Kalman Filter1/Reshapeyhat'
 * '<S208>' : 'softMBD/FCS/filters/Subsystem/x,y,z,dy,dy,dz/z,dz/Kalman Filter1/ScalarExpansionP0'
 * '<S209>' : 'softMBD/FCS/filters/Subsystem/x,y,z,dy,dy,dz/z,dz/Kalman Filter1/ScalarExpansionQ'
 * '<S210>' : 'softMBD/FCS/filters/Subsystem/x,y,z,dy,dy,dz/z,dz/Kalman Filter1/ScalarExpansionR'
 * '<S211>' : 'softMBD/FCS/filters/Subsystem/x,y,z,dy,dy,dz/z,dz/Kalman Filter1/UseCurrentEstimator'
 * '<S212>' : 'softMBD/FCS/filters/Subsystem/x,y,z,dy,dy,dz/z,dz/Kalman Filter1/checkA'
 * '<S213>' : 'softMBD/FCS/filters/Subsystem/x,y,z,dy,dy,dz/z,dz/Kalman Filter1/checkB'
 * '<S214>' : 'softMBD/FCS/filters/Subsystem/x,y,z,dy,dy,dz/z,dz/Kalman Filter1/checkC'
 * '<S215>' : 'softMBD/FCS/filters/Subsystem/x,y,z,dy,dy,dz/z,dz/Kalman Filter1/checkD'
 * '<S216>' : 'softMBD/FCS/filters/Subsystem/x,y,z,dy,dy,dz/z,dz/Kalman Filter1/checkEnable'
 * '<S217>' : 'softMBD/FCS/filters/Subsystem/x,y,z,dy,dy,dz/z,dz/Kalman Filter1/checkG'
 * '<S218>' : 'softMBD/FCS/filters/Subsystem/x,y,z,dy,dy,dz/z,dz/Kalman Filter1/checkH'
 * '<S219>' : 'softMBD/FCS/filters/Subsystem/x,y,z,dy,dy,dz/z,dz/Kalman Filter1/checkN'
 * '<S220>' : 'softMBD/FCS/filters/Subsystem/x,y,z,dy,dy,dz/z,dz/Kalman Filter1/checkP0'
 * '<S221>' : 'softMBD/FCS/filters/Subsystem/x,y,z,dy,dy,dz/z,dz/Kalman Filter1/checkQ'
 * '<S222>' : 'softMBD/FCS/filters/Subsystem/x,y,z,dy,dy,dz/z,dz/Kalman Filter1/checkR'
 * '<S223>' : 'softMBD/FCS/filters/Subsystem/x,y,z,dy,dy,dz/z,dz/Kalman Filter1/checkReset'
 * '<S224>' : 'softMBD/FCS/filters/Subsystem/x,y,z,dy,dy,dz/z,dz/Kalman Filter1/checkX0'
 * '<S225>' : 'softMBD/FCS/filters/Subsystem/x,y,z,dy,dy,dz/z,dz/Kalman Filter1/checku'
 * '<S226>' : 'softMBD/FCS/filters/Subsystem/x,y,z,dy,dy,dz/z,dz/Kalman Filter1/checky'
 * '<S227>' : 'softMBD/FCS/filters/Subsystem/x,y,z,dy,dy,dz/z,dz/Kalman Filter1/CalculatePL/DataTypeConversionL'
 * '<S228>' : 'softMBD/FCS/filters/Subsystem/x,y,z,dy,dy,dz/z,dz/Kalman Filter1/CalculatePL/DataTypeConversionM'
 * '<S229>' : 'softMBD/FCS/filters/Subsystem/x,y,z,dy,dy,dz/z,dz/Kalman Filter1/CalculatePL/DataTypeConversionP'
 * '<S230>' : 'softMBD/FCS/filters/Subsystem/x,y,z,dy,dy,dz/z,dz/Kalman Filter1/CalculatePL/DataTypeConversionZ'
 * '<S231>' : 'softMBD/FCS/filters/Subsystem/x,y,z,dy,dy,dz/z,dz/Kalman Filter1/CalculatePL/Ground'
 * '<S232>' : 'softMBD/FCS/filters/Subsystem/x,y,z,dy,dy,dz/z,dz/Kalman Filter1/CalculateYhat/Ground'
 * '<S233>' : 'softMBD/FCS/filters/Subsystem/x,y,z,dy,dy,dz/z,dz/Kalman Filter1/CovarianceOutputConfigurator/decideOutput'
 * '<S234>' : 'softMBD/FCS/filters/Subsystem/x,y,z,dy,dy,dz/z,dz/Kalman Filter1/CovarianceOutputConfigurator/decideOutput/SqrtUsedFcn'
 * '<S235>' : 'softMBD/FCS/filters/Subsystem/x,y,z,dy,dy,dz/z,dz/Kalman Filter1/Observer/MeasurementUpdate'
 * '<S236>' : 'softMBD/FCS/filters/Subsystem/x,y,z,dy,dy,dz/z,dz/Kalman Filter1/ReducedQRN/Ground'
 * '<S237>' : 'softMBD/FCS/filters/Subsystem/x,y,z,dy,dy,dz/z,dz/Kalman Filter1/UseCurrentEstimator/Enabled Subsystem'
 * '<S238>' : 'softMBD/FCS/filters/Subsystem1/pitch_kalman'
 * '<S239>' : 'softMBD/FCS/filters/Subsystem1/roll_kalman'
 * '<S240>' : 'softMBD/FCS/filters/Subsystem1/yaw_filter'
 * '<S241>' : 'softMBD/FCS/filters/Subsystem1/pitch_kalman/Kalman Filter1'
 * '<S242>' : 'softMBD/FCS/filters/Subsystem1/pitch_kalman/Kalman Filter1/CalculatePL'
 * '<S243>' : 'softMBD/FCS/filters/Subsystem1/pitch_kalman/Kalman Filter1/CalculateYhat'
 * '<S244>' : 'softMBD/FCS/filters/Subsystem1/pitch_kalman/Kalman Filter1/CovarianceOutputConfigurator'
 * '<S245>' : 'softMBD/FCS/filters/Subsystem1/pitch_kalman/Kalman Filter1/DataTypeConversionA'
 * '<S246>' : 'softMBD/FCS/filters/Subsystem1/pitch_kalman/Kalman Filter1/DataTypeConversionB'
 * '<S247>' : 'softMBD/FCS/filters/Subsystem1/pitch_kalman/Kalman Filter1/DataTypeConversionC'
 * '<S248>' : 'softMBD/FCS/filters/Subsystem1/pitch_kalman/Kalman Filter1/DataTypeConversionD'
 * '<S249>' : 'softMBD/FCS/filters/Subsystem1/pitch_kalman/Kalman Filter1/DataTypeConversionEnable'
 * '<S250>' : 'softMBD/FCS/filters/Subsystem1/pitch_kalman/Kalman Filter1/DataTypeConversionG'
 * '<S251>' : 'softMBD/FCS/filters/Subsystem1/pitch_kalman/Kalman Filter1/DataTypeConversionH'
 * '<S252>' : 'softMBD/FCS/filters/Subsystem1/pitch_kalman/Kalman Filter1/DataTypeConversionN'
 * '<S253>' : 'softMBD/FCS/filters/Subsystem1/pitch_kalman/Kalman Filter1/DataTypeConversionP'
 * '<S254>' : 'softMBD/FCS/filters/Subsystem1/pitch_kalman/Kalman Filter1/DataTypeConversionP0'
 * '<S255>' : 'softMBD/FCS/filters/Subsystem1/pitch_kalman/Kalman Filter1/DataTypeConversionQ'
 * '<S256>' : 'softMBD/FCS/filters/Subsystem1/pitch_kalman/Kalman Filter1/DataTypeConversionR'
 * '<S257>' : 'softMBD/FCS/filters/Subsystem1/pitch_kalman/Kalman Filter1/DataTypeConversionReset'
 * '<S258>' : 'softMBD/FCS/filters/Subsystem1/pitch_kalman/Kalman Filter1/DataTypeConversionX'
 * '<S259>' : 'softMBD/FCS/filters/Subsystem1/pitch_kalman/Kalman Filter1/DataTypeConversionX0'
 * '<S260>' : 'softMBD/FCS/filters/Subsystem1/pitch_kalman/Kalman Filter1/DataTypeConversionu'
 * '<S261>' : 'softMBD/FCS/filters/Subsystem1/pitch_kalman/Kalman Filter1/MemoryP'
 * '<S262>' : 'softMBD/FCS/filters/Subsystem1/pitch_kalman/Kalman Filter1/Observer'
 * '<S263>' : 'softMBD/FCS/filters/Subsystem1/pitch_kalman/Kalman Filter1/ReducedQRN'
 * '<S264>' : 'softMBD/FCS/filters/Subsystem1/pitch_kalman/Kalman Filter1/Reset'
 * '<S265>' : 'softMBD/FCS/filters/Subsystem1/pitch_kalman/Kalman Filter1/Reshapeyhat'
 * '<S266>' : 'softMBD/FCS/filters/Subsystem1/pitch_kalman/Kalman Filter1/ScalarExpansionP0'
 * '<S267>' : 'softMBD/FCS/filters/Subsystem1/pitch_kalman/Kalman Filter1/ScalarExpansionQ'
 * '<S268>' : 'softMBD/FCS/filters/Subsystem1/pitch_kalman/Kalman Filter1/ScalarExpansionR'
 * '<S269>' : 'softMBD/FCS/filters/Subsystem1/pitch_kalman/Kalman Filter1/UseCurrentEstimator'
 * '<S270>' : 'softMBD/FCS/filters/Subsystem1/pitch_kalman/Kalman Filter1/checkA'
 * '<S271>' : 'softMBD/FCS/filters/Subsystem1/pitch_kalman/Kalman Filter1/checkB'
 * '<S272>' : 'softMBD/FCS/filters/Subsystem1/pitch_kalman/Kalman Filter1/checkC'
 * '<S273>' : 'softMBD/FCS/filters/Subsystem1/pitch_kalman/Kalman Filter1/checkD'
 * '<S274>' : 'softMBD/FCS/filters/Subsystem1/pitch_kalman/Kalman Filter1/checkEnable'
 * '<S275>' : 'softMBD/FCS/filters/Subsystem1/pitch_kalman/Kalman Filter1/checkG'
 * '<S276>' : 'softMBD/FCS/filters/Subsystem1/pitch_kalman/Kalman Filter1/checkH'
 * '<S277>' : 'softMBD/FCS/filters/Subsystem1/pitch_kalman/Kalman Filter1/checkN'
 * '<S278>' : 'softMBD/FCS/filters/Subsystem1/pitch_kalman/Kalman Filter1/checkP0'
 * '<S279>' : 'softMBD/FCS/filters/Subsystem1/pitch_kalman/Kalman Filter1/checkQ'
 * '<S280>' : 'softMBD/FCS/filters/Subsystem1/pitch_kalman/Kalman Filter1/checkR'
 * '<S281>' : 'softMBD/FCS/filters/Subsystem1/pitch_kalman/Kalman Filter1/checkReset'
 * '<S282>' : 'softMBD/FCS/filters/Subsystem1/pitch_kalman/Kalman Filter1/checkX0'
 * '<S283>' : 'softMBD/FCS/filters/Subsystem1/pitch_kalman/Kalman Filter1/checku'
 * '<S284>' : 'softMBD/FCS/filters/Subsystem1/pitch_kalman/Kalman Filter1/checky'
 * '<S285>' : 'softMBD/FCS/filters/Subsystem1/pitch_kalman/Kalman Filter1/CalculatePL/DataTypeConversionL'
 * '<S286>' : 'softMBD/FCS/filters/Subsystem1/pitch_kalman/Kalman Filter1/CalculatePL/DataTypeConversionM'
 * '<S287>' : 'softMBD/FCS/filters/Subsystem1/pitch_kalman/Kalman Filter1/CalculatePL/DataTypeConversionP'
 * '<S288>' : 'softMBD/FCS/filters/Subsystem1/pitch_kalman/Kalman Filter1/CalculatePL/DataTypeConversionZ'
 * '<S289>' : 'softMBD/FCS/filters/Subsystem1/pitch_kalman/Kalman Filter1/CalculatePL/Ground'
 * '<S290>' : 'softMBD/FCS/filters/Subsystem1/pitch_kalman/Kalman Filter1/CalculateYhat/Ground'
 * '<S291>' : 'softMBD/FCS/filters/Subsystem1/pitch_kalman/Kalman Filter1/CovarianceOutputConfigurator/decideOutput'
 * '<S292>' : 'softMBD/FCS/filters/Subsystem1/pitch_kalman/Kalman Filter1/CovarianceOutputConfigurator/decideOutput/SqrtUsedFcn'
 * '<S293>' : 'softMBD/FCS/filters/Subsystem1/pitch_kalman/Kalman Filter1/Observer/MeasurementUpdate'
 * '<S294>' : 'softMBD/FCS/filters/Subsystem1/pitch_kalman/Kalman Filter1/ReducedQRN/Ground'
 * '<S295>' : 'softMBD/FCS/filters/Subsystem1/pitch_kalman/Kalman Filter1/UseCurrentEstimator/Enabled Subsystem'
 * '<S296>' : 'softMBD/FCS/filters/Subsystem1/roll_kalman/Kalman Filter'
 * '<S297>' : 'softMBD/FCS/filters/Subsystem1/roll_kalman/Kalman Filter/CalculatePL'
 * '<S298>' : 'softMBD/FCS/filters/Subsystem1/roll_kalman/Kalman Filter/CalculateYhat'
 * '<S299>' : 'softMBD/FCS/filters/Subsystem1/roll_kalman/Kalman Filter/CovarianceOutputConfigurator'
 * '<S300>' : 'softMBD/FCS/filters/Subsystem1/roll_kalman/Kalman Filter/DataTypeConversionA'
 * '<S301>' : 'softMBD/FCS/filters/Subsystem1/roll_kalman/Kalman Filter/DataTypeConversionB'
 * '<S302>' : 'softMBD/FCS/filters/Subsystem1/roll_kalman/Kalman Filter/DataTypeConversionC'
 * '<S303>' : 'softMBD/FCS/filters/Subsystem1/roll_kalman/Kalman Filter/DataTypeConversionD'
 * '<S304>' : 'softMBD/FCS/filters/Subsystem1/roll_kalman/Kalman Filter/DataTypeConversionEnable'
 * '<S305>' : 'softMBD/FCS/filters/Subsystem1/roll_kalman/Kalman Filter/DataTypeConversionG'
 * '<S306>' : 'softMBD/FCS/filters/Subsystem1/roll_kalman/Kalman Filter/DataTypeConversionH'
 * '<S307>' : 'softMBD/FCS/filters/Subsystem1/roll_kalman/Kalman Filter/DataTypeConversionN'
 * '<S308>' : 'softMBD/FCS/filters/Subsystem1/roll_kalman/Kalman Filter/DataTypeConversionP'
 * '<S309>' : 'softMBD/FCS/filters/Subsystem1/roll_kalman/Kalman Filter/DataTypeConversionP0'
 * '<S310>' : 'softMBD/FCS/filters/Subsystem1/roll_kalman/Kalman Filter/DataTypeConversionQ'
 * '<S311>' : 'softMBD/FCS/filters/Subsystem1/roll_kalman/Kalman Filter/DataTypeConversionR'
 * '<S312>' : 'softMBD/FCS/filters/Subsystem1/roll_kalman/Kalman Filter/DataTypeConversionReset'
 * '<S313>' : 'softMBD/FCS/filters/Subsystem1/roll_kalman/Kalman Filter/DataTypeConversionX'
 * '<S314>' : 'softMBD/FCS/filters/Subsystem1/roll_kalman/Kalman Filter/DataTypeConversionX0'
 * '<S315>' : 'softMBD/FCS/filters/Subsystem1/roll_kalman/Kalman Filter/DataTypeConversionu'
 * '<S316>' : 'softMBD/FCS/filters/Subsystem1/roll_kalman/Kalman Filter/MemoryP'
 * '<S317>' : 'softMBD/FCS/filters/Subsystem1/roll_kalman/Kalman Filter/Observer'
 * '<S318>' : 'softMBD/FCS/filters/Subsystem1/roll_kalman/Kalman Filter/ReducedQRN'
 * '<S319>' : 'softMBD/FCS/filters/Subsystem1/roll_kalman/Kalman Filter/Reset'
 * '<S320>' : 'softMBD/FCS/filters/Subsystem1/roll_kalman/Kalman Filter/Reshapeyhat'
 * '<S321>' : 'softMBD/FCS/filters/Subsystem1/roll_kalman/Kalman Filter/ScalarExpansionP0'
 * '<S322>' : 'softMBD/FCS/filters/Subsystem1/roll_kalman/Kalman Filter/ScalarExpansionQ'
 * '<S323>' : 'softMBD/FCS/filters/Subsystem1/roll_kalman/Kalman Filter/ScalarExpansionR'
 * '<S324>' : 'softMBD/FCS/filters/Subsystem1/roll_kalman/Kalman Filter/UseCurrentEstimator'
 * '<S325>' : 'softMBD/FCS/filters/Subsystem1/roll_kalman/Kalman Filter/checkA'
 * '<S326>' : 'softMBD/FCS/filters/Subsystem1/roll_kalman/Kalman Filter/checkB'
 * '<S327>' : 'softMBD/FCS/filters/Subsystem1/roll_kalman/Kalman Filter/checkC'
 * '<S328>' : 'softMBD/FCS/filters/Subsystem1/roll_kalman/Kalman Filter/checkD'
 * '<S329>' : 'softMBD/FCS/filters/Subsystem1/roll_kalman/Kalman Filter/checkEnable'
 * '<S330>' : 'softMBD/FCS/filters/Subsystem1/roll_kalman/Kalman Filter/checkG'
 * '<S331>' : 'softMBD/FCS/filters/Subsystem1/roll_kalman/Kalman Filter/checkH'
 * '<S332>' : 'softMBD/FCS/filters/Subsystem1/roll_kalman/Kalman Filter/checkN'
 * '<S333>' : 'softMBD/FCS/filters/Subsystem1/roll_kalman/Kalman Filter/checkP0'
 * '<S334>' : 'softMBD/FCS/filters/Subsystem1/roll_kalman/Kalman Filter/checkQ'
 * '<S335>' : 'softMBD/FCS/filters/Subsystem1/roll_kalman/Kalman Filter/checkR'
 * '<S336>' : 'softMBD/FCS/filters/Subsystem1/roll_kalman/Kalman Filter/checkReset'
 * '<S337>' : 'softMBD/FCS/filters/Subsystem1/roll_kalman/Kalman Filter/checkX0'
 * '<S338>' : 'softMBD/FCS/filters/Subsystem1/roll_kalman/Kalman Filter/checku'
 * '<S339>' : 'softMBD/FCS/filters/Subsystem1/roll_kalman/Kalman Filter/checky'
 * '<S340>' : 'softMBD/FCS/filters/Subsystem1/roll_kalman/Kalman Filter/CalculatePL/DataTypeConversionL'
 * '<S341>' : 'softMBD/FCS/filters/Subsystem1/roll_kalman/Kalman Filter/CalculatePL/DataTypeConversionM'
 * '<S342>' : 'softMBD/FCS/filters/Subsystem1/roll_kalman/Kalman Filter/CalculatePL/DataTypeConversionP'
 * '<S343>' : 'softMBD/FCS/filters/Subsystem1/roll_kalman/Kalman Filter/CalculatePL/DataTypeConversionZ'
 * '<S344>' : 'softMBD/FCS/filters/Subsystem1/roll_kalman/Kalman Filter/CalculatePL/Ground'
 * '<S345>' : 'softMBD/FCS/filters/Subsystem1/roll_kalman/Kalman Filter/CalculateYhat/Ground'
 * '<S346>' : 'softMBD/FCS/filters/Subsystem1/roll_kalman/Kalman Filter/CovarianceOutputConfigurator/decideOutput'
 * '<S347>' : 'softMBD/FCS/filters/Subsystem1/roll_kalman/Kalman Filter/CovarianceOutputConfigurator/decideOutput/SqrtUsedFcn'
 * '<S348>' : 'softMBD/FCS/filters/Subsystem1/roll_kalman/Kalman Filter/Observer/MeasurementUpdate'
 * '<S349>' : 'softMBD/FCS/filters/Subsystem1/roll_kalman/Kalman Filter/ReducedQRN/Ground'
 * '<S350>' : 'softMBD/FCS/filters/Subsystem1/roll_kalman/Kalman Filter/UseCurrentEstimator/Enabled Subsystem'
 * '<S351>' : 'softMBD/FCS/filters/pqr_LPF/Transfer Fcn1'
 * '<S352>' : 'softMBD/FCS/filters/pqr_LPF/Transfer Fcn2'
 * '<S353>' : 'softMBD/FCS/filters/pqr_LPF/Transfer Fcn3'
 * '<S354>' : 'softMBD/FCS/filters/pqr_LPF1/Transfer Fcn1'
 * '<S355>' : 'softMBD/FCS/filters/pqr_LPF1/Transfer Fcn2'
 * '<S356>' : 'softMBD/FCS/filters/pqr_LPF1/Transfer Fcn3'
 */
#endif                                 /* FCS_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
