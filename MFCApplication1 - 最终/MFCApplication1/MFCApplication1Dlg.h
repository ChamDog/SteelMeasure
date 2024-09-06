#include<vector>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;
// MFCApplication1Dlg.h: 头文件
//

#pragma once


// CMFCApplication1Dlg 对话框
class CMFCApplication1Dlg : public CDialogEx
{
// 构造
public:
	CMFCApplication1Dlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCAPPLICATION1_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedOpenpictures();
	CStatic OriPicture01; CStatic* op1 = &OriPicture01;
	CStatic OriPicture02; CStatic* op2 = &OriPicture02;
	CStatic OriginImage09; CStatic* op9 = &OriginImage09;
	CStatic OriginImage08; CStatic* op8 = &OriginImage08;
	CStatic OriginImage07; CStatic* op7 = &OriginImage07;
	CStatic OriginImage03; CStatic* op3 = &OriginImage03;
	CStatic OriginImage04; CStatic* op4 = &OriginImage04;
	CStatic OriginImage05; CStatic* op5 = &OriginImage05;
	CStatic OriginImage06; CStatic* op6 = &OriginImage06;
	vector<CStatic*> OriginImages{op1,op2,op3,op4,op5,op6,op7,op8,op9};

	CStatic WIDTH;
	CStatic LENGTH;

	void ImagesShowByFilenames(const string& prefix, const string& suffix, int cnt);
	void ImagesShowByFilenamesVector_CStr(const vector<CString>& ImagesFilenamesVector_CStr, int cnt);
	void ImageShowByFilename(const CString& ImageFilename_CStr, CStatic& PictureControlVar);
	void ImageShowByFilename(const string& ImageFilename_Str, CStatic& PictureControlVar);
	void ImagesClear();


	int FindMode(const Mat& InputMat,int i);
	int FindSteel(vector<int>& ModeVector, vector<int>& TrueSteelMatsIndexVector);

	void ImageProcess(const Mat& InputMat, Mat& OutputMat, vector<Rect>& EffectiveRectsVector);
	void ImagesProcess(const vector<Mat>& InputMatsVector, vector<Mat>& OutputMatsVector, vector<int>& TrueSteelMatsIndexVector, vector<vector<Rect>>& AllEffectiveRectsVector);
	void Process_dotbase(Mat& InputMat);
	void Process_neighborbase(Mat& InputMat, Mat& OutputMat);
	void Process_outline(Mat& InputMat, Mat& OutputMat, vector<Rect>& EffectiveRectsVector);

	void DrawRects(vector<Mat>& Mats, const vector<vector<Rect>>& Rects, const vector<int> Index);
	void SaveOutlineImage(const vector<Mat>& Mats);

	double GetWidth(const vector<vector<Rect>>& Rects,const vector<int>TrueSteelRectIndex);
	double GetLength(const vector<vector<Rect>>& Rects, const vector<int>TrueSteelRectIndex);
	float CalIen(const vector<int> TrueSteelMatsIndexVector, int x1, int y1, int x2, int y2);
	void ShowData(double width, double length);
	void ShowMode(vector<int>& GrayMatsVector);

	CStatic MODE1; CStatic* pm1;
	CStatic MODE2; CStatic* pm2;
	CStatic MODE3; CStatic* pm3;
	CStatic MODE4; CStatic* pm4;
	CStatic MODE5; CStatic* pm5;
	CStatic MODE6; CStatic* pm6;
	CStatic MODE7; CStatic* pm7;
	CStatic MODE8; CStatic* pm8;
	CStatic MODE9; CStatic* pm9;
	vector<CStatic*>pModeVector{ pm1, pm2, pm3, pm4, pm5, pm6, pm7, pm8, pm9 };

	CStatic CAMINDEX;
	CStatic XCOORD;
	CStatic YCOORD;
	afx_msg void OnBnClickedButtonchange();
	CStatic god;
	CStatic SHOWRET;
	int m_CamIndex;
	int xcoord_c;
	int ycoord_c;
};
