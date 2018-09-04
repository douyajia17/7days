; ---------------------------------------------------------------------------

_SCOPETABLE_ENTRY struc	; (sizeof=0xC)	; XREF:	.rdata:stru_55AB88r
					; .rdata:stru_55AB98r ...
EnclosingLevel	dd ?
FilterFunc	dd ?			; offset
HandlerFunc	dd ?			; offset
_SCOPETABLE_ENTRY ends

; ---------------------------------------------------------------------------

CPPEH_RECORD	struc ;	(sizeof=0x18)	; XREF:	?DebuggerProbe@@YAHK@Zr
					; ?DebuggerRuntime@@YAHKHPAXPB_W@Zr ...
old_esp		dd ?			; XREF:	DebuggerProbe(ulong)+23w
					; DebuggerProbe(ulong):loc_4E8049r ...
exc_ptr		dd ?			; XREF:	__ArrayUnwind(void *,uint,int,void (*)(void *)):loc_4EBB22r
					; start:loc_4EBE24r ... ; offset
registration	_EH3_EXCEPTION_REGISTRATION ? ;	XREF: DebuggerProbe(ulong)+3Ew
					; DebuggerProbe(ulong):loc_4E804Cw ...
CPPEH_RECORD	ends

; ---------------------------------------------------------------------------

_EH3_EXCEPTION_REGISTRATION struc ; (sizeof=0x10, standard type) ; XREF: CPPEH_RECORDr
Next		dd ?			; XREF:	DebuggerProbe(ulong)+67r
					; DebuggerRuntime(ulong,int,void *,wchar_t const *)+79r ... ; offset
ExceptionHandler dd ?			; offset
ScopeTable	dd ?			; offset
TryLevel	dd ?			; XREF:	DebuggerProbe(ulong)+3Ew
					; DebuggerProbe(ulong):loc_4E804Cw ...
_EH3_EXCEPTION_REGISTRATION ends

; ---------------------------------------------------------------------------

tagMSG		struc ;	(sizeof=0x1C, standard type) ; XREF: _WinMain@16_0r
hwnd		dd ?			; offset
message		dd ?
wParam		dd ?
lParam		dd ?
time		dd ?
pt		POINT ?
tagMSG		ends

; ---------------------------------------------------------------------------

POINT		struc ;	(sizeof=0x8, standard type) ; XREF: tagMSGr
x		dd ?
y		dd ?
POINT		ends

; ---------------------------------------------------------------------------

WNDCLASSA	struc ;	(sizeof=0x28, standard type) ; XREF: sub_4084D0r
style		dd ?
lpfnWndProc	dd ?			; offset
cbClsExtra	dd ?
cbWndExtra	dd ?
hInstance	dd ?			; offset
hIcon		dd ?			; offset
hCursor		dd ?			; offset
hbrBackground	dd ?			; offset
lpszMenuName	dd ?			; offset
lpszClassName	dd ?			; offset
WNDCLASSA	ends

; ---------------------------------------------------------------------------

tagRECT		struc ;	(sizeof=0x10, standard type) ; XREF: sub_4084D0r
left		dd ?
top		dd ?
right		dd ?
bottom		dd ?
tagRECT		ends

; ---------------------------------------------------------------------------

_WIN32_FIND_DATAA struc	; (sizeof=0x140, standard type)
					; XREF:	?GetObjectInfo@XOleUIObjInfo@COlePropertiesDialog@@UAGJKPAKPAPAD111@Zr
dwFileAttributes dd ?
ftCreationTime	FILETIME ?
ftLastAccessTime FILETIME ?
ftLastWriteTime	FILETIME ?
nFileSizeHigh	dd ?
nFileSizeLow	dd ?
dwReserved0	dd ?
dwReserved1	dd ?
cFileName	db 260 dup(?)
cAlternateFileName db 14 dup(?)
_padding	db 2 dup(?)
_WIN32_FIND_DATAA ends

; ---------------------------------------------------------------------------

FILETIME	struc ;	(sizeof=0x8, standard type) ; XREF: _WIN32_FIND_DATAAr
					; _WIN32_FIND_DATAAr ...
dwLowDateTime	dd ?
dwHighDateTime	dd ?
FILETIME	ends

; ---------------------------------------------------------------------------

_SYSTEMTIME	struc ;	(sizeof=0x10, standard type)
					; XREF:	?GetObjectInfo@XOleUIObjInfo@COlePropertiesDialog@@UAGJKPAKPAPAD111@Zr
wYear		dw ?
wMonth		dw ?
wDayOfWeek	dw ?
wDay		dw ?
wHour		dw ?
wMinute		dw ?
wSecond		dw ?
wMilliseconds	dw ?
_SYSTEMTIME	ends

; ---------------------------------------------------------------------------

_MEMORYSTATUS	struc ;	(sizeof=0x20, standard type) ; XREF: sub_410860r
					; sub_4108E0r
