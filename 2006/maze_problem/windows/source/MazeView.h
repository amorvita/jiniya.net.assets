// MazeView.h : interface of the CMazeView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAZEVIEW_H__3C02A951_F2EB_41D6_AC02_10753E49D261__INCLUDED_)
#define AFX_MAZEVIEW_H__3C02A951_F2EB_41D6_AC02_10753E49D261__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "cmaze.h"

class CMazeView : public CFormView
{
protected: // create from serialization only
	CMazeView();
	DECLARE_DYNCREATE(CMazeView)

public:
	//{{AFX_DATA(CMazeView)
	enum { IDD = IDD_MAZE_FORM };
	CProgressCtrl	m_pProg;
	CSliderCtrl	m_pSld;
	CListCtrl	m_pPath;
	CEdit	m_pSeed;
	CEdit	m_pYsize;
	CEdit	m_pXsize;
	//}}AFX_DATA

// Attributes
public:
	CMazeDoc* GetDocument();
	CBitmap curImage, curback;
	CMaze maze;
	int curFrame, max_width, max_height;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMazeView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct
	virtual void OnDraw(CDC* pDC);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMazeView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMazeView)
	afx_msg void OnSetfocusXsize();
	afx_msg void OnKillfocusXsize();
	afx_msg void OnSetfocusYsize();
	afx_msg void OnKillfocusYsize();
	afx_msg void OnSetfocusSeed();
	afx_msg void OnKillfocusSeed();
	afx_msg void OnMake();
	afx_msg void OnFind();
	afx_msg void OnExit();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnStart();
	afx_msg void OnStop();
	afx_msg void OnPause();
	afx_msg void OnRestart();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in MazeView.cpp
inline CMazeDoc* CMazeView::GetDocument()
   { return (CMazeDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAZEVIEW_H__3C02A951_F2EB_41D6_AC02_10753E49D261__INCLUDED_)
