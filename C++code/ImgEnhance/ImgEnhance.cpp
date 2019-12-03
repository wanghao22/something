#include "ImgEnhance.h"

using namespace std;
using namespace cv;
using namespace DirFile;


ImgEnhance::ImgEnhance()
{
	srand((int)time(0));
	/*m_Flag_Rotate = false;
	m_Flag_Rotate90 = false;
	m_Flag_FlipX = false;
	m_Flag_FlipY = false;
	m_Flag_FlipXY = false;
	m_Flag_Crop = false;
	m_Flag_Blur = false;
	m_Flag_Contrast = false;
	m_Flag_Brightness = false;
	m_Flag_Noise = false;
	m_Flag_Sharpen = false;
	m_Rotate_Step = 100;
	m_Crop_Scale = 0.8;
	m_Contrast_Max = 60;
	m_Contrast_Step = 20;
	m_Brightness_Max = 60;
	m_Brightness_Step = 20;
	m_Other_Path_Flag = true;
	m_Sharpen_Thre = 15;
	m_Val_Scale = 15;
	m_Sharpen_Amount = 2;*/
}


ImgEnhance::~ImgEnhance()
{
}


void ImgEnhance::Enhance()
{
	if (m_Flag_Rotate)
		IRotate();
	if (m_Flag_Rotate90)
		IRotate90();
	if (m_Flag_FlipX)
		IFlipX();
	if (m_Flag_FlipY)
		IFlipY();
	if (m_Flag_FlipXY)
		IFlipXY();
	if (m_Flag_Crop)
		ICrop();
	if (m_Flag_Blur)
		IBlur();
	if (m_Flag_Contrast)
		IContrast();
	if (m_Flag_Brightness)
		IBrightness();
	if (m_Flag_Noise)
		INoise();
	if (m_Flag_Sharpen)
		ISharpen();
	for (size_t i = 0; i < m_enhance_imgs.size(); i++)
	{
		imwrite(m_enhance_fpath[i], m_enhance_imgs[i]);
	}
	if (m_Other_Path_Flag)
	{
		ClassifyTrainVal();
	}
}

void ImgEnhance::LoadImages(string fullpath)
{
	m_imgs.clear();
	m_fullpath.clear();
	path.clear();
	name.clear();
	type.clear();
	std::vector<std::string> temp;
	findFile(fullpath, temp);
	Mat src;
	string paths, names, types;
	for (size_t i = 0; i < temp.size(); i++)
	{
		src = imread(temp[i]);
		if (src.empty())
			continue;
		if (PathDevision(temp[i], paths, names, types) != 0)
			continue;
		this->m_imgs.push_back(src);
		this->m_fullpath.push_back(temp[i]);
		this->path.push_back(paths);
		this->name.push_back(names);
		this->type.push_back(types);
	}
}

void ImgEnhance::AddImage(std::vector<std::string> filenames)
{
	for (size_t i = 0; i < filenames.size(); i++)
		AddImage(filenames[i]);
}

void ImgEnhance::AddImage(std::string filename)
{
	Mat src = imread(filename);
	if (src.empty())
		return;
	string paths, names, types;
	if (PathDevision(filename, paths, names, types) != 0)
		return;
	this->m_imgs.push_back(src);
	this->m_fullpath.push_back(filename);
	this->path.push_back(paths);
	this->name.push_back(names);
	this->type.push_back(types);
}

int ImgEnhance::SaveXML()
{
	FileStorage fs(_ENHANCE_XML_, FileStorage::WRITE);
	if (!fs.isOpened())
	{
		return -2;
	}
	fs << "m_Flag_Rotate" << m_Flag_Rotate;
	fs << "m_Flag_Rotate90" << m_Flag_Rotate90;
	fs << "m_Flag_FlipX" << m_Flag_FlipX;
	fs << "m_Flag_FlipY" << m_Flag_FlipY;
	fs << "m_Flag_FlipXY" << m_Flag_FlipXY;
	fs << "m_Flag_Crop" << m_Flag_Crop;
	fs << "m_Flag_Blur" << m_Flag_Blur;
	fs << "m_Flag_Contrast" << m_Flag_Contrast;
	fs << "m_Flag_Brightness" << m_Flag_Brightness;
	fs << "m_Flag_Noise" << m_Flag_Noise;
	fs << "m_Flag_Sharpen" << m_Flag_Sharpen;
	fs << "m_Rotate_Step" << m_Rotate_Step;
	fs << "m_Crop_Scale" << m_Crop_Scale;
	fs << "m_Contrast_Max" << m_Contrast_Max;
	fs << "m_Contrast_Step" << m_Contrast_Step;
	fs << "m_Brightness_Max" << m_Brightness_Max;
	fs << "m_Brightness_Step" << m_Brightness_Step;
	fs << "m_Other_Path_Flag" << m_Other_Path_Flag;
	fs << "m_Sharpen_Thre" << m_Sharpen_Thre;
	fs << "m_Sharpen_Amount" << m_Sharpen_Amount;
	fs << "m_Val_Scale" << m_Val_Scale;
	fs << "m_Other_Path" << m_Other_Path;
	fs.release();
	return 0;
}

