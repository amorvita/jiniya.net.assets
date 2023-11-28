// MazeDoc.cpp : implementation of the CMazeDoc class
//

#include "stdafx.h"
#include "Maze.h"

#include "MazeDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMazeDoc

IMPLEMENT_DYNCREATE(CMazeDoc, CDocument)

BEGIN_MESSAGE_MAP(CMazeDoc, CDocument)
	//{{AFX_MSG_MAP(CMazeDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMazeDoc construction/destruction

CMazeDoc::CMazeDoc()
{
	// TODO: add one-time construction code here

}

CMazeDoc::~CMazeDoc()
{
}

BOOL CMazeDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMazeDoc serialization

void CMazeDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CMazeDoc diagnostics

#ifdef _DEBUG
void CMazeDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMazeDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMazeDoc commands
