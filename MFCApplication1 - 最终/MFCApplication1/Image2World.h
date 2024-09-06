// Image2World.h: interface for the CImage2World class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IMAGE2WORLD_H__29FF8A15_9F5F_4077_A2E6_0222965A690F__INCLUDED_)
#define AFX_IMAGE2WORLD_H__29FF8A15_9F5F_4077_A2E6_0222965A690F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#include "structdef.h"
#include "matrix.h"

class CImage2World  
{
public:
	CImage2World();
	virtual ~CImage2World();
	
public:
	int m_nCamIndex;
	
	void LoadParas(CString strFileName);
	
		//µ•µ„º∆À„
	void lGetXY(double r, double c, double &x, double &y);

	
private:
	double m_lr11, m_lr12, m_lr13;
	double m_lr21, m_lr22, m_lr23;
	double m_lr31, m_lr32, m_lr33;
	
	double m_wr11, m_wr12, m_wr13;
	double m_wr21, m_wr22, m_wr23;
	double m_wr31, m_wr32, m_wr33;
	
private:
	CMatrix lH3by3;
	CMatrix wH3by3;
	void Init();
};


//extern CImage2World  G_Image2World[10];

#endif // !defined(AFX_IMAGE2WORLD_H__29FF8A15_9F5F_4077_A2E6_0222965A690F__INCLUDED_)
