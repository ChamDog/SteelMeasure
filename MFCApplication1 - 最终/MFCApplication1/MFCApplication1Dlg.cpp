
// MFCApplication1Dlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"
#include "afxdialogex.h"
#include "Image2World.h"
#include<string>
#include<vector>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;

CImage2World G_Image2World[10];

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCApplication1Dlg 对话框



CMFCApplication1Dlg::CMFCApplication1Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCAPPLICATION1_DIALOG, pParent)
	, m_CamIndex(0)
	, xcoord_c(0)
	, ycoord_c(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_OriginImage01, OriPicture01);
	DDX_Control(pDX, IDC_OriginImage02, OriPicture02);
	DDX_Control(pDX, IDC_OriginImage09, OriginImage09);
	DDX_Control(pDX, IDC_OriginImage08, OriginImage08);
	DDX_Control(pDX, IDC_OriginImage07, OriginImage07);
	DDX_Control(pDX, IDC_OriginImage03, OriginImage03);
	DDX_Control(pDX, IDC_OriginImage04, OriginImage04);
	DDX_Control(pDX, IDC_OriginImage05, OriginImage05);
	DDX_Control(pDX, IDC_OriginImage06, OriginImage06);
	DDX_Control(pDX, IDC_WIDTH, WIDTH);
	DDX_Control(pDX, IDC_LENGTH, LENGTH);
	DDX_Control(pDX, IDC_MODE1, MODE1);
	DDX_Control(pDX, IDC_MODE2, MODE2);
	DDX_Control(pDX, IDC_MODE3, MODE3);
	DDX_Control(pDX, IDC_MODE4, MODE4);
	DDX_Control(pDX, IDC_MODE5, MODE5);
	DDX_Control(pDX, IDC_MODE6, MODE6);
	DDX_Control(pDX, IDC_MODE7, MODE7);
	DDX_Control(pDX, IDC_MODE8, MODE8);
	DDX_Control(pDX, IDC_MODE9, MODE9);
	DDX_Control(pDX, IDC_CAMINDEX, CAMINDEX);
	DDX_Control(pDX, IDC_XCOORD, XCOORD);
	DDX_Control(pDX, IDC_YCOORD, YCOORD);
	DDX_Control(pDX, IDC_STATIC_SHOWRET, SHOWRET);
	DDX_Text(pDX, IDC_EDIT_CAM, m_CamIndex);
	DDX_Text(pDX, IDC_EDIT_X, xcoord_c);
	DDX_Text(pDX, IDC_EDIT_Y, ycoord_c);
}

BEGIN_MESSAGE_MAP(CMFCApplication1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_OpenPictures, &CMFCApplication1Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTONCHANGE, &CMFCApplication1Dlg::OnBnClickedButtonchange)
END_MESSAGE_MAP()


// CMFCApplication1Dlg 消息处理程序

