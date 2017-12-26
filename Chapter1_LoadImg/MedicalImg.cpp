/*********************************************************************************************************
* 模块名称: MedicalImg
* 摘    要: 图片控件实现
* 当前版本: 1.0.0
* 作    者: 秦陈陈
* 完成日期: 2017/12/20
* 内    容: 
* 注    意: none                                                                  
**********************************************************************************************************
* 取代版本: 
* 作    者:
* 完成日期: 
* 修改内容:
* 修改文件: 
*********************************************************************************************************/


/*********************************************************************************************************
*                                              包含头文件
*********************************************************************************************************/
#include "StdAfx.h"
#include "MedicalImg.h"
#include <vector>

using std::vector;		//只导入部分类型
/*********************************************************************************************************
*                                              类成员函数实现
*********************************************************************************************************/

/*********************************************************************************************************
* 函数名称:  CMedicalImg::CMedicalImg
* 权    限:  public 
* 函数功能:  构造函数
* 参    数:  void
* 返 回 值:  
* 注    意:  
*********************************************************************************************************/
CMedicalImg::CMedicalImg(void)
	:m_pDibInfo(NULL), m_strPath(L""), m_pDibBits(NULL)
{
}


/*********************************************************************************************************
* 函数名称:  CMedicalImg::CMedicalImg
* 权    限:  public 
* 函数功能:  通过图片路径初始化数据
* 参    数:  CString path
* 返 回 值:  
* 注    意:  
*********************************************************************************************************/
CMedicalImg::CMedicalImg(CString path )
	: m_strPath(path)
{
	LoadImg(path);
}


CMedicalImg::CMedicalImg(CBitmap& ddb, CPalette* palette)
	:m_pDibInfo(NULL), m_strPath(L""), m_pDibBits(NULL)
{
	BITMAP ddbinfo;
	//获得DDB的相关信息
	ddb.GetBitmap(&ddbinfo);
	/*下面根据图像的高度宽度等信息，填写DIB所必需的BITMAPINFO*/
	int w = ddbinfo.bmWidth;
	int h = ddbinfo.bmHeight;
	int BitsPerPixel = ddbinfo.bmPlanes*ddbinfo.bmBitsPixel;

	int i;
	int PaletteSize = 0, cbHeaderSize;

	//根据每像素需要几个bit来设置RGBQUAD数组的大小
	switch (BitsPerPixel)
	{
	case 1:
		PaletteSize = 2;
		break;
	case 4:
		PaletteSize = 16;
		break;
	case 8:
		PaletteSize = 256;
		break;
		//超过8位的DIB不需要调色板
	case 15:
	case 16:
		BitsPerPixel = 16;
		break;
	}

	cbHeaderSize = sizeof(BITMAPINFOHEADER) + PaletteSize * sizeof(RGBQUAD);
	if (m_pDibInfo) delete[] m_pDibInfo;
	//为BITMAPINFO的对象DibInfo分配一段内存空间
	m_pDibInfo = (BITMAPINFO*) new char[cbHeaderSize];
	//填写BITMAPINFO
	m_pDibInfo->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	m_pDibInfo->bmiHeader.biWidth = w;
	m_pDibInfo->bmiHeader.biHeight = h;
	m_pDibInfo->bmiHeader.biPlanes = 1;
	m_pDibInfo->bmiHeader.biBitCount = short(BitsPerPixel);
	m_pDibInfo->bmiHeader.biCompression = BI_RGB;
	m_pDibInfo->bmiHeader.biSizeImage = BytesPerline() * m_pDibInfo->bmiHeader.biHeight;
	m_pDibInfo->bmiHeader.biXPelsPerMeter = m_pDibInfo->bmiHeader.biYPelsPerMeter = 3780;
	m_pDibInfo->bmiHeader.biClrUsed = PaletteSize;
	m_pDibInfo->bmiHeader.biClrImportant = PaletteSize;

	if (PaletteSize)
	{
		//把RGBQUAD数组中的每个元素全部置0
		for (i = 0; i < PaletteSize; i++)
		{
			m_pDibInfo->bmiColors[i].rgbRed = 0;
			m_pDibInfo->bmiColors[i].rgbGreen = 0;
			m_pDibInfo->bmiColors[i].rgbBlue = 0;
			m_pDibInfo->bmiColors[i].rgbReserved = 0;
		}
	}

	//为DIB像素数组分配空间，大小由GetBodySize()决定
	m_pDibBits = (void*) new char[GetBodySize()];
	//判断是否由调色板，如果有则将palette中的entry
	//复制到BITMAPINFO的RGBQUAD数组中
	if (palette) CopyPalette(*palette);

	// 将DDB中的图像信息复制到DIB中
	// GetDesktopWindow()返回桌面窗口的句柄
	CWnd DesktopWnd;
	DesktopWnd.Attach(::GetDesktopWindow());
	CWindowDC dtpDC(&DesktopWnd);
	// 完成从DDB向DIB的转换工作
	::GetDIBits(dtpDC.m_hDC,
		HBITMAP(ddb),
		0,
		ddbinfo.bmHeight,
		LPVOID(m_pDibBits),
		m_pDibInfo,
		DIB_RGB_COLORS
		);
	DesktopWnd.Detach();
}


