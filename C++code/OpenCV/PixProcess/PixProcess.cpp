#include "stdafx.h"
#include "PixProcess.h"

using namespace std;
using namespace cv;

cv::Mat M00 = (cv::Mat_<double>(7, 7) <<
	0, 0.0287, 0.0686, 0.0807, 0.0686, 0.0287, 0,
	0.0287, 0.0815, 0.0816, 0.0816, 0.0816, 0.0815, 0.0287,
	0.0686, 0.0816, 0.0816, 0.0816, 0.0816, 0.0816, 0.0686,
	0.0807, 0.0816, 0.0816, 0.0816, 0.0816, 0.0816, 0.0807,
	0.0686, 0.0816, 0.0816, 0.0816, 0.0816, 0.0816, 0.0686,
	0.0287, 0.0815, 0.0816, 0.0816, 0.0816, 0.0815, 0.0287,
	0, 0.0287, 0.0686, 0.0807, 0.0686, 0.0287, 0);

cv::Mat M11R = (cv::Mat_<double>(7, 7) <<
	0, -0.015, -0.019, 0, 0.019, 0.015, 0,
	-0.0224, -0.0466, -0.0233, 0, 0.0233, 0.0466, 0.0224,
	-0.0573, -0.0466, -0.0233, 0, 0.0233, 0.0466, 0.0573,
	-0.069, -0.0466, -0.0233, 0, 0.0233, 0.0466, 0.069,
	-0.0573, -0.0466, -0.0233, 0, 0.0233, 0.0466, 0.0573,
	-0.0224, -0.0466, -0.0233, 0, 0.0233, 0.0466, 0.0224,
	0, -0.015, -0.019, 0, 0.019, 0.015, 0);

cv::Mat M11I = (cv::Mat_<double>(7, 7) <<
	0, -0.0224, -0.0573, -0.069, -0.0573, -0.0224, 0,
	-0.015, -0.0466, -0.0466, -0.0466, -0.0466, -0.0466, -0.015,
	-0.019, -0.0233, -0.0233, -0.0233, -0.0233, -0.0233, -0.019,
	0, 0, 0, 0, 0, 0, 0,
	0.019, 0.0233, 0.0233, 0.0233, 0.0233, 0.0233, 0.019,
	0.015, 0.0466, 0.0466, 0.0466, 0.0466, 0.0466, 0.015,
	0, 0.0224, 0.0573, 0.069, 0.0573, 0.0224, 0);

cv::Mat M20 = (cv::Mat_<double>(7, 7) <<
	0, 0.0225, 0.0394, 0.0396, 0.0394, 0.0225, 0,
	0.0225, 0.0271, -0.0128, -0.0261, -0.0128, 0.0271, 0.0225,
	0.0394, -0.0128, -0.0528, -0.0661, -0.0528, -0.0128, 0.0394,
	0.0396, -0.0261, -0.0661, -0.0794, -0.0661, -0.0261, 0.0396,
	0.0394, -0.0128, -0.0528, -0.0661, -0.0528, -0.0128, 0.0394,
	0.0225, 0.0271, -0.0128, -0.0261, -0.0128, 0.0271, 0.0225,
	0, 0.0225, 0.0394, 0.0396, 0.0394, 0.0225, 0);

cv::Mat M31R = (cv::Mat_<double>(7, 7) <<
	0, -0.0103, -0.0073, 0, 0.0073, 0.0103, 0,
	-0.0153, -0.0018, 0.0162, 0, -0.0162, 0.0018, 0.0153,
	-0.0223, 0.0324, 0.0333, 0, -0.0333, -0.0324, 0.0223,
	-0.0190, 0.0438, 0.0390, 0, -0.0390, -0.0438, 0.0190,
	-0.0223, 0.0324, 0.0333, 0, -0.0333, -0.0324, 0.0223,
	-0.0153, -0.0018, 0.0162, 0, -0.0162, 0.0018, 0.0153,
	0, -0.0103, -0.0073, 0, 0.0073, 0.0103, 0);

cv::Mat M31I = (cv::Mat_<double>(7, 7) <<
	0, -0.0153, -0.0223, -0.019, -0.0223, -0.0153, 0,
	-0.0103, -0.0018, 0.0324, 0.0438, 0.0324, -0.0018, -0.0103,
	-0.0073, 0.0162, 0.0333, 0.039, 0.0333, 0.0162, -0.0073,
	0, 0, 0, 0, 0, 0, 0,
	0.0073, -0.0162, -0.0333, -0.039, -0.0333, -0.0162, 0.0073,
	0.0103, 0.0018, -0.0324, -0.0438, -0.0324, 0.0018, 0.0103,
	0, 0.0153, 0.0223, 0.0190, 0.0223, 0.0153, 0);

