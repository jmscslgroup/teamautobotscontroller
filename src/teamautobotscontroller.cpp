//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: teamautobotscontroller.cpp
//
// Code generated for Simulink model 'teamautobotscontroller'.
//
// Model version                  : 1.13
// Simulink Coder version         : 9.8 (R2022b) 13-May-2022
// C/C++ source code generated on : Thu Nov 30 11:50:24 2023
//
// Target selection: ert.tlc
// Embedded hardware selection: Generic->Unspecified (assume 32-bit Generic)
// Code generation objectives: Unspecified
// Validation result: Not run
//
#include "teamautobotscontroller.h"

extern "C"
{

#include "rt_nonfinite.h"

}

#include <math.h>
#include "rtwtypes.h"
#include "teamautobotscontroller_types.h"
#include "teamautobotscontroller_private.h"

// Block signals (default storage)
B_teamautobotscontroller_T teamautobotscontroller_B;

// Continuous states
X_teamautobotscontroller_T teamautobotscontroller_X;

// Block states (default storage)
DW_teamautobotscontroller_T teamautobotscontroller_DW;

// Real-time model
RT_MODEL_teamautobotscontroll_T teamautobotscontroller_M_ =
  RT_MODEL_teamautobotscontroll_T();
RT_MODEL_teamautobotscontroll_T *const teamautobotscontroller_M =
  &teamautobotscontroller_M_;

//
// This function updates continuous states using the ODE3 fixed-step
// solver algorithm
//
static void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
{
  // Solver Matrices
  static const real_T rt_ODE3_A[3] = {
    1.0/2.0, 3.0/4.0, 1.0
  };

  static const real_T rt_ODE3_B[3][3] = {
    { 1.0/2.0, 0.0, 0.0 },

    { 0.0, 3.0/4.0, 0.0 },

    { 2.0/9.0, 1.0/3.0, 4.0/9.0 }
  };

  time_T t = rtsiGetT(si);
  time_T tnew = rtsiGetSolverStopTime(si);
  time_T h = rtsiGetStepSize(si);
  real_T *x = rtsiGetContStates(si);
  ODE3_IntgData *id = static_cast<ODE3_IntgData *>(rtsiGetSolverData(si));
  real_T *y = id->y;
  real_T *f0 = id->f[0];
  real_T *f1 = id->f[1];
  real_T *f2 = id->f[2];
  real_T hB[3];
  int_T i;
  int_T nXc = 4;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);

  // Save the state values at time t in y, we'll use x as ynew.
  (void) memcpy(y, x,
                static_cast<uint_T>(nXc)*sizeof(real_T));

  // Assumes that rtsiSetT and ModelOutputs are up-to-date
  // f0 = f(t,y)
  rtsiSetdX(si, f0);
  teamautobotscontroller_derivatives();

  // f(:,2) = feval(odefile, t + hA(1), y + f*hB(:,1), args(:)(*));
  hB[0] = h * rt_ODE3_B[0][0];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[0]);
  rtsiSetdX(si, f1);
  teamautobotscontroller_step();
  teamautobotscontroller_derivatives();

  // f(:,3) = feval(odefile, t + hA(2), y + f*hB(:,2), args(:)(*));
  for (i = 0; i <= 1; i++) {
    hB[i] = h * rt_ODE3_B[1][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[1]);
  rtsiSetdX(si, f2);
  teamautobotscontroller_step();
  teamautobotscontroller_derivatives();

  // tnew = t + hA(3);
  // ynew = y + f*hB(:,3);
  for (i = 0; i <= 2; i++) {
    hB[i] = h * rt_ODE3_B[2][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1] + f2[i]*hB[2]);
  }

  rtsiSetT(si, tnew);
  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

