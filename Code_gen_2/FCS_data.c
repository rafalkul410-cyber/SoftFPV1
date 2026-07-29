/*
 * FCS_data.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "FCS".
 *
 * Model version              : 1.17
 * Simulink Coder version : 25.2 (R2025b) 28-Jul-2025
 * C source code generated on : Wed Jul 29 17:19:23 2026
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "FCS.h"

/* Block parameters (default storage) */
P_FCS_T FCS_P = {
  /* Variable: FPV_mass
   * Referenced by: '<S5>/Constant'
   */
  0.8,

  /* Variable: MaxThrustSaturation
   * Referenced by: '<S5>/SaturationThrust1'
   */
  16.0,

  /* Variable: g
   * Referenced by:
   *   '<S5>/Constant'
   *   '<S402>/Gain'
   */
  9.81,

  /* Variable: p_0
   * Referenced by: '<S346>/Constant'
   */
  1013.25,

  /* Variable: takeoffgain
   * Referenced by: '<S5>/Gain'
   */
  1.2,

  /* Variable: Q2Ts
   * Referenced by: '<S4>/TorqueTotalThrustToThrustPerMotor'
   */
  { 0.25F, 0.25F, 0.25F, 0.25F, 66.9291306F, -66.9291306F, 66.9291306F,
    -66.9291306F, -2.35702252F, -2.35702252F, 2.35702252F, 2.35702252F,
    -2.35702252F, 2.35702252F, 2.35702252F, -2.35702252F },

  /* Mask Parameter: PIDController2_D
   * Referenced by: '<S154>/Derivative Gain'
   */
  0.0,

  /* Mask Parameter: PIDController_D
   * Referenced by: '<S260>/Derivative Gain'
   */
  0.0,

  /* Mask Parameter: PIDController1_D
   * Referenced by: '<S314>/Derivative Gain'
   */
  { 0.00012, 9.72E-5 },

  /* Mask Parameter: PIDController3_D
   * Referenced by: '<S206>/Derivative Gain'
   */
  0.0,

  /* Mask Parameter: PIDController2_I
   * Referenced by: '<S158>/Integral Gain'
   */
  0.0,

  /* Mask Parameter: PIDController3_I
   * Referenced by: '<S210>/Integral Gain'
   */
  0.0,

  /* Mask Parameter: PIDController_I
   * Referenced by: '<S264>/Integral Gain'
   */
  0.01,

  /* Mask Parameter: PIDController1_I
   * Referenced by: '<S318>/Integral Gain'
   */
  { 0.003, 0.0024300000000000003 },

  /* Mask Parameter: PIDController2_InitialCondition
   * Referenced by: '<S156>/Filter'
   */
  0.0,

  /* Mask Parameter: PIDController_InitialConditionF
   * Referenced by: '<S262>/Filter'
   */
  0.0,

  /* Mask Parameter: PIDController1_InitialCondition
   * Referenced by: '<S316>/Filter'
   */
  0.0,

  /* Mask Parameter: PIDController3_InitialCondition
   * Referenced by: '<S208>/Filter'
   */
  0.0,

  /* Mask Parameter: PIDController2_InitialConditi_e
   * Referenced by: '<S161>/Integrator'
   */
  0.0,

  /* Mask Parameter: PIDController_InitialConditio_h
   * Referenced by: '<S267>/Integrator'
   */
  0.0,

  /* Mask Parameter: PIDController1_InitialConditi_e
   * Referenced by: '<S321>/Integrator'
   */
  0.0,

  /* Mask Parameter: PIDController3_InitialConditi_m
   * Referenced by: '<S213>/Integrator'
   */
  0.0,

  /* Mask Parameter: PIDController1_LowerSaturationL
   * Referenced by: '<S116>/Saturation'
   */
  -0.5,

  /* Mask Parameter: PIDController2_LowerSaturationL
   * Referenced by: '<S168>/Saturation'
   */
  -0.3490658503988659,

  /* Mask Parameter: PIDController1_LowerSaturatio_d
   * Referenced by:
   *   '<S328>/Saturation'
   *   '<S313>/DeadZone'
   */
  -0.02,

  /* Mask Parameter: PIDController_LowerSaturationLi
   * Referenced by: '<S64>/Saturation'
   */
  -0.5,

  /* Mask Parameter: PIDController3_LowerSaturationL
   * Referenced by: '<S220>/Saturation'
   */
  -0.3490658503988659,

  /* Mask Parameter: PIDController2_N
   * Referenced by: '<S164>/Filter Coefficient'
   */
  78.69386805747331,

  /* Mask Parameter: PIDController_N
   * Referenced by: '<S270>/Filter Coefficient'
   */
  78.69386805747331,

  /* Mask Parameter: PIDController1_N
   * Referenced by: '<S324>/Filter Coefficient'
   */
  { 70.0, 70.0 },

  /* Mask Parameter: PIDController3_N
   * Referenced by: '<S216>/Filter Coefficient'
   */
  78.69386805747331,

  /* Mask Parameter: PIDController1_P
   * Referenced by: '<S114>/Proportional Gain'
   */
  0.7,

  /* Mask Parameter: PIDController2_P
   * Referenced by: '<S166>/Proportional Gain'
   */
  0.7,

  /* Mask Parameter: PIDController_P
   * Referenced by: '<S272>/Proportional Gain'
   */
  1.0,

  /* Mask Parameter: PIDController1_P_k
   * Referenced by: '<S326>/Proportional Gain'
   */
  { 0.003, 0.0024300000000000003 },

  /* Mask Parameter: PIDController_P_g
   * Referenced by: '<S62>/Proportional Gain'
   */
  0.7,

  /* Mask Parameter: PIDController3_P
   * Referenced by: '<S218>/Proportional Gain'
   */
  0.7,

  /* Mask Parameter: PIDController1_UpperSaturationL
   * Referenced by: '<S116>/Saturation'
   */
  0.5,

  /* Mask Parameter: PIDController2_UpperSaturationL
   * Referenced by: '<S168>/Saturation'
   */
  0.3490658503988659,

  /* Mask Parameter: PIDController1_UpperSaturatio_p
   * Referenced by:
   *   '<S328>/Saturation'
   *   '<S313>/DeadZone'
   */
  0.02,

  /* Mask Parameter: PIDController_UpperSaturationLi
   * Referenced by: '<S64>/Saturation'
   */
  0.5,

  /* Mask Parameter: PIDController3_UpperSaturationL
   * Referenced by: '<S220>/Saturation'
   */
  0.3490658503988659,

  /* Mask Parameter: WrapToZero_Threshold
   * Referenced by: '<S13>/FixPt Switch'
   */
  65535U,

  /* Mask Parameter: CompareToConstant_const
   * Referenced by: '<S10>/Constant'
   */
  500U,

  /* Expression: 1
   * Referenced by: '<S7>/Gain'
   */
  1.0,

  /* Expression: -1
   * Referenced by: '<S7>/Gain1'
   */
  -1.0,

  /* Expression: 0
   * Referenced by: '<S311>/Constant1'
   */
  0.0,

  /* Computed Parameter: Integrator_gainval
   * Referenced by: '<S5>/Integrator'
   */
  0.005,

  /* Expression: 0
   * Referenced by: '<S5>/Integrator'
   */
  0.0,

  /* Expression: 2
   * Referenced by: '<S5>/Integrator'
   */
  2.0,

  /* Expression: -2
   * Referenced by: '<S5>/Integrator'
   */
  -2.0,

  /* Expression: pInitialization.M
   * Referenced by: '<S348>/KalmanGainM'
   */
  { 0.099530888073182819, 0.09489305095352564 },

  /* Expression: pInitialization.C
   * Referenced by: '<S347>/C'
   */
  { 1.0, 0.0 },

  /* Computed Parameter: LPF1_A
   * Referenced by: '<S3>/LPF1'
   */
  -10.0,

  /* Computed Parameter: LPF1_C
   * Referenced by: '<S3>/LPF1'
   */
  10.0,

  /* Expression: 1/12.01
   * Referenced by: '<S346>/Gain'
   */
  0.083263946711074108,

  /* Expression: pInitialization.X0
   * Referenced by: '<S347>/X0'
   */
  { 0.0, 0.0 },

  /* Expression: -1
   * Referenced by: '<S5>/Gain5'
   */
  -1.0,

  /* Expression: 0.5
   * Referenced by: '<S5>/Saturation'
   */
  0.5,

  /* Expression: -0.5
   * Referenced by: '<S5>/Saturation'
   */
  -0.5,

  /* Expression: 0.8
   * Referenced by: '<S5>/Gain1'
   */
  0.8,

  /* Expression: 0.001
   * Referenced by: '<S5>/Gain2'
   */
  0.001,

  /* Expression: 0
   * Referenced by: '<S5>/SaturationThrust1'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S404>/Integrator'
   */
  0.0,

  /* Expression: 30*pi/180
   * Referenced by: '<S9>/Saturation'
   */
  0.52359877559829882,

  /* Expression: -30*pi/180
   * Referenced by: '<S9>/Saturation'
   */
  -0.52359877559829882,

  /* Expression: 0.002
   * Referenced by: '<S9>/Gain1'
   */
  0.002,

  /* Expression: 0
   * Referenced by: '<S9>/Integrator'
   */
  0.0,

  /* Computed Parameter: TransferFcn2_A
   * Referenced by: '<S341>/Transfer Fcn2'
   */
  -500.0,

  /* Computed Parameter: TransferFcn2_C
   * Referenced by: '<S341>/Transfer Fcn2'
   */
  500.0,

  /* Expression: 0.002*0.004
   * Referenced by: '<S9>/Gain2'
   */
  8.0E-6,

  /* Expression: numd
   * Referenced by: '<S15>/Discrete Transfer Fcn'
   */
  { 0.0, 0.048770575499285984 },

  /* Expression: dend
   * Referenced by: '<S15>/Discrete Transfer Fcn'
   */
  { 1.0, -0.951229424500714 },

  /* Expression: 0
   * Referenced by: '<S15>/Discrete Transfer Fcn'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S345>/Integrator2'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S345>/Integrator1'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S345>/Integrator3'
   */
  0.0,

  /* Computed Parameter: Integrator_gainval_j
   * Referenced by: '<S161>/Integrator'
   */
  0.005,

  /* Computed Parameter: Filter_gainval
   * Referenced by: '<S156>/Filter'
   */
  0.005,

  /* Expression: numd
   * Referenced by: '<S14>/Discrete Transfer Fcn'
   */
  { 0.11163521170465972, -0.11107595036200343 },

  /* Expression: dend
   * Referenced by: '<S14>/Discrete Transfer Fcn'
   */
  { 1.0, -1.0038911990155417 },

  /* Expression: 0
   * Referenced by: '<S14>/Discrete Transfer Fcn'
   */
  0.0,

  /* Expression: pInitialization.M
   * Referenced by: '<S461>/KalmanGainM'
   */
  { 0.20394675669207771, -0.19950604543572131 },

  /* Expression: pInitialization.C
   * Referenced by: '<S460>/C'
   */
  { 1.0, 0.0 },

  /* Computed Parameter: TransferFcn1_A
   * Referenced by: '<S342>/Transfer Fcn1'
   */
  -200.0,

  /* Computed Parameter: TransferFcn1_C
   * Referenced by: '<S342>/Transfer Fcn1'
   */
  200.0,

  /* Computed Parameter: TransferFcn2_A_e
   * Referenced by: '<S342>/Transfer Fcn2'
   */
  -200.0,

  /* Computed Parameter: TransferFcn2_C_l
   * Referenced by: '<S342>/Transfer Fcn2'
   */
  200.0,

  /* Expression: 1e-6
   * Referenced by: '<S403>/Constant'
   */
  1.0E-6,

  /* Expression: pInitialization.X0
   * Referenced by: '<S460>/X0'
   */
  { 0.0, 0.0 },

  /* Expression: pInitialization.M
   * Referenced by: '<S406>/KalmanGainM'
   */
  { 0.20394675669207771, -0.19950604543572131 },

  /* Expression: pInitialization.C
   * Referenced by: '<S405>/C'
   */
  { 1.0, 0.0 },

  /* Computed Parameter: TransferFcn_A
   * Referenced by: '<S342>/Transfer Fcn'
   */
  -200.0,

  /* Computed Parameter: TransferFcn_C
   * Referenced by: '<S342>/Transfer Fcn'
   */
  200.0,

  /* Expression: pInitialization.X0
   * Referenced by: '<S405>/X0'
   */
  { 0.0, 0.0 },

  /* Computed Parameter: Integrator_gainval_i
   * Referenced by: '<S267>/Integrator'
   */
  0.005,

  /* Computed Parameter: Filter_gainval_h
   * Referenced by: '<S262>/Filter'
   */
  0.005,

  /* Computed Parameter: TransferFcn_A_a
   * Referenced by: '<S341>/Transfer Fcn'
   */
  -500.0,

  /* Computed Parameter: TransferFcn_C_e
   * Referenced by: '<S341>/Transfer Fcn'
   */
  500.0,

  /* Computed Parameter: TransferFcn1_A_l
   * Referenced by: '<S341>/Transfer Fcn1'
   */
  -500.0,

  /* Computed Parameter: TransferFcn1_C_o
   * Referenced by: '<S341>/Transfer Fcn1'
   */
  500.0,

  /* Expression: 8.0
   * Referenced by: '<S6>/Saturation'
   */
  8.0,

  /* Expression: -8.0
   * Referenced by: '<S6>/Saturation'
   */
  -8.0,

  /* Expression: 255.875
   * Referenced by: '<S6>/ThrustToMotorCommand'
   */
  255.875,

  /* Expression: [1 -1 1 -1]
   * Referenced by: '<S6>/MotorDirections'
   */
  { 1.0, -1.0, 1.0, -1.0 },

  /* Expression: 2047
   * Referenced by: '<S6>/Saturation5'
   */
  2047.0,

  /* Expression: 48
   * Referenced by: '<S6>/Saturation5'
   */
  48.0,

  /* Expression: 0
   * Referenced by: '<S345>/Integrator'
   */
  0.0,

  /* Expression: 0.24
   * Referenced by: '<S5>/Gain3'
   */
  0.24,

  /* Computed Parameter: Filter_gainval_k
   * Referenced by: '<S208>/Filter'
   */
  0.005,

  /* Computed Parameter: Integrator_gainval_a
   * Referenced by: '<S213>/Integrator'
   */
  0.005,

  /* Expression: 0
   * Referenced by: '<S311>/ZeroGain'
   */
  0.0,

  /* Expression: 0.004
   * Referenced by: '<S9>/Gain'
   */
  0.004,

  /* Computed Parameter: LPF_A
   * Referenced by: '<S3>/LPF'
   */
  -10.0,

  /* Computed Parameter: LPF_C
   * Referenced by: '<S3>/LPF'
   */
  10.0,

  /* Computed Parameter: LPF2_A
   * Referenced by: '<S3>/LPF2'
   */
  -1.0,

  /* Computed Parameter: LPF2_C
   * Referenced by: '<S3>/LPF2'
   */
  1.0,

  /* Expression: [0 0 g]
   * Referenced by: '<S343>/Constant'
   */
  { 0.0, 0.0, 9.81 },

  /* Expression: pInitialization.A
   * Referenced by: '<S347>/A'
   */
  { 1.0, 0.0, 0.005, 1.0 },

  /* Expression: pInitialization.B
   * Referenced by: '<S347>/B'
   */
  { 1.25E-5, 0.005 },

  /* Expression: pInitialization.Z
   * Referenced by: '<S348>/CovarianceZ'
   */
  { 0.009953088807318284, 0.0094893050953525643, 0.0094893050953525643,
    0.20977487197019559 },

  /* Expression: pInitialization.L
   * Referenced by: '<S348>/KalmanGainL'
   */
  { 0.10000535332795049, 0.094893050953525723 },

  /* Expression: pInitialization.D
   * Referenced by: '<S347>/D'
   */
  0.0,

  /* Expression: pInitialization.A
   * Referenced by: '<S405>/A'
   */
  { 1.0, 0.0, -0.005, 1.0 },

  /* Expression: pInitialization.B
   * Referenced by: '<S405>/B'
   */
  { 0.005, 0.0 },

  /* Expression: pInitialization.Z
   * Referenced by: '<S406>/CovarianceZ'
   */
  { 0.20394675669207774, -0.19950604543572131, -0.19950604543572131,
    10.222585297938185 },

  /* Expression: pInitialization.L
   * Referenced by: '<S406>/KalmanGainL'
   */
  { 0.2049442869192564, -0.19950604543572328 },

  /* Expression: pInitialization.D
   * Referenced by: '<S405>/D'
   */
  0.0,

  /* Expression: pInitialization.A
   * Referenced by: '<S460>/A'
   */
  { 1.0, 0.0, -0.005, 1.0 },

  /* Expression: pInitialization.B
   * Referenced by: '<S460>/B'
   */
  { 0.005, 0.0 },

  /* Expression: pInitialization.Z
   * Referenced by: '<S461>/CovarianceZ'
   */
  { 0.20394675669207774, -0.19950604543572131, -0.19950604543572131,
    10.222585297938185 },

  /* Expression: pInitialization.L
   * Referenced by: '<S461>/KalmanGainL'
   */
  { 0.2049442869192564, -0.19950604543572328 },

  /* Expression: pInitialization.D
   * Referenced by: '<S460>/D'
   */
  0.0,

  /* Computed Parameter: Gain4_Gain
   * Referenced by: '<S5>/Gain4'
   */
  15.696F,

  /* Computed Parameter: Output_InitialCondition
   * Referenced by: '<S11>/Output'
   */
  0U,

  /* Computed Parameter: FixPtConstant_Value
   * Referenced by: '<S12>/FixPt Constant'
   */
  1U,

  /* Computed Parameter: Constant_Value_g
   * Referenced by: '<S13>/Constant'
   */
  0U,

  /* Expression: true()
   * Referenced by: '<S347>/Enable'
   */
  true,

  /* Expression: true()
   * Referenced by: '<S460>/Enable'
   */
  true,

  /* Expression: true()
   * Referenced by: '<S405>/Enable'
   */
  true,

  /* Computed Parameter: Memory_InitialCondition
   * Referenced by: '<S311>/Memory'
   */
  false,

  /* Expression: pInitialization.isSqrtUsed
   * Referenced by: '<S397>/isSqrtUsed'
   */
  false,

  /* Expression: pInitialization.isSqrtUsed
   * Referenced by: '<S455>/isSqrtUsed'
   */
  false,

  /* Expression: pInitialization.isSqrtUsed
   * Referenced by: '<S510>/isSqrtUsed'
   */
  false,

  /* Start of '<S488>/Enabled Subsystem' */
  {
    /* Expression: 0
     * Referenced by: '<S514>/deltax'
     */
    0.0
  }
  ,

  /* End of '<S488>/Enabled Subsystem' */

  /* Start of '<S481>/MeasurementUpdate' */
  {
    /* Expression: 0
     * Referenced by: '<S512>/L*(y[k]-yhat[k|k-1])'
     */
    0.0
  }
  ,

  /* End of '<S481>/MeasurementUpdate' */

  /* Start of '<S433>/Enabled Subsystem' */
  {
    /* Expression: 0
     * Referenced by: '<S459>/deltax'
     */
    0.0
  }
  ,

  /* End of '<S433>/Enabled Subsystem' */

  /* Start of '<S426>/MeasurementUpdate' */
  {
    /* Expression: 0
     * Referenced by: '<S457>/L*(y[k]-yhat[k|k-1])'
     */
    0.0
  }
  ,

  /* End of '<S426>/MeasurementUpdate' */

  /* Start of '<S375>/Enabled Subsystem' */
  {
    /* Expression: 0
     * Referenced by: '<S401>/deltax'
     */
    0.0
  }
  ,

  /* End of '<S375>/Enabled Subsystem' */

  /* Start of '<S368>/MeasurementUpdate' */
  {
    /* Expression: 0
     * Referenced by: '<S399>/L*(y[k]-yhat[k|k-1])'
     */
    0.0
  }
  /* End of '<S368>/MeasurementUpdate' */
};
