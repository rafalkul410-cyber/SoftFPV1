/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: FCS.c
 *
 * Code generated for Simulink model 'FCS'.
 *
 * Model version                  : 1.21
 * Simulink Coder version         : 25.2 (R2025b) 28-Jul-2025
 * C/C++ source code generated on : Mon Aug 10 22:44:58 2026
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-M
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. RAM efficiency
 * Validation result: Not run
 */

#include "FCS.h"
#include "rtwtypes.h"
#include <math.h>
#include <string.h>

/* Block signals and states (default storage) */
DW rtDW;

/* External inputs (root inport signals with default storage) */
ExtU rtU;

/* External outputs (root outports fed by signals with default storage) */
ExtY rtY;

/* Real-time model */
static RT_MODEL rtM_;
RT_MODEL *const rtM = &rtM_;
static void SqrtUsedFcn(const real32_T rtu_u[4], boolean_T rtu_isSqrtUsed,
  real32_T rty_P[4]);
static void MeasurementUpdate_Disable(real32_T rty_Lykyhatkk1[2],
  DW_MeasurementUpdate *localDW);
static void MeasurementUpdate(boolean_T rtu_Enable, const real32_T rtu_Lk[2],
  real32_T rtu_yk, const real32_T rtu_Ck[2], const real32_T rtu_xhatkk1[2],
  real32_T rtu_Dk, real32_T rtu_uk, real32_T rty_Lykyhatkk1[2],
  DW_MeasurementUpdate *localDW);
static void EnabledSubsystem_Disable(real32_T rty_deltax[2], DW_EnabledSubsystem
  *localDW);
static void EnabledSubsystem(boolean_T rtu_Enable, const real32_T rtu_Mk[2],
  const real32_T rtu_Ck[2], real32_T rtu_yk, const real32_T rtu_xhatkk1[2],
  real32_T rty_deltax[2], DW_EnabledSubsystem *localDW);

/*
 * Output and update for atomic system:
 *    '<S396>/SqrtUsedFcn'
 *    '<S454>/SqrtUsedFcn'
 */
static void SqrtUsedFcn(const real32_T rtu_u[4], boolean_T rtu_isSqrtUsed,
  real32_T rty_P[4])
{
  int32_T i;
  if (rtu_isSqrtUsed) {
    for (i = 0; i < 2; i++) {
      real32_T tmp;
      tmp = rtu_u[i + 2];
      rty_P[i] = tmp * rtu_u[2] + rtu_u[i] * rtu_u[0];
      rty_P[i + 2] = tmp * rtu_u[3] + rtu_u[i] * rtu_u[1];
    }
  } else {
    for (i = 0; i < 2; i++) {
      rty_P[i] = rtu_u[i];
      rty_P[i + 2] = rtu_u[i + 2];
    }
  }
}

/*
 * Disable for enable system:
 *    '<S367>/MeasurementUpdate'
 *    '<S425>/MeasurementUpdate'
 */
static void MeasurementUpdate_Disable(real32_T rty_Lykyhatkk1[2],
  DW_MeasurementUpdate *localDW)
{
  /* Outputs for Enabled SubSystem: '<S367>/MeasurementUpdate' incorporates:
   *  EnablePort: '<S398>/Enable'
   */
  /* Disable for Outport: '<S398>/L*(y[k]-yhat[k|k-1])' */
  rty_Lykyhatkk1[0] = 0.0F;
  rty_Lykyhatkk1[1] = 0.0F;

  /* End of Outputs for SubSystem: '<S367>/MeasurementUpdate' */
  localDW->MeasurementUpdate_MODE = false;
}

/*
 * Output and update for enable system:
 *    '<S367>/MeasurementUpdate'
 *    '<S425>/MeasurementUpdate'
 */
static void MeasurementUpdate(boolean_T rtu_Enable, const real32_T rtu_Lk[2],
  real32_T rtu_yk, const real32_T rtu_Ck[2], const real32_T rtu_xhatkk1[2],
  real32_T rtu_Dk, real32_T rtu_uk, real32_T rty_Lykyhatkk1[2],
  DW_MeasurementUpdate *localDW)
{
  real32_T rtb_Sum_k;

  /* Outputs for Enabled SubSystem: '<S367>/MeasurementUpdate' incorporates:
   *  EnablePort: '<S398>/Enable'
   */
  if (rtu_Enable) {
    localDW->MeasurementUpdate_MODE = true;

    /* Sum: '<S398>/Sum' incorporates:
     *  Product: '<S398>/C[k]*xhat[k|k-1]'
     *  Product: '<S398>/D[k]*u[k]'
     *  Sum: '<S398>/Add1'
     */
    rtb_Sum_k = rtu_yk - ((rtu_Ck[0] * rtu_xhatkk1[0] + rtu_Ck[1] * rtu_xhatkk1
      [1]) + rtu_Dk * rtu_uk);

    /* Product: '<S398>/Product3' */
    rty_Lykyhatkk1[0] = rtu_Lk[0] * rtb_Sum_k;
    rty_Lykyhatkk1[1] = rtu_Lk[1] * rtb_Sum_k;
  } else if (localDW->MeasurementUpdate_MODE) {
    MeasurementUpdate_Disable(rty_Lykyhatkk1, localDW);
  }

  /* End of Outputs for SubSystem: '<S367>/MeasurementUpdate' */
}

/*
 * Disable for enable system:
 *    '<S374>/Enabled Subsystem'
 *    '<S432>/Enabled Subsystem'
 */
static void EnabledSubsystem_Disable(real32_T rty_deltax[2], DW_EnabledSubsystem
  *localDW)
{
  /* Outputs for Enabled SubSystem: '<S374>/Enabled Subsystem' incorporates:
   *  EnablePort: '<S400>/Enable'
   */
  /* Disable for Outport: '<S400>/deltax' */
  rty_deltax[0] = 0.0F;
  rty_deltax[1] = 0.0F;

  /* End of Outputs for SubSystem: '<S374>/Enabled Subsystem' */
  localDW->EnabledSubsystem_MODE = false;
}

/*
 * Output and update for enable system:
 *    '<S374>/Enabled Subsystem'
 *    '<S432>/Enabled Subsystem'
 */
static void EnabledSubsystem(boolean_T rtu_Enable, const real32_T rtu_Mk[2],
  const real32_T rtu_Ck[2], real32_T rtu_yk, const real32_T rtu_xhatkk1[2],
  real32_T rty_deltax[2], DW_EnabledSubsystem *localDW)
{
  real32_T rtb_Add1;

  /* Outputs for Enabled SubSystem: '<S374>/Enabled Subsystem' incorporates:
   *  EnablePort: '<S400>/Enable'
   */
  if (rtu_Enable) {
    localDW->EnabledSubsystem_MODE = true;

    /* Sum: '<S400>/Add1' incorporates:
     *  Product: '<S400>/Product'
     */
    rtb_Add1 = rtu_yk - (rtu_Ck[0] * rtu_xhatkk1[0] + rtu_Ck[1] * rtu_xhatkk1[1]);

    /* Product: '<S400>/Product2' */
    rty_deltax[0] = rtu_Mk[0] * rtb_Add1;
    rty_deltax[1] = rtu_Mk[1] * rtb_Add1;
  } else if (localDW->EnabledSubsystem_MODE) {
    EnabledSubsystem_Disable(rty_deltax, localDW);
  }

  /* End of Outputs for SubSystem: '<S374>/Enabled Subsystem' */
}