// Model step function
void teamautobotscontroller_step(void)
{
  SL_Bus_teamautobotscontroller_std_msgs_Float64 b_varargout_2;
  SL_Bus_teamautobotscontroller_std_msgs_Float64 rtb_BusAssignment;
  real_T rtb_Data;
  real_T rtb_Merge2;
  boolean_T rtb_NotEqual_d;
  if (rtmIsMajorTimeStep(teamautobotscontroller_M)) {
    // set solver stop time
    rtsiSetSolverStopTime(&teamautobotscontroller_M->solverInfo,
                          ((teamautobotscontroller_M->Timing.clockTick0+1)*
      teamautobotscontroller_M->Timing.stepSize0));
  }                                    // end MajorTimeStep

  // Update absolute time of base rate at minor time step
  if (rtmIsMinorTimeStep(teamautobotscontroller_M)) {
    teamautobotscontroller_M->Timing.t[0] = rtsiGetT
      (&teamautobotscontroller_M->solverInfo);
  }

  if (rtmIsMajorTimeStep(teamautobotscontroller_M)) {
    // Outputs for Atomic SubSystem: '<Root>/Subscribe'
    // MATLABSystem: '<S4>/SourceBlock'
    rtb_NotEqual_d = Sub_teamautobotscontroller_36.getLatestMessage
      (&b_varargout_2);

    // Outputs for Enabled SubSystem: '<S4>/Enabled Subsystem' incorporates:
    //   EnablePort: '<S114>/Enable'

    if (rtb_NotEqual_d) {
      // SignalConversion generated from: '<S114>/In1'
      teamautobotscontroller_B.In1_b = b_varargout_2;
    }

    // End of MATLABSystem: '<S4>/SourceBlock'
    // End of Outputs for SubSystem: '<S4>/Enabled Subsystem'
    // End of Outputs for SubSystem: '<Root>/Subscribe'

    // SignalConversion generated from: '<Root>/Bus Selector'
    rtb_Data = teamautobotscontroller_B.In1_b.Data;

    // If: '<S1>/If1' incorporates:
    //   SignalConversion generated from: '<Root>/Bus Selector'

    if (rtsiIsModeUpdateTimeStep(&teamautobotscontroller_M->solverInfo)) {
      teamautobotscontroller_DW.If1_ActiveSubsystem = static_cast<int8_T>
        (!(teamautobotscontroller_B.In1_b.Data > 0.1));
    }

    switch (teamautobotscontroller_DW.If1_ActiveSubsystem) {
     case 0:
      // Outputs for IfAction SubSystem: '<S1>/NULL_Handler1' incorporates:
      //   ActionPort: '<S6>/Action Port'

      // SignalConversion generated from: '<S6>/V1' incorporates:
      //   SignalConversion generated from: '<Root>/Bus Selector'

      rtb_Merge2 = teamautobotscontroller_B.In1_b.Data;

      // End of Outputs for SubSystem: '<S1>/NULL_Handler1'
      break;

     case 1:
      // Outputs for IfAction SubSystem: '<S1>/Null_Handler2' incorporates:
      //   ActionPort: '<S7>/Action Port'

      // Sum: '<S7>/Add' incorporates:
      //   Constant: '<S7>/Constant'
      //   SignalConversion generated from: '<Root>/Bus Selector'

      rtb_Merge2 = teamautobotscontroller_B.In1_b.Data +
        teamautobotscontroller_P.Constant_Value_c;

      // End of Outputs for SubSystem: '<S1>/Null_Handler2'
      break;
    }

    // End of If: '<S1>/If1'

    // Outputs for Atomic SubSystem: '<Root>/Subscribe1'
    // MATLABSystem: '<S5>/SourceBlock'
    rtb_NotEqual_d = Sub_teamautobotscontroller_48.getLatestMessage
      (&b_varargout_2);

    // Outputs for Enabled SubSystem: '<S5>/Enabled Subsystem' incorporates:
    //   EnablePort: '<S115>/Enable'

    if (rtb_NotEqual_d) {
      // SignalConversion generated from: '<S115>/In1'
      teamautobotscontroller_B.In1 = b_varargout_2;
    }

    // End of MATLABSystem: '<S5>/SourceBlock'
    // End of Outputs for SubSystem: '<S5>/Enabled Subsystem'
    // End of Outputs for SubSystem: '<Root>/Subscribe1'

    // Product: '<S1>/Divide'
    rtb_Merge2 = teamautobotscontroller_B.In1.Data / rtb_Merge2;

    // Sum: '<S1>/Subtract' incorporates:
    //   Constant: '<Root>/Time Gap'

    teamautobotscontroller_B.error = rtb_Merge2 -
      teamautobotscontroller_P.TimeGap_Value;
  }

  // If: '<S1>/If'
  if (rtsiIsModeUpdateTimeStep(&teamautobotscontroller_M->solverInfo)) {
    teamautobotscontroller_DW.If_ActiveSubsystem = static_cast<int8_T>
      (!(teamautobotscontroller_B.error > 0.0));
  }

  switch (teamautobotscontroller_DW.If_ActiveSubsystem) {
   case 0:
    {
      real_T tmp_1;
      int32_T tmp;
      int32_T tmp_0;

      // Outputs for IfAction SubSystem: '<S1>/Switch Case: Car Hunter Mode' incorporates:
      //   ActionPort: '<S11>/Action Port'

      // Gain: '<S100>/Filter Coefficient' incorporates:
      //   Gain: '<S91>/Derivative Gain'
      //   Integrator: '<S92>/Filter'
      //   Sum: '<S92>/SumD'

      teamautobotscontroller_B.FilterCoefficient_b =
        (teamautobotscontroller_P.Car_Hunter_PID_D *
         teamautobotscontroller_B.error -
         teamautobotscontroller_X.Filter_CSTATE_f) *
        teamautobotscontroller_P.Car_Hunter_PID_N;

      // Sum: '<S106>/Sum' incorporates:
      //   Gain: '<S102>/Proportional Gain'
      //   Integrator: '<S97>/Integrator'

      teamautobotscontroller_B.Merge =
        (teamautobotscontroller_P.Car_Hunter_PID_P *
         teamautobotscontroller_B.error +
         teamautobotscontroller_X.Integrator_CSTATE_e) +
        teamautobotscontroller_B.FilterCoefficient_b;

      // DeadZone: '<S90>/DeadZone'
      if (teamautobotscontroller_B.Merge >
          teamautobotscontroller_P.Car_Hunter_PID_UpperSaturationL) {
        // Gain: '<S94>/Integral Gain'
        teamautobotscontroller_B.Switch_k = teamautobotscontroller_B.Merge -
          teamautobotscontroller_P.Car_Hunter_PID_UpperSaturationL;
      } else if (teamautobotscontroller_B.Merge >=
                 teamautobotscontroller_P.Car_Hunter_PID_LowerSaturationL) {
        // Gain: '<S94>/Integral Gain'
        teamautobotscontroller_B.Switch_k = 0.0;
      } else {
        // Gain: '<S94>/Integral Gain'
        teamautobotscontroller_B.Switch_k = teamautobotscontroller_B.Merge -
          teamautobotscontroller_P.Car_Hunter_PID_LowerSaturationL;
      }

      // End of DeadZone: '<S90>/DeadZone'

      // RelationalOperator: '<S88>/NotEqual' incorporates:
      //   Gain: '<S88>/ZeroGain'

      rtb_NotEqual_d = (teamautobotscontroller_P.ZeroGain_Gain *
                        teamautobotscontroller_B.Merge !=
                        teamautobotscontroller_B.Switch_k);

      // Signum: '<S88>/SignPreSat'
      if (rtIsNaN(teamautobotscontroller_B.Switch_k)) {
        // DataTypeConversion: '<S88>/DataTypeConv1'
        tmp_1 = (rtNaN);
      } else if (teamautobotscontroller_B.Switch_k < 0.0) {
        // DataTypeConversion: '<S88>/DataTypeConv1'
        tmp_1 = -1.0;
      } else {
        // DataTypeConversion: '<S88>/DataTypeConv1'
        tmp_1 = (teamautobotscontroller_B.Switch_k > 0.0);
      }

      // End of Signum: '<S88>/SignPreSat'

      // DataTypeConversion: '<S88>/DataTypeConv1'
      if (rtIsNaN(tmp_1)) {
        tmp_0 = 0;
      } else {
        tmp_0 = static_cast<int32_T>(fmod(tmp_1, 256.0));
      }

      // Gain: '<S94>/Integral Gain'
      teamautobotscontroller_B.Switch_k =
        teamautobotscontroller_P.Car_Hunter_PID_I *
        teamautobotscontroller_B.error;

      // Signum: '<S88>/SignPreIntegrator'
      if (rtIsNaN(teamautobotscontroller_B.Switch_k)) {
        // DataTypeConversion: '<S88>/DataTypeConv2'
        tmp_1 = (rtNaN);
      } else if (teamautobotscontroller_B.Switch_k < 0.0) {
        // DataTypeConversion: '<S88>/DataTypeConv2'
        tmp_1 = -1.0;
      } else {
        // DataTypeConversion: '<S88>/DataTypeConv2'
        tmp_1 = (teamautobotscontroller_B.Switch_k > 0.0);
      }

      // End of Signum: '<S88>/SignPreIntegrator'

      // DataTypeConversion: '<S88>/DataTypeConv2'
      if (rtIsNaN(tmp_1)) {
        tmp = 0;
      } else {
        tmp = static_cast<int32_T>(fmod(tmp_1, 256.0));
      }

      // Logic: '<S88>/AND3' incorporates:
      //   DataTypeConversion: '<S88>/DataTypeConv1'
      //   DataTypeConversion: '<S88>/DataTypeConv2'
      //   RelationalOperator: '<S88>/Equal1'

      teamautobotscontroller_B.AND3_g = (rtb_NotEqual_d && (static_cast<int8_T>
        (tmp_0 < 0 ? static_cast<int32_T>(static_cast<int8_T>
        (-static_cast<int8_T>(static_cast<uint8_T>(-static_cast<real_T>(tmp_0)))))
         : tmp_0) == (tmp < 0 ? static_cast<int32_T>(static_cast<int8_T>(-
        static_cast<int8_T>(static_cast<uint8_T>(-static_cast<real_T>(tmp))))) :
                      tmp)));
      if (rtmIsMajorTimeStep(teamautobotscontroller_M)) {
        // Memory: '<S88>/Memory'
        teamautobotscontroller_B.Memory_d =
          teamautobotscontroller_DW.Memory_PreviousInput_g;
      }

      // Switch: '<S88>/Switch'
      if (teamautobotscontroller_B.Memory_d) {
        // Gain: '<S94>/Integral Gain' incorporates:
        //   Constant: '<S88>/Constant1'
        //   Switch: '<S88>/Switch'

        teamautobotscontroller_B.Switch_k =
          teamautobotscontroller_P.Constant1_Value;
      }

      // End of Switch: '<S88>/Switch'

      // Saturate: '<S104>/Saturation'
      if (teamautobotscontroller_B.Merge >
          teamautobotscontroller_P.Car_Hunter_PID_UpperSaturationL) {
        // Sum: '<S106>/Sum' incorporates:
        //   Merge: '<S1>/Merge'

        teamautobotscontroller_B.Merge =
          teamautobotscontroller_P.Car_Hunter_PID_UpperSaturationL;
      } else if (teamautobotscontroller_B.Merge <
                 teamautobotscontroller_P.Car_Hunter_PID_LowerSaturationL) {
        // Sum: '<S106>/Sum' incorporates:
        //   Merge: '<S1>/Merge'

        teamautobotscontroller_B.Merge =
          teamautobotscontroller_P.Car_Hunter_PID_LowerSaturationL;
      }

      // End of Saturate: '<S104>/Saturation'
      // End of Outputs for SubSystem: '<S1>/Switch Case: Car Hunter Mode'
    }
    break;

   case 1:
    {
      real_T tmp_1;
      int32_T tmp;
      int32_T tmp_0;

      // Outputs for IfAction SubSystem: '<S1>/Switch Case: Car Follower Mode' incorporates:
      //   ActionPort: '<S10>/Action Port'

      // Gain: '<S49>/Filter Coefficient' incorporates:
      //   Gain: '<S40>/Derivative Gain'
      //   Integrator: '<S41>/Filter'
      //   Sum: '<S41>/SumD'

      teamautobotscontroller_B.FilterCoefficient =
        (teamautobotscontroller_P.Car_Follower_PID_D *
         teamautobotscontroller_B.error - teamautobotscontroller_X.Filter_CSTATE)
        * teamautobotscontroller_P.Car_Follower_PID_N;

      // Sum: '<S106>/Sum' incorporates:
      //   Gain: '<S51>/Proportional Gain'
      //   Integrator: '<S46>/Integrator'
      //   Sum: '<S55>/Sum'

      teamautobotscontroller_B.Merge =
        (teamautobotscontroller_P.Car_Follower_PID_P *
         teamautobotscontroller_B.error +
         teamautobotscontroller_X.Integrator_CSTATE) +
        teamautobotscontroller_B.FilterCoefficient;

      // DeadZone: '<S39>/DeadZone'
      if (teamautobotscontroller_B.Merge >
          teamautobotscontroller_P.Car_Follower_PID_UpperSaturatio) {
        // Gain: '<S43>/Integral Gain'
        teamautobotscontroller_B.Switch = teamautobotscontroller_B.Merge -
          teamautobotscontroller_P.Car_Follower_PID_UpperSaturatio;
      } else if (teamautobotscontroller_B.Merge >=
                 teamautobotscontroller_P.Car_Follower_PID_LowerSaturatio) {
        // Gain: '<S43>/Integral Gain'
        teamautobotscontroller_B.Switch = 0.0;
      } else {
        // Gain: '<S43>/Integral Gain'
        teamautobotscontroller_B.Switch = teamautobotscontroller_B.Merge -
          teamautobotscontroller_P.Car_Follower_PID_LowerSaturatio;
      }

      // End of DeadZone: '<S39>/DeadZone'

      // RelationalOperator: '<S37>/NotEqual' incorporates:
      //   Gain: '<S37>/ZeroGain'

      rtb_NotEqual_d = (teamautobotscontroller_P.ZeroGain_Gain_l *
                        teamautobotscontroller_B.Merge !=
                        teamautobotscontroller_B.Switch);

      // Signum: '<S37>/SignPreSat'
      if (rtIsNaN(teamautobotscontroller_B.Switch)) {
        // DataTypeConversion: '<S37>/DataTypeConv1'
        tmp_1 = (rtNaN);
      } else if (teamautobotscontroller_B.Switch < 0.0) {
        // DataTypeConversion: '<S37>/DataTypeConv1'
        tmp_1 = -1.0;
      } else {
        // DataTypeConversion: '<S37>/DataTypeConv1'
        tmp_1 = (teamautobotscontroller_B.Switch > 0.0);
      }

      // End of Signum: '<S37>/SignPreSat'

      // DataTypeConversion: '<S37>/DataTypeConv1'
      if (rtIsNaN(tmp_1)) {
        tmp_0 = 0;
      } else {
        tmp_0 = static_cast<int32_T>(fmod(tmp_1, 256.0));
      }

      // Gain: '<S43>/Integral Gain'
      teamautobotscontroller_B.Switch =
        teamautobotscontroller_P.Car_Follower_PID_I *
        teamautobotscontroller_B.error;

      // Signum: '<S37>/SignPreIntegrator'
      if (rtIsNaN(teamautobotscontroller_B.Switch)) {
        // DataTypeConversion: '<S37>/DataTypeConv2'
        tmp_1 = (rtNaN);
      } else if (teamautobotscontroller_B.Switch < 0.0) {
        // DataTypeConversion: '<S37>/DataTypeConv2'
        tmp_1 = -1.0;
      } else {
        // DataTypeConversion: '<S37>/DataTypeConv2'
        tmp_1 = (teamautobotscontroller_B.Switch > 0.0);
      }

      // End of Signum: '<S37>/SignPreIntegrator'

      // DataTypeConversion: '<S37>/DataTypeConv2'
      if (rtIsNaN(tmp_1)) {
        tmp = 0;
      } else {
        tmp = static_cast<int32_T>(fmod(tmp_1, 256.0));
      }

      // Logic: '<S37>/AND3' incorporates:
      //   DataTypeConversion: '<S37>/DataTypeConv1'
      //   DataTypeConversion: '<S37>/DataTypeConv2'
      //   RelationalOperator: '<S37>/Equal1'

      teamautobotscontroller_B.AND3 = (rtb_NotEqual_d && (static_cast<int8_T>
        (tmp_0 < 0 ? static_cast<int32_T>(static_cast<int8_T>
        (-static_cast<int8_T>(static_cast<uint8_T>(-static_cast<real_T>(tmp_0)))))
         : tmp_0) == (tmp < 0 ? static_cast<int32_T>(static_cast<int8_T>(-
        static_cast<int8_T>(static_cast<uint8_T>(-static_cast<real_T>(tmp))))) :
                      tmp)));
      if (rtmIsMajorTimeStep(teamautobotscontroller_M)) {
        // Memory: '<S37>/Memory'
        teamautobotscontroller_B.Memory =
          teamautobotscontroller_DW.Memory_PreviousInput;
      }

      // Switch: '<S37>/Switch'
      if (teamautobotscontroller_B.Memory) {
        // Gain: '<S43>/Integral Gain' incorporates:
        //   Constant: '<S37>/Constant1'
        //   Switch: '<S37>/Switch'

        teamautobotscontroller_B.Switch =
          teamautobotscontroller_P.Constant1_Value_h;
      }

      // End of Switch: '<S37>/Switch'

      // Saturate: '<S53>/Saturation'
      if (teamautobotscontroller_B.Merge >
          teamautobotscontroller_P.Car_Follower_PID_UpperSaturatio) {
        // Sum: '<S106>/Sum' incorporates:
        //   Merge: '<S1>/Merge'

        teamautobotscontroller_B.Merge =
          teamautobotscontroller_P.Car_Follower_PID_UpperSaturatio;
      } else if (teamautobotscontroller_B.Merge <
                 teamautobotscontroller_P.Car_Follower_PID_LowerSaturatio) {
        // Sum: '<S106>/Sum' incorporates:
        //   Merge: '<S1>/Merge'

        teamautobotscontroller_B.Merge =
          teamautobotscontroller_P.Car_Follower_PID_LowerSaturatio;
      }

      // End of Saturate: '<S53>/Saturation'
      // End of Outputs for SubSystem: '<S1>/Switch Case: Car Follower Mode'
    }
    break;
  }

  // End of If: '<S1>/If'
  if (rtmIsMajorTimeStep(teamautobotscontroller_M)) {
    // If: '<S1>/Abide By Speed Limit' incorporates:
    //   Constant: '<Root>/Speed Limit'

    if (rtsiIsModeUpdateTimeStep(&teamautobotscontroller_M->solverInfo)) {
      teamautobotscontroller_DW.AbideBySpeedLimit_ActiveSubsyst =
        static_cast<int8_T>(!(rtb_Data >=
        teamautobotscontroller_P.SpeedLimit_Value));
    }

    switch (teamautobotscontroller_DW.AbideBySpeedLimit_ActiveSubsyst) {
     case 0:
      // Outputs for IfAction SubSystem: '<S1>/Stop_Acceleratiing' incorporates:
      //   ActionPort: '<S9>/Action Port'

      // SignalConversion generated from: '<S9>/Out1' incorporates:
      //   Constant: '<S9>/Constant'

      rtb_Merge2 = teamautobotscontroller_P.Constant_Value_l;

      // End of Outputs for SubSystem: '<S1>/Stop_Acceleratiing'
      break;

     case 1:
      // Outputs for IfAction SubSystem: '<S1>/Pass As Normal' incorporates:
      //   ActionPort: '<S8>/Action Port'

      // SignalConversion generated from: '<S8>/V1'
      rtb_Merge2 = teamautobotscontroller_B.Merge;

      // End of Outputs for SubSystem: '<S1>/Pass As Normal'
      break;
    }

    // End of If: '<S1>/Abide By Speed Limit'

    // BusAssignment: '<Root>/Bus Assignment'
    rtb_BusAssignment.Data = rtb_Merge2;

    // Outputs for Atomic SubSystem: '<Root>/Publish'
    // MATLABSystem: '<S3>/SinkBlock'
    Pub_teamautobotscontroller_37.publish(&rtb_BusAssignment);

    // End of Outputs for SubSystem: '<Root>/Publish'
  }

  if (rtmIsMajorTimeStep(teamautobotscontroller_M)) {
    // Update for If: '<S1>/If'
    switch (teamautobotscontroller_DW.If_ActiveSubsystem) {
     case 0:
      // Update for IfAction SubSystem: '<S1>/Switch Case: Car Hunter Mode' incorporates:
      //   ActionPort: '<S11>/Action Port'

      if (rtmIsMajorTimeStep(teamautobotscontroller_M)) {
        // Update for Memory: '<S88>/Memory'
        teamautobotscontroller_DW.Memory_PreviousInput_g =
          teamautobotscontroller_B.AND3_g;
      }

      // End of Update for SubSystem: '<S1>/Switch Case: Car Hunter Mode'
      break;

     case 1:
      // Update for IfAction SubSystem: '<S1>/Switch Case: Car Follower Mode' incorporates:
      //   ActionPort: '<S10>/Action Port'

      if (rtmIsMajorTimeStep(teamautobotscontroller_M)) {
        // Update for Memory: '<S37>/Memory'
        teamautobotscontroller_DW.Memory_PreviousInput =
          teamautobotscontroller_B.AND3;
      }

      // End of Update for SubSystem: '<S1>/Switch Case: Car Follower Mode'
      break;
    }

    // End of Update for If: '<S1>/If'
  }                                    // end MajorTimeStep

  if (rtmIsMajorTimeStep(teamautobotscontroller_M)) {
    rt_ertODEUpdateContinuousStates(&teamautobotscontroller_M->solverInfo);

    // Update absolute time for base rate
    // The "clockTick0" counts the number of times the code of this task has
    //  been executed. The absolute time is the multiplication of "clockTick0"
    //  and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
    //  overflow during the application lifespan selected.

    ++teamautobotscontroller_M->Timing.clockTick0;
    teamautobotscontroller_M->Timing.t[0] = rtsiGetSolverStopTime
      (&teamautobotscontroller_M->solverInfo);

    {
      // Update absolute timer for sample time: [0.2s, 0.0s]
      // The "clockTick1" counts the number of times the code of this task has
      //  been executed. The resolution of this integer timer is 0.2, which is the step size
      //  of the task. Size of "clockTick1" ensures timer will not overflow during the
      //  application lifespan selected.

      teamautobotscontroller_M->Timing.clockTick1++;
    }
  }                                    // end MajorTimeStep
}

