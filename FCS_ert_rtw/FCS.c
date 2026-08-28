/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: FCS.c
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

#include "FCS.h"
#include "rtwtypes.h"
#include <math.h>
#include <string.h>
#include "math.h"

/* Block signals and states (default storage) */
DW rtDW;

/* External inputs (root inport signals with default storage) */
ExtU rtU;

/* External outputs (root outports fed by signals with default storage) */
ExtY rtY;

/* Real-time model */
static RT_MODEL rtM_;
RT_MODEL *const rtM = &rtM_;
extern real32_T rt_atan2f_snf(real32_T u0, real32_T u1);
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
static real_T rtGetNaN(void);
static real32_T rtGetNaNF(void);

/*===========*
 * Constants *
 *===========*/
#define RT_PI                          3.14159265358979323846
#define RT_PIF                         3.1415927F
#define RT_LN_10                       2.30258509299404568402
#define RT_LN_10F                      2.3025851F
#define RT_LOG10E                      0.43429448190325182765
#define RT_LOG10EF                     0.43429449F
#define RT_E                           2.7182818284590452354
#define RT_EF                          2.7182817F

/*
 * UNUSED_PARAMETER(x)
 *   Used to specify that a function parameter (argument) is required but not
 *   accessed by the function body.
 */
#ifndef UNUSED_PARAMETER
#if defined(__LCC__)
#define UNUSED_PARAMETER(x)                                      /* do nothing */
#else

/*
 * This is the semi-ANSI standard way of indicating that an
 * unused function parameter is required.
 */
#define UNUSED_PARAMETER(x)            (void) (x)
#endif
#endif

extern real_T rtInf;
extern real_T rtMinusInf;
extern real_T rtNaN;
extern real32_T rtInfF;
extern real32_T rtMinusInfF;
extern real32_T rtNaNF;
static boolean_T rtIsInf(real_T value);
static boolean_T rtIsInfF(real32_T value);
static boolean_T rtIsNaN(real_T value);
static boolean_T rtIsNaNF(real32_T value);
real_T rtNaN = -(real_T)NAN;
real_T rtInf = (real_T)INFINITY;
real_T rtMinusInf = -(real_T)INFINITY;
real32_T rtNaNF = -(real32_T)NAN;
real32_T rtInfF = (real32_T)INFINITY;
real32_T rtMinusInfF = -(real32_T)INFINITY;

/* Return rtNaN needed by the generated code. */
static real_T rtGetNaN(void)
{
  return rtNaN;
}

/* Return rtNaNF needed by the generated code. */
static real32_T rtGetNaNF(void)
{
  return rtNaNF;
}

/* Test if value is infinite */
static boolean_T rtIsInf(real_T value)
{
  return (boolean_T)isinf(value);
}

/* Test if single-precision value is infinite */
static boolean_T rtIsInfF(real32_T value)
{
  return (boolean_T)isinf(value);
}

/* Test if value is not a number */
static boolean_T rtIsNaN(real_T value)
{
  return (boolean_T)(isnan(value) != 0);
}

/* Test if single-precision value is not a number */
static boolean_T rtIsNaNF(real32_T value)
{
  return (boolean_T)(isnan(value) != 0);
}

/*
 * Output and update for atomic system:
 *    '<S233>/SqrtUsedFcn'
 *    '<S291>/SqrtUsedFcn'
 *    '<S346>/SqrtUsedFcn'
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
 *    '<S204>/MeasurementUpdate'
 *    '<S262>/MeasurementUpdate'
 *    '<S317>/MeasurementUpdate'
 */
static void MeasurementUpdate_Disable(real32_T rty_Lykyhatkk1[2],
  DW_MeasurementUpdate *localDW)
{
  /* Outputs for Enabled SubSystem: '<S204>/MeasurementUpdate' incorporates:
   *  EnablePort: '<S235>/Enable'
   */
  /* Disable for Outport: '<S235>/L*(y[k]-yhat[k|k-1])' */
  rty_Lykyhatkk1[0] = 0.0F;
  rty_Lykyhatkk1[1] = 0.0F;

  /* End of Outputs for SubSystem: '<S204>/MeasurementUpdate' */
  localDW->MeasurementUpdate_MODE = false;
}

/*
 * Output and update for enable system:
 *    '<S204>/MeasurementUpdate'
 *    '<S262>/MeasurementUpdate'
 *    '<S317>/MeasurementUpdate'
 */
static void MeasurementUpdate(boolean_T rtu_Enable, const real32_T rtu_Lk[2],
  real32_T rtu_yk, const real32_T rtu_Ck[2], const real32_T rtu_xhatkk1[2],
  real32_T rtu_Dk, real32_T rtu_uk, real32_T rty_Lykyhatkk1[2],
  DW_MeasurementUpdate *localDW)
{
  real32_T rtb_Sum_k;

  /* Outputs for Enabled SubSystem: '<S204>/MeasurementUpdate' incorporates:
   *  EnablePort: '<S235>/Enable'
   */
  if (rtu_Enable) {
    localDW->MeasurementUpdate_MODE = true;

    /* Sum: '<S235>/Sum' incorporates:
     *  Product: '<S235>/C[k]*xhat[k|k-1]'
     *  Product: '<S235>/D[k]*u[k]'
     *  Sum: '<S235>/Add1'
     */
    rtb_Sum_k = rtu_yk - ((rtu_Ck[0] * rtu_xhatkk1[0] + rtu_Ck[1] * rtu_xhatkk1
      [1]) + rtu_Dk * rtu_uk);

    /* Product: '<S235>/Product3' */
    rty_Lykyhatkk1[0] = rtu_Lk[0] * rtb_Sum_k;
    rty_Lykyhatkk1[1] = rtu_Lk[1] * rtb_Sum_k;
  } else if (localDW->MeasurementUpdate_MODE) {
    MeasurementUpdate_Disable(rty_Lykyhatkk1, localDW);
  }

  /* End of Outputs for SubSystem: '<S204>/MeasurementUpdate' */
}

/*
 * Disable for enable system:
 *    '<S211>/Enabled Subsystem'
 *    '<S269>/Enabled Subsystem'
 *    '<S324>/Enabled Subsystem'
 */
static void EnabledSubsystem_Disable(real32_T rty_deltax[2], DW_EnabledSubsystem
  *localDW)
{
  /* Outputs for Enabled SubSystem: '<S211>/Enabled Subsystem' incorporates:
   *  EnablePort: '<S237>/Enable'
   */
  /* Disable for Outport: '<S237>/deltax' */
  rty_deltax[0] = 0.0F;
  rty_deltax[1] = 0.0F;

  /* End of Outputs for SubSystem: '<S211>/Enabled Subsystem' */
  localDW->EnabledSubsystem_MODE = false;
}

/*
 * Output and update for enable system:
 *    '<S211>/Enabled Subsystem'
 *    '<S269>/Enabled Subsystem'
 *    '<S324>/Enabled Subsystem'
 */
static void EnabledSubsystem(boolean_T rtu_Enable, const real32_T rtu_Mk[2],
  const real32_T rtu_Ck[2], real32_T rtu_yk, const real32_T rtu_xhatkk1[2],
  real32_T rty_deltax[2], DW_EnabledSubsystem *localDW)
{
  real32_T rtb_Add1;

  /* Outputs for Enabled SubSystem: '<S211>/Enabled Subsystem' incorporates:
   *  EnablePort: '<S237>/Enable'
   */
  if (rtu_Enable) {
    localDW->EnabledSubsystem_MODE = true;

    /* Sum: '<S237>/Add1' incorporates:
     *  Product: '<S237>/Product'
     */
    rtb_Add1 = rtu_yk - (rtu_Ck[0] * rtu_xhatkk1[0] + rtu_Ck[1] * rtu_xhatkk1[1]);

    /* Product: '<S237>/Product2' */
    rty_deltax[0] = rtu_Mk[0] * rtb_Add1;
    rty_deltax[1] = rtu_Mk[1] * rtb_Add1;
  } else if (localDW->EnabledSubsystem_MODE) {
    EnabledSubsystem_Disable(rty_deltax, localDW);
  }

  /* End of Outputs for SubSystem: '<S211>/Enabled Subsystem' */
}

