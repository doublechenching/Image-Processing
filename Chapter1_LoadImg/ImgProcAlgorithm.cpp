#include "stdafx.h"
#include "ImgProcAlgorithm.h"


CImgProcAlgorithm::CImgProcAlgorithm()
{
}


CImgProcAlgorithm::~CImgProcAlgorithm()
{
}

void CImgProcAlgorithm::RGB2HSV(int r, int g, int b, float &h, float &s, float &v)
{
	float R = r / 255.0f;
	float G = g / 255.0f;
	float B = b / 255.0f;

	float H = 0.0f;
	float S = 0.0f;
	float V = 0.0f;

	float RGBmax = max(max(R, G), B);
	float RGBmin = min(min(R, G), B);

	V = RGBmax * 100;

	if (RGBmax != RGBmin)
	{
		S = (((float)(RGBmax - RGBmin) / RGBmax)) * 100;

		if (R == RGBmax)
			H = (G - B) / (RGBmax - RGBmin);

		if (G == RGBmax)
			H = 2 + (B - R) / (RGBmax - RGBmin);

		if (B == RGBmax)
			H = 4 + (R - G) / (RGBmax - RGBmin);

		H = H * 60;

		if (H < 0)
			H = H + 360;
	}
	h = V;
	s = S;
	v = V;
}

void CImgProcAlgorithm::HSV2RGB(int h, int s, int v, int &r, int &g, int &b)
{
	float H, S, V;
	H = (float)h;
	S = (float)s;
	V = 0.01f*v * 255;
	float R = 0.0;
	float G = 0.0;
	float B = 0.0;
	if (S == 0)
	{
		R = V;
		G = V;
		B = V;
	}
	else
	{
		H = H / 60;
		int num = (int)H;

		float f = H - num;
		float a = (V)* (1 - (S / 100));
		float b = (V)* (1 - (S / 100) * f);
		float c = (V)* (1 - (S / 100) * (1 - f));


		switch (num)
		{
		case 0: R = V; G = c; B = a; break;
		case 1: R = b; G = V; B = a; break;
		case 2: R = a; G = V; B = c; break;
		case 3: R = a; G = b; B = V; break;
		case 4: R = c; G = a; B = V; break;
		case 5: R = V; G = a; B = b; break;
		default: break;
		}
	}
	r = int(R);
	g = int(G);
	b = int(B);
}