dwLength	dd ?
dwMemoryLoad	dd ?
dwTotalPhys	dd ?
dwAvailPhys	dd ?
dwTotalPageFile	dd ?
dwAvailPageFile	dd ?
dwTotalVirtual	dd ?
dwAvailVirtual	dd ?
_MEMORYSTATUS	ends

; ---------------------------------------------------------------------------

RECT		struc ;	(sizeof=0x10, standard type) ; XREF: sub_410DB0r
					; sub_410EE0r
left		dd ?
top		dd ?
right		dd ?
bottom		dd ?
RECT		ends

; ---------------------------------------------------------------------------

_STARTUPINFOA	struc ;	(sizeof=0x44, standard type) ; XREF: startr __ioinitr
cb		dd ?
lpReserved	dd ?			; offset
lpDesktop	dd ?			; offset
lpTitle		dd ?			; offset
dwX		dd ?
dwY		dd ?
dwXSize		dd ?
dwYSize		dd ?
dwXCountChars	dd ?
dwYCountChars	dd ?
dwFillAttribute	dd ?
dwFlags		dd ?			; XREF:	start:loc_4EBDBBw start+164r
wShowWindow	dw ?			; XREF:	start+16Cr
cbReserved2	dw ?
lpReserved2	dd ?			; offset
hStdInput	dd ?			; offset
hStdOutput	dd ?			; offset
hStdError	dd ?			; offset
_STARTUPINFOA	ends

; ---------------------------------------------------------------------------

_MEMORY_BASIC_INFORMATION struc	; (sizeof=0x1C,	standard type) ; XREF: __ValidateEH3RNr
					; __resetstkoflwr
BaseAddress	dd ?			; offset
AllocationBase	dd ?			; offset
AllocationProtect dd ?
RegionSize	dd ?
State		dd ?
Protect		dd ?
Type		dd ?
_MEMORY_BASIC_INFORMATION ends

; ---------------------------------------------------------------------------

_cpinfo		struc ;	(sizeof=0x14, standard type) ; XREF: __setmbcpr
					; _setSBUpLowr	...
MaxCharSize	dd ?			; XREF:	___convertcp+69r
					; ___convertcp+81r
DefaultChar	db 2 dup(?)
LeadByte	db 12 dup(?)
_padding	db 2 dup(?)
_cpinfo		ends

; ---------------------------------------------------------------------------

_SYSTEM_INFO	struc ;	(sizeof=0x24, standard type) ; XREF: __resetstkoflwr
anonymous_0	_SYSTEM_INFO::$1593C2ABA4C275C0FBEC2498FA3B0937	?
dwPageSize	dd ?
lpMinimumApplicationAddress dd ?	; offset
lpMaximumApplicationAddress dd ?	; offset
dwActiveProcessorMask dd ?
dwNumberOfProcessors dd	?
dwProcessorType	dd ?
dwAllocationGranularity	dd ?
wProcessorLevel	dw ?
wProcessorRevision dw ?
_SYSTEM_INFO	ends

; ---------------------------------------------------------------------------

_SYSTEM_INFO::$1593C2ABA4C275C0FBEC2498FA3B0937	union ;	(sizeof=0x4, standard type)
					; XREF:	_SYSTEM_INFOr
dwOemId		dd ?
anonymous_0	_SYSTEM_INFO::$1593C2ABA4C275C0FBEC2498FA3B0937::$AA04DEB0C6383F89F13D312A174572A9 ?
_SYSTEM_INFO::$1593C2ABA4C275C0FBEC2498FA3B0937	ends

; ---------------------------------------------------------------------------

_SYSTEM_INFO::$1593C2ABA4C275C0FBEC2498FA3B0937::$AA04DEB0C6383F89F13D312A174572A9 struc ; (sizeof=0x4,	standard type)
					; XREF:	_SYSTEM_INFO::$1593C2ABA4C275C0FBEC2498FA3B0937r
wProcessorArchitecture dw ?
wReserved	dw ?
_SYSTEM_INFO::$1593C2ABA4C275C0FBEC2498FA3B0937::$AA04DEB0C6383F89F13D312A174572A9 ends

; ---------------------------------------------------------------------------

_FILETIME	struc ;	(sizeof=0x8, standard type) ; XREF: ___security_init_cookier
dwLowDateTime	dd ?
dwHighDateTime	dd ?
_FILETIME	ends

; ---------------------------------------------------------------------------

LARGE_INTEGER	union ;	(sizeof=0x8, standard type) ; XREF: ___security_init_cookier
anonymous_0	_LARGE_INTEGER::$837407842DC9087486FDFA5FEB63B74E ?
u		_LARGE_INTEGER::$837407842DC9087486FDFA5FEB63B74E ?
QuadPart	dq ?
LARGE_INTEGER	ends

; ---------------------------------------------------------------------------

_LARGE_INTEGER::$837407842DC9087486FDFA5FEB63B74E struc	; (sizeof=0x8, standard	type)
					; XREF:	LARGE_INTEGERr	LARGE_INTEGERr
LowPart		dd ?
HighPart	dd ?
_LARGE_INTEGER::$837407842DC9087486FDFA5FEB63B74E ends