cv::Mat M40 = (cv::Mat_<double>(7, 7) <<
	0, 0.013, 0.0056, -0.0018, 0.0056, 0.013, 0,
	0.0130, -0.0186, -0.0323, -0.0239, -0.0323, -0.0186, 0.0130,
	0.0056, -0.0323, 0.0125, 0.0406, 0.0125, -0.0323, 0.0056,
	-0.0018, -0.0239, 0.0406, 0.0751, 0.0406, -0.0239, -0.0018,
	0.0056, -0.0323, 0.0125, 0.0406, 0.0125, -0.0323, 0.0056,
	0.0130, -0.0186, -0.0323, -0.0239, -0.0323, -0.0186, 0.0130,
	0, 0.013, 0.0056, -0.0018, 0.0056, 0.013, 0);

PixProcess::PixProcess()
{
}

PixProcess::~PixProcess()
{
}

bool __stdcall PixProcess::Excute(cv::Mat src, cv::Mat &dst, int option)
{
	switch (option)
	{
	case(THRESHOLD_PROCESS) :
		if (ThresholdPro(src, dst) != 0)
		{
			return false;
		}
		return true;
	case(INVERSE_PROCESS) :
		bitwise_not(src, dst);
		return true;
	case(CANNY_PROCESS) :
		if (CannyProcess(src, dst) != 0)
		{
			return false;
		}
		return true;
	case(SOBEL_PROCESS) :
		if (SobelProcess(src, dst) != 0)
		{
			return false;
		}
		return true;
	case(LAPLACE_PROCESS) :
		if (LaplaceProcess(src, dst) != 0)
		{
			return false;
		}
		return true;
	case(SUB_PIX_PROCESS) :
		if (SubPixProcess(src, dst) != 0)
		{
			return false;
		}
		return true;
	case(DIVISION_BY_HSV) :
		if (DivisionByHSV(src, dst) != 0)
		{
			return false;
		}
		return true;
	case(DIVISION_BY_RGB) :
		if (DivisionByRGB(src, dst) != 0)
		{
			return false;
		}
		return true;
	case(DIVISION_BY_GRAY) :
		if (DivisionByGray(src, dst) != 0)
		{
			return false;
		}
		return true;
	default:
		return false;
	}
}

int __stdcall PixProcess::Excute_(cv::Mat src, cv::Mat &dst, int option)
{
	switch (option)
	{
	case(THRESHOLD_PROCESS) :
		return ThresholdPro(src, dst);
	case(INVERSE_PROCESS) :
		bitwise_not(src, dst);
		return 0;
	case(CANNY_PROCESS) :
		return CannyProcess(src, dst);
	case(SOBEL_PROCESS) :
		return SobelProcess(src, dst);
	case(LAPLACE_PROCESS) :
		return LaplaceProcess(src, dst);
	case(SUB_PIX_PROCESS) :
		return SubPixProcess(src, dst);
	case(DIVISION_BY_HSV) :
		return DivisionByHSV(src, dst);
	case(DIVISION_BY_RGB) :
		return DivisionByRGB(src, dst);
	case(DIVISION_BY_GRAY) :
		return DivisionByGray(src, dst);
	default:
		return false;
	}
}

