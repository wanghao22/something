#include "stdafx.h"
#include "Bayer2BGR.h"

#pragma warning(disable: 4244)
#pragma warning(disable: 4018)

/*Mat dst = src.clone();
m_to.Bayer8ToRgb24(src.data, IMAGE_WIDTH, IMAGE_HEIGHT, dst.data, src.step * IMAGE_HEIGHT);
cvtColor(dst, dst, CV_RGB2BGR);*/

BayerToBGR::BayerToBGR()
{
	m_ulWidth = 0;
	m_ulHeight = 0;
	m_pBay = NULL;
	m_pRGB24 = NULL;
}

BayerToBGR::~BayerToBGR()
{
}

int BayerToBGR::Bayer8ToRgb24(unsigned char * pbBayer, int dwWidth, int dwHeight, unsigned char* pbRgb, int iRgbBufLen)
{
	BayerToBGR cPixelFormatConvert;
	return cPixelFormatConvert.ExecBayer8ToRgb24(pbBayer, dwWidth, dwHeight, pbRgb, iRgbBufLen);
	return 0;
}

int BayerToBGR::ExecBayer8ToRgb24(unsigned char * pbBayer, int dwWidth, int dwHeight, unsigned char* pbRgb, int iRgbBufLen)
{
	if (NULL == pbBayer || NULL == pbRgb)
	{
		return 0;
	}
	if (dwWidth <= 0 || dwHeight <= 0 || iRgbBufLen <= 0)
	{
		return 0;
	}
	if (iRgbBufLen != dwWidth * dwHeight * 3)
	{
		return 0;
	}

	m_pBay = pbBayer;
	m_pRGB24 = pbRgb;
	m_ulWidth = dwWidth;
	m_ulHeight = dwHeight;

	bayer_to_rgb24();
	return 1;
}

void BayerToBGR::bayer_copy(int x, int y)
{
	G(x + 0, y + 0) = Bay(x + 0, y + 0);
	G(x + 1, y + 1) = Bay(x + 1, y + 1);
	G(x + 0, y + 1) = G(x + 1, y + 0) = ((unsigned long)Bay(x + 0, y + 0) + (unsigned long)Bay(x + 1, y + 1)) / 2;

	R(x + 0, y + 0) = R(x + 1, y + 0) = R(x + 1, y + 1) = R(x + 0, y + 1) = Bay(x + 0, y + 1);
	B(x + 1, y + 1) = B(x + 0, y + 0) = B(x + 0, y + 1) = B(x + 1, y + 0) = Bay(x + 1, y + 0);
}

void BayerToBGR::bayer_bilinear(int x, int y)
{
	R(x + 0, y + 0) = ((unsigned long)Bay(x + 0, y + 1) + (unsigned long)Bay(x + 0, y - 1)) / 2;
	G(x + 0, y + 0) = Bay(x + 0, y + 0);
	B(x + 0, y + 0) = ((unsigned long)Bay(x - 1, y + 0) + (unsigned long)Bay(x + 1, y + 0)) / 2;

	R(x + 0, y + 1) = Bay(x + 0, y + 1);
	G(x + 0, y + 1) = ((unsigned long)Bay(x + 0, y + 0) + (unsigned long)Bay(x + 0, y + 2) + (unsigned long)Bay(x - 1, y + 1) + (unsigned long)Bay(x + 1, y + 1)) / 4;
	B(x + 0, y + 1) = ((unsigned long)Bay(x + 1, y + 0) + (unsigned long)Bay(x - 1, y + 0) + (unsigned long)Bay(x + 1, y + 2) + (unsigned long)Bay(x - 1, y + 2)) / 4;

	R(x + 1, y + 0) = ((unsigned long)Bay(x + 0, y + 1) + (unsigned long)Bay(x + 2, y + 1) + (unsigned long)Bay(x + 0, y - 1) + (unsigned long)Bay(x + 2, y - 1)) / 4;
	G(x + 1, y + 0) = ((unsigned long)Bay(x + 0, y + 0) + (unsigned long)Bay(x + 2, y + 0) + (unsigned long)Bay(x + 1, y - 1) + (unsigned long)Bay(x + 1, y + 1)) / 4;
	B(x + 1, y + 0) = Bay(x + 1, y + 0);

	R(x + 1, y + 1) = ((unsigned long)Bay(x + 0, y + 1) + (unsigned long)Bay(x + 2, y + 1)) / 2;
	G(x + 1, y + 1) = Bay(x + 1, y + 1);
	B(x + 1, y + 1) = ((unsigned long)Bay(x + 1, y + 0) + (unsigned long)Bay(x + 1, y + 2)) / 2;
}

void BayerToBGR::bayer_to_rgb24()
{
	int i, j;

	for (i = 0; i < m_ulWidth; i += 2)
	{
		for (j = 0; j < m_ulHeight; j += 2)
		{
			if (i == 0 || j == 0 || i == m_ulWidth - 2 || j == m_ulHeight - 2)
			{
				bayer_copy(i, j);
			}
			else
			{
				bayer_bilinear(i, j);
			}
		}
	}
}
