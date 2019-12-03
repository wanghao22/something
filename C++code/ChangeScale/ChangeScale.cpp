#include "ChangeScale.h"

using namespace std;

namespace ChangeScale {
	///10-->16
	string ten2sixtenn(int val, bool captialFlag)
	{
		string str = "";
		if (val < 0)
		{
			val = -val;
			str += "-";
		}
		vector<char> temp;
		while (val != 0)
		{
			int k = val % 16;
			if (k < 10)
				temp.push_back('0' + k);
			else
			{
				if (captialFlag)
					temp.push_back('A' + k - 10);
				else
					temp.push_back('a' + k - 10);
			}
			val /= 16;
		}
		int cnt = temp.size();
		for (int i = 0; i < cnt; i++)
		{
			str += temp[cnt - 1 - i];
		}
		return str;
	}

	///10->8
	string ten2eight(int val)
	{
		string str = "";
		if (val < 0)
		{
			val = -val;
			str += "-";
		}
		vector<char> temp;
		while (val != 0)
		{
			int k = val % 8;
			temp.push_back('0' + k);
			val /= 8;
		}
		int cnt = temp.size();
		for (int i = 0; i < cnt; i++)
		{
			str += temp[cnt - 1 - i];
		}
		return str;
	}

	///10->2
	string ten2two(int val)
	{
		string str = "";
		if (val < 0)
		{
			val = -val;
			str += "-";
		}
		vector<char> temp;
		while (val != 0)
		{
			int k = val % 2;
			temp.push_back('0' + k);
			val /= 2;
		}
		int cnt = temp.size();
		for (int i = 0; i < cnt; i++)
		{
			str += temp[cnt - 1 - i];
		}
		return str;
	}

	///2->10
	int two2ten(string str)
	{
		int cnt = str.length();
		if (cnt < 1)
			return 0;
		bool flag = false;
		if (str[0] == '-')
		{
			flag = true;
			str = str.substr(1, cnt - 1);
		}
		cnt = str.length();
		int result = 0;
		for (int i = 0; i < cnt; i++)
		{
			int t = str[cnt - 1 - i] - '0';
			if (t > 2 - 1)
				throw OverFlowException();
			result += t*pow(2, i);
		}
		if (flag)
			result = -result;
		return result;
	}

	///8->10
	int eight2ten(string str)
	{
		int cnt = str.length();
		if (cnt < 1)
			return 0;
		bool flag = false;
		if (str[0] == '-')
		{
			flag = true;
			str = str.substr(1, cnt - 1);
		}
		cnt = str.length();
		int result = 0;
		for (int i = 0; i < cnt; i++)
		{
			int t = str[cnt - 1 - i] - '0';
			if (t > 8 - 1)
				throw OverFlowException();
			result += t*pow(8, i);
		}
		if (flag)
			result = -result;
		return result;
	}

	///16->10
	int sixtenn2ten(string str)
	{
		int cnt = str.length();
		if (cnt < 1)
			return 0;
		bool flag = false;
		if (str[0] == '-')
		{
			flag = true;
			str = str.substr(1, cnt - 1);
		}
		cnt = str.length();
		int result = 0;
		for (int i = 0; i < cnt; i++)
		{
			char c = str[cnt - 1 - i];
			int t = 0;
			if (c >= '0'&&c <= '9')
				t = c - '0';
			else if (c >= 'a'&&c <= 'f')
				t = c - 'a' + 10;
			else if (c >= 'A'&&c <= 'F')
				t = c - 'A' + 10;
			else
				throw OverFlowException();
			result += t*pow(16, i);
		}
		if (flag)
			result = -result;
		return result;
	}

	///16->2
	string sixtenn2two(string str)
	{
		int val = sixtenn2ten(str);
		return ten2two(val);
	}

	///8->2
	string eight2two(string str)
	{
		int val = eight2ten(str);
		return ten2two(val);
	}

	///16->8
	string sixtenn2eight(string str)
	{
		int val = sixtenn2ten(str);
		return ten2eight(val);
	}

	///8->16
	string eight2sixtenn(string str, bool captialFlag)
	{
		int val = eight2ten(str);
		return ten2sixtenn(val, captialFlag);
	}

	///2->16
	string two2sixtenn(string str, bool captialFlag)
	{
		int val = two2ten(str);
		return ten2sixtenn(val, captialFlag);
	}

	///2->8
	string two2eight(string str)
	{
		int val = two2ten(str);
		return ten2eight(val);
	}
}