int __stdcall PixProcess::SaveXML()
{
	FileStorage fs(_PIX_PROCESS_XML_, FileStorage::WRITE);
	if (!fs.isOpened())
	{
		return _OPEN_XML_ERROR_;
	}
	//ThresholdProcess
	fs << "ThresholdProcess" << "{" << "name" << "ThresholdProcess" << "type" << 2 << "suntype" << THRESHOLD_PROCESS;
	fs << "Threshold_Thre" << m_Threshold_Thre;
	fs << "Threshold_Mode" << m_Threshold_Mode << "}";
	//InverseProcess
	fs << "InverseProcess" << "{" << "name" << "InverseProcess" << "type" << 2 << "suntype" << INVERSE_PROCESS << "}";
	//CannyProcess
	fs << "CannyProcess" << "{" << "name" << "CannyProcess" << "type" << 2 << "suntype" << CANNY_PROCESS;
	fs << "Canny_BlurSize" << m_Canny_BlurSize;
	fs << "Canny_Ksize" << m_Canny_Ksize;
	fs << "Canny_Min" << m_Canny_Min;
	fs << "Canny_Max" << m_Canny_Max;
	fs << "Canny_Gradient" << m_Canny_Gradient << "}";
	//SobelProcess
	fs << "SobelProcess" << "{" << "name" << "SobelProcess" << "type" << 2 << "suntype" << SOBEL_PROCESS;
	fs << "Sobel_Depth" << m_SobelDepth;
	fs << "Sobel_Dx" << m_SobelDx;
	fs << "Sobel_Dy" << m_SobelDy;
	fs << "Sobel_Ksize" << m_SobelKsize;
	fs << "Sobel_Type" << m_SobelType;
	fs << "Sobel_Scale" << m_SobelScale;
	fs << "Sobel_Delta" << m_SobelDelta <<"}";
	//LaplaceProcess
	fs << "LaplaceProcess" << "{" << "name" << "LaplaceProcess" << "type" << 2 << "suntype" << LAPLACE_PROCESS;
	fs << "Laplace_Gusize" << m_LaplaceGusize;
	fs << "Laplace_Depth" << m_LaplaceDepth;
	fs << "Laplace_Ksize" << m_LaplaceKsize;
	fs << "Laplace_Type" << m_LaplaceType;
	fs << "Laplace_Scale" << m_LaplaceScale;
	fs << "Laplace_Delta" << m_LaplaceDelta << "}";
	//SubPixProcess
	fs << "SubPixProcess" << "{" << "name" << "SubPixProcess" << "type" << 2 << "suntype" << SUB_PIX_PROCESS;
	fs << "SubPix_Size" << m_SubPixSize;
	fs << "SubPix_AutoThreMode" << m_SubAutoThreMode;
	fs << "SubPix_AutoThreType" << m_SubAutoThreType;
	fs << "SubPix_AutoThreKsize" << m_SubAutoThreKsize;
	fs << "SubPix_C" << m_SubPixC;
	fs << "SubPix_Color_R" << m_SubPixColor.val[2];
	fs << "SubPix_Color_G" << m_SubPixColor.val[1];
	fs << "SubPix_Color_B" << m_SubPixColor.val[0] << "}";
	//DivisionByHSV
	fs << "DivisionByHSV" << "{" << "name" << "DivisionByHSV" << "type" << 2 << "suntype" << DIVISION_BY_HSV;
	fs << "H_min" << m_H_min;
	fs << "S_min" << m_S_min;
	fs << "V_min" << m_V_min;
	fs << "H_max" << m_H_max;
	fs << "S_max" << m_S_max;
	fs << "V_max" << m_V_max << "}";
	//DivisionByRGB
	fs << "DivisionByRGB" << "{" << "name" << "DivisionByRGB" << "type" << 2 << "suntype" << DIVISION_BY_RGB;
	fs << "R_min" << m_R_min;
	fs << "G_min" << m_G_min;
	fs << "B_min" << m_B_min;
	fs << "R_max" << m_R_max;
	fs << "G_max" << m_G_max;
	fs << "B_max" << m_B_max << "}";
	//DivisionByGray
	fs << "DivisionByGray" << "{" << "name" << "DivisionByGray" << "type" << 2 << "suntype" << DIVISION_BY_GRAY;
	fs << "Gray_Case" << m_Gray_Case;
	fs << "Gray_Min" << m_Gray_Min;
	fs << "Gray_Max" << m_Gray_Max << "}";
	fs.release();
	return 0;
}

