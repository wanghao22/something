#include <iostream>
#include <vector>
using namespace std;

///string str = GetStringFromInt(10,4);
///input:10,4
///output:"0010"
string GetStringFromInt(int val, int len)
{
	string result = "";
	if (len < 1)
		return "ERROR";
	if (val < 0)
	{
		val = -val;
		result += "-";
	}
	if (val > pow(10, len) - 1)
		return "ERROR";
	for (int i = 0; i < len; i++)
	{
		int p = pow(10, (len - 1 - i));
		int t = val / p;
		result += to_string(t);
		val = val % p;
	}
	return result;
}

//��бʽ����ֱ��
void DrawLineByKP(cv::Mat &src, double k, cv::Point pt)
{
	//��б�������ʱ
	if (isnan(k))
	{
		line(src, Point(pt.x, 0), Point(pt.x, src.rows), cv::Scalar(0, 255, 0), 2, 8, 0);
		circle(src, pt, 3, Scalar(0, 0, 255), CV_FILLED);
		return;
	}
	//��б��Ϊ0ʱ
	if (k == 0)
	{
		line(src, Point(0, pt.y), Point(src.cols, pt.y), cv::Scalar(0, 255, 0), 2, 8, 0);
		circle(src, pt, 3, Scalar(0, 0, 255), CV_FILLED);
		return;
	}
	cv::Point point1, point2;
	//��б�ʱȽ�Сʱ����xȷ��ֱ��
	if (abs(k) <= 1)
	{
		point1.x = 0;
		point1.y = k * (0 - pt.x) + pt.y;
		point2.x = src.cols;
		point2.y = k * (src.cols - pt.x) + pt.y;
	}
	//��б�ʱȽϴ�ʱ����yȷ��ֱ��
	else
	{
		point1.y = 0;
		point1.x = ((0 - pt.y) / k) + pt.x;
		point2.y = src.rows;
		point2.x = ((src.rows - pt.y) / k) + pt.x;
	}
	cout << "Point 1:(" << point1.x << ", " << point1.y << ")" << endl;
	cout << "Point 2:(" << point2.x << ", " << point2.y << ")" << endl;
	cv::line(src, point1, point2, cv::Scalar(0, 255, 0), 2, 8, 0);
	circle(src, pt, 3, Scalar(0, 0, 255), CV_FILLED);
}

//�������������
void RandomArray(std::vector<int>oldArray, std::vector<int> &newArray) {
	// �������
	for (int i = LENGTH; i>0; i--) {
		srand(unsigned(time(NULL)));
		// ѡ�е�����±�
		int index = rand() % i;
		// ����ѡ�е��±꽫ԭ����ѡ�е�Ԫ��push��������
		newArray.push_back(oldArray[index]);
		// ��ԭ������ѡ�е�Ԫ���޳�
		oldArray.erase(oldArray.begin() + index);
	}
}

//�ָ��ַ��� "111,22,333","," ->{"111","22","333"}
std::vector<std::string> StringSplit(std::string str, std::string separator)
{
	vector<string> result;
	while (true)
	{
		int index = str.find(separator);
		if (index == -1)
		{
			result.push_back(str);
			break;
		}
		string temp = str.substr(0, index);
		str = str.substr(index + 1);
		result.push_back(temp);
	}
	return result;
}

//��Mat��ͼ��д�뵽XML�ļ���
int WriteInToXML(std::string xmlfile, cv::Mat src)
{
	FileStorage fs(xmlfile, FileStorage::WRITE);
	if (!fs.isOpened())
		return -1;
	fs << "rows" << src.rows;
	fs << "cols" << src.cols;
	fs << "type" << src.type();
	int chaneel = src.channels();
	fs << "channels" << chaneel;
	fs << "data" << "[";
	for (int i = 0; i<src.rows; i++)
	{
		for (int j = 0; j < src.cols; j++)
		{
			if (chaneel == 1)
			{
				int t = src.at<uchar>(i, j);
				fs << t;
			}
			else if (chaneel == 3)
			{
				Vec3b p = src.at<Vec3b>(i, j);
				int t = p[0]; fs << t;
				t = p[1]; fs << t;
				t = p[2]; fs << t;
			}
			else if (chaneel == 4)
			{
				Vec4b p = src.at<Vec4b>(i, j);
				int t = p[0]; fs << t;
				t = p[1]; fs << t;
				t = p[2]; fs << t;
				t = p[3]; fs << t;
			}
			else
				return -2;
		}
	}
	fs << "]";
	fs.release();
	return 0;
}

//��XML�ļ��ж�ȡͼ��
int ReadFromXML(std::string xmlfile, cv::Mat &dst)
{
	FileStorage fs(xmlfile, FileStorage::READ);
	if (!fs.isOpened())
		return -1;
	int row, col, type;
	fs["rows"] >> row;
	fs["cols"] >> col;
	fs["type"] >> type;
	if (row <= 0 || col <= 0)
		return -2;
	dst = Mat::zeros(row, col, type);
	vector<int> MatData;
	int chaneel = dst.channels();
	FileNode DataNode = fs["data"];
	for (FileNodeIterator it = DataNode.begin(); it != DataNode.end(); it++)
	{
		MatData.push_back(*it);
	}
	if (MatData.size() != row*col*chaneel)
		return -2;
	int idx = 0;
	for (int i = 0; i<dst.rows; i++)
	{
		for (int j = 0; j < dst.cols; j++)
		{
			if (chaneel == 1)
			{
				dst.at<uchar>(i, j) = MatData[idx];
				idx += 1;
			}
			else if (chaneel == 3)
			{
				dst.at<Vec3b>(i, j) = Vec3b(MatData[idx], MatData[idx + 1], MatData[idx + 2]);
				idx += 3;
			}
			else if (chaneel == 4)
			{
				dst.at<Vec4b>(i, j) = Vec4b(MatData[idx], MatData[idx + 1], MatData[idx + 2], MatData[idx + 3]);
				idx += 4;
			}
			else
				return -2;
		}
	}
	fs.release();
	return 0;
}