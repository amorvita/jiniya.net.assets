// MazeDoc.h : interface of the CMazeDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAZEDOC_H__4DA4745E_2E98_414F_8471_91F552C53FB8__INCLUDED_)
#define AFX_MAZEDOC_H__4DA4745E_2E98_414F_8471_91F552C53FB8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMazeDoc : public CDocument
{
protected: // create from serialization only
	CMazeDoc();
	DECLARE_DYNCREATE(CMazeDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMazeDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMazeDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMazeDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAZEDOC_H__4DA4745E_2E98_414F_8471_91F552C53FB8__INCLUDED_)