int __stdcall PixProcess::SaveXML(char* filename)
{
	FileStorage fs(filename, FileStorage::WRITE);
	if (!fs.isOpened())
	{
		return _OPEN_XML_ERROR_;
	}
	//ThresholdProcess
	fs << "ThresholdProcess" << "{" << "name" << "ThresholdProcess" << "type" << 2 << "suntype" << THRESHOLD_PROCESS;
	fs << "Threshold_Thre" << m_Threshold_Thre;
	fs << "Threshold_Mode" << m_Threshold_Mode << "}";
	//InverseProcess
	fs << "InverseProcess" << "{" << "name" << "InverseProcess" << "type" << 2 << "suntype" << INVERSE_PROCESS << "}";
	//CannyProcess
	fs << "CannyProcess" << "{" << "name" << "CannyProcess" << "type" << 2 << "suntype" << CANNY_PROCESS;
	fs << "Canny_BlurSize" << m_Canny_BlurSize;
	fs << "Canny_Ksize" << m_Canny_Ksize;
	fs << "Canny_Min" << m_Canny_Min;
	fs << "Canny_Max" << m_Canny_Max;
	fs << "Canny_Gradient" << m_Canny_Gradient << "}";
	//SobelProcess
	fs << "SobelProcess" << "{" << "name" << "SobelProcess" << "type" << 2 << "suntype" << SOBEL_PROCESS;
	fs << "Sobel_Depth" << m_SobelDepth;
	fs << "Sobel_Dx" << m_SobelDx;
	fs << "Sobel_Dy" << m_SobelDy;
	fs << "Sobel_Ksize" << m_SobelKsize;
	fs << "Sobel_Type" << m_SobelType;
	fs << "Sobel_Scale" << m_SobelScale;
	fs << "Sobel_Delta" << m_SobelDelta << "}";
	//LaplaceProcess
	fs << "LaplaceProcess" << "{" << "name" << "LaplaceProcess" << "type" << 2 << "suntype" << LAPLACE_PROCESS;
	fs << "Laplace_Gusize" << m_LaplaceGusize;
	fs << "Laplace_Depth" << m_LaplaceDepth;
	fs << "Laplace_Ksize" << m_LaplaceKsize;
	fs << "Laplace_Type" << m_LaplaceType;
	fs << "Laplace_Scale" << m_LaplaceScale;
	fs << "Laplace_Delta" << m_LaplaceDelta << "}";
	//SubPixProcess
	fs << "SubPixProcess" << "{" << "name" << "SubPixProcess" << "type" << 2 << "suntype" << SUB_PIX_PROCESS;
	fs << "SubPix_Size" << m_SubPixSize;
	fs << "SubPix_AutoThreMode" << m_SubAutoThreMode;
	fs << "SubPix_AutoThreType" << m_SubAutoThreType;
	fs << "SubPix_AutoThreKsize" << m_SubAutoThreKsize;
	fs << "SubPix_C" << m_SubPixC;
	fs << "SubPix_Color_R" << m_SubPixColor.val[2];
	fs << "SubPix_Color_G" << m_SubPixColor.val[1];
	fs << "SubPix_Color_B" << m_SubPixColor.val[0] << "}";
	//DivisionByHSV
	fs << "DivisionByHSV" << "{" << "name" << "DivisionByHSV" << "type" << 2 << "suntype" << DIVISION_BY_HSV;
	fs << "H_min" << m_H_min;
	fs << "S_min" << m_S_min;
	fs << "V_min" << m_V_min;
	fs << "H_max" << m_H_max;
	fs << "S_max" << m_S_max;
	fs << "V_max" << m_V_max << "}";
	//DivisionByRGB
	fs << "DivisionByRGB" << "{" << "name" << "DivisionByRGB" << "type" << 2 << "suntype" << DIVISION_BY_RGB;
	fs << "R_min" << m_R_min;
	fs << "G_min" << m_G_min;
	fs << "B_min" << m_B_min;
	fs << "R_max" << m_R_max;
	fs << "G_max" << m_G_max;
	fs << "B_max" << m_B_max << "}";
	//DivisionByGray
	fs << "DivisionByGray" << "{" << "name" << "DivisionByGray" << "type" << 2 << "suntype" << DIVISION_BY_GRAY;
	fs << "Gray_Case" << m_Gray_Case;
	fs << "Gray_Min" << m_Gray_Min;
	fs << "Gray_Max" << m_Gray_Max << "}";
	fs.release();
	return 0;
}