BOOL CMFCApplication1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	CString strpath = "S:/study/程设/calibrate_para_hot/CalibResults333-image";
	CString fname;

	for (int i = 0; i < 10; i++)
	{
		fname.Format("%d", i);
		fname = strpath + fname;
		fname = fname + ".ini";
		G_Image2World[i].LoadParas(fname);
	}

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCApplication1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFCApplication1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFCApplication1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCApplication1Dlg::OnBnClickedButton1()
{
	//PART I:选择图片/

	TCHAR szFilter[] = _T("bmp文件(*.bmp)|*.bmp|JPEG文件(*.jpg)|*.jpg||");
	//文件类型说明和扩展名间用 | 分隔，每种文件类型间用 | 分隔，末尾用 || 指明。
	CFileDialog fileDlg(TRUE, NULL, NULL, OFN_ALLOWMULTISELECT, szFilter, this);

	//CFileDialog构造一个CFileDialog对象
	/*
	第1个参数：TRUE为打开文件对话框；FALSE为保存文件对话框
	2：  指定默认的文件扩展名。
	3：指定默认的文件名。
	4：指明一些特定风格。
	5：是最重要的一个参数，它指明可供选择的文件类型和相应的扩展名。
	6：为父窗口指针。
	*/

	if (fileDlg.DoModal() != IDOK)     //没有点确定按钮
		return;
	POSITION pos = fileDlg.GetStartPosition();

	//POSITION就是MFC的iterator，
	//GetStartPosition是取第一个iterator，
	//GetNextAssoc是取出当前元素然后向后移动iterator

	vector<CString> OriginImagesFilenamesVector_CStr;
	vector<Mat>     OriginMatsVector;

	while (pos != NULL)
	{
		int nCount = 0;
		CString szPathName = fileDlg.GetNextPathName(pos);
		string ss(szPathName);
		//CString CFileDialog::GetNextPathName( POSITION& pos ) 对于选择了多个文件的情况得到下一个文件位置，并同时返回当前文件名。但必须已经调用过POSITION CFileDialog::GetStartPosition( )来得到最初的POSITION变量。
		TRACE(_T("%s/n"), szPathName);
		nCount++;
		//将图片地址保存到vector<CString> OriginImagesFilenamesVector_CStr容器中
		//将图片保存到vector<Mat> Mats_origin容器中
		if (OriginImagesFilenamesVector_CStr.size() < 9)//最多取九张
		{
			OriginImagesFilenamesVector_CStr.push_back(szPathName);
			OriginMatsVector.push_back(imread(ss));
		}
	}

	//先显示原始图片
	ImagesClear();//清空所有图片
	ImagesShowByFilenamesVector_CStr(OriginImagesFilenamesVector_CStr, OriginImagesFilenamesVector_CStr.size());

	//PART II:处理
	vector<vector<Rect>>  AllEffectiveRectsVector(OriginMatsVector.size());//存储所有图片中的有效矩形
	vector<int>   ModeVector(OriginMatsVector.size());
	vector<Mat>   ProcessedMatsVector(OriginMatsVector.size());//存储处理后的图片
	vector<int>   TrueSteelMatsIndexVector(2);//存完整钢板图片的索引

	for (int i = 0; i < OriginMatsVector.size(); i++)
	{
		ModeVector[i] = FindMode(OriginMatsVector[i],i);
	}//模式数组,此后GrayMatsVector被释放



	int isComplete = FindSteel(ModeVector, TrueSteelMatsIndexVector);
	ShowMode(ModeVector);

	if (isComplete)
	{
		ImagesProcess(OriginMatsVector, ProcessedMatsVector, TrueSteelMatsIndexVector, AllEffectiveRectsVector);
		DrawRects(OriginMatsVector, AllEffectiveRectsVector,TrueSteelMatsIndexVector);
		SaveOutlineImage(OriginMatsVector);
		ImagesShowByFilenames("ProcessedSteelImageOutline0", ".png", OriginMatsVector.size());

		Rect LeftRect = AllEffectiveRectsVector[TrueSteelMatsIndexVector[0]][0];
		Rect RightRect = AllEffectiveRectsVector[TrueSteelMatsIndexVector[1]][0];
		int	x1 = LeftRect.x, y1 = RightRect.y;
		int x2 = RightRect.x + RightRect.width, y2 = RightRect.y + RightRect.height;

		CalIen(TrueSteelMatsIndexVector, x1, y1, x2, y2);

		ShowData(GetWidth(AllEffectiveRectsVector,TrueSteelMatsIndexVector), GetLength(AllEffectiveRectsVector,TrueSteelMatsIndexVector));
	}
}

void CMFCApplication1Dlg::OnBnClickedOpenpictures()
{
}

void CMFCApplication1Dlg::ImagesShowByFilenames(const string& prefix, const string& suffix,int cnt)
{
	for (int i = 0; i < cnt; i++)
	{
		string filename = prefix + to_string(i + 1) + suffix;
		ImageShowByFilename(filename, *OriginImages[i]);
	}
}

void CMFCApplication1Dlg::ImagesShowByFilenamesVector_CStr(const vector<CString>& ImagesFilenamesVector_CStr, int cnt)
{
	for (int i = 0; i < cnt; i++)
	{
		ImageShowByFilename(ImagesFilenamesVector_CStr[i], *OriginImages[i]);
	}
}


