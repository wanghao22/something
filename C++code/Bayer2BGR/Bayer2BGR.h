#pragma once

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;

#define u8 uint8_t

#define R(x,y) m_pRGB24[2 + 3 * ((x) + m_ulWidth * (y))]
#define G(x,y) m_pRGB24[1 + 3 * ((x) + m_ulWidth * (y))]
#define B(x,y) m_pRGB24[0 + 3 * ((x) + m_ulWidth * (y))]
#define Bay(x,y) m_pBay[(x) + m_ulWidth * (y)]

class BayerToBGR
{
public:
	BayerToBGR();
	~BayerToBGR();

public:
	//函数名称：Bayer8ToRgb24
	//描述：将8位Bayer原始数据转换为24位RGB格式数据
	//注意：该函数不可重入
	/*
	* 要求的Bayer数据排列格式如下（GBRG）：
	*
	* G B G B G B G B...
	* R G R G R G R G...
	* G B G B G B G B...
	* R G R G R G R G...
	* G B G B G B G B...
	* R G R G R G R G...
	* G B G B G B G B...
	* R G R G R G R G...
	* ..................
	* ..................
	*/
	static int Bayer8ToRgb24(unsigned char* pbBayer, int dwWidth, int dwHeight, unsigned char* pbRgb, int iRgbBufLen);

protected:
	int ExecBayer8ToRgb24(unsigned char* pbBayer, int dwWidth, int dwHeight, unsigned char* pbRgb, int iRgbBufLen);

private:
	unsigned long m_ulWidth;
	unsigned long m_ulHeight;
	u8 *m_pBay;
	u8 *m_pRGB24;

private:
	void bayer_copy(int x, int y);
	void bayer_bilinear(int x, int y);
	void bayer_to_rgb24();
};