int __stdcall PixProcess::LoadXML()
{
	FileStorage fs(_PIX_PROCESS_XML_, FileStorage::READ);
	if (!fs.isOpened())
	{
		return _OPEN_XML_ERROR_;
	}
	FileNode ThresholdNode = fs["ThresholdProcess"];
	m_Threshold_Thre = ThresholdNode["Threshold_Thre"];
	m_Threshold_Mode = ThresholdNode["Threshold_Mode"];
	FileNode CannyNode = fs["CannyProcess"];
	m_Canny_BlurSize = CannyNode["Canny_BlurSize"];
	m_Canny_Ksize = CannyNode["Canny_Ksize"];
	m_Canny_Min = CannyNode["Canny_Min"];
	m_Canny_Max = CannyNode["Canny_Max"];
	m_Canny_Gradient = (int)CannyNode["Canny_Gradient"];
	FileNode SobelNode = fs["SobelProcess"];
	m_SobelDepth = SobelNode["Sobel_Depth"];
	m_SobelDx = SobelNode["Sobel_Dx"];
	m_SobelDy = SobelNode["Sobel_Dy"];
	m_SobelKsize = SobelNode["Sobel_Ksize"];
	m_SobelType = SobelNode["Sobel_Type"];
	m_SobelScale = SobelNode["Sobel_Scale"];
	m_SobelDelta = SobelNode["Sobel_Delta"];
	FileNode LaplaceNode = fs["LaplaceProcess"];
	m_LaplaceGusize = LaplaceNode["Laplace_Gusize"];
	m_LaplaceDepth = LaplaceNode["Laplace_Depth"];
	m_LaplaceKsize = LaplaceNode["Laplace_Ksize"];
	m_LaplaceType = LaplaceNode["Laplace_Type"];
	m_LaplaceScale = LaplaceNode["Laplace_Scale"];
	m_LaplaceDelta = LaplaceNode["Laplace_Delta"];
	FileNode SubPixNode = fs["SubPixProcess"];
	m_SubPixSize = SubPixNode["SubPix_Size"];
	m_SubAutoThreMode = SubPixNode["SubPix_AutoThreMode"];
	m_SubAutoThreType = SubPixNode["SubPix_AutoThreType"];
	m_SubAutoThreKsize = SubPixNode["SubPix_AutoThreKsize"];
	m_SubPixC = SubPixNode["SubPix_C"];
	int rr = SubPixNode["SubPix_Color_R"];
	int rg = SubPixNode["SubPix_Color_G"];
	int rb = SubPixNode["SubPix_Color_B"];
	m_SubPixColor = Scalar(rb, rg, rr);
	FileNode HSVNode = fs["DivisionByHSV"];
	m_H_min = HSVNode["H_min"];
	m_S_min = HSVNode["S_min"];
	m_V_min = HSVNode["V_min"];
	m_H_max = HSVNode["H_max"];
	m_S_max = HSVNode["S_max"];
	m_V_max = HSVNode["V_max"];
	FileNode RGBNode = fs["DivisionByRGB"];
	m_R_min = RGBNode["R_min"];
	m_G_min = RGBNode["G_min"];
	m_B_min = RGBNode["B_min"];
	m_R_max = RGBNode["R_max"];
	m_G_max = RGBNode["G_max"];
	m_B_max = RGBNode["B_max"];
	FileNode GrayNode = fs["DivisionByGray"];
	m_Gray_Case = GrayNode["Gray_Case"];
	m_Gray_Min = GrayNode["Gray_Min"];
	m_Gray_Max = GrayNode["Gray_Max"];
	fs.release();
	return 0;
}

int __stdcall PixProcess::LoadXML(char* filename)
{
	FileStorage fs(filename, FileStorage::READ);
	if (!fs.isOpened())
	{
		return _OPEN_XML_ERROR_;
	}
	FileNode ThresholdNode = fs["ThresholdProcess"];
	m_Threshold_Thre = ThresholdNode["Threshold_Thre"];
	m_Threshold_Mode = ThresholdNode["Threshold_Mode"];
	FileNode CannyNode = fs["CannyProcess"];
	m_Canny_BlurSize = CannyNode["Canny_BlurSize"];
	m_Canny_Ksize = CannyNode["Canny_Ksize"];
	m_Canny_Min = CannyNode["Canny_Min"];
	m_Canny_Max = CannyNode["Canny_Max"];
	m_Canny_Gradient = (int)CannyNode["Canny_Gradient"];
	FileNode SobelNode = fs["SobelProcess"];
	m_SobelDepth = SobelNode["Sobel_Depth"];
	m_SobelDx = SobelNode["Sobel_Dx"];
	m_SobelDy = SobelNode["Sobel_Dy"];
	m_SobelKsize = SobelNode["Sobel_Ksize"];
	m_SobelType = SobelNode["Sobel_Type"];
	m_SobelScale = SobelNode["Sobel_Scale"];
	m_SobelDelta = SobelNode["Sobel_Delta"];
	FileNode LaplaceNode = fs["LaplaceProcess"];
	m_LaplaceGusize = LaplaceNode["Laplace_Gusize"];
	m_LaplaceDepth = LaplaceNode["Laplace_Depth"];
	m_LaplaceKsize = LaplaceNode["Laplace_Ksize"];
	m_LaplaceType = LaplaceNode["Laplace_Type"];
	m_LaplaceScale = LaplaceNode["Laplace_Scale"];
	m_LaplaceDelta = LaplaceNode["Laplace_Delta"];
	FileNode SubPixNode = fs["SubPixProcess"];
	m_SubPixSize = SubPixNode["SubPix_Size"];
	m_SubAutoThreMode = SubPixNode["SubPix_AutoThreMode"];
	m_SubAutoThreType = SubPixNode["SubPix_AutoThreType"];
	m_SubAutoThreKsize = SubPixNode["SubPix_AutoThreKsize"];
	m_SubPixC = SubPixNode["SubPix_C"];
	int rr = SubPixNode["SubPix_Color_R"];
	int rg = SubPixNode["SubPix_Color_G"];
	int rb = SubPixNode["SubPix_Color_B"];
	m_SubPixColor = Scalar(rb, rg, rr);
	FileNode HSVNode = fs["DivisionByHSV"];
	m_H_min = HSVNode["H_min"];
	m_S_min = HSVNode["S_min"];
	m_V_min = HSVNode["V_min"];
	m_H_max = HSVNode["H_max"];
	m_S_max = HSVNode["S_max"];
	m_V_max = HSVNode["V_max"];
	FileNode RGBNode = fs["DivisionByRGB"];
	m_R_min = RGBNode["R_min"];
	m_G_min = RGBNode["G_min"];
	m_B_min = RGBNode["B_min"];
	m_R_max = RGBNode["R_max"];
	m_G_max = RGBNode["G_max"];
	m_B_max = RGBNode["B_max"];
	FileNode GrayNode = fs["DivisionByGray"];
	m_Gray_Case = GrayNode["Gray_Case"];
	m_Gray_Min = GrayNode["Gray_Min"];
	m_Gray_Max = GrayNode["Gray_Max"];
	fs.release();
	return 0;
}