void CMFCApplication1Dlg::ImageShowByFilename(const CString& ImageFilename_CStr, CStatic& PictureControlVar)
{
	//O1
	CImage image;//图片对象
	image.Load(ImageFilename_CStr);//加载
	CRect rectControl;//存尺寸信息
	PictureControlVar.GetClientRect(rectControl);//获取尺寸信息
	CDC* pDc = PictureControlVar.GetDC();//获取与图片硬件相关DC
	image.Draw(pDc->m_hDC, rectControl);//绘制
	image.Destroy();//销毁
	PictureControlVar.ReleaseDC(pDc);//释放指针
}

void CMFCApplication1Dlg::ImageShowByFilename(const string& ImageFilename_Str, CStatic& PictureControlVar)
{
	//O1
	CString ImageFilename_CStr(ImageFilename_Str.c_str());
	ImageShowByFilename(ImageFilename_CStr, PictureControlVar);
}



void CMFCApplication1Dlg::ImagesClear()
{
	for (int i = 0; i < 9; i++)
	{
		OriginImages[i]->SetBitmap(NULL);
	}
	this->RedrawWindow();
}


int CMFCApplication1Dlg::FindMode(const Mat& InputMat,int i)
{
	int m_nCurCamreno = i;

	Mat gray_image, gaublur_image, bi_image;
	cvtColor(InputMat, gray_image, COLOR_RGB2GRAY);
	GaussianBlur(gray_image, gaublur_image, Size(3, 3), 0);
	threshold(gaublur_image, bi_image, 0, 255, THRESH_OTSU);

	int ret = 0;
	int roiHi = 5;
	int startcol = 10;
	int rowoft = 20;
	if (m_nCurCamreno == 0)
		rowoft = 88;
	int endcol = bi_image.cols - rowoft;

	Rect LeftRoi(startcol - roiHi, bi_image.rows / 2 - roiHi, 2 * roiHi, 2 * roiHi);
	Rect RightRoi(endcol - roiHi, bi_image.rows / 2 - roiHi, 2 * roiHi, 2 * roiHi);


	Mat LeftRoiimg = bi_image(LeftRoi);
	Mat RightRoiimg = bi_image(RightRoi);

	cv::Scalar fleft_mu = cv::mean(LeftRoiimg);
	double dLeftmu = fleft_mu[0];

	cv::Scalar right_mu = cv::mean(RightRoiimg);
	double dRightmu = right_mu[0];

	if (dLeftmu > 150 && dRightmu > 150)
	{
		ret = 2;
	}
	else if (dLeftmu >150 && dRightmu < 80)
	{
		ret = 3;

	}
	else if (dLeftmu < 80 && dRightmu >150)
	{
		ret = 1;

	}
	else
	{
		ret = 0;

	}
	return ret;
}

int CMFCApplication1Dlg::FindSteel(vector<int>& ModeVector, vector<int>& TrueSteelMatsIndexVector)
{
	int cnt = ModeVector.size();
	int i, j, find = 0;
	for (i = 0; i < cnt; i++)
	{
		if (ModeVector[i] == 1)
		{
			for (int j = i + 1; j < cnt; j++)
			{
				if (ModeVector[j] == 1) { break; }
				if (ModeVector[j] == 3)
				{
					TrueSteelMatsIndexVector[0] = i;
					TrueSteelMatsIndexVector[1] = j;
					find = 1;
					break;
				}
			}
		}
		if (find == 1) { break; }
	}
	return find;
}


void CMFCApplication1Dlg::ImageProcess(const Mat& InputMat, Mat& OutputMat, vector<Rect>& EffectiveRectsVector)
{
	Mat pImage_fst(InputMat), pImage_fst2, pImage_sec, pImage_trd;
	Process_dotbase(pImage_fst);
	Process_neighborbase(pImage_fst, pImage_fst2);
	pImage_sec = pImage_fst2;
	pImage_trd.create(pImage_sec.size(), CV_8UC3);//定义三通道轮廓提取图像
	Process_outline(pImage_sec, pImage_trd, EffectiveRectsVector);
	OutputMat = pImage_trd;
}