// Derivatives for root system: '<Root>'
void teamautobotscontroller_derivatives(void)
{
  XDot_teamautobotscontroller_T *_rtXdot;
  _rtXdot = ((XDot_teamautobotscontroller_T *) teamautobotscontroller_M->derivs);

  // Derivatives for If: '<S1>/If'
  {
    real_T *dx;
    int_T i;
    dx = &(((XDot_teamautobotscontroller_T *) teamautobotscontroller_M->derivs
           )->Integrator_CSTATE_e);
    for (i=0; i < 2; i++) {
      dx[i] = 0.0;
    }
  }

  {
    real_T *dx;
    int_T i;
    dx = &(((XDot_teamautobotscontroller_T *) teamautobotscontroller_M->derivs
           )->Integrator_CSTATE);
    for (i=0; i < 2; i++) {
      dx[i] = 0.0;
    }
  }

  switch (teamautobotscontroller_DW.If_ActiveSubsystem) {
   case 0:
    // Derivatives for IfAction SubSystem: '<S1>/Switch Case: Car Hunter Mode' incorporates:
    //   ActionPort: '<S11>/Action Port'

    // Derivatives for Integrator: '<S97>/Integrator'
    _rtXdot->Integrator_CSTATE_e = teamautobotscontroller_B.Switch_k;

    // Derivatives for Integrator: '<S92>/Filter'
    _rtXdot->Filter_CSTATE_f = teamautobotscontroller_B.FilterCoefficient_b;

    // End of Derivatives for SubSystem: '<S1>/Switch Case: Car Hunter Mode'
    break;

   case 1:
    // Derivatives for IfAction SubSystem: '<S1>/Switch Case: Car Follower Mode' incorporates:
    //   ActionPort: '<S10>/Action Port'

    // Derivatives for Integrator: '<S46>/Integrator'
    _rtXdot->Integrator_CSTATE = teamautobotscontroller_B.Switch;

    // Derivatives for Integrator: '<S41>/Filter'
    _rtXdot->Filter_CSTATE = teamautobotscontroller_B.FilterCoefficient;

    // End of Derivatives for SubSystem: '<S1>/Switch Case: Car Follower Mode'
    break;
  }

  // End of Derivatives for If: '<S1>/If'
}

