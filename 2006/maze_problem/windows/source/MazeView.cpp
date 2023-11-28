// MazeView.cpp : implementation of the CMazeView class
//

#include "stdafx.h"
#include "Maze.h"

#include "MazeDoc.h"
#include "MazeView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMazeView

IMPLEMENT_DYNCREATE(CMazeView, CFormView)

BEGIN_MESSAGE_MAP(CMazeView, CFormView)
	//{{AFX_MSG_MAP(CMazeView)
	ON_EN_SETFOCUS(IDC_XSIZE, OnSetfocusXsize)
	ON_EN_KILLFOCUS(IDC_XSIZE, OnKillfocusXsize)
	ON_EN_SETFOCUS(IDC_YSIZE, OnSetfocusYsize)
	ON_EN_KILLFOCUS(IDC_YSIZE, OnKillfocusYsize)
	ON_EN_SETFOCUS(IDC_SEED, OnSetfocusSeed)
	ON_EN_KILLFOCUS(IDC_SEED, OnKillfocusSeed)
	ON_BN_CLICKED(IDC_MAKE, OnMake)
	ON_BN_CLICKED(IDC_FIND, OnFind)
	ON_BN_CLICKED(IDC_EXIT, OnExit)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_START, OnStart)
	ON_BN_CLICKED(IDC_STOP, OnStop)
	ON_BN_CLICKED(IDC_PAUSE, OnPause)
	ON_BN_CLICKED(IDC_RESTART, OnRestart)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMazeView construction/destruction

CMazeView::CMazeView()
	: CFormView(CMazeView::IDD)
{
	//{{AFX_DATA_INIT(CMazeView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// TODO: add construction code here

}

CMazeView::~CMazeView()
{
}

void CMazeView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMazeView)
	DDX_Control(pDX, IDC_PROGRESS1, m_pProg);
	DDX_Control(pDX, IDC_SLIDER1, m_pSld);
	DDX_Control(pDX, IDC_LIST1, m_pPath);
	DDX_Control(pDX, IDC_SEED, m_pSeed);
	DDX_Control(pDX, IDC_YSIZE, m_pYsize);
	DDX_Control(pDX, IDC_XSIZE, m_pXsize);
	//}}AFX_DATA_MAP
}

BOOL CMazeView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	cs.lpszName = "Maze Problem(200024272 신영진)";

	return CFormView::PreCreateWindow(cs);
}

void CMazeView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

	RECT r;
	int x, y, width, height;
	GetDlgItem(IDC_SET)->GetWindowRect(&r);
	ScreenToClient(&r);
	width = r.right - r.left;
	height = r.bottom - r.top;

	m_pXsize.MoveWindow(r.left+5,r.top+15,(width-10)/3, (height-10)/3);
	m_pYsize.MoveWindow(r.left+5+(width-10)/3,r.top+15,(width-10)/3, (height-10)/3);
	m_pSeed.MoveWindow(r.left+5+(width-10)/3+(width-10)/3,r.top+15,(width-10)/3, (height-10)/3);
	
	GetDlgItem(IDC_MAKE)->MoveWindow(r.left+5,r.bottom-35,(width-10)/3, (height-10)/3);
	GetDlgItem(IDC_FIND)->MoveWindow(r.left+5+(width-10)/3,r.bottom-35,(width-10)/3, (height-10)/3);
	GetDlgItem(IDC_EXIT)->MoveWindow(r.left+5+(width-10)/3+(width-10)/3,r.bottom-35,(width-10)/3, (height-10)/3);

	GetDlgItem(IDC_SIMUL)->GetWindowRect(&r);
	ScreenToClient(&r);
	width = r.right - r.left;
	height = r.bottom - r.top;

	x = r.left + 5;
	y = r.top + 25;
	GetDlgItem(IDC_TIMEVAL)->MoveWindow(x,y,(width-30) * 0.3, (height-30) / 4);

	x += (width-30) * 0.3 + 5;
	y -= 5;
	m_pSld.MoveWindow(x,y,(width-30) * 0.7, (height-30) / 4);

	x = r.left + 5;
	y += (height-30)/4 + 10;
	GetDlgItem(IDC_INFO)->MoveWindow(x,y,width-20, (height-30)/4);

	x = r.left + 5;
	y += (height-30)/4 + 5;
	GetDlgItem(IDC_PR)->MoveWindow(x,y,(width-30) * 0.3, (height-30) / 8);

	x += (width-30) * 0.3 + 5;