//private:
int PixProcess::ThresholdPro(cv::Mat src, cv::Mat &dst)
{
	if (src.empty())
	{
		return _NO_IMAGE_;
	}
	Mat gray;
	if (src.channels() == 3)
		cv::cvtColor(src, gray, CV_BGR2GRAY);
	else if (src.channels() == 1)
		gray = src.clone();
	else
		return _PARAM_ERROR_;
	cv::threshold(gray, dst, m_Threshold_Thre, 0xff, m_Threshold_Mode);
	return 0;
}

int PixProcess::CannyProcess(cv::Mat src, cv::Mat &dst)
{
	if (src.empty())
	{
		return _NO_IMAGE_;
	}
	Mat edge, gray;
	if (src.channels() == 3)
		cv::cvtColor(src, gray, CV_BGR2GRAY);
	else if (src.channels() == 1)
		gray = src.clone();
	else
		return _PARAM_ERROR_;
	if (m_Canny_BlurSize % 2 == 0)
	{
		m_Canny_BlurSize++;
	}
	if (m_Canny_Ksize % 2 == 0)
	{
		m_Canny_Ksize++;
	}
	blur(gray, edge, Size(m_Canny_BlurSize, m_Canny_BlurSize));
	Canny(edge, dst, m_Canny_Min, m_Canny_Max, m_Canny_Ksize, m_Canny_Gradient);
	return 0;
}

int PixProcess::SobelProcess(cv::Mat src, cv::Mat &dst)
{
	if (src.empty())
	{
		return _NO_IMAGE_;
	}
	Mat temp;
	if (m_SobelDx == 0 && m_SobelDy == 0)
	{
		return _PARAM_ERROR_;
	}
	if (m_SobelKsize % 2 == 0)
	{
		m_SobelKsize++;
	}
	Sobel(src, temp, m_SobelDepth, m_SobelDx, m_SobelDy, m_SobelKsize, m_SobelScale, m_SobelDelta, m_SobelType);
	convertScaleAbs(temp, dst);
	return 0;
}

int PixProcess::LaplaceProcess(cv::Mat src, cv::Mat &dst)
{
	if (src.empty())
	{
		return _NO_IMAGE_;
	}
	Mat edge, gray;
	Mat abs_dst;
	//高斯滤波消除噪声
	if (m_LaplaceGusize % 2 == 0)
	{
		m_LaplaceGusize++;
	}
	if (m_LaplaceKsize % 2 == 0)
	{
		m_LaplaceKsize++;
	}
	GaussianBlur(src, gray, Size(m_LaplaceGusize, m_LaplaceGusize), 0, 0, BORDER_DEFAULT);
	if (gray.channels() == 3)
		cv::cvtColor(gray, edge, CV_BGR2GRAY);
	else if (gray.channels() == 1)
		edge = gray.clone();
	else
		return _PARAM_ERROR_;
	//第三个参数：目标图像深度；第四个参数：滤波器孔径尺寸；第五个参数：比例因子；第六个参数：表示结果存入目标图
	Laplacian(edge, abs_dst, m_LaplaceDepth, m_LaplaceKsize, m_LaplaceScale, m_LaplaceDelta, m_LaplaceType);
	//计算绝对值，并将结果转为8位
	convertScaleAbs(abs_dst, dst);
	return 0;
}