/* Model step function */
void FCS_step(void)
{
  real_T rtb_MathFunction[9];
  real_T rtb_MathFunction_0[9];
  real_T Product2;
  real_T pData_idx_0;
  real_T pData_idx_1;
  real_T pData_idx_1_tmp;
  real_T pData_idx_2_tmp;
  real_T pData_idx_4;
  real_T pData_idx_6;
  real_T pData_idx_6_tmp;
  real_T pData_idx_7;
  real_T pData_idx_7_tmp;
  real_T pData_tmp;
  real_T pData_tmp_0;
  real_T pData_tmp_1;
  real_T rtb_Akxhatkk1_idx_0;
  real_T rtb_Atan;
  real_T rtb_Sum;
  int32_T i;
  int32_T tmp_3;
  real32_T rtb_P_nk[4];
  real32_T rtb_Minus[3];
  real32_T rtb_Add_m_idx_0;
  real32_T rtb_Add_m_idx_1;
  real32_T rtb_Add_n_idx_0;
  real32_T rtb_Asin;
  real32_T rtb_DiscreteTransferFcn;
  real32_T rtb_DiscreteTransferFcn_dw;
  real32_T rtb_DiscreteTransferFcn_l;
  real32_T rtb_FilterCoefficient_a_0;
  real32_T rtb_FilterCoefficient_a_idx_0;
  real32_T rtb_Gain_p;
  real32_T rtb_Integrator_cs;
  real32_T rtb_Integrator_g_0;
  real32_T rtb_Integrator_g_idx_0;
  real32_T rtb_Integrator_g_idx_1;
  real32_T rtb_Integrator_n;
  real32_T rtb_Saturation;
  real32_T rtb_Saturation_a;
  real32_T rtb_Sum1_k_idx_0;
  real32_T rtb_Sum1_k_idx_1;
  real32_T rtb_Sum_h_idx_1;
  real32_T rtb_Sum_j;
  real32_T tmp;
  real32_T tmp_0;
  real32_T tmp_1;
  real32_T tmp_2;
  real32_T u0;
  real32_T u0_tmp;
  boolean_T rtb_Compare;
  boolean_T rtb_OR;

  /* Delay: '<S459>/MemoryX' incorporates:
   *  Constant: '<S459>/X0'
   */
  if (rtDW.icLoad) {
    rtDW.MemoryX_DSTATE[0] = 0.0;
    rtDW.MemoryX_DSTATE[1] = 0.0;
  }

  /* DiscreteTransferFcn: '<S517>/Discrete Transfer Fcn' */
  rtb_Sum_j = 0.63212055F * rtDW.DiscreteTransferFcn_states;

  /* DiscreteTransferFcn: '<S518>/Discrete Transfer Fcn' */
  rtb_Integrator_cs = 0.63212055F * rtDW.DiscreteTransferFcn_states_e;

  /* Trigonometry: '<S402>/Atan' incorporates:
   *  Constant: '<S402>/Constant'
   *  Product: '<S402>/Divide'
   *  Sum: '<S402>/Sum'
   */
  rtb_Atan = atan(rtb_Sum_j / (rtb_Integrator_cs + 1.0E-6));

  /* Outputs for Enabled SubSystem: '<S487>/Enabled Subsystem' incorporates:
   *  EnablePort: '<S513>/Enable'
   */
  /* Product: '<S513>/Product2' incorporates:
   *  Constant: '<S459>/C'
   *  Constant: '<S460>/KalmanGainM'
   *  Delay: '<S459>/MemoryX'
   *  Product: '<S513>/Product'
   *  Sum: '<S513>/Add1'
   */
  Product2 = (rtb_Atan - (0.0 * rtDW.MemoryX_DSTATE[1] + rtDW.MemoryX_DSTATE[0]))
    * 0.20394675669207771;

  /* End of Outputs for SubSystem: '<S487>/Enabled Subsystem' */

  /* Sum: '<S487>/Add' incorporates:
   *  Delay: '<S459>/MemoryX'
   */
  rtb_Akxhatkk1_idx_0 = Product2 + rtDW.MemoryX_DSTATE[0];

  /* Delay: '<S404>/MemoryX' incorporates:
   *  Constant: '<S404>/X0'
   */
  if (rtDW.icLoad_e) {
    rtDW.MemoryX_DSTATE_m[0] = 0.0F;
    rtDW.MemoryX_DSTATE_m[1] = 0.0F;
  }

  /* DiscreteTransferFcn: '<S519>/Discrete Transfer Fcn' */
  rtb_Integrator_n = 0.63212055F * rtDW.DiscreteTransferFcn_states_b;

  /* Gain: '<S401>/Gain' */
  rtb_Sum1_k_idx_0 = 0.101936802F * rtb_Integrator_n;

  /* Trigonometry: '<S401>/Asin' */
  if (rtb_Sum1_k_idx_0 > 1.0F) {
    rtb_Sum1_k_idx_0 = 1.0F;
  } else if (rtb_Sum1_k_idx_0 < -1.0F) {
    rtb_Sum1_k_idx_0 = -1.0F;
  }

  rtb_Asin = asinf(rtb_Sum1_k_idx_0);

  /* End of Trigonometry: '<S401>/Asin' */

  /* Outputs for Enabled SubSystem: '<S432>/Enabled Subsystem' */
  /* Constant: '<S404>/Enable' incorporates:
   *  Constant: '<S404>/C'
   *  Delay: '<S404>/MemoryX'
   */
  EnabledSubsystem(true, rtConstB.Conversion_p, rtConstP.pooled7, rtb_Asin,
                   rtDW.MemoryX_DSTATE_m, rtDW.Product2_d,
                   &rtDW.EnabledSubsystem_p);

  /* End of Outputs for SubSystem: '<S432>/Enabled Subsystem' */

  /* Sum: '<S432>/Add' incorporates:
   *  Delay: '<S404>/MemoryX'
   */
  rtb_Add_n_idx_0 = rtDW.Product2_d[0] + rtDW.MemoryX_DSTATE_m[0];

  /* Angle2Dcm: '<S342>/Rotation Angles to Direction Cosine Matrix' incorporates:
   *  DataTypeConversion: '<S342>/Data Type Conversion3'
   *  DataTypeConversion: '<S402>/Data Type Conversion3'
   *  DiscreteIntegrator: '<S403>/Integrator1'
   *  Math: '<S342>/Math Function'
   */
  rtb_Sum = cos(rtDW.Integrator1_DSTATE);
  pData_tmp = sin(rtDW.Integrator1_DSTATE);
  pData_tmp_1 = cos(rtb_Add_n_idx_0);
  pData_tmp_0 = sin(rtb_Add_n_idx_0);
  pData_idx_0 = 0.0 * pData_tmp_0 + pData_tmp_1;
  pData_idx_6_tmp = 0.0 * pData_tmp_1;
  pData_idx_6 = pData_idx_6_tmp - pData_tmp_0;
  pData_idx_1_tmp = rtb_Sum * 0.0;
  pData_idx_1 = (pData_idx_6_tmp + pData_idx_1_tmp) + pData_tmp * pData_tmp_0;
  pData_idx_4 = pData_tmp * 0.0 + rtb_Sum;
  pData_idx_7_tmp = 0.0 * -pData_tmp_0;
  pData_idx_7 = (pData_idx_7_tmp + pData_idx_1_tmp) + pData_tmp * pData_tmp_1;
  pData_idx_2_tmp = -pData_tmp * 0.0;
  pData_tmp_0 = (pData_idx_6_tmp + pData_idx_2_tmp) + pData_tmp_0 * rtb_Sum;
  pData_idx_1_tmp -= pData_tmp;
  pData_tmp_1 = (pData_idx_7_tmp + pData_idx_2_tmp) + rtb_Sum * pData_tmp_1;
  rtb_Sum = cos((real32_T)rtb_Akxhatkk1_idx_0);
  pData_tmp = sin((real32_T)rtb_Akxhatkk1_idx_0);
  pData_idx_7_tmp = pData_idx_6 * 0.0;
  rtb_MathFunction[0] = (pData_idx_0 * rtb_Sum + 0.0 * -pData_tmp) +
    pData_idx_7_tmp;
  pData_idx_2_tmp = pData_idx_7 * 0.0;
  rtb_MathFunction[1] = (rtb_Sum * pData_idx_1 + -pData_tmp * pData_idx_4) +
    pData_idx_2_tmp;
  pData_idx_6_tmp = pData_tmp_1 * 0.0;
  rtb_MathFunction[2] = (rtb_Sum * pData_tmp_0 + -pData_tmp * pData_idx_1_tmp) +
    pData_idx_6_tmp;
  rtb_MathFunction[3] = (pData_idx_0 * pData_tmp + 0.0 * rtb_Sum) +
    pData_idx_7_tmp;
  rtb_MathFunction[4] = (pData_tmp * pData_idx_1 + pData_idx_4 * rtb_Sum) +
    pData_idx_2_tmp;
  rtb_MathFunction[5] = (pData_tmp * pData_tmp_0 + rtb_Sum * pData_idx_1_tmp) +
    pData_idx_6_tmp;
  rtb_MathFunction[6] = pData_idx_0 * 0.0 + pData_idx_6;
  rtb_MathFunction[7] = (pData_idx_1 * 0.0 + pData_idx_4 * 0.0) + pData_idx_7;
  rtb_MathFunction[8] = (pData_tmp_0 * 0.0 + pData_idx_1_tmp * 0.0) +
    pData_tmp_1;

  /* Math: '<S342>/Math Function' */
  for (i = 0; i < 3; i++) {
    rtb_MathFunction_0[3 * i] = rtb_MathFunction[i];
    rtb_MathFunction_0[3 * i + 1] = rtb_MathFunction[i + 3];
    rtb_MathFunction_0[3 * i + 2] = rtb_MathFunction[i + 6];
  }

  memcpy(&rtb_MathFunction[0], &rtb_MathFunction_0[0], 9U * sizeof(real_T));

  /* End of Math: '<S342>/Math Function' */

  /* RelationalOperator: '<S10>/Compare' incorporates:
   *  Constant: '<S10>/Constant'
   *  UnitDelay: '<S11>/Output'
   */
  rtb_Compare = (rtDW.Output_DSTATE <= 500);

  /* Logic: '<S5>/OR' incorporates:
   *  Inport: '<Root>/controlModePosVSOrient'
   */
  rtb_OR = (rtb_Compare || rtU.controlModePosVSOrient);

  /* DiscreteIntegrator: '<S5>/Integrator1' */
  if ((!rtb_OR) && (rtDW.Integrator1_PrevResetState == 1)) {
    rtDW.Integrator1_DSTATE_i = 0.0F;
  }

  /* Delay: '<S346>/MemoryX' incorporates:
   *  Constant: '<S346>/X0'
   */
  if (rtDW.icLoad_h) {
    rtDW.MemoryX_DSTATE_h[0] = 0.0F;
    rtDW.MemoryX_DSTATE_h[1] = 0.0F;
  }

  /* Gain: '<S345>/Gain' incorporates:
   *  Constant: '<S345>/Constant'
   *  DiscreteTransferFcn: '<S338>/Discrete Transfer Fcn'
   *  Sum: '<S345>/Add'
   */
  rtb_Gain_p = (1013.25F - 0.0487705767F * rtDW.DiscreteTransferFcn_states_m) *
    0.0832639486F;

  /* Outputs for Enabled SubSystem: '<S374>/Enabled Subsystem' */
  /* Constant: '<S346>/Enable' incorporates:
   *  Constant: '<S346>/C'
   *  Delay: '<S346>/MemoryX'
   */
  EnabledSubsystem(true, rtConstB.Conversion_n, rtConstP.pooled7, rtb_Gain_p,
                   rtDW.MemoryX_DSTATE_h, rtDW.Product2_b,
                   &rtDW.EnabledSubsystem_e);

  /* End of Outputs for SubSystem: '<S374>/Enabled Subsystem' */

  /* Sum: '<S374>/Add' incorporates:
   *  Delay: '<S346>/MemoryX'
   */
  rtb_Add_m_idx_0 = rtDW.Product2_b[0] + rtDW.MemoryX_DSTATE_h[0];
  rtb_Add_m_idx_1 = rtDW.Product2_b[1] + rtDW.MemoryX_DSTATE_h[1];

  /* Sum: '<S5>/Sum1' incorporates:
   *  Gain: '<S5>/Gain5'
   *  Inport: '<Root>/pos_ref'
   */
  rtb_Saturation = rtU.pos_ref[2] - (-rtb_Add_m_idx_0);

  /* Saturate: '<S5>/Saturation' */
  if (rtb_Saturation > 0.5F) {
    rtb_Saturation = 0.5F;
  } else if (rtb_Saturation < -0.5F) {
    rtb_Saturation = -0.5F;
  }

  /* End of Saturate: '<S5>/Saturation' */

  /* Sum: '<S9>/Sum' incorporates:
   *  DiscreteIntegrator: '<S403>/Integrator1'
   *  Inport: '<Root>/orient_ref'
   */
  rtb_Saturation_a = rtU.orient_ref[0] - rtDW.Integrator1_DSTATE;

  /* Saturate: '<S9>/Saturation' */
  if (rtb_Saturation_a > 0.52359879F) {
    rtb_Saturation_a = 0.52359879F;
  } else if (rtb_Saturation_a < -0.52359879F) {
    rtb_Saturation_a = -0.52359879F;
  }

  /* End of Saturate: '<S9>/Saturation' */

  /* DiscreteTransferFcn: '<S515>/Discrete Transfer Fcn' */
  rtb_DiscreteTransferFcn = 0.917915F * rtDW.DiscreteTransferFcn_states_l;

  /* DiscreteTransferFcn: '<S516>/Discrete Transfer Fcn' */
  rtb_DiscreteTransferFcn_dw = 0.917915F * rtDW.DiscreteTransferFcn_states_f;

  /* DiscreteTransferFcn: '<S514>/Discrete Transfer Fcn' */
  rtb_DiscreteTransferFcn_l = 0.917915F * rtDW.DiscreteTransferFcn_states_bf;

  /* Switch: '<S2>/Switch' incorporates:
   *  DiscreteTransferFcn: '<S19>/Discrete Transfer Fcn'
   *  DiscreteTransferFcn: '<S20>/Discrete Transfer Fcn'
   *  Gain: '<S7>/Gain1'
   *  Inport: '<Root>/controlModePosVSOrient'
   *  Inport: '<Root>/orient_ref'
   */
  if (rtU.controlModePosVSOrient) {
    rtb_Integrator_g_idx_0 = 0.221199214F * rtDW.DiscreteTransferFcn_states_li;
    rtb_Integrator_g_idx_1 = -(0.221199214F * rtDW.DiscreteTransferFcn_states_h);
  } else {
    rtb_Integrator_g_idx_0 = rtU.orient_ref[1];
    rtb_Integrator_g_idx_1 = rtU.orient_ref[2];
  }

  /* End of Switch: '<S2>/Switch' */

  /* Sum: '<S8>/Sum' incorporates:
   *  DataTypeConversion: '<S402>/Data Type Conversion3'
   */
  rtb_Integrator_g_idx_1 -= (real32_T)rtb_Akxhatkk1_idx_0;
  rtb_Sum_h_idx_1 = rtb_Integrator_g_idx_0 - rtb_Add_n_idx_0;

  /* Gain: '<S268>/Filter Coefficient' incorporates:
   *  DiscreteIntegrator: '<S260>/Filter'
   *  Gain: '<S258>/Derivative Gain'
   *  Sum: '<S260>/SumD'
   */
  rtb_Integrator_g_0 = (0.0F * rtb_Integrator_g_idx_1 - rtDW.Filter_DSTATE[0]) *
    78.6938705F;
  rtb_Integrator_g_idx_0 = rtb_Integrator_g_0;

  /* Sum: '<S274>/Sum' incorporates:
   *  DiscreteIntegrator: '<S265>/Integrator'
   *  Gain: '<S258>/Derivative Gain'
   */
  rtb_Sum1_k_idx_0 = (rtb_Integrator_g_idx_1 + rtDW.Integrator_DSTATE_n[0]) +
    rtb_Integrator_g_0;

  /* Gain: '<S268>/Filter Coefficient' incorporates:
   *  DiscreteIntegrator: '<S260>/Filter'
   *  Gain: '<S258>/Derivative Gain'
   *  Sum: '<S260>/SumD'
   */
  rtb_Integrator_g_0 = (0.0F * rtb_Sum_h_idx_1 - rtDW.Filter_DSTATE[1]) *
    78.6938705F;

  /* Sum: '<S8>/Sum1' incorporates:
   *  DiscreteIntegrator: '<S265>/Integrator'
   *  Gain: '<S258>/Derivative Gain'
   *  Sum: '<S274>/Sum'
   */
  rtb_Sum1_k_idx_0 -= rtb_DiscreteTransferFcn_dw;
  rtb_Sum1_k_idx_1 = ((rtb_Sum_h_idx_1 + rtDW.Integrator_DSTATE_n[1]) +
                      rtb_Integrator_g_0) - rtb_DiscreteTransferFcn_l;

  /* Gain: '<S320>/Filter Coefficient' incorporates:
   *  DiscreteIntegrator: '<S312>/Filter'
   *  Gain: '<S310>/Derivative Gain'
   *  Sum: '<S312>/SumD'
   */
  rtb_FilterCoefficient_a_0 = (0.00012F * rtb_Sum1_k_idx_0 -
    rtDW.Filter_DSTATE_e[0]) * 70.0F;
  rtb_FilterCoefficient_a_idx_0 = rtb_FilterCoefficient_a_0;

  /* Gain: '<S322>/Proportional Gain' incorporates:
   *  Gain: '<S310>/Derivative Gain'
   *  Gain: '<S314>/Integral Gain'
   */
  u0_tmp = 0.003F * rtb_Sum1_k_idx_0;

  /* Sum: '<S326>/Sum' incorporates:
   *  DiscreteIntegrator: '<S317>/Integrator'
   *  Gain: '<S322>/Proportional Gain'
   */
  rtb_Sum1_k_idx_0 = (u0_tmp + rtDW.Integrator_DSTATE_b[0]) +
    rtb_FilterCoefficient_a_0;

  /* Gain: '<S320>/Filter Coefficient' incorporates:
   *  DiscreteIntegrator: '<S312>/Filter'
   *  Gain: '<S310>/Derivative Gain'
   *  Sum: '<S312>/SumD'
   */
  rtb_FilterCoefficient_a_0 = (9.72E-5F * rtb_Sum1_k_idx_1 -
    rtDW.Filter_DSTATE_e[1]) * 70.0F;

  /* Gain: '<S322>/Proportional Gain' incorporates:
   *  Gain: '<S310>/Derivative Gain'
   *  Gain: '<S314>/Integral Gain'
   */
  rtb_Sum1_k_idx_1 *= 0.00243F;

  /* Sum: '<S326>/Sum' incorporates:
   *  DiscreteIntegrator: '<S317>/Integrator'
   *  Gain: '<S322>/Proportional Gain'
   */
  u0 = (rtb_Sum1_k_idx_1 + rtDW.Integrator_DSTATE_b[1]) +
    rtb_FilterCoefficient_a_0;

  /* Switch: '<S5>/Switch' incorporates:
   *  Gain: '<S5>/Gain4'
   *  Inport: '<Root>/controlModePosVSOrient'
   *  Inport: '<Root>/orient_ref'
   *  Switch: '<S5>/Switch1'
   */
  if (rtb_Compare) {
    tmp_2 = -9.41760063F;
  } else if (rtU.controlModePosVSOrient) {
    /* Switch: '<S5>/Switch1' incorporates:
     *  DiscreteIntegrator: '<S5>/Integrator1'
     *  Gain: '<S5>/Gain1'
     *  Gain: '<S5>/Gain2'
     *  Sum: '<S5>/Sum2'
     */
    tmp_2 = (0.8F * rtb_Saturation + rtDW.Integrator1_DSTATE_i) - 0.001F *
      rtb_Add_m_idx_1;
  } else {
    tmp_2 = 15.696F * rtU.orient_ref[3];
  }

  /* Saturate: '<S5>/SaturationThrust1' incorporates:
   *  Sum: '<S5>/Sum'
   *  Switch: '<S5>/Switch'
   */
  if (tmp_2 - 7.848F > 16.0F) {
    /* SignalConversion generated from: '<S4>/Matrix Multiply' */
    rtb_P_nk[0] = 16.0F;
  } else if (tmp_2 - 7.848F < 0.0F) {
    /* SignalConversion generated from: '<S4>/Matrix Multiply' */
    rtb_P_nk[0] = 0.0F;
  } else {
    /* SignalConversion generated from: '<S4>/Matrix Multiply' */
    rtb_P_nk[0] = tmp_2 - 7.848F;
  }

  /* End of Saturate: '<S5>/SaturationThrust1' */

  /* SignalConversion generated from: '<S4>/Matrix Multiply' incorporates:
   *  DiscreteIntegrator: '<S9>/Integrator'
   *  Gain: '<S9>/Gain1'
   *  Gain: '<S9>/Gain2'
   *  Sum: '<S9>/Sum1'
   */
  rtb_P_nk[1] = (0.002F * rtb_Saturation_a + rtDW.Integrator_DSTATE) - 8.0E-6F *
    rtb_DiscreteTransferFcn;

  /* Saturate: '<S324>/Saturation' */
  if (u0 > 0.2F) {
    /* SignalConversion generated from: '<S4>/Matrix Multiply' */
    rtb_P_nk[2] = 0.2F;
  } else if (u0 < -0.2F) {
    /* SignalConversion generated from: '<S4>/Matrix Multiply' */
    rtb_P_nk[2] = -0.2F;
  } else {
    /* SignalConversion generated from: '<S4>/Matrix Multiply' */
    rtb_P_nk[2] = u0;
  }

  if (rtb_Sum1_k_idx_0 > 0.2F) {
    /* SignalConversion generated from: '<S4>/Matrix Multiply' */
    rtb_P_nk[3] = 0.2F;
  } else if (rtb_Sum1_k_idx_0 < -0.2F) {
    /* SignalConversion generated from: '<S4>/Matrix Multiply' */
    rtb_P_nk[3] = -0.2F;
  } else {
    /* SignalConversion generated from: '<S4>/Matrix Multiply' */
    rtb_P_nk[3] = rtb_Sum1_k_idx_0;
  }

  /* End of Saturate: '<S324>/Saturation' */

  /* Product: '<S4>/Matrix Multiply' incorporates:
   *  Constant: '<S4>/TorqueTotalThrustToThrustPerMotor'
   */
  tmp = 0.0F;
  tmp_0 = 0.0F;
  u0 = 0.0F;
  tmp_1 = 0.0F;
  for (i = 0; i < 4; i++) {
    tmp_2 = rtb_P_nk[i];
    tmp_3 = i << 2;
    tmp += rtConstP.TorqueTotalThrustToThrustPerMot[tmp_3] * tmp_2;
    tmp_0 += rtConstP.TorqueTotalThrustToThrustPerMot[tmp_3 + 1] * tmp_2;
    u0 += rtConstP.TorqueTotalThrustToThrustPerMot[tmp_3 + 2] * tmp_2;
    tmp_1 += rtConstP.TorqueTotalThrustToThrustPerMot[tmp_3 + 3] * tmp_2;
  }

  /* End of Product: '<S4>/Matrix Multiply' */

  /* Saturate: '<S6>/Saturation' */
  if (tmp > 8.0F) {
    tmp = 8.0F;
  } else if (tmp < -8.0F) {
    tmp = -8.0F;
  }

  /* Saturate: '<S6>/Saturation5' incorporates:
   *  Gain: '<S6>/ThrustToMotorCommand'
   *  Saturate: '<S6>/Saturation'
   */
  rtb_Sum1_k_idx_0 = 255.875F * tmp;
  if (rtb_Sum1_k_idx_0 < 48.0F) {
    /* Outport: '<Root>/FCSb' incorporates:
     *  Gain: '<S6>/MotorDirections'
     */
    rtY.FCSb[0] = 48.0F;
  } else {
    /* Outport: '<Root>/FCSb' incorporates:
     *  Gain: '<S6>/MotorDirections'
     */
    rtY.FCSb[0] = rtb_Sum1_k_idx_0;
  }

  /* Saturate: '<S6>/Saturation' */
  if (tmp_0 > 8.0F) {
    tmp_0 = 8.0F;
  } else if (tmp_0 < -8.0F) {
    tmp_0 = -8.0F;
  }

  /* Saturate: '<S6>/Saturation5' incorporates:
   *  Gain: '<S6>/MotorDirections'
   *  Gain: '<S6>/ThrustToMotorCommand'
   *  Saturate: '<S6>/Saturation'
   */
  rtb_Sum1_k_idx_0 = -(255.875F * tmp_0);
  if (rtb_Sum1_k_idx_0 < 48.0F) {
    /* Outport: '<Root>/FCSb' */
    rtY.FCSb[1] = 48.0F;
  } else {
    /* Outport: '<Root>/FCSb' */
    rtY.FCSb[1] = rtb_Sum1_k_idx_0;
  }

  /* Saturate: '<S6>/Saturation' */
  if (u0 > 8.0F) {
    u0 = 8.0F;
  } else if (u0 < -8.0F) {
    u0 = -8.0F;
  }

  /* Saturate: '<S6>/Saturation5' incorporates:
   *  Gain: '<S6>/ThrustToMotorCommand'
   *  Saturate: '<S6>/Saturation'
   */
  rtb_Sum1_k_idx_0 = 255.875F * u0;
  if (rtb_Sum1_k_idx_0 < 48.0F) {
    /* Outport: '<Root>/FCSb' incorporates:
     *  Gain: '<S6>/MotorDirections'
     */
    rtY.FCSb[2] = 48.0F;
  } else {
    /* Outport: '<Root>/FCSb' incorporates:
     *  Gain: '<S6>/MotorDirections'
     */
    rtY.FCSb[2] = rtb_Sum1_k_idx_0;
  }

  /* Saturate: '<S6>/Saturation' */
  if (tmp_1 > 8.0F) {
    tmp_1 = 8.0F;
  } else if (tmp_1 < -8.0F) {
    tmp_1 = -8.0F;
  }

  /* Saturate: '<S6>/Saturation5' incorporates:
   *  Gain: '<S6>/MotorDirections'
   *  Gain: '<S6>/ThrustToMotorCommand'
   *  Saturate: '<S6>/Saturation'
   */
  rtb_Sum1_k_idx_0 = -(255.875F * tmp_1);
  if (rtb_Sum1_k_idx_0 < 48.0F) {
    /* Outport: '<Root>/FCSb' */
    rtY.FCSb[3] = 48.0F;
  } else {
    /* Outport: '<Root>/FCSb' */
    rtY.FCSb[3] = rtb_Sum1_k_idx_0;
  }

  /* Sum: '<S342>/Minus' incorporates:
   *  Constant: '<S342>/Constant'
   *  Math: '<S342>/Math Function'
   *  Product: '<S342>/Matrix Multiply'
   *  SignalConversion generated from: '<S342>/Matrix Multiply'
   */
  for (i = 0; i < 3; i++) {
    rtb_Minus[i] = (real32_T)((rtb_MathFunction[i + 3] * rtb_Sum_j +
      rtb_MathFunction[i] * rtb_Integrator_n) + rtb_MathFunction[i + 6] *
      rtb_Integrator_cs) + rtConstP.Constant_Value_j[i];
  }

  /* End of Sum: '<S342>/Minus' */

  /* Outputs for Enabled SubSystem: '<S367>/MeasurementUpdate' */
  /* Constant: '<S346>/Enable' incorporates:
   *  Constant: '<S346>/C'
   *  Constant: '<S346>/D'
   *  Delay: '<S346>/MemoryX'
   */
  MeasurementUpdate(true, rtConstB.Conversion, rtb_Gain_p, rtConstP.pooled7,
                    rtDW.MemoryX_DSTATE_h, 0.0F, rtb_Minus[2], rtDW.Product3_a,
                    &rtDW.MeasurementUpdate_g);

  /* End of Outputs for SubSystem: '<S367>/MeasurementUpdate' */

  /* Outputs for Enabled SubSystem: '<S480>/MeasurementUpdate' incorporates:
   *  EnablePort: '<S511>/Enable'
   */
  /* Product: '<S511>/D[k]*u[k]' incorporates:
   *  Constant: '<S459>/D'
   *  Product: '<S480>/B[k]*u[k]'
   */
  rtb_Akxhatkk1_idx_0 = 0.0 * rtb_DiscreteTransferFcn_dw;

  /* Sum: '<S511>/Sum' incorporates:
   *  Constant: '<S459>/C'
   *  Delay: '<S459>/MemoryX'
   *  Product: '<S511>/C[k]*xhat[k|k-1]'
   *  Product: '<S511>/D[k]*u[k]'
   *  Sum: '<S511>/Add1'
   */
  rtb_Sum = rtb_Atan - ((0.0 * rtDW.MemoryX_DSTATE[1] + rtDW.MemoryX_DSTATE[0])
                        + rtb_Akxhatkk1_idx_0);

  /* End of Outputs for SubSystem: '<S480>/MeasurementUpdate' */

  /* Outputs for Enabled SubSystem: '<S425>/MeasurementUpdate' */
  /* Constant: '<S404>/Enable' incorporates:
   *  Constant: '<S404>/C'
   *  Constant: '<S404>/D'
   *  Delay: '<S404>/MemoryX'
   */
  MeasurementUpdate(true, rtConstB.Conversion_i, rtb_Asin, rtConstP.pooled7,
                    rtDW.MemoryX_DSTATE_m, 0.0F, rtb_DiscreteTransferFcn_l,
                    rtDW.Product3_m, &rtDW.MeasurementUpdate_p);

  /* End of Outputs for SubSystem: '<S425>/MeasurementUpdate' */

  /* Outport: '<Root>/xyz_s' incorporates:
   *  DiscreteIntegrator: '<S344>/Integrator1'
   *  DiscreteIntegrator: '<S344>/Integrator5'
   */
  rtY.xyz_s[0] = rtDW.Integrator1_DSTATE_a;
  rtY.xyz_s[1] = rtDW.Integrator5_DSTATE;
  rtY.xyz_s[2] = rtb_Add_m_idx_0;

  /* Sum: '<S7>/Sum' incorporates:
   *  DiscreteIntegrator: '<S344>/Integrator1'
   *  DiscreteIntegrator: '<S344>/Integrator5'
   *  Inport: '<Root>/pos_ref'
   */
  tmp = rtU.pos_ref[0] - rtDW.Integrator1_DSTATE_a;
  tmp_0 = rtU.pos_ref[1] - rtDW.Integrator5_DSTATE;

  /* Outport: '<Root>/dxdydz_s' incorporates:
   *  DiscreteIntegrator: '<S344>/Integrator2'
   *  DiscreteIntegrator: '<S344>/Integrator4'
   */
  rtY.dxdydz_s[0] = rtDW.Integrator4_DSTATE;
  rtY.dxdydz_s[1] = rtDW.Integrator2_DSTATE;
  rtY.dxdydz_s[2] = rtb_Add_m_idx_1;

  /* Outport: '<Root>/rollpitchyaw_s' incorporates:
   *  DataTypeConversion: '<S402>/Data Type Conversion3'
   *  Delay: '<S459>/MemoryX'
   *  DiscreteIntegrator: '<S403>/Integrator1'
   *  Product: '<S513>/Product2'
   *  Sum: '<S487>/Add'
   */
  rtY.rollpitchyaw_s[0] = (real32_T)(Product2 + rtDW.MemoryX_DSTATE[0]);
  rtY.rollpitchyaw_s[1] = rtb_Add_n_idx_0;
  rtY.rollpitchyaw_s[2] = rtDW.Integrator1_DSTATE;

  /* Gain: '<S112>/Proportional Gain' incorporates:
   *  DiscreteIntegrator: '<S403>/Integrator1'
   *  MATLAB Function: '<S7>/Position error transformation (Earth to Body frame)'
   */
  rtb_Sum1_k_idx_0 = (-sinf(rtDW.Integrator1_DSTATE) * tmp + cosf
                      (rtDW.Integrator1_DSTATE) * tmp_0) * 0.7F;

  /* Saturate: '<S114>/Saturation' */
  if (rtb_Sum1_k_idx_0 > 0.5F) {
    rtb_Sum1_k_idx_0 = 0.5F;
  } else if (rtb_Sum1_k_idx_0 < -0.5F) {
    rtb_Sum1_k_idx_0 = -0.5F;
  }

  /* Sum: '<S7>/Sum2' incorporates:
   *  DiscreteIntegrator: '<S344>/Integrator2'
   *  Saturate: '<S114>/Saturation'
   */
  rtb_Add_n_idx_0 = rtb_Sum1_k_idx_0 - rtDW.Integrator2_DSTATE;

  /* Gain: '<S152>/Derivative Gain' incorporates:
   *  Gain: '<S156>/Integral Gain'
   */
  rtb_Integrator_cs = 0.0F * rtb_Add_n_idx_0;

  /* Gain: '<S162>/Filter Coefficient' incorporates:
   *  DiscreteIntegrator: '<S154>/Filter'
   *  Gain: '<S152>/Derivative Gain'
   *  Sum: '<S154>/SumD'
   */
  rtb_Sum_j = (rtb_Integrator_cs - rtDW.Filter_DSTATE_k) * 78.6938705F;

  /* Sum: '<S168>/Sum' incorporates:
   *  DiscreteIntegrator: '<S159>/Integrator'
   *  Gain: '<S164>/Proportional Gain'
   */
  rtb_Sum1_k_idx_0 = (0.7F * rtb_Add_n_idx_0 + rtDW.Integrator_DSTATE_m) +
    rtb_Sum_j;

  /* Gain: '<S60>/Proportional Gain' incorporates:
   *  DiscreteIntegrator: '<S403>/Integrator1'
   *  MATLAB Function: '<S7>/Position error transformation (Earth to Body frame)'
   */
  u0 = (cosf(rtDW.Integrator1_DSTATE) * tmp + sinf(rtDW.Integrator1_DSTATE) *
        tmp_0) * 0.7F;

  /* Saturate: '<S62>/Saturation' */
  if (u0 > 0.5F) {
    u0 = 0.5F;
  } else if (u0 < -0.5F) {
    u0 = -0.5F;
  }

  /* Sum: '<S7>/Sum1' incorporates:
   *  DiscreteIntegrator: '<S344>/Integrator4'
   *  Saturate: '<S62>/Saturation'
   */
  rtb_Add_n_idx_0 = u0 - rtDW.Integrator4_DSTATE;

  /* Gain: '<S204>/Derivative Gain' incorporates:
   *  Gain: '<S208>/Integral Gain'
   */
  rtb_Asin = 0.0F * rtb_Add_n_idx_0;

  /* Gain: '<S214>/Filter Coefficient' incorporates:
   *  DiscreteIntegrator: '<S206>/Filter'
   *  Gain: '<S204>/Derivative Gain'
   *  Sum: '<S206>/SumD'
   */
  rtb_Integrator_n = (rtb_Asin - rtDW.Filter_DSTATE_p) * 78.6938705F;

  /* Sum: '<S220>/Sum' incorporates:
   *  DiscreteIntegrator: '<S211>/Integrator'
   *  Gain: '<S216>/Proportional Gain'
   */
  u0 = (0.7F * rtb_Add_n_idx_0 + rtDW.Integrator_DSTATE_c) + rtb_Integrator_n;

  /* Outport: '<Root>/pqr_s' */
  rtY.pqr_s[0] = rtb_DiscreteTransferFcn_dw;
  rtY.pqr_s[1] = rtb_DiscreteTransferFcn_l;
  rtY.pqr_s[2] = rtb_DiscreteTransferFcn;

  /* MATLAB Function: '<S396>/SqrtUsedFcn' incorporates:
   *  Constant: '<S396>/isSqrtUsed'
   */
  SqrtUsedFcn(rtConstB.Conversion_e, false, rtb_P_nk);

  /* MATLAB Function: '<S454>/SqrtUsedFcn' incorporates:
   *  Constant: '<S454>/isSqrtUsed'
   */
  SqrtUsedFcn(rtConstB.Conversion_o, false, rtb_P_nk);

  /* Outport: '<Root>/emergency' incorporates:
   *  Inport: '<Root>/kill_switch'
   */
  rtY.emergency = rtU.kill_switch;

  /* Update for DiscreteIntegrator: '<S403>/Integrator1' */
  rtDW.Integrator1_DSTATE += 0.005F * rtb_DiscreteTransferFcn;

  /* Update for Delay: '<S459>/MemoryX' */
  rtDW.icLoad = false;

  /* Product: '<S480>/A[k]*xhat[k|k-1]' incorporates:
   *  Constant: '<S459>/A'
   *  Delay: '<S459>/MemoryX'
   */
  rtb_Atan = rtDW.MemoryX_DSTATE[0];
  Product2 = 0.0 * rtDW.MemoryX_DSTATE[0];
  pData_tmp = rtDW.MemoryX_DSTATE[1];

  /* Outputs for Enabled SubSystem: '<S480>/MeasurementUpdate' incorporates:
   *  EnablePort: '<S511>/Enable'
   */
  /* Update for Delay: '<S459>/MemoryX' incorporates:
   *  Constant: '<S459>/A'
   *  Constant: '<S459>/B'
   *  Constant: '<S460>/KalmanGainL'
   *  Product: '<S480>/A[k]*xhat[k|k-1]'
   *  Product: '<S480>/B[k]*u[k]'
   *  Product: '<S511>/Product3'
   *  Sum: '<S480>/Add'
   */
  rtDW.MemoryX_DSTATE[0] = ((-0.005 * pData_tmp + rtb_Atan) + 0.005 *
    rtb_DiscreteTransferFcn_dw) + 0.2049442869192564 * rtb_Sum;
  rtDW.MemoryX_DSTATE[1] = ((Product2 + pData_tmp) + rtb_Akxhatkk1_idx_0) +
    -0.19950604543572328 * rtb_Sum;

  /* End of Outputs for SubSystem: '<S480>/MeasurementUpdate' */

  /* Update for DiscreteTransferFcn: '<S517>/Discrete Transfer Fcn' incorporates:
   *  Inport: '<Root>/axayaz_s'
   */
  rtDW.DiscreteTransferFcn_states = rtU.axayaz_s[1] - -0.36787945F *
    rtDW.DiscreteTransferFcn_states;

  /* Update for DiscreteTransferFcn: '<S518>/Discrete Transfer Fcn' incorporates:
   *  Inport: '<Root>/axayaz_s'
   */
  rtDW.DiscreteTransferFcn_states_e = rtU.axayaz_s[2] - -0.36787945F *
    rtDW.DiscreteTransferFcn_states_e;

  /* Update for Delay: '<S404>/MemoryX' */
  rtDW.icLoad_e = false;

  /* Product: '<S425>/A[k]*xhat[k|k-1]' incorporates:
   *  Constant: '<S404>/A'
   *  Delay: '<S404>/MemoryX'
   */
  tmp = rtDW.MemoryX_DSTATE_m[0];
  tmp_0 = 0.0F * rtDW.MemoryX_DSTATE_m[0];
  tmp_2 = rtDW.MemoryX_DSTATE_m[1];

  /* Update for Delay: '<S404>/MemoryX' incorporates:
   *  Constant: '<S404>/A'
   *  Constant: '<S404>/B'
   *  Product: '<S425>/A[k]*xhat[k|k-1]'
   *  Product: '<S425>/B[k]*u[k]'
   *  Product: '<S456>/Product3'
   *  Sum: '<S425>/Add'
   */
  rtDW.MemoryX_DSTATE_m[0] = ((-0.005F * tmp_2 + tmp) + 0.005F *
    rtb_DiscreteTransferFcn_l) + rtDW.Product3_m[0];
  rtDW.MemoryX_DSTATE_m[1] = (0.0F * rtb_DiscreteTransferFcn_l + (tmp_0 + tmp_2))
    + rtDW.Product3_m[1];

  /* Update for DiscreteTransferFcn: '<S519>/Discrete Transfer Fcn' incorporates:
   *  Inport: '<Root>/axayaz_s'
   */
  rtDW.DiscreteTransferFcn_states_b = rtU.axayaz_s[0] - -0.36787945F *
    rtDW.DiscreteTransferFcn_states_b;

  /* Update for UnitDelay: '<S11>/Output' incorporates:
   *  Constant: '<S12>/FixPt Constant'
   *  Sum: '<S12>/FixPt Sum1'
   */
  rtDW.Output_DSTATE++;

  /* Update for DiscreteIntegrator: '<S5>/Integrator1' incorporates:
   *  Gain: '<S5>/Gain3'
   */
  rtDW.Integrator1_DSTATE_i += 0.24F * rtb_Saturation * 0.005F;
  if (rtDW.Integrator1_DSTATE_i > 2.0F) {
    rtDW.Integrator1_DSTATE_i = 2.0F;
  } else if (rtDW.Integrator1_DSTATE_i < -2.0F) {
    rtDW.Integrator1_DSTATE_i = -2.0F;
  }

  rtDW.Integrator1_PrevResetState = (int8_T)rtb_OR;

  /* End of Update for DiscreteIntegrator: '<S5>/Integrator1' */

  /* Update for Delay: '<S346>/MemoryX' */
  rtDW.icLoad_h = false;

  /* Product: '<S367>/A[k]*xhat[k|k-1]' incorporates:
   *  Constant: '<S346>/A'
   *  Delay: '<S346>/MemoryX'
   */
  tmp = rtDW.MemoryX_DSTATE_h[0];
  tmp_0 = 0.0F * rtDW.MemoryX_DSTATE_h[0];
  tmp_2 = rtDW.MemoryX_DSTATE_h[1];

  /* Update for DiscreteTransferFcn: '<S338>/Discrete Transfer Fcn' incorporates:
   *  Inport: '<Root>/altitude_s'
   */
  rtDW.DiscreteTransferFcn_states_m = rtU.altitude_s - -0.951229453F *
    rtDW.DiscreteTransferFcn_states_m;

  /* Update for DiscreteIntegrator: '<S9>/Integrator' incorporates:
   *  Gain: '<S9>/Gain'
   */
  rtDW.Integrator_DSTATE += 0.004F * rtb_Saturation_a * 0.005F;

  /* Update for DiscreteTransferFcn: '<S515>/Discrete Transfer Fcn' incorporates:
   *  Inport: '<Root>/pqr_sf'
   */
  rtDW.DiscreteTransferFcn_states_l = rtU.pqr_sf[2] - -0.082085F *
    rtDW.DiscreteTransferFcn_states_l;

  /* Update for DiscreteTransferFcn: '<S516>/Discrete Transfer Fcn' incorporates:
   *  Inport: '<Root>/pqr_sf'
   */
  rtDW.DiscreteTransferFcn_states_f = rtU.pqr_sf[0] - -0.082085F *
    rtDW.DiscreteTransferFcn_states_f;

  /* Update for DiscreteTransferFcn: '<S514>/Discrete Transfer Fcn' incorporates:
   *  Inport: '<Root>/pqr_sf'
   */
  rtDW.DiscreteTransferFcn_states_bf = rtU.pqr_sf[1] - -0.082085F *
    rtDW.DiscreteTransferFcn_states_bf;

  /* Saturate: '<S218>/Saturation' */
  if (u0 > 0.34906584F) {
    u0 = 0.34906584F;
  } else if (u0 < -0.34906584F) {
    u0 = -0.34906584F;
  }

  /* Update for DiscreteTransferFcn: '<S20>/Discrete Transfer Fcn' incorporates:
   *  Saturate: '<S218>/Saturation'
   */
  rtDW.DiscreteTransferFcn_states_li = u0 - -0.778800786F *
    rtDW.DiscreteTransferFcn_states_li;

  /* Saturate: '<S166>/Saturation' */
  if (rtb_Sum1_k_idx_0 > 0.34906584F) {
    rtb_Sum1_k_idx_0 = 0.34906584F;
  } else if (rtb_Sum1_k_idx_0 < -0.34906584F) {
    rtb_Sum1_k_idx_0 = -0.34906584F;
  }

  /* Update for DiscreteTransferFcn: '<S19>/Discrete Transfer Fcn' incorporates:
   *  Saturate: '<S166>/Saturation'
   */
  rtDW.DiscreteTransferFcn_states_h = rtb_Sum1_k_idx_0 - -0.778800786F *
    rtDW.DiscreteTransferFcn_states_h;

  /* Update for Delay: '<S346>/MemoryX' incorporates:
   *  Constant: '<S346>/A'
   *  Constant: '<S346>/B'
   *  Product: '<S367>/A[k]*xhat[k|k-1]'
   *  Product: '<S367>/B[k]*u[k]'
   *  Product: '<S398>/Product3'
   *  Sum: '<S367>/Add'
   */
  rtDW.MemoryX_DSTATE_h[0] = ((0.005F * tmp_2 + tmp) + 1.25E-5F * rtb_Minus[2])
    + rtDW.Product3_a[0];

  /* Update for DiscreteIntegrator: '<S265>/Integrator' incorporates:
   *  Gain: '<S262>/Integral Gain'
   */
  rtDW.Integrator_DSTATE_n[0] += 0.01F * rtb_Integrator_g_idx_1 * 0.005F;

  /* Update for DiscreteIntegrator: '<S260>/Filter' */
  rtDW.Filter_DSTATE[0] += 0.005F * rtb_Integrator_g_idx_0;

  /* Update for DiscreteIntegrator: '<S317>/Integrator' */
  rtDW.Integrator_DSTATE_b[0] += u0_tmp * 0.005F;

  /* Update for DiscreteIntegrator: '<S312>/Filter' */
  rtDW.Filter_DSTATE_e[0] += 0.005F * rtb_FilterCoefficient_a_idx_0;

  /* Update for Delay: '<S346>/MemoryX' incorporates:
   *  Constant: '<S346>/B'
   *  Product: '<S367>/A[k]*xhat[k|k-1]'
   *  Product: '<S367>/B[k]*u[k]'
   *  Product: '<S398>/Product3'
   *  Sum: '<S367>/Add'
   */
  rtDW.MemoryX_DSTATE_h[1] = (0.005F * rtb_Minus[2] + (tmp_0 + tmp_2)) +
    rtDW.Product3_a[1];

  /* Update for DiscreteIntegrator: '<S265>/Integrator' incorporates:
   *  Gain: '<S262>/Integral Gain'
   */
  rtDW.Integrator_DSTATE_n[1] += 0.01F * rtb_Sum_h_idx_1 * 0.005F;

  /* Update for DiscreteIntegrator: '<S260>/Filter' incorporates:
   *  Gain: '<S268>/Filter Coefficient'
   */
  rtDW.Filter_DSTATE[1] += 0.005F * rtb_Integrator_g_0;

  /* Update for DiscreteIntegrator: '<S317>/Integrator' */
  rtDW.Integrator_DSTATE_b[1] += rtb_Sum1_k_idx_1 * 0.005F;

  /* Update for DiscreteIntegrator: '<S312>/Filter' incorporates:
   *  Gain: '<S320>/Filter Coefficient'
   */
  rtDW.Filter_DSTATE_e[1] += 0.005F * rtb_FilterCoefficient_a_0;

  /* Update for DiscreteIntegrator: '<S344>/Integrator5' incorporates:
   *  DiscreteIntegrator: '<S344>/Integrator2'
   */
  rtDW.Integrator5_DSTATE += 0.005F * rtDW.Integrator2_DSTATE;

  /* Update for DiscreteIntegrator: '<S344>/Integrator1' incorporates:
   *  DiscreteIntegrator: '<S344>/Integrator4'
   */
  rtDW.Integrator1_DSTATE_a += 0.005F * rtDW.Integrator4_DSTATE;

  /* Update for DiscreteIntegrator: '<S344>/Integrator4' */
  rtDW.Integrator4_DSTATE += 0.005F * rtb_Minus[0];

  /* Update for DiscreteIntegrator: '<S344>/Integrator2' */
  rtDW.Integrator2_DSTATE += 0.005F * rtb_Minus[1];

  /* Update for DiscreteIntegrator: '<S154>/Filter' */
  rtDW.Filter_DSTATE_k += 0.005F * rtb_Sum_j;

  /* Update for DiscreteIntegrator: '<S159>/Integrator' */
  rtDW.Integrator_DSTATE_m += 0.005F * rtb_Integrator_cs;

  /* Update for DiscreteIntegrator: '<S206>/Filter' */
  rtDW.Filter_DSTATE_p += 0.005F * rtb_Integrator_n;

  /* Update for DiscreteIntegrator: '<S211>/Integrator' */
  rtDW.Integrator_DSTATE_c += rtb_Asin * 0.005F;
}

/* Model initialize function */
void FCS_initialize(void)
{
  /* InitializeConditions for Delay: '<S459>/MemoryX' */
  rtDW.icLoad = true;

  /* InitializeConditions for Delay: '<S404>/MemoryX' */
  rtDW.icLoad_e = true;

  /* InitializeConditions for DiscreteIntegrator: '<S5>/Integrator1' */
  rtDW.Integrator1_PrevResetState = 2;

  /* InitializeConditions for Delay: '<S346>/MemoryX' */
  rtDW.icLoad_h = true;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