int ImgEnhance::LoadXML()
{
	FileStorage fs(_ENHANCE_XML_, FileStorage::READ);
	if (!fs.isOpened())
	{
		return -2;
	}
	fs["m_Flag_Rotate"] >> m_Flag_Rotate;
	fs["m_Flag_Rotate90"] >> m_Flag_Rotate90;
	fs["m_Flag_FlipX"] >> m_Flag_FlipX;
	fs["m_Flag_FlipY"] >> m_Flag_FlipY;
	fs["m_Flag_FlipXY"] >> m_Flag_FlipXY;
	fs["m_Flag_Crop"] >> m_Flag_Crop;
	fs["m_Flag_Blur"] >> m_Flag_Blur;
	fs["m_Flag_Contrast"] >> m_Flag_Contrast;
	fs["m_Flag_Brightness"] >> m_Flag_Brightness;
	fs["m_Flag_Noise"] >> m_Flag_Noise;
	fs["m_Flag_Sharpen"] >> m_Flag_Sharpen;
	fs["m_Rotate_Step"] >> m_Rotate_Step;
	fs["m_Crop_Scale"] >> m_Crop_Scale;
	fs["m_Contrast_Max"] >> m_Contrast_Max;
	fs["m_Contrast_Step"] >> m_Contrast_Step;
	fs["m_Brightness_Max"] >> m_Brightness_Max;
	fs["m_Brightness_Step"] >> m_Brightness_Step;
	fs["m_Other_Path_Flag"] >> m_Other_Path_Flag;
	fs["m_Sharpen_Thre"] >> m_Sharpen_Thre;
	fs["m_Sharpen_Amount"] >> m_Sharpen_Amount;
	fs["m_Val_Scale"] >> m_Val_Scale;
	fs["m_Other_Path"] >> m_Other_Path;
	fs.release();
	return 0;
}

//private:
void ImgEnhance::findFile(std::string path, std::vector<std::string>& res)
{
	string p;
	intptr_t hFile = 0;                //文件句柄
	struct _finddata_t fileinfo;    //文件信息
									//查找文件夹中的第一个文件，然后利用句柄进行遍历
	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != 0)
	{
		do
		{
			string path_s = p.assign(path).append("\\").append(fileinfo.name);
			if (strcmp(fileinfo.name, ".") == 0 || strcmp(fileinfo.name, "..") == 0)
				continue;
			if (fileinfo.attrib == _A_SUBDIR)
			{
				//遍历子目录
				std::vector<std::string> temp;
				findFile(path_s, temp);
				for (size_t i = 0; i < temp.size(); i++)
					res.push_back(temp[i]);
				continue;
			}
			res.push_back(path_s);            //插入容器
		} while (_findnext(hFile, &fileinfo) == 0);
		_findclose(hFile);    //关闭文件
	}
}

int ImgEnhance::PathDevision(std::string str, std::string & path, std::string & name, std::string & type)
{
	size_t i = str.find_last_of("/");
	size_t j = str.find_last_of("\\");
	size_t k = str.find_last_of(".");
	size_t d = 0;
	size_t l = str.length();
	if (i >= l&&j >= l)
	{
		return -1;
	}
	else if (i >= l)
		d = j;
	else if (j > l)
		d = i;
	else
		d = MAX(i, j);
	path = str.substr(0, d + 1);
	name = str.substr(d + 1, k - d - 1);
	type = str.substr(k, l - k);
	return 0;
}

void ImgEnhance::Do_rotate(cv::Mat src, cv::Mat & dst, double angle)
{
	cv::Point2f center(src.cols / 2.0, src.rows / 2.0);
	cv::Mat rot = cv::getRotationMatrix2D(center, angle, 1.0);
	warpAffine(src, dst, rot, src.size());
}