int PixProcess::SubPixProcess(cv::Mat src, cv::Mat &dst)
{
	if (src.empty())
	{
		return _NO_IMAGE_;
	}
	Mat gray;
	if (src.channels() == 3)
	{
		cv::cvtColor(src, gray, CV_BGR2GRAY);
		dst = src.clone();
	}
	else if (src.channels() == 1)
	{
		gray = src.clone();
		cvtColor(src, dst, CV_GRAY2BGR);
	}
	else
		return _PARAM_ERROR_;
	if (m_SubPixSize % 2 == 0)
	{
		m_SubPixSize++;
	}
	if (m_SubAutoThreKsize % 2 == 0)
	{
		m_SubAutoThreKsize++;
	}
	Mat SubImage = gray.clone();
	Mat NewSmoothImage;
	medianBlur(gray, NewSmoothImage, m_SubPixSize);
	Mat NewAdaThresImage;
	//自适应二值化
	adaptiveThreshold(NewSmoothImage, NewAdaThresImage, 0xff, m_SubAutoThreMode, m_SubAutoThreType, m_SubAutoThreKsize, m_SubPixC);
	vector<Point2d> SubEdgePoints;
	Mat ZerImageM00;
	filter2D(NewAdaThresImage, ZerImageM00, CV_64F, M00, Point(-1, -1), 0, BORDER_DEFAULT);
	Mat ZerImageM11R;
	filter2D(NewAdaThresImage, ZerImageM11R, CV_64F, M11R, Point(-1, -1), 0, BORDER_DEFAULT);
	Mat ZerImageM11I;
	filter2D(NewAdaThresImage, ZerImageM11I, CV_64F, M11I, Point(-1, -1), 0, BORDER_DEFAULT);
	Mat ZerImageM20;
	filter2D(NewAdaThresImage, ZerImageM20, CV_64F, M20, Point(-1, -1), 0, BORDER_DEFAULT);
	Mat ZerImageM31R;
	filter2D(NewAdaThresImage, ZerImageM31R, CV_64F, M31R, Point(-1, -1), 0, BORDER_DEFAULT);
	Mat ZerImageM31I;
	filter2D(NewAdaThresImage, ZerImageM31I, CV_64F, M31I, Point(-1, -1), 0, BORDER_DEFAULT);
	Mat ZerImageM40;
	filter2D(NewAdaThresImage, ZerImageM40, CV_64F, M40, Point(-1, -1), 0, BORDER_DEFAULT);
	int row_number = NewAdaThresImage.rows;
	int col_number = NewAdaThresImage.cols;
	for (int i = 0; i < row_number; i++)
	{
		for (int j = 0; j <col_number; j++)
		{
			if (ZerImageM00.at<double>(i, j) == 0)
			{
				continue;
			}
			double theta_temporary = atan2(ZerImageM31I.at<double>(i, j), ZerImageM31R.at<double>(i, j));
			double rotated_z11 = 0.0;
			rotated_z11 = sin(theta_temporary)*(ZerImageM11I.at<double>(i, j)) + cos(theta_temporary)*(ZerImageM11R.at<double>(i, j));
			double rotated_z31 = 0.0;
			rotated_z31 = sin(theta_temporary)*(ZerImageM31I.at<double>(i, j)) + cos(theta_temporary)*(ZerImageM31R.at<double>(i, j));
			double l_method1 = sqrt((5 * ZerImageM40.at<double>(i, j) + 3 * ZerImageM20.at<double>(i, j)) / (8 * ZerImageM20.at<double>(i, j)));
			double l_method2 = sqrt((5 * rotated_z31 + rotated_z11) / (6 * rotated_z11));
			double l = (l_method1 + l_method2) / 2;
			double k, h;
			k = 3 * rotated_z11 / 2 / pow((1 - l_method2*l_method2), 1.5);
			h = (ZerImageM00.at<double>(i, j) - k*CV_PI / 2 + k*asin(l_method2) + k*l_method2*sqrt(1 - l_method2*l_method2)) / CV_PI;
			double k_value = 20.0;
			double l_value = sqrt(2) / 7;
			double absl = abs(l_method2 - l_method1);
			if (k >= k_value && absl <= l_value)
			{
				Point2d point_temporary;
				point_temporary.x = j + 7*l*cos(theta_temporary) / 2;
				point_temporary.y = i + 7*l*sin(theta_temporary) / 2;
				SubEdgePoints.push_back(point_temporary);
			}
			else
			{
				continue;
			}
		}
	}
	//显示所检测到的亚像素边缘
	for (size_t i = 0; i < SubEdgePoints.size(); i++)
	{
		Point center_forshow(cvRound(SubEdgePoints[i].x), cvRound(SubEdgePoints[i].y));
		circle(dst, center_forshow, 1, m_SubPixColor, 1, 8, 0);
	}
	return 0;
}
	
