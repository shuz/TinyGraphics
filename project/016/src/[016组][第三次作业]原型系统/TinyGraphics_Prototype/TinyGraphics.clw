; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CModifyPerspectiveCamera
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "TinyGraphics.h"
LastPage=0

ClassCount=7
Class1=CTinyGraphicsApp
Class2=CTinyGraphicsDoc
Class3=CTinyGraphicsView
Class4=CMainFrame

ResourceCount=6
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Class5=CAboutDlg
Resource3=IDD_INSERT_CUBOID
Resource4=IDD_ABOUTBOX (English (U.S.))
Class6=CInsertCuboid
Resource5=IDR_MAINFRAME (English (U.S.))
Class7=CModifyPerspectiveCamera
Resource6=IDD_MODIFY_CAMERA

[CLS:CTinyGraphicsApp]
Type=0
HeaderFile=TinyGraphics.h
ImplementationFile=TinyGraphics.cpp
Filter=N

[CLS:CTinyGraphicsDoc]
Type=0
HeaderFile=TinyGraphicsDoc.h
ImplementationFile=TinyGraphicsDoc.cpp
Filter=N
LastObject=CTinyGraphicsDoc
BaseClass=CDocument
VirtualFilter=DC

[CLS:CTinyGraphicsView]
Type=0
HeaderFile=TinyGraphicsView.h
ImplementationFile=TinyGraphicsView.cpp
Filter=C
LastObject=ID_MENU_CAMERA_ADJUST
BaseClass=CView
VirtualFilter=VWC


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
LastObject=CMainFrame




[CLS:CAboutDlg]
Type=0
HeaderFile=TinyGraphics.cpp
ImplementationFile=TinyGraphics.cpp
Filter=D
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Class=CAboutDlg

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_PRINT
Command6=ID_FILE_PRINT_PREVIEW
Command7=ID_FILE_PRINT_SETUP
Command8=ID_FILE_MRU_FILE1
Command9=ID_APP_EXIT
Command10=ID_EDIT_UNDO
Command11=ID_EDIT_CUT
Command12=ID_EDIT_COPY
Command13=ID_EDIT_PASTE
Command14=ID_VIEW_TOOLBAR
Command15=ID_VIEW_STATUS_BAR
CommandCount=16
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command16=ID_APP_ABOUT

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
CommandCount=14
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE


[TB:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_APP_ABOUT
CommandCount=8

[MNU:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_PRINT
Command6=ID_FILE_PRINT_PREVIEW
Command7=ID_FILE_PRINT_SETUP
Command8=ID_FILE_MRU_FILE1
Command9=ID_APP_EXIT
Command10=ID_EDIT_UNDO
Command11=ID_EDIT_CUT
Command12=ID_EDIT_COPY
Command13=ID_EDIT_PASTE
Command14=ID_VIEW_TOOLBAR
Command15=ID_VIEW_STATUS_BAR
Command16=ID_MENU_INSERT_CUBOID
Command17=ID_MENU_CAMERA_ADJUST
Command18=ID_APP_ABOUT
CommandCount=18

[ACL:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
CommandCount=14

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_INSERT_CUBOID]
Type=1
Class=CInsertCuboid
ControlCount=14
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_EDIT_LENGTH,edit,1350631552
Control7=IDC_EDIT_WIDTH,edit,1350631552
Control8=IDC_EDIT_HEIGHT,edit,1350631552
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STATIC,static,1342308352
Control11=IDC_STATIC,static,1342308352
Control12=IDC_EDIT_X,edit,1350631552
Control13=IDC_EDIT_Y,edit,1350631552
Control14=IDC_EDIT_Z,edit,1350631552

[CLS:CInsertCuboid]
Type=0
HeaderFile=InsertCuboid.h
ImplementationFile=InsertCuboid.cpp
BaseClass=CDialog
Filter=D
LastObject=CInsertCuboid
VirtualFilter=dWC

[DLG:IDD_MODIFY_CAMERA]
Type=1
Class=CModifyPerspectiveCamera
ControlCount=26
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_EDIT_VRP_X,edit,1350631552
Control6=IDC_EDIT_VRP_Y,edit,1350631552
Control7=IDC_EDIT_VRP_Z,edit,1350631552
Control8=IDC_EDIT_VPN_X,edit,1350631552
Control9=IDC_EDIT_VPN_Y,edit,1350631552
Control10=IDC_EDIT_VPN_Z,edit,1350631552
Control11=IDC_STATIC,static,1342308352
Control12=IDC_EDIT_VUP_X,edit,1350631552
Control13=IDC_EDIT_VUP_Y,edit,1350631552
Control14=IDC_EDIT_VUP_Z,edit,1350631552
Control15=IDC_STATIC,static,1342308352
Control16=IDC_EDIT_COP_X,edit,1350631552
Control17=IDC_EDIT_COP_Y,edit,1350631552
Control18=IDC_EDIT_COP_Z,edit,1350631552
Control19=IDC_STATIC,static,1342308352
Control20=IDC_EDIT_U_MIN,edit,1350631552
Control21=IDC_EDIT_U_MAX,edit,1350631552
Control22=IDC_STATIC,static,1342308352
Control23=IDC_EDIT_V_MIN,edit,1350631552
Control24=IDC_EDIT_V_MAX,edit,1350631552
Control25=IDC_STATIC,static,1342308352
Control26=IDC_STATIC,static,1342308352

[CLS:CModifyPerspectiveCamera]
Type=0
HeaderFile=ModifyPerspectiveCamera.h
ImplementationFile=ModifyPerspectiveCamera.cpp
BaseClass=CDialog
Filter=D
LastObject=CModifyPerspectiveCamera
VirtualFilter=dWC