// Model initialize function
void teamautobotscontroller_initialize(void)
{
  // Registration code

  // initialize non-finites
  rt_InitInfAndNaN(sizeof(real_T));

  {
    // Setup solver object
    rtsiSetSimTimeStepPtr(&teamautobotscontroller_M->solverInfo,
                          &teamautobotscontroller_M->Timing.simTimeStep);
    rtsiSetTPtr(&teamautobotscontroller_M->solverInfo, &rtmGetTPtr
                (teamautobotscontroller_M));
    rtsiSetStepSizePtr(&teamautobotscontroller_M->solverInfo,
                       &teamautobotscontroller_M->Timing.stepSize0);
    rtsiSetdXPtr(&teamautobotscontroller_M->solverInfo,
                 &teamautobotscontroller_M->derivs);
    rtsiSetContStatesPtr(&teamautobotscontroller_M->solverInfo, (real_T **)
                         &teamautobotscontroller_M->contStates);
    rtsiSetNumContStatesPtr(&teamautobotscontroller_M->solverInfo,
      &teamautobotscontroller_M->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&teamautobotscontroller_M->solverInfo,
      &teamautobotscontroller_M->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&teamautobotscontroller_M->solverInfo,
      &teamautobotscontroller_M->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&teamautobotscontroller_M->solverInfo,
      &teamautobotscontroller_M->periodicContStateRanges);
    rtsiSetErrorStatusPtr(&teamautobotscontroller_M->solverInfo,
                          (&rtmGetErrorStatus(teamautobotscontroller_M)));
    rtsiSetRTModelPtr(&teamautobotscontroller_M->solverInfo,
                      teamautobotscontroller_M);
  }

  rtsiSetSimTimeStep(&teamautobotscontroller_M->solverInfo, MAJOR_TIME_STEP);
  teamautobotscontroller_M->intgData.y = teamautobotscontroller_M->odeY;
  teamautobotscontroller_M->intgData.f[0] = teamautobotscontroller_M->odeF[0];
  teamautobotscontroller_M->intgData.f[1] = teamautobotscontroller_M->odeF[1];
  teamautobotscontroller_M->intgData.f[2] = teamautobotscontroller_M->odeF[2];
  teamautobotscontroller_M->contStates = ((X_teamautobotscontroller_T *)
    &teamautobotscontroller_X);
  rtsiSetSolverData(&teamautobotscontroller_M->solverInfo, static_cast<void *>
                    (&teamautobotscontroller_M->intgData));
  rtsiSetIsMinorTimeStepWithModeChange(&teamautobotscontroller_M->solverInfo,
    false);
  rtsiSetSolverName(&teamautobotscontroller_M->solverInfo,"ode3");
  rtmSetTPtr(teamautobotscontroller_M, &teamautobotscontroller_M->Timing.tArray
             [0]);
  teamautobotscontroller_M->Timing.stepSize0 = 0.2;

  {
    char_T b_zeroDelimTopic[17];
    char_T b_zeroDelimTopic_0[11];
    char_T b_zeroDelimTopic_1[10];
    static const char_T tmp[16] = { '/', 'c', 'a', 'r', '/', 's', 't', 'a', 't',
      'e', '/', 'v', 'e', 'l', '_', 'x' };

    static const char_T tmp_0[10] = { '/', 'l', 'e', 'a', 'd', '_', 'd', 'i',
      's', 't' };

    static const char_T tmp_1[9] = { 'c', 'm', 'd', '_', 'a', 'c', 'c', 'e', 'l'
    };

    // Start for If: '<S1>/If1'
    teamautobotscontroller_DW.If1_ActiveSubsystem = -1;

    // Start for If: '<S1>/If'
    teamautobotscontroller_DW.If_ActiveSubsystem = -1;

    // Start for If: '<S1>/Abide By Speed Limit'
    teamautobotscontroller_DW.AbideBySpeedLimit_ActiveSubsyst = -1;

    // SystemInitialize for Atomic SubSystem: '<Root>/Subscribe'
    // SystemInitialize for Enabled SubSystem: '<S4>/Enabled Subsystem'
    // SystemInitialize for SignalConversion generated from: '<S114>/In1' incorporates:
    //   Outport: '<S114>/Out1'

    teamautobotscontroller_B.In1_b = teamautobotscontroller_P.Out1_Y0;

    // End of SystemInitialize for SubSystem: '<S4>/Enabled Subsystem'

    // Start for MATLABSystem: '<S4>/SourceBlock'
    teamautobotscontroller_DW.obj_g.matlabCodegenIsDeleted = false;
    teamautobotscontroller_DW.obj_g.isInitialized = 1;
    for (int32_T i = 0; i < 16; i++) {
      b_zeroDelimTopic[i] = tmp[i];
    }

    b_zeroDelimTopic[16] = '\x00';
    Sub_teamautobotscontroller_36.createSubscriber(&b_zeroDelimTopic[0], 1);
    teamautobotscontroller_DW.obj_g.isSetupComplete = true;

    // End of Start for MATLABSystem: '<S4>/SourceBlock'
    // End of SystemInitialize for SubSystem: '<Root>/Subscribe'

    // SystemInitialize for Atomic SubSystem: '<Root>/Subscribe1'
    // SystemInitialize for Enabled SubSystem: '<S5>/Enabled Subsystem'
    // SystemInitialize for SignalConversion generated from: '<S115>/In1' incorporates:
    //   Outport: '<S115>/Out1'

    teamautobotscontroller_B.In1 = teamautobotscontroller_P.Out1_Y0_d;

    // End of SystemInitialize for SubSystem: '<S5>/Enabled Subsystem'

    // Start for MATLABSystem: '<S5>/SourceBlock'
    teamautobotscontroller_DW.obj_j.matlabCodegenIsDeleted = false;
    teamautobotscontroller_DW.obj_j.isInitialized = 1;
    for (int32_T i = 0; i < 10; i++) {
      b_zeroDelimTopic_0[i] = tmp_0[i];
    }

    b_zeroDelimTopic_0[10] = '\x00';
    Sub_teamautobotscontroller_48.createSubscriber(&b_zeroDelimTopic_0[0], 1);
    teamautobotscontroller_DW.obj_j.isSetupComplete = true;

    // End of Start for MATLABSystem: '<S5>/SourceBlock'
    // End of SystemInitialize for SubSystem: '<Root>/Subscribe1'

    // SystemInitialize for IfAction SubSystem: '<S1>/Switch Case: Car Hunter Mode' 
    // InitializeConditions for Integrator: '<S97>/Integrator'
    teamautobotscontroller_X.Integrator_CSTATE_e =
      teamautobotscontroller_P.Car_Hunter_PID_InitialConditi_c;

    // InitializeConditions for Integrator: '<S92>/Filter'
    teamautobotscontroller_X.Filter_CSTATE_f =
      teamautobotscontroller_P.Car_Hunter_PID_InitialCondition;

    // InitializeConditions for Memory: '<S88>/Memory'
    teamautobotscontroller_DW.Memory_PreviousInput_g =
      teamautobotscontroller_P.Memory_InitialCondition;

    // End of SystemInitialize for SubSystem: '<S1>/Switch Case: Car Hunter Mode' 

    // SystemInitialize for IfAction SubSystem: '<S1>/Switch Case: Car Follower Mode' 
    // InitializeConditions for Integrator: '<S46>/Integrator'
    teamautobotscontroller_X.Integrator_CSTATE =
      teamautobotscontroller_P.Car_Follower_PID_InitialCondi_d;

    // InitializeConditions for Integrator: '<S41>/Filter'
    teamautobotscontroller_X.Filter_CSTATE =
      teamautobotscontroller_P.Car_Follower_PID_InitialConditi;

    // InitializeConditions for Memory: '<S37>/Memory'
    teamautobotscontroller_DW.Memory_PreviousInput =
      teamautobotscontroller_P.Memory_InitialCondition_d;

    // End of SystemInitialize for SubSystem: '<S1>/Switch Case: Car Follower Mode' 

    // SystemInitialize for Atomic SubSystem: '<Root>/Publish'
    // Start for MATLABSystem: '<S3>/SinkBlock'
    teamautobotscontroller_DW.obj.matlabCodegenIsDeleted = false;
    teamautobotscontroller_DW.obj.isInitialized = 1;
    for (int32_T i = 0; i < 9; i++) {
      b_zeroDelimTopic_1[i] = tmp_1[i];
    }

    b_zeroDelimTopic_1[9] = '\x00';
    Pub_teamautobotscontroller_37.createPublisher(&b_zeroDelimTopic_1[0], 1);
    teamautobotscontroller_DW.obj.isSetupComplete = true;

    // End of Start for MATLABSystem: '<S3>/SinkBlock'
    // End of SystemInitialize for SubSystem: '<Root>/Publish'
  }
}

