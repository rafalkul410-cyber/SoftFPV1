/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: FCS_data.c
 *
 * Code generated for Simulink model 'FCS'.
 *
 * Model version                  : 1.20
 * Simulink Coder version         : 25.2 (R2025b) 28-Jul-2025
 * C/C++ source code generated on : Mon Aug  3 22:44:34 2026
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-M
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. RAM efficiency
 * Validation result: Not run
 */

#include "FCS.h"

/* Constant parameters (default storage) */
const ConstP rtConstP = {
  /* Expression: [0 0 g]
   * Referenced by: '<S342>/Constant'
   */
  { 0.0, 0.0, 9.81 },

  /* Pooled Parameter (Expression: pInitialization.C)
   * Referenced by:
   *   '<S404>/C'
   *   '<S459>/C'
   *   '<S346>/C'
   */
  { 1.0, 0.0 },

  /* Expression: pInitialization.Z
   * Referenced by: '<S347>/CovarianceZ'
   */
  { 0.009953088807318284, 0.0094893050953525643, 0.0094893050953525643,
    0.20977487197019559 },

  /* Expression: pInitialization.L
   * Referenced by: '<S347>/KalmanGainL'
   */
  { 0.10000535332795049, 0.094893050953525723 },

  /* Expression: pInitialization.M
   * Referenced by: '<S347>/KalmanGainM'
   */
  { 0.099530888073182819, 0.09489305095352564 },

  /* Pooled Parameter (Expression: pInitialization.Z)
   * Referenced by:
   *   '<S405>/CovarianceZ'
   *   '<S460>/CovarianceZ'
   */
  { 0.20394675669207774, -0.19950604543572131, -0.19950604543572131,
    10.222585297938185 },

  /* Pooled Parameter (Expression: pInitialization.L)
   * Referenced by:
   *   '<S405>/KalmanGainL'
   *   '<S460>/KalmanGainL'
   */
  { 0.2049442869192564, -0.19950604543572328 },

  /* Pooled Parameter (Expression: pInitialization.M)
   * Referenced by:
   *   '<S405>/KalmanGainM'
   *   '<S460>/KalmanGainM'
   */
  { 0.20394675669207771, -0.19950604543572131 },

  /* Computed Parameter: TorqueTotalThrustToThrustPerMot
   * Referenced by: '<S4>/TorqueTotalThrustToThrustPerMotor'
   */
  { 0.25F, 0.25F, 0.25F, 0.25F, 66.9291306F, -66.9291306F, 66.9291306F,
    -66.9291306F, -2.35702252F, -2.35702252F, 2.35702252F, 2.35702252F,
    -2.35702252F, 2.35702252F, 2.35702252F, -2.35702252F }
};

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
