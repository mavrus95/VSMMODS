ORIGIN		= DigiMars C++
ORIGIN_VER	= Version 7.22
VERSION		= RELEASE

!IFDEF SUB_DEBUG
DEBUG		= $(SUB_DEBUG)
NDEBUG		= !$(SUB_DEBUG)
!ELSE
DEBUG		= 0
NDEBUG		= 1
!ENDIF

PROJ		= DALLAS
APPTYPE		= WIN32 DLL
PROJTYPE	= DLL

CC		= SC
CPP		= SPP
JAVAC		= sj
MAKE		= SMAKE
RC		= RCC
HC		= HC31
ASM		= SC
DISASM		= OBJ2ASM
LNK		= LINK
DLLS		= 

HEADERS		= DALLAS.HPP ..\..\..\..\..\..\..\dm\include\windows.h ..\..\..\..\..\..\..\dm\include\win32\scdefs.h  \
		..\..\..\..\..\..\..\dm\include\win32\WINDOWS.H ..\..\..\..\..\..\..\dm\include\excpt.h ..\..\..\..\..\..\..\dm\include\stdarg.h ..\..\..\..\..\..\..\dm\include\windef.h  \
		..\..\..\..\..\..\..\dm\include\win32\WINDEF.H ..\..\..\..\..\..\..\dm\include\winnt.h ..\..\..\..\..\..\..\dm\include\win32\WINNT.H ..\..\..\..\..\..\..\dm\include\ctype.h  \
		..\..\..\..\..\..\..\dm\include\pshpack4.h ..\..\..\..\..\..\..\dm\include\win32\pshpack4.h ..\..\..\..\..\..\..\dm\include\poppack.h ..\..\..\..\..\..\..\dm\include\win32\poppack.h  \
		..\..\..\..\..\..\..\dm\include\win32\pshpack2.h ..\..\..\..\..\..\..\dm\include\string.h ..\..\..\..\..\..\..\dm\include\winbase.h ..\..\..\..\..\..\..\dm\include\win32\WINBASE.H  \
		..\..\..\..\..\..\..\dm\include\winerror.h ..\..\..\..\..\..\..\dm\include\win32\WINERROR.H ..\..\..\..\..\..\..\dm\include\wingdi.h ..\..\..\..\..\..\..\dm\include\win32\WINGDI.H  \
		..\..\..\..\..\..\..\dm\include\pshpack1.h ..\..\..\..\..\..\..\dm\include\win32\pshpack1.h ..\..\..\..\..\..\..\dm\include\pshpack2.h ..\..\..\..\..\..\..\dm\include\winuser.h  \
		..\..\..\..\..\..\..\dm\include\win32\WINUSER.H ..\..\..\..\..\..\..\dm\include\winnls.h ..\..\..\..\..\..\..\dm\include\win32\WINNLS.H ..\..\..\..\..\..\..\dm\include\wincon.h  \
		..\..\..\..\..\..\..\dm\include\win32\WINCON.H ..\..\..\..\..\..\..\dm\include\winver.h ..\..\..\..\..\..\..\dm\include\win32\WINVER.H ..\..\..\..\..\..\..\dm\include\winreg.h  \
		..\..\..\..\..\..\..\dm\include\win32\WINREG.H ..\..\..\..\..\..\..\dm\include\winnetwk.h ..\..\..\..\..\..\..\dm\include\win32\WINNETWK.H ..\..\..\..\..\..\..\dm\include\cderr.h  \
		..\..\..\..\..\..\..\dm\include\win32\CDERR.H ..\..\..\..\..\..\..\dm\include\dde.h ..\..\..\..\..\..\..\dm\include\win32\DDE.H ..\..\..\..\..\..\..\dm\include\ddeml.h  \
		..\..\..\..\..\..\..\dm\include\win32\DDEML.H ..\..\..\..\..\..\..\dm\include\dlgs.h ..\..\..\..\..\..\..\dm\include\win32\DLGS.H ..\..\..\..\..\..\..\dm\include\lzexpand.h  \
		..\..\..\..\..\..\..\dm\include\win32\LZEXPAND.H ..\..\..\..\..\..\..\dm\include\mmsystem.h ..\..\..\..\..\..\..\dm\include\win32\MMSYSTEM.H ..\..\..\..\..\..\..\dm\include\nb30.h  \
		..\..\..\..\..\..\..\dm\include\win32\NB30.H ..\..\..\..\..\..\..\dm\include\rpc.h ..\..\..\..\..\..\..\dm\include\win32\rpc.h ..\..\..\..\..\..\..\dm\include\rpcdce.h  \
		..\..\..\..\..\..\..\dm\include\win32\RPCDCE.H ..\..\..\..\..\..\..\dm\include\rpcdcep.h ..\..\..\..\..\..\..\dm\include\win32\RPCDCEP.H ..\..\..\..\..\..\..\dm\include\rpcnsi.h  \
		..\..\..\..\..\..\..\dm\include\win32\RPCNSI.H ..\..\..\..\..\..\..\dm\include\rpcnterr.h ..\..\..\..\..\..\..\dm\include\win32\RPCNTERR.H ..\..\..\..\..\..\..\dm\include\shellapi.h  \
		..\..\..\..\..\..\..\dm\include\win32\shellapi.h ..\..\..\..\..\..\..\dm\include\winperf.h ..\..\..\..\..\..\..\dm\include\win32\WINPERF.H ..\..\..\..\..\..\..\dm\include\winsock2.h  \
		..\..\..\..\..\..\..\dm\include\win32\WINSOCK2.H ..\..\..\..\..\..\..\dm\include\mswsock.h ..\..\..\..\..\..\..\dm\include\win32\MSWSOCK.H ..\..\..\..\..\..\..\dm\include\wincrypt.h  \
		..\..\..\..\..\..\..\dm\include\win32\WINCRYPT.H ..\..\..\..\..\..\..\dm\include\commdlg.h ..\..\..\..\..\..\..\dm\include\win32\COMMDLG.H ..\..\..\..\..\..\..\dm\include\winspool.h  \
		..\..\..\..\..\..\..\dm\include\win32\WINSPOOL.H ..\..\..\..\..\..\..\dm\include\prsht.h ..\..\..\..\..\..\..\dm\include\win32\PRSHT.H ..\..\..\..\..\..\..\dm\include\ole2.h  \
		..\..\..\..\..\..\..\dm\include\win32\OLE2.H ..\..\..\..\..\..\..\dm\include\pshpack8.h ..\..\..\..\..\..\..\dm\include\win32\pshpack8.h ..\..\..\..\..\..\..\dm\include\objbase.h  \
		..\..\..\..\..\..\..\dm\include\win32\objbase.h ..\..\..\..\..\..\..\dm\include\rpcndr.h ..\..\..\..\..\..\..\dm\include\win32\RPCNDR.H ..\..\..\..\..\..\..\dm\include\rpcnsip.h  \
		..\..\..\..\..\..\..\dm\include\win32\RPCNSIP.H ..\..\..\..\..\..\..\dm\include\stdlib.h ..\..\..\..\..\..\..\dm\include\wtypes.h ..\..\..\..\..\..\..\dm\include\win32\wtypes.h  \
		..\..\..\..\..\..\..\dm\include\unknwn.h ..\..\..\..\..\..\..\dm\include\win32\unknwn.h ..\..\..\..\..\..\..\dm\include\objidl.h ..\..\..\..\..\..\..\dm\include\win32\objidl.h  \
		..\..\..\..\..\..\..\dm\include\cguid.h ..\..\..\..\..\..\..\dm\include\win32\CGUID.H ..\..\..\..\..\..\..\dm\include\oleauto.h ..\..\..\..\..\..\..\dm\include\win32\OLEAUTO.H  \
		..\..\..\..\..\..\..\dm\include\oaidl.h ..\..\..\..\..\..\..\dm\include\win32\oaidl.h ..\..\..\..\..\..\..\dm\include\oleidl.h ..\..\..\..\..\..\..\dm\include\win32\oleidl.h  \
		..\..\..\..\..\..\..\dm\include\winsvc.h ..\..\..\..\..\..\..\dm\include\win32\WINSVC.H ..\..\..\..\..\..\..\dm\include\mcx.h ..\..\..\..\..\..\..\dm\include\win32\MCX.H  \
		..\..\..\..\..\..\..\dm\include\imm.h ..\..\..\..\..\..\..\dm\include\win32\IMM.H ..\..\..\..\..\..\..\dm\include\math.h ..\..\..\..\..\..\..\dm\include\time.h  \
		"..\..\..\..\..\..\..\Program Files\Labcenter Electronics\Proteus 6 Professional\INCLUDE\vsm.hpp" "..\..\..\..\..\..\..\Program Files\Labcenter Electronics\Proteus 6 Professional\INCLUDE\vdm.hpp" "..\..\..\..\..\..\..\Program Files\Labcenter Electronics\Proteus 6 Professional\INCLUDE\DEVKEYS.H" 

