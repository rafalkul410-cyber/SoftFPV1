/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: FCS_data.c
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

/* Invariant block signals (default storage) */
const ConstB rtConstB = {
  { 0.100005351F, 0.0948930532F },     /* '<S227>/Conversion' */

  { 0.0995308906F, 0.0948930532F },    /* '<S228>/Conversion' */

  { 0.00995308906F, 0.00948930532F, 0.00948930532F, 0.209774867F },/* '<S230>/Conversion' */

  { 0.204944283F, -0.199506044F },     /* '<S285>/Conversion' */

  { 0.203946754F, -0.199506044F },     /* '<S286>/Conversion' */

  { 0.203946754F, -0.199506044F, -0.199506044F, 10.2225857F },/* '<S288>/Conversion' */

  { 0.204944283F, -0.199506044F },     /* '<S340>/Conversion' */

  { 0.203946754F, -0.199506044F },     /* '<S341>/Conversion' */

  { 0.203946754F, -0.199506044F, -0.199506044F, 10.2225857F }/* '<S343>/Conversion' */
};

/* Constant parameters (default storage) */
const ConstP rtConstP = {
  /* Computed Parameter: TorqueTotalThrustToThrustPerMot
   * Referenced by: '<S5>/TorqueTotalThrustToThrustPerMotor'
   */
  { 0.25F, 0.25F, 0.25F, 0.25F, 66.9291306F, -66.9291306F, 66.9291306F,
    -66.9291306F, -2.35702252F, -2.35702252F, 2.35702252F, 2.35702252F,
    -2.35702252F, 2.35702252F, 2.35702252F, -2.35702252F },

  /* Computed Parameter: Constant_Value_j
   * Referenced by: '<S179>/Constant'
   */
  { 0.0F, 0.0F, 9.81F },

  /* Pooled Parameter (Expression: )
   * Referenced by:
   *   '<S241>/C'
   *   '<S296>/C'
   *   '<S183>/C'
   */
  { 1.0F, 0.0F }
};

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