void ImgEnhance::Do_Vintensity(cv::Mat src, cv::Mat & dst, int value)
{
	cvtColor(src, dst, CV_BGR2HSV);
	for (int i = 0; i < dst.rows; i++)
	{
		for (int j = 0; j < dst.cols; j++)
		{
			if (value > 0)
				dst.at<Vec3b>(i, j)[2] = MIN(dst.at<Vec3b>(i, j)[2] + value, 255);
			else
				dst.at<Vec3b>(i, j)[2] = MAX(dst.at<Vec3b>(i, j)[2] + value, 0);
		}
	}
	cvtColor(dst, dst, CV_HSV2BGR);
}

void ImgEnhance::Do_Sharpen(cv::Mat src, cv::Mat & dst, double threshold, double amount)
{
	Mat blurred;
	double sigma = 1;
	GaussianBlur(src, blurred, Size(), sigma, sigma);
	//int depth = CV_MAT_DEPTH(imageSrc.type());
	Mat lowContrastMask = abs(src - blurred) < threshold;
	dst = src*(1 + amount) + blurred*(-amount);      //original + (original - blurred) * amount
	src.copyTo(dst, lowContrastMask);//将imageSrc中lowContrastMask对应的非0部分复制到dst中
	//lowContrastMask等于1时，说明高频分量比较小，有可能是噪声，此时不做锐化
}

int ImgEnhance::IRotate()
{
	for (size_t i = 0; i < m_imgs.size(); i++)
	{
		for (int j = m_Rotate_Step; j < 360; j += m_Rotate_Step)
		{
			if (m_imgs[i].empty())
				continue;
			if (m_imgs[i].cols != m_imgs[i].rows)
				continue;
			cv::Mat dst;
			Do_rotate(m_imgs[i], dst, j);
			m_enhance_imgs.push_back(dst);
			if (m_Other_Path_Flag)
			{
				m_enhance_fpath.push_back(m_Other_Path + ClassifyFloder(path[i]) + name[i] + "Rotate"
					+ to_string(j) + type[i]);
			}
			else
				m_enhance_fpath.push_back(path[i] + name[i] + "Rotate" + to_string(j) + type[i]);
		}
	}
	return 0;
}

int ImgEnhance::IRotate90()
{
	for (size_t i = 0; i < m_imgs.size(); i++)
	{
		if (m_imgs[i].empty())
			continue;
		if (m_imgs[i].cols != m_imgs[i].rows)
			continue;
		cv::Mat dst1, dst2;
		Do_rotate(m_imgs[i], dst1, 90);
		Do_rotate(m_imgs[i], dst2, 270);
		m_enhance_imgs.push_back(dst1);
		m_enhance_imgs.push_back(dst2);
		if (m_Other_Path_Flag)
		{
			m_enhance_fpath.push_back(m_Other_Path + ClassifyFloder(path[i]) + 
				name[i] + "Rotate90" + type[i]);
			m_enhance_fpath.push_back(m_Other_Path + ClassifyFloder(path[i]) + 
				name[i] + "Rotate270" + type[i]);
		}
		else
		{
			m_enhance_fpath.push_back(path[i] + name[i] + "Rotate90" + type[i]);
			m_enhance_fpath.push_back(path[i] + name[i] + "Rotate270" + type[i]);
		}
	}
	return 0;
}

int ImgEnhance::IFlipX()
{
	for (size_t i = 0; i < m_imgs.size(); i++)
	{
		if (m_imgs[i].empty())
		continue;
		Mat dst;
		flip(m_imgs[i], dst, 0);
		m_enhance_imgs.push_back(dst);
		if (m_Other_Path_Flag)
		{
			m_enhance_fpath.push_back(m_Other_Path + ClassifyFloder(path[i]) + 
				name[i] + "FlipX" + type[i]);
		}
		else
			m_enhance_fpath.push_back(path[i] + name[i] + "FlipX"+ type[i]);
	}
	return 0;
}

int ImgEnhance::IFlipY()
{
	for (size_t i = 0; i < m_imgs.size(); i++)
	{
		if (m_imgs[i].empty())
		continue;
		Mat dst;
		flip(m_imgs[i], dst, 1);
		m_enhance_imgs.push_back(dst);
		if (m_Other_Path_Flag)
		{
			m_enhance_fpath.push_back(m_Other_Path + ClassifyFloder(path[i]) + 
				name[i] + "FlipY" + type[i]);
		}
		else
			m_enhance_fpath.push_back(path[i] + name[i] + "FlipY" + type[i]);
	}
	return 0;
}