DEFFILE		= DALLAS.DEF

!IF $(DEBUG)
OUTPUTDIR	= .
CREATEOUTPUTDIR	=
TARGETDIR	= .
CREATETARGETDIR	=

SYMROOT		= 
SYMS		= 
LIBS		= KERNEL32.LIB GDI32.LIB USER32.LIB 

CFLAGS		=  -mn -C -WD -S -3 -a8 -c -gf 
LFLAGS		=  /CO /NOI /DO /DE /NOPACKF /XN /NT /ENTRY:_DllMainCRTStartup /BAS:268435456 /A:512 /IMPL:$(TARGETDIR)\$$SCW$$.LIB
DEFINES		= -D_MBCS=1
!ELSE
OUTPUTDIR	= .
CREATEOUTPUTDIR	=
TARGETDIR	= "C:\Program Files\Labcenter Electronics\Proteus 6 Professional\MODELS"
!IF EXIST ("C:\Program Files\Labcenter Electronics\Proteus 6 Professional\MODELS")
CREATETARGETDIR	=
!ELSE
CREATETARGETDIR	= if not exist $(TARGETDIR)\*.* md $(TARGETDIR)
!ENDIF

SYMROOT		= 
SYMS		= 
LIBS		= KERNEL32.LIB GDI32.LIB USER32.LIB 