int PixProcess::DivisionByHSV(cv::Mat src, cv::Mat &dst)
{
	if (src.empty())
	{
		return _NO_IMAGE_;
	}
	Mat hsv;
	if (src.channels() == 3)
		cv::cvtColor(src, hsv, CV_BGR2HSV);
	else if (src.channels() == 1)
	{
		cv::cvtColor(src, src, CV_GRAY2BGR);
		cv::cvtColor(src, hsv, CV_BGR2HSV);
	}
	else
		return _PARAM_ERROR_;
	Mat mask;
	inRange(hsv, Scalar(m_H_min, m_S_min, m_V_min), Scalar(m_H_max, m_S_max, m_V_max), mask);
	src.copyTo(dst, mask);
	return 0;
}
	
int PixProcess::DivisionByRGB(cv::Mat src, cv::Mat &dst)
{
	if (src.empty())
	{
		return _NO_IMAGE_;
	}
	Mat rgb;
	if (src.channels() == 3)
		rgb = src.clone();
	else if (src.channels() == 1)
		cv::cvtColor(src, rgb, CV_GRAY2BGR);
	else
		return _PARAM_ERROR_;
	Mat mask;
	inRange(rgb, Scalar(m_R_min, m_G_min, m_B_min), Scalar(m_R_max, m_G_max, m_B_max), mask);
	src.copyTo(dst, mask);
	return 0;
}

int PixProcess::DivisionByGray(cv::Mat src, cv::Mat &dst)
{
	if (src.empty())
	{
		return _NO_IMAGE_;
	}
	Mat gray, hsv;
	vector<Mat> mat_hsv(3), mat_bgr(3);
	if (src.channels() == 3)
	{
		cv::cvtColor(src, gray, CV_BGR2GRAY);
		cvtColor(src, hsv, CV_BGR2HSV);
		split(src, mat_bgr);
		split(hsv, mat_hsv);
	}
	else if (src.channels() == 1)
	{
		gray = src.clone();
	}
	else
	{
		return _PARAM_ERROR_;
	}
	switch (m_Gray_Case)
	{
	case(DIVISION_BY_H) :
		return DivisionGrayImage(mat_hsv[0], dst, m_Gray_Min, m_Gray_Max);
	case(DIVISION_BY_S) :
		return DivisionGrayImage(mat_hsv[1], dst, m_Gray_Min, m_Gray_Max);
	case(DIVISION_BY_V) :
		return DivisionGrayImage(mat_hsv[2], dst, m_Gray_Min, m_Gray_Max);
	case(DIVISION_BY_R) :
		return DivisionGrayImage(mat_bgr[2], dst, m_Gray_Min, m_Gray_Max);
	case(DIVISION_BY_G) :
		return DivisionGrayImage(mat_bgr[1], dst, m_Gray_Min, m_Gray_Max);
	case(DIVISION_BY_B) :
		return DivisionGrayImage(mat_bgr[0], dst, m_Gray_Min, m_Gray_Max);
	case(DIVISION_BY_O) :
		return DivisionGrayImage(gray, dst, m_Gray_Min, m_Gray_Max);
	default:
		break;
	}
	return 0;
}

int PixProcess::DivisionGrayImage(cv::Mat src, cv::Mat &dst, int min, int max)
{
	if (src.empty())
	{
		return _NO_IMAGE_;
	}
	Mat gray;
	if (src.channels() == 3)
	{
		cv::cvtColor(src, gray, CV_BGR2GRAY);
	}
	else if (src.channels() == 1)
	{
		gray = src.clone();
	}
	else
	{
		return _PARAM_ERROR_;
	}
	dst = gray.clone();
	int tmp;
	for (int i = 0; i < gray.rows; i++)
	{
		for (int j = 0; j < gray.cols; j++)
		{
			tmp = gray.at<uchar>(i, j);
			if (tmp >= min&&tmp <= max)
			{
				dst.at<uchar>(i, j) = tmp;
			}
			else
			{
				dst.at<uchar>(i, j) = 0;
			}
		}
	}
	return 0;
}