int ImgEnhance::IFlipXY()
{
	for (size_t i = 0; i < m_imgs.size(); i++)
	{
		if (m_imgs[i].empty())
		continue;
		Mat dst;
		flip(m_imgs[i], dst, -1);
		m_enhance_imgs.push_back(dst);
		if (m_Other_Path_Flag)
		{
			m_enhance_fpath.push_back(m_Other_Path + ClassifyFloder(path[i]) + 
				name[i] + "FlipXY" + type[i]);
		}
		else
			m_enhance_fpath.push_back(path[i] + name[i] + "FlipXY" + type[i]);
	}
	return 0;
}

int ImgEnhance::ICrop()
{
	m_Crop_Scale = MAX(m_Crop_Scale, 0.5);
	m_Crop_Scale = MIN(m_Crop_Scale, 0.9);
	for (size_t i = 0; i < m_imgs.size(); i++)
	{
		if (m_imgs[i].empty())
			continue;
		CvRect roi1, roi2, roi3, roi4;
		double sub = 1 - m_Crop_Scale;
		roi1 = cvRect(0, 0, m_imgs[i].cols*m_Crop_Scale, m_imgs[i].rows*m_Crop_Scale);
		roi2 = cvRect(m_imgs[i].cols*sub - 1, 0, m_imgs[i].cols*m_Crop_Scale, m_imgs[i].rows*m_Crop_Scale);
		roi3 = cvRect(0, m_imgs[i].rows*sub - 1, m_imgs[i].cols*m_Crop_Scale, m_imgs[i].rows*m_Crop_Scale);
		roi4 = cvRect(m_imgs[i].cols*sub - 1, m_imgs[i].rows*sub - 1,
			m_imgs[i].cols*m_Crop_Scale, m_imgs[i].rows*m_Crop_Scale);
		Mat dst1, dst2, dst3, dst4;
		dst1 = m_imgs[i](roi1);
		dst2 = m_imgs[i](roi2);
		dst3 = m_imgs[i](roi3);
		dst4 = m_imgs[i](roi4);
		resize(dst1, dst1, m_imgs[i].size());
		resize(dst2, dst2, m_imgs[i].size());
		resize(dst3, dst3, m_imgs[i].size());
		resize(dst4, dst4, m_imgs[i].size());
		m_enhance_imgs.push_back(dst1);
		m_enhance_imgs.push_back(dst2);
		m_enhance_imgs.push_back(dst3);
		m_enhance_imgs.push_back(dst4);
		if (m_Other_Path_Flag)
		{
			m_enhance_fpath.push_back(m_Other_Path + ClassifyFloder(path[i]) + 
				name[i] + "Crop1" + type[i]);
			m_enhance_fpath.push_back(m_Other_Path + ClassifyFloder(path[i]) + 
				name[i] + "Crop2" + type[i]);
			m_enhance_fpath.push_back(m_Other_Path + ClassifyFloder(path[i]) + 
				name[i] + "Crop3" + type[i]);
			m_enhance_fpath.push_back(m_Other_Path + ClassifyFloder(path[i]) + 
				name[i] + "Crop4" + type[i]);
		}
		else
		{
			m_enhance_fpath.push_back(path[i] + name[i] + "Crop1" + type[i]);
			m_enhance_fpath.push_back(path[i] + name[i] + "Crop2" + type[i]);
			m_enhance_fpath.push_back(path[i] + name[i] + "Crop3" + type[i]);
			m_enhance_fpath.push_back(path[i] + name[i] + "Crop4" + type[i]);
		}
	}
	return 0;
}

int ImgEnhance::IBlur()
{
	for (size_t i = 0; i < m_imgs.size(); i++)
	{
		if (m_imgs[i].empty())
			continue;
		Mat dst;
		blur(m_imgs[i], dst, cvSize(3, 3));
		m_enhance_imgs.push_back(dst);
		if (m_Other_Path_Flag)
		{
			m_enhance_fpath.push_back(m_Other_Path + ClassifyFloder(path[i]) + 
				name[i] + "Blur" + type[i]);
		}
		else
			m_enhance_fpath.push_back(path[i] + name[i] + "Blur" + type[i]);
	}
	return 0;
}

