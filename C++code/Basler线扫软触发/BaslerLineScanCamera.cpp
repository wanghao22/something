#include "stdafx.h"
#include "BaslerLineScanCamera.h"
#include "baslerLineScanTest.h"
#include "baslerLineScanTestDlg.h"

using namespace cv;
using namespace Pylon;
using namespace GenApi;
using namespace Basler_GigECameraParams;

BaslerLineScanCamera::BaslerLineScanCamera()
{
}

BaslerLineScanCamera::~BaslerLineScanCamera()
{
	
}

CHeartbeatHelper::CHeartbeatHelper(CInstantCamera& camera)
	: m_pHeartbeatTimeout(NULL)
{
	// m_pHeartbeatTimeout may be NULL
	m_pHeartbeatTimeout = camera.GetTLNodeMap().GetNode("HeartbeatTimeout");
}

bool CHeartbeatHelper::SetValue(int64_t NewValue)
{
	// Do nothing if no heartbeat feature is available.
	if (!m_pHeartbeatTimeout.IsValid())
		return false;

	// Apply the increment and cut off invalid values if neccessary.
	int64_t correctedValue = NewValue - (NewValue % m_pHeartbeatTimeout->GetInc());

	m_pHeartbeatTimeout->SetValue(correctedValue);
	return true;
}

bool CHeartbeatHelper::SetMax()
{
	// Do nothing if no heartbeat feature is available.
	if (!m_pHeartbeatTimeout.IsValid())
		return false;

	int64_t maxVal = m_pHeartbeatTimeout->GetMax();
	return SetValue(maxVal);
}

void BaslerLineScanCamera::openCamera()
{
	try
	{
		CDeviceInfo di;
		di.SetSerialNumber("22159207");
		di.SetDeviceClass(BaslerGigEDeviceClass);
		m_Camera.Attach(CTlFactory::GetInstance().CreateDevice(di));
		m_Camera.RegisterConfiguration(new CSoftwareTriggerConfiguration, RegistrationMode_ReplaceAll, Cleanup_Delete);

		CHeartbeatHelper heartbeatHelper(m_Camera);
		heartbeatHelper.SetValue(30000);

		m_Camera.Open();

		//下载参数设置
		m_Camera.UserSetSelector.SetValue(UserSetSelector_UserSet1);
		m_Camera.UserSetLoad.Execute();

		//启动捕获
		m_Camera.StartGrabbing(INFINITE, GrabStrategy_LatestImageOnly, GrabLoop_ProvidedByUser);

	}
	catch (const GenericException &e)
	{
		AfxMessageBox(CString(e.GetDescription()));
	}
}

bool BaslerLineScanCamera::TriggerCameraAndGrabImage(CBaslerGigEInstantCamera& cameraObject, 
	CGrabResultPtr& ptrGrabResult, Mat& srcImg)
{
	try
	{
		if (cameraObject.CanWaitForFrameTriggerReady())
		{
			// Execute the software trigger. Wait up to 500 ms for the camera to be ready for trigger.
			if (cameraObject.WaitForFrameTriggerReady(5000, TimeoutHandling_ThrowException))
			{
				cameraObject.ExecuteSoftwareTrigger();
				cameraObject.RetrieveResult(5000, ptrGrabResult, TimeoutHandling_ThrowException);
				if (ptrGrabResult->GrabSucceeded())
				{
					memcpy((unsigned char*)srcImg.datastart, (uint8_t *)ptrGrabResult->GetBuffer(), ptrGrabResult->GetImageSize());
				}
				else
				{
					return false;
				}
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}
	catch (const GenericException &e)
	{
		AfxMessageBox(CString(e.GetDescription()));
		return false;
	}
	return true;
}

void BaslerLineScanCamera::closeCamera()
{
	m_Camera.DestroyDevice();
}