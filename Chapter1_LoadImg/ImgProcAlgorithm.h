#pragma once
class CImgProcAlgorithm
{
public:
	CImgProcAlgorithm();
	~CImgProcAlgorithm();
	static void RGB2HSV(int r, int g, int b, float &h, float &s, float &v);
	static void HSV2RGB(int h, int s, int v, int &r, int &g, int &b);
};

