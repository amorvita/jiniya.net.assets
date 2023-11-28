; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMazeView
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Maze.h"
LastPage=0

ClassCount=5
Class1=CMazeApp
Class2=CMazeDoc
Class3=CMazeView
Class4=CMainFrame

ResourceCount=7
Resource1=IDR_MAINFRAME
Resource2=IDD_ABOUTBOX
Class5=CAboutDlg
Resource7=IDD_MAZE_FORM

[CLS:CMazeApp]
Type=0
HeaderFile=Maze.h
ImplementationFile=Maze.cpp
Filter=N

[CLS:CMazeDoc]
Type=0
HeaderFile=MazeDoc.h
ImplementationFile=MazeDoc.cpp
Filter=N

[CLS:CMazeView]
Type=0
HeaderFile=MazeView.h
ImplementationFile=MazeView.cpp
Filter=D
LastObject=CMazeView
BaseClass=CFormView
VirtualFilter=VWC


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T




[CLS:CAboutDlg]
Type=0
HeaderFile=Maze.cpp
ImplementationFile=Maze.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_MRU_FILE1
Command6=ID_APP_EXIT
Command7=ID_EDIT_UNDO
Command8=ID_EDIT_CUT
Command9=ID_EDIT_COPY
Command10=ID_EDIT_PASTE
Command11=ID_VIEW_STATUS_BAR
Command12=ID_APP_ABOUT
CommandCount=12

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_UNDO
Command5=ID_EDIT_CUT
Command6=ID_EDIT_COPY
Command7=ID_EDIT_PASTE
Command8=ID_EDIT_UNDO
Command9=ID_EDIT_CUT
Command10=ID_EDIT_COPY
Command11=ID_EDIT_PASTE
Command12=ID_NEXT_PANE
Command13=ID_PREV_PANE
CommandCount=13

[DLG:IDD_MAZE_FORM]
Type=1
Class=CMazeView
ControlCount=20
Control1=IDC_SET,button,1342177287
Control2=IDC_XSIZE,edit,1350631552
Control3=IDC_YSIZE,edit,1350631552
Control4=IDC_SEED,edit,1350631552
Control5=IDC_MAKE,button,1342242817
Control6=IDC_FIND,button,1476460544
Control7=IDC_SIMUL,button,1342177287
Control8=IDC_SLIDER1,msctls_trackbar32,1342242832
Control9=IDC_START,button,1476460544
Control10=IDC_STOP,button,1476460544
Control11=IDC_PAUSE,button,1476460544
Control12=IDC_RESTART,button,1476460544
Control13=IDC_PR,static,1342308352
Control14=IDC_PROGRESS1,msctls_progress32,1350565888
Control15=IDC_LIST1,SysListView32,1350631425
Control16=IDC_STATIC,static,1342308354
Control17=IDC_EXIT,button,1342242816
Control18=IDC_MAZE,button,1342177287
Control19=IDC_TIMEVAL,static,1342308352
Control20=IDC_INFO,static,1342308354