//	y -= 5;
	m_pProg.MoveWindow(x,y,(width-30) * 0.7, (height-30) / 8);

	y += (height-30)/8 + 5;
	x = r.left + 5;
	GetDlgItem(IDC_START)->MoveWindow(x,y,(width-40) * 0.25, (height-30) / 4);

	x += (width-40) * 0.25 + 10;
	GetDlgItem(IDC_STOP)->MoveWindow(x,y,(width-40) * 0.25, (height-30) / 4);

	x += (width-40) * 0.25 + 10;
	GetDlgItem(IDC_PAUSE)->MoveWindow(x,y,(width-40) * 0.25, (height-30) / 4);

	x += (width-40) * 0.25 + 10;
	GetDlgItem(IDC_RESTART)->MoveWindow(x,y,(width-40) * 0.25, (height-30) / 4);

	m_pXsize.SetWindowText(_T("가로크기"));
	m_pYsize.SetWindowText(_T("세로크기"));
	m_pSeed.SetWindowText(_T("미로시드"));
	m_pXsize.SetReadOnly(TRUE);
	m_pYsize.SetReadOnly(TRUE);
	m_pSeed.SetReadOnly(TRUE);
	
	CButton *pBtn = (CButton *)GetDlgItem(IDC_MAKE);
	pBtn->SetFocus();

	curImage.LoadBitmap(IDB_BACK);

	LV_COLUMN lvcol;
	char *tag[4] = {"탐색 번호", "X 좌표", "Y 좌표", "방향"};
	int cwidth[4] = {60,60,60,100};
	int i;

	for(i=0;i<4;++i) {
		lvcol.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
		lvcol.fmt = LVCFMT_LEFT;
		lvcol.pszText = tag[i];
		lvcol.iSubItem = i;
		lvcol.cx = cwidth[i];
		m_pPath.InsertColumn(i, &lvcol);
	}

	max_width = 370;
	max_height = 375;
	m_pSld.SetRange(50, 450);
	m_pSld.SetPos(50);
	SetWindowText("미로찾기");
/*	CDC *pDC,curDC;
	pDC = GetDC();
	curImage.LoadBitmap(IDB_BACK);

	curDC.CreateCompatibleDC(pDC);
	curDC.SelectObject(&curImage);
	
	RECT r;
	GetDlgItem(IDC_MAZE)->GetClientRect(&r);
	ClientToScreen(&r);

	pDC->BitBlt(0,0,218,258,&curDC,r.left,r.top,SRCCOPY);

	ReleaseDC(pDC);
*/
}

/////////////////////////////////////////////////////////////////////////////
// CMazeView diagnostics

#ifdef _DEBUG
void CMazeView::AssertValid() const
{
	CFormView::AssertValid();
}

