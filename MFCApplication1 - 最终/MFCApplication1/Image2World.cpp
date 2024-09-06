// Image2World.cpp: implementation of the CImage2World class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "math.h"
#include "Image2World.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CImage2World::CImage2World()
{
	m_lr11=0.0, m_lr12=0.0, m_lr13=0.0;
	m_lr21=0.0, m_lr22=0.0, m_lr23=0.0;
	m_lr31=0.0, m_lr32=0.0, m_lr33=0.0;

	m_wr11=0.0, m_wr12=0.0, m_wr13=0.0;
	m_wr21=0.0, m_wr22=0.0, m_wr23=0.0;
	m_wr31=0.0, m_wr32=0.0, m_wr33=0.0;
}

CImage2World::~CImage2World()
{

}

void CImage2World::Init()
{
	CMatrix matA(3,3);
	matA(0, 0)= m_lr11; matA(0, 1)= m_lr12; matA(0, 2)= m_lr13;
	matA(1, 0)= m_lr21;  matA(1, 1)= m_lr22;   matA(1, 2)= m_lr23;
	matA(2, 0)= m_lr31;  matA(2, 1)= m_lr32;    matA(2, 2)=m_lr33;

	matA.getInverse();
	lH3by3 = matA;

	CMatrix matB(3,3);
	matB(0, 0)= m_wr11; matB(0, 1)= m_wr12; matB(0, 2)= m_wr13;
	matB(1, 0)= m_wr21;  matB(1, 1)= m_wr22;   matB(1, 2)= m_wr23;
	matB(2, 0)= m_wr31;  matB(2, 1)= m_wr32;    matB(2, 2)=m_wr33;

	matB.getInverse();
	wH3by3 = matB;
}

void CImage2World::LoadParas(CString strFileName)
{
	char tempStr[255];
	char * stopstring;

	//HOMOMATRIX
	::GetPrivateProfileString("HOMOMATRIX", "r11", "0", tempStr, 80, strFileName);
	m_lr11 = strtod( tempStr, &stopstring);
	::GetPrivateProfileString("HOMOMATRIX", "r12", "0", tempStr, 80, strFileName);
	m_lr12 = strtod( tempStr, &stopstring);
	::GetPrivateProfileString("HOMOMATRIX", "r13", "0", tempStr, 80, strFileName);
	m_lr13 = strtod( tempStr, &stopstring);

	::GetPrivateProfileString("HOMOMATRIX", "r21", "0", tempStr, 80, strFileName);
	m_lr21 = strtod( tempStr, &stopstring);
	::GetPrivateProfileString("HOMOMATRIX", "r22", "0", tempStr, 80, strFileName);
	m_lr22 = strtod( tempStr, &stopstring);
	::GetPrivateProfileString("HOMOMATRIX", "r23", "0", tempStr, 80, strFileName);
	m_lr23 = strtod( tempStr, &stopstring);

	::GetPrivateProfileString("HOMOMATRIX", "r31", "0", tempStr, 80, strFileName);
	m_lr31 = strtod( tempStr, &stopstring);
	::GetPrivateProfileString("HOMOMATRIX", "r32", "0", tempStr, 80, strFileName);
	m_lr32 = strtod( tempStr, &stopstring);
	::GetPrivateProfileString("HOMOMATRIX", "r33", "0", tempStr, 80, strFileName);
	m_lr33 = strtod( tempStr, &stopstring);

	//WHOMOMATRIX
	::GetPrivateProfileString("WHOMOMATRIX", "r11", "0", tempStr, 80, strFileName);
	m_wr11 = strtod( tempStr, &stopstring);
	::GetPrivateProfileString("WHOMOMATRIX", "r12", "0", tempStr, 80, strFileName);
	m_wr12 = strtod( tempStr, &stopstring);
	::GetPrivateProfileString("WHOMOMATRIX", "r13", "0", tempStr, 80, strFileName);
	m_wr13 = strtod( tempStr, &stopstring);

	::GetPrivateProfileString("WHOMOMATRIX", "r21", "0", tempStr, 80, strFileName);
	m_wr21 = strtod( tempStr, &stopstring);
	::GetPrivateProfileString("WHOMOMATRIX", "r22", "0", tempStr, 80, strFileName);
	m_wr22 = strtod( tempStr, &stopstring);
	::GetPrivateProfileString("WHOMOMATRIX", "r23", "0", tempStr, 80, strFileName);
	m_wr23 = strtod( tempStr, &stopstring);

	::GetPrivateProfileString("WHOMOMATRIX", "r31", "0", tempStr, 80, strFileName);
	m_wr31 = strtod( tempStr, &stopstring);
	::GetPrivateProfileString("WHOMOMATRIX", "r32", "0", tempStr, 80, strFileName);
	m_wr32 = strtod( tempStr, &stopstring);
	::GetPrivateProfileString("WHOMOMATRIX", "r33", "0", tempStr, 80, strFileName);
	m_wr33 = strtod( tempStr, &stopstring);

	Init();
}

void CImage2World::lGetXY(double r, double c, 
						 double &x, double &y)
{
	CMatrix matRC(3, 1);
	matRC(0, 0)=r;	matRC(1, 0)=c;	matRC(2, 0)=1;
	
	CMatrix matXY;
	matXY = lH3by3*matRC;

	x = matXY(0, 0)/matXY(2, 0);
	y = matXY(1, 0)/matXY(2, 0);
}