int ImgEnhance::IContrast()
{
	for (size_t i = 0; i < m_imgs.size(); i++)
	{
		for (int j = m_Contrast_Step; j < m_Contrast_Max; j += m_Contrast_Step)
		{
			if (m_imgs[i].empty())
				continue;
			cv::Mat dst;
			Do_Vintensity(m_imgs[i], dst, 0 - j);
			m_enhance_imgs.push_back(dst);
			if (m_Other_Path_Flag)
			{
				m_enhance_fpath.push_back(m_Other_Path + ClassifyFloder(path[i]) + 
					name[i] + "Contrast" + to_string(j) + type[i]);
			}
			else
				m_enhance_fpath.push_back(path[i] + name[i] + "Contrast" + to_string(j) + type[i]);
		}
	}
	return 0;
}

int ImgEnhance::IBrightness()
{
	for (size_t i = 0; i < m_imgs.size(); i++)
	{
		for (int j = m_Brightness_Step; j < m_Brightness_Max; j += m_Brightness_Step)
		{
			if (m_imgs[i].empty())
				continue;
			cv::Mat dst;
			Do_Vintensity(m_imgs[i], dst, j);
			m_enhance_imgs.push_back(dst);
			if (m_Other_Path_Flag)
			{
				m_enhance_fpath.push_back(m_Other_Path + ClassifyFloder(path[i]) + 
					name[i] + "Brightness" + to_string(j) + type[i]);
			}
			else
				m_enhance_fpath.push_back(path[i] + name[i] + "Brightness" + to_string(j) + type[i]);
		}
	}
	return 0;
}

int ImgEnhance::INoise()
{
	for (size_t i = 0; i < m_imgs.size(); i++)
	{
		if (m_imgs[i].empty())
			continue;
		Mat GaussianMat = m_imgs[i].clone();
		RNG rng;
		rng.fill(GaussianMat, cv::RNG::NORMAL, rng.uniform((double)0, (double)20),
			rng.uniform((double)0, (double)20));
		Mat dst;
		add(m_imgs[i], GaussianMat, dst);
		m_enhance_imgs.push_back(dst);
		if (m_Other_Path_Flag)
		{
			m_enhance_fpath.push_back(m_Other_Path + ClassifyFloder(path[i]) + 
				name[i] + "Noise" + type[i]);
		}
		else
			m_enhance_fpath.push_back(path[i] + name[i] + "Noise" + type[i]);
	}
	return 0;
}

int ImgEnhance::ISharpen()
{
	for (size_t i = 0; i < m_imgs.size(); i++)
	{
		if (m_imgs[i].empty())
			continue;
		Mat dst;
		Do_Sharpen(m_imgs[i], dst, m_Sharpen_Thre, m_Sharpen_Amount);
		m_enhance_imgs.push_back(dst);
		if (m_Other_Path_Flag)
		{
			m_enhance_fpath.push_back(m_Other_Path + ClassifyFloder(path[i]) + 
				name[i] + "Sharpen" + type[i]);
		}
		else
			m_enhance_fpath.push_back(path[i] + name[i] + "Sharpen" + type[i]);
	}
	return 0;
}

void ImgEnhance::ClassifyTrainVal()
{
	string train_file = m_Other_Path + "/train.txt";
	string val_file = m_Other_Path + "/val.txt";
	ofstream train, val;
	train.open(train_file);
	val.open(val_file);
	bool train_f;
	int judege;
	string filename;
	for (size_t i = 0; i < m_imgs.size(); i++)
	{
		string fullpath = m_Other_Path + ClassifyFloder(path[i]) + name[i] + type[i];
		imwrite(fullpath, m_imgs[i]);
		GiveTxtInfo(fullpath, train_f, judege, filename);
		if (train_f)
			train << filename << " " << judege << endl;
		else
			val << filename << " " << judege << endl;
	}
	for (size_t i = 0; i < m_enhance_fpath.size(); i++)
	{
		GiveTxtInfo(m_enhance_fpath[i], train_f, judege, filename);
		if (train_f)
			train << filename << " " << judege << endl;
		else
			val << filename << " " << judege << endl;
	}
	train.close();
	val.close();
}

std::string ImgEnhance::ClassifyFloder(std::string strl)
{
	int x = rand() % 1000;
	int y = strl.find("NG");
	if (y != -1 && x < m_Val_Scale)
		return "/val/NG/";
	else if (y != -1 && x >= m_Val_Scale)
		return "/train/NG/";
	else if (y == -1 && x < m_Val_Scale)
		return "/val/OK/";
	else
		return "/train/OK/";
}