CFLAGS		=  -mn -o+time -WD -5 -a8 -c 
LFLAGS		=  /NOI /DO /DE /PACKF /XN /NT /ENTRY:_DllMainCRTStartup /BAS:268435456 /A:512 /IMPL:$(TARGETDIR)\$$SCW$$.LIB
DEFINES		= -D_MBCS=1
!ENDIF

HFLAGS		= $(CFLAGS) 
MFLAGS		= MASTERPROJ=$(PROJ) 
LIBFLAGS	=  /C 
RESFLAGS	=  -32 
DEBUGGERFLAGS	=  
AFLAGS		= $(CFLAGS) 
HELPFLAGS	= 

MODEL		= N

PAR		= PROJS BATS OBJS

RCDEFINES	= 

INCLUDES	= -I"C:\Program Files\Labcenter Electronics\Proteus 6 Professional\INCLUDE"

INCLUDEDOBJS	= 

OBJS		= DALLAS.OBJ 

RCFILES		= 

RESFILES	= 

HELPFILES	= 

BATS		= 

.SUFFIXES: .C .CP .CPP .CXX .CC .H .HPP .HXX .COM .EXE .DLL .LIB .RTF .DLG .ASM .RES .RC .OBJ 

.C.OBJ:
	$(CC) $(CFLAGS) $(DEFINES) $(INCLUDES) -o$*.obj $*.c

.CPP.OBJ:
	$(CC) $(CFLAGS) $(DEFINES) $(INCLUDES) -o$*.obj $*.cpp

.CXX.OBJ:
	$(CC) $(CFLAGS) $(DEFINES) $(INCLUDES) -o$*.obj $*.cxx

.CC.OBJ:
	$(CC) $(CFLAGS) $(DEFINES) $(INCLUDES) -o$*.obj $*.cc

.CP.OBJ:
	$(CC) $(CFLAGS) $(DEFINES) $(INCLUDES) -o$*.obj $*.cp

.H.SYM:
	$(CC) $(HFLAGS) $(DEFINES) $(INCLUDES) -HF -o$(*B).sym $*.h

.HPP.SYM:
	$(CC) $(HFLAGS) $(DEFINES) $(INCLUDES) -HF -o$(*B).sym $*.hpp

.HXX.SYM:
	$(CC) $(HFLAGS) $(DEFINES) $(INCLUDES) -HF -o$(*B).sym $*.hxx

.C.EXP:
	$(CPP) $(CFLAGS) $(DEFINES) $(INCLUDES)   $*.c   -o$*.lst

.CPP.EXP:
	$(CPP) $(CFLAGS) $(DEFINES) $(INCLUDES) $*.cpp -o$*.lst

.CXX.EXP:
	$(CPP) $(CFLAGS) $(DEFINES) $(INCLUDES) $*.cxx -o$*.lst

.CP.EXP:
	$(CPP) $(CFLAGS) $(DEFINES) $(INCLUDES)  $*.cp  -o$*.lst

.CC.EXP:
	$(CPP) $(CFLAGS) $(DEFINES) $(INCLUDES)  $*.cc  -o$*.lst

.ASM.EXP:
	$(CPP) $(CFLAGS) $(DEFINES) $(INCLUDES) $*.asm -o$*.lst

.OBJ.COD:
	$(DISASM) $*.OBJ -c

!IF $(DEBUG)
.OBJ.EXE:
		$(LNK) $(LFLAGS) @<<$(PROJ).LNK
DALLAS.OBJ
$$SCW$$.DLL
NUL
KERNEL32.LIB GDI32.LIB USER32.LIB 
DALLAS.DEF;
<<
!ELSE
.OBJ.EXE:
		$(LNK) $(LFLAGS) @$(PROJ).LNK<<