// Model terminate function
void teamautobotscontroller_terminate(void)
{
  // Terminate for Atomic SubSystem: '<Root>/Subscribe'
  // Terminate for MATLABSystem: '<S4>/SourceBlock'
  if (!teamautobotscontroller_DW.obj_g.matlabCodegenIsDeleted) {
    teamautobotscontroller_DW.obj_g.matlabCodegenIsDeleted = true;
  }

  // End of Terminate for MATLABSystem: '<S4>/SourceBlock'
  // End of Terminate for SubSystem: '<Root>/Subscribe'

  // Terminate for Atomic SubSystem: '<Root>/Subscribe1'
  // Terminate for MATLABSystem: '<S5>/SourceBlock'
  if (!teamautobotscontroller_DW.obj_j.matlabCodegenIsDeleted) {
    teamautobotscontroller_DW.obj_j.matlabCodegenIsDeleted = true;
  }

  // End of Terminate for MATLABSystem: '<S5>/SourceBlock'
  // End of Terminate for SubSystem: '<Root>/Subscribe1'

  // Terminate for Atomic SubSystem: '<Root>/Publish'
  // Terminate for MATLABSystem: '<S3>/SinkBlock'
  if (!teamautobotscontroller_DW.obj.matlabCodegenIsDeleted) {
    teamautobotscontroller_DW.obj.matlabCodegenIsDeleted = true;
  }

  // End of Terminate for MATLABSystem: '<S3>/SinkBlock'
  // End of Terminate for SubSystem: '<Root>/Publish'
}

//
// File trailer for generated code.
//
// [EOF]
//
