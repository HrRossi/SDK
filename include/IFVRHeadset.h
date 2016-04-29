#pragma once

#ifndef _IFVRHEADSET_H
#define _IFVRHEADSET_H

#include "FoveTypes.h"

namespace Fove
{
	class IFVRHeadset
	{
	public:
		// members
		// General
		virtual bool Initialise() = 0;
		// hardware connected
		virtual bool IsHardwareConnected() = 0;
		// the hardware for their requested capabilities started
		virtual bool IsHardwareReady() = 0;
		virtual bool IsHeadsetMounted() = 0;
		virtual float GetVersion() = 0;
		virtual Fove::EFVR_ErrorCode GetLastError() = 0;
		
		// eye tracking
		virtual Fove::SFVR_GazeScreenCoord GetGazePoint() = 0;
		// start and stop the subsystem
		virtual bool DisableEyeTracking() = 0;
		virtual bool EnableEyeTracking() = 0;
		// temp
		virtual Fove::SFVR_EyeImage GetFrameData() = 0;
		// status
		virtual bool IsEyeTracking() = 0;
		virtual bool IsEyeTrackingReady() = 0;
		virtual bool IsCalibrated() = 0;

		// motion sensor
		virtual bool IsMotionReady() = 0;
		virtual Fove::SFVR_HeadOrientation GetOrientation() = 0;
		virtual bool TareOrientationSensor() = 0;

		// position tracking
		virtual bool IsPositionReady() = 0;
		virtual Fove::SFVR_Pose GetPosition() = 0;
		virtual bool TarePositionSensors() = 0;

		// metrics
		virtual SFVR_Matrix44 GetProjectionMatrixLH(EFVR_Eye whichEye, float zNear, float zFar) = 0;
		virtual SFVR_Matrix44 GetProjectionMatrixRH(EFVR_Eye whichEye, float zNear, float zFar) = 0;
		//! Returns values at 1 unit away. Please convert yourself by multiplying by zNear.
		virtual void AssignRawProjectionValues(EFVR_Eye whichEye, float *l, float *r, float *t, float *b) = 0;
		virtual SFVR_Matrix44 GetEyeToHeadMatrix(EFVR_Eye whichEye) = 0;

		// calibration
		virtual void StartCalibration() = 0;
		virtual SFVR_CalibrationTarget TickCalibration(float deltaTime) = 0;

		// constructor & destructor
		virtual ~IFVRHeadset();
		virtual void Destroy() = 0;
	};

	inline IFVRHeadset::~IFVRHeadset() { }

	__declspec (dllexport) IFVRHeadset* GetFVRHeadset();
}
#endif // _IFVRHEADSET_H