void CMazeView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CMazeDoc* CMazeView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMazeDoc)));
	return (CMazeDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMazeView message handlers

void CMazeView::OnSetfocusXsize() 
{
	// TODO: Add your control notification handler code here
	m_pXsize.SetReadOnly(FALSE);
	m_pXsize.SetWindowText(_T(""));
}

void CMazeView::OnKillfocusXsize() 
{
	// TODO: Add your control notification handler code here
	char buf[4096];

	m_pXsize.GetWindowText(buf, 4096);
	if(buf[0] == 0) {
		m_pXsize.SetWindowText(_T("가로크기"));
	}

	m_pXsize.SetReadOnly(TRUE);
}

void CMazeView::OnSetfocusYsize() 
{
	// TODO: Add your control notification handler code here
	m_pYsize.SetReadOnly(FALSE);	
	m_pYsize.SetWindowText(_T(""));
}

void CMazeView::OnKillfocusYsize() 
{
	// TODO: Add your control notification handler code here
	char buf[4096];

	m_pYsize.GetWindowText(buf, 4096);
	if(buf[0] == 0) {
		m_pYsize.SetWindowText(_T("세로크기"));
	}

	m_pYsize.SetReadOnly(TRUE);	
}

void CMazeView::OnSetfocusSeed() 
{
	// TODO: Add your control notification handler code here
	m_pSeed.SetReadOnly(FALSE);
	m_pSeed.SetWindowText(_T(""));
}

void CMazeView::OnKillfocusSeed() 
{
	// TODO: Add your control notification handler code here
	char buf[4096];

	m_pSeed.GetWindowText(buf, 4096);
	if(buf[0] == 0) {
		m_pSeed.SetWindowText(_T("미로시드"));
	}

	m_pSeed.SetReadOnly(TRUE);		
}

void CMazeView::OnMake() 
{
	// TODO: Add your control notification handler code here
	int xsize, ysize, seed;
	char buf[4096];

	m_pXsize.GetWindowText(buf, 4096);
	sscanf(buf, "%d", &xsize);

	m_pYsize.GetWindowText(buf, 4096);
	sscanf(buf, "%d", &ysize);

	m_pSeed.GetWindowText(buf, 4096);
	sscanf(buf, "%d", &seed);

	CString af;
	af.Format("%d %d %d", xsize, ysize, seed);

	if(xsize < 6 || ysize < 6)
		AfxMessageBox(_T("미로의 크기는 최소한 6x6이상이어야 합니다..."));
	else if(seed > xsize-2 || seed > ysize-2 || seed < 2)
		AfxMessageBox(_T("미로 시드의 갯수는 2에서 미로의 크기사이로 입력해 주세요..."));
	else {
		maze.resize_maze(xsize, ysize, seed);

//		CPen pen;
//		pen.CreatePen(PS_DOT, 1, RGB(255,0,0));
//		cdc.SelectObject(&pen);

		CBitmap wh, blk;
		CDC *pDC, cdc, w,b;

		pDC = GetDC();
		cdc.CreateCompatibleDC(pDC);
		cdc.SelectObject(&curImage);

		wh.LoadBitmap(IDB_WHDOT);
		w.CreateCompatibleDC(pDC);
		w.SelectObject(&wh);

		blk.LoadBitmap(IDB_BLKDOT);
		b.CreateCompatibleDC(pDC);
		b.SelectObject(&blk);

		maze.draw_maze(&cdc, &w, &b, 370,375);
		ReleaseDC(pDC);
		Invalidate(FALSE);

		GetDlgItem(IDC_FIND)->EnableWindow(TRUE);
		GetDlgItem(IDC_START)->EnableWindow(FALSE);
		GetDlgItem(IDC_INFO)->SetWindowText("길찾기를 눌러 탐색을 하시고 나면\n시뮬레이션 결과를 보실 수 있습니다...");
	}
}

void CMazeView::OnFind() 
{
	// TODO: Add your control notification handler code here
	char *msg[3] = {
		"메모리 할당에 실패하였습니다...",
		"미로를 빠져나갈 길이 존재하지 않습니다...",
		"미로를 성공적으로 탈출 하였습니다..."
	};

	m_pPath.DeleteAllItems();

	int rtn = maze.find_solution();

	LV_ITEM lvitem;
	char *pdir[9] = {"북쪽", "북동쪽", "동쪽", "동남쪽", "남쪽", "서남쪽", "서쪽", "북서쪽", "끝"};
	int i;

	lvitem.mask = LVIF_TEXT;

	char tmp[4096];
	for(i=0;i<maze.stk.get_size();++i) {
		lvitem.iItem = i;
		lvitem.iSubItem = 0;
		sprintf(tmp, "%d", i);
		lvitem.pszText = tmp;
		m_pPath.InsertItem(&lvitem);
		
		lvitem.iItem = i;
		lvitem.iSubItem = 1;
		sprintf(tmp, "%d", maze.stk[i].get_curpos().get_x());
		lvitem.pszText = tmp;
		m_pPath.SetItem(&lvitem);

		lvitem.iItem = i;
		lvitem.iSubItem = 2;
		sprintf(tmp, "%d", maze.stk[i].get_curpos().get_y());;
		lvitem.pszText = tmp;
		m_pPath.SetItem(&lvitem);

		lvitem.iItem = i;
		lvitem.iSubItem = 3;
		
		sprintf(tmp, "%s", pdir[maze.stk[i].get_dir()]);
		lvitem.pszText = tmp;
		m_pPath.SetItem(&lvitem);
	}

	CPen pen(PS_SOLID, 2, RGB(255,0,0));

	CBitmap wh, blk;
	CDC *pDC, cdc,b,w;
	pDC = GetDC();
	cdc.CreateCompatibleDC(pDC);
	cdc.SelectObject(&curImage);
	cdc.SelectObject(&pen);

	wh.LoadBitmap(IDB_WHDOT);
	w.CreateCompatibleDC(pDC);
	w.SelectObject(&wh);

	blk.LoadBitmap(IDB_BLKDOT);
	b.CreateCompatibleDC(pDC);
	b.SelectObject(&blk);

	maze.draw_maze(&cdc, &w, &b, 370,375);

	float effi;
	char buf[4096];
//	if(maze._back_track >= maze._total_visit)
//		eff = 0;
//	else
		effi = (float(maze._total_visit) / (maze._back_track+maze._total_visit)) * 100;

	sprintf(buf, "총 탐색수 : %02d\t재 탐색수 : %02d\n탐색 효율 : %02.2f(%%)", maze._total_visit, maze._back_track, effi);
	GetDlgItem(IDC_INFO)->SetWindowText(buf);

	ReleaseDC(pDC);
	AfxMessageBox(msg[rtn+1]);
	Invalidate(FALSE);
	GetDlgItem(IDC_FIND)->EnableWindow(FALSE);
	GetDlgItem(IDC_START)->EnableWindow(TRUE);
}

void CMazeView::OnExit() 
{
	// TODO: Add your control notification handler code here
	exit(0);
}

void CMazeView::OnDraw(CDC* pDC) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CDC cdc;
	cdc.CreateCompatibleDC(pDC);

	cdc.SelectObject(&curImage);

//	RECT r;
//	GetDlgItem(IDC_MAZE)->GetClientRect(&r);
//	ClientToScreen(&r);
//	ScreenToClient(&r);

//	CString af;
//	af.Format("%d", r.bottom);
//	AfxMessageBox(af);
	pDC->BitBlt(18,26,370,375,&cdc,0,0,SRCCOPY);
	
}