void* CMedicalImg::GetBits()
{
	return m_pDibBits;
}

int CMedicalImg::GetBitsPerPixel()
{
	if (!m_pDibInfo)
	{
		return 0;
	}
		
	return m_pDibInfo->bmiHeader.biBitCount;
}

long CMedicalImg::GetWidth()
{
	return m_pDibInfo->bmiHeader.biWidth;
}

long CMedicalImg::GetHeight()
{
	return m_pDibInfo->bmiHeader.biHeight;
}

long CMedicalImg::BytesPerline()
{
	return ((((m_pDibInfo->bmiHeader.biWidth * GetBitsPerPixel()) + 31) / 32) * 4);
}

void CMedicalImg::CopyPalette(CPalette& palette)
{
	int i;
	PALETTEENTRY *pe;

	if (!m_pDibInfo->bmiHeader.biBitCount) return;
	if (palette.GetEntryCount() != m_pDibInfo->bmiHeader.biBitCount) return;

	pe = new PALETTEENTRY[palette.GetEntryCount()];
	palette.GetPaletteEntries(0, palette.GetEntryCount(), pe);

	for (i = 0; i < palette.GetEntryCount(); i++)
	{
		m_pDibInfo->bmiColors[i].rgbRed = pe[i].peRed;
		m_pDibInfo->bmiColors[i].rgbGreen = pe[i].peGreen;
		m_pDibInfo->bmiColors[i].rgbBlue = pe[i].peBlue;
		m_pDibInfo->bmiColors[i].rgbReserved = 0;
	}

	delete[] pe;
}

int CMedicalImg::GetPaletteCount()
{
	int iPaletteSize = 0;
	if (!m_pDibInfo) return 0;
	switch (m_pDibInfo->bmiHeader.biBitCount)
	{
	case 1:
		iPaletteSize = 2;
		break;
	case 4:
		iPaletteSize = 16;
		break;
	case 8:
		iPaletteSize = 256;
		break;
	}
	return iPaletteSize;
}

long CMedicalImg::GetBodySize()
{
	return BytesPerline() * m_pDibInfo->bmiHeader.biHeight;
}


int CMedicalImg::StretchToDC(CDC& dc, CRect& src, CRect& dst, DWORD rop /*= SRCCOPY*/)
{
	return ::StretchDIBits(
		dc.m_hDC,
		dst.left,
		dst.top,
		dst.Width(),
		dst.Height(),
		src.left,
		src.top,
		src.Width(),
		src.Height(),
		m_pDibBits,
		m_pDibInfo,
		DIB_RGB_COLORS,
		rop
		);
}

int CMedicalImg::SetToDC(CDC& dc, CRect& src, CPoint& dst)
{
	return ::SetDIBitsToDevice(
		dc.m_hDC,
		dst.x,
		dst.y,
		src.Width(),
		src.Height(),
		src.left,
		src.top,
		0,
		m_pDibInfo->bmiHeader.biHeight,
		m_pDibBits,
		m_pDibInfo,
		DIB_RGB_COLORS
		);
}

/*********************************************************************************************************
* 函数名称:  CMedicalImg::~CMedicalImg
* 权    限:  public 
* 函数功能:  析构函数
* 参    数:  void
* 返 回 值:  
* 注    意:  
*********************************************************************************************************/
CMedicalImg::~CMedicalImg(void)
{
	delete[] m_pDibInfo;
	delete[] m_pDibBits;
}