void CMFCApplication1Dlg::ImagesProcess(const vector<Mat>& InputMatsVector, vector<Mat>& OutputMatsVector, vector<int>& TrueSteelMatsIndexVector, vector<vector<Rect>>& AllEffectiveRectsVector)
{
	for (int i = TrueSteelMatsIndexVector[0]; i <= TrueSteelMatsIndexVector[1]; i++)
	{
		ImageProcess(InputMatsVector[i], OutputMatsVector[i], AllEffectiveRectsVector[i]);
	}
}


void CMFCApplication1Dlg::Process_dotbase(Mat& InputMat)
{
	// 亮度变换
	for (int y = 0; y < InputMat.rows; y++) {
		for (int x = 0; x < InputMat.cols; x++) {
			for (int c = 0; c < InputMat.channels(); c++) {
				InputMat.at<Vec3b>(y, x)[c] = saturate_cast<uchar>(InputMat.at<Vec3b>(y, x)[c] - 50);
			}
		}
	}
}

void CMFCApplication1Dlg::Process_neighborbase(Mat& InputMat,Mat& OutputMat)//滤波
{
	Mat gray,gaublur_image,bi_image;
	cvtColor(InputMat, gray, COLOR_RGB2GRAY);//灰
	threshold(gray, bi_image, 0, 255, THRESH_OTSU);//二值
	GaussianBlur(bi_image, gaublur_image, Size(3, 3), 0);
	OutputMat = gaublur_image;
}


void CMFCApplication1Dlg::Process_outline(Mat& InputMat, Mat& OutputMat,vector<Rect>& EffectiveRects)
{
	//Mat canny;
	//Canny(InputMat, canny, 50, 200);

	//轮廓发现与绘制
	vector<vector<Point>>contours;//轮廓
	vector<Vec4i> hierarchy;
	findContours(InputMat, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_NONE);
	//绘制轮廓
	drawContours(OutputMat, contours, -1, Scalar(0, 80, 0));

	//寻找轮廓的外接矩形
	for (int n = 0; n < contours.size() && contours[n].size()>10; n++)
	{
		Rect rect = boundingRect(contours[n]);
		if (!rect.empty() && rect.height > 200 && rect.height < 450) { EffectiveRects.push_back(rect); }
		rectangle(OutputMat, rect, Scalar(80, 0, 80), 2, 8, 0);
	}
}

void CMFCApplication1Dlg::DrawRects(vector<Mat>& Mats, const vector<vector<Rect>>& Rects,const vector<int> Index)
{
	for (int i = Index[0]; i <= Index[1]; i++)
	{
		for (int j = 0; j < Rects[i].size(); j++)
		{
			rectangle(Mats[i], Rects[i][j], Scalar(0, 0, 255), 10, 8, 0);
		}
	}
}

void CMFCApplication1Dlg::SaveOutlineImage(const vector<Mat>& Mats)
{
	int cnt = Mats.size();
	for (int i = 0; i < cnt; ++i) 
	{
		string filename = "ProcessedSteelImageOutline0" + to_string(i + 1) + ".png";
		imwrite(filename, Mats[i]);
	}

}

double CMFCApplication1Dlg::GetWidth(const vector<vector<Rect>>& Rects, const vector<int>TrueSteelRectIndexVector)
{
	double WidthSum = 0;
	int cnt = 0;
	for (int n = TrueSteelRectIndexVector[0]; n < TrueSteelRectIndexVector[1]; n++)
	{
		if (!Rects[n].empty())
		{
			cnt++;
			WidthSum += Rects[n][0].height;
		}
	}
	return WidthSum/cnt;
}

double CMFCApplication1Dlg::GetLength(const vector<vector<Rect>>& Rects, const vector<int>TrueSteelRectIndexVector)
{
	double LengthSum = 0;
	for (int n = TrueSteelRectIndexVector[0]; n < TrueSteelRectIndexVector[1]; n++)
	{
		if (!Rects[n].empty())
		{
			LengthSum += Rects[n][0].width;
		}
	}
	return LengthSum;
}

