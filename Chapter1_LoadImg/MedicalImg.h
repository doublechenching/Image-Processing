/*********************************************************************************************************
* 模块名称: MedicalImg
* 摘    要: MVC框架中数据模型，医学图像
* 当前版本: 1.0.0
* 作    者: 秦陈陈
* 完成日期: 2017/12/20
* 内    容: 医学图像对象
* 注    意: 所有的数据模型只能和控制器交互                                                                  
**********************************************************************************************************
* 取代版本: 
* 作    者:
* 完成日期: 
* 修改内容:
* 修改文件: 
*********************************************************************************************************/
#pragma once

/*********************************************************************************************************
*                                              结构体定义
*********************************************************************************************************/
struct Pixel
{
	unsigned char iR;
	unsigned char iG;
	unsigned char iB;
};

/*********************************************************************************************************
*                                              类定义
*********************************************************************************************************/
class CMedicalImg
{
public:
	CMedicalImg(void);
	~CMedicalImg(void);
	CMedicalImg(CString path);			// 从文件中读取DIB
	CMedicalImg(CBitmap& ddb, CPalette* palette);	// 从DDB中获得DIB
	void* GetBits();					// 返回像素数组
	int GetBitsPerPixel();				// 返回每个像素的位数
	long GetWidth();					// 获取图像的宽度
	long GetHeight();					// 获取图像的高度
	long BytesPerline();				// 获得图像每行扫描线所需的字节数
	CPalette* GetPalette();				// 获取调色板
	void CopyPalette(CPalette&);		// 复制调色板
	int	GetPaletteCount();				// 获得调色板的大小
	long GetBodySize();					// 获得像素数组的大小
	// 在指定DC上缩放输出
	int StretchToDC(CDC& dc, CRect& src, CRect& dst, DWORD rop = SRCCOPY);
	int SetToDC(CDC& dc, CRect& src, CPoint& dst);	// 在指定DC上输出，不改变大小
	void LoadImg(CString path);
	void SaveDIB(CString dibName);
	int GetPixelRGB(int row, int col, int &r, int &g, int b);
	void UpdateRGB(char * imageBuffer, int deltaR, int deltaG, int deltaB);
private:
	void* m_pDibBits;			// 像素数组
	BITMAPINFO*	m_pDibInfo;		// DIB文件
public:
	CString m_strPath;			// 图片路径
};

