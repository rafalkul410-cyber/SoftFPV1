/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: FCS_data.c
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

/* Invariant block signals (default storage) */
const ConstB rtConstB = {
  { 0.100005351F, 0.0948930532F },     /* '<S390>/Conversion' */

  { 0.0995308906F, 0.0948930532F },    /* '<S391>/Conversion' */

  { 0.00995308906F, 0.00948930532F, 0.00948930532F, 0.209774867F },/* '<S393>/Conversion' */

  { 0.204944283F, -0.199506044F },     /* '<S448>/Conversion' */

  { 0.203946754F, -0.199506044F },     /* '<S449>/Conversion' */

  { 0.203946754F, -0.199506044F, -0.199506044F, 10.2225857F }/* '<S451>/Conversion' */
};

/* Constant parameters (default storage) */
const ConstP rtConstP = {
  /* Computed Parameter: TorqueTotalThrustToThrustPerMot
   * Referenced by: '<S4>/TorqueTotalThrustToThrustPerMotor'
   */
  { 0.25F, 0.25F, 0.25F, 0.25F, 66.9291306F, -66.9291306F, 66.9291306F,
    -66.9291306F, -2.35702252F, -2.35702252F, 2.35702252F, 2.35702252F,
    -2.35702252F, 2.35702252F, 2.35702252F, -2.35702252F },

  /* Computed Parameter: Constant_Value_j
   * Referenced by: '<S342>/Constant'
   */
  { 0.0F, 0.0F, 9.81F },

  /* Pooled Parameter (Expression: )
   * Referenced by:
   *   '<S404>/C'
   *   '<S346>/C'
   */
  { 1.0F, 0.0F }
};

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