float CMFCApplication1Dlg::CalIen(const vector<int> TrueSteelMatsIndexVector, int x1, int y1, int x2, int y2)
{
	float flen = 0;
	float fwid = 0;

	Point pt_c[3];
	Point2i pt_w[3];
	int CamIndex[3] = { 0 };
	bool bfind = true;

	pt_c[0].x = x1/1.0; pt_c[0].y = y1/1.0;
	pt_c[1].x = x2/1.0; pt_c[1].y = y2/1.0;
	CamIndex[1] = TrueSteelMatsIndexVector[1];//右边缘
	CamIndex[0] = TrueSteelMatsIndexVector[0];//左边缘

	if (bfind)
	{
		double dr = 0;
		double dc = 0;
		double x;
		double y;

		for (int i = 0; i < 2; i++)
		{
			dr = pt_c[i].x;
			dc = pt_c[i].y;
			G_Image2World[CamIndex[i] + 1].lGetXY(dr, dc, x, y);
			pt_w[i].x = x;
			pt_w[i].y = y;

		}

		flen = fabs(pt_w[0].x - pt_w[1].x);
		fwid = fabs(pt_w[0].y - pt_w[1].y);


	}

	CString str;
	str.Format("len=%.2f,wid=%.2f", flen, fwid);

	CWnd* pwnd = GetDlgItem(IDC_STATIC_SHOWRET);

	pwnd->SetWindowTextA(str);

	return flen;
}

void CMFCApplication1Dlg::ShowData(double width, double length)
{
	CString StrWidth;
	StrWidth.Format(_T("%.3f"), width);
	SetDlgItemText(IDC_WIDTH, StrWidth);

	CString StrLength;
	StrLength.Format(_T("%.3f"), length);
	SetDlgItemText(IDC_LENGTH, StrLength);
}

void CMFCApplication1Dlg::ShowMode(vector<int>& ModeVector)
{
	int cnt = ModeVector.size();
	vector<CString> StrMode(cnt);
	if (cnt >= 1) { StrMode[0].Format(_T("%d"), ModeVector[0]); SetDlgItemText(IDC_MODE1, StrMode[0]); }
	if (cnt >= 2) { StrMode[1].Format(_T("%d"), ModeVector[1]); SetDlgItemText(IDC_MODE2, StrMode[1]); }
	if (cnt >= 3) { StrMode[2].Format(_T("%d"), ModeVector[2]); SetDlgItemText(IDC_MODE3, StrMode[2]); }
	if (cnt >= 4) { StrMode[3].Format(_T("%d"), ModeVector[3]); SetDlgItemText(IDC_MODE4, StrMode[3]); }
	if (cnt >= 5) { StrMode[4].Format(_T("%d"), ModeVector[4]); SetDlgItemText(IDC_MODE5, StrMode[4]); }
	if (cnt >= 6) { StrMode[5].Format(_T("%d"), ModeVector[5]); SetDlgItemText(IDC_MODE6, StrMode[5]); }
	if (cnt >= 7) { StrMode[6].Format(_T("%d"), ModeVector[6]); SetDlgItemText(IDC_MODE7, StrMode[6]); }
	if (cnt >= 8) { StrMode[7].Format(_T("%d"), ModeVector[7]); SetDlgItemText(IDC_MODE8, StrMode[7]); }
	if (cnt >= 9) { StrMode[8].Format(_T("%d"), ModeVector[8]); SetDlgItemText(IDC_MODE9, StrMode[8]); }
}








void CMFCApplication1Dlg::OnBnClickedButtonchange()
{//坐标变换函数
	UpdateData(TRUE);
	if ((m_CamIndex >= 1) && (m_CamIndex <= 9)&&(xcoord_c>=0)&& (xcoord_c <= 768)&&(ycoord_c>=0) && (ycoord_c <= 576))
	{
		double x_w, y_w;
		G_Image2World[m_CamIndex].lGetXY(xcoord_c, ycoord_c, x_w, y_w);
		xcoord_c = x_w;
		ycoord_c = y_w;
		UpdateData(FALSE);
	}
}
