#pragma once
#ifndef _BASLER_LINESCAN_CAMERA_H
#define _BASLER_LINESCAN_CAMERA_H

#include "stdafx.h"
#include "opencv2\core\core.hpp"
#include "opencv2\core\core.hpp"
#include <pylon/PylonIncludes.h>
#include <pylon/gige/PylonGigEIncludes.h>
#include <pylon/PylonGUI.h>

class CHeartbeatHelper
{
public:
	explicit CHeartbeatHelper(Pylon::CInstantCamera& camera);

	bool SetValue(int64_t NewValue);

	bool SetMax();

protected:
	GenApi::CIntegerPtr m_pHeartbeatTimeout; // Pointer to the node, will be NULL if no node exists.
};

class BaslerLineScanCamera
{
public:
	BaslerLineScanCamera();
	~BaslerLineScanCamera();
	Pylon::CBaslerGigEInstantCamera m_Camera;
	void openCamera();
	bool TriggerCameraAndGrabImage(Pylon::CBaslerGigEInstantCamera& cameraObject, 
		Pylon::CGrabResultPtr& ptrGrabResult, cv::Mat& srcImg);
	void closeCamera();
};

#endif