void CMazeView::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	static int jx, jy;
	int mx, my;
	int px, py;

	CBitmap bluedot, whdot;
	CDC *pDC, cdc, wdc, bdc;

	if(curFrame >= maze.lst.get_size()) {
		pDC = GetDC();
		cdc.CreateCompatibleDC(pDC);
		cdc.SelectObject(&curImage);

		whdot.LoadBitmap(IDB_WHDOT);
		wdc.CreateCompatibleDC(pDC);
		wdc.SelectObject(&whdot);

		cdc.BitBlt(jx,jy,5,5,&wdc,0,0,SRCCOPY);
		pDC->BitBlt(18,26,370,375,&cdc,0,0,SRCCOPY);
		ReleaseDC(pDC);

		CButton *pBtn = (CButton *)GetDlgItem(IDC_START);
		pBtn->EnableWindow(TRUE);
		GetDlgItem(IDC_PAUSE)->EnableWindow(FALSE);
		GetDlgItem(IDC_STOP)->EnableWindow(FALSE);
		GetDlgItem(IDC_RESTART)->EnableWindow(FALSE);
		GetDlgItem(IDC_MAKE)->EnableWindow(TRUE);

		KillTimer(1);
		return;
	}

	pDC = GetDC();
	cdc.CreateCompatibleDC(pDC);
	cdc.SelectObject(&curImage);

	bluedot.LoadBitmap(IDB_BLUDOT);
	bdc.CreateCompatibleDC(pDC);
	bdc.SelectObject(&bluedot);

	whdot.LoadBitmap(IDB_WHDOT);
	wdc.CreateCompatibleDC(pDC);
	wdc.SelectObject(&whdot);

	px = int(max_width / (maze._maxx-2));
	py = int(max_height / (maze._maxy-2));

	mx = (maze.lst.get_at(curFrame).get_curpos().get_x()-1) * px + px/2;
	my = (maze.lst.get_at(curFrame).get_curpos().get_y()-1) * py + py/2;

	if(curFrame != 0)
		cdc.BitBlt(jx,jy,5,5,&wdc,0,0,SRCCOPY);

	cdc.BitBlt(mx,my,5,5,&bdc,0,0,SRCCOPY);

	pDC->BitBlt(18,26,370,375,&cdc,0,0,SRCCOPY);
	ReleaseDC(pDC);

	//Invalidate(FALSE);
	jx = mx;
	jy = my;
	m_pProg.SetPos(curFrame);
	++curFrame;

	CFormView::OnTimer(nIDEvent);
}