/*********************************************************************************************************
* 函数名称:  CMedicalImg::LoadImg
* 权    限:  public 
* 函数功能:  通过路径导入图片
* 参    数:  CString path： 图片路径
* 返 回 值:  
* 注    意:  
*********************************************************************************************************/
void CMedicalImg::LoadImg( CString path )
{
	// 创建CFile对象
	m_strPath = path;
	CFile bmpFile(path, CFile::modeRead | CFile::typeBinary);

	BITMAPFILEHEADER bmfileheader;
	BITMAPINFOHEADER bmheader;

	ULONGLONG headpos;
	int iPaletteSize = 0;
	int iRet, iCB_HeaderSize;
	// 获取文件指针的位置
	headpos = bmpFile.GetPosition();
	// 读取BMP文件头
	iRet = bmpFile.Read(&bmfileheader, sizeof(BITMAPFILEHEADER));
	// 如果文件类型标头不是“0x4d42”，表示该文件不是BMP类型文件
	if (bmfileheader.bfType != 0x4d42)
	{
		AfxMessageBox(L"Error!");
		return;
	}
	// 读取BMP文件信息头	
	iRet = bmpFile.Read(&bmheader, sizeof(BITMAPINFOHEADER));
	// 计算RGBQUAD的大小
	switch (bmheader.biBitCount)
	{
	case 1:
		iPaletteSize = 2;
		break;
	case 4:
		iPaletteSize = 16;
		break;
	case 8:
		iPaletteSize = 256;
		break;
	}

	// 为BITMAPINFO结构分配内存
	iCB_HeaderSize = sizeof(BITMAPINFOHEADER) + iPaletteSize*sizeof(RGBQUAD);
	m_pDibInfo = (BITMAPINFO*) new char[iCB_HeaderSize];
	m_pDibInfo->bmiHeader = bmheader;
	// 读取调色板
	if (iPaletteSize)
	{
		iRet = bmpFile.Read(&(m_pDibInfo->bmiColors[0]), iPaletteSize*sizeof(RGBQUAD));
		if (iRet != int(iPaletteSize*sizeof(RGBQUAD)))
		{
			delete[] m_pDibInfo;
			m_pDibInfo = NULL;
			return;
		}
	}

	// 为像素数组分配空间，大小由GetBodySize()决定
	m_pDibBits = (void*) new char[GetBodySize()];
	// 把文件指针移动到DIB图像数组
	bmpFile.Seek(headpos + bmfileheader.bfOffBits, CFile::begin);
	// 读取像素数组
	iRet = bmpFile.Read(m_pDibBits, GetBodySize());
	if (iRet != int(GetBodySize()))
	{
		delete[] m_pDibInfo;
		delete[] m_pDibBits;
		m_pDibInfo = NULL;
		m_pDibBits = NULL;
	}
	//关闭文件
	bmpFile.Close();
}


void CMedicalImg::SaveDIB(CString dibName)
{
	//若DIB为空则提示错误并返回
	if (!m_pDibInfo)
	{
		AfxMessageBox(L"DIB信息不存在！");
		return;
	}

	//通过文件名创建CFile对象
	//若文件打开失败则提示错误并返回
	CFile file;
	if (!file.Open(dibName, CFile::modeCreate | CFile::modeReadWrite))
	{
		AfxMessageBox(L"建立文件失败！");
		return;
	}

	//Bitmap文件头
	BITMAPFILEHEADER bmfileheader;

	long size = BytesPerline() * m_pDibInfo->bmiHeader.biHeight;
	int PaletteSize = GetPaletteCount();

	//填写BMP文件的数据
	bmfileheader.bfType = 0x4d42;//类型表示"BM"
	bmfileheader.bfReserved1 = bmfileheader.bfReserved2 = 0;//保留字0
	bmfileheader.bfOffBits =
		sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER)
		+ PaletteSize*sizeof(RGBQUAD);
	bmfileheader.bfSize = bmfileheader.bfOffBits + size;

	//将文件头，位图信息和像素数组写入磁盘文件
	file.Write(&bmfileheader, sizeof(BITMAPFILEHEADER));
	file.Write(m_pDibInfo, sizeof(BITMAPINFOHEADER) + PaletteSize*sizeof(RGBQUAD));
	file.Write(m_pDibBits, size);
	//关闭文件
	file.Close();
}

int CMedicalImg::GetPixelRGB(int row, int col, int &r, int &g, int b)
{
	char *pDibBits = (char *)m_pDibBits;
	int index = (row - 1) * BytesPerline() + (col - 1) * GetBitsPerPixel();
	b = (int)(*(pDibBits + index + 0));
	g = (int)(*(pDibBits + index + 1));
	r = (int)(*(pDibBits + index + 2));

	return 0;
}

void CMedicalImg::UpdateRGB(char * imageBuffer, int deltaR, int deltaG, int deltaB)
{
	int index = 0;
	for (int i = 0; i < GetHeight(); i++)
	{
		for (int j = 0; j < GetWidth(); j++)
		{
			index = i * BytesPerline() + j * GetBitsPerPixel() / 8;
			imageBuffer[index] = abs((imageBuffer[index] + deltaB) % 255);
			imageBuffer[index + 1] = abs((imageBuffer[index + 1] + deltaG) %255);
			imageBuffer[index + 2] = abs((imageBuffer[index + 1] + deltaR) %255);
		}
	}
}