real32_T rt_atan2f_snf(real32_T u0, real32_T u1)
{
  real32_T y;
  if (rtIsNaNF(u0) || rtIsNaNF(u1)) {
    y = (rtNaNF);
  } else if (rtIsInfF(u0) && rtIsInfF(u1)) {
    int32_T tmp;
    int32_T tmp_0;
    if (u0 > 0.0F) {
      tmp = 1;
    } else {
      tmp = -1;
    }

    if (u1 > 0.0F) {
      tmp_0 = 1;
    } else {
      tmp_0 = -1;
    }

    y = atan2f((real32_T)tmp, (real32_T)tmp_0);
  } else if (u1 == 0.0F) {
    if (u0 > 0.0F) {
      y = RT_PIF / 2.0F;
    } else if (u0 < 0.0F) {
      y = -(RT_PIF / 2.0F);
    } else {
      y = 0.0F;
    }
  } else {
    y = atan2f(u0, u1);
  }

  return y;
}

/* Model step function */
void FCS_step(void)
{
  real_T rtb_MathFunction[9];
  real_T rtb_MathFunction_0[9];
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
  real_T pData_tmp_2;
  int32_T i;
  int32_T tmp_5;
  real32_T rtb_Saturation[4];
  real32_T rtb_Saturation1_0[4];
  real32_T rtb_Minus[3];
  real32_T rtb_Add_m_idx_0;
  real32_T rtb_Add_m_idx_1;
  real32_T rtb_Add_n_idx_0;
  real32_T rtb_Add_ny_idx_0;
  real32_T rtb_Atan2;
  real32_T rtb_Atan2_e;
  real32_T rtb_DeadZone_g_0;
  real32_T rtb_DeadZone_g_idx_0;
  real32_T rtb_DeadZone_h;
  real32_T rtb_DiscreteTransferFcn_c;
  real32_T rtb_DiscreteTransferFcn_d;
  real32_T rtb_DiscreteTransferFcn_h;
  real32_T rtb_DiscreteTransferFcn_i;
  real32_T rtb_DiscreteTransferFcn_mz;
  real32_T rtb_FilterCoefficient;
  real32_T rtb_FilterCoefficient_a_0;
  real32_T rtb_FilterCoefficient_a_idx_0;
  real32_T rtb_Gain;
  real32_T rtb_IntegralGain_b;
  real32_T rtb_IntegralGain_i_idx_0;
  real32_T rtb_IntegralGain_i_idx_1;
  real32_T rtb_Integrator_g_idx_0;
  real32_T rtb_Integrator_g_idx_1;
  real32_T rtb_Saturation1;
  real32_T rtb_Saturation_0;
  real32_T rtb_Sum3;
  real32_T rtb_Sum_idx_0;
  real32_T rtb_Sum_idx_1;
  real32_T rtb_Switch3;
  real32_T tmp;
  real32_T tmp_0;
  real32_T tmp_1;
  real32_T tmp_2;
  int8_T tmp_3;
  int8_T tmp_4;

  /* Delay: '<S296>/MemoryX' incorporates:
   *  Constant: '<S296>/X0'
   */
  if (rtDW.icLoad) {
    rtDW.MemoryX_DSTATE[0] = 0.0F;
    rtDW.MemoryX_DSTATE[1] = 0.0F;
  }

  /* DiscreteTransferFcn: '<S354>/Discrete Transfer Fcn' */
  rtb_DiscreteTransferFcn_i = 0.63212055F * rtDW.DiscreteTransferFcn_states;

  /* DiscreteTransferFcn: '<S355>/Discrete Transfer Fcn' */
  rtb_DiscreteTransferFcn_h = 0.63212055F * rtDW.DiscreteTransferFcn_states_l;

  /* Trigonometry: '<S239>/Atan2' */
  rtb_Atan2 = rt_atan2f_snf(rtb_DiscreteTransferFcn_i, rtb_DiscreteTransferFcn_h);

  /* Outputs for Enabled SubSystem: '<S324>/Enabled Subsystem' */
  /* Constant: '<S296>/Enable' incorporates:
   *  Constant: '<S296>/C'
   *  Delay: '<S296>/MemoryX'
   */
  EnabledSubsystem(true, rtConstB.Conversion_b, rtConstP.pooled8, rtb_Atan2,
                   rtDW.MemoryX_DSTATE, rtDW.Product2, &rtDW.EnabledSubsystem_i);

  /* End of Outputs for SubSystem: '<S324>/Enabled Subsystem' */

  /* Sum: '<S324>/Add' incorporates:
   *  Delay: '<S296>/MemoryX'
   */
  rtb_Add_n_idx_0 = rtDW.Product2[0] + rtDW.MemoryX_DSTATE[0];

  /* Delay: '<S241>/MemoryX' incorporates:
   *  Constant: '<S241>/X0'
   */
  if (rtDW.icLoad_e) {
    rtDW.MemoryX_DSTATE_m[0] = 0.0F;
    rtDW.MemoryX_DSTATE_m[1] = 0.0F;
  }

  /* DiscreteTransferFcn: '<S356>/Discrete Transfer Fcn' */
  rtb_DiscreteTransferFcn_c = 0.63212055F * rtDW.DiscreteTransferFcn_states_o;

  /* Trigonometry: '<S238>/Atan2' incorporates:
   *  Gain: '<S238>/Gain1'
   *  Math: '<S238>/Square'
   *  Math: '<S238>/Square1'
   *  Sqrt: '<S238>/Sqrt'
   *  Sum: '<S238>/Sum'
   */
  rtb_Atan2_e = rt_atan2f_snf(-rtb_DiscreteTransferFcn_c, sqrtf
    (rtb_DiscreteTransferFcn_i * rtb_DiscreteTransferFcn_i +
     rtb_DiscreteTransferFcn_h * rtb_DiscreteTransferFcn_h));

  /* Outputs for Enabled SubSystem: '<S269>/Enabled Subsystem' */
  /* Constant: '<S241>/Enable' incorporates:
   *  Constant: '<S241>/C'
   *  Delay: '<S241>/MemoryX'
   */
  EnabledSubsystem(true, rtConstB.Conversion_p, rtConstP.pooled8, rtb_Atan2_e,
                   rtDW.MemoryX_DSTATE_m, rtDW.Product2_d,
                   &rtDW.EnabledSubsystem_p);

  /* End of Outputs for SubSystem: '<S269>/Enabled Subsystem' */

  /* Sum: '<S269>/Add' incorporates:
   *  Delay: '<S241>/MemoryX'
   */
  rtb_Add_ny_idx_0 = rtDW.Product2_d[0] + rtDW.MemoryX_DSTATE_m[0];

  /* Angle2Dcm: '<S179>/Rotation Angles to Direction Cosine Matrix' incorporates:
   *  DataTypeConversion: '<S179>/Data Type Conversion3'
   *  DiscreteIntegrator: '<S240>/Integrator1'
   *  Math: '<S179>/Math Function'
   */
  pData_tmp_0 = cos(rtb_Add_n_idx_0);
  pData_tmp = sin(rtb_Add_n_idx_0);
  pData_tmp_2 = cos(rtb_Add_ny_idx_0);
  pData_tmp_1 = sin(rtb_Add_ny_idx_0);
  pData_idx_0 = 0.0 * pData_tmp_1 + pData_tmp_2;
  pData_idx_6_tmp = 0.0 * pData_tmp_2;
  pData_idx_6 = pData_idx_6_tmp - pData_tmp_1;
  pData_idx_1_tmp = pData_tmp_0 * 0.0;
  pData_idx_1 = (pData_idx_6_tmp + pData_idx_1_tmp) + pData_tmp * pData_tmp_1;
  pData_idx_4 = pData_tmp * 0.0 + pData_tmp_0;
  pData_idx_7_tmp = 0.0 * -pData_tmp_1;
  pData_idx_7 = (pData_idx_7_tmp + pData_idx_1_tmp) + pData_tmp * pData_tmp_2;
  pData_idx_2_tmp = -pData_tmp * 0.0;
  pData_tmp_1 = (pData_idx_6_tmp + pData_idx_2_tmp) + pData_tmp_1 * pData_tmp_0;
  pData_idx_1_tmp -= pData_tmp;
  pData_tmp_2 = (pData_idx_7_tmp + pData_idx_2_tmp) + pData_tmp_0 * pData_tmp_2;
  pData_tmp_0 = cos(rtDW.Integrator1_DSTATE);
  pData_tmp = sin(rtDW.Integrator1_DSTATE);
  pData_idx_7_tmp = pData_idx_6 * 0.0;
  rtb_MathFunction[0] = (pData_idx_0 * pData_tmp_0 + 0.0 * -pData_tmp) +
    pData_idx_7_tmp;
  pData_idx_2_tmp = pData_idx_7 * 0.0;
  rtb_MathFunction[1] = (pData_tmp_0 * pData_idx_1 + -pData_tmp * pData_idx_4) +
    pData_idx_2_tmp;
  pData_idx_6_tmp = pData_tmp_2 * 0.0;
  rtb_MathFunction[2] = (pData_tmp_0 * pData_tmp_1 + -pData_tmp *
    pData_idx_1_tmp) + pData_idx_6_tmp;
  rtb_MathFunction[3] = (pData_idx_0 * pData_tmp + 0.0 * pData_tmp_0) +
    pData_idx_7_tmp;
  rtb_MathFunction[4] = (pData_tmp * pData_idx_1 + pData_idx_4 * pData_tmp_0) +
    pData_idx_2_tmp;
  rtb_MathFunction[5] = (pData_tmp * pData_tmp_1 + pData_tmp_0 * pData_idx_1_tmp)
    + pData_idx_6_tmp;
  rtb_MathFunction[6] = pData_idx_0 * 0.0 + pData_idx_6;
  rtb_MathFunction[7] = (pData_idx_1 * 0.0 + pData_idx_4 * 0.0) + pData_idx_7;
  rtb_MathFunction[8] = (pData_tmp_1 * 0.0 + pData_idx_1_tmp * 0.0) +
    pData_tmp_2;

  /* Math: '<S179>/Math Function' */
  for (i = 0; i < 3; i++) {
    rtb_MathFunction_0[3 * i] = rtb_MathFunction[i];
    rtb_MathFunction_0[3 * i + 1] = rtb_MathFunction[i + 3];
    rtb_MathFunction_0[3 * i + 2] = rtb_MathFunction[i + 6];
  }

  memcpy(&rtb_MathFunction[0], &rtb_MathFunction_0[0], 9U * sizeof(real_T));

  /* End of Math: '<S179>/Math Function' */

  /* Delay: '<S183>/MemoryX' incorporates:
   *  Constant: '<S183>/X0'
   */
  if (rtDW.icLoad_h) {
    rtDW.MemoryX_DSTATE_h[0] = 0.0F;
    rtDW.MemoryX_DSTATE_h[1] = 0.0F;
  }

  /* Gain: '<S182>/Gain' incorporates:
   *  Constant: '<S182>/Constant'
   *  DiscreteTransferFcn: '<S175>/Discrete Transfer Fcn'
   *  Sum: '<S182>/Add'
   */
  rtb_Gain = (1013.25F - 0.0487705767F * rtDW.DiscreteTransferFcn_states_f) *
    0.0832639486F;

  /* Outputs for Enabled SubSystem: '<S211>/Enabled Subsystem' */
  /* Constant: '<S183>/Enable' incorporates:
   *  Constant: '<S183>/C'
   *  Delay: '<S183>/MemoryX'
   */
  EnabledSubsystem(true, rtConstB.Conversion_n, rtConstP.pooled8, rtb_Gain,
                   rtDW.MemoryX_DSTATE_h, rtDW.Product2_b,
                   &rtDW.EnabledSubsystem_e);

  /* End of Outputs for SubSystem: '<S211>/Enabled Subsystem' */

  /* Sum: '<S211>/Add' incorporates:
   *  Delay: '<S183>/MemoryX'
   */
  rtb_Add_m_idx_0 = rtDW.Product2_b[0] + rtDW.MemoryX_DSTATE_h[0];
  rtb_Add_m_idx_1 = rtDW.Product2_b[1] + rtDW.MemoryX_DSTATE_h[1];

  /* Switch: '<S6>/Switch3' incorporates:
   *  Inport: '<Root>/controlModePosVSOrient'
   *  UnitDelay: '<S6>/Unit Delay'
   */
  if (rtU.controlModePosVSOrient) {
    rtb_Switch3 = rtb_Add_m_idx_0;
  } else {
    rtb_Switch3 = rtDW.UnitDelay_DSTATE;
  }

  /* End of Switch: '<S6>/Switch3' */

  /* Sum: '<S6>/Sum3' */
  rtb_Sum3 = rtb_Switch3 - rtb_Add_m_idx_0;

  /* DiscreteIntegrator: '<S6>/Integrator2' incorporates:
   *  Inport: '<Root>/controlModePosVSOrient'
   */
  if (rtU.controlModePosVSOrient && (rtDW.Integrator2_PrevResetState <= 0)) {
    rtDW.Integrator2_DSTATE = 0.0F;
  }

  /* Saturate: '<S4>/Saturation' incorporates:
   *  Inport: '<Root>/orient_ref'
   */
  if (rtU.orient_ref[0] > 1.0F) {
    rtb_FilterCoefficient = 1.0F;
  } else if (rtU.orient_ref[0] < -1.0F) {
    rtb_FilterCoefficient = -1.0F;
  } else {
    rtb_FilterCoefficient = rtU.orient_ref[0];
  }

  /* DeadZone: '<S4>/Dead Zone' */
  if (rtb_FilterCoefficient > 0.03F) {
    rtb_Integrator_g_idx_0 = rtb_FilterCoefficient - 0.03F;
    rtb_Saturation[0] = rtb_FilterCoefficient - 0.03F;
  } else if (rtb_FilterCoefficient >= -0.03F) {
    rtb_Integrator_g_idx_0 = 0.0F;
    rtb_Saturation[0] = 0.0F;
  } else {
    rtb_Integrator_g_idx_0 = rtb_FilterCoefficient - -0.03F;
    rtb_Saturation[0] = rtb_FilterCoefficient - -0.03F;
  }

  /* Saturate: '<S4>/Saturation' incorporates:
   *  Inport: '<Root>/orient_ref'
   */
  if (rtU.orient_ref[1] > 1.0F) {
    rtb_FilterCoefficient = 1.0F;
  } else if (rtU.orient_ref[1] < -1.0F) {
    rtb_FilterCoefficient = -1.0F;
  } else {
    rtb_FilterCoefficient = rtU.orient_ref[1];
  }

  /* DeadZone: '<S4>/Dead Zone' */
  if (rtb_FilterCoefficient > 0.03F) {
    rtb_Saturation_0 = rtb_FilterCoefficient - 0.03F;
    rtb_Saturation[1] = rtb_FilterCoefficient - 0.03F;
  } else if (rtb_FilterCoefficient >= -0.03F) {
    rtb_Saturation_0 = 0.0F;
    rtb_Saturation[1] = 0.0F;
  } else {
    rtb_Saturation_0 = rtb_FilterCoefficient - -0.03F;
    rtb_Saturation[1] = rtb_FilterCoefficient - -0.03F;
  }

  /* Saturate: '<S4>/Saturation' incorporates:
   *  Inport: '<Root>/orient_ref'
   */
  if (rtU.orient_ref[2] > 1.0F) {
    rtb_FilterCoefficient = 1.0F;
  } else if (rtU.orient_ref[2] < -1.0F) {
    rtb_FilterCoefficient = -1.0F;
  } else {
    rtb_FilterCoefficient = rtU.orient_ref[2];
  }

  /* DeadZone: '<S4>/Dead Zone' */
  if (rtb_FilterCoefficient > 0.03F) {
    rtb_IntegralGain_b = rtb_FilterCoefficient - 0.03F;
    rtb_Saturation[2] = rtb_FilterCoefficient - 0.03F;
  } else if (rtb_FilterCoefficient >= -0.03F) {
    rtb_IntegralGain_b = 0.0F;
    rtb_Saturation[2] = 0.0F;
  } else {
    rtb_IntegralGain_b = rtb_FilterCoefficient - -0.03F;
    rtb_Saturation[2] = rtb_FilterCoefficient - -0.03F;
  }

  /* Saturate: '<S4>/Saturation' incorporates:
   *  Inport: '<Root>/orient_ref'
   */
  if (rtU.orient_ref[3] > 1.0F) {
    rtb_FilterCoefficient = 1.0F;
  } else if (rtU.orient_ref[3] < -1.0F) {
    rtb_FilterCoefficient = -1.0F;
  } else {
    rtb_FilterCoefficient = rtU.orient_ref[3];
  }

  /* DeadZone: '<S4>/Dead Zone' */
  if (rtb_FilterCoefficient > 0.03F) {
    rtb_Saturation[3] = rtb_FilterCoefficient - 0.03F;
  } else if (rtb_FilterCoefficient >= -0.03F) {
    rtb_Saturation[3] = 0.0F;
  } else {
    rtb_Saturation[3] = rtb_FilterCoefficient - -0.03F;
  }

  /* Switch: '<S6>/Switch2' incorporates:
   *  Constant: '<S4>/Constant'
   *  Constant: '<S6>/Constant'
   *  DeadZone: '<S4>/Dead Zone'
   *  DiscreteIntegrator: '<S6>/Integrator2'
   *  Gain: '<S4>/Gain3'
   *  Gain: '<S6>/Gain5'
   *  Gain: '<S6>/Gain6'
   *  Inport: '<Root>/controlModePosVSOrient'
   *  Sum: '<S4>/Sum'
   *  Sum: '<S6>/Add'
   *  Sum: '<S6>/Sum4'
   */
  if (rtU.controlModePosVSOrient) {
    rtb_Saturation1 = ((5.0F * rtb_Sum3 - 2.0F * rtb_Add_m_idx_1) +
                       rtDW.Integrator2_DSTATE) + 4.905F;
  } else {
    if (rtb_FilterCoefficient > 0.03F) {
      /* DeadZone: '<S4>/Dead Zone' */
      rtb_Sum_idx_1 = rtb_FilterCoefficient - 0.03F;
    } else if (rtb_FilterCoefficient >= -0.03F) {
      /* DeadZone: '<S4>/Dead Zone' */
      rtb_Sum_idx_1 = 0.0F;
    } else {
      /* DeadZone: '<S4>/Dead Zone' */
      rtb_Sum_idx_1 = rtb_FilterCoefficient - -0.03F;
    }

    rtb_Saturation1 = 4.405F * rtb_Sum_idx_1 + 4.905F;
  }

  /* End of Switch: '<S6>/Switch2' */

  /* RateLimiter: '<S6>/Rate Limiter' */
  rtb_FilterCoefficient = rtb_Saturation1 - rtDW.PrevY;
  if (rtb_FilterCoefficient > 0.125F) {
    rtb_Saturation1 = rtDW.PrevY + 0.125F;
  } else if (rtb_FilterCoefficient < -0.125F) {
    rtb_Saturation1 = rtDW.PrevY - 0.125F;
  }

  rtDW.PrevY = rtb_Saturation1;

  /* End of RateLimiter: '<S6>/Rate Limiter' */

  /* Saturate: '<S6>/Saturation1' */
  if (rtb_Saturation1 > 11.0F) {
    /* SignalConversion generated from: '<S5>/Matrix Multiply' */
    rtb_Saturation1_0[0] = 11.0F;
  } else if (rtb_Saturation1 < 0.5F) {
    /* SignalConversion generated from: '<S5>/Matrix Multiply' */
    rtb_Saturation1_0[0] = 0.5F;
  } else {
    /* SignalConversion generated from: '<S5>/Matrix Multiply' */
    rtb_Saturation1_0[0] = rtb_Saturation1;
  }

  /* End of Saturate: '<S6>/Saturation1' */

  /* Switch: '<S2>/Switch1' incorporates:
   *  Constant: '<S2>/Constant1'
   *  DeadZone: '<S4>/Dead Zone'
   *  Gain: '<S4>/Gain2'
   *  Inport: '<Root>/controlModePosVSOrient'
   */
  if (rtU.controlModePosVSOrient) {
    rtb_IntegralGain_b = 0.0F;
  } else {
    rtb_IntegralGain_b *= 3.49F;
  }

  /* End of Switch: '<S2>/Switch1' */

  /* RateLimiter: '<S2>/Rate Limiter1' */
  rtb_FilterCoefficient = rtb_IntegralGain_b - rtDW.PrevY_l;
  if (rtb_FilterCoefficient > 0.1F) {
    rtb_IntegralGain_b = rtDW.PrevY_l + 0.1F;
  } else if (rtb_FilterCoefficient < -0.1F) {
    rtb_IntegralGain_b = rtDW.PrevY_l - 0.1F;
  }

  rtDW.PrevY_l = rtb_IntegralGain_b;

  /* End of RateLimiter: '<S2>/Rate Limiter1' */

  /* DiscreteTransferFcn: '<S352>/Discrete Transfer Fcn' */
  rtb_Saturation1 = 0.917915F * rtDW.DiscreteTransferFcn_states_ll;

  /* Sum: '<S8>/Sum' */
  rtb_IntegralGain_b -= rtb_Saturation1;

  /* Saturate: '<S8>/Saturation' */
  if (rtb_IntegralGain_b > 3.5F) {
    rtb_IntegralGain_b = 3.5F;
  } else if (rtb_IntegralGain_b < -3.5F) {
    rtb_IntegralGain_b = -3.5F;
  }

  /* End of Saturate: '<S8>/Saturation' */

  /* Gain: '<S157>/Filter Coefficient' incorporates:
   *  DiscreteIntegrator: '<S149>/Filter'
   *  Gain: '<S147>/Derivative Gain'
   *  Sum: '<S149>/SumD'
   */
  rtb_FilterCoefficient = (0.00254149409F * rtb_IntegralGain_b -
    rtDW.Filter_DSTATE) * 78.6938705F;

  /* Sum: '<S163>/Sum' incorporates:
   *  DiscreteIntegrator: '<S154>/Integrator'
   *  Gain: '<S159>/Proportional Gain'
   */
  rtb_DeadZone_h = (0.03F * rtb_IntegralGain_b + rtDW.Integrator_DSTATE) +
    rtb_FilterCoefficient;

  /* DiscreteTransferFcn: '<S353>/Discrete Transfer Fcn' */
  rtb_DiscreteTransferFcn_d = 0.917915F * rtDW.DiscreteTransferFcn_states_n;

  /* DiscreteTransferFcn: '<S351>/Discrete Transfer Fcn' */
  rtb_DiscreteTransferFcn_mz = 0.917915F * rtDW.DiscreteTransferFcn_states_nu;

  /* Switch: '<S2>/Switch2' incorporates:
   *  Constant: '<S2>/Constant'
   *  DeadZone: '<S4>/Dead Zone'
   *  Gain: '<S4>/Gain'
   *  Gain: '<S4>/Gain1'
   *  Inport: '<Root>/controlModePosVSOrient'
   */
  if (rtU.controlModePosVSOrient) {
    rtb_Integrator_g_idx_0 = 0.0F;
    rtb_Integrator_g_idx_1 = 0.0F;
  } else {
    rtb_Integrator_g_idx_0 *= 0.5236F;
    rtb_Integrator_g_idx_1 = 0.5236F * rtb_Saturation_0;
  }

  /* End of Switch: '<S2>/Switch2' */

  /* RateLimiter: '<S2>/Rate Limiter' */
  rtb_Saturation_0 = rtb_Integrator_g_idx_0;
  rtb_Sum_idx_1 = rtb_Integrator_g_idx_0 - rtDW.PrevY_g[0];
  if (rtb_Sum_idx_1 > 0.015F) {
    rtb_Saturation_0 = rtDW.PrevY_g[0] + 0.015F;
  } else if (rtb_Sum_idx_1 < -0.015F) {
    rtb_Saturation_0 = rtDW.PrevY_g[0] - 0.015F;
  }

  rtb_Integrator_g_idx_0 = rtb_Saturation_0;
  rtDW.PrevY_g[0] = rtb_Saturation_0;
  rtb_Saturation_0 = rtb_Integrator_g_idx_1;
  rtb_Sum_idx_1 = rtb_Integrator_g_idx_1 - rtDW.PrevY_g[1];
  if (rtb_Sum_idx_1 > 0.015F) {
    rtb_Saturation_0 = rtDW.PrevY_g[1] + 0.015F;
  } else if (rtb_Sum_idx_1 < -0.015F) {
    rtb_Saturation_0 = rtDW.PrevY_g[1] - 0.015F;
  }

  rtDW.PrevY_g[1] = rtb_Saturation_0;

  /* Sum: '<S7>/Sum' incorporates:
   *  RateLimiter: '<S2>/Rate Limiter'
   */
  rtb_Sum_idx_0 = rtb_Saturation_0 - rtb_Add_n_idx_0;
  rtb_Sum_idx_1 = rtb_Integrator_g_idx_0 - rtb_Add_ny_idx_0;

  /* Gain: '<S38>/Derivative Gain' incorporates:
   *  Gain: '<S42>/Integral Gain'
   */
  rtb_Integrator_g_idx_1 = 0.0F * rtb_Sum_idx_0;

  /* Gain: '<S48>/Filter Coefficient' incorporates:
   *  DiscreteIntegrator: '<S40>/Filter'
   *  Gain: '<S38>/Derivative Gain'
   *  Sum: '<S40>/SumD'
   */
  rtb_Saturation_0 = (rtb_Integrator_g_idx_1 - rtDW.Filter_DSTATE_j[0]) *
    78.6938705F;
  rtb_Integrator_g_idx_0 = rtb_Saturation_0;

  /* Sum: '<S54>/Sum' incorporates:
   *  DiscreteIntegrator: '<S45>/Integrator'
   *  Gain: '<S38>/Derivative Gain'
   *  Gain: '<S50>/Proportional Gain'
   */
  rtb_IntegralGain_i_idx_0 = (5.0F * rtb_Sum_idx_0 + rtDW.Integrator_DSTATE_n[0])
    + rtb_Saturation_0;

  /* Gain: '<S38>/Derivative Gain' incorporates:
   *  Gain: '<S42>/Integral Gain'
   */
  rtb_Sum_idx_0 = 0.0F * rtb_Sum_idx_1;

  /* Gain: '<S48>/Filter Coefficient' incorporates:
   *  DiscreteIntegrator: '<S40>/Filter'
   *  Gain: '<S38>/Derivative Gain'
   *  Sum: '<S40>/SumD'
   */
  rtb_Saturation_0 = (rtb_Sum_idx_0 - rtDW.Filter_DSTATE_j[1]) * 78.6938705F;

  /* Sum: '<S54>/Sum' incorporates:
   *  DiscreteIntegrator: '<S45>/Integrator'
   *  Gain: '<S38>/Derivative Gain'
   *  Gain: '<S50>/Proportional Gain'
   */
  rtb_Sum_idx_1 = (5.0F * rtb_Sum_idx_1 + rtDW.Integrator_DSTATE_n[1]) +
    rtb_Saturation_0;

  /* Saturate: '<S7>/Saturation' */
  if (rtb_IntegralGain_i_idx_0 > 4.0F) {
    rtb_IntegralGain_i_idx_0 = 4.0F;
  } else if (rtb_IntegralGain_i_idx_0 < -4.0F) {
    rtb_IntegralGain_i_idx_0 = -4.0F;
  }

  /* Sum: '<S7>/Sum1' incorporates:
   *  Saturate: '<S7>/Saturation'
   */
  rtb_IntegralGain_i_idx_0 -= rtb_DiscreteTransferFcn_d;

  /* Saturate: '<S7>/Saturation' */
  if (rtb_Sum_idx_1 > 4.0F) {
    rtb_Sum_idx_1 = 4.0F;
  } else if (rtb_Sum_idx_1 < -4.0F) {
    rtb_Sum_idx_1 = -4.0F;
  }

  /* Sum: '<S7>/Sum1' incorporates:
   *  Saturate: '<S7>/Saturation'
   */
  rtb_IntegralGain_i_idx_1 = rtb_Sum_idx_1 - rtb_DiscreteTransferFcn_mz;

  /* Gain: '<S102>/Filter Coefficient' incorporates:
   *  DiscreteIntegrator: '<S94>/Filter'
   *  Gain: '<S92>/Derivative Gain'
   *  Sum: '<S94>/SumD'
   */
  rtb_FilterCoefficient_a_0 = (0.0015F * rtb_IntegralGain_i_idx_0 -
    rtDW.Filter_DSTATE_e[0]) * 85.0F;
  rtb_FilterCoefficient_a_idx_0 = rtb_FilterCoefficient_a_0;

  /* Sum: '<S108>/Sum' incorporates:
   *  DiscreteIntegrator: '<S99>/Integrator'
   *  Gain: '<S104>/Proportional Gain'
   *  Gain: '<S92>/Derivative Gain'
   */
  rtb_DeadZone_g_0 = (0.05F * rtb_IntegralGain_i_idx_0 +
                      rtDW.Integrator_DSTATE_b[0]) + rtb_FilterCoefficient_a_0;
  rtb_DeadZone_g_idx_0 = rtb_DeadZone_g_0;

  /* Saturate: '<S106>/Saturation' */
  if (rtb_DeadZone_g_0 > 0.35F) {
    /* SignalConversion generated from: '<S5>/Matrix Multiply' */
    rtb_Saturation1_0[3] = 0.35F;
  } else if (rtb_DeadZone_g_0 < -0.35F) {
    /* SignalConversion generated from: '<S5>/Matrix Multiply' */
    rtb_Saturation1_0[3] = -0.35F;
  } else {
    /* SignalConversion generated from: '<S5>/Matrix Multiply' */
    rtb_Saturation1_0[3] = rtb_DeadZone_g_0;
  }

  /* Gain: '<S102>/Filter Coefficient' incorporates:
   *  DiscreteIntegrator: '<S94>/Filter'
   *  Gain: '<S92>/Derivative Gain'
   *  Sum: '<S94>/SumD'
   */
  rtb_FilterCoefficient_a_0 = (0.0018F * rtb_IntegralGain_i_idx_1 -
    rtDW.Filter_DSTATE_e[1]) * 85.0F;

  /* Sum: '<S108>/Sum' incorporates:
   *  DiscreteIntegrator: '<S99>/Integrator'
   *  Gain: '<S104>/Proportional Gain'
   *  Gain: '<S92>/Derivative Gain'
   */
  rtb_DeadZone_g_0 = (0.055F * rtb_IntegralGain_i_idx_1 +
                      rtDW.Integrator_DSTATE_b[1]) + rtb_FilterCoefficient_a_0;

  /* Saturate: '<S161>/Saturation' */
  if (rtb_DeadZone_h > 0.8F) {
    /* SignalConversion generated from: '<S5>/Matrix Multiply' */
    rtb_Saturation1_0[1] = 0.8F;
  } else if (rtb_DeadZone_h < -0.8F) {
    /* SignalConversion generated from: '<S5>/Matrix Multiply' */
    rtb_Saturation1_0[1] = -0.8F;
  } else {
    /* SignalConversion generated from: '<S5>/Matrix Multiply' */
    rtb_Saturation1_0[1] = rtb_DeadZone_h;
  }

  /* End of Saturate: '<S161>/Saturation' */

  /* Saturate: '<S106>/Saturation' */
  if (rtb_DeadZone_g_0 > 0.35F) {
    /* SignalConversion generated from: '<S5>/Matrix Multiply' */
    rtb_Saturation1_0[2] = 0.35F;
  } else if (rtb_DeadZone_g_0 < -0.35F) {
    /* SignalConversion generated from: '<S5>/Matrix Multiply' */
    rtb_Saturation1_0[2] = -0.35F;
  } else {
    /* SignalConversion generated from: '<S5>/Matrix Multiply' */
    rtb_Saturation1_0[2] = rtb_DeadZone_g_0;
  }

  /* Product: '<S5>/Matrix Multiply' incorporates:
   *  Constant: '<S5>/TorqueTotalThrustToThrustPerMotor'
   */
  tmp = 0.0F;
  tmp_0 = 0.0F;
  tmp_1 = 0.0F;
  tmp_2 = 0.0F;
  for (i = 0; i < 4; i++) {
    rtb_Sum_idx_1 = rtb_Saturation1_0[i];
    tmp_5 = i << 2;
    tmp += rtConstP.TorqueTotalThrustToThrustPerMot[tmp_5] * rtb_Sum_idx_1;
    tmp_0 += rtConstP.TorqueTotalThrustToThrustPerMot[tmp_5 + 1] * rtb_Sum_idx_1;
    tmp_1 += rtConstP.TorqueTotalThrustToThrustPerMot[tmp_5 + 2] * rtb_Sum_idx_1;
    tmp_2 += rtConstP.TorqueTotalThrustToThrustPerMot[tmp_5 + 3] * rtb_Sum_idx_1;
  }

  /* End of Product: '<S5>/Matrix Multiply' */

  /* Saturate: '<S5>/Saturation' */
  if (tmp > 3.0F) {
    tmp = 3.0F;
  } else if (tmp < 0.1F) {
    tmp = 0.1F;
  }

  /* Outport: '<Root>/FCSb' incorporates:
   *  Bias: '<S5>/Bias'
   *  Gain: '<S5>/ThrustToMotorCommand'
   *  Saturate: '<S5>/Saturation'
   *  Saturate: '<S5>/Saturation5'
   */
  rtY.FCSb[0] = 666.333313F * tmp + 48.0F;

  /* Saturate: '<S5>/Saturation' */
  if (tmp_0 > 3.0F) {
    tmp_0 = 3.0F;
  } else if (tmp_0 < 0.1F) {
    tmp_0 = 0.1F;
  }

  /* Outport: '<Root>/FCSb' incorporates:
   *  Bias: '<S5>/Bias'
   *  Gain: '<S5>/ThrustToMotorCommand'
   *  Saturate: '<S5>/Saturation'
   *  Saturate: '<S5>/Saturation5'
   */
  rtY.FCSb[1] = 666.333313F * tmp_0 + 48.0F;

  /* Saturate: '<S5>/Saturation' */
  if (tmp_1 > 3.0F) {
    tmp_1 = 3.0F;
  } else if (tmp_1 < 0.1F) {
    tmp_1 = 0.1F;
  }

  /* Outport: '<Root>/FCSb' incorporates:
   *  Bias: '<S5>/Bias'
   *  Gain: '<S5>/ThrustToMotorCommand'
   *  Saturate: '<S5>/Saturation'
   *  Saturate: '<S5>/Saturation5'
   */
  rtY.FCSb[2] = 666.333313F * tmp_1 + 48.0F;

  /* Saturate: '<S5>/Saturation' */
  if (tmp_2 > 3.0F) {
    tmp_2 = 3.0F;
  } else if (tmp_2 < 0.1F) {
    tmp_2 = 0.1F;
  }

  /* Outport: '<Root>/FCSb' incorporates:
   *  Bias: '<S5>/Bias'
   *  Gain: '<S5>/ThrustToMotorCommand'
   *  Saturate: '<S5>/Saturation'
   *  Saturate: '<S5>/Saturation5'
   */
  rtY.FCSb[3] = 666.333313F * tmp_2 + 48.0F;

  /* Sum: '<S179>/Minus' incorporates:
   *  Constant: '<S179>/Constant'
   *  Math: '<S179>/Math Function'
   *  Product: '<S179>/Matrix Multiply'
   *  SignalConversion generated from: '<S179>/Matrix Multiply'
   */
  for (i = 0; i < 3; i++) {
    rtb_Minus[i] = (real32_T)((rtb_MathFunction[i + 3] *
      rtb_DiscreteTransferFcn_i + rtb_MathFunction[i] *
      rtb_DiscreteTransferFcn_c) + rtb_MathFunction[i + 6] *
      rtb_DiscreteTransferFcn_h) + rtConstP.Constant_Value_j[i];
  }

  /* End of Sum: '<S179>/Minus' */

  /* Outputs for Enabled SubSystem: '<S204>/MeasurementUpdate' */
  /* Constant: '<S183>/Enable' incorporates:
   *  Constant: '<S183>/C'
   *  Constant: '<S183>/D'
   *  Delay: '<S183>/MemoryX'
   */
  MeasurementUpdate(true, rtConstB.Conversion, rtb_Gain, rtConstP.pooled8,
                    rtDW.MemoryX_DSTATE_h, 0.0F, rtb_Minus[2], rtDW.Product3_a,
                    &rtDW.MeasurementUpdate_g);

  /* End of Outputs for SubSystem: '<S204>/MeasurementUpdate' */

  /* Outputs for Enabled SubSystem: '<S317>/MeasurementUpdate' */
  /* Constant: '<S296>/Enable' incorporates:
   *  Constant: '<S296>/C'
   *  Constant: '<S296>/D'
   *  Delay: '<S296>/MemoryX'
   */
  MeasurementUpdate(true, rtConstB.Conversion_g, rtb_Atan2, rtConstP.pooled8,
                    rtDW.MemoryX_DSTATE, 0.0F, rtb_DiscreteTransferFcn_d,
                    rtDW.Product3, &rtDW.MeasurementUpdate_e);

  /* End of Outputs for SubSystem: '<S317>/MeasurementUpdate' */

  /* Outputs for Enabled SubSystem: '<S262>/MeasurementUpdate' */
  /* Constant: '<S241>/Enable' incorporates:
   *  Constant: '<S241>/C'
   *  Constant: '<S241>/D'
   *  Delay: '<S241>/MemoryX'
   */
  MeasurementUpdate(true, rtConstB.Conversion_i, rtb_Atan2_e, rtConstP.pooled8,
                    rtDW.MemoryX_DSTATE_m, 0.0F, rtb_DiscreteTransferFcn_mz,
                    rtDW.Product3_m, &rtDW.MeasurementUpdate_p);

  /* End of Outputs for SubSystem: '<S262>/MeasurementUpdate' */

  /* DeadZone: '<S91>/DeadZone' */
  if (rtb_DeadZone_g_idx_0 > 0.35F) {
    rtb_DeadZone_g_idx_0 -= 0.35F;
  } else if (rtb_DeadZone_g_idx_0 >= -0.35F) {
    rtb_DeadZone_g_idx_0 = 0.0F;
  } else {
    rtb_DeadZone_g_idx_0 -= -0.35F;
  }

  /* Gain: '<S96>/Integral Gain' */
  rtb_IntegralGain_i_idx_0 *= 0.08F;

  /* DeadZone: '<S91>/DeadZone' incorporates:
   *  Sum: '<S108>/Sum'
   */
  if (rtb_DeadZone_g_0 > 0.35F) {
    rtb_DiscreteTransferFcn_i = rtb_DeadZone_g_0 - 0.35F;
  } else if (rtb_DeadZone_g_0 >= -0.35F) {
    rtb_DiscreteTransferFcn_i = 0.0F;
  } else {
    rtb_DiscreteTransferFcn_i = rtb_DeadZone_g_0 - -0.35F;
  }

  /* Gain: '<S96>/Integral Gain' */
  rtb_IntegralGain_i_idx_1 *= 0.09F;

  /* Outport: '<Root>/xyz_s' incorporates:
   *  DiscreteIntegrator: '<S181>/Integrator1'
   *  DiscreteIntegrator: '<S181>/Integrator5'
   */
  rtY.xyz_s[0] = rtDW.Integrator1_DSTATE_p;
  rtY.xyz_s[1] = rtDW.Integrator5_DSTATE;
  rtY.xyz_s[2] = rtb_Add_m_idx_0;

  /* Outport: '<Root>/dxdydz_s' incorporates:
   *  DiscreteIntegrator: '<S181>/Integrator2'
   *  DiscreteIntegrator: '<S181>/Integrator4'
   */
  rtY.dxdydz_s[0] = rtDW.Integrator4_DSTATE;
  rtY.dxdydz_s[1] = rtDW.Integrator2_DSTATE_g;
  rtY.dxdydz_s[2] = rtb_Add_m_idx_1;

  /* Outport: '<Root>/rollpitchyaw_s' incorporates:
   *  DiscreteIntegrator: '<S240>/Integrator1'
   */
  rtY.rollpitchyaw_s[0] = rtb_Add_n_idx_0;
  rtY.rollpitchyaw_s[1] = rtb_Add_ny_idx_0;
  rtY.rollpitchyaw_s[2] = rtDW.Integrator1_DSTATE;

  /* Outport: '<Root>/pqr_s' */
  rtY.pqr_s[0] = rtb_DiscreteTransferFcn_d;
  rtY.pqr_s[1] = rtb_DiscreteTransferFcn_mz;
  rtY.pqr_s[2] = rtb_Saturation1;

  /* DeadZone: '<S146>/DeadZone' */
  if (rtb_DeadZone_h > 0.8F) {
    rtb_DeadZone_h -= 0.8F;
  } else if (rtb_DeadZone_h >= -0.8F) {
    rtb_DeadZone_h = 0.0F;
  } else {
    rtb_DeadZone_h -= -0.8F;
  }

  /* End of DeadZone: '<S146>/DeadZone' */

  /* Gain: '<S151>/Integral Gain' */
  rtb_IntegralGain_b *= 0.02F;

  /* MATLAB Function: '<S233>/SqrtUsedFcn' incorporates:
   *  Constant: '<S233>/isSqrtUsed'
   */
  SqrtUsedFcn(rtConstB.Conversion_e, false, rtb_Saturation);

  /* MATLAB Function: '<S291>/SqrtUsedFcn' incorporates:
   *  Constant: '<S291>/isSqrtUsed'
   */
  SqrtUsedFcn(rtConstB.Conversion_o, false, rtb_Saturation);

  /* MATLAB Function: '<S346>/SqrtUsedFcn' incorporates:
   *  Constant: '<S346>/isSqrtUsed'
   */
  SqrtUsedFcn(rtConstB.Conversion_d, false, rtb_Saturation);

  /* Outport: '<Root>/emergency' incorporates:
   *  Inport: '<Root>/kill_switch'
   */
  rtY.emergency = rtU.kill_switch;

  /* Update for Delay: '<S296>/MemoryX' */
  rtDW.icLoad = false;

  /* Product: '<S317>/A[k]*xhat[k|k-1]' incorporates:
   *  Constant: '<S296>/A'
   *  Delay: '<S296>/MemoryX'
   */
  tmp = rtDW.MemoryX_DSTATE[0];
  tmp_0 = 0.0F * rtDW.MemoryX_DSTATE[0];
  rtb_Sum_idx_1 = rtDW.MemoryX_DSTATE[1];

  /* Update for DiscreteTransferFcn: '<S354>/Discrete Transfer Fcn' incorporates:
   *  Inport: '<Root>/axayaz_s'
   */
  rtDW.DiscreteTransferFcn_states = rtU.axayaz_s[1] - -0.36787945F *
    rtDW.DiscreteTransferFcn_states;

  /* Update for DiscreteTransferFcn: '<S355>/Discrete Transfer Fcn' incorporates:
   *  Inport: '<Root>/axayaz_s'
   */
  rtDW.DiscreteTransferFcn_states_l = rtU.axayaz_s[2] - -0.36787945F *
    rtDW.DiscreteTransferFcn_states_l;

  /* Update for Delay: '<S241>/MemoryX' */
  rtDW.icLoad_e = false;

  /* Update for Delay: '<S296>/MemoryX' incorporates:
   *  Constant: '<S296>/A'
   *  Constant: '<S296>/B'
   *  Product: '<S317>/A[k]*xhat[k|k-1]'
   *  Product: '<S317>/B[k]*u[k]'
   *  Product: '<S348>/Product3'
   *  Sum: '<S317>/Add'
   */
  rtDW.MemoryX_DSTATE[0] = ((-0.005F * rtb_Sum_idx_1 + tmp) + 0.005F *
    rtb_DiscreteTransferFcn_d) + rtDW.Product3[0];
  rtDW.MemoryX_DSTATE[1] = (0.0F * rtb_DiscreteTransferFcn_d + (tmp_0 +
    rtb_Sum_idx_1)) + rtDW.Product3[1];

  /* Product: '<S262>/A[k]*xhat[k|k-1]' incorporates:
   *  Constant: '<S241>/A'
   *  Delay: '<S241>/MemoryX'
   */
  tmp = rtDW.MemoryX_DSTATE_m[0];
  tmp_0 = 0.0F * rtDW.MemoryX_DSTATE_m[0];
  rtb_Sum_idx_1 = rtDW.MemoryX_DSTATE_m[1];

  /* Update for DiscreteTransferFcn: '<S356>/Discrete Transfer Fcn' incorporates:
   *  Inport: '<Root>/axayaz_s'
   */
  rtDW.DiscreteTransferFcn_states_o = rtU.axayaz_s[0] - -0.36787945F *
    rtDW.DiscreteTransferFcn_states_o;

  /* Update for DiscreteIntegrator: '<S240>/Integrator1' */
  rtDW.Integrator1_DSTATE += 0.005F * rtb_Saturation1;

  /* Update for Delay: '<S183>/MemoryX' */
  rtDW.icLoad_h = false;

  /* Update for Delay: '<S241>/MemoryX' incorporates:
   *  Constant: '<S241>/A'
   *  Constant: '<S241>/B'
   *  Product: '<S262>/A[k]*xhat[k|k-1]'
   *  Product: '<S262>/B[k]*u[k]'
   *  Product: '<S293>/Product3'
   *  Sum: '<S262>/Add'
   */
  rtDW.MemoryX_DSTATE_m[0] = ((-0.005F * rtb_Sum_idx_1 + tmp) + 0.005F *
    rtb_DiscreteTransferFcn_mz) + rtDW.Product3_m[0];
  rtDW.MemoryX_DSTATE_m[1] = (0.0F * rtb_DiscreteTransferFcn_mz + (tmp_0 +
    rtb_Sum_idx_1)) + rtDW.Product3_m[1];

  /* Product: '<S204>/A[k]*xhat[k|k-1]' incorporates:
   *  Constant: '<S183>/A'
   *  Delay: '<S183>/MemoryX'
   */
  tmp = rtDW.MemoryX_DSTATE_h[0];
  tmp_0 = 0.0F * rtDW.MemoryX_DSTATE_h[0];
  rtb_Sum_idx_1 = rtDW.MemoryX_DSTATE_h[1];

  /* Update for Delay: '<S183>/MemoryX' incorporates:
   *  Constant: '<S183>/A'
   *  Constant: '<S183>/B'
   *  Product: '<S204>/A[k]*xhat[k|k-1]'
   *  Product: '<S204>/B[k]*u[k]'
   *  Product: '<S235>/Product3'
   *  Sum: '<S204>/Add'
   */
  rtDW.MemoryX_DSTATE_h[0] = ((0.005F * rtb_Sum_idx_1 + tmp) + 1.25E-5F *
    rtb_Minus[2]) + rtDW.Product3_a[0];
  rtDW.MemoryX_DSTATE_h[1] = (0.005F * rtb_Minus[2] + (tmp_0 + rtb_Sum_idx_1)) +
    rtDW.Product3_a[1];

  /* Update for DiscreteTransferFcn: '<S175>/Discrete Transfer Fcn' incorporates:
   *  Inport: '<Root>/altitude_s'
   */
  rtDW.DiscreteTransferFcn_states_f = rtU.altitude_s - -0.951229453F *
    rtDW.DiscreteTransferFcn_states_f;

  /* Update for UnitDelay: '<S6>/Unit Delay' */
  rtDW.UnitDelay_DSTATE = rtb_Switch3;

  /* Update for DiscreteIntegrator: '<S6>/Integrator2' incorporates:
   *  Gain: '<S6>/Gain4'
   *  Inport: '<Root>/controlModePosVSOrient'
   */
  rtDW.Integrator2_DSTATE += 1.2F * rtb_Sum3 * 0.005F;
  if (rtDW.Integrator2_DSTATE > 1.5F) {
    rtDW.Integrator2_DSTATE = 1.5F;
  } else if (rtDW.Integrator2_DSTATE < -1.5F) {
    rtDW.Integrator2_DSTATE = -1.5F;
  }

  rtDW.Integrator2_PrevResetState = (int8_T)rtU.controlModePosVSOrient;

  /* End of Update for DiscreteIntegrator: '<S6>/Integrator2' */

  /* Update for DiscreteTransferFcn: '<S352>/Discrete Transfer Fcn' incorporates:
   *  Inport: '<Root>/pqr_sf'
   */
  rtDW.DiscreteTransferFcn_states_ll = rtU.pqr_sf[2] - -0.082085F *
    rtDW.DiscreteTransferFcn_states_ll;

  /* Switch: '<S144>/Switch1' incorporates:
   *  Constant: '<S144>/Clamping_zero'
   *  Constant: '<S144>/Constant'
   *  Constant: '<S144>/Constant2'
   *  RelationalOperator: '<S144>/fix for DT propagation issue'
   */
  if (rtb_DeadZone_h > 0.0F) {
    tmp_3 = 1;
  } else {
    tmp_3 = -1;
  }

  /* Switch: '<S144>/Switch2' incorporates:
   *  Constant: '<S144>/Clamping_zero'
   *  Constant: '<S144>/Constant3'
   *  Constant: '<S144>/Constant4'
   *  RelationalOperator: '<S144>/fix for DT propagation issue1'
   */
  if (rtb_IntegralGain_b > 0.0F) {
    tmp_4 = 1;
  } else {
    tmp_4 = -1;
  }

  /* Switch: '<S144>/Switch' incorporates:
   *  Constant: '<S144>/Clamping_zero'
   *  Constant: '<S144>/Constant1'
   *  Logic: '<S144>/AND3'
   *  RelationalOperator: '<S144>/Equal1'
   *  RelationalOperator: '<S144>/Relational Operator'
   *  Switch: '<S144>/Switch1'
   *  Switch: '<S144>/Switch2'
   */
  if ((rtb_DeadZone_h != 0.0F) && (tmp_3 == tmp_4)) {
    rtb_IntegralGain_b = 0.0F;
  }

  /* Update for DiscreteIntegrator: '<S154>/Integrator' incorporates:
   *  Switch: '<S144>/Switch'
   */
  rtDW.Integrator_DSTATE += 0.005F * rtb_IntegralGain_b;

  /* Update for DiscreteIntegrator: '<S149>/Filter' */
  rtDW.Filter_DSTATE += 0.005F * rtb_FilterCoefficient;

  /* Update for DiscreteTransferFcn: '<S353>/Discrete Transfer Fcn' incorporates:
   *  Inport: '<Root>/pqr_sf'
   */
  rtDW.DiscreteTransferFcn_states_n = rtU.pqr_sf[0] - -0.082085F *
    rtDW.DiscreteTransferFcn_states_n;

  /* Update for DiscreteTransferFcn: '<S351>/Discrete Transfer Fcn' incorporates:
   *  Inport: '<Root>/pqr_sf'
   */
  rtDW.DiscreteTransferFcn_states_nu = rtU.pqr_sf[1] - -0.082085F *
    rtDW.DiscreteTransferFcn_states_nu;

  /* Update for DiscreteIntegrator: '<S45>/Integrator' */
  rtDW.Integrator_DSTATE_n[0] += rtb_Integrator_g_idx_1 * 0.005F;

  /* Update for DiscreteIntegrator: '<S40>/Filter' */
  rtDW.Filter_DSTATE_j[0] += 0.005F * rtb_Integrator_g_idx_0;

  /* Switch: '<S89>/Switch1' incorporates:
   *  Constant: '<S89>/Clamping_zero'
   *  Constant: '<S89>/Constant'
   *  Constant: '<S89>/Constant2'
   *  RelationalOperator: '<S89>/fix for DT propagation issue'
   */
  if (rtb_DeadZone_g_idx_0 > 0.0F) {
    tmp_3 = 1;
  } else {
    tmp_3 = -1;
  }

  /* Switch: '<S89>/Switch2' incorporates:
   *  Constant: '<S89>/Clamping_zero'
   *  Constant: '<S89>/Constant3'
   *  Constant: '<S89>/Constant4'
   *  RelationalOperator: '<S89>/fix for DT propagation issue1'
   */
  if (rtb_IntegralGain_i_idx_0 > 0.0F) {
    tmp_4 = 1;
  } else {
    tmp_4 = -1;
  }

  /* Switch: '<S89>/Switch' incorporates:
   *  Constant: '<S89>/Clamping_zero'
   *  Constant: '<S89>/Constant1'
   *  Logic: '<S89>/AND3'
   *  RelationalOperator: '<S89>/Equal1'
   *  RelationalOperator: '<S89>/Relational Operator'
   *  Switch: '<S89>/Switch1'
   *  Switch: '<S89>/Switch2'
   */
  if ((rtb_DeadZone_g_idx_0 != 0.0F) && (tmp_3 == tmp_4)) {
    rtb_IntegralGain_i_idx_0 = 0.0F;
  }

  /* Update for DiscreteIntegrator: '<S99>/Integrator' incorporates:
   *  Switch: '<S89>/Switch'
   */
  rtDW.Integrator_DSTATE_b[0] += 0.005F * rtb_IntegralGain_i_idx_0;

  /* Update for DiscreteIntegrator: '<S94>/Filter' */
  rtDW.Filter_DSTATE_e[0] += 0.005F * rtb_FilterCoefficient_a_idx_0;

  /* Update for DiscreteIntegrator: '<S45>/Integrator' */
  rtDW.Integrator_DSTATE_n[1] += rtb_Sum_idx_0 * 0.005F;

  /* Update for DiscreteIntegrator: '<S40>/Filter' incorporates:
   *  Gain: '<S48>/Filter Coefficient'
   */
  rtDW.Filter_DSTATE_j[1] += 0.005F * rtb_Saturation_0;

  /* Switch: '<S89>/Switch1' incorporates:
   *  Constant: '<S89>/Clamping_zero'
   *  Constant: '<S89>/Constant'
   *  Constant: '<S89>/Constant2'
   *  RelationalOperator: '<S89>/fix for DT propagation issue'
   */
  if (rtb_DiscreteTransferFcn_i > 0.0F) {
    tmp_3 = 1;
  } else {
    tmp_3 = -1;
  }

  /* Switch: '<S89>/Switch2' incorporates:
   *  Constant: '<S89>/Clamping_zero'
   *  Constant: '<S89>/Constant3'
   *  Constant: '<S89>/Constant4'
   *  RelationalOperator: '<S89>/fix for DT propagation issue1'
   */
  if (rtb_IntegralGain_i_idx_1 > 0.0F) {
    tmp_4 = 1;
  } else {
    tmp_4 = -1;
  }

  /* Switch: '<S89>/Switch' incorporates:
   *  Constant: '<S89>/Clamping_zero'
   *  Constant: '<S89>/Constant1'
   *  Logic: '<S89>/AND3'
   *  RelationalOperator: '<S89>/Equal1'
   *  RelationalOperator: '<S89>/Relational Operator'
   *  Switch: '<S89>/Switch1'
   *  Switch: '<S89>/Switch2'
   */
  if ((rtb_DiscreteTransferFcn_i != 0.0F) && (tmp_3 == tmp_4)) {
    rtb_IntegralGain_i_idx_1 = 0.0F;
  }

  /* Update for DiscreteIntegrator: '<S99>/Integrator' incorporates:
   *  Switch: '<S89>/Switch'
   */
  rtDW.Integrator_DSTATE_b[1] += 0.005F * rtb_IntegralGain_i_idx_1;

  /* Update for DiscreteIntegrator: '<S94>/Filter' incorporates:
   *  Gain: '<S102>/Filter Coefficient'
   */
  rtDW.Filter_DSTATE_e[1] += 0.005F * rtb_FilterCoefficient_a_0;

  /* Update for DiscreteIntegrator: '<S181>/Integrator5' incorporates:
   *  DiscreteIntegrator: '<S181>/Integrator2'
   */
  rtDW.Integrator5_DSTATE += 0.005F * rtDW.Integrator2_DSTATE_g;

  /* Update for DiscreteIntegrator: '<S181>/Integrator1' incorporates:
   *  DiscreteIntegrator: '<S181>/Integrator4'
   */
  rtDW.Integrator1_DSTATE_p += 0.005F * rtDW.Integrator4_DSTATE;

  /* Update for DiscreteIntegrator: '<S181>/Integrator4' */
  rtDW.Integrator4_DSTATE += 0.005F * rtb_Minus[0];

  /* Update for DiscreteIntegrator: '<S181>/Integrator2' */
  rtDW.Integrator2_DSTATE_g += 0.005F * rtb_Minus[1];
}

/* Model initialize function */
void FCS_initialize(void)
{
  /* InitializeConditions for Delay: '<S296>/MemoryX' */
  rtDW.icLoad = true;

  /* InitializeConditions for Delay: '<S241>/MemoryX' */
  rtDW.icLoad_e = true;

  /* InitializeConditions for Delay: '<S183>/MemoryX' */
  rtDW.icLoad_h = true;

  /* InitializeConditions for DiscreteIntegrator: '<S6>/Integrator2' */
  rtDW.Integrator2_PrevResetState = 2;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