DALLAS.OBJ
"C:\Program Files\Labcenter Electronics\Proteus 6 Professional\MODELS\$$SCW$$".DLL
NUL
KERNEL32.LIB GDI32.LIB USER32.LIB 
DALLAS.DEF;
<<
!ENDIF

.RTF.HLP:
	$(HC) $(HELPFLAGS) $*.HPJ

.ASM.OBJ:
	$(ASM) $(AFLAGS) $(DEFINES) $(INCLUDES) -o$*.obj $*.asm

.RC.RES: 
	$(RC) $(RCDEFINES) $(RESFLAGS) $(INCLUDES) $*.rc -o$*.res

.DLG.RES:
	echo ^#include "windows.h" >$$$*.rc
	echo ^IF EXIST "$*.h" >>$$$*.rc
	echo ^#include "$*.h" >>$$$*.rc
	echo ^#include "$*.dlg" >>$$$*.rc
	$(RC) $(RCDEFINES) $(RESFLAGS) $(INCLUDES) $$$*.rc
	-del $*.res
	-ren $$$*.res $*.res



all:	noteout createdir $(PRECOMPILE) $(SYMS) $(OBJS) $(INCLUDEDOBJS) $(POSTCOMPILE) $(TARGETDIR)\$(PROJ).$(PROJTYPE) $(POSTLINK) _done


all2:	createdir $(PRECOMPILE) $(SYMS) $(OBJS) $(INCLUDEDOBJS) $(POSTCOMPILE) $(TARGETDIR)\$(PROJ).$(PROJTYPE) $(POSTLINK) _done

noteout:
	REM Output to $(OUTPUTDIR)

createdir:
	$(CREATEOUTPUTDIR)
	$(CREATETARGETDIR)
	
$(TARGETDIR)\$(PROJ).$(PROJTYPE): $(OBJS) $(INCLUDEDOBJS) $(RCFILES) $(RESFILES) $(HELPFILES) $(DEFFILE)
			-del $(TARGETDIR)\$(PROJ).$(PROJTYPE)
!IF $(DEBUG)
		$(LNK) $(LFLAGS) @<<$(PROJ).LNK
DALLAS.OBJ
$$SCW$$.DLL
NUL
KERNEL32.LIB GDI32.LIB USER32.LIB 
DALLAS.DEF;
<<
!ELSE
		$(LNK) $(LFLAGS) @<<$(PROJ).LNK
DALLAS.OBJ
"C:\Program Files\Labcenter Electronics\Proteus 6 Professional\MODELS\$$SCW$$".DLL
NUL
KERNEL32.LIB GDI32.LIB USER32.LIB 
DALLAS.DEF;
<<
!ENDIF

			-ren $(TARGETDIR)\$$SCW$$.$(PROJTYPE) $(PROJ).$(PROJTYPE)
			-del $(TARGETDIR)\$(PROJ).LIB
			-ren $(TARGETDIR)\$$SCW$$.LIB $(PROJ).LIB
			-echo $(TARGETDIR)\$(PROJ).$(PROJTYPE) built

_done:
		REM  Project is up to date

buildall:	clean	all


clean:
		-del $(TARGETDIR)\$$SCW$$.$(PROJTYPE)
		-del $(PROJ).CLE
		-del $(OUTPUTDIR)\SCPH.SYM
		-del DALLAS.dpd
		-del $(OBJS)

cleanres:

res:		cleanres $(RCFILES) all


link:
!IF $(DEBUG)
		$(LNK) $(LFLAGS) @<<$(PROJ).LNK
DALLAS.OBJ
$$SCW$$.DLL
NUL
KERNEL32.LIB GDI32.LIB USER32.LIB 
DALLAS.DEF;
<<
!ELSE
		$(LNK) $(LFLAGS) @<<$(PROJ).LNK
DALLAS.OBJ
"C:\Program Files\Labcenter Electronics\Proteus 6 Professional\MODELS\$$SCW$$".DLL
NUL
KERNEL32.LIB GDI32.LIB USER32.LIB 
DALLAS.DEF;
<<
!ENDIF

		-del $(TARGETDIR)\$(PROJ).$(PROJTYPE)
		-ren $(TARGETDIR)\$$SCW$$.$(PROJTYPE) $(PROJ).$(PROJTYPE)
			-del $(TARGETDIR)\$(PROJ).LIB
			-ren $(TARGETDIR)\$$SCW$$.LIB $(PROJ).LIB





!IF EXIST (DALLAS.dpd)
!INCLUDE DALLAS.dpd
!ENDIF