void ImgEnhance::GiveTxtInfo(std::string fullpath, bool & train_flag, int & info, std::string &filename)
{
	string str1, str2, str3;
	if (PathDevision(fullpath, str1, str2, str3) != 0)
		return;
	if (str1.find("OK") != -1)
	{
		if (str1.find("train") != -1)
		{
			train_flag = true;
			filename = "train/OK/" + str2 + str3;
		}
		else
		{
			train_flag = false;
			filename = "val/OK/" + str2 + str3;
		}
		info = 1;
	}
	else
	{
		if (str1.find("train") != -1)
		{
			train_flag = true;
			filename = "train/NG/" + str2 + str3;
		}
		else
		{
			train_flag = false;
			filename = "val/NG/" + str2 + str3;
		}
		info = 0;
	}
}

void ImgEnhance::TrainStart(string out_dir)
{
	//开始cmd
	vector<string> cmd;
	cmd.push_back("rd /s/q ..\\temp\\lmdb\\train");
	cmd.push_back("rd /s/q ..\\temp\\lmdb\\val");
	string convert = DirAddSubdir(caffe_tools_dir, "convert_imageset.exe");
	string compute = DirAddSubdir(caffe_tools_dir, "compute_image_mean.exe");
	string caffe = DirAddSubdir(caffe_tools_dir, "caffe.exe");
	string caffemodel = DirAddSubdir(this_dir, "temp");
	caffemodel = DirAddSubdir(caffemodel, "caffemodel");
	cmd.push_back(convert + " --shuffle --resize_height=0 --resize_width=0 ..\\temp\\data\\ ..\\temp\\data\\train.txt ..\\temp\\lmdb\\train");
	cmd.push_back(convert + " --shuffle --resize_height=0 --resize_width=0 ..\\temp\\data\\ ..\\temp\\data\\val.txt ..\\temp\\lmdb\\val");
	cmd.push_back(compute + " ..\\temp\\lmdb\\train ..\\temp\\caffemodel\\mean.binaryproto");
	cmd.push_back(caffe + " train -solver ..\\temp\\caffemodel\\solver.prototxt");
	cmd.push_back("copy ..\\temp\\caffemodel\\mean.binaryproto " + out_dir);
	cmd.push_back("copy ..\\temp\\caffemodel\\caffenet_train_iter_10000.caffemodel " + out_dir + "\\caffenet.caffemodel");
	cmd.push_back("del " + caffemodel + "\\*.caffemodel");
	cmd.push_back("del " + caffemodel + "\\*.solverstate");
	for (size_t i = 0; i < cmd.size(); i++)
	{
		system(cmd[i].c_str());
	}
}

void ImgEnhance::CmdTrainStart(std::string out_dir)
{
	ofstream outfile;
	outfile.open(_TRAIN_CMD_);
	outfile << "rd /s/q ..\\temp\\lmdb\\train" << endl;
	outfile << "rd /s/q ..\\temp\\lmdb\\val" << endl;
	string convert = DirAddSubdir(caffe_tools_dir, "convert_imageset.exe");
	string compute = DirAddSubdir(caffe_tools_dir, "compute_image_mean.exe");
	string caffe = DirAddSubdir(caffe_tools_dir, "caffe.exe");
	string caffemodel = DirAddSubdir(this_dir, "temp");
	caffemodel = DirAddSubdir(caffemodel, "caffemodel");
	outfile << convert + " --shuffle --resize_height=0 --resize_width=0 ..\\temp\\data\\ ..\\temp\\data\\train.txt ..\\temp\\lmdb\\train" << endl;
	outfile << convert + " --shuffle --resize_height=0 --resize_width=0 ..\\temp\\data\\ ..\\temp\\data\\val.txt ..\\temp\\lmdb\\val" << endl;
	outfile << compute + " ..\\temp\\lmdb\\train ..\\temp\\caffemodel\\mean.binaryproto" << endl;
	outfile << caffe + " train -solver ..\\temp\\caffemodel\\solver.prototxt" << endl;
	outfile << "copy ..\\temp\\caffemodel\\mean.binaryproto " + out_dir << endl;
	outfile << "copy ..\\temp\\caffemodel\\caffenet_train_iter_10000.caffemodel " + out_dir + "\\caffenet.caffemodel" << endl;
	outfile << "del " + caffemodel + "\\*.caffemodel" << endl;
	outfile << "del " + caffemodel + "\\*.solverstate" << endl;
	outfile.close();
	system(_TRAIN_CMD_);
}
