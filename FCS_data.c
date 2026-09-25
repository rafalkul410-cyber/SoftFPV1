/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: FCS_data.c
 *
 * Code generated for Simulink model 'FCS'.
 *
 * Model version                  : 1.18
 * Simulink Coder version         : 25.2 (R2025b) 28-Jul-2025
 * C/C++ source code generated on : Fri Sep 25 22:12:09 2026
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-M
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "FCS.h"

/* Block parameters (default storage) */
P_FCS_T FCS_P = {
  /* Variable: Q2Ts
   * Referenced by: '<S5>/Multiply'
   */
  { 0.25, 0.25, 0.25, 0.25, -3.2141217326661251, 3.2141217326661251,
    3.2141217326661251, -3.2141217326661251, -3.2141217326661251,
    -3.2141217326661251, 3.2141217326661251, 3.2141217326661251,
    26.913090637956955, -26.913090637956955, 26.913090637956955,
    -26.913090637956955 },

  /* Variable: kd_pq
   * Referenced by: '<S154>/Derivative Gain'
   */
  { 0.0F, 0.0F },

  /* Variable: kd_pr
   * Referenced by: '<S98>/Derivative Gain'
   */
  0.0F,

  /* Variable: kd_y
   * Referenced by: '<S214>/Derivative Gain'
   */
  0.0F,

  /* Variable: ki_pq
   * Referenced by: '<S160>/Integral Gain'
   */
  { 0.0F, 0.0F },

  /* Variable: ki_pr
   * Referenced by: '<S102>/Integral Gain'
   */
  0.0F,

  /* Variable: ki_y
   * Referenced by: '<S218>/Integral Gain'
   */
  0.0F,

  /* Variable: kp_pq
   * Referenced by: '<S168>/Proportional Gain'
   */
  { 0.92F, 0.92F },

  /* Variable: kp_pr
   * Referenced by: '<S110>/Proportional Gain'
   */
  4.0F,

  /* Variable: kp_y
   * Referenced by: '<S226>/Proportional Gain'
   */
  0.04F,

  /* Mask Parameter: PIDController2DOF_Differentiato
   * Referenced by: '<S156>/UD'
   */
  0.0F,

  /* Mask Parameter: PIDController_InitialConditionF
   * Referenced by: '<S100>/Filter'
   */
  0.0F,

  /* Mask Parameter: PIDController2DOF_InitialCondit
   * Referenced by: '<S216>/Filter'
   */
  0.0F,

  /* Mask Parameter: PIDController_InitialConditio_l
   * Referenced by: '<S105>/Integrator'
   */
  0.0F,

  /* Mask Parameter: PIDController2DOF_InitialCond_j
   * Referenced by: '<S163>/Integrator'
   */
  0.0F,

  /* Mask Parameter: PIDController2DOF_InitialCond_a
   * Referenced by: '<S221>/Integrator'
   */
  0.0F,

  /* Mask Parameter: PIDController2DOF_LowerIntegrat
   * Referenced by: '<S163>/Integrator'
   */
  { -0.01F, -0.01F },

  /* Mask Parameter: PIDController2DOF_LowerIntegr_i
   * Referenced by: '<S221>/Integrator'
   */
  -0.02F,

  /* Mask Parameter: PIDController2DOF_LowerSaturati
   * Referenced by:
   *   '<S170>/Saturation'
   *   '<S153>/DeadZone'
   */
  { -0.15F, -0.15F },

  /* Mask Parameter: PIDController_N
   * Referenced by: '<S108>/Filter Coefficient'
   */
  { 85.0F, 85.0F },

  /* Mask Parameter: PIDController2DOF_N
   * Referenced by: '<S224>/Filter Coefficient'
   */
  100.0F,

  /* Mask Parameter: PIDController2DOF_UpperIntegrat
   * Referenced by: '<S163>/Integrator'
   */
  { 0.01F, 0.01F },

  /* Mask Parameter: PIDController2DOF_UpperIntegr_j
   * Referenced by: '<S221>/Integrator'
   */
  0.02F,

  /* Mask Parameter: PIDController2DOF_UpperSaturati
   * Referenced by:
   *   '<S170>/Saturation'
   *   '<S153>/DeadZone'
   */
  { 0.15F, 0.15F },

  /* Mask Parameter: PIDController2DOF_b
   * Referenced by: '<S178>/Setpoint Weighting (Proportional)'
   */
  1.0F,

  /* Mask Parameter: PIDController2DOF_b_d
   * Referenced by: '<S236>/Setpoint Weighting (Proportional)'
   */
  1.0F,

  /* Mask Parameter: PIDController2DOF_c
   * Referenced by: '<S179>/Setpoint Weighting (Derivative)'
   */
  { 0.0F, 0.0F },

  /* Mask Parameter: PIDController2DOF_c_c
   * Referenced by: '<S237>/Setpoint Weighting (Derivative)'
   */
  0.0F,

  /* Mask Parameter: CompareToConstant1_const
   * Referenced by: '<S368>/Constant'
   */
  8.0F,

  /* Mask Parameter: CompareToConstant_const
   * Referenced by: '<S367>/Constant'
   */
  11.5F,

  /* Mask Parameter: CompareToConstant1_const_i
   * Referenced by: '<S311>/Constant'
   */
  8.0F,

  /* Mask Parameter: CompareToConstant_const_b
   * Referenced by: '<S310>/Constant'
   */
  11.5F,

  /* Mask Parameter: CompareToConstant_const_k
   * Referenced by: '<S67>/Constant'
   */
  0.0F,

  /* Mask Parameter: CompareToConstant1_const_l
   * Referenced by: '<S68>/Constant'
   */
  0.0F,

  /* Mask Parameter: CompareToConstant_const_d
   * Referenced by: '<S183>/Constant'
   */
  0.0F,

  /* Expression: 0.0
   * Referenced by: '<S7>/Constant1'
   */
  0.0,

  /* Expression: 0.0
   * Referenced by: '<S7>/Constant'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S8>/Constant1'
   */
  0.0,

  /* Expression: pInitialization.M
   * Referenced by: '<S370>/KalmanGainM'
   */
  { 0.13177446878757812, 0.0 },

  /* Expression: pInitialization.M
   * Referenced by: '<S313>/KalmanGainM'
   */
  { 0.038576148803713059, -0.053705414564908134 },

  /* Expression: 2.0
   * Referenced by: '<S7>/Rate Limiter'
   */
  2.0,

  /* Expression: -2.0
   * Referenced by: '<S7>/Rate Limiter'
   */
  -2.0,

  /* Expression: 2.0
   * Referenced by: '<S8>/Rate Limiter1'
   */
  2.0,

  /* Expression: -2.0
   * Referenced by: '<S8>/Rate Limiter1'
   */
  -2.0,

  /* Expression: 0.1
   * Referenced by: '<S8>/Saturatio_yaw'
   */
  0.1,

  /* Expression: -0.1
   * Referenced by: '<S8>/Saturatio_yaw'
   */
  -0.1,

  /* Expression: 9.0
   * Referenced by: '<S5>/Saturation'
   */
  9.0,

  /* Expression: 0.15
   * Referenced by: '<S5>/Saturation'
   */
  0.15,

  /* Expression: (2047-48)/9.0
   * Referenced by: '<S5>/ThrustToMotorCommand'
   */
  222.11111111111111,

  /* Expression: pInitialization.L
   * Referenced by: '<S253>/KalmanGainL'
   */
  { 0.0047286981477743066, 0.0022307873674884205 },

  /* Expression: pInitialization.M
   * Referenced by: '<S253>/KalmanGainM'
   */
  { 0.0047175442109368363, 0.0022307873674884148 },

  /* Expression: pInitialization.L
   * Referenced by: '<S313>/KalmanGainL'
   */
  { 0.038844675876537629, -0.053705414564907981 },

  /* Expression: pInitialization.L
   * Referenced by: '<S370>/KalmanGainL'
   */
  { 0.13177446878757812, -0.0 },

  /* Expression: pInitialization.Z
   * Referenced by: '<S253>/CovarianceZ'
   */
  { 0.0023587721054684182, 0.0011153936837442074, 0.0011153936837442074,
    0.001056122002301506 },

  /* Expression: pInitialization.Z
   * Referenced by: '<S313>/CovarianceZ'
   */
  { 0.038576148803713059, -0.053705414564908134, -0.053705414564908134,
    0.43097496723079509 },

  /* Expression: pInitialization.Z
   * Referenced by: '<S370>/CovarianceZ'
   */
  { 0.0065887234393789051, 0.0, 0.0, 0.0 },

  /* Computed Parameter: Gain_Gain
   * Referenced by: '<S8>/Gain'
   */
  0.8F,

  /* Computed Parameter: Gain1_Gain
   * Referenced by: '<S8>/Gain1'
   */
  0.8F,

  /* Computed Parameter: Saturation_yaw2_UpperSat
   * Referenced by: '<S8>/Saturation_yaw2'
   */
  0.5F,

  /* Computed Parameter: Saturation_yaw2_LowerSat
   * Referenced by: '<S8>/Saturation_yaw2'
   */
  -0.5F,

  /* Computed Parameter: Gain1_Gain_a
   * Referenced by: '<S307>/Gain1'
   */
  -1.0F,

  /* Computed Parameter: Constant1_Value_a
   * Referenced by: '<S151>/Constant1'
   */
  0.0F,

  /* Computed Parameter: X0_Value
   * Referenced by: '<S369>/X0'
   */
  { 0.0F, 0.0F },

  /* Computed Parameter: DiscreteTransferFcn_NumCoef
   * Referenced by: '<S424>/Discrete Transfer Fcn'
   */
  { 0.0F, 0.0327839F },

  /* Computed Parameter: DiscreteTransferFcn_DenCoef
   * Referenced by: '<S424>/Discrete Transfer Fcn'
   */
  { 1.0F, -0.967216074F },

  /* Computed Parameter: DiscreteTransferFcn_InitialStat
   * Referenced by: '<S424>/Discrete Transfer Fcn'
   */
  0.0F,

  /* Computed Parameter: DiscreteTransferFcn_NumCoef_k
   * Referenced by: '<S425>/Discrete Transfer Fcn'
   */
  { 0.0F, 0.0327839F },

  /* Computed Parameter: DiscreteTransferFcn_DenCoef_m
   * Referenced by: '<S425>/Discrete Transfer Fcn'
   */
  { 1.0F, -0.967216074F },

  /* Computed Parameter: DiscreteTransferFcn_InitialSt_i
   * Referenced by: '<S425>/Discrete Transfer Fcn'
   */
  0.0F,

  /* Computed Parameter: DiscreteTransferFcn_NumCoef_kj
   * Referenced by: '<S426>/Discrete Transfer Fcn'
   */
  { 0.0F, 0.0327839F },

  /* Computed Parameter: DiscreteTransferFcn_DenCoef_c
   * Referenced by: '<S426>/Discrete Transfer Fcn'
   */
  { 1.0F, -0.967216074F },

  /* Computed Parameter: DiscreteTransferFcn_InitialSt_n
   * Referenced by: '<S426>/Discrete Transfer Fcn'
   */
  0.0F,

  /* Computed Parameter: UnitDelay_InitialCondition
   * Referenced by: '<S308>/Unit Delay'
   */
  0.0F,

  /* Computed Parameter: C_Value
   * Referenced by: '<S369>/C'
   */
  { 1.0F, 0.0F },

  /* Computed Parameter: X0_Value_h
   * Referenced by: '<S312>/X0'
   */
  { 0.0F, 0.0F },

  /* Computed Parameter: UnitDelay_InitialCondition_m
   * Referenced by: '<S307>/Unit Delay'
   */
  0.0F,

  /* Computed Parameter: C_Value_m
   * Referenced by: '<S312>/C'
   */
  { 1.0F, 0.0F },

  /* Computed Parameter: Integrator1_gainval
   * Referenced by: '<S309>/Integrator1'
   */
  0.005F,

  /* Computed Parameter: Integrator1_IC
   * Referenced by: '<S309>/Integrator1'
   */
  0.0F,

  /* Computed Parameter: DeadZone_Start
   * Referenced by: '<S4>/Dead Zone'
   */
  -0.03F,

  /* Computed Parameter: DeadZone_End
   * Referenced by: '<S4>/Dead Zone'
   */
  0.03F,

  /* Computed Parameter: A_Value
   * Referenced by: '<S252>/A'
   */
  { 1.0F, 0.0F, 0.005F, 1.0F },

  /* Computed Parameter: A_Value_b
   * Referenced by: '<S312>/A'
   */
  { 1.0F, 0.0F, -0.005F, 1.0F },

  /* Computed Parameter: A_Value_k
   * Referenced by: '<S369>/A'
   */
  { 1.0F, 0.0F, 0.0F, 0.0F },

  /* Computed Parameter: Saturation4_UpperSat
   * Referenced by: '<S4>/Saturation4'
   */
  2.0F,

  /* Computed Parameter: Saturation4_LowerSat
   * Referenced by: '<S4>/Saturation4'
   */
  -1.0F,

  /* Computed Parameter: Gain3_Gain
   * Referenced by: '<S4>/Gain3'
   */
  4.405F,

  /* Computed Parameter: DiscreteTransferFcn_NumCoef_c
   * Referenced by: '<S429>/Discrete Transfer Fcn'
   */
  { 0.0F, 0.0327839F },

  /* Computed Parameter: DiscreteTransferFcn_DenCoef_b
   * Referenced by: '<S429>/Discrete Transfer Fcn'
   */
  { 1.0F, -0.967216074F },

  /* Computed Parameter: DiscreteTransferFcn_InitialS_il
   * Referenced by: '<S429>/Discrete Transfer Fcn'
   */
  0.0F,

  /* Computed Parameter: DiscreteTransferFcn_NumCoef_a
   * Referenced by: '<S427>/Discrete Transfer Fcn'
   */
  { 0.0F, 0.0327839F },

  /* Computed Parameter: DiscreteTransferFcn_DenCoef_a
   * Referenced by: '<S427>/Discrete Transfer Fcn'
   */
  { 1.0F, -0.967216074F },

  /* Computed Parameter: DiscreteTransferFcn_InitialSt_j
   * Referenced by: '<S427>/Discrete Transfer Fcn'
   */
  0.0F,

  /* Computed Parameter: Saturation1_UpperSat
   * Referenced by: '<S4>/Saturation1'
   */
  1.0F,

  /* Computed Parameter: Saturation1_LowerSat
   * Referenced by: '<S4>/Saturation1'
   */
  -1.0F,

  /* Computed Parameter: Gain_Gain_h
   * Referenced by: '<S4>/Gain'
   */
  0.5236F,

  /* Computed Parameter: Saturation2_UpperSat
   * Referenced by: '<S4>/Saturation2'
   */
  1.0F,

  /* Computed Parameter: Saturation2_LowerSat
   * Referenced by: '<S4>/Saturation2'
   */
  -1.0F,

  /* Computed Parameter: Gain1_Gain_j
   * Referenced by: '<S4>/Gain1'
   */
  0.5236F,

  /* Computed Parameter: RateLimiter_IC
   * Referenced by: '<S7>/Rate Limiter'
   */
  0.0F,

  /* Computed Parameter: Gain1_Gain_p
   * Referenced by: '<S7>/Gain1'
   */
  0.8F,

  /* Computed Parameter: Saturation_pitchroll_UpperSat
   * Referenced by: '<S7>/Saturation_pitchroll'
   */
  0.5233F,

  /* Computed Parameter: Saturation_pitchroll_LowerSat
   * Referenced by: '<S7>/Saturation_pitchroll'
   */
  -0.5233F,

  /* Computed Parameter: Integrator_gainval
   * Referenced by: '<S105>/Integrator'
   */
  1.0F,

  /* Computed Parameter: Filter_gainval
   * Referenced by: '<S100>/Filter'
   */
  0.005F,

  /* Computed Parameter: Integrator_gainval_i
   * Referenced by: '<S163>/Integrator'
   */
  0.005F,

  /* Computed Parameter: Tsamp_WtEt
   * Referenced by: '<S158>/Tsamp'
   */
  200.0F,

  /* Computed Parameter: Saturation_pq_UpperSat
   * Referenced by: '<S7>/Saturation_pq'
   */
  0.2F,

  /* Computed Parameter: Saturation_pq_LowerSat
   * Referenced by: '<S7>/Saturation_pq'
   */
  -0.2F,

  /* Computed Parameter: Gain_Gain_hu
   * Referenced by: '<S7>/Gain'
   */
  { 1.0F, -1.0F },

  /* Computed Parameter: Saturation3_UpperSat
   * Referenced by: '<S4>/Saturation3'
   */
  1.0F,

  /* Computed Parameter: Saturation3_LowerSat
   * Referenced by: '<S4>/Saturation3'
   */
  -1.0F,

  /* Computed Parameter: Gain2_Gain
   * Referenced by: '<S4>/Gain2'
   */
  0.5236F,

  /* Computed Parameter: RateLimiter1_IC
   * Referenced by: '<S8>/Rate Limiter1'
   */
  0.0F,

  /* Computed Parameter: UnitDelay_InitialCondition_n
   * Referenced by: '<S8>/Unit Delay'
   */
  0.0F,

  /* Computed Parameter: DiscreteTransferFcn_NumCoef_o
   * Referenced by: '<S428>/Discrete Transfer Fcn'
   */
  { 0.0F, 0.0327839F },

  /* Computed Parameter: DiscreteTransferFcn_DenCoef_o
   * Referenced by: '<S428>/Discrete Transfer Fcn'
   */
  { 1.0F, -0.967216074F },

  /* Computed Parameter: DiscreteTransferFcn_InitialSt_m
   * Referenced by: '<S428>/Discrete Transfer Fcn'
   */
  0.0F,

  /* Computed Parameter: Integrator_gainval_o
   * Referenced by: '<S221>/Integrator'
   */
  0.005F,

  /* Computed Parameter: Filter_gainval_k
   * Referenced by: '<S216>/Filter'
   */
  0.005F,

  /* Computed Parameter: Bias_Bias
   * Referenced by: '<S5>/Bias'
   */
  48.0F,

  /* Computed Parameter: Saturation5_UpperSat
   * Referenced by: '<S5>/Saturation5'
   */
  2047.0F,

  /* Computed Parameter: Saturation5_LowerSat
   * Referenced by: '<S5>/Saturation5'
   */
  48.0F,

  /* Computed Parameter: Constant_Value_b
   * Referenced by: '<S248>/Constant'
   */
  { 0.0F, 0.0F, -9.81F },

  /* Computed Parameter: B_Value
   * Referenced by: '<S252>/B'
   */
  { 1.25E-5F, 0.005F },

  /* Computed Parameter: X0_Value_a
   * Referenced by: '<S252>/X0'
   */
  { 0.0F, 0.0F },

  /* Computed Parameter: DiscreteTransferFcn_NumCoef_h
   * Referenced by: '<S244>/Discrete Transfer Fcn'
   */
  { 0.0F, 0.0487705767F },

  /* Computed Parameter: DiscreteTransferFcn_DenCoef_n
   * Referenced by: '<S244>/Discrete Transfer Fcn'
   */
  { 1.0F, -0.951229453F },

  /* Computed Parameter: DiscreteTransferFcn_InitialSt_k
   * Referenced by: '<S244>/Discrete Transfer Fcn'
   */
  0.0F,

  /* Computed Parameter: D_Value
   * Referenced by: '<S252>/D'
   */
  0.0F,

  /* Computed Parameter: C_Value_p
   * Referenced by: '<S252>/C'
   */
  { 1.0F, 0.0F },

  /* Computed Parameter: Integrator5_gainval
   * Referenced by: '<S250>/Integrator5'
   */
  0.005F,

  /* Computed Parameter: Integrator5_IC
   * Referenced by: '<S250>/Integrator5'
   */
  0.0F,

  /* Computed Parameter: Integrator1_gainval_f
   * Referenced by: '<S250>/Integrator1'
   */
  0.005F,

  /* Computed Parameter: Integrator1_IC_a
   * Referenced by: '<S250>/Integrator1'
   */
  0.0F,

  /* Computed Parameter: Integrator4_gainval
   * Referenced by: '<S250>/Integrator4'
   */
  0.005F,

  /* Computed Parameter: Integrator4_IC
   * Referenced by: '<S250>/Integrator4'
   */
  0.0F,

  /* Computed Parameter: Integrator2_gainval
   * Referenced by: '<S250>/Integrator2'
   */
  0.005F,

  /* Computed Parameter: Integrator2_IC
   * Referenced by: '<S250>/Integrator2'
   */
  0.0F,

  /* Computed Parameter: Clamping_zero_Value
   * Referenced by: '<S151>/Clamping_zero'
   */
  0.0F,

  /* Computed Parameter: B_Value_l
   * Referenced by: '<S312>/B'
   */
  { 0.005F, 0.0F },

  /* Computed Parameter: D_Value_a
   * Referenced by: '<S312>/D'
   */
  0.0F,

  /* Computed Parameter: B_Value_lw
   * Referenced by: '<S369>/B'
   */
  { 0.005F, 0.0F },

  /* Computed Parameter: D_Value_d
   * Referenced by: '<S369>/D'
   */
  0.0F,

  /* Expression: true()
   * Referenced by: '<S369>/Enable'
   */
  true,

  /* Expression: true()
   * Referenced by: '<S312>/Enable'
   */
  true,

  /* Expression: true()
   * Referenced by: '<S252>/Enable'
   */
  true,

  /* Expression: pInitialization.isSqrtUsed
   * Referenced by: '<S302>/isSqrtUsed'
   */
  false,

  /* Expression: pInitialization.isSqrtUsed
   * Referenced by: '<S362>/isSqrtUsed'
   */
  false,

  /* Expression: pInitialization.isSqrtUsed
   * Referenced by: '<S419>/isSqrtUsed'
   */
  false,

  /* Computed Parameter: Constant_Value_m
   * Referenced by: '<S151>/Constant'
   */
  1,

  /* Computed Parameter: Constant2_Value
   * Referenced by: '<S151>/Constant2'
   */
  -1,

  /* Computed Parameter: Constant3_Value
   * Referenced by: '<S151>/Constant3'
   */
  1,

  /* Computed Parameter: Constant4_Value
   * Referenced by: '<S151>/Constant4'
   */
  -1,

  /* Start of '<S397>/Enabled Subsystem' */
  {
    /* Computed Parameter: deltax_Y0
     * Referenced by: '<S423>/deltax'
     */
    0.0F
  }
  ,

  /* End of '<S397>/Enabled Subsystem' */

  /* Start of '<S390>/MeasurementUpdate' */
  {
    /* Computed Parameter: Lykyhatkk1_Y0
     * Referenced by: '<S421>/L*(y[k]-yhat[k|k-1])'
     */
    0.0F
  }
  ,

  /* End of '<S390>/MeasurementUpdate' */

  /* Start of '<S340>/Enabled Subsystem' */
  {
    /* Computed Parameter: deltax_Y0
     * Referenced by: '<S366>/deltax'
     */
    0.0F
  }
  ,

  /* End of '<S340>/Enabled Subsystem' */

  /* Start of '<S333>/MeasurementUpdate' */
  {
    /* Computed Parameter: Lykyhatkk1_Y0
     * Referenced by: '<S364>/L*(y[k]-yhat[k|k-1])'
     */
    0.0F
  }
  ,

  /* End of '<S333>/MeasurementUpdate' */

  /* Start of '<S280>/Enabled Subsystem' */
  {
    /* Computed Parameter: deltax_Y0
     * Referenced by: '<S306>/deltax'
     */
    0.0F
  }
  ,

  /* End of '<S280>/Enabled Subsystem' */

  /* Start of '<S273>/MeasurementUpdate' */
  {
    /* Computed Parameter: Lykyhatkk1_Y0
     * Referenced by: '<S304>/L*(y[k]-yhat[k|k-1])'
     */
    0.0F
  }
  /* End of '<S273>/MeasurementUpdate' */
};

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
