# Microsoft Developer Studio Project File - Name="CGFramework" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=CGFramework - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "CGFramework.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "CGFramework.mak" CFG="CGFramework - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "CGFramework - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "CGFramework - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "CGFramework - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
F90=df.exe
# ADD BASE F90 /compile_only /nologo /warn:nofileopt /winapp
# ADD F90 /compile_only /nologo /warn:nofileopt /winapp
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "CGFramework - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
F90=df.exe
# ADD BASE F90 /check:bounds /compile_only /dbglibs /debug:full /nologo /traceback /warn:argument_checking /warn:nofileopt /winapp
# ADD F90 /check:bounds /compile_only /dbglibs /debug:full /nologo /traceback /warn:argument_checking /warn:nofileopt /winapp
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "CGFramework - Win32 Release"
# Name "CGFramework - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat;f90;for;f;fpp"
# Begin Source File

SOURCE=.\CGFramework.cpp
# End Source File
# Begin Source File

SOURCE=.\CGFramework.rc
# End Source File
# Begin Source File

SOURCE=.\CGFrameworkDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\CGFrameworkView.cpp
# End Source File
# Begin Source File

SOURCE=.\ControllerBase.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgPivot.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSelectController.cpp
# End Source File
# Begin Source File

SOURCE=.\Init.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\MyController.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=.\CGFramework.h
# End Source File
# Begin Source File

SOURCE=.\CGFrameworkDoc.h
# End Source File
# Begin Source File

SOURCE=.\CGFrameworkView.h
# End Source File
# Begin Source File

SOURCE=.\ControllerBase.h
# End Source File
# Begin Source File

SOURCE=.\DlgPivot.h
# End Source File
# Begin Source File

SOURCE=.\DlgSelectController.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\MyController.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\CGFramework.ico
# End Source File
# Begin Source File

SOURCE=.\res\CGFramework.rc2
# End Source File
# Begin Source File

SOURCE=.\res\CGFrameworkDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# End Group
# Begin Group "Utilities"

# PROP Default_Filter ".h"
# Begin Group "Shapes"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Utilities\Shape3D\Cuboid.h
# End Source File
# Begin Source File

SOURCE=.\Utilities\Shape3D\Rect3D.h
# End Source File
# Begin Source File

SOURCE=.\Utilities\Shape3D\Shadow.h
# End Source File
# Begin Source File

SOURCE=.\Utilities\Shape3D\SLine3D.h
# End Source File
# Begin Source File

SOURCE=.\Utilities\Shape3D\SPoint3D.h
# End Source File
# Begin Source File

SOURCE=.\Utilities\Shape3D\SurfaceHiddenCuboid.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\Utilities\Matrix4D.h
# End Source File
# Begin Source File

SOURCE=.\Utilities\Painter.h
# End Source File
# Begin Source File

SOURCE=.\Utilities\Painter3D.h
# End Source File
# Begin Source File

SOURCE=.\Utilities\Primitive2D.h
# End Source File
# Begin Source File

SOURCE=.\Utilities\Primitive3D.h
# End Source File
# Begin Source File

SOURCE=.\Utilities\ProjectPainter3D.h
# End Source File
# Begin Source File

SOURCE=.\Utilities\Shape3D.h
# End Source File
# Begin Source File

SOURCE=.\Utilities\Transform.h
# End Source File
# Begin Source File

SOURCE=.\Utilities\World3D.h
# End Source File
# End Group
# Begin Group "Utilities Impl"

# PROP Default_Filter ".cpp"
# Begin Group "Shape Impl"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Utilities\Shape3D\Cuboid.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\Utilities\Shape3D\Rect3D.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\Utilities\Shape3D\Shadow.cpp

!IF  "$(CFG)" == "CGFramework - Win32 Release"

!ELSEIF  "$(CFG)" == "CGFramework - Win32 Debug"

# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Utilities\Shape3D\SLine3D.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\Utilities\Shape3D\SPoint3D.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\Utilities\Shape3D\SurfaceHiddenCuboid.cpp

!IF  "$(CFG)" == "CGFramework - Win32 Release"

!ELSEIF  "$(CFG)" == "CGFramework - Win32 Debug"

# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# End Group
# Begin Source File

SOURCE=.\Utilities\Matrix4D.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\Utilities\Painter.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\Utilities\Painter3D.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\Utilities\Primitive3D.cpp

!IF  "$(CFG)" == "CGFramework - Win32 Release"

!ELSEIF  "$(CFG)" == "CGFramework - Win32 Debug"

# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Utilities\ProjectPainter3D.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\Utilities\Shape3D.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\Utilities\Transform.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\Utilities\World3D.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
