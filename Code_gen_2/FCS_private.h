/*
 * FCS_private.h
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

#ifndef FCS_private_h_
#define FCS_private_h_
#include "rtwtypes.h"
#include "builtin_typeid_types.h"
#include "multiword_types.h"
#include "FCS.h"
#include "FCS_types.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"

/* Private macros used by the generated code to access rtModel */
#ifndef rtmIsMajorTimeStep
#define rtmIsMajorTimeStep(rtm)        (((rtm)->Timing.simTimeStep) == MAJOR_TIME_STEP)
#endif

#ifndef rtmIsMinorTimeStep
#define rtmIsMinorTimeStep(rtm)        (((rtm)->Timing.simTimeStep) == MINOR_TIME_STEP)
#endif

#ifndef rtmSetTFinal
#define rtmSetTFinal(rtm, val)         ((rtm)->Timing.tFinal = (val))
#endif

#ifndef rtmSetTPtr
#define rtmSetTPtr(rtm, val)           ((rtm)->Timing.t = (val))
#endif

extern void FCS_MeasurementUpdate_Init(B_MeasurementUpdate_FCS_T *localB,
  P_MeasurementUpdate_FCS_T *localP);
extern void FCS_MeasurementUpdate_Disable(B_MeasurementUpdate_FCS_T *localB,
  DW_MeasurementUpdate_FCS_T *localDW, P_MeasurementUpdate_FCS_T *localP);
extern void FCS_MeasurementUpdate(RT_MODEL_FCS_T * const FCS_M, boolean_T
  rtu_Enable, const real_T rtu_Lk[2], real_T rtu_yk, const real_T rtu_Ck[2],
  const real_T rtu_xhatkk1[2], real_T rtu_Dk, real_T rtu_uk,
  B_MeasurementUpdate_FCS_T *localB, DW_MeasurementUpdate_FCS_T *localDW,
  P_MeasurementUpdate_FCS_T *localP);
extern void FCS_EnabledSubsystem_Init(B_EnabledSubsystem_FCS_T *localB,
  P_EnabledSubsystem_FCS_T *localP);
extern void FCS_EnabledSubsystem_Disable(B_EnabledSubsystem_FCS_T *localB,
  DW_EnabledSubsystem_FCS_T *localDW, P_EnabledSubsystem_FCS_T *localP);
extern void FCS_EnabledSubsystem(RT_MODEL_FCS_T * const FCS_M, boolean_T
  rtu_Enable, const real_T rtu_Mk[2], const real_T rtu_Ck[2], real_T rtu_yk,
  const real_T rtu_xhatkk1[2], B_EnabledSubsystem_FCS_T *localB,
  DW_EnabledSubsystem_FCS_T *localDW, P_EnabledSubsystem_FCS_T *localP);

/* private model entry point functions */
extern void FCS_derivatives(void);

#endif                                 /* FCS_private_h_ */
