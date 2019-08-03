# Microsoft Developer Studio Project File - Name="TinyGraphics" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=TinyGraphics - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "TinyGraphics.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "TinyGraphics.mak" CFG="TinyGraphics - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "TinyGraphics - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "TinyGraphics - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/TinyGraphics", OAAAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "TinyGraphics - Win32 Release"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x809 /d "NDEBUG"
# ADD RSC /l 0x809 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "TinyGraphics - Win32 Debug"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x809 /d "_DEBUG"
# ADD RSC /l 0x809 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "TinyGraphics - Win32 Release"
# Name "TinyGraphics - Win32 Debug"
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\TinyGraphics.ico
# End Source File
# Begin Source File

SOURCE=.\res\TinyGraphics.rc2
# End Source File
# Begin Source File

SOURCE=.\res\TinyGraphicsDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# End Group
# Begin Group "MFC Classes"

# PROP Default_Filter ""
# Begin Group "MFC Classes Impl"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\ModifyPerspectiveCamera.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\TinyGraphics.cpp
# End Source File
# Begin Source File

SOURCE=.\TinyGraphics.rc
# End Source File
# Begin Source File

SOURCE=.\TinyGraphicsDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\TinyGraphicsView.cpp
# End Source File
# End Group
# Begin Group "Insert Object Dialogs"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\InsertCuboid.cpp
# End Source File
# Begin Source File

SOURCE=.\InsertCuboid.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\ModifyPerspectiveCamera.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\TinyGraphics.h
# End Source File
# Begin Source File

SOURCE=.\TinyGraphicsDoc.h
# End Source File
# Begin Source File

SOURCE=.\TinyGraphicsView.h
# End Source File
# End Group
# Begin Group "Tiny Grahpics Kernel"

# PROP Default_Filter ""
# Begin Group "2D Graphics"

# PROP Default_Filter ""
# Begin Group "2D Graphics Impl"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Kernel\Graphics2D.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# End Group
# Begin Source File

SOURCE=.\Kernel\Graphics2D.h
# End Source File
# Begin Source File

SOURCE=.\Kernel\Primitive2D.h
# End Source File
# End Group
# Begin Group "3D Graphics"

# PROP Default_Filter ""
# Begin Group "Object3D Hierarchy"

# PROP Default_Filter ""
# Begin Group "Object3D Hierarchy Impl"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Kernel\Cuboid.cpp

!IF  "$(CFG)" == "TinyGraphics - Win32 Release"

!ELSEIF  "$(CFG)" == "TinyGraphics - Win32 Debug"

# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Kernel\Object3D.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# End Group
# Begin Source File

SOURCE=.\Kernel\Cuboid.h
# End Source File
# Begin Source File

SOURCE=.\Kernel\Object3D.h
# End Source File
# End Group
# Begin Group "3D Graphics Impl"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Kernel\Graphics3D.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\Kernel\ViewingGraphics3D.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\Kernel\World3D.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# End Group
# Begin Group "Camera"

# PROP Default_Filter ""
# Begin Group "Camera Impl"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Kernel\Camera.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\Kernel\ParellelCamera.cpp

!IF  "$(CFG)" == "TinyGraphics - Win32 Release"

!ELSEIF  "$(CFG)" == "TinyGraphics - Win32 Debug"

# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Kernel\PerspectiveCamera.cpp

!IF  "$(CFG)" == "TinyGraphics - Win32 Release"

!ELSEIF  "$(CFG)" == "TinyGraphics - Win32 Debug"

# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# End Group
# Begin Source File

SOURCE=.\Kernel\Camera.h
# End Source File
# Begin Source File

SOURCE=.\Kernel\ParellelCamera.h
# End Source File
# Begin Source File

SOURCE=.\Kernel\PerspectiveCamera.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\Kernel\Graphics3D.h
# End Source File
# Begin Source File

SOURCE=.\Kernel\Primitive3D.h
# End Source File
# Begin Source File

SOURCE=.\Kernel\ViewingGraphics3D.h
# End Source File
# Begin Source File

SOURCE=.\Kernel\World3D.h
# End Source File
# End Group
# Begin Group "Utilities"

# PROP Default_Filter ""
# Begin Group "Matrix"

# PROP Default_Filter ""
# Begin Group "Matrix Impl"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Kernel\Matrix4D.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\Kernel\Vector3D.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\Kernel\Vector4D.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# End Group
# Begin Source File

SOURCE=.\Kernel\Matrix4D.h
# End Source File
# Begin Source File

SOURCE=.\Kernel\Real.h
# End Source File
# Begin Source File

SOURCE=.\Kernel\Vector3D.h
# End Source File
# Begin Source File

SOURCE=.\Kernel\Vector4D.h
# End Source File
# End Group
# Begin Group "Utilities Impl"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Kernel\ColorRGB.cpp

!IF  "$(CFG)" == "TinyGraphics - Win32 Release"

!ELSEIF  "$(CFG)" == "TinyGraphics - Win32 Debug"

# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# End Group
# Begin Source File

SOURCE=.\Kernel\ColorRGB.h
# End Source File
# End Group
# End Group
# Begin Group "Kernel-MFC Adapter"

# PROP Default_Filter ""
# Begin Group "Kernel-MFC Adapter Impl"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\CDCGraphics2D.cpp

!IF  "$(CFG)" == "TinyGraphics - Win32 Release"

!ELSEIF  "$(CFG)" == "TinyGraphics - Win32 Debug"

# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# End Group
# Begin Source File

SOURCE=.\CDCGraphics2D.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