void CMazeView::OnStart() 
{
	// TODO: Add your control notification handler code here
	int tk = m_pSld.GetPos();
	CDC *pDC, cdc, odc;
	pDC = GetDC();
	odc.CreateCompatibleDC(pDC);
	odc.SelectObject(&curImage);

	cdc.CreateCompatibleDC(pDC);
	cdc.SelectObject(&curback);

	cdc.BitBlt(0,0,max_width,max_height,&odc,0,0,SRCCOPY);
	ReleaseDC(pDC);

	curFrame = 0;
	CButton *pBtn = (CButton *)GetDlgItem(IDC_START);
	pBtn->EnableWindow(FALSE);
	GetDlgItem(IDC_MAKE)->EnableWindow(FALSE);
	GetDlgItem(IDC_STOP)->EnableWindow(TRUE);
	GetDlgItem(IDC_PAUSE)->EnableWindow(TRUE);

	m_pProg.SetRange(0, maze.lst.get_size());
	m_pProg.SetPos(0);
	SetTimer(1, tk, NULL);
}

void CMazeView::OnStop() 
{
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_STOP)->EnableWindow(FALSE);
	GetDlgItem(IDC_PAUSE)->EnableWindow(FALSE);
	GetDlgItem(IDC_RESTART)->EnableWindow(FALSE);
	GetDlgItem(IDC_START)->EnableWindow(TRUE);
	m_pProg.SetPos(0);
	curFrame = maze.lst.get_size() + 1;
}

void CMazeView::OnPause() 
{
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_PAUSE)->EnableWindow(FALSE);
	GetDlgItem(IDC_STOP)->EnableWindow(FALSE);
	GetDlgItem(IDC_RESTART)->EnableWindow(TRUE);
	KillTimer(1);
}

void CMazeView::OnRestart() 
{
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_PAUSE)->EnableWindow(TRUE);
	GetDlgItem(IDC_RESTART)->EnableWindow(FALSE);

	int tk = m_pSld.GetPos();
	SetTimer(1, tk, NULL);	
}
