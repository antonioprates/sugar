/**
 * This file has no copyright assigned and is placed in the Public Domain.
 * This file is part of the w64 mingw-runtime package.
 * No warranty is given; refer to the file DISCLAIMER within this package.
 */
#ifndef _WINUSER_
#define _WINUSER_

#define WINUSERAPI DECLSPEC_IMPORT

#ifdef __cplusplus
extern "C" {
#endif

#ifndef WINVER
#define WINVER 0x0502
#endif

#include <stdarg.h>

#ifndef NOUSER
typedef HANDLE HDWP;
typedef VOID MENUTEMPLATEA;
typedef VOID MENUTEMPLATEW;
typedef PVOID LPMENUTEMPLATEA;
typedef PVOID LPMENUTEMPLATEW;

#ifdef UNICODE
typedef MENUTEMPLATEW MENUTEMPLATE;
typedef LPMENUTEMPLATEW LPMENUTEMPLATE;
#else
typedef MENUTEMPLATEA MENUTEMPLATE;
typedef LPMENUTEMPLATEA LPMENUTEMPLATE;
#endif

typedef LRESULT(CALLBACK* WNDPROC)(HWND, UINT, WPARAM, LPARAM);
typedef INT_PTR(CALLBACK* DLGPROC)(HWND, UINT, WPARAM, LPARAM);
typedef VOID(CALLBACK* TIMERPROC)(HWND, UINT, UINT_PTR, DWORD);
typedef WINBOOL(CALLBACK* GRAYSTRINGPROC)(HDC, LPARAM, int);
typedef WINBOOL(CALLBACK* WNDENUMPROC)(HWND, LPARAM);
typedef LRESULT(CALLBACK* HOOKPROC)(int code, WPARAM wParam, LPARAM lParam);
typedef VOID(CALLBACK* SENDASYNCPROC)(HWND, UINT, ULONG_PTR, LRESULT);
typedef WINBOOL(CALLBACK* PROPENUMPROCA)(HWND, LPCSTR, HANDLE);
typedef WINBOOL(CALLBACK* PROPENUMPROCW)(HWND, LPCWSTR, HANDLE);
typedef WINBOOL(CALLBACK* PROPENUMPROCEXA)(HWND, LPSTR, HANDLE, ULONG_PTR);
typedef WINBOOL(CALLBACK* PROPENUMPROCEXW)(HWND, LPWSTR, HANDLE, ULONG_PTR);
typedef int(CALLBACK* EDITWORDBREAKPROCA)(LPSTR lpch,
                                          int ichCurrent,
                                          int cch,
                                          int code);
typedef int(CALLBACK* EDITWORDBREAKPROCW)(LPWSTR lpch,
                                          int ichCurrent,
                                          int cch,
                                          int code);
typedef WINBOOL(CALLBACK* DRAWSTATEPROC)(HDC hdc,
                                         LPARAM lData,
                                         WPARAM wData,
                                         int cx,
                                         int cy);

#ifdef UNICODE
typedef PROPENUMPROCW PROPENUMPROC;
typedef PROPENUMPROCEXW PROPENUMPROCEX;
typedef EDITWORDBREAKPROCW EDITWORDBREAKPROC;
#else
typedef PROPENUMPROCA PROPENUMPROC;
typedef PROPENUMPROCEXA PROPENUMPROCEX;
typedef EDITWORDBREAKPROCA EDITWORDBREAKPROC;
#endif

typedef WINBOOL(CALLBACK* NAMEENUMPROCA)(LPSTR, LPARAM);
typedef WINBOOL(CALLBACK* NAMEENUMPROCW)(LPWSTR, LPARAM);
typedef NAMEENUMPROCA WINSTAENUMPROCA;
typedef NAMEENUMPROCA DESKTOPENUMPROCA;
typedef NAMEENUMPROCW WINSTAENUMPROCW;
typedef NAMEENUMPROCW DESKTOPENUMPROCW;

#ifdef UNICODE
typedef WINSTAENUMPROCW WINSTAENUMPROC;
typedef DESKTOPENUMPROCW DESKTOPENUMPROC;
#else
typedef WINSTAENUMPROCA WINSTAENUMPROC;
typedef DESKTOPENUMPROCA DESKTOPENUMPROC;
#endif

#define IS_INTRESOURCE(_r) ((((ULONG_PTR)(_r)) >> 16) == 0)
#define MAKEINTRESOURCEA(i) ((LPSTR)((ULONG_PTR)((WORD)(i))))
#define MAKEINTRESOURCEW(i) ((LPWSTR)((ULONG_PTR)((WORD)(i))))
#ifdef UNICODE
#define MAKEINTRESOURCE MAKEINTRESOURCEW
#else
#define MAKEINTRESOURCE MAKEINTRESOURCEA
#endif

#ifndef NORESOURCE

#define RT_CURSOR MAKEINTRESOURCE(1)
#define RT_BITMAP MAKEINTRESOURCE(2)
#define RT_ICON MAKEINTRESOURCE(3)
#define RT_MENU MAKEINTRESOURCE(4)
#define RT_DIALOG MAKEINTRESOURCE(5)
#define RT_STRING MAKEINTRESOURCE(6)
#define RT_FONTDIR MAKEINTRESOURCE(7)
#define RT_FONT MAKEINTRESOURCE(8)
#define RT_ACCELERATOR MAKEINTRESOURCE(9)
#define RT_RCDATA MAKEINTRESOURCE(10)
#define RT_MESSAGETABLE MAKEINTRESOURCE(11)

#define DIFFERENCE 11
#define RT_GROUP_CURSOR MAKEINTRESOURCE((ULONG_PTR)RT_CURSOR + DIFFERENCE)
#define RT_GROUP_ICON MAKEINTRESOURCE((ULONG_PTR)RT_ICON + DIFFERENCE)
#define RT_VERSION MAKEINTRESOURCE(16)
#define RT_DLGINCLUDE MAKEINTRESOURCE(17)
#define RT_PLUGPLAY MAKEINTRESOURCE(19)
#define RT_VXD MAKEINTRESOURCE(20)
#define RT_ANICURSOR MAKEINTRESOURCE(21)
#define RT_ANIICON MAKEINTRESOURCE(22)
#define RT_HTML MAKEINTRESOURCE(23)
#ifdef RC_INVOKED
#define RT_MANIFEST 24
#define CREATEPROCESS_MANIFEST_RESOURCE_ID 1
#define ISOLATIONAWARE_MANIFEST_RESOURCE_ID 2
#define ISOLATIONAWARE_NOSTATICIMPORT_MANIFEST_RESOURCE_ID 3
#define MINIMUM_RESERVED_MANIFEST_RESOURCE_ID 1
#define MAXIMUM_RESERVED_MANIFEST_RESOURCE_ID 16
#else
#define RT_MANIFEST MAKEINTRESOURCE(24)
#define CREATEPROCESS_MANIFEST_RESOURCE_ID MAKEINTRESOURCE(1)
#define ISOLATIONAWARE_MANIFEST_RESOURCE_ID MAKEINTRESOURCE(2)
#define ISOLATIONAWARE_NOSTATICIMPORT_MANIFEST_RESOURCE_ID MAKEINTRESOURCE(3)
#define MINIMUM_RESERVED_MANIFEST_RESOURCE_ID MAKEINTRESOURCE(1)
#define MAXIMUM_RESERVED_MANIFEST_RESOURCE_ID MAKEINTRESOURCE(16)
#endif
#endif

#ifdef UNICODE
#define wvsprintf wvsprintfW
#define wsprintf wsprintfW
#else
#define wvsprintf wvsprintfA
#define wsprintf wsprintfA
#endif

WINUSERAPI int WINAPI wvsprintfA(LPSTR, LPCSTR, va_list arglist);
WINUSERAPI int WINAPI wvsprintfW(LPWSTR, LPCWSTR, va_list arglist);
WINUSERAPI int WINAPIV wsprintfA(LPSTR, LPCSTR, ...);
WINUSERAPI int WINAPIV wsprintfW(LPWSTR, LPCWSTR, ...);

#define SETWALLPAPER_DEFAULT ((LPWSTR)-1)

#ifndef NOSCROLL
#define SB_HORZ 0
#define SB_VERT 1
#define SB_CTL 2
#define SB_BOTH 3

#define SB_LINEUP 0
#define SB_LINELEFT 0
#define SB_LINEDOWN 1
#define SB_LINERIGHT 1
#define SB_PAGEUP 2
#define SB_PAGELEFT 2
#define SB_PAGEDOWN 3
#define SB_PAGERIGHT 3
#define SB_THUMBPOSITION 4
#define SB_THUMBTRACK 5
#define SB_TOP 6
#define SB_LEFT 6
#define SB_BOTTOM 7
#define SB_RIGHT 7
#define SB_ENDSCROLL 8
#endif

#ifndef NOSHOWWINDOW
#define SW_HIDE 0
#define SW_SHOWNORMAL 1
#define SW_NORMAL 1
#define SW_SHOWMINIMIZED 2
#define SW_SHOWMAXIMIZED 3
#define SW_MAXIMIZE 3
#define SW_SHOWNOACTIVATE 4
#define SW_SHOW 5
#define SW_MINIMIZE 6
#define SW_SHOWMINNOACTIVE 7
#define SW_SHOWNA 8
#define SW_RESTORE 9
#define SW_SHOWDEFAULT 10
#define SW_FORCEMINIMIZE 11
#define SW_MAX 11

#define HIDE_WINDOW 0
#define SHOW_OPENWINDOW 1
#define SHOW_ICONWINDOW 2
#define SHOW_FULLSCREEN 3
#define SHOW_OPENNOACTIVATE 4

#define SW_PARENTCLOSING 1
#define SW_OTHERZOOM 2
#define SW_PARENTOPENING 3
#define SW_OTHERUNZOOM 4
#endif

#define AW_HOR_POSITIVE 0x00000001
#define AW_HOR_NEGATIVE 0x00000002
#define AW_VER_POSITIVE 0x00000004
#define AW_VER_NEGATIVE 0x00000008
#define AW_CENTER 0x00000010
#define AW_HIDE 0x00010000
#define AW_ACTIVATE 0x00020000
#define AW_SLIDE 0x00040000
#define AW_BLEND 0x00080000

#define KF_EXTENDED 0x0100
#define KF_DLGMODE 0x0800
#define KF_MENUMODE 0x1000
#define KF_ALTDOWN 0x2000
#define KF_REPEAT 0x4000
#define KF_UP 0x8000

#ifndef NOVIRTUALKEYCODES

#define VK_LBUTTON 0x01
#define VK_RBUTTON 0x02
#define VK_CANCEL 0x03
#define VK_MBUTTON 0x04
#define VK_XBUTTON1 0x05
#define VK_XBUTTON2 0x06
#define VK_BACK 0x08
#define VK_TAB 0x09
#define VK_CLEAR 0x0C
#define VK_RETURN 0x0D
#define VK_SHIFT 0x10
#define VK_CONTROL 0x11
#define VK_MENU 0x12
#define VK_PAUSE 0x13
#define VK_CAPITAL 0x14
#define VK_KANA 0x15
#define VK_HANGEUL 0x15
#define VK_HANGUL 0x15
#define VK_JUNJA 0x17
#define VK_FINAL 0x18
#define VK_HANJA 0x19
#define VK_KANJI 0x19
#define VK_ESCAPE 0x1B
#define VK_CONVERT 0x1C
#define VK_NONCONVERT 0x1D
#define VK_ACCEPT 0x1E
#define VK_MODECHANGE 0x1F
#define VK_SPACE 0x20
#define VK_PRIOR 0x21
#define VK_NEXT 0x22
#define VK_END 0x23
#define VK_HOME 0x24
#define VK_LEFT 0x25
#define VK_UP 0x26
#define VK_RIGHT 0x27
#define VK_DOWN 0x28
#define VK_SELECT 0x29
#define VK_PRINT 0x2A
#define VK_EXECUTE 0x2B
#define VK_SNAPSHOT 0x2C
#define VK_INSERT 0x2D
#define VK_DELETE 0x2E
#define VK_HELP 0x2F

#define VK_LWIN 0x5B
#define VK_RWIN 0x5C
#define VK_APPS 0x5D
#define VK_SLEEP 0x5F
#define VK_NUMPAD0 0x60
#define VK_NUMPAD1 0x61
#define VK_NUMPAD2 0x62
#define VK_NUMPAD3 0x63
#define VK_NUMPAD4 0x64
#define VK_NUMPAD5 0x65
#define VK_NUMPAD6 0x66
#define VK_NUMPAD7 0x67
#define VK_NUMPAD8 0x68
#define VK_NUMPAD9 0x69
#define VK_MULTIPLY 0x6A
#define VK_ADD 0x6B
#define VK_SEPARATOR 0x6C
#define VK_SUBTRACT 0x6D
#define VK_DECIMAL 0x6E
#define VK_DIVIDE 0x6F
#define VK_F1 0x70
#define VK_F2 0x71
#define VK_F3 0x72
#define VK_F4 0x73
#define VK_F5 0x74
#define VK_F6 0x75
#define VK_F7 0x76
#define VK_F8 0x77
#define VK_F9 0x78
#define VK_F10 0x79
#define VK_F11 0x7A
#define VK_F12 0x7B
#define VK_F13 0x7C
#define VK_F14 0x7D
#define VK_F15 0x7E
#define VK_F16 0x7F
#define VK_F17 0x80
#define VK_F18 0x81
#define VK_F19 0x82
#define VK_F20 0x83
#define VK_F21 0x84
#define VK_F22 0x85
#define VK_F23 0x86
#define VK_F24 0x87
#define VK_NUMLOCK 0x90
#define VK_SCROLL 0x91
#define VK_OEM_NEC_EQUAL 0x92
#define VK_OEM_FJ_JISHO 0x92
#define VK_OEM_FJ_MASSHOU 0x93
#define VK_OEM_FJ_TOUROKU 0x94
#define VK_OEM_FJ_LOYA 0x95
#define VK_OEM_FJ_ROYA 0x96
#define VK_LSHIFT 0xA0
#define VK_RSHIFT 0xA1
#define VK_LCONTROL 0xA2
#define VK_RCONTROL 0xA3
#define VK_LMENU 0xA4
#define VK_RMENU 0xA5
#define VK_BROWSER_BACK 0xA6
#define VK_BROWSER_FORWARD 0xA7
#define VK_BROWSER_REFRESH 0xA8
#define VK_BROWSER_STOP 0xA9
#define VK_BROWSER_SEARCH 0xAA
#define VK_BROWSER_FAVORITES 0xAB
#define VK_BROWSER_HOME 0xAC
#define VK_VOLUME_MUTE 0xAD
#define VK_VOLUME_DOWN 0xAE
#define VK_VOLUME_UP 0xAF
#define VK_MEDIA_NEXT_TRACK 0xB0
#define VK_MEDIA_PREV_TRACK 0xB1
#define VK_MEDIA_STOP 0xB2
#define VK_MEDIA_PLAY_PAUSE 0xB3
#define VK_LAUNCH_MAIL 0xB4
#define VK_LAUNCH_MEDIA_SELECT 0xB5
#define VK_LAUNCH_APP1 0xB6
#define VK_LAUNCH_APP2 0xB7
#define VK_OEM_1 0xBA
#define VK_OEM_PLUS 0xBB
#define VK_OEM_COMMA 0xBC
#define VK_OEM_MINUS 0xBD
#define VK_OEM_PERIOD 0xBE
#define VK_OEM_2 0xBF
#define VK_OEM_3 0xC0
#define VK_OEM_4 0xDB
#define VK_OEM_5 0xDC
#define VK_OEM_6 0xDD
#define VK_OEM_7 0xDE
#define VK_OEM_8 0xDF
#define VK_OEM_AX 0xE1
#define VK_OEM_102 0xE2
#define VK_ICO_HELP 0xE3
#define VK_ICO_00 0xE4
#define VK_PROCESSKEY 0xE5
#define VK_ICO_CLEAR 0xE6
#define VK_PACKET 0xE7
#define VK_OEM_RESET 0xE9
#define VK_OEM_JUMP 0xEA
#define VK_OEM_PA1 0xEB
#define VK_OEM_PA2 0xEC
#define VK_OEM_PA3 0xED
#define VK_OEM_WSCTRL 0xEE
#define VK_OEM_CUSEL 0xEF
#define VK_OEM_ATTN 0xF0
#define VK_OEM_FINISH 0xF1
#define VK_OEM_COPY 0xF2
#define VK_OEM_AUTO 0xF3
#define VK_OEM_ENLW 0xF4
#define VK_OEM_BACKTAB 0xF5
#define VK_ATTN 0xF6
#define VK_CRSEL 0xF7
#define VK_EXSEL 0xF8
#define VK_EREOF 0xF9
#define VK_PLAY 0xFA
#define VK_ZOOM 0xFB
#define VK_NONAME 0xFC
#define VK_PA1 0xFD
#define VK_OEM_CLEAR 0xFE
#endif

#ifndef NOWH

#define WH_MIN (-1)
#define WH_MSGFILTER (-1)
#define WH_JOURNALRECORD 0
#define WH_JOURNALPLAYBACK 1
#define WH_KEYBOARD 2
#define WH_GETMESSAGE 3
#define WH_CALLWNDPROC 4
#define WH_CBT 5
#define WH_SYSMSGFILTER 6
#define WH_MOUSE 7
#define WH_HARDWARE 8
#define WH_DEBUG 9
#define WH_SHELL 10
#define WH_FOREGROUNDIDLE 11
#define WH_CALLWNDPROCRET 12

#define WH_KEYBOARD_LL 13
#define WH_MOUSE_LL 14

#define WH_MAX 14

#define WH_MINHOOK WH_MIN
#define WH_MAXHOOK WH_MAX

#define HC_ACTION 0
#define HC_GETNEXT 1
#define HC_SKIP 2
#define HC_NOREMOVE 3
#define HC_NOREM HC_NOREMOVE
#define HC_SYSMODALON 4
#define HC_SYSMODALOFF 5

#define HCBT_MOVESIZE 0
#define HCBT_MINMAX 1
#define HCBT_QS 2
#define HCBT_CREATEWND 3
#define HCBT_DESTROYWND 4
#define HCBT_ACTIVATE 5
#define HCBT_CLICKSKIPPED 6
#define HCBT_KEYSKIPPED 7
#define HCBT_SYSCOMMAND 8
#define HCBT_SETFOCUS 9

typedef struct tagCBT_CREATEWNDA {
  struct tagCREATESTRUCTA* lpcs;
  HWND hwndInsertAfter;
} CBT_CREATEWNDA, *LPCBT_CREATEWNDA;

typedef struct tagCBT_CREATEWNDW {
  struct tagCREATESTRUCTW* lpcs;
  HWND hwndInsertAfter;
} CBT_CREATEWNDW, *LPCBT_CREATEWNDW;
#ifdef UNICODE
typedef CBT_CREATEWNDW CBT_CREATEWND;
typedef LPCBT_CREATEWNDW LPCBT_CREATEWND;
#else
typedef CBT_CREATEWNDA CBT_CREATEWND;
typedef LPCBT_CREATEWNDA LPCBT_CREATEWND;
#endif

typedef struct tagCBTACTIVATESTRUCT {
  WINBOOL fMouse;
  HWND hWndActive;
} CBTACTIVATESTRUCT, *LPCBTACTIVATESTRUCT;

typedef struct tagWTSSESSION_NOTIFICATION {
  DWORD cbSize;
  DWORD dwSessionId;

} WTSSESSION_NOTIFICATION, *PWTSSESSION_NOTIFICATION;

#define WTS_CONSOLE_CONNECT 0x1
#define WTS_CONSOLE_DISCONNECT 0x2
#define WTS_REMOTE_CONNECT 0x3
#define WTS_REMOTE_DISCONNECT 0x4
#define WTS_SESSION_LOGON 0x5
#define WTS_SESSION_LOGOFF 0x6
#define WTS_SESSION_LOCK 0x7
#define WTS_SESSION_UNLOCK 0x8
#define WTS_SESSION_REMOTE_CONTROL 0x9

#define MSGF_DIALOGBOX 0
#define MSGF_MESSAGEBOX 1
#define MSGF_MENU 2
#define MSGF_SCROLLBAR 5
#define MSGF_NEXTWINDOW 6
#define MSGF_MAX 8
#define MSGF_USER 4096

#define HSHELL_WINDOWCREATED 1
#define HSHELL_WINDOWDESTROYED 2
#define HSHELL_ACTIVATESHELLWINDOW 3

#define HSHELL_WINDOWACTIVATED 4
#define HSHELL_GETMINRECT 5
#define HSHELL_REDRAW 6
#define HSHELL_TASKMAN 7
#define HSHELL_LANGUAGE 8
#define HSHELL_SYSMENU 9
#define HSHELL_ENDTASK 10
#define HSHELL_ACCESSIBILITYSTATE 11
#define HSHELL_APPCOMMAND 12
#define HSHELL_WINDOWREPLACED 13
#define HSHELL_WINDOWREPLACING 14
#define HSHELL_HIGHBIT 0x8000
#define HSHELL_FLASH (HSHELL_REDRAW | HSHELL_HIGHBIT)
#define HSHELL_RUDEAPPACTIVATED (HSHELL_WINDOWACTIVATED | HSHELL_HIGHBIT)

#define ACCESS_STICKYKEYS 0x0001
#define ACCESS_FILTERKEYS 0x0002
#define ACCESS_MOUSEKEYS 0x0003

#define APPCOMMAND_BROWSER_BACKWARD 1
#define APPCOMMAND_BROWSER_FORWARD 2
#define APPCOMMAND_BROWSER_REFRESH 3
#define APPCOMMAND_BROWSER_STOP 4
#define APPCOMMAND_BROWSER_SEARCH 5
#define APPCOMMAND_BROWSER_FAVORITES 6
#define APPCOMMAND_BROWSER_HOME 7
#define APPCOMMAND_VOLUME_MUTE 8
#define APPCOMMAND_VOLUME_DOWN 9
#define APPCOMMAND_VOLUME_UP 10
#define APPCOMMAND_MEDIA_NEXTTRACK 11
#define APPCOMMAND_MEDIA_PREVIOUSTRACK 12
#define APPCOMMAND_MEDIA_STOP 13
#define APPCOMMAND_MEDIA_PLAY_PAUSE 14
#define APPCOMMAND_LAUNCH_MAIL 15
#define APPCOMMAND_LAUNCH_MEDIA_SELECT 16
#define APPCOMMAND_LAUNCH_APP1 17
#define APPCOMMAND_LAUNCH_APP2 18
#define APPCOMMAND_BASS_DOWN 19
#define APPCOMMAND_BASS_BOOST 20
#define APPCOMMAND_BASS_UP 21
#define APPCOMMAND_TREBLE_DOWN 22
#define APPCOMMAND_TREBLE_UP 23
#define APPCOMMAND_MICROPHONE_VOLUME_MUTE 24
#define APPCOMMAND_MICROPHONE_VOLUME_DOWN 25
#define APPCOMMAND_MICROPHONE_VOLUME_UP 26
#define APPCOMMAND_HELP 27
#define APPCOMMAND_FIND 28
#define APPCOMMAND_NEW 29
#define APPCOMMAND_OPEN 30
#define APPCOMMAND_CLOSE 31
#define APPCOMMAND_SAVE 32
#define APPCOMMAND_PRINT 33
#define APPCOMMAND_UNDO 34
#define APPCOMMAND_REDO 35
#define APPCOMMAND_COPY 36
#define APPCOMMAND_CUT 37
#define APPCOMMAND_PASTE 38
#define APPCOMMAND_REPLY_TO_MAIL 39
#define APPCOMMAND_FORWARD_MAIL 40
#define APPCOMMAND_SEND_MAIL 41
#define APPCOMMAND_SPELL_CHECK 42
#define APPCOMMAND_DICTATE_OR_COMMAND_CONTROL_TOGGLE 43
#define APPCOMMAND_MIC_ON_OFF_TOGGLE 44
#define APPCOMMAND_CORRECTION_LIST 45
#define APPCOMMAND_MEDIA_PLAY 46
#define APPCOMMAND_MEDIA_PAUSE 47
#define APPCOMMAND_MEDIA_RECORD 48
#define APPCOMMAND_MEDIA_FAST_FORWARD 49
#define APPCOMMAND_MEDIA_REWIND 50
#define APPCOMMAND_MEDIA_CHANNEL_UP 51
#define APPCOMMAND_MEDIA_CHANNEL_DOWN 52

#define FAPPCOMMAND_MOUSE 0x8000
#define FAPPCOMMAND_KEY 0
#define FAPPCOMMAND_OEM 0x1000
#define FAPPCOMMAND_MASK 0xF000

#define GET_APPCOMMAND_LPARAM(lParam) \
  ((short)(HIWORD(lParam) & ~FAPPCOMMAND_MASK))
#define GET_DEVICE_LPARAM(lParam) ((WORD)(HIWORD(lParam) & FAPPCOMMAND_MASK))
#define GET_MOUSEORKEY_LPARAM GET_DEVICE_LPARAM
#define GET_FLAGS_LPARAM(lParam) (LOWORD(lParam))
#define GET_KEYSTATE_LPARAM(lParam) GET_FLAGS_LPARAM(lParam)

typedef struct {
  HWND hwnd;
  RECT rc;
} SHELLHOOKINFO, *LPSHELLHOOKINFO;

typedef struct tagEVENTMSG {
  UINT message;
  UINT paramL;
  UINT paramH;
  DWORD time;
  HWND hwnd;
} EVENTMSG, *PEVENTMSGMSG, *NPEVENTMSGMSG, *LPEVENTMSGMSG;

typedef struct tagEVENTMSG *PEVENTMSG, *NPEVENTMSG, *LPEVENTMSG;

typedef struct tagCWPSTRUCT {
  LPARAM lParam;
  WPARAM wParam;
  UINT message;
  HWND hwnd;
} CWPSTRUCT, *PCWPSTRUCT, *NPCWPSTRUCT, *LPCWPSTRUCT;

typedef struct tagCWPRETSTRUCT {
  LRESULT lResult;
  LPARAM lParam;
  WPARAM wParam;
  UINT message;
  HWND hwnd;
} CWPRETSTRUCT, *PCWPRETSTRUCT, *NPCWPRETSTRUCT, *LPCWPRETSTRUCT;

#define LLKHF_EXTENDED (KF_EXTENDED >> 8)
#define LLKHF_INJECTED 0x00000010
#define LLKHF_ALTDOWN (KF_ALTDOWN >> 8)
#define LLKHF_UP (KF_UP >> 8)

#define LLMHF_INJECTED 0x00000001

typedef struct tagKBDLLHOOKSTRUCT {
  DWORD vkCode;
  DWORD scanCode;
  DWORD flags;
  DWORD time;
  ULONG_PTR dwExtraInfo;
} KBDLLHOOKSTRUCT, *LPKBDLLHOOKSTRUCT, *PKBDLLHOOKSTRUCT;

typedef struct tagMSLLHOOKSTRUCT {
  POINT pt;
  DWORD mouseData;
  DWORD flags;
  DWORD time;
  ULONG_PTR dwExtraInfo;
} MSLLHOOKSTRUCT, *LPMSLLHOOKSTRUCT, *PMSLLHOOKSTRUCT;

typedef struct tagDEBUGHOOKINFO {
  DWORD idThread;
  DWORD idThreadInstaller;
  LPARAM lParam;
  WPARAM wParam;
  int code;
} DEBUGHOOKINFO, *PDEBUGHOOKINFO, *NPDEBUGHOOKINFO, *LPDEBUGHOOKINFO;

typedef struct tagMOUSEHOOKSTRUCT {
  POINT pt;
  HWND hwnd;
  UINT wHitTestCode;
  ULONG_PTR dwExtraInfo;
} MOUSEHOOKSTRUCT, *LPMOUSEHOOKSTRUCT, *PMOUSEHOOKSTRUCT;

#ifdef __cplusplus
typedef struct tagMOUSEHOOKSTRUCTEX : public tagMOUSEHOOKSTRUCT {
  DWORD mouseData;
} MOUSEHOOKSTRUCTEX, *LPMOUSEHOOKSTRUCTEX, *PMOUSEHOOKSTRUCTEX;
#else
typedef struct tagMOUSEHOOKSTRUCTEX {
  MOUSEHOOKSTRUCT _unnamed;
  DWORD mouseData;
} MOUSEHOOKSTRUCTEX, *LPMOUSEHOOKSTRUCTEX, *PMOUSEHOOKSTRUCTEX;
#endif

typedef struct tagHARDWAREHOOKSTRUCT {
  HWND hwnd;
  UINT message;
  WPARAM wParam;
  LPARAM lParam;
} HARDWAREHOOKSTRUCT, *LPHARDWAREHOOKSTRUCT, *PHARDWAREHOOKSTRUCT;
#endif

#define HKL_PREV 0
#define HKL_NEXT 1

#define KLF_ACTIVATE 0x00000001
#define KLF_SUBSTITUTE_OK 0x00000002
#define KLF_REORDER 0x00000008
#define KLF_REPLACELANG 0x00000010
#define KLF_NOTELLSHELL 0x00000080
#define KLF_SETFORPROCESS 0x00000100
#define KLF_SHIFTLOCK 0x00010000
#define KLF_RESET 0x40000000

#define INPUTLANGCHANGE_SYSCHARSET 0x0001
#define INPUTLANGCHANGE_FORWARD 0x0002
#define INPUTLANGCHANGE_BACKWARD 0x0004

#define KL_NAMELENGTH 9

#ifdef UNICODE
#define LoadKeyboardLayout LoadKeyboardLayoutW
#define GetKeyboardLayoutName GetKeyboardLayoutNameW
#else
#define LoadKeyboardLayout LoadKeyboardLayoutA
#define GetKeyboardLayoutName GetKeyboardLayoutNameA
#endif

WINUSERAPI HKL WINAPI LoadKeyboardLayoutA(LPCSTR pwszKLID, UINT Flags);
WINUSERAPI HKL WINAPI LoadKeyboardLayoutW(LPCWSTR pwszKLID, UINT Flags);
WINUSERAPI HKL WINAPI ActivateKeyboardLayout(HKL hkl, UINT Flags);
WINUSERAPI int WINAPI ToUnicodeEx(UINT wVirtKey,
                                  UINT wScanCode,
                                  CONST BYTE* lpKeyState,
                                  LPWSTR pwszBuff,
                                  int cchBuff,
                                  UINT wFlags,
                                  HKL dwhkl);
WINUSERAPI WINBOOL WINAPI UnloadKeyboardLayout(HKL hkl);
WINUSERAPI WINBOOL WINAPI GetKeyboardLayoutNameA(LPSTR pwszKLID);
WINUSERAPI WINBOOL WINAPI GetKeyboardLayoutNameW(LPWSTR pwszKLID);
WINUSERAPI int WINAPI GetKeyboardLayoutList(int nBuff, HKL* lpList);
WINUSERAPI HKL WINAPI GetKeyboardLayout(DWORD idThread);

typedef struct tagMOUSEMOVEPOINT {
  int x;
  int y;
  DWORD time;
  ULONG_PTR dwExtraInfo;
} MOUSEMOVEPOINT, *PMOUSEMOVEPOINT, *LPMOUSEMOVEPOINT;

#define GMMP_USE_DISPLAY_POINTS 1
#define GMMP_USE_HIGH_RESOLUTION_POINTS 2

WINUSERAPI int WINAPI GetMouseMovePointsEx(UINT cbSize,
                                           LPMOUSEMOVEPOINT lppt,
                                           LPMOUSEMOVEPOINT lpptBuf,
                                           int nBufPoints,
                                           DWORD resolution);

#ifndef NODESKTOP

#define DESKTOP_READOBJECTS 0x0001L
#define DESKTOP_CREATEWINDOW 0x0002L
#define DESKTOP_CREATEMENU 0x0004L
#define DESKTOP_HOOKCONTROL 0x0008L
#define DESKTOP_JOURNALRECORD 0x0010L
#define DESKTOP_JOURNALPLAYBACK 0x0020L
#define DESKTOP_ENUMERATE 0x0040L
#define DESKTOP_WRITEOBJECTS 0x0080L
#define DESKTOP_SWITCHDESKTOP 0x0100L

#define DF_ALLOWOTHERACCOUNTHOOK 0x0001L

#ifdef _WINGDI_
#ifndef NOGDI
#ifdef UNICODE
#define CreateDesktop CreateDesktopW
#else
#define CreateDesktop CreateDesktopA
#endif

WINUSERAPI HDESK WINAPI CreateDesktopA(LPCSTR lpszDesktop,
                                       LPCSTR lpszDevice,
                                       LPDEVMODEA pDevmode,
                                       DWORD dwFlags,
                                       ACCESS_MASK dwDesiredAccess,
                                       LPSECURITY_ATTRIBUTES lpsa);
WINUSERAPI HDESK WINAPI CreateDesktopW(LPCWSTR lpszDesktop,
                                       LPCWSTR lpszDevice,
                                       LPDEVMODEW pDevmode,
                                       DWORD dwFlags,
                                       ACCESS_MASK dwDesiredAccess,
                                       LPSECURITY_ATTRIBUTES lpsa);
#endif
#endif

#ifdef UNICODE
#define OpenDesktop OpenDesktopW
#define EnumDesktops EnumDesktopsW
#else
#define OpenDesktop OpenDesktopA
#define EnumDesktops EnumDesktopsA
#endif

WINUSERAPI HDESK WINAPI OpenDesktopA(LPCSTR lpszDesktop,
                                     DWORD dwFlags,
                                     WINBOOL fInherit,
                                     ACCESS_MASK dwDesiredAccess);
WINUSERAPI HDESK WINAPI OpenDesktopW(LPCWSTR lpszDesktop,
                                     DWORD dwFlags,
                                     WINBOOL fInherit,
                                     ACCESS_MASK dwDesiredAccess);
WINUSERAPI HDESK WINAPI OpenInputDesktop(DWORD dwFlags,
                                         WINBOOL fInherit,
                                         ACCESS_MASK dwDesiredAccess);
WINUSERAPI WINBOOL WINAPI EnumDesktopsA(HWINSTA hwinsta,
                                        DESKTOPENUMPROCA lpEnumFunc,
                                        LPARAM lParam);
WINUSERAPI WINBOOL WINAPI EnumDesktopsW(HWINSTA hwinsta,
                                        DESKTOPENUMPROCW lpEnumFunc,
                                        LPARAM lParam);
WINUSERAPI WINBOOL WINAPI EnumDesktopWindows(HDESK hDesktop,
                                             WNDENUMPROC lpfn,
                                             LPARAM lParam);
WINUSERAPI WINBOOL WINAPI SwitchDesktop(HDESK hDesktop);
WINUSERAPI WINBOOL WINAPI SetThreadDesktop(HDESK hDesktop);
WINUSERAPI WINBOOL WINAPI CloseDesktop(HDESK hDesktop);
WINUSERAPI HDESK WINAPI GetThreadDesktop(DWORD dwThreadId);
#endif

#ifndef NOWINDOWSTATION
#define WINSTA_ENUMDESKTOPS 0x0001L
#define WINSTA_READATTRIBUTES 0x0002L
#define WINSTA_ACCESSCLIPBOARD 0x0004L
#define WINSTA_CREATEDESKTOP 0x0008L
#define WINSTA_WRITEATTRIBUTES 0x0010L
#define WINSTA_ACCESSGLOBALATOMS 0x0020L
#define WINSTA_EXITWINDOWS 0x0040L
#define WINSTA_ENUMERATE 0x0100L
#define WINSTA_READSCREEN 0x0200L
#define WINSTA_ALL_ACCESS                                                     \
  (WINSTA_ENUMDESKTOPS | WINSTA_READATTRIBUTES | WINSTA_ACCESSCLIPBOARD |     \
   WINSTA_CREATEDESKTOP | WINSTA_WRITEATTRIBUTES | WINSTA_ACCESSGLOBALATOMS | \
   WINSTA_EXITWINDOWS | WINSTA_ENUMERATE | WINSTA_READSCREEN)

#define CWF_CREATE_ONLY 0x0001L

#define WSF_VISIBLE 0x0001L

#ifdef UNICODE
#define CreateWindowStation CreateWindowStationW
#define OpenWindowStation OpenWindowStationW
#define EnumWindowStations EnumWindowStationsW
#else
#define CreateWindowStation CreateWindowStationA
#define OpenWindowStation OpenWindowStationA
#define EnumWindowStations EnumWindowStationsA
#endif

WINUSERAPI HWINSTA WINAPI CreateWindowStationA(LPCSTR lpwinsta,
                                               DWORD dwFlags,
                                               ACCESS_MASK dwDesiredAccess,
                                               LPSECURITY_ATTRIBUTES lpsa);
WINUSERAPI HWINSTA WINAPI CreateWindowStationW(LPCWSTR lpwinsta,
                                               DWORD dwFlags,
                                               ACCESS_MASK dwDesiredAccess,
                                               LPSECURITY_ATTRIBUTES lpsa);
WINUSERAPI HWINSTA WINAPI OpenWindowStationA(LPCSTR lpszWinSta,
                                             WINBOOL fInherit,
                                             ACCESS_MASK dwDesiredAccess);
WINUSERAPI HWINSTA WINAPI OpenWindowStationW(LPCWSTR lpszWinSta,
                                             WINBOOL fInherit,
                                             ACCESS_MASK dwDesiredAccess);
WINUSERAPI WINBOOL WINAPI EnumWindowStationsA(WINSTAENUMPROCA lpEnumFunc,
                                              LPARAM lParam);
WINUSERAPI WINBOOL WINAPI EnumWindowStationsW(WINSTAENUMPROCW lpEnumFunc,
                                              LPARAM lParam);
WINUSERAPI WINBOOL WINAPI CloseWindowStation(HWINSTA hWinSta);
WINUSERAPI WINBOOL WINAPI SetProcessWindowStation(HWINSTA hWinSta);
WINUSERAPI HWINSTA WINAPI GetProcessWindowStation(VOID);
#endif

#ifndef NOSECURITY
WINUSERAPI WINBOOL WINAPI
SetUserObjectSecurity(HANDLE hObj,
                      PSECURITY_INFORMATION pSIRequested,
                      PSECURITY_DESCRIPTOR pSID);
WINUSERAPI WINBOOL WINAPI
GetUserObjectSecurity(HANDLE hObj,
                      PSECURITY_INFORMATION pSIRequested,
                      PSECURITY_DESCRIPTOR pSID,
                      DWORD nLength,
                      LPDWORD lpnLengthNeeded);

#define UOI_FLAGS 1
#define UOI_NAME 2
#define UOI_TYPE 3
#define UOI_USER_SID 4

typedef struct tagUSEROBJECTFLAGS {
  WINBOOL fInherit;
  WINBOOL fReserved;
  DWORD dwFlags;
} USEROBJECTFLAGS, *PUSEROBJECTFLAGS;

#ifdef UNICODE
#define GetUserObjectInformation GetUserObjectInformationW
#define SetUserObjectInformation SetUserObjectInformationW
#else
#define GetUserObjectInformation GetUserObjectInformationA
#define SetUserObjectInformation SetUserObjectInformationA
#endif

WINUSERAPI WINBOOL WINAPI GetUserObjectInformationA(HANDLE hObj,
                                                    int nIndex,
                                                    PVOID pvInfo,
                                                    DWORD nLength,
                                                    LPDWORD lpnLengthNeeded);
WINUSERAPI WINBOOL WINAPI GetUserObjectInformationW(HANDLE hObj,
                                                    int nIndex,
                                                    PVOID pvInfo,
                                                    DWORD nLength,
                                                    LPDWORD lpnLengthNeeded);
WINUSERAPI WINBOOL WINAPI SetUserObjectInformationA(HANDLE hObj,
                                                    int nIndex,
                                                    PVOID pvInfo,
                                                    DWORD nLength);
WINUSERAPI WINBOOL WINAPI SetUserObjectInformationW(HANDLE hObj,
                                                    int nIndex,
                                                    PVOID pvInfo,
                                                    DWORD nLength);
#endif

typedef struct tagWNDCLASSEXA {
  UINT cbSize;
  UINT style;
  WNDPROC lpfnWndProc;
  int cbClsExtra;
  int cbWndExtra;
  HINSTANCE hInstance;
  HICON hIcon;
  HCURSOR hCursor;
  HBRUSH hbrBackground;
  LPCSTR lpszMenuName;
  LPCSTR lpszClassName;
  HICON hIconSm;
} WNDCLASSEXA, *PWNDCLASSEXA, *NPWNDCLASSEXA, *LPWNDCLASSEXA;

typedef struct tagWNDCLASSEXW {
  UINT cbSize;
  UINT style;
  WNDPROC lpfnWndProc;
  int cbClsExtra;
  int cbWndExtra;
  HINSTANCE hInstance;
  HICON hIcon;
  HCURSOR hCursor;
  HBRUSH hbrBackground;
  LPCWSTR lpszMenuName;
  LPCWSTR lpszClassName;

  HICON hIconSm;
} WNDCLASSEXW, *PWNDCLASSEXW, *NPWNDCLASSEXW, *LPWNDCLASSEXW;

#ifdef UNICODE
typedef WNDCLASSEXW WNDCLASSEX;
typedef PWNDCLASSEXW PWNDCLASSEX;
typedef NPWNDCLASSEXW NPWNDCLASSEX;
typedef LPWNDCLASSEXW LPWNDCLASSEX;
#else
typedef WNDCLASSEXA WNDCLASSEX;
typedef PWNDCLASSEXA PWNDCLASSEX;
typedef NPWNDCLASSEXA NPWNDCLASSEX;
typedef LPWNDCLASSEXA LPWNDCLASSEX;
#endif

typedef struct tagWNDCLASSA {
  UINT style;
  WNDPROC lpfnWndProc;
  int cbClsExtra;
  int cbWndExtra;
  HINSTANCE hInstance;
  HICON hIcon;
  HCURSOR hCursor;
  HBRUSH hbrBackground;
  LPCSTR lpszMenuName;
  LPCSTR lpszClassName;
} WNDCLASSA, *PWNDCLASSA, *NPWNDCLASSA, *LPWNDCLASSA;

typedef struct tagWNDCLASSW {
  UINT style;
  WNDPROC lpfnWndProc;
  int cbClsExtra;
  int cbWndExtra;
  HINSTANCE hInstance;
  HICON hIcon;
  HCURSOR hCursor;
  HBRUSH hbrBackground;
  LPCWSTR lpszMenuName;
  LPCWSTR lpszClassName;
} WNDCLASSW, *PWNDCLASSW, *NPWNDCLASSW, *LPWNDCLASSW;

#ifdef UNICODE
typedef WNDCLASSW WNDCLASS;
typedef PWNDCLASSW PWNDCLASS;
typedef NPWNDCLASSW NPWNDCLASS;
typedef LPWNDCLASSW LPWNDCLASS;
#else
typedef WNDCLASSA WNDCLASS;
typedef PWNDCLASSA PWNDCLASS;
typedef NPWNDCLASSA NPWNDCLASS;
typedef LPWNDCLASSA LPWNDCLASS;
#endif

WINUSERAPI WINBOOL WINAPI IsHungAppWindow(HWND hwnd);
WINUSERAPI VOID WINAPI DisableProcessWindowsGhosting(VOID);

#ifndef NOMSG
typedef struct tagMSG {
  HWND hwnd;
  UINT message;
  WPARAM wParam;
  LPARAM lParam;
  DWORD time;
  POINT pt;
} MSG, *PMSG, *NPMSG, *LPMSG;

#define POINTSTOPOINT(pt, pts)                  \
  {                                             \
    (pt).x = (LONG)(SHORT)LOWORD(*(LONG*)&pts); \
    (pt).y = (LONG)(SHORT)HIWORD(*(LONG*)&pts); \
  }

#define POINTTOPOINTS(pt) (MAKELONG((short)((pt).x), (short)((pt).y)))
#define MAKEWPARAM(l, h) ((WPARAM)(DWORD)MAKELONG(l, h))
#define MAKELPARAM(l, h) ((LPARAM)(DWORD)MAKELONG(l, h))
#define MAKELRESULT(l, h) ((LRESULT)(DWORD)MAKELONG(l, h))
#endif

#ifndef NOWINOFFSETS
#define GWL_WNDPROC (-4)
#define GWL_HINSTANCE (-6)
#define GWL_HWNDPARENT (-8)
#define GWL_STYLE (-16)
#define GWL_EXSTYLE (-20)
#define GWL_USERDATA (-21)
#define GWL_ID (-12)

#ifdef _WIN64
#undef GWL_WNDPROC
#undef GWL_HINSTANCE
#undef GWL_HWNDPARENT
#undef GWL_USERDATA
#endif

#define GWLP_WNDPROC (-4)
#define GWLP_HINSTANCE (-6)
#define GWLP_HWNDPARENT (-8)
#define GWLP_USERDATA (-21)
#define GWLP_ID (-12)

#define GCL_MENUNAME (-8)
#define GCL_HBRBACKGROUND (-10)
#define GCL_HCURSOR (-12)
#define GCL_HICON (-14)
#define GCL_HMODULE (-16)
#define GCL_CBWNDEXTRA (-18)
#define GCL_CBCLSEXTRA (-20)
#define GCL_WNDPROC (-24)
#define GCL_STYLE (-26)
#define GCW_ATOM (-32)
#define GCL_HICONSM (-34)

#ifdef _WIN64

#undef GCL_MENUNAME
#undef GCL_HBRBACKGROUND
#undef GCL_HCURSOR
#undef GCL_HICON
#undef GCL_HMODULE
#undef GCL_WNDPROC
#undef GCL_HICONSM
#endif

#define GCLP_MENUNAME (-8)
#define GCLP_HBRBACKGROUND (-10)
#define GCLP_HCURSOR (-12)
#define GCLP_HICON (-14)
#define GCLP_HMODULE (-16)
#define GCLP_WNDPROC (-24)
#define GCLP_HICONSM (-34)
#endif

#ifndef NOWINMESSAGES

#define WM_NULL 0x0000
#define WM_CREATE 0x0001
#define WM_DESTROY 0x0002
#define WM_MOVE 0x0003
#define WM_SIZE 0x0005

#define WM_ACTIVATE 0x0006

#define WA_INACTIVE 0
#define WA_ACTIVE 1
#define WA_CLICKACTIVE 2

#define WM_SETFOCUS 0x0007
#define WM_KILLFOCUS 0x0008
#define WM_ENABLE 0x000A
#define WM_SETREDRAW 0x000B
#define WM_SETTEXT 0x000C
#define WM_GETTEXT 0x000D
#define WM_GETTEXTLENGTH 0x000E
#define WM_PAINT 0x000F
#define WM_CLOSE 0x0010
#ifndef _WIN32_WCE
#define WM_QUERYENDSESSION 0x0011
#define WM_QUERYOPEN 0x0013
#define WM_ENDSESSION 0x0016
#endif
#define WM_QUIT 0x0012
#define WM_ERASEBKGND 0x0014
#define WM_SYSCOLORCHANGE 0x0015
#define WM_SHOWWINDOW 0x0018
#define WM_WININICHANGE 0x001A
#define WM_SETTINGCHANGE WM_WININICHANGE
#define WM_DEVMODECHANGE 0x001B
#define WM_ACTIVATEAPP 0x001C
#define WM_FONTCHANGE 0x001D
#define WM_TIMECHANGE 0x001E
#define WM_CANCELMODE 0x001F
#define WM_SETCURSOR 0x0020
#define WM_MOUSEACTIVATE 0x0021
#define WM_CHILDACTIVATE 0x0022
#define WM_QUEUESYNC 0x0023

#define WM_GETMINMAXINFO 0x0024

typedef struct tagMINMAXINFO {
  POINT ptReserved;
  POINT ptMaxSize;
  POINT ptMaxPosition;
  POINT ptMinTrackSize;
  POINT ptMaxTrackSize;
} MINMAXINFO, *PMINMAXINFO, *LPMINMAXINFO;

#define WM_PAINTICON 0x0026
#define WM_ICONERASEBKGND 0x0027
#define WM_NEXTDLGCTL 0x0028
#define WM_SPOOLERSTATUS 0x002A
#define WM_DRAWITEM 0x002B
#define WM_MEASUREITEM 0x002C
#define WM_DELETEITEM 0x002D
#define WM_VKEYTOITEM 0x002E
#define WM_CHARTOITEM 0x002F
#define WM_SETFONT 0x0030
#define WM_GETFONT 0x0031
#define WM_SETHOTKEY 0x0032
#define WM_GETHOTKEY 0x0033
#define WM_QUERYDRAGICON 0x0037
#define WM_COMPAREITEM 0x0039
#ifndef _WIN32_WCE
#define WM_GETOBJECT 0x003D
#endif
#define WM_COMPACTING 0x0041
#define WM_COMMNOTIFY 0x0044
#define WM_WINDOWPOSCHANGING 0x0046
#define WM_WINDOWPOSCHANGED 0x0047

#define WM_POWER 0x0048

#define PWR_OK 1
#define PWR_FAIL (-1)
#define PWR_SUSPENDREQUEST 1
#define PWR_SUSPENDRESUME 2
#define PWR_CRITICALRESUME 3

#define WM_COPYDATA 0x004A
#define WM_CANCELJOURNAL 0x004B

typedef struct tagCOPYDATASTRUCT {
  ULONG_PTR dwData;
  DWORD cbData;
  PVOID lpData;
} COPYDATASTRUCT, *PCOPYDATASTRUCT;

typedef struct tagMDINEXTMENU {
  HMENU hmenuIn;
  HMENU hmenuNext;
  HWND hwndNext;
} MDINEXTMENU, *PMDINEXTMENU, *LPMDINEXTMENU;

#define WM_NOTIFY 0x004E
#define WM_INPUTLANGCHANGEREQUEST 0x0050
#define WM_INPUTLANGCHANGE 0x0051
#define WM_TCARD 0x0052
#define WM_HELP 0x0053
#define WM_USERCHANGED 0x0054
#define WM_NOTIFYFORMAT 0x0055

#define NFR_ANSI 1
#define NFR_UNICODE 2
#define NF_QUERY 3
#define NF_REQUERY 4

#define WM_CONTEXTMENU 0x007B
#define WM_STYLECHANGING 0x007C
#define WM_STYLECHANGED 0x007D
#define WM_DISPLAYCHANGE 0x007E
#define WM_GETICON 0x007F
#define WM_SETICON 0x0080

#define WM_NCCREATE 0x0081
#define WM_NCDESTROY 0x0082
#define WM_NCCALCSIZE 0x0083
#define WM_NCHITTEST 0x0084
#define WM_NCPAINT 0x0085
#define WM_NCACTIVATE 0x0086
#define WM_GETDLGCODE 0x0087
#ifndef _WIN32_WCE
#define WM_SYNCPAINT 0x0088
#endif
#define WM_NCMOUSEMOVE 0x00A0
#define WM_NCLBUTTONDOWN 0x00A1
#define WM_NCLBUTTONUP 0x00A2
#define WM_NCLBUTTONDBLCLK 0x00A3
#define WM_NCRBUTTONDOWN 0x00A4
#define WM_NCRBUTTONUP 0x00A5
#define WM_NCRBUTTONDBLCLK 0x00A6
#define WM_NCMBUTTONDOWN 0x00A7
#define WM_NCMBUTTONUP 0x00A8
#define WM_NCMBUTTONDBLCLK 0x00A9

#define WM_NCXBUTTONDOWN 0x00AB
#define WM_NCXBUTTONUP 0x00AC
#define WM_NCXBUTTONDBLCLK 0x00AD
#define WM_INPUT 0x00FF
#define WM_KEYFIRST 0x0100
#define WM_KEYDOWN 0x0100
#define WM_KEYUP 0x0101
#define WM_CHAR 0x0102
#define WM_DEADCHAR 0x0103
#define WM_SYSKEYDOWN 0x0104
#define WM_SYSKEYUP 0x0105
#define WM_SYSCHAR 0x0106
#define WM_SYSDEADCHAR 0x0107
#define WM_UNICHAR 0x0109
#define WM_KEYLAST 0x0109
#define UNICODE_NOCHAR 0xFFFF
#define WM_IME_STARTCOMPOSITION 0x010D
#define WM_IME_ENDCOMPOSITION 0x010E
#define WM_IME_COMPOSITION 0x010F
#define WM_IME_KEYLAST 0x010F
#define WM_INITDIALOG 0x0110
#define WM_COMMAND 0x0111
#define WM_SYSCOMMAND 0x0112
#define WM_TIMER 0x0113
#define WM_HSCROLL 0x0114
#define WM_VSCROLL 0x0115
#define WM_INITMENU 0x0116
#define WM_INITMENUPOPUP 0x0117
#define WM_MENUSELECT 0x011F
#define WM_MENUCHAR 0x0120
#define WM_ENTERIDLE 0x0121
#ifndef _WIN32_WCE
#define WM_MENURBUTTONUP 0x0122
#define WM_MENUDRAG 0x0123
#define WM_MENUGETOBJECT 0x0124
#define WM_UNINITMENUPOPUP 0x0125
#define WM_MENUCOMMAND 0x0126

#ifndef _WIN32_WCE
#define WM_CHANGEUISTATE 0x0127
#define WM_UPDATEUISTATE 0x0128
#define WM_QUERYUISTATE 0x0129

#define UIS_SET 1
#define UIS_CLEAR 2
#define UIS_INITIALIZE 3

#define UISF_HIDEFOCUS 0x1
#define UISF_HIDEACCEL 0x2
#define UISF_ACTIVE 0x4
#endif
#endif

#define WM_CTLCOLORMSGBOX 0x0132
#define WM_CTLCOLOREDIT 0x0133
#define WM_CTLCOLORLISTBOX 0x0134
#define WM_CTLCOLORBTN 0x0135
#define WM_CTLCOLORDLG 0x0136
#define WM_CTLCOLORSCROLLBAR 0x0137
#define WM_CTLCOLORSTATIC 0x0138
#define MN_GETHMENU 0x01E1

#define WM_MOUSEFIRST 0x0200
#define WM_MOUSEMOVE 0x0200
#define WM_LBUTTONDOWN 0x0201
#define WM_LBUTTONUP 0x0202
#define WM_LBUTTONDBLCLK 0x0203
#define WM_RBUTTONDOWN 0x0204
#define WM_RBUTTONUP 0x0205
#define WM_RBUTTONDBLCLK 0x0206
#define WM_MBUTTONDOWN 0x0207
#define WM_MBUTTONUP 0x0208
#define WM_MBUTTONDBLCLK 0x0209
#define WM_MOUSEWHEEL 0x020A
#define WM_XBUTTONDOWN 0x020B
#define WM_XBUTTONUP 0x020C
#define WM_XBUTTONDBLCLK 0x020D
#define WM_MOUSELAST 0x020D

#define WHEEL_DELTA 120
#define GET_WHEEL_DELTA_WPARAM(wParam) ((short)HIWORD(wParam))

#define WHEEL_PAGESCROLL (UINT_MAX)

#define GET_KEYSTATE_WPARAM(wParam) (LOWORD(wParam))
#define GET_NCHITTEST_WPARAM(wParam) ((short)LOWORD(wParam))
#define GET_XBUTTON_WPARAM(wParam) (HIWORD(wParam))

#define XBUTTON1 0x0001
#define XBUTTON2 0x0002

#define WM_PARENTNOTIFY 0x0210
#define WM_ENTERMENULOOP 0x0211
#define WM_EXITMENULOOP 0x0212

#define WM_NEXTMENU 0x0213
#define WM_SIZING 0x0214
#define WM_CAPTURECHANGED 0x0215
#define WM_MOVING 0x0216

#define WM_POWERBROADCAST 0x0218

#ifndef _WIN32_WCE
#define PBT_APMQUERYSUSPEND 0x0000
#define PBT_APMQUERYSTANDBY 0x0001

#define PBT_APMQUERYSUSPENDFAILED 0x0002
#define PBT_APMQUERYSTANDBYFAILED 0x0003

#define PBT_APMSUSPEND 0x0004
#define PBT_APMSTANDBY 0x0005

#define PBT_APMRESUMECRITICAL 0x0006
#define PBT_APMRESUMESUSPEND 0x0007
#define PBT_APMRESUMESTANDBY 0x0008

#define PBTF_APMRESUMEFROMFAILURE 0x00000001

#define PBT_APMBATTERYLOW 0x0009
#define PBT_APMPOWERSTATUSCHANGE 0x000A

#define PBT_APMOEMEVENT 0x000B
#define PBT_APMRESUMEAUTOMATIC 0x0012
#endif

#define WM_DEVICECHANGE 0x0219

#define WM_MDICREATE 0x0220
#define WM_MDIDESTROY 0x0221
#define WM_MDIACTIVATE 0x0222
#define WM_MDIRESTORE 0x0223
#define WM_MDINEXT 0x0224
#define WM_MDIMAXIMIZE 0x0225
#define WM_MDITILE 0x0226
#define WM_MDICASCADE 0x0227
#define WM_MDIICONARRANGE 0x0228
#define WM_MDIGETACTIVE 0x0229

#define WM_MDISETMENU 0x0230
#define WM_ENTERSIZEMOVE 0x0231
#define WM_EXITSIZEMOVE 0x0232
#define WM_DROPFILES 0x0233
#define WM_MDIREFRESHMENU 0x0234

#define WM_IME_SETCONTEXT 0x0281
#define WM_IME_NOTIFY 0x0282
#define WM_IME_CONTROL 0x0283
#define WM_IME_COMPOSITIONFULL 0x0284
#define WM_IME_SELECT 0x0285
#define WM_IME_CHAR 0x0286
#define WM_IME_REQUEST 0x0288
#define WM_IME_KEYDOWN 0x0290
#define WM_IME_KEYUP 0x0291

#define WM_MOUSEHOVER 0x02A1
#define WM_MOUSELEAVE 0x02A3
#define WM_NCMOUSEHOVER 0x02A0
#define WM_NCMOUSELEAVE 0x02A2
#define WM_WTSSESSION_CHANGE 0x02B1
#define WM_TABLET_FIRST 0x02c0
#define WM_TABLET_LAST 0x02df
#define WM_CUT 0x0300
#define WM_COPY 0x0301
#define WM_PASTE 0x0302
#define WM_CLEAR 0x0303
#define WM_UNDO 0x0304
#define WM_RENDERFORMAT 0x0305
#define WM_RENDERALLFORMATS 0x0306
#define WM_DESTROYCLIPBOARD 0x0307
#define WM_DRAWCLIPBOARD 0x0308
#define WM_PAINTCLIPBOARD 0x0309
#define WM_VSCROLLCLIPBOARD 0x030A
#define WM_SIZECLIPBOARD 0x030B
#define WM_ASKCBFORMATNAME 0x030C
#define WM_CHANGECBCHAIN 0x030D
#define WM_HSCROLLCLIPBOARD 0x030E
#define WM_QUERYNEWPALETTE 0x030F
#define WM_PALETTEISCHANGING 0x0310
#define WM_PALETTECHANGED 0x0311
#define WM_HOTKEY 0x0312
#define WM_PRINT 0x0317
#define WM_PRINTCLIENT 0x0318
#define WM_APPCOMMAND 0x0319
#define WM_THEMECHANGED 0x031A
#define WM_HANDHELDFIRST 0x0358
#define WM_HANDHELDLAST 0x035F
#define WM_AFXFIRST 0x0360
#define WM_AFXLAST 0x037F
#define WM_PENWINFIRST 0x0380
#define WM_PENWINLAST 0x038F
#define WM_APP 0x8000
#define WM_USER 0x0400

#define WMSZ_LEFT 1
#define WMSZ_RIGHT 2
#define WMSZ_TOP 3
#define WMSZ_TOPLEFT 4
#define WMSZ_TOPRIGHT 5
#define WMSZ_BOTTOM 6
#define WMSZ_BOTTOMLEFT 7
#define WMSZ_BOTTOMRIGHT 8

#ifndef NONCMESSAGES

#define HTERROR (-2)
#define HTTRANSPARENT (-1)
#define HTNOWHERE 0
#define HTCLIENT 1
#define HTCAPTION 2
#define HTSYSMENU 3
#define HTGROWBOX 4
#define HTSIZE HTGROWBOX
#define HTMENU 5
#define HTHSCROLL 6
#define HTVSCROLL 7
#define HTMINBUTTON 8
#define HTMAXBUTTON 9
#define HTLEFT 10
#define HTRIGHT 11
#define HTTOP 12
#define HTTOPLEFT 13
#define HTTOPRIGHT 14
#define HTBOTTOM 15
#define HTBOTTOMLEFT 16
#define HTBOTTOMRIGHT 17
#define HTBORDER 18
#define HTREDUCE HTMINBUTTON
#define HTZOOM HTMAXBUTTON
#define HTSIZEFIRST HTLEFT
#define HTSIZELAST HTBOTTOMRIGHT
#define HTOBJECT 19
#define HTCLOSE 20
#define HTHELP 21

#define SMTO_NORMAL 0x0000
#define SMTO_BLOCK 0x0001
#define SMTO_ABORTIFHUNG 0x0002
#define SMTO_NOTIMEOUTIFNOTHUNG 0x0008
#endif

#define MA_ACTIVATE 1
#define MA_ACTIVATEANDEAT 2
#define MA_NOACTIVATE 3
#define MA_NOACTIVATEANDEAT 4

#define ICON_SMALL 0
#define ICON_BIG 1
#define ICON_SMALL2 2

#ifdef UNICODE
#define RegisterWindowMessage RegisterWindowMessageW
#else
#define RegisterWindowMessage RegisterWindowMessageA
#endif

WINUSERAPI UINT WINAPI RegisterWindowMessageA(LPCSTR lpString);
WINUSERAPI UINT WINAPI RegisterWindowMessageW(LPCWSTR lpString);

#define SIZE_RESTORED 0
#define SIZE_MINIMIZED 1
#define SIZE_MAXIMIZED 2
#define SIZE_MAXSHOW 3
#define SIZE_MAXHIDE 4

#define SIZENORMAL SIZE_RESTORED
#define SIZEICONIC SIZE_MINIMIZED
#define SIZEFULLSCREEN SIZE_MAXIMIZED
#define SIZEZOOMSHOW SIZE_MAXSHOW
#define SIZEZOOMHIDE SIZE_MAXHIDE

typedef struct tagWINDOWPOS {
  HWND hwnd;
  HWND hwndInsertAfter;
  int x;
  int y;
  int cx;
  int cy;
  UINT flags;
} WINDOWPOS, *LPWINDOWPOS, *PWINDOWPOS;

typedef struct tagNCCALCSIZE_PARAMS {
  RECT rgrc[3];
  PWINDOWPOS lppos;
} NCCALCSIZE_PARAMS, *LPNCCALCSIZE_PARAMS;

#define WVR_ALIGNTOP 0x0010
#define WVR_ALIGNLEFT 0x0020
#define WVR_ALIGNBOTTOM 0x0040
#define WVR_ALIGNRIGHT 0x0080
#define WVR_HREDRAW 0x0100
#define WVR_VREDRAW 0x0200
#define WVR_REDRAW (WVR_HREDRAW | WVR_VREDRAW)
#define WVR_VALIDRECTS 0x0400

#ifndef NOKEYSTATES

#define MK_LBUTTON 0x0001
#define MK_RBUTTON 0x0002
#define MK_SHIFT 0x0004
#define MK_CONTROL 0x0008
#define MK_MBUTTON 0x0010
#define MK_XBUTTON1 0x0020
#define MK_XBUTTON2 0x0040
#endif

#ifndef NOTRACKMOUSEEVENT
#define TME_HOVER 0x00000001
#define TME_LEAVE 0x00000002
#define TME_NONCLIENT 0x00000010
#define TME_QUERY 0x40000000
#define TME_CANCEL 0x80000000

#define HOVER_DEFAULT 0xFFFFFFFF
#endif

typedef struct tagTRACKMOUSEEVENT {
  DWORD cbSize;
  DWORD dwFlags;
  HWND hwndTrack;
  DWORD dwHoverTime;
} TRACKMOUSEEVENT, *LPTRACKMOUSEEVENT;

WINUSERAPI WINBOOL WINAPI TrackMouseEvent(LPTRACKMOUSEEVENT lpEventTrack);
#endif

#ifndef NOWINSTYLES

#define WS_OVERLAPPED 0x00000000L
#define WS_POPUP 0x80000000L
#define WS_CHILD 0x40000000L
#define WS_MINIMIZE 0x20000000L
#define WS_VISIBLE 0x10000000L
#define WS_DISABLED 0x08000000L
#define WS_CLIPSIBLINGS 0x04000000L
#define WS_CLIPCHILDREN 0x02000000L
#define WS_MAXIMIZE 0x01000000L
#define WS_CAPTION 0x00C00000L
#define WS_BORDER 0x00800000L
#define WS_DLGFRAME 0x00400000L
#define WS_VSCROLL 0x00200000L
#define WS_HSCROLL 0x00100000L
#define WS_SYSMENU 0x00080000L
#define WS_THICKFRAME 0x00040000L
#define WS_GROUP 0x00020000L
#define WS_TABSTOP 0x00010000L
#define WS_MINIMIZEBOX 0x00020000L
#define WS_MAXIMIZEBOX 0x00010000L
#define WS_TILED WS_OVERLAPPED
#define WS_ICONIC WS_MINIMIZE
#define WS_SIZEBOX WS_THICKFRAME
#define WS_TILEDWINDOW WS_OVERLAPPEDWINDOW
#define WS_OVERLAPPEDWINDOW                                                   \
  (WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX | \
   WS_MAXIMIZEBOX)
#define WS_POPUPWINDOW (WS_POPUP | WS_BORDER | WS_SYSMENU)
#define WS_CHILDWINDOW (WS_CHILD)

#define WS_EX_DLGMODALFRAME 0x00000001L
#define WS_EX_NOPARENTNOTIFY 0x00000004L
#define WS_EX_TOPMOST 0x00000008L
#define WS_EX_ACCEPTFILES 0x00000010L
#define WS_EX_TRANSPARENT 0x00000020L
#define WS_EX_MDICHILD 0x00000040L
#define WS_EX_TOOLWINDOW 0x00000080L
#define WS_EX_WINDOWEDGE 0x00000100L
#define WS_EX_CLIENTEDGE 0x00000200L
#define WS_EX_CONTEXTHELP 0x00000400L
#define WS_EX_RIGHT 0x00001000L
#define WS_EX_LEFT 0x00000000L
#define WS_EX_RTLREADING 0x00002000L
#define WS_EX_LTRREADING 0x00000000L
#define WS_EX_LEFTSCROLLBAR 0x00004000L
#define WS_EX_RIGHTSCROLLBAR 0x00000000L
#define WS_EX_CONTROLPARENT 0x00010000L
#define WS_EX_STATICEDGE 0x00020000L
#define WS_EX_APPWINDOW 0x00040000L
#define WS_EX_OVERLAPPEDWINDOW (WS_EX_WINDOWEDGE | WS_EX_CLIENTEDGE)
#define WS_EX_PALETTEWINDOW \
  (WS_EX_WINDOWEDGE | WS_EX_TOOLWINDOW | WS_EX_TOPMOST)
#define WS_EX_LAYERED 0x00080000
#define WS_EX_NOINHERITLAYOUT 0x00100000L
#define WS_EX_LAYOUTRTL 0x00400000L
#define WS_EX_COMPOSITED 0x02000000L
#define WS_EX_NOACTIVATE 0x08000000L

#define CS_VREDRAW 0x0001
#define CS_HREDRAW 0x0002
#define CS_DBLCLKS 0x0008
#define CS_OWNDC 0x0020
#define CS_CLASSDC 0x0040
#define CS_PARENTDC 0x0080
#define CS_NOCLOSE 0x0200
#define CS_SAVEBITS 0x0800
#define CS_BYTEALIGNCLIENT 0x1000
#define CS_BYTEALIGNWINDOW 0x2000
#define CS_GLOBALCLASS 0x4000
#define CS_IME 0x00010000
#define CS_DROPSHADOW 0x00020000
#endif

#define PRF_CHECKVISIBLE 0x00000001L
#define PRF_NONCLIENT 0x00000002L
#define PRF_CLIENT 0x00000004L
#define PRF_ERASEBKGND 0x00000008L
#define PRF_CHILDREN 0x00000010L
#define PRF_OWNED 0x00000020L

#define BDR_RAISEDOUTER 0x0001
#define BDR_SUNKENOUTER 0x0002
#define BDR_RAISEDINNER 0x0004
#define BDR_SUNKENINNER 0x0008

#define BDR_OUTER (BDR_RAISEDOUTER | BDR_SUNKENOUTER)
#define BDR_INNER (BDR_RAISEDINNER | BDR_SUNKENINNER)
#define BDR_RAISED (BDR_RAISEDOUTER | BDR_RAISEDINNER)
#define BDR_SUNKEN (BDR_SUNKENOUTER | BDR_SUNKENINNER)

#define EDGE_RAISED (BDR_RAISEDOUTER | BDR_RAISEDINNER)
#define EDGE_SUNKEN (BDR_SUNKENOUTER | BDR_SUNKENINNER)
#define EDGE_ETCHED (BDR_SUNKENOUTER | BDR_RAISEDINNER)
#define EDGE_BUMP (BDR_RAISEDOUTER | BDR_SUNKENINNER)

#define BF_LEFT 0x0001
#define BF_TOP 0x0002
#define BF_RIGHT 0x0004
#define BF_BOTTOM 0x0008

#define BF_TOPLEFT (BF_TOP | BF_LEFT)
#define BF_TOPRIGHT (BF_TOP | BF_RIGHT)
#define BF_BOTTOMLEFT (BF_BOTTOM | BF_LEFT)
#define BF_BOTTOMRIGHT (BF_BOTTOM | BF_RIGHT)
#define BF_RECT (BF_LEFT | BF_TOP | BF_RIGHT | BF_BOTTOM)

#define BF_DIAGONAL 0x0010

#define BF_DIAGONAL_ENDTOPRIGHT (BF_DIAGONAL | BF_TOP | BF_RIGHT)
#define BF_DIAGONAL_ENDTOPLEFT (BF_DIAGONAL | BF_TOP | BF_LEFT)
#define BF_DIAGONAL_ENDBOTTOMLEFT (BF_DIAGONAL | BF_BOTTOM | BF_LEFT)
#define BF_DIAGONAL_ENDBOTTOMRIGHT (BF_DIAGONAL | BF_BOTTOM | BF_RIGHT)

#define BF_MIDDLE 0x0800
#define BF_SOFT 0x1000
#define BF_ADJUST 0x2000
#define BF_FLAT 0x4000
#define BF_MONO 0x8000

WINUSERAPI WINBOOL WINAPI DrawEdge(HDC hdc,
                                   LPRECT qrc,
                                   UINT edge,
                                   UINT grfFlags);

#define DFC_CAPTION 1
#define DFC_MENU 2
#define DFC_SCROLL 3
#define DFC_BUTTON 4
#define DFC_POPUPMENU 5

#define DFCS_CAPTIONCLOSE 0x0000
#define DFCS_CAPTIONMIN 0x0001
#define DFCS_CAPTIONMAX 0x0002
#define DFCS_CAPTIONRESTORE 0x0003
#define DFCS_CAPTIONHELP 0x0004

#define DFCS_MENUARROW 0x0000
#define DFCS_MENUCHECK 0x0001
#define DFCS_MENUBULLET 0x0002
#define DFCS_MENUARROWRIGHT 0x0004
#define DFCS_SCROLLUP 0x0000
#define DFCS_SCROLLDOWN 0x0001
#define DFCS_SCROLLLEFT 0x0002
#define DFCS_SCROLLRIGHT 0x0003
#define DFCS_SCROLLCOMBOBOX 0x0005
#define DFCS_SCROLLSIZEGRIP 0x0008
#define DFCS_SCROLLSIZEGRIPRIGHT 0x0010

#define DFCS_BUTTONCHECK 0x0000
#define DFCS_BUTTONRADIOIMAGE 0x0001
#define DFCS_BUTTONRADIOMASK 0x0002
#define DFCS_BUTTONRADIO 0x0004
#define DFCS_BUTTON3STATE 0x0008
#define DFCS_BUTTONPUSH 0x0010

#define DFCS_INACTIVE 0x0100
#define DFCS_PUSHED 0x0200
#define DFCS_CHECKED 0x0400

#define DFCS_TRANSPARENT 0x0800
#define DFCS_HOT 0x1000

#define DFCS_ADJUSTRECT 0x2000
#define DFCS_FLAT 0x4000
#define DFCS_MONO 0x8000

WINUSERAPI WINBOOL WINAPI DrawFrameControl(HDC, LPRECT, UINT, UINT);

#define DC_ACTIVE 0x0001
#define DC_SMALLCAP 0x0002
#define DC_ICON 0x0004
#define DC_TEXT 0x0008
#define DC_INBUTTON 0x0010
#define DC_GRADIENT 0x0020
#define DC_BUTTONS 0x1000

WINUSERAPI WINBOOL WINAPI DrawCaption(HWND hwnd,
                                      HDC hdc,
                                      CONST RECT* lprect,
                                      UINT flags);

#define IDANI_OPEN 1
#define IDANI_CAPTION 3

WINUSERAPI WINBOOL WINAPI DrawAnimatedRects(HWND hwnd,
                                            int idAni,
                                            CONST RECT* lprcFrom,
                                            CONST RECT* lprcTo);

#ifndef NOCLIPBOARD

#define CF_TEXT 1
#define CF_BITMAP 2
#define CF_METAFILEPICT 3
#define CF_SYLK 4
#define CF_DIF 5
#define CF_TIFF 6
#define CF_OEMTEXT 7
#define CF_DIB 8
#define CF_PALETTE 9
#define CF_PENDATA 10
#define CF_RIFF 11
#define CF_WAVE 12
#define CF_UNICODETEXT 13
#define CF_ENHMETAFILE 14
#define CF_HDROP 15
#define CF_LOCALE 16
#define CF_DIBV5 17
#define CF_MAX 18

#define CF_OWNERDISPLAY 0x0080
#define CF_DSPTEXT 0x0081
#define CF_DSPBITMAP 0x0082
#define CF_DSPMETAFILEPICT 0x0083
#define CF_DSPENHMETAFILE 0x008E

#define CF_PRIVATEFIRST 0x0200
#define CF_PRIVATELAST 0x02FF

#define CF_GDIOBJFIRST 0x0300
#define CF_GDIOBJLAST 0x03FF
#endif

#define FVIRTKEY TRUE
#define FNOINVERT 0x02
#define FSHIFT 0x04
#define FCONTROL 0x08
#define FALT 0x10

typedef struct tagACCEL {
  BYTE fVirt;
  WORD key;
  WORD cmd;
} ACCEL, *LPACCEL;

typedef struct tagPAINTSTRUCT {
  HDC hdc;
  WINBOOL fErase;
  RECT rcPaint;
  WINBOOL fRestore;
  WINBOOL fIncUpdate;
  BYTE rgbReserved[32];
} PAINTSTRUCT, *PPAINTSTRUCT, *NPPAINTSTRUCT, *LPPAINTSTRUCT;

typedef struct tagCREATESTRUCTA {
  LPVOID lpCreateParams;
  HINSTANCE hInstance;
  HMENU hMenu;
  HWND hwndParent;
  int cy;
  int cx;
  int y;
  int x;
  LONG style;
  LPCSTR lpszName;
  LPCSTR lpszClass;
  DWORD dwExStyle;
} CREATESTRUCTA, *LPCREATESTRUCTA;

typedef struct tagCREATESTRUCTW {
  LPVOID lpCreateParams;
  HINSTANCE hInstance;
  HMENU hMenu;
  HWND hwndParent;
  int cy;
  int cx;
  int y;
  int x;
  LONG style;
  LPCWSTR lpszName;
  LPCWSTR lpszClass;
  DWORD dwExStyle;
} CREATESTRUCTW, *LPCREATESTRUCTW;

#ifdef UNICODE
typedef CREATESTRUCTW CREATESTRUCT;
typedef LPCREATESTRUCTW LPCREATESTRUCT;
#else
typedef CREATESTRUCTA CREATESTRUCT;
typedef LPCREATESTRUCTA LPCREATESTRUCT;
#endif

typedef struct tagWINDOWPLACEMENT {
  UINT length;
  UINT flags;
  UINT showCmd;
  POINT ptMinPosition;
  POINT ptMaxPosition;
  RECT rcNormalPosition;
} WINDOWPLACEMENT;
typedef WINDOWPLACEMENT *PWINDOWPLACEMENT, *LPWINDOWPLACEMENT;

#define WPF_SETMINPOSITION 0x0001
#define WPF_RESTORETOMAXIMIZED 0x0002
#define WPF_ASYNCWINDOWPLACEMENT 0x0004

typedef struct tagNMHDR {
  HWND hwndFrom;
  UINT_PTR idFrom;
  UINT code;
} NMHDR;

typedef NMHDR* LPNMHDR;

typedef struct tagSTYLESTRUCT {
  DWORD styleOld;
  DWORD styleNew;
} STYLESTRUCT, *LPSTYLESTRUCT;

#define ODT_MENU 1
#define ODT_LISTBOX 2
#define ODT_COMBOBOX 3
#define ODT_BUTTON 4
#define ODT_STATIC 5

#define ODA_DRAWENTIRE 0x0001
#define ODA_SELECT 0x0002
#define ODA_FOCUS 0x0004

#define ODS_SELECTED 0x0001
#define ODS_GRAYED 0x0002
#define ODS_DISABLED 0x0004
#define ODS_CHECKED 0x0008
#define ODS_FOCUS 0x0010
#define ODS_DEFAULT 0x0020
#define ODS_COMBOBOXEDIT 0x1000
#define ODS_HOTLIGHT 0x0040
#define ODS_INACTIVE 0x0080
#define ODS_NOACCEL 0x0100
#define ODS_NOFOCUSRECT 0x0200

typedef struct tagMEASUREITEMSTRUCT {
  UINT CtlType;
  UINT CtlID;
  UINT itemID;
  UINT itemWidth;
  UINT itemHeight;
  ULONG_PTR itemData;
} MEASUREITEMSTRUCT, *PMEASUREITEMSTRUCT, *LPMEASUREITEMSTRUCT;

typedef struct tagDRAWITEMSTRUCT {
  UINT CtlType;
  UINT CtlID;
  UINT itemID;
  UINT itemAction;
  UINT itemState;
  HWND hwndItem;
  HDC hDC;
  RECT rcItem;
  ULONG_PTR itemData;
} DRAWITEMSTRUCT, *PDRAWITEMSTRUCT, *LPDRAWITEMSTRUCT;

typedef struct tagDELETEITEMSTRUCT {
  UINT CtlType;
  UINT CtlID;
  UINT itemID;
  HWND hwndItem;
  ULONG_PTR itemData;
} DELETEITEMSTRUCT, *PDELETEITEMSTRUCT, *LPDELETEITEMSTRUCT;

typedef struct tagCOMPAREITEMSTRUCT {
  UINT CtlType;
  UINT CtlID;
  HWND hwndItem;
  UINT itemID1;
  ULONG_PTR itemData1;
  UINT itemID2;
  ULONG_PTR itemData2;
  DWORD dwLocaleId;
} COMPAREITEMSTRUCT, *PCOMPAREITEMSTRUCT, *LPCOMPAREITEMSTRUCT;

#ifndef NOMSG
#ifdef UNICODE
#define GetMessage GetMessageW
#define DispatchMessage DispatchMessageW
#define PeekMessage PeekMessageW
#else
#define GetMessage GetMessageA
#define DispatchMessage DispatchMessageA
#define PeekMessage PeekMessageA
#endif

WINUSERAPI WINBOOL WINAPI GetMessageA(LPMSG lpMsg,
                                      HWND hWnd,
                                      UINT wMsgFilterMin,
                                      UINT wMsgFilterMax);
WINUSERAPI WINBOOL WINAPI GetMessageW(LPMSG lpMsg,
                                      HWND hWnd,
                                      UINT wMsgFilterMin,
                                      UINT wMsgFilterMax);
WINUSERAPI WINBOOL WINAPI TranslateMessage(CONST MSG* lpMsg);
WINUSERAPI LRESULT WINAPI DispatchMessageA(CONST MSG* lpMsg);
WINUSERAPI LRESULT WINAPI DispatchMessageW(CONST MSG* lpMsg);
WINUSERAPI WINBOOL WINAPI SetMessageQueue(int cMessagesMax);
WINUSERAPI WINBOOL WINAPI PeekMessageA(LPMSG lpMsg,
                                       HWND hWnd,
                                       UINT wMsgFilterMin,
                                       UINT wMsgFilterMax,
                                       UINT wRemoveMsg);
WINUSERAPI WINBOOL WINAPI PeekMessageW(LPMSG lpMsg,
                                       HWND hWnd,
                                       UINT wMsgFilterMin,
                                       UINT wMsgFilterMax,
                                       UINT wRemoveMsg);

#define PM_NOREMOVE 0x0000
#define PM_REMOVE 0x0001
#define PM_NOYIELD 0x0002
#define PM_QS_INPUT (QS_INPUT << 16)
#define PM_QS_POSTMESSAGE ((QS_POSTMESSAGE | QS_HOTKEY | QS_TIMER) << 16)
#define PM_QS_PAINT (QS_PAINT << 16)
#define PM_QS_SENDMESSAGE (QS_SENDMESSAGE << 16)
#endif

WINUSERAPI WINBOOL WINAPI RegisterHotKey(HWND hWnd,
                                         int id,
                                         UINT fsModifiers,
                                         UINT vk);
WINUSERAPI WINBOOL WINAPI UnregisterHotKey(HWND hWnd, int id);

#define MOD_ALT 0x0001
#define MOD_CONTROL 0x0002
#define MOD_SHIFT 0x0004
#define MOD_WIN 0x0008

#define IDHOT_SNAPWINDOW (-1)
#define IDHOT_SNAPDESKTOP (-2)

#ifdef WIN_INTERNAL
#ifndef LSTRING
#define NOLSTRING
#endif
#ifndef LFILEIO
#define NOLFILEIO
#endif
#endif

#define ENDSESSION_LOGOFF 0x80000000

#define EWX_LOGOFF 0
#define EWX_SHUTDOWN 0x00000001
#define EWX_REBOOT 0x00000002
#define EWX_FORCE 0x00000004
#define EWX_POWEROFF 0x00000008
#define EWX_FORCEIFHUNG 0x00000010

#define ExitWindows(dwReserved, Code) ExitWindowsEx(EWX_LOGOFF, 0xFFFFFFFF)

#ifdef UNICODE
#define SendMessage SendMessageW
#define SendMessageTimeout SendMessageTimeoutW
#define SendNotifyMessage SendNotifyMessageW
#define SendMessageCallback SendMessageCallbackW
#else
#define SendMessage SendMessageA
#define SendMessageTimeout SendMessageTimeoutA
#define SendNotifyMessage SendNotifyMessageA
#define SendMessageCallback SendMessageCallbackA
#endif

WINUSERAPI WINBOOL WINAPI ExitWindowsEx(UINT uFlags, DWORD dwReason);
WINUSERAPI WINBOOL WINAPI SwapMouseButton(WINBOOL fSwap);
WINUSERAPI DWORD WINAPI GetMessagePos(VOID);
WINUSERAPI LONG WINAPI GetMessageTime(VOID);
WINUSERAPI LPARAM WINAPI GetMessageExtraInfo(VOID);
WINUSERAPI WINBOOL WINAPI IsWow64Message(VOID);
WINUSERAPI LPARAM WINAPI SetMessageExtraInfo(LPARAM lParam);
WINUSERAPI LRESULT WINAPI SendMessageA(HWND hWnd,
                                       UINT Msg,
                                       WPARAM wParam,
                                       LPARAM lParam);
WINUSERAPI LRESULT WINAPI SendMessageW(HWND hWnd,
                                       UINT Msg,
                                       WPARAM wParam,
                                       LPARAM lParam);
WINUSERAPI LRESULT WINAPI SendMessageTimeoutA(HWND hWnd,
                                              UINT Msg,
                                              WPARAM wParam,
                                              LPARAM lParam,
                                              UINT fuFlags,
                                              UINT uTimeout,
                                              PDWORD_PTR lpdwResult);
WINUSERAPI LRESULT WINAPI SendMessageTimeoutW(HWND hWnd,
                                              UINT Msg,
                                              WPARAM wParam,
                                              LPARAM lParam,
                                              UINT fuFlags,
                                              UINT uTimeout,
                                              PDWORD_PTR lpdwResult);
WINUSERAPI WINBOOL WINAPI SendNotifyMessageA(HWND hWnd,
                                             UINT Msg,
                                             WPARAM wParam,
                                             LPARAM lParam);
WINUSERAPI WINBOOL WINAPI SendNotifyMessageW(HWND hWnd,
                                             UINT Msg,
                                             WPARAM wParam,
                                             LPARAM lParam);
WINUSERAPI WINBOOL WINAPI SendMessageCallbackA(HWND hWnd,
                                               UINT Msg,
                                               WPARAM wParam,
                                               LPARAM lParam,
                                               SENDASYNCPROC lpResultCallBack,
                                               ULONG_PTR dwData);
WINUSERAPI WINBOOL WINAPI SendMessageCallbackW(HWND hWnd,
                                               UINT Msg,
                                               WPARAM wParam,
                                               LPARAM lParam,
                                               SENDASYNCPROC lpResultCallBack,
                                               ULONG_PTR dwData);

typedef struct {
  UINT cbSize;
  HDESK hdesk;
  HWND hwnd;
  LUID luid;
} BSMINFO, *PBSMINFO;

#ifdef UNICODE
#define BroadcastSystemMessageEx BroadcastSystemMessageExW
#define BroadcastSystemMessage BroadcastSystemMessageW
#else
#define BroadcastSystemMessageEx BroadcastSystemMessageExA
#define BroadcastSystemMessage BroadcastSystemMessageA
#endif

WINUSERAPI long WINAPI BroadcastSystemMessageExA(DWORD flags,
                                                 LPDWORD lpInfo,
                                                 UINT Msg,
                                                 WPARAM wParam,
                                                 LPARAM lParam,
                                                 PBSMINFO pbsmInfo);
WINUSERAPI long WINAPI BroadcastSystemMessageExW(DWORD flags,
                                                 LPDWORD lpInfo,
                                                 UINT Msg,
                                                 WPARAM wParam,
                                                 LPARAM lParam,
                                                 PBSMINFO pbsmInfo);
WINUSERAPI long WINAPI BroadcastSystemMessageA(DWORD flags,
                                               LPDWORD lpInfo,
                                               UINT Msg,
                                               WPARAM wParam,
                                               LPARAM lParam);
WINUSERAPI long WINAPI BroadcastSystemMessageW(DWORD flags,
                                               LPDWORD lpInfo,
                                               UINT Msg,
                                               WPARAM wParam,
                                               LPARAM lParam);

#define BSM_ALLCOMPONENTS 0x00000000
#define BSM_VXDS 0x00000001
#define BSM_NETDRIVER 0x00000002
#define BSM_INSTALLABLEDRIVERS 0x00000004
#define BSM_APPLICATIONS 0x00000008
#define BSM_ALLDESKTOPS 0x00000010

#define BSF_QUERY 0x00000001
#define BSF_IGNORECURRENTTASK 0x00000002
#define BSF_FLUSHDISK 0x00000004
#define BSF_NOHANG 0x00000008
#define BSF_POSTMESSAGE 0x00000010
#define BSF_FORCEIFHUNG 0x00000020
#define BSF_NOTIMEOUTIFNOTHUNG 0x00000040
#define BSF_ALLOWSFW 0x00000080
#define BSF_SENDNOTIFYMESSAGE 0x00000100
#define BSF_RETURNHDESK 0x00000200
#define BSF_LUID 0x00000400

#define BROADCAST_QUERY_DENY 0x424D5144

typedef PVOID HDEVNOTIFY;
typedef HDEVNOTIFY* PHDEVNOTIFY;

#define DEVICE_NOTIFY_WINDOW_HANDLE 0x00000000
#define DEVICE_NOTIFY_SERVICE_HANDLE 0x00000001
#define DEVICE_NOTIFY_ALL_INTERFACE_CLASSES 0x00000004

#ifdef UNICODE
#define RegisterDeviceNotification RegisterDeviceNotificationW
#define PostMessage PostMessageW
#define PostThreadMessage PostThreadMessageW
#define PostAppMessage PostAppMessageW
#define DefWindowProc DefWindowProcW
#define CallWindowProc CallWindowProcW
#define RegisterClass RegisterClassW
#define UnregisterClass UnregisterClassW
#define GetClassInfo GetClassInfoW
#define RegisterClassEx RegisterClassExW
#define GetClassInfoEx GetClassInfoExW
#else
#define RegisterDeviceNotification RegisterDeviceNotificationA
#define PostMessage PostMessageA
#define PostThreadMessage PostThreadMessageA
#define PostAppMessage PostAppMessageA
#define DefWindowProc DefWindowProcA
#define CallWindowProc CallWindowProcA
#define RegisterClass RegisterClassA
#define UnregisterClass UnregisterClassA
#define GetClassInfo GetClassInfoA
#define RegisterClassEx RegisterClassExA
#define GetClassInfoEx GetClassInfoExA
#endif

WINUSERAPI HDEVNOTIFY WINAPI
RegisterDeviceNotificationA(HANDLE hRecipient,
                            LPVOID NotificationFilter,
                            DWORD Flags);
WINUSERAPI HDEVNOTIFY WINAPI
RegisterDeviceNotificationW(HANDLE hRecipient,
                            LPVOID NotificationFilter,
                            DWORD Flags);
WINUSERAPI WINBOOL WINAPI UnregisterDeviceNotification(HDEVNOTIFY Handle);
WINUSERAPI WINBOOL WINAPI PostMessageA(HWND hWnd,
                                       UINT Msg,
                                       WPARAM wParam,
                                       LPARAM lParam);
WINUSERAPI WINBOOL WINAPI PostMessageW(HWND hWnd,
                                       UINT Msg,
                                       WPARAM wParam,
                                       LPARAM lParam);
WINUSERAPI WINBOOL WINAPI PostThreadMessageA(DWORD idThread,
                                             UINT Msg,
                                             WPARAM wParam,
                                             LPARAM lParam);
WINUSERAPI WINBOOL WINAPI PostThreadMessageW(DWORD idThread,
                                             UINT Msg,
                                             WPARAM wParam,
                                             LPARAM lParam);
#define PostAppMessageA(idThread, wMsg, wParam, lParam) \
  PostThreadMessageA((DWORD)idThread, wMsg, wParam, lParam)
#define PostAppMessageW(idThread, wMsg, wParam, lParam) \
  PostThreadMessageW((DWORD)idThread, wMsg, wParam, lParam)

#define HWND_BROADCAST ((HWND)0xffff)
#define HWND_MESSAGE ((HWND)-3)

WINUSERAPI WINBOOL WINAPI AttachThreadInput(DWORD idAttach,
                                            DWORD idAttachTo,
                                            WINBOOL fAttach);
WINUSERAPI WINBOOL WINAPI ReplyMessage(LRESULT lResult);
WINUSERAPI WINBOOL WINAPI WaitMessage(VOID);
WINUSERAPI DWORD WINAPI WaitForInputIdle(HANDLE hProcess, DWORD dwMilliseconds);
WINUSERAPI LRESULT WINAPI DefWindowProcA(HWND hWnd,
                                         UINT Msg,
                                         WPARAM wParam,
                                         LPARAM lParam);
WINUSERAPI LRESULT WINAPI DefWindowProcW(HWND hWnd,
                                         UINT Msg,
                                         WPARAM wParam,
                                         LPARAM lParam);
WINUSERAPI VOID WINAPI PostQuitMessage(int nExitCode);
WINUSERAPI LRESULT WINAPI CallWindowProcA(WNDPROC lpPrevWndFunc,
                                          HWND hWnd,
                                          UINT Msg,
                                          WPARAM wParam,
                                          LPARAM lParam);
WINUSERAPI LRESULT WINAPI CallWindowProcW(WNDPROC lpPrevWndFunc,
                                          HWND hWnd,
                                          UINT Msg,
                                          WPARAM wParam,
                                          LPARAM lParam);
WINUSERAPI WINBOOL WINAPI InSendMessage(VOID);
WINUSERAPI DWORD WINAPI InSendMessageEx(LPVOID lpReserved);

#define ISMEX_NOSEND 0x00000000
#define ISMEX_SEND 0x00000001
#define ISMEX_NOTIFY 0x00000002
#define ISMEX_CALLBACK 0x00000004
#define ISMEX_REPLIED 0x00000008

WINUSERAPI UINT WINAPI GetDoubleClickTime(VOID);
WINUSERAPI WINBOOL WINAPI SetDoubleClickTime(UINT);
WINUSERAPI ATOM WINAPI RegisterClassA(CONST WNDCLASSA* lpWndClass);
WINUSERAPI ATOM WINAPI RegisterClassW(CONST WNDCLASSW* lpWndClass);
WINUSERAPI WINBOOL WINAPI UnregisterClassA(LPCSTR lpClassName,
                                           HINSTANCE hInstance);
WINUSERAPI WINBOOL WINAPI UnregisterClassW(LPCWSTR lpClassName,
                                           HINSTANCE hInstance);
WINUSERAPI WINBOOL WINAPI GetClassInfoA(HINSTANCE hInstance,
                                        LPCSTR lpClassName,
                                        LPWNDCLASSA lpWndClass);
WINUSERAPI WINBOOL WINAPI GetClassInfoW(HINSTANCE hInstance,
                                        LPCWSTR lpClassName,
                                        LPWNDCLASSW lpWndClass);
WINUSERAPI ATOM WINAPI RegisterClassExA(CONST WNDCLASSEXA*);
WINUSERAPI ATOM WINAPI RegisterClassExW(CONST WNDCLASSEXW*);
WINUSERAPI WINBOOL WINAPI GetClassInfoExA(HINSTANCE hInstance,
                                          LPCSTR lpszClass,
                                          LPWNDCLASSEXA lpwcx);
WINUSERAPI WINBOOL WINAPI GetClassInfoExW(HINSTANCE hInstance,
                                          LPCWSTR lpszClass,
                                          LPWNDCLASSEXW lpwcx);

#define CW_USEDEFAULT ((int)0x80000000)

#define HWND_DESKTOP ((HWND)0)

typedef BOOLEAN(WINAPI* PREGISTERCLASSNAMEW)(LPCWSTR);

#ifdef UNICODE
#define CreateWindowEx CreateWindowExW
#define CreateWindow CreateWindowW
#else
#define CreateWindowEx CreateWindowExA
#define CreateWindow CreateWindowA
#endif

WINUSERAPI HWND WINAPI CreateWindowExA(DWORD dwExStyle,
                                       LPCSTR lpClassName,
                                       LPCSTR lpWindowName,
                                       DWORD dwStyle,
                                       int X,
                                       int Y,
                                       int nWidth,
                                       int nHeight,
                                       HWND hWndParent,
                                       HMENU hMenu,
                                       HINSTANCE hInstance,
                                       LPVOID lpParam);
WINUSERAPI HWND WINAPI CreateWindowExW(DWORD dwExStyle,
                                       LPCWSTR lpClassName,
                                       LPCWSTR lpWindowName,
                                       DWORD dwStyle,
                                       int X,
                                       int Y,
                                       int nWidth,
                                       int nHeight,
                                       HWND hWndParent,
                                       HMENU hMenu,
                                       HINSTANCE hInstance,
                                       LPVOID lpParam);
#define CreateWindowA(lpClassName, lpWindowName, dwStyle, x, y, nWidth, \
                      nHeight, hWndParent, hMenu, hInstance, lpParam)   \
  CreateWindowExA(0L, lpClassName, lpWindowName, dwStyle, x, y, nWidth, \
                  nHeight, hWndParent, hMenu, hInstance, lpParam)
#define CreateWindowW(lpClassName, lpWindowName, dwStyle, x, y, nWidth, \
                      nHeight, hWndParent, hMenu, hInstance, lpParam)   \
  CreateWindowExW(0L, lpClassName, lpWindowName, dwStyle, x, y, nWidth, \
                  nHeight, hWndParent, hMenu, hInstance, lpParam)
WINUSERAPI WINBOOL WINAPI IsWindow(HWND hWnd);
WINUSERAPI WINBOOL WINAPI IsMenu(HMENU hMenu);
WINUSERAPI WINBOOL WINAPI IsChild(HWND hWndParent, HWND hWnd);
WINUSERAPI WINBOOL WINAPI DestroyWindow(HWND hWnd);
WINUSERAPI WINBOOL WINAPI ShowWindow(HWND hWnd, int nCmdShow);
WINUSERAPI WINBOOL WINAPI AnimateWindow(HWND hWnd, DWORD dwTime, DWORD dwFlags);

#if defined(_WINGDI_) && !defined(NOGDI)
WINUSERAPI WINBOOL WINAPI UpdateLayeredWindow(HWND hWnd,
                                              HDC hdcDst,
                                              POINT* pptDst,
                                              SIZE* psize,
                                              HDC hdcSrc,
                                              POINT* pptSrc,
                                              COLORREF crKey,
                                              BLENDFUNCTION* pblend,
                                              DWORD dwFlags);

typedef struct tagUPDATELAYEREDWINDOWINFO {
  DWORD cbSize;
  HDC hdcDst;
  POINT CONST* pptDst;
  SIZE CONST* psize;
  HDC hdcSrc;
  POINT CONST* pptSrc;
  COLORREF crKey;
  BLENDFUNCTION CONST* pblend;
  DWORD dwFlags;
  RECT CONST* prcDirty;
} UPDATELAYEREDWINDOWINFO, *PUPDATELAYEREDWINDOWINFO;

WINUSERAPI WINBOOL WINAPI
UpdateLayeredWindowIndirect(HWND hWnd, UPDATELAYEREDWINDOWINFO CONST* pULWInfo);
WINUSERAPI WINBOOL WINAPI GetLayeredWindowAttributes(HWND hwnd,
                                                     COLORREF* pcrKey,
                                                     BYTE* pbAlpha,
                                                     DWORD* pdwFlags);

#define PW_CLIENTONLY 0x00000001

WINUSERAPI WINBOOL WINAPI PrintWindow(HWND hwnd, HDC hdcBlt, UINT nFlags);
WINUSERAPI WINBOOL WINAPI SetLayeredWindowAttributes(HWND hwnd,
                                                     COLORREF crKey,
                                                     BYTE bAlpha,
                                                     DWORD dwFlags);

#define LWA_COLORKEY 0x00000001
#define LWA_ALPHA 0x00000002

#define ULW_COLORKEY 0x00000001
#define ULW_ALPHA 0x00000002
#define ULW_OPAQUE 0x00000004

#define ULW_EX_NORESIZE 0x00000008

WINUSERAPI WINBOOL WINAPI ShowWindowAsync(HWND hWnd, int nCmdShow);
WINUSERAPI WINBOOL WINAPI FlashWindow(HWND hWnd, WINBOOL bInvert);

typedef struct {
  UINT cbSize;
  HWND hwnd;
  DWORD dwFlags;
  UINT uCount;
  DWORD dwTimeout;
} FLASHWINFO, *PFLASHWINFO;

WINUSERAPI WINBOOL WINAPI FlashWindowEx(PFLASHWINFO pfwi);

#define FLASHW_STOP 0
#define FLASHW_CAPTION 0x00000001
#define FLASHW_TRAY 0x00000002
#define FLASHW_ALL (FLASHW_CAPTION | FLASHW_TRAY)
#define FLASHW_TIMER 0x00000004
#define FLASHW_TIMERNOFG 0x0000000C

WINUSERAPI WINBOOL WINAPI ShowOwnedPopups(HWND hWnd, WINBOOL fShow);
WINUSERAPI WINBOOL WINAPI OpenIcon(HWND hWnd);
WINUSERAPI WINBOOL WINAPI CloseWindow(HWND hWnd);
WINUSERAPI WINBOOL WINAPI
MoveWindow(HWND hWnd, int X, int Y, int nWidth, int nHeight, WINBOOL bRepaint);
WINUSERAPI WINBOOL WINAPI SetWindowPos(HWND hWnd,
                                       HWND hWndInsertAfter,
                                       int X,
                                       int Y,
                                       int cx,
                                       int cy,
                                       UINT uFlags);
WINUSERAPI WINBOOL WINAPI GetWindowPlacement(HWND hWnd,
                                             WINDOWPLACEMENT* lpwndpl);
WINUSERAPI WINBOOL WINAPI SetWindowPlacement(HWND hWnd,
                                             CONST WINDOWPLACEMENT* lpwndpl);

#ifndef NODEFERWINDOWPOS
WINUSERAPI HDWP WINAPI BeginDeferWindowPos(int nNumWindows);
WINUSERAPI HDWP WINAPI DeferWindowPos(HDWP hWinPosInfo,
                                      HWND hWnd,
                                      HWND hWndInsertAfter,
                                      int x,
                                      int y,
                                      int cx,
                                      int cy,
                                      UINT uFlags);
WINUSERAPI WINBOOL WINAPI EndDeferWindowPos(HDWP hWinPosInfo);
#endif

WINUSERAPI WINBOOL WINAPI IsWindowVisible(HWND hWnd);
WINUSERAPI WINBOOL WINAPI IsIconic(HWND hWnd);
WINUSERAPI WINBOOL WINAPI AnyPopup(VOID);
WINUSERAPI WINBOOL WINAPI BringWindowToTop(HWND hWnd);
WINUSERAPI WINBOOL WINAPI IsZoomed(HWND hWnd);

#define SWP_NOSIZE 0x0001
#define SWP_NOMOVE 0x0002
#define SWP_NOZORDER 0x0004
#define SWP_NOREDRAW 0x0008
#define SWP_NOACTIVATE 0x0010
#define SWP_FRAMECHANGED 0x0020
#define SWP_SHOWWINDOW 0x0040
#define SWP_HIDEWINDOW 0x0080
#define SWP_NOCOPYBITS 0x0100
#define SWP_NOOWNERZORDER 0x0200
#define SWP_NOSENDCHANGING 0x0400

#define SWP_DRAWFRAME SWP_FRAMECHANGED
#define SWP_NOREPOSITION SWP_NOOWNERZORDER
#define SWP_DEFERERASE 0x2000
#define SWP_ASYNCWINDOWPOS 0x4000

#define HWND_TOP ((HWND)0)
#define HWND_BOTTOM ((HWND)1)
#define HWND_TOPMOST ((HWND)-1)
#define HWND_NOTOPMOST ((HWND)-2)

#ifndef NOCTLMGR

#include <pshpack2.h>

typedef struct {
  DWORD style;
  DWORD dwExtendedStyle;
  WORD cdit;
  short x;
  short y;
  short cx;
  short cy;
} DLGTEMPLATE;

typedef DLGTEMPLATE* LPDLGTEMPLATEA;
typedef DLGTEMPLATE* LPDLGTEMPLATEW;

#ifdef UNICODE
typedef LPDLGTEMPLATEW LPDLGTEMPLATE;
#else
typedef LPDLGTEMPLATEA LPDLGTEMPLATE;
#endif

typedef CONST DLGTEMPLATE* LPCDLGTEMPLATEA;
typedef CONST DLGTEMPLATE* LPCDLGTEMPLATEW;

#ifdef UNICODE
typedef LPCDLGTEMPLATEW LPCDLGTEMPLATE;
#else
typedef LPCDLGTEMPLATEA LPCDLGTEMPLATE;
#endif

typedef struct {
  DWORD style;
  DWORD dwExtendedStyle;
  short x;
  short y;
  short cx;
  short cy;
  WORD id;
} DLGITEMTEMPLATE;

typedef DLGITEMTEMPLATE* PDLGITEMTEMPLATEA;
typedef DLGITEMTEMPLATE* PDLGITEMTEMPLATEW;

#ifdef UNICODE
typedef PDLGITEMTEMPLATEW PDLGITEMTEMPLATE;
#else
typedef PDLGITEMTEMPLATEA PDLGITEMTEMPLATE;
#endif

typedef DLGITEMTEMPLATE* LPDLGITEMTEMPLATEA;
typedef DLGITEMTEMPLATE* LPDLGITEMTEMPLATEW;

#ifdef UNICODE
typedef LPDLGITEMTEMPLATEW LPDLGITEMTEMPLATE;
#else
typedef LPDLGITEMTEMPLATEA LPDLGITEMTEMPLATE;
#endif

#include <poppack.h>

#ifdef UNICODE
#define CreateDialogParam CreateDialogParamW
#define CreateDialogIndirectParam CreateDialogIndirectParamW
#define CreateDialog CreateDialogW
#define CreateDialogIndirect CreateDialogIndirectW
#define DialogBoxParam DialogBoxParamW
#define DialogBoxIndirectParam DialogBoxIndirectParamW
#define DialogBox DialogBoxW
#define DialogBoxIndirect DialogBoxIndirectW
#define SetDlgItemText SetDlgItemTextW
#define GetDlgItemText GetDlgItemTextW
#define SendDlgItemMessage SendDlgItemMessageW
#define DefDlgProc DefDlgProcW
#else
#define CreateDialogParam CreateDialogParamA
#define CreateDialogIndirectParam CreateDialogIndirectParamA
#define CreateDialog CreateDialogA
#define CreateDialogIndirect CreateDialogIndirectA
#define DialogBoxParam DialogBoxParamA
#define DialogBoxIndirectParam DialogBoxIndirectParamA
#define DialogBox DialogBoxA
#define DialogBoxIndirect DialogBoxIndirectA
#define SetDlgItemText SetDlgItemTextA
#define GetDlgItemText GetDlgItemTextA
#define SendDlgItemMessage SendDlgItemMessageA
#define DefDlgProc DefDlgProcA
#endif

WINUSERAPI HWND WINAPI CreateDialogParamA(HINSTANCE hInstance,
                                          LPCSTR lpTemplateName,
                                          HWND hWndParent,
                                          DLGPROC lpDialogFunc,
                                          LPARAM dwInitParam);
WINUSERAPI HWND WINAPI CreateDialogParamW(HINSTANCE hInstance,
                                          LPCWSTR lpTemplateName,
                                          HWND hWndParent,
                                          DLGPROC lpDialogFunc,
                                          LPARAM dwInitParam);
WINUSERAPI HWND WINAPI CreateDialogIndirectParamA(HINSTANCE hInstance,
                                                  LPCDLGTEMPLATEA lpTemplate,
                                                  HWND hWndParent,
                                                  DLGPROC lpDialogFunc,
                                                  LPARAM dwInitParam);
WINUSERAPI HWND WINAPI CreateDialogIndirectParamW(HINSTANCE hInstance,
                                                  LPCDLGTEMPLATEW lpTemplate,
                                                  HWND hWndParent,
                                                  DLGPROC lpDialogFunc,
                                                  LPARAM dwInitParam);
#define CreateDialogA(hInstance, lpName, hWndParent, lpDialogFunc) \
  CreateDialogParamA(hInstance, lpName, hWndParent, lpDialogFunc, 0L)
#define CreateDialogW(hInstance, lpName, hWndParent, lpDialogFunc) \
  CreateDialogParamW(hInstance, lpName, hWndParent, lpDialogFunc, 0L)
#define CreateDialogIndirectA(hInstance, lpTemplate, hWndParent, lpDialogFunc) \
  CreateDialogIndirectParamA(hInstance, lpTemplate, hWndParent, lpDialogFunc,  \
                             0L)
#define CreateDialogIndirectW(hInstance, lpTemplate, hWndParent, lpDialogFunc) \
  CreateDialogIndirectParamW(hInstance, lpTemplate, hWndParent, lpDialogFunc,  \
                             0L)
WINUSERAPI INT_PTR WINAPI DialogBoxParamA(HINSTANCE hInstance,
                                          LPCSTR lpTemplateName,
                                          HWND hWndParent,
                                          DLGPROC lpDialogFunc,
                                          LPARAM dwInitParam);
WINUSERAPI INT_PTR WINAPI DialogBoxParamW(HINSTANCE hInstance,
                                          LPCWSTR lpTemplateName,
                                          HWND hWndParent,
                                          DLGPROC lpDialogFunc,
                                          LPARAM dwInitParam);
WINUSERAPI INT_PTR WINAPI
DialogBoxIndirectParamA(HINSTANCE hInstance,
                        LPCDLGTEMPLATEA hDialogTemplate,
                        HWND hWndParent,
                        DLGPROC lpDialogFunc,
                        LPARAM dwInitParam);
WINUSERAPI INT_PTR WINAPI
DialogBoxIndirectParamW(HINSTANCE hInstance,
                        LPCDLGTEMPLATEW hDialogTemplate,
                        HWND hWndParent,
                        DLGPROC lpDialogFunc,
                        LPARAM dwInitParam);
#define DialogBoxA(hInstance, lpTemplate, hWndParent, lpDialogFunc) \
  DialogBoxParamA(hInstance, lpTemplate, hWndParent, lpDialogFunc, 0L)
#define DialogBoxW(hInstance, lpTemplate, hWndParent, lpDialogFunc) \
  DialogBoxParamW(hInstance, lpTemplate, hWndParent, lpDialogFunc, 0L)
#define DialogBoxIndirectA(hInstance, lpTemplate, hWndParent, lpDialogFunc) \
  DialogBoxIndirectParamA(hInstance, lpTemplate, hWndParent, lpDialogFunc, 0L)
#define DialogBoxIndirectW(hInstance, lpTemplate, hWndParent, lpDialogFunc) \
  DialogBoxIndirectParamW(hInstance, lpTemplate, hWndParent, lpDialogFunc, 0L)
WINUSERAPI WINBOOL WINAPI EndDialog(HWND hDlg, INT_PTR nResult);
WINUSERAPI HWND WINAPI GetDlgItem(HWND hDlg, int nIDDlgItem);
WINUSERAPI WINBOOL WINAPI SetDlgItemInt(HWND hDlg,
                                        int nIDDlgItem,
                                        UINT uValue,
                                        WINBOOL bSigned);
WINUSERAPI UINT WINAPI GetDlgItemInt(HWND hDlg,
                                     int nIDDlgItem,
                                     WINBOOL* lpTranslated,
                                     WINBOOL bSigned);
WINUSERAPI WINBOOL WINAPI SetDlgItemTextA(HWND hDlg,
                                          int nIDDlgItem,
                                          LPCSTR lpString);
WINUSERAPI WINBOOL WINAPI SetDlgItemTextW(HWND hDlg,
                                          int nIDDlgItem,
                                          LPCWSTR lpString);
WINUSERAPI UINT WINAPI GetDlgItemTextA(HWND hDlg,
                                       int nIDDlgItem,
                                       LPSTR lpString,
                                       int cchMax);
WINUSERAPI UINT WINAPI GetDlgItemTextW(HWND hDlg,
                                       int nIDDlgItem,
                                       LPWSTR lpString,
                                       int cchMax);
WINUSERAPI WINBOOL WINAPI CheckDlgButton(HWND hDlg, int nIDButton, UINT uCheck);
WINUSERAPI WINBOOL WINAPI CheckRadioButton(HWND hDlg,
                                           int nIDFirstButton,
                                           int nIDLastButton,
                                           int nIDCheckButton);
WINUSERAPI UINT WINAPI IsDlgButtonChecked(HWND hDlg, int nIDButton);
WINUSERAPI LRESULT WINAPI SendDlgItemMessageA(HWND hDlg,
                                              int nIDDlgItem,
                                              UINT Msg,
                                              WPARAM wParam,
                                              LPARAM lParam);
WINUSERAPI LRESULT WINAPI SendDlgItemMessageW(HWND hDlg,
                                              int nIDDlgItem,
                                              UINT Msg,
                                              WPARAM wParam,
                                              LPARAM lParam);
WINUSERAPI HWND WINAPI GetNextDlgGroupItem(HWND hDlg,
                                           HWND hCtl,
                                           WINBOOL bPrevious);
WINUSERAPI HWND WINAPI GetNextDlgTabItem(HWND hDlg,
                                         HWND hCtl,
                                         WINBOOL bPrevious);
WINUSERAPI int WINAPI GetDlgCtrlID(HWND hWnd);
WINUSERAPI long WINAPI GetDialogBaseUnits(VOID);
WINUSERAPI LRESULT WINAPI DefDlgProcA(HWND hDlg,
                                      UINT Msg,
                                      WPARAM wParam,
                                      LPARAM lParam);
WINUSERAPI LRESULT WINAPI DefDlgProcW(HWND hDlg,
                                      UINT Msg,
                                      WPARAM wParam,
                                      LPARAM lParam);

#define DLGWINDOWEXTRA 30
#endif

#ifndef NOMSG

#ifdef UNICODE
#define CallMsgFilter CallMsgFilterW
#else
#define CallMsgFilter CallMsgFilterA
#endif

WINUSERAPI WINBOOL WINAPI CallMsgFilterA(LPMSG lpMsg, int nCode);
WINUSERAPI WINBOOL WINAPI CallMsgFilterW(LPMSG lpMsg, int nCode);
#endif

#ifndef NOCLIPBOARD

#ifdef UNICODE
#define RegisterClipboardFormat RegisterClipboardFormatW
#define GetClipboardFormatName GetClipboardFormatNameW
#else
#define RegisterClipboardFormat RegisterClipboardFormatA
#define GetClipboardFormatName GetClipboardFormatNameA
#endif

WINUSERAPI WINBOOL WINAPI OpenClipboard(HWND hWndNewOwner);
WINUSERAPI WINBOOL WINAPI CloseClipboard(VOID);
WINUSERAPI DWORD WINAPI GetClipboardSequenceNumber(VOID);
WINUSERAPI HWND WINAPI GetClipboardOwner(VOID);
WINUSERAPI HWND WINAPI SetClipboardViewer(HWND hWndNewViewer);
WINUSERAPI HWND WINAPI GetClipboardViewer(VOID);
WINUSERAPI WINBOOL WINAPI ChangeClipboardChain(HWND hWndRemove,
                                               HWND hWndNewNext);
WINUSERAPI HANDLE WINAPI SetClipboardData(UINT uFormat, HANDLE hMem);
WINUSERAPI HANDLE WINAPI GetClipboardData(UINT uFormat);
WINUSERAPI UINT WINAPI RegisterClipboardFormatA(LPCSTR lpszFormat);
WINUSERAPI UINT WINAPI RegisterClipboardFormatW(LPCWSTR lpszFormat);
WINUSERAPI int WINAPI CountClipboardFormats(VOID);
WINUSERAPI UINT WINAPI EnumClipboardFormats(UINT format);
WINUSERAPI int WINAPI GetClipboardFormatNameA(UINT format,
                                              LPSTR lpszFormatName,
                                              int cchMaxCount);
WINUSERAPI int WINAPI GetClipboardFormatNameW(UINT format,
                                              LPWSTR lpszFormatName,
                                              int cchMaxCount);
WINUSERAPI WINBOOL WINAPI EmptyClipboard(VOID);
WINUSERAPI WINBOOL WINAPI IsClipboardFormatAvailable(UINT format);
WINUSERAPI int WINAPI GetPriorityClipboardFormat(UINT* paFormatPriorityList,
                                                 int cFormats);
WINUSERAPI HWND WINAPI GetOpenClipboardWindow(VOID);
#endif

#ifdef UNICODE
#define CharToOem CharToOemW
#define OemToChar OemToCharW
#define CharToOemBuff CharToOemBuffW
#define OemToCharBuff OemToCharBuffW
#define CharUpper CharUpperW
#define CharUpperBuff CharUpperBuffW
#define CharLower CharLowerW
#define CharLowerBuff CharLowerBuffW
#define CharNext CharNextW
#define CharPrev CharPrevW
#else
#define CharToOem CharToOemA
#define OemToChar OemToCharA
#define CharToOemBuff CharToOemBuffA
#define OemToCharBuff OemToCharBuffA
#define CharUpper CharUpperA
#define CharUpperBuff CharUpperBuffA
#define CharLower CharLowerA
#define CharLowerBuff CharLowerBuffA
#define CharNext CharNextA
#define CharPrev CharPrevA
#endif

WINUSERAPI WINBOOL WINAPI CharToOemA(LPCSTR lpszSrc, LPSTR lpszDst);
WINUSERAPI WINBOOL WINAPI CharToOemW(LPCWSTR lpszSrc, LPSTR lpszDst);
WINUSERAPI WINBOOL WINAPI OemToCharA(LPCSTR lpszSrc, LPSTR lpszDst);
WINUSERAPI WINBOOL WINAPI OemToCharW(LPCSTR lpszSrc, LPWSTR lpszDst);
WINUSERAPI WINBOOL WINAPI CharToOemBuffA(LPCSTR lpszSrc,
                                         LPSTR lpszDst,
                                         DWORD cchDstLength);
WINUSERAPI WINBOOL WINAPI CharToOemBuffW(LPCWSTR lpszSrc,
                                         LPSTR lpszDst,
                                         DWORD cchDstLength);
WINUSERAPI WINBOOL WINAPI OemToCharBuffA(LPCSTR lpszSrc,
                                         LPSTR lpszDst,
                                         DWORD cchDstLength);
WINUSERAPI WINBOOL WINAPI OemToCharBuffW(LPCSTR lpszSrc,
                                         LPWSTR lpszDst,
                                         DWORD cchDstLength);
WINUSERAPI LPSTR WINAPI CharUpperA(LPSTR lpsz);
WINUSERAPI LPWSTR WINAPI CharUpperW(LPWSTR lpsz);
WINUSERAPI DWORD WINAPI CharUpperBuffA(LPSTR lpsz, DWORD cchLength);
WINUSERAPI DWORD WINAPI CharUpperBuffW(LPWSTR lpsz, DWORD cchLength);
WINUSERAPI LPSTR WINAPI CharLowerA(LPSTR lpsz);
WINUSERAPI LPWSTR WINAPI CharLowerW(LPWSTR lpsz);
WINUSERAPI DWORD WINAPI CharLowerBuffA(LPSTR lpsz, DWORD cchLength);
WINUSERAPI DWORD WINAPI CharLowerBuffW(LPWSTR lpsz, DWORD cchLength);
WINUSERAPI LPSTR WINAPI CharNextA(LPCSTR lpsz);
WINUSERAPI LPWSTR WINAPI CharNextW(LPCWSTR lpsz);
WINUSERAPI LPSTR WINAPI CharPrevA(LPCSTR lpszStart, LPCSTR lpszCurrent);
WINUSERAPI LPWSTR WINAPI CharPrevW(LPCWSTR lpszStart, LPCWSTR lpszCurrent);
WINUSERAPI LPSTR WINAPI CharNextExA(WORD CodePage,
                                    LPCSTR lpCurrentChar,
                                    DWORD dwFlags);
WINUSERAPI LPSTR WINAPI CharPrevExA(WORD CodePage,
                                    LPCSTR lpStart,
                                    LPCSTR lpCurrentChar,
                                    DWORD dwFlags);

#define AnsiToOem CharToOemA
#define OemToAnsi OemToCharA
#define AnsiToOemBuff CharToOemBuffA
#define OemToAnsiBuff OemToCharBuffA
#define AnsiUpper CharUpperA
#define AnsiUpperBuff CharUpperBuffA
#define AnsiLower CharLowerA
#define AnsiLowerBuff CharLowerBuffA
#define AnsiNext CharNextA
#define AnsiPrev CharPrevA

#ifndef NOLANGUAGE

#ifdef UNICODE
#define IsCharAlpha IsCharAlphaW
#define IsCharAlphaNumeric IsCharAlphaNumericW
#define IsCharUpper IsCharUpperW
#define IsCharLower IsCharLowerW
#else
#define IsCharAlpha IsCharAlphaA
#define IsCharAlphaNumeric IsCharAlphaNumericA
#define IsCharUpper IsCharUpperA
#define IsCharLower IsCharLowerA
#endif

WINUSERAPI WINBOOL WINAPI IsCharAlphaA(CHAR ch);
WINUSERAPI WINBOOL WINAPI IsCharAlphaW(WCHAR ch);
WINUSERAPI WINBOOL WINAPI IsCharAlphaNumericA(CHAR ch);
WINUSERAPI WINBOOL WINAPI IsCharAlphaNumericW(WCHAR ch);
WINUSERAPI WINBOOL WINAPI IsCharUpperA(CHAR ch);
WINUSERAPI WINBOOL WINAPI IsCharUpperW(WCHAR ch);
WINUSERAPI WINBOOL WINAPI IsCharLowerA(CHAR ch);
WINUSERAPI WINBOOL WINAPI IsCharLowerW(WCHAR ch);
#endif

#ifdef UNICODE
#define GetKeyNameText GetKeyNameTextW
#define VkKeyScan VkKeyScanW
#define VkKeyScanEx VkKeyScanExW
#else
#define GetKeyNameText GetKeyNameTextA
#define VkKeyScan VkKeyScanA
#define VkKeyScanEx VkKeyScanExA
#endif

WINUSERAPI HWND WINAPI SetFocus(HWND hWnd);
WINUSERAPI HWND WINAPI GetActiveWindow(VOID);
WINUSERAPI HWND WINAPI GetFocus(VOID);
WINUSERAPI UINT WINAPI GetKBCodePage(VOID);
WINUSERAPI SHORT WINAPI GetKeyState(int nVirtKey);
WINUSERAPI SHORT WINAPI GetAsyncKeyState(int vKey);
WINUSERAPI WINBOOL WINAPI GetKeyboardState(PBYTE lpKeyState);
WINUSERAPI WINBOOL WINAPI SetKeyboardState(LPBYTE lpKeyState);
WINUSERAPI int WINAPI GetKeyNameTextA(LONG lParam, LPSTR lpString, int cchSize);
WINUSERAPI int WINAPI GetKeyNameTextW(LONG lParam,
                                      LPWSTR lpString,
                                      int cchSize);
WINUSERAPI int WINAPI GetKeyboardType(int nTypeFlag);
WINUSERAPI int WINAPI ToAscii(UINT uVirtKey,
                              UINT uScanCode,
                              CONST BYTE* lpKeyState,
                              LPWORD lpChar,
                              UINT uFlags);
WINUSERAPI int WINAPI ToAsciiEx(UINT uVirtKey,
                                UINT uScanCode,
                                CONST BYTE* lpKeyState,
                                LPWORD lpChar,
                                UINT uFlags,
                                HKL dwhkl);
WINUSERAPI int WINAPI ToUnicode(UINT wVirtKey,
                                UINT wScanCode,
                                CONST BYTE* lpKeyState,
                                LPWSTR pwszBuff,
                                int cchBuff,
                                UINT wFlags);
WINUSERAPI DWORD WINAPI OemKeyScan(WORD wOemChar);
WINUSERAPI SHORT WINAPI VkKeyScanA(CHAR ch);
WINUSERAPI SHORT WINAPI VkKeyScanW(WCHAR ch);
WINUSERAPI SHORT WINAPI VkKeyScanExA(CHAR ch, HKL dwhkl);
WINUSERAPI SHORT WINAPI VkKeyScanExW(WCHAR ch, HKL dwhkl);

#define KEYEVENTF_EXTENDEDKEY 0x0001
#define KEYEVENTF_KEYUP 0x0002
#define KEYEVENTF_UNICODE 0x0004
#define KEYEVENTF_SCANCODE 0x0008

WINUSERAPI VOID WINAPI keybd_event(BYTE bVk,
                                   BYTE bScan,
                                   DWORD dwFlags,
                                   ULONG_PTR dwExtraInfo);

#define MOUSEEVENTF_MOVE 0x0001
#define MOUSEEVENTF_LEFTDOWN 0x0002
#define MOUSEEVENTF_LEFTUP 0x0004
#define MOUSEEVENTF_RIGHTDOWN 0x0008
#define MOUSEEVENTF_RIGHTUP 0x0010
#define MOUSEEVENTF_MIDDLEDOWN 0x0020
#define MOUSEEVENTF_MIDDLEUP 0x0040
#define MOUSEEVENTF_XDOWN 0x0080
#define MOUSEEVENTF_XUP 0x0100
#define MOUSEEVENTF_WHEEL 0x0800
#define MOUSEEVENTF_VIRTUALDESK 0x4000
#define MOUSEEVENTF_ABSOLUTE 0x8000

WINUSERAPI VOID WINAPI mouse_event(DWORD dwFlags,
                                   DWORD dx,
                                   DWORD dy,
                                   DWORD dwData,
                                   ULONG_PTR dwExtraInfo);

typedef struct tagMOUSEINPUT {
  LONG dx;
  LONG dy;
  DWORD mouseData;
  DWORD dwFlags;
  DWORD time;
  ULONG_PTR dwExtraInfo;
} MOUSEINPUT, *PMOUSEINPUT, *LPMOUSEINPUT;

typedef struct tagKEYBDINPUT {
  WORD wVk;
  WORD wScan;
  DWORD dwFlags;
  DWORD time;
  ULONG_PTR dwExtraInfo;
} KEYBDINPUT, *PKEYBDINPUT, *LPKEYBDINPUT;

typedef struct tagHARDWAREINPUT {
  DWORD uMsg;
  WORD wParamL;
  WORD wParamH;
} HARDWAREINPUT, *PHARDWAREINPUT, *LPHARDWAREINPUT;

#define INPUT_MOUSE 0
#define INPUT_KEYBOARD 1
#define INPUT_HARDWARE 2

typedef struct tagINPUT {
  DWORD type;
  union {
    MOUSEINPUT mi;
    KEYBDINPUT ki;
    HARDWAREINPUT hi;
  };
} INPUT, *PINPUT, *LPINPUT;

WINUSERAPI UINT WINAPI SendInput(UINT cInputs, LPINPUT pInputs, int cbSize);

typedef struct tagLASTINPUTINFO {
  UINT cbSize;
  DWORD dwTime;
} LASTINPUTINFO, *PLASTINPUTINFO;

#ifdef UNICODE
#define MapVirtualKey MapVirtualKeyW
#define MapVirtualKeyEx MapVirtualKeyExW
#else
#define MapVirtualKey MapVirtualKeyA
#define MapVirtualKeyEx MapVirtualKeyExA
#endif

WINUSERAPI WINBOOL WINAPI GetLastInputInfo(PLASTINPUTINFO plii);
WINUSERAPI UINT WINAPI MapVirtualKeyA(UINT uCode, UINT uMapType);
WINUSERAPI UINT WINAPI MapVirtualKeyW(UINT uCode, UINT uMapType);
WINUSERAPI UINT WINAPI MapVirtualKeyExA(UINT uCode, UINT uMapType, HKL dwhkl);
WINUSERAPI UINT WINAPI MapVirtualKeyExW(UINT uCode, UINT uMapType, HKL dwhkl);
WINUSERAPI WINBOOL WINAPI GetInputState(VOID);
WINUSERAPI DWORD WINAPI GetQueueStatus(UINT flags);
WINUSERAPI HWND WINAPI GetCapture(VOID);
WINUSERAPI HWND WINAPI SetCapture(HWND hWnd);
WINUSERAPI WINBOOL WINAPI ReleaseCapture(VOID);
WINUSERAPI DWORD WINAPI MsgWaitForMultipleObjects(DWORD nCount,
                                                  CONST HANDLE* pHandles,
                                                  WINBOOL fWaitAll,
                                                  DWORD dwMilliseconds,
                                                  DWORD dwWakeMask);
WINUSERAPI DWORD WINAPI MsgWaitForMultipleObjectsEx(DWORD nCount,
                                                    CONST HANDLE* pHandles,
                                                    DWORD dwMilliseconds,
                                                    DWORD dwWakeMask,
                                                    DWORD dwFlags);

#define MWMO_WAITALL 0x0001
#define MWMO_ALERTABLE 0x0002
#define MWMO_INPUTAVAILABLE 0x0004

#define QS_KEY 0x0001
#define QS_MOUSEMOVE 0x0002
#define QS_MOUSEBUTTON 0x0004
#define QS_POSTMESSAGE 0x0008
#define QS_TIMER 0x0010
#define QS_PAINT 0x0020
#define QS_SENDMESSAGE 0x0040
#define QS_HOTKEY 0x0080
#define QS_ALLPOSTMESSAGE 0x0100
#define QS_RAWINPUT 0x0400
#define QS_MOUSE (QS_MOUSEMOVE | QS_MOUSEBUTTON)
#define QS_INPUT (QS_MOUSE | QS_KEY | QS_RAWINPUT)
#define QS_ALLEVENTS \
  (QS_INPUT | QS_POSTMESSAGE | QS_TIMER | QS_PAINT | QS_HOTKEY)
#define QS_ALLINPUT \
  (QS_INPUT | QS_POSTMESSAGE | QS_TIMER | QS_PAINT | QS_HOTKEY | QS_SENDMESSAGE)

#define USER_TIMER_MAXIMUM 0x7FFFFFFF
#define USER_TIMER_MINIMUM 0x0000000A

#ifdef UNICODE
#define LoadAccelerators LoadAcceleratorsW
#define CreateAcceleratorTable CreateAcceleratorTableW
#define CopyAcceleratorTable CopyAcceleratorTableW
#else
#define LoadAccelerators LoadAcceleratorsA
#define CreateAcceleratorTable CreateAcceleratorTableA
#define CopyAcceleratorTable CopyAcceleratorTableA
#endif

WINUSERAPI UINT_PTR WINAPI SetTimer(HWND hWnd,
                                    UINT_PTR nIDEvent,
                                    UINT uElapse,
                                    TIMERPROC lpTimerFunc);
WINUSERAPI WINBOOL WINAPI KillTimer(HWND hWnd, UINT_PTR uIDEvent);
WINUSERAPI WINBOOL WINAPI IsWindowUnicode(HWND hWnd);
WINUSERAPI WINBOOL WINAPI EnableWindow(HWND hWnd, WINBOOL bEnable);
WINUSERAPI WINBOOL WINAPI IsWindowEnabled(HWND hWnd);
WINUSERAPI HACCEL WINAPI LoadAcceleratorsA(HINSTANCE hInstance,
                                           LPCSTR lpTableName);
WINUSERAPI HACCEL WINAPI LoadAcceleratorsW(HINSTANCE hInstance,
                                           LPCWSTR lpTableName);
WINUSERAPI HACCEL WINAPI CreateAcceleratorTableA(LPACCEL paccel, int cAccel);
WINUSERAPI HACCEL WINAPI CreateAcceleratorTableW(LPACCEL paccel, int cAccel);
WINUSERAPI WINBOOL WINAPI DestroyAcceleratorTable(HACCEL hAccel);
WINUSERAPI int WINAPI CopyAcceleratorTableA(HACCEL hAccelSrc,
                                            LPACCEL lpAccelDst,
                                            int cAccelEntries);
WINUSERAPI int WINAPI CopyAcceleratorTableW(HACCEL hAccelSrc,
                                            LPACCEL lpAccelDst,
                                            int cAccelEntries);

#ifndef NOMSG

#ifdef UNICODE
#define TranslateAccelerator TranslateAcceleratorW
#else
#define TranslateAccelerator TranslateAcceleratorA
#endif

WINUSERAPI int WINAPI TranslateAcceleratorA(HWND hWnd,
                                            HACCEL hAccTable,
                                            LPMSG lpMsg);
WINUSERAPI int WINAPI TranslateAcceleratorW(HWND hWnd,
                                            HACCEL hAccTable,
                                            LPMSG lpMsg);
#endif

#ifndef NOSYSMETRICS

#define SM_CXSCREEN 0
#define SM_CYSCREEN 1
#define SM_CXVSCROLL 2
#define SM_CYHSCROLL 3
#define SM_CYCAPTION 4
#define SM_CXBORDER 5
#define SM_CYBORDER 6
#define SM_CXDLGFRAME 7
#define SM_CYDLGFRAME 8
#define SM_CYVTHUMB 9
#define SM_CXHTHUMB 10
#define SM_CXICON 11
#define SM_CYICON 12
#define SM_CXCURSOR 13
#define SM_CYCURSOR 14
#define SM_CYMENU 15
#define SM_CXFULLSCREEN 16
#define SM_CYFULLSCREEN 17
#define SM_CYKANJIWINDOW 18
#define SM_MOUSEPRESENT 19
#define SM_CYVSCROLL 20
#define SM_CXHSCROLL 21
#define SM_DEBUG 22
#define SM_SWAPBUTTON 23
#define SM_RESERVED1 24
#define SM_RESERVED2 25
#define SM_RESERVED3 26
#define SM_RESERVED4 27
#define SM_CXMIN 28
#define SM_CYMIN 29
#define SM_CXSIZE 30
#define SM_CYSIZE 31
#define SM_CXFRAME 32
#define SM_CYFRAME 33
#define SM_CXMINTRACK 34
#define SM_CYMINTRACK 35
#define SM_CXDOUBLECLK 36
#define SM_CYDOUBLECLK 37
#define SM_CXICONSPACING 38
#define SM_CYICONSPACING 39
#define SM_MENUDROPALIGNMENT 40
#define SM_PENWINDOWS 41
#define SM_DBCSENABLED 42
#define SM_CMOUSEBUTTONS 43

#define SM_CXFIXEDFRAME SM_CXDLGFRAME
#define SM_CYFIXEDFRAME SM_CYDLGFRAME
#define SM_CXSIZEFRAME SM_CXFRAME
#define SM_CYSIZEFRAME SM_CYFRAME

#define SM_SECURE 44
#define SM_CXEDGE 45
#define SM_CYEDGE 46
#define SM_CXMINSPACING 47
#define SM_CYMINSPACING 48
#define SM_CXSMICON 49
#define SM_CYSMICON 50
#define SM_CYSMCAPTION 51
#define SM_CXSMSIZE 52
#define SM_CYSMSIZE 53
#define SM_CXMENUSIZE 54
#define SM_CYMENUSIZE 55
#define SM_ARRANGE 56
#define SM_CXMINIMIZED 57
#define SM_CYMINIMIZED 58
#define SM_CXMAXTRACK 59
#define SM_CYMAXTRACK 60
#define SM_CXMAXIMIZED 61
#define SM_CYMAXIMIZED 62
#define SM_NETWORK 63
#define SM_CLEANBOOT 67
#define SM_CXDRAG 68
#define SM_CYDRAG 69
#define SM_SHOWSOUNDS 70
#define SM_CXMENUCHECK 71
#define SM_CYMENUCHECK 72
#define SM_SLOWMACHINE 73
#define SM_MIDEASTENABLED 74
#define SM_MOUSEWHEELPRESENT 75
#define SM_XVIRTUALSCREEN 76
#define SM_YVIRTUALSCREEN 77
#define SM_CXVIRTUALSCREEN 78
#define SM_CYVIRTUALSCREEN 79
#define SM_CMONITORS 80
#define SM_SAMEDISPLAYFORMAT 81
#define SM_IMMENABLED 82
#define SM_CXFOCUSBORDER 83
#define SM_CYFOCUSBORDER 84
#define SM_TABLETPC 86
#define SM_MEDIACENTER 87
#define SM_STARTER 88
#define SM_SERVERR2 89
#define SM_CMETRICS 90
#define SM_REMOTESESSION 0x1000
#define SM_SHUTTINGDOWN 0x2000
#define SM_REMOTECONTROL 0x2001
#define SM_CARETBLINKINGENABLED 0x2002

WINUSERAPI int WINAPI GetSystemMetrics(int nIndex);
#endif

#ifndef NOMENUS

#ifdef UNICODE
#define LoadMenu LoadMenuW
#define LoadMenuIndirect LoadMenuIndirectW
#define ChangeMenu ChangeMenuW
#define GetMenuString GetMenuStringW
#define InsertMenu InsertMenuW
#define AppendMenu AppendMenuW
#define ModifyMenu ModifyMenuW
#else
#define LoadMenu LoadMenuA
#define LoadMenuIndirect LoadMenuIndirectA
#define ChangeMenu ChangeMenuA
#define GetMenuString GetMenuStringA
#define InsertMenu InsertMenuA
#define AppendMenu AppendMenuA
#define ModifyMenu ModifyMenuA
#endif

WINUSERAPI HMENU WINAPI LoadMenuA(HINSTANCE hInstance, LPCSTR lpMenuName);
WINUSERAPI HMENU WINAPI LoadMenuW(HINSTANCE hInstance, LPCWSTR lpMenuName);
WINUSERAPI HMENU WINAPI LoadMenuIndirectA(CONST MENUTEMPLATEA* lpMenuTemplate);
WINUSERAPI HMENU WINAPI LoadMenuIndirectW(CONST MENUTEMPLATEW* lpMenuTemplate);
WINUSERAPI HMENU WINAPI GetMenu(HWND hWnd);
WINUSERAPI WINBOOL WINAPI SetMenu(HWND hWnd, HMENU hMenu);
WINUSERAPI WINBOOL WINAPI ChangeMenuA(HMENU hMenu,
                                      UINT cmd,
                                      LPCSTR lpszNewItem,
                                      UINT cmdInsert,
                                      UINT flags);
WINUSERAPI WINBOOL WINAPI ChangeMenuW(HMENU hMenu,
                                      UINT cmd,
                                      LPCWSTR lpszNewItem,
                                      UINT cmdInsert,
                                      UINT flags);
WINUSERAPI WINBOOL WINAPI HiliteMenuItem(HWND hWnd,
                                         HMENU hMenu,
                                         UINT uIDHiliteItem,
                                         UINT uHilite);
WINUSERAPI int WINAPI GetMenuStringA(HMENU hMenu,
                                     UINT uIDItem,
                                     LPSTR lpString,
                                     int cchMax,
                                     UINT flags);
WINUSERAPI int WINAPI GetMenuStringW(HMENU hMenu,
                                     UINT uIDItem,
                                     LPWSTR lpString,
                                     int cchMax,
                                     UINT flags);
WINUSERAPI UINT WINAPI GetMenuState(HMENU hMenu, UINT uId, UINT uFlags);
WINUSERAPI WINBOOL WINAPI DrawMenuBar(HWND hWnd);

#define PMB_ACTIVE 0x00000001

WINUSERAPI HMENU WINAPI GetSystemMenu(HWND hWnd, WINBOOL bRevert);
WINUSERAPI HMENU WINAPI CreateMenu(VOID);
WINUSERAPI HMENU WINAPI CreatePopupMenu(VOID);
WINUSERAPI WINBOOL WINAPI DestroyMenu(HMENU hMenu);
WINUSERAPI DWORD WINAPI CheckMenuItem(HMENU hMenu,
                                      UINT uIDCheckItem,
                                      UINT uCheck);
WINUSERAPI WINBOOL WINAPI EnableMenuItem(HMENU hMenu,
                                         UINT uIDEnableItem,
                                         UINT uEnable);
WINUSERAPI HMENU WINAPI GetSubMenu(HMENU hMenu, int nPos);
WINUSERAPI UINT WINAPI GetMenuItemID(HMENU hMenu, int nPos);
WINUSERAPI int WINAPI GetMenuItemCount(HMENU hMenu);
WINUSERAPI WINBOOL WINAPI InsertMenuA(HMENU hMenu,
                                      UINT uPosition,
                                      UINT uFlags,
                                      UINT_PTR uIDNewItem,
                                      LPCSTR lpNewItem);
WINUSERAPI WINBOOL WINAPI InsertMenuW(HMENU hMenu,
                                      UINT uPosition,
                                      UINT uFlags,
                                      UINT_PTR uIDNewItem,
                                      LPCWSTR lpNewItem);
WINUSERAPI WINBOOL WINAPI AppendMenuA(HMENU hMenu,
                                      UINT uFlags,
                                      UINT_PTR uIDNewItem,
                                      LPCSTR lpNewItem);
WINUSERAPI WINBOOL WINAPI AppendMenuW(HMENU hMenu,
                                      UINT uFlags,
                                      UINT_PTR uIDNewItem,
                                      LPCWSTR lpNewItem);
WINUSERAPI WINBOOL WINAPI ModifyMenuA(HMENU hMnu,
                                      UINT uPosition,
                                      UINT uFlags,
                                      UINT_PTR uIDNewItem,
                                      LPCSTR lpNewItem);
WINUSERAPI WINBOOL WINAPI ModifyMenuW(HMENU hMnu,
                                      UINT uPosition,
                                      UINT uFlags,
                                      UINT_PTR uIDNewItem,
                                      LPCWSTR lpNewItem);
WINUSERAPI WINBOOL WINAPI RemoveMenu(HMENU hMenu, UINT uPosition, UINT uFlags);
WINUSERAPI WINBOOL WINAPI DeleteMenu(HMENU hMenu, UINT uPosition, UINT uFlags);
WINUSERAPI WINBOOL WINAPI SetMenuItemBitmaps(HMENU hMenu,
                                             UINT uPosition,
                                             UINT uFlags,
                                             HBITMAP hBitmapUnchecked,
                                             HBITMAP hBitmapChecked);
WINUSERAPI LONG WINAPI GetMenuCheckMarkDimensions(VOID);
WINUSERAPI WINBOOL WINAPI TrackPopupMenu(HMENU hMenu,
                                         UINT uFlags,
                                         int x,
                                         int y,
                                         int nReserved,
                                         HWND hWnd,
                                         CONST RECT* prcRect);

#define MNC_IGNORE 0
#define MNC_CLOSE 1
#define MNC_EXECUTE 2
#define MNC_SELECT 3

typedef struct tagTPMPARAMS {
  UINT cbSize;
  RECT rcExclude;
} TPMPARAMS;

typedef TPMPARAMS* LPTPMPARAMS;

WINUSERAPI WINBOOL WINAPI
TrackPopupMenuEx(HMENU, UINT, int, int, HWND, LPTPMPARAMS);

#define MNS_NOCHECK 0x80000000
#define MNS_MODELESS 0x40000000
#define MNS_DRAGDROP 0x20000000
#define MNS_AUTODISMISS 0x10000000
#define MNS_NOTIFYBYPOS 0x08000000
#define MNS_CHECKORBMP 0x04000000

#define MIM_MAXHEIGHT 0x00000001
#define MIM_BACKGROUND 0x00000002
#define MIM_HELPID 0x00000004
#define MIM_MENUDATA 0x00000008
#define MIM_STYLE 0x00000010
#define MIM_APPLYTOSUBMENUS 0x80000000

typedef struct tagMENUINFO {
  DWORD cbSize;
  DWORD fMask;
  DWORD dwStyle;
  UINT cyMax;
  HBRUSH hbrBack;
  DWORD dwContextHelpID;
  ULONG_PTR dwMenuData;
} MENUINFO, *LPMENUINFO;

typedef MENUINFO CONST* LPCMENUINFO;

WINUSERAPI WINBOOL WINAPI GetMenuInfo(HMENU, LPMENUINFO);
WINUSERAPI WINBOOL WINAPI SetMenuInfo(HMENU, LPCMENUINFO);
WINUSERAPI WINBOOL WINAPI EndMenu(VOID);

#define MND_CONTINUE 0
#define MND_ENDMENU 1

typedef struct tagMENUGETOBJECTINFO {
  DWORD dwFlags;
  UINT uPos;
  HMENU hmenu;
  PVOID riid;
  PVOID pvObj;
} MENUGETOBJECTINFO, *PMENUGETOBJECTINFO;

#define MNGOF_TOPGAP 0x00000001
#define MNGOF_BOTTOMGAP 0x00000002

#define MNGO_NOINTERFACE 0x00000000
#define MNGO_NOERROR 0x00000001

#define MIIM_STATE 0x00000001
#define MIIM_ID 0x00000002
#define MIIM_SUBMENU 0x00000004
#define MIIM_CHECKMARKS 0x00000008
#define MIIM_TYPE 0x00000010
#define MIIM_DATA 0x00000020

#define MIIM_STRING 0x00000040
#define MIIM_BITMAP 0x00000080
#define MIIM_FTYPE 0x00000100

#define HBMMENU_CALLBACK ((HBITMAP)-1)
#define HBMMENU_SYSTEM ((HBITMAP)1)
#define HBMMENU_MBAR_RESTORE ((HBITMAP)2)
#define HBMMENU_MBAR_MINIMIZE ((HBITMAP)3)
#define HBMMENU_MBAR_CLOSE ((HBITMAP)5)
#define HBMMENU_MBAR_CLOSE_D ((HBITMAP)6)
#define HBMMENU_MBAR_MINIMIZE_D ((HBITMAP)7)
#define HBMMENU_POPUP_CLOSE ((HBITMAP)8)
#define HBMMENU_POPUP_RESTORE ((HBITMAP)9)
#define HBMMENU_POPUP_MAXIMIZE ((HBITMAP)10)
#define HBMMENU_POPUP_MINIMIZE ((HBITMAP)11)

typedef struct tagMENUITEMINFOA {
  UINT cbSize;
  UINT fMask;
  UINT fType;
  UINT fState;
  UINT wID;
  HMENU hSubMenu;
  HBITMAP hbmpChecked;
  HBITMAP hbmpUnchecked;
  ULONG_PTR dwItemData;
  LPSTR dwTypeData;
  UINT cch;
  HBITMAP hbmpItem;
} MENUITEMINFOA, *LPMENUITEMINFOA;

typedef struct tagMENUITEMINFOW {
  UINT cbSize;
  UINT fMask;
  UINT fType;
  UINT fState;
  UINT wID;
  HMENU hSubMenu;
  HBITMAP hbmpChecked;
  HBITMAP hbmpUnchecked;
  ULONG_PTR dwItemData;
  LPWSTR dwTypeData;
  UINT cch;
  HBITMAP hbmpItem;
} MENUITEMINFOW, *LPMENUITEMINFOW;

#ifdef UNICODE
typedef MENUITEMINFOW MENUITEMINFO;
typedef LPMENUITEMINFOW LPMENUITEMINFO;
#else
typedef MENUITEMINFOA MENUITEMINFO;
typedef LPMENUITEMINFOA LPMENUITEMINFO;
#endif
typedef MENUITEMINFOA CONST* LPCMENUITEMINFOA;
typedef MENUITEMINFOW CONST* LPCMENUITEMINFOW;
#ifdef UNICODE
typedef LPCMENUITEMINFOW LPCMENUITEMINFO;
#else
typedef LPCMENUITEMINFOA LPCMENUITEMINFO;
#endif

#ifdef UNICODE
#define InsertMenuItem InsertMenuItemW
#define GetMenuItemInfo GetMenuItemInfoW
#define SetMenuItemInfo SetMenuItemInfoW
#else
#define InsertMenuItem InsertMenuItemA
#define GetMenuItemInfo GetMenuItemInfoA
#define SetMenuItemInfo SetMenuItemInfoA
#endif

WINUSERAPI WINBOOL WINAPI InsertMenuItemA(HMENU hmenu,
                                          UINT item,
                                          WINBOOL fByPosition,
                                          LPCMENUITEMINFOA lpmi);
WINUSERAPI WINBOOL WINAPI InsertMenuItemW(HMENU hmenu,
                                          UINT item,
                                          WINBOOL fByPosition,
                                          LPCMENUITEMINFOW lpmi);
WINUSERAPI WINBOOL WINAPI GetMenuItemInfoA(HMENU hmenu,
                                           UINT item,
                                           WINBOOL fByPosition,
                                           LPMENUITEMINFOA lpmii);
WINUSERAPI WINBOOL WINAPI GetMenuItemInfoW(HMENU hmenu,
                                           UINT item,
                                           WINBOOL fByPosition,
                                           LPMENUITEMINFOW lpmii);
WINUSERAPI WINBOOL WINAPI SetMenuItemInfoA(HMENU hmenu,
                                           UINT item,
                                           WINBOOL fByPositon,
                                           LPCMENUITEMINFOA lpmii);
WINUSERAPI WINBOOL WINAPI SetMenuItemInfoW(HMENU hmenu,
                                           UINT item,
                                           WINBOOL fByPositon,
                                           LPCMENUITEMINFOW lpmii);

#define GMDI_USEDISABLED 0x0001L
#define GMDI_GOINTOPOPUPS 0x0002L

WINUSERAPI UINT WINAPI GetMenuDefaultItem(HMENU hMenu,
                                          UINT fByPos,
                                          UINT gmdiFlags);
WINUSERAPI WINBOOL WINAPI SetMenuDefaultItem(HMENU hMenu,
                                             UINT uItem,
                                             UINT fByPos);
WINUSERAPI WINBOOL WINAPI GetMenuItemRect(HWND hWnd,
                                          HMENU hMenu,
                                          UINT uItem,
                                          LPRECT lprcItem);
WINUSERAPI int WINAPI MenuItemFromPoint(HWND hWnd, HMENU hMenu, POINT ptScreen);

#define TPM_LEFTBUTTON 0x0000L
#define TPM_RIGHTBUTTON 0x0002L
#define TPM_LEFTALIGN 0x0000L
#define TPM_CENTERALIGN 0x0004L
#define TPM_RIGHTALIGN 0x0008L
#define TPM_TOPALIGN 0x0000L
#define TPM_VCENTERALIGN 0x0010L
#define TPM_BOTTOMALIGN 0x0020L

#define TPM_HORIZONTAL 0x0000L
#define TPM_VERTICAL 0x0040L
#define TPM_NONOTIFY 0x0080L
#define TPM_RETURNCMD 0x0100L
#define TPM_RECURSE 0x0001L
#define TPM_HORPOSANIMATION 0x0400L
#define TPM_HORNEGANIMATION 0x0800L
#define TPM_VERPOSANIMATION 0x1000L
#define TPM_VERNEGANIMATION 0x2000L
#define TPM_NOANIMATION 0x4000L
#define TPM_LAYOUTRTL 0x8000L
#endif

typedef struct tagDROPSTRUCT {
  HWND hwndSource;
  HWND hwndSink;
  DWORD wFmt;
  ULONG_PTR dwData;
  POINT ptDrop;
  DWORD dwControlData;
} DROPSTRUCT, *PDROPSTRUCT, *LPDROPSTRUCT;

#define DOF_EXECUTABLE 0x8001
#define DOF_DOCUMENT 0x8002
#define DOF_DIRECTORY 0x8003
#define DOF_MULTIPLE 0x8004
#define DOF_PROGMAN 0x0001
#define DOF_SHELLDATA 0x0002

#define DO_DROPFILE 0x454C4946L
#define DO_PRINTFILE 0x544E5250L

WINUSERAPI DWORD WINAPI DragObject(HWND hwndParent,
                                   HWND hwndFrom,
                                   UINT fmt,
                                   ULONG_PTR data,
                                   HCURSOR hcur);
WINUSERAPI WINBOOL WINAPI DragDetect(HWND hwnd, POINT pt);
WINUSERAPI WINBOOL WINAPI DrawIcon(HDC hDC, int X, int Y, HICON hIcon);

#ifndef NODRAWTEXT

#define DT_TOP 0x00000000
#define DT_LEFT 0x00000000
#define DT_CENTER 0x00000001
#define DT_RIGHT 0x00000002
#define DT_VCENTER 0x00000004
#define DT_BOTTOM 0x00000008
#define DT_WORDBREAK 0x00000010
#define DT_SINGLELINE 0x00000020
#define DT_EXPANDTABS 0x00000040
#define DT_TABSTOP 0x00000080
#define DT_NOCLIP 0x00000100
#define DT_EXTERNALLEADING 0x00000200
#define DT_CALCRECT 0x00000400
#define DT_NOPREFIX 0x00000800
#define DT_INTERNAL 0x00001000

#define DT_EDITCONTROL 0x00002000
#define DT_PATH_ELLIPSIS 0x00004000
#define DT_END_ELLIPSIS 0x00008000
#define DT_MODIFYSTRING 0x00010000
#define DT_RTLREADING 0x00020000
#define DT_WORD_ELLIPSIS 0x00040000
#define DT_NOFULLWIDTHCHARBREAK 0x00080000
#define DT_HIDEPREFIX 0x00100000
#define DT_PREFIXONLY 0x00200000

typedef struct tagDRAWTEXTPARAMS {
  UINT cbSize;
  int iTabLength;
  int iLeftMargin;
  int iRightMargin;
  UINT uiLengthDrawn;
} DRAWTEXTPARAMS, *LPDRAWTEXTPARAMS;

#ifdef UNICODE
#define DrawText DrawTextW
#define DrawTextEx DrawTextExW
#else
#define DrawText DrawTextA
#define DrawTextEx DrawTextExA
#endif

WINUSERAPI int WINAPI
DrawTextA(HDC hdc, LPCSTR lpchText, int cchText, LPRECT lprc, UINT format);
WINUSERAPI int WINAPI
DrawTextW(HDC hdc, LPCWSTR lpchText, int cchText, LPRECT lprc, UINT format);
WINUSERAPI int WINAPI DrawTextExA(HDC hdc,
                                  LPSTR lpchText,
                                  int cchText,
                                  LPRECT lprc,
                                  UINT format,
                                  LPDRAWTEXTPARAMS lpdtp);
WINUSERAPI int WINAPI DrawTextExW(HDC hdc,
                                  LPWSTR lpchText,
                                  int cchText,
                                  LPRECT lprc,
                                  UINT format,
                                  LPDRAWTEXTPARAMS lpdtp);
#endif

#ifdef UNICODE
#define GrayString GrayStringW
#define DrawState DrawStateW
#define TabbedTextOut TabbedTextOutW
#define GetTabbedTextExtent GetTabbedTextExtentW
#else
#define GrayString GrayStringA
#define DrawState DrawStateA
#define TabbedTextOut TabbedTextOutA
#define GetTabbedTextExtent GetTabbedTextExtentA
#endif

WINUSERAPI WINBOOL WINAPI GrayStringA(HDC hDC,
                                      HBRUSH hBrush,
                                      GRAYSTRINGPROC lpOutputFunc,
                                      LPARAM lpData,
                                      int nCount,
                                      int X,
                                      int Y,
                                      int nWidth,
                                      int nHeight);
WINUSERAPI WINBOOL WINAPI GrayStringW(HDC hDC,
                                      HBRUSH hBrush,
                                      GRAYSTRINGPROC lpOutputFunc,
                                      LPARAM lpData,
                                      int nCount,
                                      int X,
                                      int Y,
                                      int nWidth,
                                      int nHeight);

#define DST_COMPLEX 0x0000
#define DST_TEXT 0x0001
#define DST_PREFIXTEXT 0x0002
#define DST_ICON 0x0003
#define DST_BITMAP 0x0004

#define DSS_NORMAL 0x0000
#define DSS_UNION 0x0010
#define DSS_DISABLED 0x0020
#define DSS_MONO 0x0080
#define DSS_HIDEPREFIX 0x0200
#define DSS_PREFIXONLY 0x0400
#define DSS_RIGHT 0x8000

WINUSERAPI WINBOOL WINAPI DrawStateA(HDC hdc,
                                     HBRUSH hbrFore,
                                     DRAWSTATEPROC qfnCallBack,
                                     LPARAM lData,
                                     WPARAM wData,
                                     int x,
                                     int y,
                                     int cx,
                                     int cy,
                                     UINT uFlags);
WINUSERAPI WINBOOL WINAPI DrawStateW(HDC hdc,
                                     HBRUSH hbrFore,
                                     DRAWSTATEPROC qfnCallBack,
                                     LPARAM lData,
                                     WPARAM wData,
                                     int x,
                                     int y,
                                     int cx,
                                     int cy,
                                     UINT uFlags);
WINUSERAPI LONG WINAPI TabbedTextOutA(HDC hdc,
                                      int x,
                                      int y,
                                      LPCSTR lpString,
                                      int chCount,
                                      int nTabPositions,
                                      CONST INT* lpnTabStopPositions,
                                      int nTabOrigin);
WINUSERAPI LONG WINAPI TabbedTextOutW(HDC hdc,
                                      int x,
                                      int y,
                                      LPCWSTR lpString,
                                      int chCount,
                                      int nTabPositions,
                                      CONST INT* lpnTabStopPositions,
                                      int nTabOrigin);
WINUSERAPI DWORD WINAPI GetTabbedTextExtentA(HDC hdc,
                                             LPCSTR lpString,
                                             int chCount,
                                             int nTabPositions,
                                             CONST INT* lpnTabStopPositions);
WINUSERAPI DWORD WINAPI GetTabbedTextExtentW(HDC hdc,
                                             LPCWSTR lpString,
                                             int chCount,
                                             int nTabPositions,
                                             CONST INT* lpnTabStopPositions);
WINUSERAPI WINBOOL WINAPI UpdateWindow(HWND hWnd);
WINUSERAPI HWND WINAPI SetActiveWindow(HWND hWnd);
WINUSERAPI HWND WINAPI GetForegroundWindow(VOID);
WINUSERAPI WINBOOL WINAPI PaintDesktop(HDC hdc);
WINUSERAPI VOID WINAPI SwitchToThisWindow(HWND hwnd, WINBOOL fUnknown);
WINUSERAPI WINBOOL WINAPI SetForegroundWindow(HWND hWnd);
WINUSERAPI WINBOOL WINAPI AllowSetForegroundWindow(DWORD dwProcessId);

#define ASFW_ANY ((DWORD)-1)

WINUSERAPI WINBOOL WINAPI LockSetForegroundWindow(UINT uLockCode);

#define LSFW_LOCK 1
#define LSFW_UNLOCK 2

WINUSERAPI HWND WINAPI WindowFromDC(HDC hDC);
WINUSERAPI HDC WINAPI GetDC(HWND hWnd);
WINUSERAPI HDC WINAPI GetDCEx(HWND hWnd, HRGN hrgnClip, DWORD flags);

#define DCX_WINDOW 0x00000001L
#define DCX_CACHE 0x00000002L
#define DCX_NORESETATTRS 0x00000004L
#define DCX_CLIPCHILDREN 0x00000008L
#define DCX_CLIPSIBLINGS 0x00000010L
#define DCX_PARENTCLIP 0x00000020L
#define DCX_EXCLUDERGN 0x00000040L
#define DCX_INTERSECTRGN 0x00000080L
#define DCX_EXCLUDEUPDATE 0x00000100L
#define DCX_INTERSECTUPDATE 0x00000200L
#define DCX_LOCKWINDOWUPDATE 0x00000400L

#define DCX_VALIDATE 0x00200000L

WINUSERAPI HDC WINAPI GetWindowDC(HWND hWnd);
WINUSERAPI int WINAPI ReleaseDC(HWND hWnd, HDC hDC);
WINUSERAPI HDC WINAPI BeginPaint(HWND hWnd, LPPAINTSTRUCT lpPaint);
WINUSERAPI WINBOOL WINAPI EndPaint(HWND hWnd, CONST PAINTSTRUCT* lpPaint);
WINUSERAPI WINBOOL WINAPI GetUpdateRect(HWND hWnd,
                                        LPRECT lpRect,
                                        WINBOOL bErase);
WINUSERAPI int WINAPI GetUpdateRgn(HWND hWnd, HRGN hRgn, WINBOOL bErase);
WINUSERAPI int WINAPI SetWindowRgn(HWND hWnd, HRGN hRgn, WINBOOL bRedraw);
WINUSERAPI int WINAPI GetWindowRgn(HWND hWnd, HRGN hRgn);
WINUSERAPI int WINAPI GetWindowRgnBox(HWND hWnd, LPRECT lprc);
WINUSERAPI int WINAPI ExcludeUpdateRgn(HDC hDC, HWND hWnd);
WINUSERAPI WINBOOL WINAPI InvalidateRect(HWND hWnd,
                                         CONST RECT* lpRect,
                                         WINBOOL bErase);
WINUSERAPI WINBOOL WINAPI ValidateRect(HWND hWnd, CONST RECT* lpRect);
WINUSERAPI WINBOOL WINAPI InvalidateRgn(HWND hWnd, HRGN hRgn, WINBOOL bErase);
WINUSERAPI WINBOOL WINAPI ValidateRgn(HWND hWnd, HRGN hRgn);
WINUSERAPI WINBOOL WINAPI RedrawWindow(HWND hWnd,
                                       CONST RECT* lprcUpdate,
                                       HRGN hrgnUpdate,
                                       UINT flags);

#define RDW_INVALIDATE 0x0001
#define RDW_INTERNALPAINT 0x0002
#define RDW_ERASE 0x0004

#define RDW_VALIDATE 0x0008
#define RDW_NOINTERNALPAINT 0x0010
#define RDW_NOERASE 0x0020

#define RDW_NOCHILDREN 0x0040
#define RDW_ALLCHILDREN 0x0080

#define RDW_UPDATENOW 0x0100
#define RDW_ERASENOW 0x0200

#define RDW_FRAME 0x0400
#define RDW_NOFRAME 0x0800

WINUSERAPI WINBOOL WINAPI LockWindowUpdate(HWND hWndLock);
WINUSERAPI WINBOOL WINAPI ScrollWindow(HWND hWnd,
                                       int XAmount,
                                       int YAmount,
                                       CONST RECT* lpRect,
                                       CONST RECT* lpClipRect);
WINUSERAPI WINBOOL WINAPI ScrollDC(HDC hDC,
                                   int dx,
                                   int dy,
                                   CONST RECT* lprcScroll,
                                   CONST RECT* lprcClip,
                                   HRGN hrgnUpdate,
                                   LPRECT lprcUpdate);
WINUSERAPI int WINAPI ScrollWindowEx(HWND hWnd,
                                     int dx,
                                     int dy,
                                     CONST RECT* prcScroll,
                                     CONST RECT* prcClip,
                                     HRGN hrgnUpdate,
                                     LPRECT prcUpdate,
                                     UINT flags);

#define SW_SCROLLCHILDREN 0x0001
#define SW_INVALIDATE 0x0002
#define SW_ERASE 0x0004
#define SW_SMOOTHSCROLL 0x0010

#ifndef NOSCROLL
WINUSERAPI int WINAPI SetScrollPos(HWND hWnd,
                                   int nBar,
                                   int nPos,
                                   WINBOOL bRedraw);
WINUSERAPI int WINAPI GetScrollPos(HWND hWnd, int nBar);
WINUSERAPI WINBOOL WINAPI
SetScrollRange(HWND hWnd, int nBar, int nMinPos, int nMaxPos, WINBOOL bRedraw);
WINUSERAPI WINBOOL WINAPI GetScrollRange(HWND hWnd,
                                         int nBar,
                                         LPINT lpMinPos,
                                         LPINT lpMaxPos);
WINUSERAPI WINBOOL WINAPI ShowScrollBar(HWND hWnd, int wBar, WINBOOL bShow);
WINUSERAPI WINBOOL WINAPI EnableScrollBar(HWND hWnd,
                                          UINT wSBflags,
                                          UINT wArrows);

#define ESB_ENABLE_BOTH 0x0000
#define ESB_DISABLE_BOTH 0x0003

#define ESB_DISABLE_LEFT 0x0001
#define ESB_DISABLE_RIGHT 0x0002

#define ESB_DISABLE_UP 0x0001
#define ESB_DISABLE_DOWN 0x0002

#define ESB_DISABLE_LTUP ESB_DISABLE_LEFT
#define ESB_DISABLE_RTDN ESB_DISABLE_RIGHT
#endif

#ifdef UNICODE
#define SetProp SetPropW
#define GetProp GetPropW
#define RemoveProp RemovePropW
#define EnumPropsEx EnumPropsExW
#define EnumProps EnumPropsW
#define SetWindowText SetWindowTextW
#define GetWindowText GetWindowTextW
#define GetWindowTextLength GetWindowTextLengthW
#else
#define SetProp SetPropA
#define GetProp GetPropA
#define RemoveProp RemovePropA
#define EnumPropsEx EnumPropsExA
#define EnumProps EnumPropsA
#define SetWindowText SetWindowTextA
#define GetWindowText GetWindowTextA
#define GetWindowTextLength GetWindowTextLengthA
#endif

WINUSERAPI WINBOOL WINAPI SetPropA(HWND hWnd, LPCSTR lpString, HANDLE hData);
WINUSERAPI WINBOOL WINAPI SetPropW(HWND hWnd, LPCWSTR lpString, HANDLE hData);
WINUSERAPI HANDLE WINAPI GetPropA(HWND hWnd, LPCSTR lpString);
WINUSERAPI HANDLE WINAPI GetPropW(HWND hWnd, LPCWSTR lpString);
WINUSERAPI HANDLE WINAPI RemovePropA(HWND hWnd, LPCSTR lpString);
WINUSERAPI HANDLE WINAPI RemovePropW(HWND hWnd, LPCWSTR lpString);
WINUSERAPI int WINAPI EnumPropsExA(HWND hWnd,
                                   PROPENUMPROCEXA lpEnumFunc,
                                   LPARAM lParam);
WINUSERAPI int WINAPI EnumPropsExW(HWND hWnd,
                                   PROPENUMPROCEXW lpEnumFunc,
                                   LPARAM lParam);
WINUSERAPI int WINAPI EnumPropsA(HWND hWnd, PROPENUMPROCA lpEnumFunc);
WINUSERAPI int WINAPI EnumPropsW(HWND hWnd, PROPENUMPROCW lpEnumFunc);
WINUSERAPI WINBOOL WINAPI SetWindowTextA(HWND hWnd, LPCSTR lpString);
WINUSERAPI WINBOOL WINAPI SetWindowTextW(HWND hWnd, LPCWSTR lpString);
WINUSERAPI int WINAPI GetWindowTextA(HWND hWnd, LPSTR lpString, int nMaxCount);
WINUSERAPI int WINAPI GetWindowTextW(HWND hWnd, LPWSTR lpString, int nMaxCount);
WINUSERAPI int WINAPI GetWindowTextLengthA(HWND hWnd);
WINUSERAPI int WINAPI GetWindowTextLengthW(HWND hWnd);
WINUSERAPI WINBOOL WINAPI GetClientRect(HWND hWnd, LPRECT lpRect);
WINUSERAPI WINBOOL WINAPI GetWindowRect(HWND hWnd, LPRECT lpRect);
WINUSERAPI WINBOOL WINAPI AdjustWindowRect(LPRECT lpRect,
                                           DWORD dwStyle,
                                           WINBOOL bMenu);
WINUSERAPI WINBOOL WINAPI AdjustWindowRectEx(LPRECT lpRect,
                                             DWORD dwStyle,
                                             WINBOOL bMenu,
                                             DWORD dwExStyle);

#define HELPINFO_WINDOW 0x0001
#define HELPINFO_MENUITEM 0x0002

typedef struct tagHELPINFO {
  UINT cbSize;
  int iContextType;
  int iCtrlId;
  HANDLE hItemHandle;
  DWORD_PTR dwContextId;
  POINT MousePos;
} HELPINFO, *LPHELPINFO;

WINUSERAPI WINBOOL WINAPI SetWindowContextHelpId(HWND, DWORD);
WINUSERAPI DWORD WINAPI GetWindowContextHelpId(HWND);
WINUSERAPI WINBOOL WINAPI SetMenuContextHelpId(HMENU, DWORD);
WINUSERAPI DWORD WINAPI GetMenuContextHelpId(HMENU);

#ifndef NOMB

#define MB_OK 0x00000000L
#define MB_OKCANCEL 0x00000001L
#define MB_ABORTRETRYIGNORE 0x00000002L
#define MB_YESNOCANCEL 0x00000003L
#define MB_YESNO 0x00000004L
#define MB_RETRYCANCEL 0x00000005L
#define MB_CANCELTRYCONTINUE 0x00000006L
#define MB_ICONHAND 0x00000010L
#define MB_ICONQUESTION 0x00000020L
#define MB_ICONEXCLAMATION 0x00000030L
#define MB_ICONASTERISK 0x00000040L
#define MB_USERICON 0x00000080L
#define MB_ICONWARNING MB_ICONEXCLAMATION
#define MB_ICONERROR MB_ICONHAND
#define MB_ICONINFORMATION MB_ICONASTERISK
#define MB_ICONSTOP MB_ICONHAND
#define MB_DEFBUTTON1 0x00000000L
#define MB_DEFBUTTON2 0x00000100L
#define MB_DEFBUTTON3 0x00000200L
#define MB_DEFBUTTON4 0x00000300L
#define MB_APPLMODAL 0x00000000L
#define MB_SYSTEMMODAL 0x00001000L
#define MB_TASKMODAL 0x00002000L
#define MB_HELP 0x00004000L
#define MB_NOFOCUS 0x00008000L
#define MB_SETFOREGROUND 0x00010000L
#define MB_DEFAULT_DESKTOP_ONLY 0x00020000L
#define MB_TOPMOST 0x00040000L
#define MB_RIGHT 0x00080000L
#define MB_RTLREADING 0x00100000L
#define MB_SERVICE_NOTIFICATION 0x00200000L
#define MB_SERVICE_NOTIFICATION_NT3X 0x00040000L
#define MB_TYPEMASK 0x0000000FL
#define MB_ICONMASK 0x000000F0L
#define MB_DEFMASK 0x00000F00L
#define MB_MODEMASK 0x00003000L
#define MB_MISCMASK 0x0000C000L

#ifdef UNICODE
#define MessageBox MessageBoxW
#define MessageBoxEx MessageBoxExW
#else
#define MessageBox MessageBoxA
#define MessageBoxEx MessageBoxExA
#endif

WINUSERAPI int WINAPI MessageBoxA(HWND hWnd,
                                  LPCSTR lpText,
                                  LPCSTR lpCaption,
                                  UINT uType);
WINUSERAPI int WINAPI MessageBoxW(HWND hWnd,
                                  LPCWSTR lpText,
                                  LPCWSTR lpCaption,
                                  UINT uType);
WINUSERAPI int WINAPI MessageBoxExA(HWND hWnd,
                                    LPCSTR lpText,
                                    LPCSTR lpCaption,
                                    UINT uType,
                                    WORD wLanguageId);
WINUSERAPI int WINAPI MessageBoxExW(HWND hWnd,
                                    LPCWSTR lpText,
                                    LPCWSTR lpCaption,
                                    UINT uType,
                                    WORD wLanguageId);

typedef VOID(CALLBACK* MSGBOXCALLBACK)(LPHELPINFO lpHelpInfo);

typedef struct tagMSGBOXPARAMSA {
  UINT cbSize;
  HWND hwndOwner;
  HINSTANCE hInstance;
  LPCSTR lpszText;
  LPCSTR lpszCaption;
  DWORD dwStyle;
  LPCSTR lpszIcon;
  DWORD_PTR dwContextHelpId;
  MSGBOXCALLBACK lpfnMsgBoxCallback;
  DWORD dwLanguageId;
} MSGBOXPARAMSA, *PMSGBOXPARAMSA, *LPMSGBOXPARAMSA;

typedef struct tagMSGBOXPARAMSW {
  UINT cbSize;
  HWND hwndOwner;
  HINSTANCE hInstance;
  LPCWSTR lpszText;
  LPCWSTR lpszCaption;
  DWORD dwStyle;
  LPCWSTR lpszIcon;
  DWORD_PTR dwContextHelpId;
  MSGBOXCALLBACK lpfnMsgBoxCallback;
  DWORD dwLanguageId;
} MSGBOXPARAMSW, *PMSGBOXPARAMSW, *LPMSGBOXPARAMSW;

#ifdef UNICODE
typedef MSGBOXPARAMSW MSGBOXPARAMS;
typedef PMSGBOXPARAMSW PMSGBOXPARAMS;
typedef LPMSGBOXPARAMSW LPMSGBOXPARAMS;
#else
typedef MSGBOXPARAMSA MSGBOXPARAMS;
typedef PMSGBOXPARAMSA PMSGBOXPARAMS;
typedef LPMSGBOXPARAMSA LPMSGBOXPARAMS;
#endif

#ifdef UNICODE
#define MessageBoxIndirect MessageBoxIndirectW
#else
#define MessageBoxIndirect MessageBoxIndirectA
#endif

WINUSERAPI int WINAPI MessageBoxIndirectA(CONST MSGBOXPARAMSA* lpmbp);
WINUSERAPI int WINAPI MessageBoxIndirectW(CONST MSGBOXPARAMSW* lpmbp);
WINUSERAPI WINBOOL WINAPI MessageBeep(UINT uType);
#endif

WINUSERAPI int WINAPI ShowCursor(WINBOOL bShow);
WINUSERAPI WINBOOL WINAPI SetCursorPos(int X, int Y);
WINUSERAPI HCURSOR WINAPI SetCursor(HCURSOR hCursor);
WINUSERAPI WINBOOL WINAPI GetCursorPos(LPPOINT lpPoint);
WINUSERAPI WINBOOL WINAPI ClipCursor(CONST RECT* lpRect);
WINUSERAPI WINBOOL WINAPI GetClipCursor(LPRECT lpRect);
WINUSERAPI HCURSOR WINAPI GetCursor(VOID);
WINUSERAPI WINBOOL WINAPI CreateCaret(HWND hWnd,
                                      HBITMAP hBitmap,
                                      int nWidth,
                                      int nHeight);
WINUSERAPI UINT WINAPI GetCaretBlinkTime(VOID);
WINUSERAPI WINBOOL WINAPI SetCaretBlinkTime(UINT uMSeconds);
WINUSERAPI WINBOOL WINAPI DestroyCaret(VOID);
WINUSERAPI WINBOOL WINAPI HideCaret(HWND hWnd);
WINUSERAPI WINBOOL WINAPI ShowCaret(HWND hWnd);
WINUSERAPI WINBOOL WINAPI SetCaretPos(int X, int Y);
WINUSERAPI WINBOOL WINAPI GetCaretPos(LPPOINT lpPoint);
WINUSERAPI WINBOOL WINAPI ClientToScreen(HWND hWnd, LPPOINT lpPoint);
WINUSERAPI WINBOOL WINAPI ScreenToClient(HWND hWnd, LPPOINT lpPoint);
WINUSERAPI int WINAPI MapWindowPoints(HWND hWndFrom,
                                      HWND hWndTo,
                                      LPPOINT lpPoints,
                                      UINT cPoints);
WINUSERAPI HWND WINAPI WindowFromPoint(POINT Point);
WINUSERAPI HWND WINAPI ChildWindowFromPoint(HWND hWndParent, POINT Point);

#define CWP_ALL 0x0000
#define CWP_SKIPINVISIBLE 0x0001
#define CWP_SKIPDISABLED 0x0002
#define CWP_SKIPTRANSPARENT 0x0004

WINUSERAPI HWND WINAPI ChildWindowFromPointEx(HWND hwnd, POINT pt, UINT flags);

#ifndef NOCOLOR

#define CTLCOLOR_MSGBOX 0
#define CTLCOLOR_EDIT 1
#define CTLCOLOR_LISTBOX 2
#define CTLCOLOR_BTN 3
#define CTLCOLOR_DLG 4
#define CTLCOLOR_SCROLLBAR 5
#define CTLCOLOR_STATIC 6
#define CTLCOLOR_MAX 7

#define COLOR_SCROLLBAR 0
#define COLOR_BACKGROUND 1
#define COLOR_ACTIVECAPTION 2
#define COLOR_INACTIVECAPTION 3
#define COLOR_MENU 4
#define COLOR_WINDOW 5
#define COLOR_WINDOWFRAME 6
#define COLOR_MENUTEXT 7
#define COLOR_WINDOWTEXT 8
#define COLOR_CAPTIONTEXT 9
#define COLOR_ACTIVEBORDER 10
#define COLOR_INACTIVEBORDER 11
#define COLOR_APPWORKSPACE 12
#define COLOR_HIGHLIGHT 13
#define COLOR_HIGHLIGHTTEXT 14
#define COLOR_BTNFACE 15
#define COLOR_BTNSHADOW 16
#define COLOR_GRAYTEXT 17
#define COLOR_BTNTEXT 18
#define COLOR_INACTIVECAPTIONTEXT 19
#define COLOR_BTNHIGHLIGHT 20

#define COLOR_3DDKSHADOW 21
#define COLOR_3DLIGHT 22
#define COLOR_INFOTEXT 23
#define COLOR_INFOBK 24

#define COLOR_HOTLIGHT 26
#define COLOR_GRADIENTACTIVECAPTION 27
#define COLOR_GRADIENTINACTIVECAPTION 28
#define COLOR_MENUHILIGHT 29
#define COLOR_MENUBAR 30

#define COLOR_DESKTOP COLOR_BACKGROUND
#define COLOR_3DFACE COLOR_BTNFACE
#define COLOR_3DSHADOW COLOR_BTNSHADOW
#define COLOR_3DHIGHLIGHT COLOR_BTNHIGHLIGHT
#define COLOR_3DHILIGHT COLOR_BTNHIGHLIGHT
#define COLOR_BTNHILIGHT COLOR_BTNHIGHLIGHT

WINUSERAPI DWORD WINAPI GetSysColor(int nIndex);
WINUSERAPI HBRUSH WINAPI GetSysColorBrush(int nIndex);
WINUSERAPI WINBOOL WINAPI SetSysColors(int cElements,
                                       CONST INT* lpaElements,
                                       CONST COLORREF* lpaRgbValues);
#endif

WINUSERAPI WINBOOL WINAPI DrawFocusRect(HDC hDC, CONST RECT* lprc);
WINUSERAPI int WINAPI FillRect(HDC hDC, CONST RECT* lprc, HBRUSH hbr);
WINUSERAPI int WINAPI FrameRect(HDC hDC, CONST RECT* lprc, HBRUSH hbr);
WINUSERAPI WINBOOL WINAPI InvertRect(HDC hDC, CONST RECT* lprc);
WINUSERAPI WINBOOL WINAPI
SetRect(LPRECT lprc, int xLeft, int yTop, int xRight, int yBottom);
WINUSERAPI WINBOOL WINAPI SetRectEmpty(LPRECT lprc);
WINUSERAPI WINBOOL WINAPI CopyRect(LPRECT lprcDst, CONST RECT* lprcSrc);
WINUSERAPI WINBOOL WINAPI InflateRect(LPRECT lprc, int dx, int dy);
WINUSERAPI WINBOOL WINAPI IntersectRect(LPRECT lprcDst,
                                        CONST RECT* lprcSrc1,
                                        CONST RECT* lprcSrc2);
WINUSERAPI WINBOOL WINAPI UnionRect(LPRECT lprcDst,
                                    CONST RECT* lprcSrc1,
                                    CONST RECT* lprcSrc2);
WINUSERAPI WINBOOL WINAPI SubtractRect(LPRECT lprcDst,
                                       CONST RECT* lprcSrc1,
                                       CONST RECT* lprcSrc2);
WINUSERAPI WINBOOL WINAPI OffsetRect(LPRECT lprc, int dx, int dy);
WINUSERAPI WINBOOL WINAPI IsRectEmpty(CONST RECT* lprc);
WINUSERAPI WINBOOL WINAPI EqualRect(CONST RECT* lprc1, CONST RECT* lprc2);
WINUSERAPI WINBOOL WINAPI PtInRect(CONST RECT* lprc, POINT pt);

#ifndef NOWINOFFSETS

#ifdef UNICODE
#define GetWindowLong GetWindowLongW
#define SetWindowLong SetWindowLongW
#else
#define GetWindowLong GetWindowLongA
#define SetWindowLong SetWindowLongA
#endif

WINUSERAPI WORD WINAPI GetWindowWord(HWND hWnd, int nIndex);
WINUSERAPI WORD WINAPI SetWindowWord(HWND hWnd, int nIndex, WORD wNewWord);
WINUSERAPI LONG WINAPI GetWindowLongA(HWND hWnd, int nIndex);
WINUSERAPI LONG WINAPI GetWindowLongW(HWND hWnd, int nIndex);
WINUSERAPI LONG WINAPI SetWindowLongA(HWND hWnd, int nIndex, LONG dwNewLong);
WINUSERAPI LONG WINAPI SetWindowLongW(HWND hWnd, int nIndex, LONG dwNewLong);

#ifdef _WIN64

#ifdef UNICODE
#define GetWindowLongPtr GetWindowLongPtrW
#define SetWindowLongPtr SetWindowLongPtrW
#else
#define GetWindowLongPtr GetWindowLongPtrA
#define SetWindowLongPtr SetWindowLongPtrA
#endif

WINUSERAPI LONG_PTR WINAPI GetWindowLongPtrA(HWND hWnd, int nIndex);
WINUSERAPI LONG_PTR WINAPI GetWindowLongPtrW(HWND hWnd, int nIndex);
WINUSERAPI LONG_PTR WINAPI SetWindowLongPtrA(HWND hWnd,
                                             int nIndex,
                                             LONG_PTR dwNewLong);
WINUSERAPI LONG_PTR WINAPI SetWindowLongPtrW(HWND hWnd,
                                             int nIndex,
                                             LONG_PTR dwNewLong);
#else

#ifdef UNICODE
#define GetWindowLongPtr GetWindowLongPtrW
#define SetWindowLongPtr SetWindowLongPtrW
#else
#define GetWindowLongPtr GetWindowLongPtrA
#define SetWindowLongPtr SetWindowLongPtrA
#endif

#define GetWindowLongPtrA GetWindowLongA
#define GetWindowLongPtrW GetWindowLongW
#define SetWindowLongPtrA SetWindowLongA
#define SetWindowLongPtrW SetWindowLongW
#endif

#ifdef UNICODE
#define GetClassLong GetClassLongW
#define SetClassLong SetClassLongW
#else
#define GetClassLong GetClassLongA
#define SetClassLong SetClassLongA
#endif

WINUSERAPI WORD WINAPI GetClassWord(HWND hWnd, int nIndex);
WINUSERAPI WORD WINAPI SetClassWord(HWND hWnd, int nIndex, WORD wNewWord);
WINUSERAPI DWORD WINAPI GetClassLongA(HWND hWnd, int nIndex);
WINUSERAPI DWORD WINAPI GetClassLongW(HWND hWnd, int nIndex);
WINUSERAPI DWORD WINAPI SetClassLongA(HWND hWnd, int nIndex, LONG dwNewLong);
WINUSERAPI DWORD WINAPI SetClassLongW(HWND hWnd, int nIndex, LONG dwNewLong);

#ifdef _WIN64

#ifdef UNICODE
#define GetClassLongPtr GetClassLongPtrW
#define SetClassLongPtr SetClassLongPtrW
#else
#define GetClassLongPtr GetClassLongPtrA
#define SetClassLongPtr SetClassLongPtrA
#endif

WINUSERAPI ULONG_PTR WINAPI GetClassLongPtrA(HWND hWnd, int nIndex);
WINUSERAPI ULONG_PTR WINAPI GetClassLongPtrW(HWND hWnd, int nIndex);
WINUSERAPI ULONG_PTR WINAPI SetClassLongPtrA(HWND hWnd,
                                             int nIndex,
                                             LONG_PTR dwNewLong);
WINUSERAPI ULONG_PTR WINAPI SetClassLongPtrW(HWND hWnd,
                                             int nIndex,
                                             LONG_PTR dwNewLong);
#else
#ifdef UNICODE
#define GetClassLongPtr GetClassLongPtrW
#define SetClassLongPtr SetClassLongPtrW
#else
#define GetClassLongPtr GetClassLongPtrA
#define SetClassLongPtr SetClassLongPtrA
#endif

#define GetClassLongPtrA GetClassLongA
#define GetClassLongPtrW GetClassLongW
#define SetClassLongPtrA SetClassLongA
#define SetClassLongPtrW SetClassLongW
#endif
#endif

#ifdef UNICODE
#define FindWindow FindWindowW
#define FindWindowEx FindWindowExW
#define GetClassName GetClassNameW
#else
#define FindWindow FindWindowA
#define FindWindowEx FindWindowExA
#define GetClassName GetClassNameA
#endif

WINUSERAPI WINBOOL WINAPI GetProcessDefaultLayout(DWORD* pdwDefaultLayout);
WINUSERAPI WINBOOL WINAPI SetProcessDefaultLayout(DWORD dwDefaultLayout);
WINUSERAPI HWND WINAPI GetDesktopWindow(VOID);
WINUSERAPI HWND WINAPI GetParent(HWND hWnd);
WINUSERAPI HWND WINAPI SetParent(HWND hWndChild, HWND hWndNewParent);
WINUSERAPI WINBOOL WINAPI EnumChildWindows(HWND hWndParent,
                                           WNDENUMPROC lpEnumFunc,
                                           LPARAM lParam);
WINUSERAPI HWND WINAPI FindWindowA(LPCSTR lpClassName, LPCSTR lpWindowName);
WINUSERAPI HWND WINAPI FindWindowW(LPCWSTR lpClassName, LPCWSTR lpWindowName);
WINUSERAPI HWND WINAPI FindWindowExA(HWND hWndParent,
                                     HWND hWndChildAfter,
                                     LPCSTR lpszClass,
                                     LPCSTR lpszWindow);
WINUSERAPI HWND WINAPI FindWindowExW(HWND hWndParent,
                                     HWND hWndChildAfter,
                                     LPCWSTR lpszClass,
                                     LPCWSTR lpszWindow);
WINUSERAPI HWND WINAPI GetShellWindow(VOID);
WINUSERAPI WINBOOL WINAPI RegisterShellHookWindow(HWND hwnd);
WINUSERAPI WINBOOL WINAPI DeregisterShellHookWindow(HWND hwnd);
WINUSERAPI WINBOOL WINAPI EnumWindows(WNDENUMPROC lpEnumFunc, LPARAM lParam);
WINUSERAPI WINBOOL WINAPI EnumThreadWindows(DWORD dwThreadId,
                                            WNDENUMPROC lpfn,
                                            LPARAM lParam);

#define EnumTaskWindows(hTask, lpfn, lParam) \
  EnumThreadWindows(HandleToUlong(hTask), lpfn, lParam)

WINUSERAPI int WINAPI GetClassNameA(HWND hWnd,
                                    LPSTR lpClassName,
                                    int nMaxCount);
WINUSERAPI int WINAPI GetClassNameW(HWND hWnd,
                                    LPWSTR lpClassName,
                                    int nMaxCount);
WINUSERAPI HWND WINAPI GetTopWindow(HWND hWnd);

#define GetNextWindow(hWnd, wCmd) GetWindow(hWnd, wCmd)
#define GetSysModalWindow() (NULL)
#define SetSysModalWindow(hWnd) (NULL)

WINUSERAPI DWORD WINAPI GetWindowThreadProcessId(HWND hWnd,
                                                 LPDWORD lpdwProcessId);
WINUSERAPI WINBOOL WINAPI IsGUIThread(WINBOOL bConvert);

#define GetWindowTask(hWnd) \
  ((HANDLE)(DWORD_PTR)GetWindowThreadProcessId(hWnd, NULL))

WINUSERAPI HWND WINAPI GetLastActivePopup(HWND hWnd);

#define GW_HWNDFIRST 0
#define GW_HWNDLAST 1
#define GW_HWNDNEXT 2
#define GW_HWNDPREV 3
#define GW_OWNER 4
#define GW_CHILD 5
#define GW_ENABLEDPOPUP 6
#define GW_MAX 6

WINUSERAPI HWND WINAPI GetWindow(HWND hWnd, UINT uCmd);

#ifndef NOWH

#ifdef UNICODE
#define SetWindowsHook SetWindowsHookW
#define SetWindowsHookEx SetWindowsHookExW
#else
#define SetWindowsHook SetWindowsHookA
#define SetWindowsHookEx SetWindowsHookExA
#endif

WINUSERAPI HHOOK WINAPI SetWindowsHookA(int nFilterType,
                                        HOOKPROC pfnFilterProc);
WINUSERAPI HHOOK WINAPI SetWindowsHookW(int nFilterType,
                                        HOOKPROC pfnFilterProc);
WINUSERAPI WINBOOL WINAPI UnhookWindowsHook(int nCode, HOOKPROC pfnFilterProc);
WINUSERAPI HHOOK WINAPI SetWindowsHookExA(int idHook,
                                          HOOKPROC lpfn,
                                          HINSTANCE hmod,
                                          DWORD dwThreadId);
WINUSERAPI HHOOK WINAPI SetWindowsHookExW(int idHook,
                                          HOOKPROC lpfn,
                                          HINSTANCE hmod,
                                          DWORD dwThreadId);
WINUSERAPI WINBOOL WINAPI UnhookWindowsHookEx(HHOOK hhk);
WINUSERAPI LRESULT WINAPI CallNextHookEx(HHOOK hhk,
                                         int nCode,
                                         WPARAM wParam,
                                         LPARAM lParam);
#define DefHookProc(nCode, wParam, lParam, phhk) \
  CallNextHookEx(*phhk, nCode, wParam, lParam)
#endif

#ifndef NOMENUS

#define MF_INSERT 0x00000000L
#define MF_CHANGE 0x00000080L
#define MF_APPEND 0x00000100L
#define MF_DELETE 0x00000200L
#define MF_REMOVE 0x00001000L
#define MF_BYCOMMAND 0x00000000L
#define MF_BYPOSITION 0x00000400L
#define MF_SEPARATOR 0x00000800L
#define MF_ENABLED 0x00000000L
#define MF_GRAYED 0x00000001L
#define MF_DISABLED 0x00000002L
#define MF_UNCHECKED 0x00000000L
#define MF_CHECKED 0x00000008L
#define MF_USECHECKBITMAPS 0x00000200L
#define MF_STRING 0x00000000L
#define MF_BITMAP 0x00000004L
#define MF_OWNERDRAW 0x00000100L
#define MF_POPUP 0x00000010L
#define MF_MENUBARBREAK 0x00000020L
#define MF_MENUBREAK 0x00000040L
#define MF_UNHILITE 0x00000000L
#define MF_HILITE 0x00000080L
#define MF_DEFAULT 0x00001000L
#define MF_SYSMENU 0x00002000L
#define MF_HELP 0x00004000L
#define MF_RIGHTJUSTIFY 0x00004000L
#define MF_MOUSESELECT 0x00008000L
#define MF_END 0x00000080L

#define MFT_STRING MF_STRING
#define MFT_BITMAP MF_BITMAP
#define MFT_MENUBARBREAK MF_MENUBARBREAK
#define MFT_MENUBREAK MF_MENUBREAK
#define MFT_OWNERDRAW MF_OWNERDRAW
#define MFT_RADIOCHECK 0x00000200L
#define MFT_SEPARATOR MF_SEPARATOR
#define MFT_RIGHTORDER 0x00002000L
#define MFT_RIGHTJUSTIFY MF_RIGHTJUSTIFY

#define MFS_GRAYED 0x00000003L
#define MFS_DISABLED MFS_GRAYED
#define MFS_CHECKED MF_CHECKED
#define MFS_HILITE MF_HILITE
#define MFS_ENABLED MF_ENABLED
#define MFS_UNCHECKED MF_UNCHECKED
#define MFS_UNHILITE MF_UNHILITE
#define MFS_DEFAULT MF_DEFAULT

WINUSERAPI WINBOOL WINAPI
CheckMenuRadioItem(HMENU hmenu, UINT first, UINT last, UINT check, UINT flags);

typedef struct {
  WORD versionNumber;
  WORD offset;
} MENUITEMTEMPLATEHEADER, *PMENUITEMTEMPLATEHEADER;

typedef struct {
  WORD mtOption;
  WORD mtID;
  WCHAR mtString[1];
} MENUITEMTEMPLATE, *PMENUITEMTEMPLATE;
#define MF_END 0x00000080L
#endif

#ifndef NOSYSCOMMANDS

#define SC_SIZE 0xF000
#define SC_MOVE 0xF010
#define SC_MINIMIZE 0xF020
#define SC_MAXIMIZE 0xF030
#define SC_NEXTWINDOW 0xF040
#define SC_PREVWINDOW 0xF050
#define SC_CLOSE 0xF060
#define SC_VSCROLL 0xF070
#define SC_HSCROLL 0xF080
#define SC_MOUSEMENU 0xF090
#define SC_KEYMENU 0xF100
#define SC_ARRANGE 0xF110
#define SC_RESTORE 0xF120
#define SC_TASKLIST 0xF130
#define SC_SCREENSAVE 0xF140
#define SC_HOTKEY 0xF150
#define SC_DEFAULT 0xF160
#define SC_MONITORPOWER 0xF170
#define SC_CONTEXTHELP 0xF180
#define SC_SEPARATOR 0xF00F
#define SC_ICON SC_MINIMIZE
#define SC_ZOOM SC_MAXIMIZE
#endif

#ifdef UNICODE
#define LoadBitmap LoadBitmapW
#define LoadCursor LoadCursorW
#define LoadCursorFromFile LoadCursorFromFileW
#else
#define LoadBitmap LoadBitmapA
#define LoadCursor LoadCursorA
#define LoadCursorFromFile LoadCursorFromFileA
#endif

WINUSERAPI HBITMAP WINAPI LoadBitmapA(HINSTANCE hInstance, LPCSTR lpBitmapName);
WINUSERAPI HBITMAP WINAPI LoadBitmapW(HINSTANCE hInstance,
                                      LPCWSTR lpBitmapName);
WINUSERAPI HCURSOR WINAPI LoadCursorA(HINSTANCE hInstance, LPCSTR lpCursorName);
WINUSERAPI HCURSOR WINAPI LoadCursorW(HINSTANCE hInstance,
                                      LPCWSTR lpCursorName);
WINUSERAPI HCURSOR WINAPI LoadCursorFromFileA(LPCSTR lpFileName);
WINUSERAPI HCURSOR WINAPI LoadCursorFromFileW(LPCWSTR lpFileName);
WINUSERAPI HCURSOR WINAPI CreateCursor(HINSTANCE hInst,
                                       int xHotSpot,
                                       int yHotSpot,
                                       int nWidth,
                                       int nHeight,
                                       CONST VOID* pvANDPlane,
                                       CONST VOID* pvXORPlane);
WINUSERAPI WINBOOL WINAPI DestroyCursor(HCURSOR hCursor);

#define CopyCursor(pcur) ((HCURSOR)CopyIcon((HICON)(pcur)))

#define IDC_ARROW MAKEINTRESOURCE(32512)
#define IDC_IBEAM MAKEINTRESOURCE(32513)
#define IDC_WAIT MAKEINTRESOURCE(32514)
#define IDC_CROSS MAKEINTRESOURCE(32515)
#define IDC_UPARROW MAKEINTRESOURCE(32516)
#define IDC_SIZE MAKEINTRESOURCE(32640)
#define IDC_ICON MAKEINTRESOURCE(32641)
#define IDC_SIZENWSE MAKEINTRESOURCE(32642)
#define IDC_SIZENESW MAKEINTRESOURCE(32643)
#define IDC_SIZEWE MAKEINTRESOURCE(32644)
#define IDC_SIZENS MAKEINTRESOURCE(32645)
#define IDC_SIZEALL MAKEINTRESOURCE(32646)
#define IDC_NO MAKEINTRESOURCE(32648)
#define IDC_HAND MAKEINTRESOURCE(32649)
#define IDC_APPSTARTING MAKEINTRESOURCE(32650)
#define IDC_HELP MAKEINTRESOURCE(32651)

WINUSERAPI WINBOOL WINAPI SetSystemCursor(HCURSOR hcur, DWORD id);

typedef struct _ICONINFO {
  WINBOOL fIcon;
  DWORD xHotspot;
  DWORD yHotspot;
  HBITMAP hbmMask;
  HBITMAP hbmColor;
} ICONINFO;
typedef ICONINFO* PICONINFO;

#ifdef UNICODE
#define LoadIcon LoadIconW
#define PrivateExtractIcons PrivateExtractIconsW
#else
#define LoadIcon LoadIconA
#define PrivateExtractIcons PrivateExtractIconsA
#endif

WINUSERAPI HICON WINAPI LoadIconA(HINSTANCE hInstance, LPCSTR lpIconName);
WINUSERAPI HICON WINAPI LoadIconW(HINSTANCE hInstance, LPCWSTR lpIconName);
WINUSERAPI UINT WINAPI PrivateExtractIconsA(LPCSTR szFileName,
                                            int nIconIndex,
                                            int cxIcon,
                                            int cyIcon,
                                            HICON* phicon,
                                            UINT* piconid,
                                            UINT nIcons,
                                            UINT flags);
WINUSERAPI UINT WINAPI PrivateExtractIconsW(LPCWSTR szFileName,
                                            int nIconIndex,
                                            int cxIcon,
                                            int cyIcon,
                                            HICON* phicon,
                                            UINT* piconid,
                                            UINT nIcons,
                                            UINT flags);
WINUSERAPI HICON WINAPI CreateIcon(HINSTANCE hInstance,
                                   int nWidth,
                                   int nHeight,
                                   BYTE cPlanes,
                                   BYTE cBitsPixel,
                                   CONST BYTE* lpbANDbits,
                                   CONST BYTE* lpbXORbits);
WINUSERAPI WINBOOL WINAPI DestroyIcon(HICON hIcon);
WINUSERAPI int WINAPI LookupIconIdFromDirectory(PBYTE presbits, WINBOOL fIcon);
WINUSERAPI int WINAPI LookupIconIdFromDirectoryEx(PBYTE presbits,
                                                  WINBOOL fIcon,
                                                  int cxDesired,
                                                  int cyDesired,
                                                  UINT Flags);
WINUSERAPI HICON WINAPI CreateIconFromResource(PBYTE presbits,
                                               DWORD dwResSize,
                                               WINBOOL fIcon,
                                               DWORD dwVer);
WINUSERAPI HICON WINAPI CreateIconFromResourceEx(PBYTE presbits,
                                                 DWORD dwResSize,
                                                 WINBOOL fIcon,
                                                 DWORD dwVer,
                                                 int cxDesired,
                                                 int cyDesired,
                                                 UINT Flags);

typedef struct tagCURSORSHAPE {
  int xHotSpot;
  int yHotSpot;
  int cx;
  int cy;
  int cbWidth;
  BYTE Planes;
  BYTE BitsPixel;
} CURSORSHAPE, *LPCURSORSHAPE;

#define IMAGE_BITMAP 0
#define IMAGE_ICON 1
#define IMAGE_CURSOR 2
#define IMAGE_ENHMETAFILE 3

#define LR_DEFAULTCOLOR 0x0000
#define LR_MONOCHROME 0x0001
#define LR_COLOR 0x0002
#define LR_COPYRETURNORG 0x0004
#define LR_COPYDELETEORG 0x0008
#define LR_LOADFROMFILE 0x0010
#define LR_LOADTRANSPARENT 0x0020
#define LR_DEFAULTSIZE 0x0040
#define LR_VGACOLOR 0x0080
#define LR_LOADMAP3DCOLORS 0x1000
#define LR_CREATEDIBSECTION 0x2000
#define LR_COPYFROMRESOURCE 0x4000
#define LR_SHARED 0x8000

#ifdef UNICODE
#define LoadImage LoadImageW
#else
#define LoadImage LoadImageA
#endif

WINUSERAPI HANDLE WINAPI LoadImageA(HINSTANCE hInst,
                                    LPCSTR name,
                                    UINT type,
                                    int cx,
                                    int cy,
                                    UINT fuLoad);
WINUSERAPI HANDLE WINAPI LoadImageW(HINSTANCE hInst,
                                    LPCWSTR name,
                                    UINT type,
                                    int cx,
                                    int cy,
                                    UINT fuLoad);
WINUSERAPI HANDLE WINAPI
CopyImage(HANDLE h, UINT type, int cx, int cy, UINT flags);

#define DI_MASK 0x0001
#define DI_IMAGE 0x0002
#define DI_NORMAL 0x0003
#define DI_COMPAT 0x0004
#define DI_DEFAULTSIZE 0x0008
#define DI_NOMIRROR 0x0010

WINUSERAPI WINBOOL WINAPI DrawIconEx(HDC hdc,
                                     int xLeft,
                                     int yTop,
                                     HICON hIcon,
                                     int cxWidth,
                                     int cyWidth,
                                     UINT istepIfAniCur,
                                     HBRUSH hbrFlickerFreeDraw,
                                     UINT diFlags);
WINUSERAPI HICON WINAPI CreateIconIndirect(PICONINFO piconinfo);
WINUSERAPI HICON WINAPI CopyIcon(HICON hIcon);
WINUSERAPI WINBOOL WINAPI GetIconInfo(HICON hIcon, PICONINFO piconinfo);

#define RES_ICON 1
#define RES_CURSOR 2

#ifdef OEMRESOURCE

#define OBM_CLOSE 32754
#define OBM_UPARROW 32753
#define OBM_DNARROW 32752
#define OBM_RGARROW 32751
#define OBM_LFARROW 32750
#define OBM_REDUCE 32749
#define OBM_ZOOM 32748
#define OBM_RESTORE 32747
#define OBM_REDUCED 32746
#define OBM_ZOOMD 32745
#define OBM_RESTORED 32744
#define OBM_UPARROWD 32743
#define OBM_DNARROWD 32742
#define OBM_RGARROWD 32741
#define OBM_LFARROWD 32740
#define OBM_MNARROW 32739
#define OBM_COMBO 32738
#define OBM_UPARROWI 32737
#define OBM_DNARROWI 32736
#define OBM_RGARROWI 32735
#define OBM_LFARROWI 32734

#define OBM_OLD_CLOSE 32767
#define OBM_SIZE 32766
#define OBM_OLD_UPARROW 32765
#define OBM_OLD_DNARROW 32764
#define OBM_OLD_RGARROW 32763
#define OBM_OLD_LFARROW 32762
#define OBM_BTSIZE 32761
#define OBM_CHECK 32760
#define OBM_CHECKBOXES 32759
#define OBM_BTNCORNERS 32758
#define OBM_OLD_REDUCE 32757
#define OBM_OLD_ZOOM 32756
#define OBM_OLD_RESTORE 32755

#define OCR_NORMAL 32512
#define OCR_IBEAM 32513
#define OCR_WAIT 32514
#define OCR_CROSS 32515
#define OCR_UP 32516
#define OCR_SIZE 32640
#define OCR_ICON 32641
#define OCR_SIZENWSE 32642
#define OCR_SIZENESW 32643
#define OCR_SIZEWE 32644
#define OCR_SIZENS 32645
#define OCR_SIZEALL 32646
#define OCR_ICOCUR 32647
#define OCR_NO 32648
#define OCR_HAND 32649
#define OCR_APPSTARTING 32650

#define OIC_SAMPLE 32512
#define OIC_HAND 32513
#define OIC_QUES 32514
#define OIC_BANG 32515
#define OIC_NOTE 32516
#define OIC_WINLOGO 32517
#define OIC_WARNING OIC_BANG
#define OIC_ERROR OIC_HAND
#define OIC_INFORMATION OIC_NOTE
#endif

#define ORD_LANGDRIVER 1

#ifndef NOICONS

#ifdef RC_INVOKED
#define IDI_APPLICATION 32512
#define IDI_HAND 32513
#define IDI_QUESTION 32514
#define IDI_EXCLAMATION 32515
#define IDI_ASTERISK 32516
#define IDI_WINLOGO 32517
#else
#define IDI_APPLICATION MAKEINTRESOURCE(32512)
#define IDI_HAND MAKEINTRESOURCE(32513)
#define IDI_QUESTION MAKEINTRESOURCE(32514)
#define IDI_EXCLAMATION MAKEINTRESOURCE(32515)
#define IDI_ASTERISK MAKEINTRESOURCE(32516)
#define IDI_WINLOGO MAKEINTRESOURCE(32517)
#endif

#define IDI_WARNING IDI_EXCLAMATION
#define IDI_ERROR IDI_HAND
#define IDI_INFORMATION IDI_ASTERISK
#endif

#ifdef UNICODE
#define LoadString LoadStringW
#else
#define LoadString LoadStringA
#endif

WINUSERAPI int WINAPI LoadStringA(HINSTANCE hInstance,
                                  UINT uID,
                                  LPSTR lpBuffer,
                                  int cchBufferMax);
WINUSERAPI int WINAPI LoadStringW(HINSTANCE hInstance,
                                  UINT uID,
                                  LPWSTR lpBuffer,
                                  int cchBufferMax);

#define IDOK 1
#define IDCANCEL 2
#define IDABORT 3
#define IDRETRY 4
#define IDIGNORE 5
#define IDYES 6
#define IDNO 7
#define IDCLOSE 8
#define IDHELP 9
#define IDTRYAGAIN 10
#define IDCONTINUE 11

#ifndef IDTIMEOUT
#define IDTIMEOUT 32000
#endif

#ifndef NOCTLMGR

#ifndef NOWINSTYLES
#define ES_LEFT 0x0000L
#define ES_CENTER 0x0001L
#define ES_RIGHT 0x0002L
#define ES_MULTILINE 0x0004L
#define ES_UPPERCASE 0x0008L
#define ES_LOWERCASE 0x0010L
#define ES_PASSWORD 0x0020L
#define ES_AUTOVSCROLL 0x0040L
#define ES_AUTOHSCROLL 0x0080L
#define ES_NOHIDESEL 0x0100L
#define ES_OEMCONVERT 0x0400L
#define ES_READONLY 0x0800L
#define ES_WANTRETURN 0x1000L
#define ES_NUMBER 0x2000L
#endif

#define EN_SETFOCUS 0x0100
#define EN_KILLFOCUS 0x0200
#define EN_CHANGE 0x0300
#define EN_UPDATE 0x0400
#define EN_ERRSPACE 0x0500
#define EN_MAXTEXT 0x0501
#define EN_HSCROLL 0x0601
#define EN_VSCROLL 0x0602
#define EN_ALIGN_LTR_EC 0x0700
#define EN_ALIGN_RTL_EC 0x0701

#define EC_LEFTMARGIN 0x0001
#define EC_RIGHTMARGIN 0x0002
#define EC_USEFONTINFO 0xffff

#define EMSIS_COMPOSITIONSTRING 0x0001

#define EIMES_GETCOMPSTRATONCE 0x0001
#define EIMES_CANCELCOMPSTRINFOCUS 0x0002
#define EIMES_COMPLETECOMPSTRKILLFOCUS 0x0004

#ifndef NOWINMESSAGES

#define EM_GETSEL 0x00B0
#define EM_SETSEL 0x00B1
#define EM_GETRECT 0x00B2
#define EM_SETRECT 0x00B3
#define EM_SETRECTNP 0x00B4
#define EM_SCROLL 0x00B5
#define EM_LINESCROLL 0x00B6
#define EM_SCROLLCARET 0x00B7
#define EM_GETMODIFY 0x00B8
#define EM_SETMODIFY 0x00B9
#define EM_GETLINECOUNT 0x00BA
#define EM_LINEINDEX 0x00BB
#define EM_SETHANDLE 0x00BC
#define EM_GETHANDLE 0x00BD
#define EM_GETTHUMB 0x00BE
#define EM_LINELENGTH 0x00C1
#define EM_REPLACESEL 0x00C2
#define EM_GETLINE 0x00C4
#define EM_LIMITTEXT 0x00C5
#define EM_CANUNDO 0x00C6
#define EM_UNDO 0x00C7
#define EM_FMTLINES 0x00C8
#define EM_LINEFROMCHAR 0x00C9
#define EM_SETTABSTOPS 0x00CB
#define EM_SETPASSWORDCHAR 0x00CC
#define EM_EMPTYUNDOBUFFER 0x00CD
#define EM_GETFIRSTVISIBLELINE 0x00CE
#define EM_SETREADONLY 0x00CF
#define EM_SETWORDBREAKPROC 0x00D0
#define EM_GETWORDBREAKPROC 0x00D1
#define EM_GETPASSWORDCHAR 0x00D2
#define EM_SETMARGINS 0x00D3
#define EM_GETMARGINS 0x00D4
#define EM_SETLIMITTEXT EM_LIMITTEXT
#define EM_GETLIMITTEXT 0x00D5
#define EM_POSFROMCHAR 0x00D6
#define EM_CHARFROMPOS 0x00D7
#define EM_SETIMESTATUS 0x00D8
#define EM_GETIMESTATUS 0x00D9
#endif

#define WB_LEFT 0
#define WB_RIGHT 1
#define WB_ISDELIMITER 2

#define BS_PUSHBUTTON 0x00000000L
#define BS_DEFPUSHBUTTON 0x00000001L
#define BS_CHECKBOX 0x00000002L
#define BS_AUTOCHECKBOX 0x00000003L
#define BS_RADIOBUTTON 0x00000004L
#define BS_3STATE 0x00000005L
#define BS_AUTO3STATE 0x00000006L
#define BS_GROUPBOX 0x00000007L
#define BS_USERBUTTON 0x00000008L
#define BS_AUTORADIOBUTTON 0x00000009L
#define BS_PUSHBOX 0x0000000AL
#define BS_OWNERDRAW 0x0000000BL
#define BS_TYPEMASK 0x0000000FL
#define BS_LEFTTEXT 0x00000020L
#define BS_TEXT 0x00000000L
#define BS_ICON 0x00000040L
#define BS_BITMAP 0x00000080L
#define BS_LEFT 0x00000100L
#define BS_RIGHT 0x00000200L
#define BS_CENTER 0x00000300L
#define BS_TOP 0x00000400L
#define BS_BOTTOM 0x00000800L
#define BS_VCENTER 0x00000C00L
#define BS_PUSHLIKE 0x00001000L
#define BS_MULTILINE 0x00002000L
#define BS_NOTIFY 0x00004000L
#define BS_FLAT 0x00008000L
#define BS_RIGHTBUTTON BS_LEFTTEXT

#define BN_CLICKED 0
#define BN_PAINT 1
#define BN_HILITE 2
#define BN_UNHILITE 3
#define BN_DISABLE 4
#define BN_DOUBLECLICKED 5
#define BN_PUSHED BN_HILITE
#define BN_UNPUSHED BN_UNHILITE
#define BN_DBLCLK BN_DOUBLECLICKED
#define BN_SETFOCUS 6
#define BN_KILLFOCUS 7

#define BM_GETCHECK 0x00F0
#define BM_SETCHECK 0x00F1
#define BM_GETSTATE 0x00F2
#define BM_SETSTATE 0x00F3
#define BM_SETSTYLE 0x00F4
#define BM_CLICK 0x00F5
#define BM_GETIMAGE 0x00F6
#define BM_SETIMAGE 0x00F7

#define BST_UNCHECKED 0x0000
#define BST_CHECKED 0x0001
#define BST_INDETERMINATE 0x0002
#define BST_PUSHED 0x0004
#define BST_FOCUS 0x0008

#define SS_LEFT 0x00000000L
#define SS_CENTER 0x00000001L
#define SS_RIGHT 0x00000002L
#define SS_ICON 0x00000003L
#define SS_BLACKRECT 0x00000004L
#define SS_GRAYRECT 0x00000005L
#define SS_WHITERECT 0x00000006L
#define SS_BLACKFRAME 0x00000007L
#define SS_GRAYFRAME 0x00000008L
#define SS_WHITEFRAME 0x00000009L
#define SS_USERITEM 0x0000000AL
#define SS_SIMPLE 0x0000000BL
#define SS_LEFTNOWORDWRAP 0x0000000CL
#define SS_OWNERDRAW 0x0000000DL
#define SS_BITMAP 0x0000000EL
#define SS_ENHMETAFILE 0x0000000FL
#define SS_ETCHEDHORZ 0x00000010L
#define SS_ETCHEDVERT 0x00000011L
#define SS_ETCHEDFRAME 0x00000012L
#define SS_TYPEMASK 0x0000001FL
#define SS_REALSIZECONTROL 0x00000040L
#define SS_NOPREFIX 0x00000080L
#define SS_NOTIFY 0x00000100L
#define SS_CENTERIMAGE 0x00000200L
#define SS_RIGHTJUST 0x00000400L
#define SS_REALSIZEIMAGE 0x00000800L
#define SS_SUNKEN 0x00001000L
#define SS_EDITCONTROL 0x00002000L
#define SS_ENDELLIPSIS 0x00004000L
#define SS_PATHELLIPSIS 0x00008000L
#define SS_WORDELLIPSIS 0x0000C000L
#define SS_ELLIPSISMASK 0x0000C000L

#ifndef NOWINMESSAGES

#define STM_SETICON 0x0170
#define STM_GETICON 0x0171
#define STM_SETIMAGE 0x0172
#define STM_GETIMAGE 0x0173
#define STN_CLICKED 0
#define STN_DBLCLK 1
#define STN_ENABLE 2
#define STN_DISABLE 3
#define STM_MSGMAX 0x0174
#endif

#define WC_DIALOG (MAKEINTATOM(0x8002))

#define DWL_MSGRESULT 0
#define DWL_DLGPROC 4
#define DWL_USER 8

#ifdef _WIN64

#undef DWL_MSGRESULT
#undef DWL_DLGPROC
#undef DWL_USER
#endif

#define DWLP_MSGRESULT 0
#define DWLP_DLGPROC DWLP_MSGRESULT + sizeof(LRESULT)
#define DWLP_USER DWLP_DLGPROC + sizeof(DLGPROC)

#ifndef NOMSG

#ifdef UNICODE
#define IsDialogMessage IsDialogMessageW
#else
#define IsDialogMessage IsDialogMessageA
#endif

WINUSERAPI WINBOOL WINAPI IsDialogMessageA(HWND hDlg, LPMSG lpMsg);
WINUSERAPI WINBOOL WINAPI IsDialogMessageW(HWND hDlg, LPMSG lpMsg);
#endif

#ifdef UNICODE
#define DlgDirList DlgDirListW
#define DlgDirSelectEx DlgDirSelectExW
#define DlgDirListComboBox DlgDirListComboBoxW
#define DlgDirSelectComboBoxEx DlgDirSelectComboBoxExW
#else
#define DlgDirList DlgDirListA
#define DlgDirSelectEx DlgDirSelectExA
#define DlgDirListComboBox DlgDirListComboBoxA
#define DlgDirSelectComboBoxEx DlgDirSelectComboBoxExA
#endif

WINUSERAPI WINBOOL WINAPI MapDialogRect(HWND hDlg, LPRECT lpRect);
WINUSERAPI int WINAPI DlgDirListA(HWND hDlg,
                                  LPSTR lpPathSpec,
                                  int nIDListBox,
                                  int nIDStaticPath,
                                  UINT uFileType);
WINUSERAPI int WINAPI DlgDirListW(HWND hDlg,
                                  LPWSTR lpPathSpec,
                                  int nIDListBox,
                                  int nIDStaticPath,
                                  UINT uFileType);

#define DDL_READWRITE 0x0000
#define DDL_READONLY 0x0001
#define DDL_HIDDEN 0x0002
#define DDL_SYSTEM 0x0004
#define DDL_DIRECTORY 0x0010
#define DDL_ARCHIVE 0x0020

#define DDL_POSTMSGS 0x2000
#define DDL_DRIVES 0x4000
#define DDL_EXCLUSIVE 0x8000

WINUSERAPI WINBOOL WINAPI DlgDirSelectExA(HWND hwndDlg,
                                          LPSTR lpString,
                                          int chCount,
                                          int idListBox);
WINUSERAPI WINBOOL WINAPI DlgDirSelectExW(HWND hwndDlg,
                                          LPWSTR lpString,
                                          int chCount,
                                          int idListBox);
WINUSERAPI int WINAPI DlgDirListComboBoxA(HWND hDlg,
                                          LPSTR lpPathSpec,
                                          int nIDComboBox,
                                          int nIDStaticPath,
                                          UINT uFiletype);
WINUSERAPI int WINAPI DlgDirListComboBoxW(HWND hDlg,
                                          LPWSTR lpPathSpec,
                                          int nIDComboBox,
                                          int nIDStaticPath,
                                          UINT uFiletype);
WINUSERAPI WINBOOL WINAPI DlgDirSelectComboBoxExA(HWND hwndDlg,
                                                  LPSTR lpString,
                                                  int cchOut,
                                                  int idComboBox);
WINUSERAPI WINBOOL WINAPI DlgDirSelectComboBoxExW(HWND hwndDlg,
                                                  LPWSTR lpString,
                                                  int cchOut,
                                                  int idComboBox);

#define DS_ABSALIGN 0x01L
#define DS_SYSMODAL 0x02L
#define DS_LOCALEDIT 0x20L
#define DS_SETFONT 0x40L
#define DS_MODALFRAME 0x80L
#define DS_NOIDLEMSG 0x100L
#define DS_SETFOREGROUND 0x200L

#define DS_3DLOOK 0x0004L
#define DS_FIXEDSYS 0x0008L
#define DS_NOFAILCREATE 0x0010L
#define DS_CONTROL 0x0400L
#define DS_CENTER 0x0800L
#define DS_CENTERMOUSE 0x1000L
#define DS_CONTEXTHELP 0x2000L

#define DS_SHELLFONT (DS_SETFONT | DS_FIXEDSYS)

#if (_WIN32_WCE >= 0x0500)
#define DS_USEPIXELS 0x8000L
#endif

#define DM_GETDEFID (WM_USER + 0)
#define DM_SETDEFID (WM_USER + 1)
#define DM_REPOSITION (WM_USER + 2)

#define DC_HASDEFID 0x534B

#define DLGC_WANTARROWS 0x0001
#define DLGC_WANTTAB 0x0002
#define DLGC_WANTALLKEYS 0x0004
#define DLGC_WANTMESSAGE 0x0004
#define DLGC_HASSETSEL 0x0008
#define DLGC_DEFPUSHBUTTON 0x0010
#define DLGC_UNDEFPUSHBUTTON 0x0020
#define DLGC_RADIOBUTTON 0x0040
#define DLGC_WANTCHARS 0x0080
#define DLGC_STATIC 0x0100
#define DLGC_BUTTON 0x2000

#define LB_CTLCODE 0L

#define LB_OKAY 0
#define LB_ERR (-1)
#define LB_ERRSPACE (-2)

#define LBN_ERRSPACE (-2)
#define LBN_SELCHANGE 1
#define LBN_DBLCLK 2
#define LBN_SELCANCEL 3
#define LBN_SETFOCUS 4
#define LBN_KILLFOCUS 5

#ifndef NOWINMESSAGES

#define LB_ADDSTRING 0x0180
#define LB_INSERTSTRING 0x0181
#define LB_DELETESTRING 0x0182
#define LB_SELITEMRANGEEX 0x0183
#define LB_RESETCONTENT 0x0184
#define LB_SETSEL 0x0185
#define LB_SETCURSEL 0x0186
#define LB_GETSEL 0x0187
#define LB_GETCURSEL 0x0188
#define LB_GETTEXT 0x0189
#define LB_GETTEXTLEN 0x018A
#define LB_GETCOUNT 0x018B
#define LB_SELECTSTRING 0x018C
#define LB_DIR 0x018D
#define LB_GETTOPINDEX 0x018E
#define LB_FINDSTRING 0x018F
#define LB_GETSELCOUNT 0x0190
#define LB_GETSELITEMS 0x0191
#define LB_SETTABSTOPS 0x0192
#define LB_GETHORIZONTALEXTENT 0x0193
#define LB_SETHORIZONTALEXTENT 0x0194
#define LB_SETCOLUMNWIDTH 0x0195
#define LB_ADDFILE 0x0196
#define LB_SETTOPINDEX 0x0197
#define LB_GETITEMRECT 0x0198
#define LB_GETITEMDATA 0x0199
#define LB_SETITEMDATA 0x019A
#define LB_SELITEMRANGE 0x019B
#define LB_SETANCHORINDEX 0x019C
#define LB_GETANCHORINDEX 0x019D
#define LB_SETCARETINDEX 0x019E
#define LB_GETCARETINDEX 0x019F
#define LB_SETITEMHEIGHT 0x01A0
#define LB_GETITEMHEIGHT 0x01A1
#define LB_FINDSTRINGEXACT 0x01A2
#define LB_SETLOCALE 0x01A5
#define LB_GETLOCALE 0x01A6
#define LB_SETCOUNT 0x01A7
#define LB_INITSTORAGE 0x01A8
#define LB_ITEMFROMPOINT 0x01A9
#if (_WIN32_WCE >= 0x0400)
#define LB_MULTIPLEADDSTRING 0x01B1
#endif
#define LB_GETLISTBOXINFO 0x01B2
#define LB_MSGMAX 0x01B3
#endif

#ifndef NOWINSTYLES

#define LBS_NOTIFY 0x0001L
#define LBS_SORT 0x0002L
#define LBS_NOREDRAW 0x0004L
#define LBS_MULTIPLESEL 0x0008L
#define LBS_OWNERDRAWFIXED 0x0010L
#define LBS_OWNERDRAWVARIABLE 0x0020L
#define LBS_HASSTRINGS 0x0040L
#define LBS_USETABSTOPS 0x0080L
#define LBS_NOINTEGRALHEIGHT 0x0100L
#define LBS_MULTICOLUMN 0x0200L
#define LBS_WANTKEYBOARDINPUT 0x0400L
#define LBS_EXTENDEDSEL 0x0800L
#define LBS_DISABLENOSCROLL 0x1000L
#define LBS_NODATA 0x2000L
#define LBS_NOSEL 0x4000L
#define LBS_COMBOBOX 0x8000L

#define LBS_STANDARD (LBS_NOTIFY | LBS_SORT | WS_VSCROLL | WS_BORDER)
#endif

#define CB_OKAY 0
#define CB_ERR (-1)
#define CB_ERRSPACE (-2)

#define CBN_ERRSPACE (-1)
#define CBN_SELCHANGE 1
#define CBN_DBLCLK 2
#define CBN_SETFOCUS 3
#define CBN_KILLFOCUS 4
#define CBN_EDITCHANGE 5
#define CBN_EDITUPDATE 6
#define CBN_DROPDOWN 7
#define CBN_CLOSEUP 8
#define CBN_SELENDOK 9
#define CBN_SELENDCANCEL 10

#ifndef NOWINSTYLES

#define CBS_SIMPLE 0x0001L
#define CBS_DROPDOWN 0x0002L
#define CBS_DROPDOWNLIST 0x0003L
#define CBS_OWNERDRAWFIXED 0x0010L
#define CBS_OWNERDRAWVARIABLE 0x0020L
#define CBS_AUTOHSCROLL 0x0040L
#define CBS_OEMCONVERT 0x0080L
#define CBS_SORT 0x0100L
#define CBS_HASSTRINGS 0x0200L
#define CBS_NOINTEGRALHEIGHT 0x0400L
#define CBS_DISABLENOSCROLL 0x0800L
#define CBS_UPPERCASE 0x2000L
#define CBS_LOWERCASE 0x4000L
#endif

#ifndef NOWINMESSAGES
#define CB_GETEDITSEL 0x0140
#define CB_LIMITTEXT 0x0141
#define CB_SETEDITSEL 0x0142
#define CB_ADDSTRING 0x0143
#define CB_DELETESTRING 0x0144
#define CB_DIR 0x0145
#define CB_GETCOUNT 0x0146
#define CB_GETCURSEL 0x0147
#define CB_GETLBTEXT 0x0148
#define CB_GETLBTEXTLEN 0x0149
#define CB_INSERTSTRING 0x014A
#define CB_RESETCONTENT 0x014B
#define CB_FINDSTRING 0x014C
#define CB_SELECTSTRING 0x014D
#define CB_SETCURSEL 0x014E
#define CB_SHOWDROPDOWN 0x014F
#define CB_GETITEMDATA 0x0150
#define CB_SETITEMDATA 0x0151
#define CB_GETDROPPEDCONTROLRECT 0x0152
#define CB_SETITEMHEIGHT 0x0153
#define CB_GETITEMHEIGHT 0x0154
#define CB_SETEXTENDEDUI 0x0155
#define CB_GETEXTENDEDUI 0x0156
#define CB_GETDROPPEDSTATE 0x0157
#define CB_FINDSTRINGEXACT 0x0158
#define CB_SETLOCALE 0x0159
#define CB_GETLOCALE 0x015A
#define CB_GETTOPINDEX 0x015b
#define CB_SETTOPINDEX 0x015c
#define CB_GETHORIZONTALEXTENT 0x015d
#define CB_SETHORIZONTALEXTENT 0x015e
#define CB_GETDROPPEDWIDTH 0x015f
#define CB_SETDROPPEDWIDTH 0x0160
#define CB_INITSTORAGE 0x0161
#if (_WIN32_WCE >= 0x0400)
#define CB_MULTIPLEADDSTRING 0x0163
#endif
#define CB_GETCOMBOBOXINFO 0x0164
#define CB_MSGMAX 0x0165
#endif

#ifndef NOWINSTYLES

#define SBS_HORZ 0x0000L
#define SBS_VERT 0x0001L
#define SBS_TOPALIGN 0x0002L
#define SBS_LEFTALIGN 0x0002L
#define SBS_BOTTOMALIGN 0x0004L
#define SBS_RIGHTALIGN 0x0004L
#define SBS_SIZEBOXTOPLEFTALIGN 0x0002L
#define SBS_SIZEBOXBOTTOMRIGHTALIGN 0x0004L
#define SBS_SIZEBOX 0x0008L
#define SBS_SIZEGRIP 0x0010L
#endif

#ifndef NOWINMESSAGES
#define SBM_SETPOS 0x00E0
#define SBM_GETPOS 0x00E1
#define SBM_SETRANGE 0x00E2
#define SBM_SETRANGEREDRAW 0x00E6
#define SBM_GETRANGE 0x00E3
#define SBM_ENABLE_ARROWS 0x00E4
#define SBM_SETSCROLLINFO 0x00E9
#define SBM_GETSCROLLINFO 0x00EA
#define SBM_GETSCROLLBARINFO 0x00EB

#define SIF_RANGE 0x0001
#define SIF_PAGE 0x0002
#define SIF_POS 0x0004
#define SIF_DISABLENOSCROLL 0x0008
#define SIF_TRACKPOS 0x0010
#define SIF_ALL (SIF_RANGE | SIF_PAGE | SIF_POS | SIF_TRACKPOS)

typedef struct tagSCROLLINFO {
  UINT cbSize;
  UINT fMask;
  int nMin;
  int nMax;
  UINT nPage;
  int nPos;
  int nTrackPos;
} SCROLLINFO, *LPSCROLLINFO;
typedef SCROLLINFO CONST* LPCSCROLLINFO;

WINUSERAPI int WINAPI SetScrollInfo(HWND hwnd,
                                    int nBar,
                                    LPCSCROLLINFO lpsi,
                                    WINBOOL redraw);
WINUSERAPI WINBOOL WINAPI GetScrollInfo(HWND hwnd, int nBar, LPSCROLLINFO lpsi);
#endif
#endif

#ifndef NOMDI

#define MDIS_ALLCHILDSTYLES 0x0001

#define MDITILE_VERTICAL 0x0000
#define MDITILE_HORIZONTAL 0x0001
#define MDITILE_SKIPDISABLED 0x0002
#define MDITILE_ZORDER 0x0004

typedef struct tagMDICREATESTRUCTA {
  LPCSTR szClass;
  LPCSTR szTitle;
  HANDLE hOwner;
  int x;
  int y;
  int cx;
  int cy;
  DWORD style;
  LPARAM lParam;
} MDICREATESTRUCTA, *LPMDICREATESTRUCTA;

typedef struct tagMDICREATESTRUCTW {
  LPCWSTR szClass;
  LPCWSTR szTitle;
  HANDLE hOwner;
  int x;
  int y;
  int cx;
  int cy;
  DWORD style;
  LPARAM lParam;
} MDICREATESTRUCTW, *LPMDICREATESTRUCTW;

#ifdef UNICODE
typedef MDICREATESTRUCTW MDICREATESTRUCT;
typedef LPMDICREATESTRUCTW LPMDICREATESTRUCT;
#else
typedef MDICREATESTRUCTA MDICREATESTRUCT;
typedef LPMDICREATESTRUCTA LPMDICREATESTRUCT;
#endif

typedef struct tagCLIENTCREATESTRUCT {
  HANDLE hWindowMenu;
  UINT idFirstChild;
} CLIENTCREATESTRUCT, *LPCLIENTCREATESTRUCT;

#ifdef UNICODE
#define DefFrameProc DefFrameProcW
#define DefMDIChildProc DefMDIChildProcW
#define CreateMDIWindow CreateMDIWindowW
#else
#define DefFrameProc DefFrameProcA
#define DefMDIChildProc DefMDIChildProcA
#define CreateMDIWindow CreateMDIWindowA
#endif

WINUSERAPI LRESULT WINAPI DefFrameProcA(HWND hWnd,
                                        HWND hWndMDIClient,
                                        UINT uMsg,
                                        WPARAM wParam,
                                        LPARAM lParam);
WINUSERAPI LRESULT WINAPI DefFrameProcW(HWND hWnd,
                                        HWND hWndMDIClient,
                                        UINT uMsg,
                                        WPARAM wParam,
                                        LPARAM lParam);
WINUSERAPI LRESULT WINAPI DefMDIChildProcA(HWND hWnd,
                                           UINT uMsg,
                                           WPARAM wParam,
                                           LPARAM lParam);
WINUSERAPI LRESULT WINAPI DefMDIChildProcW(HWND hWnd,
                                           UINT uMsg,
                                           WPARAM wParam,
                                           LPARAM lParam);

#ifndef NOMSG
WINUSERAPI WINBOOL WINAPI TranslateMDISysAccel(HWND hWndClient, LPMSG lpMsg);
#endif

WINUSERAPI UINT WINAPI ArrangeIconicWindows(HWND hWnd);
WINUSERAPI HWND WINAPI CreateMDIWindowA(LPCSTR lpClassName,
                                        LPCSTR lpWindowName,
                                        DWORD dwStyle,
                                        int X,
                                        int Y,
                                        int nWidth,
                                        int nHeight,
                                        HWND hWndParent,
                                        HINSTANCE hInstance,
                                        LPARAM lParam);
WINUSERAPI HWND WINAPI CreateMDIWindowW(LPCWSTR lpClassName,
                                        LPCWSTR lpWindowName,
                                        DWORD dwStyle,
                                        int X,
                                        int Y,
                                        int nWidth,
                                        int nHeight,
                                        HWND hWndParent,
                                        HINSTANCE hInstance,
                                        LPARAM lParam);
WINUSERAPI WORD WINAPI TileWindows(HWND hwndParent,
                                   UINT wHow,
                                   CONST RECT* lpRect,
                                   UINT cKids,
                                   const HWND* lpKids);
WINUSERAPI WORD WINAPI CascadeWindows(HWND hwndParent,
                                      UINT wHow,
                                      CONST RECT* lpRect,
                                      UINT cKids,
                                      const HWND* lpKids);
#endif
#endif

#ifndef NOHELP

typedef DWORD HELPPOLY;
typedef struct tagMULTIKEYHELPA {
  DWORD mkSize;
  CHAR mkKeylist;
  CHAR szKeyphrase[1];
} MULTIKEYHELPA, *PMULTIKEYHELPA, *LPMULTIKEYHELPA;

typedef struct tagMULTIKEYHELPW {
  DWORD mkSize;
  WCHAR mkKeylist;
  WCHAR szKeyphrase[1];
} MULTIKEYHELPW, *PMULTIKEYHELPW, *LPMULTIKEYHELPW;

#ifdef UNICODE
typedef MULTIKEYHELPW MULTIKEYHELP;
typedef PMULTIKEYHELPW PMULTIKEYHELP;
typedef LPMULTIKEYHELPW LPMULTIKEYHELP;
#else
typedef MULTIKEYHELPA MULTIKEYHELP;
typedef PMULTIKEYHELPA PMULTIKEYHELP;
typedef LPMULTIKEYHELPA LPMULTIKEYHELP;
#endif

typedef struct tagHELPWININFOA {
  int wStructSize;
  int x;
  int y;
  int dx;
  int dy;
  int wMax;
  CHAR rgchMember[2];
} HELPWININFOA, *PHELPWININFOA, *LPHELPWININFOA;

typedef struct tagHELPWININFOW {
  int wStructSize;
  int x;
  int y;
  int dx;
  int dy;
  int wMax;
  WCHAR rgchMember[2];
} HELPWININFOW, *PHELPWININFOW, *LPHELPWININFOW;

#ifdef UNICODE
typedef HELPWININFOW HELPWININFO;
typedef PHELPWININFOW PHELPWININFO;
typedef LPHELPWININFOW LPHELPWININFO;
#else
typedef HELPWININFOA HELPWININFO;
typedef PHELPWININFOA PHELPWININFO;
typedef LPHELPWININFOA LPHELPWININFO;
#endif

#define HELP_CONTEXT 0x0001L
#define HELP_QUIT 0x0002L
#define HELP_INDEX 0x0003L
#define HELP_CONTENTS 0x0003L
#define HELP_HELPONHELP 0x0004L
#define HELP_SETINDEX 0x0005L
#define HELP_SETCONTENTS 0x0005L
#define HELP_CONTEXTPOPUP 0x0008L
#define HELP_FORCEFILE 0x0009L
#define HELP_KEY 0x0101L
#define HELP_COMMAND 0x0102L
#define HELP_PARTIALKEY 0x0105L
#define HELP_MULTIKEY 0x0201L
#define HELP_SETWINPOS 0x0203L
#define HELP_CONTEXTMENU 0x000a
#define HELP_FINDER 0x000b
#define HELP_WM_HELP 0x000c
#define HELP_SETPOPUP_POS 0x000d

#define HELP_TCARD 0x8000
#define HELP_TCARD_DATA 0x0010
#define HELP_TCARD_OTHER_CALLER 0x0011

#define IDH_NO_HELP 28440
#define IDH_MISSING_CONTEXT 28441
#define IDH_GENERIC_HELP_BUTTON 28442
#define IDH_OK 28443
#define IDH_CANCEL 28444
#define IDH_HELP 28445

#ifdef UNICODE
#define WinHelp WinHelpW
#else
#define WinHelp WinHelpA
#endif

WINUSERAPI WINBOOL WINAPI WinHelpA(HWND hWndMain,
                                   LPCSTR lpszHelp,
                                   UINT uCommand,
                                   ULONG_PTR dwData);
WINUSERAPI WINBOOL WINAPI WinHelpW(HWND hWndMain,
                                   LPCWSTR lpszHelp,
                                   UINT uCommand,
                                   ULONG_PTR dwData);
#endif

#define GR_GDIOBJECTS 0
#define GR_USEROBJECTS 1

WINUSERAPI DWORD WINAPI GetGuiResources(HANDLE hProcess, DWORD uiFlags);

#ifndef NOSYSPARAMSINFO

#define SPI_GETBEEP 0x0001
#define SPI_SETBEEP 0x0002
#define SPI_GETMOUSE 0x0003
#define SPI_SETMOUSE 0x0004
#define SPI_GETBORDER 0x0005
#define SPI_SETBORDER 0x0006
#define SPI_GETKEYBOARDSPEED 0x000A
#define SPI_SETKEYBOARDSPEED 0x000B
#define SPI_LANGDRIVER 0x000C
#define SPI_ICONHORIZONTALSPACING 0x000D
#define SPI_GETSCREENSAVETIMEOUT 0x000E
#define SPI_SETSCREENSAVETIMEOUT 0x000F
#define SPI_GETSCREENSAVEACTIVE 0x0010
#define SPI_SETSCREENSAVEACTIVE 0x0011
#define SPI_GETGRIDGRANULARITY 0x0012
#define SPI_SETGRIDGRANULARITY 0x0013
#define SPI_SETDESKWALLPAPER 0x0014
#define SPI_SETDESKPATTERN 0x0015
#define SPI_GETKEYBOARDDELAY 0x0016
#define SPI_SETKEYBOARDDELAY 0x0017
#define SPI_ICONVERTICALSPACING 0x0018
#define SPI_GETICONTITLEWRAP 0x0019
#define SPI_SETICONTITLEWRAP 0x001A
#define SPI_GETMENUDROPALIGNMENT 0x001B
#define SPI_SETMENUDROPALIGNMENT 0x001C
#define SPI_SETDOUBLECLKWIDTH 0x001D
#define SPI_SETDOUBLECLKHEIGHT 0x001E
#define SPI_GETICONTITLELOGFONT 0x001F
#define SPI_SETDOUBLECLICKTIME 0x0020
#define SPI_SETMOUSEBUTTONSWAP 0x0021
#define SPI_SETICONTITLELOGFONT 0x0022
#define SPI_GETFASTTASKSWITCH 0x0023
#define SPI_SETFASTTASKSWITCH 0x0024
#define SPI_SETDRAGFULLWINDOWS 0x0025
#define SPI_GETDRAGFULLWINDOWS 0x0026
#define SPI_GETNONCLIENTMETRICS 0x0029
#define SPI_SETNONCLIENTMETRICS 0x002A
#define SPI_GETMINIMIZEDMETRICS 0x002B
#define SPI_SETMINIMIZEDMETRICS 0x002C
#define SPI_GETICONMETRICS 0x002D
#define SPI_SETICONMETRICS 0x002E
#define SPI_SETWORKAREA 0x002F
#define SPI_GETWORKAREA 0x0030
#define SPI_SETPENWINDOWS 0x0031

#define SPI_GETHIGHCONTRAST 0x0042
#define SPI_SETHIGHCONTRAST 0x0043
#define SPI_GETKEYBOARDPREF 0x0044
#define SPI_SETKEYBOARDPREF 0x0045
#define SPI_GETSCREENREADER 0x0046
#define SPI_SETSCREENREADER 0x0047
#define SPI_GETANIMATION 0x0048
#define SPI_SETANIMATION 0x0049
#define SPI_GETFONTSMOOTHING 0x004A
#define SPI_SETFONTSMOOTHING 0x004B
#define SPI_SETDRAGWIDTH 0x004C
#define SPI_SETDRAGHEIGHT 0x004D
#define SPI_SETHANDHELD 0x004E
#define SPI_GETLOWPOWERTIMEOUT 0x004F
#define SPI_GETPOWEROFFTIMEOUT 0x0050
#define SPI_SETLOWPOWERTIMEOUT 0x0051
#define SPI_SETPOWEROFFTIMEOUT 0x0052
#define SPI_GETLOWPOWERACTIVE 0x0053
#define SPI_GETPOWEROFFACTIVE 0x0054
#define SPI_SETLOWPOWERACTIVE 0x0055
#define SPI_SETPOWEROFFACTIVE 0x0056
#define SPI_SETCURSORS 0x0057
#define SPI_SETICONS 0x0058
#define SPI_GETDEFAULTINPUTLANG 0x0059
#define SPI_SETDEFAULTINPUTLANG 0x005A
#define SPI_SETLANGTOGGLE 0x005B
#define SPI_GETWINDOWSEXTENSION 0x005C
#define SPI_SETMOUSETRAILS 0x005D
#define SPI_GETMOUSETRAILS 0x005E
#define SPI_SETSCREENSAVERRUNNING 0x0061
#define SPI_SCREENSAVERRUNNING SPI_SETSCREENSAVERRUNNING
#define SPI_GETFILTERKEYS 0x0032
#define SPI_SETFILTERKEYS 0x0033
#define SPI_GETTOGGLEKEYS 0x0034
#define SPI_SETTOGGLEKEYS 0x0035
#define SPI_GETMOUSEKEYS 0x0036
#define SPI_SETMOUSEKEYS 0x0037
#define SPI_GETSHOWSOUNDS 0x0038
#define SPI_SETSHOWSOUNDS 0x0039
#define SPI_GETSTICKYKEYS 0x003A
#define SPI_SETSTICKYKEYS 0x003B
#define SPI_GETACCESSTIMEOUT 0x003C
#define SPI_SETACCESSTIMEOUT 0x003D
#define SPI_GETSERIALKEYS 0x003E
#define SPI_SETSERIALKEYS 0x003F
#define SPI_GETSOUNDSENTRY 0x0040
#define SPI_SETSOUNDSENTRY 0x0041
#define SPI_GETSNAPTODEFBUTTON 0x005F
#define SPI_SETSNAPTODEFBUTTON 0x0060
#define SPI_GETMOUSEHOVERWIDTH 0x0062
#define SPI_SETMOUSEHOVERWIDTH 0x0063
#define SPI_GETMOUSEHOVERHEIGHT 0x0064
#define SPI_SETMOUSEHOVERHEIGHT 0x0065
#define SPI_GETMOUSEHOVERTIME 0x0066
#define SPI_SETMOUSEHOVERTIME 0x0067
#define SPI_GETWHEELSCROLLLINES 0x0068
#define SPI_SETWHEELSCROLLLINES 0x0069
#define SPI_GETMENUSHOWDELAY 0x006A
#define SPI_SETMENUSHOWDELAY 0x006B
#define SPI_GETSHOWIMEUI 0x006E
#define SPI_SETSHOWIMEUI 0x006F
#define SPI_GETMOUSESPEED 0x0070
#define SPI_SETMOUSESPEED 0x0071
#define SPI_GETSCREENSAVERRUNNING 0x0072
#define SPI_GETDESKWALLPAPER 0x0073

#define SPI_GETACTIVEWINDOWTRACKING 0x1000
#define SPI_SETACTIVEWINDOWTRACKING 0x1001
#define SPI_GETMENUANIMATION 0x1002
#define SPI_SETMENUANIMATION 0x1003
#define SPI_GETCOMBOBOXANIMATION 0x1004
#define SPI_SETCOMBOBOXANIMATION 0x1005
#define SPI_GETLISTBOXSMOOTHSCROLLING 0x1006
#define SPI_SETLISTBOXSMOOTHSCROLLING 0x1007
#define SPI_GETGRADIENTCAPTIONS 0x1008
#define SPI_SETGRADIENTCAPTIONS 0x1009
#define SPI_GETKEYBOARDCUES 0x100A
#define SPI_SETKEYBOARDCUES 0x100B
#define SPI_GETMENUUNDERLINES SPI_GETKEYBOARDCUES
#define SPI_SETMENUUNDERLINES SPI_SETKEYBOARDCUES
#define SPI_GETACTIVEWNDTRKZORDER 0x100C
#define SPI_SETACTIVEWNDTRKZORDER 0x100D
#define SPI_GETHOTTRACKING 0x100E
#define SPI_SETHOTTRACKING 0x100F
#define SPI_GETMENUFADE 0x1012
#define SPI_SETMENUFADE 0x1013
#define SPI_GETSELECTIONFADE 0x1014
#define SPI_SETSELECTIONFADE 0x1015
#define SPI_GETTOOLTIPANIMATION 0x1016
#define SPI_SETTOOLTIPANIMATION 0x1017
#define SPI_GETTOOLTIPFADE 0x1018
#define SPI_SETTOOLTIPFADE 0x1019
#define SPI_GETCURSORSHADOW 0x101A
#define SPI_SETCURSORSHADOW 0x101B
#define SPI_GETMOUSESONAR 0x101C
#define SPI_SETMOUSESONAR 0x101D
#define SPI_GETMOUSECLICKLOCK 0x101E
#define SPI_SETMOUSECLICKLOCK 0x101F
#define SPI_GETMOUSEVANISH 0x1020
#define SPI_SETMOUSEVANISH 0x1021
#define SPI_GETFLATMENU 0x1022
#define SPI_SETFLATMENU 0x1023
#define SPI_GETDROPSHADOW 0x1024
#define SPI_SETDROPSHADOW 0x1025
#define SPI_GETBLOCKSENDINPUTRESETS 0x1026
#define SPI_SETBLOCKSENDINPUTRESETS 0x1027
#define SPI_GETUIEFFECTS 0x103E
#define SPI_SETUIEFFECTS 0x103F
#define SPI_GETFOREGROUNDLOCKTIMEOUT 0x2000
#define SPI_SETFOREGROUNDLOCKTIMEOUT 0x2001
#define SPI_GETACTIVEWNDTRKTIMEOUT 0x2002
#define SPI_SETACTIVEWNDTRKTIMEOUT 0x2003
#define SPI_GETFOREGROUNDFLASHCOUNT 0x2004
#define SPI_SETFOREGROUNDFLASHCOUNT 0x2005
#define SPI_GETCARETWIDTH 0x2006
#define SPI_SETCARETWIDTH 0x2007
#define SPI_GETMOUSECLICKLOCKTIME 0x2008
#define SPI_SETMOUSECLICKLOCKTIME 0x2009
#define SPI_GETFONTSMOOTHINGTYPE 0x200A
#define SPI_SETFONTSMOOTHINGTYPE 0x200B

#define FE_FONTSMOOTHINGSTANDARD 0x0001
#define FE_FONTSMOOTHINGCLEARTYPE 0x0002
#define FE_FONTSMOOTHINGDOCKING 0x8000

#define SPI_GETFONTSMOOTHINGCONTRAST 0x200C
#define SPI_SETFONTSMOOTHINGCONTRAST 0x200D
#define SPI_GETFOCUSBORDERWIDTH 0x200E
#define SPI_SETFOCUSBORDERWIDTH 0x200F
#define SPI_GETFOCUSBORDERHEIGHT 0x2010
#define SPI_SETFOCUSBORDERHEIGHT 0x2011
#define SPI_GETFONTSMOOTHINGORIENTATION 0x2012
#define SPI_SETFONTSMOOTHINGORIENTATION 0x2013

#define FE_FONTSMOOTHINGORIENTATIONBGR 0x0000
#define FE_FONTSMOOTHINGORIENTATIONRGB 0x0001

#define SPIF_UPDATEINIFILE 0x0001
#define SPIF_SENDWININICHANGE 0x0002
#define SPIF_SENDCHANGE SPIF_SENDWININICHANGE

#define METRICS_USEDEFAULT -1
#ifdef _WINGDI_
#ifndef NOGDI
typedef struct tagNONCLIENTMETRICSA {
  UINT cbSize;
  int iBorderWidth;
  int iScrollWidth;
  int iScrollHeight;
  int iCaptionWidth;
  int iCaptionHeight;
  LOGFONTA lfCaptionFont;
  int iSmCaptionWidth;
  int iSmCaptionHeight;
  LOGFONTA lfSmCaptionFont;
  int iMenuWidth;
  int iMenuHeight;
  LOGFONTA lfMenuFont;
  LOGFONTA lfStatusFont;
  LOGFONTA lfMessageFont;
} NONCLIENTMETRICSA, *PNONCLIENTMETRICSA, *LPNONCLIENTMETRICSA;

typedef struct tagNONCLIENTMETRICSW {
  UINT cbSize;
  int iBorderWidth;
  int iScrollWidth;
  int iScrollHeight;
  int iCaptionWidth;
  int iCaptionHeight;
  LOGFONTW lfCaptionFont;
  int iSmCaptionWidth;
  int iSmCaptionHeight;
  LOGFONTW lfSmCaptionFont;
  int iMenuWidth;
  int iMenuHeight;
  LOGFONTW lfMenuFont;
  LOGFONTW lfStatusFont;
  LOGFONTW lfMessageFont;
} NONCLIENTMETRICSW, *PNONCLIENTMETRICSW, *LPNONCLIENTMETRICSW;

#ifdef UNICODE
typedef NONCLIENTMETRICSW NONCLIENTMETRICS;
typedef PNONCLIENTMETRICSW PNONCLIENTMETRICS;
typedef LPNONCLIENTMETRICSW LPNONCLIENTMETRICS;
#else
typedef NONCLIENTMETRICSA NONCLIENTMETRICS;
typedef PNONCLIENTMETRICSA PNONCLIENTMETRICS;
typedef LPNONCLIENTMETRICSA LPNONCLIENTMETRICS;
#endif
#endif
#endif

#define ARW_BOTTOMLEFT 0x0000L
#define ARW_BOTTOMRIGHT 0x0001L
#define ARW_TOPLEFT 0x0002L
#define ARW_TOPRIGHT 0x0003L
#define ARW_STARTMASK 0x0003L
#define ARW_STARTRIGHT 0x0001L
#define ARW_STARTTOP 0x0002L

#define ARW_LEFT 0x0000L
#define ARW_RIGHT 0x0000L
#define ARW_UP 0x0004L
#define ARW_DOWN 0x0004L
#define ARW_HIDE 0x0008L

typedef struct tagMINIMIZEDMETRICS {
  UINT cbSize;
  int iWidth;
  int iHorzGap;
  int iVertGap;
  int iArrange;
} MINIMIZEDMETRICS, *PMINIMIZEDMETRICS, *LPMINIMIZEDMETRICS;

#ifdef _WINGDI_
#ifndef NOGDI
typedef struct tagICONMETRICSA {
  UINT cbSize;
  int iHorzSpacing;
  int iVertSpacing;
  int iTitleWrap;
  LOGFONTA lfFont;
} ICONMETRICSA, *PICONMETRICSA, *LPICONMETRICSA;

typedef struct tagICONMETRICSW {
  UINT cbSize;
  int iHorzSpacing;
  int iVertSpacing;
  int iTitleWrap;
  LOGFONTW lfFont;
} ICONMETRICSW, *PICONMETRICSW, *LPICONMETRICSW;

#ifdef UNICODE
typedef ICONMETRICSW ICONMETRICS;
typedef PICONMETRICSW PICONMETRICS;
typedef LPICONMETRICSW LPICONMETRICS;
#else
typedef ICONMETRICSA ICONMETRICS;
typedef PICONMETRICSA PICONMETRICS;
typedef LPICONMETRICSA LPICONMETRICS;
#endif
#endif
#endif

typedef struct tagANIMATIONINFO {
  UINT cbSize;
  int iMinAnimate;
} ANIMATIONINFO, *LPANIMATIONINFO;

typedef struct tagSERIALKEYSA {
  UINT cbSize;
  DWORD dwFlags;
  LPSTR lpszActivePort;
  LPSTR lpszPort;
  UINT iBaudRate;
  UINT iPortState;
  UINT iActive;
} SERIALKEYSA, *LPSERIALKEYSA;

typedef struct tagSERIALKEYSW {
  UINT cbSize;
  DWORD dwFlags;
  LPWSTR lpszActivePort;
  LPWSTR lpszPort;
  UINT iBaudRate;
  UINT iPortState;
  UINT iActive;
} SERIALKEYSW, *LPSERIALKEYSW;

#ifdef UNICODE
typedef SERIALKEYSW SERIALKEYS;
typedef LPSERIALKEYSW LPSERIALKEYS;
#else
typedef SERIALKEYSA SERIALKEYS;
typedef LPSERIALKEYSA LPSERIALKEYS;
#endif

#define SERKF_SERIALKEYSON 0x00000001
#define SERKF_AVAILABLE 0x00000002
#define SERKF_INDICATOR 0x00000004

typedef struct tagHIGHCONTRASTA {
  UINT cbSize;
  DWORD dwFlags;
  LPSTR lpszDefaultScheme;
} HIGHCONTRASTA, *LPHIGHCONTRASTA;

typedef struct tagHIGHCONTRASTW {
  UINT cbSize;
  DWORD dwFlags;
  LPWSTR lpszDefaultScheme;
} HIGHCONTRASTW, *LPHIGHCONTRASTW;

#ifdef UNICODE
typedef HIGHCONTRASTW HIGHCONTRAST;
typedef LPHIGHCONTRASTW LPHIGHCONTRAST;
#else
typedef HIGHCONTRASTA HIGHCONTRAST;
typedef LPHIGHCONTRASTA LPHIGHCONTRAST;
#endif

#define HCF_HIGHCONTRASTON 0x00000001
#define HCF_AVAILABLE 0x00000002
#define HCF_HOTKEYACTIVE 0x00000004
#define HCF_CONFIRMHOTKEY 0x00000008
#define HCF_HOTKEYSOUND 0x00000010
#define HCF_INDICATOR 0x00000020
#define HCF_HOTKEYAVAILABLE 0x00000040
#define HCF_LOGONDESKTOP 0x00000100
#define HCF_DEFAULTDESKTOP 0x00000200

#define CDS_UPDATEREGISTRY 0x00000001
#define CDS_TEST 0x00000002
#define CDS_FULLSCREEN 0x00000004
#define CDS_GLOBAL 0x00000008
#define CDS_SET_PRIMARY 0x00000010
#define CDS_VIDEOPARAMETERS 0x00000020
#define CDS_RESET 0x40000000
#define CDS_NORESET 0x10000000

// gr #include <tvout.h>

#define DISP_CHANGE_SUCCESSFUL 0
#define DISP_CHANGE_RESTART 1
#define DISP_CHANGE_FAILED -1
#define DISP_CHANGE_BADMODE -2
#define DISP_CHANGE_NOTUPDATED -3
#define DISP_CHANGE_BADFLAGS -4
#define DISP_CHANGE_BADPARAM -5
#define DISP_CHANGE_BADDUALVIEW -6

#ifdef _WINGDI_
#ifndef NOGDI

#ifdef UNICODE
#define ChangeDisplaySettings ChangeDisplaySettingsW
#define ChangeDisplaySettingsEx ChangeDisplaySettingsExW
#define EnumDisplaySettings EnumDisplaySettingsW
#define EnumDisplaySettingsEx EnumDisplaySettingsExW
#define EnumDisplayDevices EnumDisplayDevicesW
#else
#define ChangeDisplaySettings ChangeDisplaySettingsA
#define ChangeDisplaySettingsEx ChangeDisplaySettingsExA
#define EnumDisplaySettings EnumDisplaySettingsA
#define EnumDisplaySettingsEx EnumDisplaySettingsExA
#define EnumDisplayDevices EnumDisplayDevicesA
#endif

WINUSERAPI LONG WINAPI ChangeDisplaySettingsA(LPDEVMODEA lpDevMode,
                                              DWORD dwFlags);
WINUSERAPI LONG WINAPI ChangeDisplaySettingsW(LPDEVMODEW lpDevMode,
                                              DWORD dwFlags);
WINUSERAPI LONG WINAPI ChangeDisplaySettingsExA(LPCSTR lpszDeviceName,
                                                LPDEVMODEA lpDevMode,
                                                HWND hwnd,
                                                DWORD dwflags,
                                                LPVOID lParam);
WINUSERAPI LONG WINAPI ChangeDisplaySettingsExW(LPCWSTR lpszDeviceName,
                                                LPDEVMODEW lpDevMode,
                                                HWND hwnd,
                                                DWORD dwflags,
                                                LPVOID lParam);

#define ENUM_CURRENT_SETTINGS ((DWORD)-1)
#define ENUM_REGISTRY_SETTINGS ((DWORD)-2)

WINUSERAPI WINBOOL WINAPI EnumDisplaySettingsA(LPCSTR lpszDeviceName,
                                               DWORD iModeNum,
                                               LPDEVMODEA lpDevMode);
WINUSERAPI WINBOOL WINAPI EnumDisplaySettingsW(LPCWSTR lpszDeviceName,
                                               DWORD iModeNum,
                                               LPDEVMODEW lpDevMode);
WINUSERAPI WINBOOL WINAPI EnumDisplaySettingsExA(LPCSTR lpszDeviceName,
                                                 DWORD iModeNum,
                                                 LPDEVMODEA lpDevMode,
                                                 DWORD dwFlags);
WINUSERAPI WINBOOL WINAPI EnumDisplaySettingsExW(LPCWSTR lpszDeviceName,
                                                 DWORD iModeNum,
                                                 LPDEVMODEW lpDevMode,
                                                 DWORD dwFlags);

#define EDS_RAWMODE 0x00000002

WINUSERAPI WINBOOL WINAPI EnumDisplayDevicesA(LPCSTR lpDevice,
                                              DWORD iDevNum,
                                              PDISPLAY_DEVICEA lpDisplayDevice,
                                              DWORD dwFlags);
WINUSERAPI WINBOOL WINAPI EnumDisplayDevicesW(LPCWSTR lpDevice,
                                              DWORD iDevNum,
                                              PDISPLAY_DEVICEW lpDisplayDevice,
                                              DWORD dwFlags);
#endif
#endif

#ifdef UNICODE
#define SystemParametersInfo SystemParametersInfoW
#else
#define SystemParametersInfo SystemParametersInfoA
#endif

WINUSERAPI WINBOOL WINAPI SystemParametersInfoA(UINT uiAction,
                                                UINT uiParam,
                                                PVOID pvParam,
                                                UINT fWinIni);
WINUSERAPI WINBOOL WINAPI SystemParametersInfoW(UINT uiAction,
                                                UINT uiParam,
                                                PVOID pvParam,
                                                UINT fWinIni);
#endif

typedef struct tagFILTERKEYS {
  UINT cbSize;
  DWORD dwFlags;
  DWORD iWaitMSec;
  DWORD iDelayMSec;
  DWORD iRepeatMSec;
  DWORD iBounceMSec;
} FILTERKEYS, *LPFILTERKEYS;

#define FKF_FILTERKEYSON 0x00000001
#define FKF_AVAILABLE 0x00000002
#define FKF_HOTKEYACTIVE 0x00000004
#define FKF_CONFIRMHOTKEY 0x00000008
#define FKF_HOTKEYSOUND 0x00000010
#define FKF_INDICATOR 0x00000020
#define FKF_CLICKON 0x00000040

typedef struct tagSTICKYKEYS {
  UINT cbSize;
  DWORD dwFlags;
} STICKYKEYS, *LPSTICKYKEYS;

#define SKF_STICKYKEYSON 0x00000001
#define SKF_AVAILABLE 0x00000002
#define SKF_HOTKEYACTIVE 0x00000004
#define SKF_CONFIRMHOTKEY 0x00000008
#define SKF_HOTKEYSOUND 0x00000010
#define SKF_INDICATOR 0x00000020
#define SKF_AUDIBLEFEEDBACK 0x00000040
#define SKF_TRISTATE 0x00000080
#define SKF_TWOKEYSOFF 0x00000100
#define SKF_LALTLATCHED 0x10000000
#define SKF_LCTLLATCHED 0x04000000
#define SKF_LSHIFTLATCHED 0x01000000
#define SKF_RALTLATCHED 0x20000000
#define SKF_RCTLLATCHED 0x08000000
#define SKF_RSHIFTLATCHED 0x02000000
#define SKF_LWINLATCHED 0x40000000
#define SKF_RWINLATCHED 0x80000000
#define SKF_LALTLOCKED 0x00100000
#define SKF_LCTLLOCKED 0x00040000
#define SKF_LSHIFTLOCKED 0x00010000
#define SKF_RALTLOCKED 0x00200000
#define SKF_RCTLLOCKED 0x00080000
#define SKF_RSHIFTLOCKED 0x00020000
#define SKF_LWINLOCKED 0x00400000
#define SKF_RWINLOCKED 0x00800000

typedef struct tagMOUSEKEYS {
  UINT cbSize;
  DWORD dwFlags;
  DWORD iMaxSpeed;
  DWORD iTimeToMaxSpeed;
  DWORD iCtrlSpeed;
  DWORD dwReserved1;
  DWORD dwReserved2;
} MOUSEKEYS, *LPMOUSEKEYS;

#define MKF_MOUSEKEYSON 0x00000001
#define MKF_AVAILABLE 0x00000002
#define MKF_HOTKEYACTIVE 0x00000004
#define MKF_CONFIRMHOTKEY 0x00000008
#define MKF_HOTKEYSOUND 0x00000010
#define MKF_INDICATOR 0x00000020
#define MKF_MODIFIERS 0x00000040
#define MKF_REPLACENUMBERS 0x00000080
#define MKF_LEFTBUTTONSEL 0x10000000
#define MKF_RIGHTBUTTONSEL 0x20000000
#define MKF_LEFTBUTTONDOWN 0x01000000
#define MKF_RIGHTBUTTONDOWN 0x02000000
#define MKF_MOUSEMODE 0x80000000

typedef struct tagACCESSTIMEOUT {
  UINT cbSize;
  DWORD dwFlags;
  DWORD iTimeOutMSec;
} ACCESSTIMEOUT, *LPACCESSTIMEOUT;

#define ATF_TIMEOUTON 0x00000001
#define ATF_ONOFFFEEDBACK 0x00000002

#define SSGF_NONE 0
#define SSGF_DISPLAY 3

#define SSTF_NONE 0
#define SSTF_CHARS 1
#define SSTF_BORDER 2
#define SSTF_DISPLAY 3

#define SSWF_NONE 0
#define SSWF_TITLE 1
#define SSWF_WINDOW 2
#define SSWF_DISPLAY 3
#define SSWF_CUSTOM 4

typedef struct tagSOUNDSENTRYA {
  UINT cbSize;
  DWORD dwFlags;
  DWORD iFSTextEffect;
  DWORD iFSTextEffectMSec;
  DWORD iFSTextEffectColorBits;
  DWORD iFSGrafEffect;
  DWORD iFSGrafEffectMSec;
  DWORD iFSGrafEffectColor;
  DWORD iWindowsEffect;
  DWORD iWindowsEffectMSec;
  LPSTR lpszWindowsEffectDLL;
  DWORD iWindowsEffectOrdinal;
} SOUNDSENTRYA, *LPSOUNDSENTRYA;

typedef struct tagSOUNDSENTRYW {
  UINT cbSize;
  DWORD dwFlags;
  DWORD iFSTextEffect;
  DWORD iFSTextEffectMSec;
  DWORD iFSTextEffectColorBits;
  DWORD iFSGrafEffect;
  DWORD iFSGrafEffectMSec;
  DWORD iFSGrafEffectColor;
  DWORD iWindowsEffect;
  DWORD iWindowsEffectMSec;
  LPWSTR lpszWindowsEffectDLL;
  DWORD iWindowsEffectOrdinal;
} SOUNDSENTRYW, *LPSOUNDSENTRYW;

#ifdef UNICODE
typedef SOUNDSENTRYW SOUNDSENTRY;
typedef LPSOUNDSENTRYW LPSOUNDSENTRY;
#else
typedef SOUNDSENTRYA SOUNDSENTRY;
typedef LPSOUNDSENTRYA LPSOUNDSENTRY;
#endif

#define SSF_SOUNDSENTRYON 0x00000001
#define SSF_AVAILABLE 0x00000002
#define SSF_INDICATOR 0x00000004

typedef struct tagTOGGLEKEYS {
  UINT cbSize;
  DWORD dwFlags;
} TOGGLEKEYS, *LPTOGGLEKEYS;

#define TKF_TOGGLEKEYSON 0x00000001
#define TKF_AVAILABLE 0x00000002
#define TKF_HOTKEYACTIVE 0x00000004
#define TKF_CONFIRMHOTKEY 0x00000008
#define TKF_HOTKEYSOUND 0x00000010
#define TKF_INDICATOR 0x00000020

WINUSERAPI VOID WINAPI SetDebugErrorLevel(DWORD dwLevel);

#define SLE_ERROR 0x00000001
#define SLE_MINORERROR 0x00000002
#define SLE_WARNING 0x00000003

WINUSERAPI VOID WINAPI SetLastErrorEx(DWORD dwErrCode, DWORD dwType);
WINUSERAPI int WINAPI InternalGetWindowText(HWND hWnd,
                                            LPWSTR pString,
                                            int cchMaxCount);

#ifdef WINNT
WINUSERAPI WINBOOL WINAPI EndTask(HWND hWnd, WINBOOL fShutDown, WINBOOL fForce);
#endif

#define MONITOR_DEFAULTTONULL 0x00000000
#define MONITOR_DEFAULTTOPRIMARY 0x00000001
#define MONITOR_DEFAULTTONEAREST 0x00000002

WINUSERAPI HMONITOR WINAPI MonitorFromPoint(POINT pt, DWORD dwFlags);
WINUSERAPI HMONITOR WINAPI MonitorFromRect(LPCRECT lprc, DWORD dwFlags);
WINUSERAPI HMONITOR WINAPI MonitorFromWindow(HWND hwnd, DWORD dwFlags);

#define MONITORINFOF_PRIMARY 0x00000001

#ifndef CCHDEVICENAME
#define CCHDEVICENAME 32
#endif

typedef struct tagMONITORINFO {
  DWORD cbSize;
  RECT rcMonitor;
  RECT rcWork;
  DWORD dwFlags;
} MONITORINFO, *LPMONITORINFO;

#ifdef __cplusplus
typedef struct tagMONITORINFOEXA : public tagMONITORINFO {
  CHAR szDevice[CCHDEVICENAME];
} MONITORINFOEXA, *LPMONITORINFOEXA;

typedef struct tagMONITORINFOEXW : public tagMONITORINFO {
  WCHAR szDevice[CCHDEVICENAME];
} MONITORINFOEXW, *LPMONITORINFOEXW;

#ifdef UNICODE
typedef MONITORINFOEXW MONITORINFOEX;
typedef LPMONITORINFOEXW LPMONITORINFOEX;
#else
typedef MONITORINFOEXA MONITORINFOEX;
typedef LPMONITORINFOEXA LPMONITORINFOEX;
#endif
#else
typedef struct tagMONITORINFOEXA {
  MONITORINFO mi;
  CHAR szDevice[CCHDEVICENAME];
} MONITORINFOEXA, *LPMONITORINFOEXA;

typedef struct tagMONITORINFOEXW {
  MONITORINFO mi;
  WCHAR szDevice[CCHDEVICENAME];
} MONITORINFOEXW, *LPMONITORINFOEXW;
#ifdef UNICODE
typedef MONITORINFOEXW MONITORINFOEX;
typedef LPMONITORINFOEXW LPMONITORINFOEX;
#else
typedef MONITORINFOEXA MONITORINFOEX;
typedef LPMONITORINFOEXA LPMONITORINFOEX;
#endif
#endif

#ifdef UNICODE
#define GetMonitorInfo GetMonitorInfoW
#else
#define GetMonitorInfo GetMonitorInfoA
#endif

WINUSERAPI WINBOOL WINAPI GetMonitorInfoA(HMONITOR hMonitor,
                                          LPMONITORINFO lpmi);
WINUSERAPI WINBOOL WINAPI GetMonitorInfoW(HMONITOR hMonitor,
                                          LPMONITORINFO lpmi);

typedef WINBOOL(CALLBACK* MONITORENUMPROC)(HMONITOR, HDC, LPRECT, LPARAM);

WINUSERAPI WINBOOL WINAPI EnumDisplayMonitors(HDC hdc,
                                              LPCRECT lprcClip,
                                              MONITORENUMPROC lpfnEnum,
                                              LPARAM dwData);

#ifndef NOWINABLE
WINUSERAPI VOID WINAPI NotifyWinEvent(DWORD event,
                                      HWND hwnd,
                                      LONG idObject,
                                      LONG idChild);

typedef VOID(CALLBACK* WINEVENTPROC)(HWINEVENTHOOK hWinEventHook,
                                     DWORD event,
                                     HWND hwnd,
                                     LONG idObject,
                                     LONG idChild,
                                     DWORD idEventThread,
                                     DWORD dwmsEventTime);

WINUSERAPI HWINEVENTHOOK WINAPI SetWinEventHook(DWORD eventMin,
                                                DWORD eventMax,
                                                HMODULE hmodWinEventProc,
                                                WINEVENTPROC pfnWinEventProc,
                                                DWORD idProcess,
                                                DWORD idThread,
                                                DWORD dwFlags);
WINUSERAPI WINBOOL WINAPI IsWinEventHookInstalled(DWORD event);

#define WINEVENT_OUTOFCONTEXT 0x0000
#define WINEVENT_SKIPOWNTHREAD 0x0001
#define WINEVENT_SKIPOWNPROCESS 0x0002
#define WINEVENT_INCONTEXT 0x0004

WINUSERAPI WINBOOL WINAPI UnhookWinEvent(HWINEVENTHOOK hWinEventHook);

#define CHILDID_SELF 0
#define INDEXID_OBJECT 0
#define INDEXID_CONTAINER 0

#define OBJID_WINDOW ((LONG)0x00000000)
#define OBJID_SYSMENU ((LONG)0xFFFFFFFF)
#define OBJID_TITLEBAR ((LONG)0xFFFFFFFE)
#define OBJID_MENU ((LONG)0xFFFFFFFD)
#define OBJID_CLIENT ((LONG)0xFFFFFFFC)
#define OBJID_VSCROLL ((LONG)0xFFFFFFFB)
#define OBJID_HSCROLL ((LONG)0xFFFFFFFA)
#define OBJID_SIZEGRIP ((LONG)0xFFFFFFF9)
#define OBJID_CARET ((LONG)0xFFFFFFF8)
#define OBJID_CURSOR ((LONG)0xFFFFFFF7)
#define OBJID_ALERT ((LONG)0xFFFFFFF6)
#define OBJID_SOUND ((LONG)0xFFFFFFF5)
#define OBJID_QUERYCLASSNAMEIDX ((LONG)0xFFFFFFF4)
#define OBJID_NATIVEOM ((LONG)0xFFFFFFF0)

#define EVENT_MIN 0x00000001
#define EVENT_MAX 0x7FFFFFFF

#define EVENT_SYSTEM_SOUND 0x0001
#define EVENT_SYSTEM_ALERT 0x0002
#define EVENT_SYSTEM_FOREGROUND 0x0003
#define EVENT_SYSTEM_MENUSTART 0x0004
#define EVENT_SYSTEM_MENUEND 0x0005
#define EVENT_SYSTEM_MENUPOPUPSTART 0x0006
#define EVENT_SYSTEM_MENUPOPUPEND 0x0007
#define EVENT_SYSTEM_CAPTURESTART 0x0008
#define EVENT_SYSTEM_CAPTUREEND 0x0009
#define EVENT_SYSTEM_MOVESIZESTART 0x000A
#define EVENT_SYSTEM_MOVESIZEEND 0x000B
#define EVENT_SYSTEM_CONTEXTHELPSTART 0x000C
#define EVENT_SYSTEM_CONTEXTHELPEND 0x000D
#define EVENT_SYSTEM_DRAGDROPSTART 0x000E
#define EVENT_SYSTEM_DRAGDROPEND 0x000F
#define EVENT_SYSTEM_DIALOGSTART 0x0010
#define EVENT_SYSTEM_DIALOGEND 0x0011
#define EVENT_SYSTEM_SCROLLINGSTART 0x0012
#define EVENT_SYSTEM_SCROLLINGEND 0x0013
#define EVENT_SYSTEM_SWITCHSTART 0x0014
#define EVENT_SYSTEM_SWITCHEND 0x0015
#define EVENT_SYSTEM_MINIMIZESTART 0x0016
#define EVENT_SYSTEM_MINIMIZEEND 0x0017

#define EVENT_CONSOLE_CARET 0x4001
#define EVENT_CONSOLE_UPDATE_REGION 0x4002
#define EVENT_CONSOLE_UPDATE_SIMPLE 0x4003
#define EVENT_CONSOLE_UPDATE_SCROLL 0x4004
#define EVENT_CONSOLE_LAYOUT 0x4005
#define EVENT_CONSOLE_START_APPLICATION 0x4006
#define EVENT_CONSOLE_END_APPLICATION 0x4007

#define CONSOLE_APPLICATION_16BIT 0x0001

#define CONSOLE_CARET_SELECTION 0x0001
#define CONSOLE_CARET_VISIBLE 0x0002

#define EVENT_OBJECT_CREATE 0x8000
#define EVENT_OBJECT_DESTROY 0x8001
#define EVENT_OBJECT_SHOW 0x8002
#define EVENT_OBJECT_HIDE 0x8003
#define EVENT_OBJECT_REORDER 0x8004

#define EVENT_OBJECT_FOCUS 0x8005
#define EVENT_OBJECT_SELECTION 0x8006
#define EVENT_OBJECT_SELECTIONADD 0x8007
#define EVENT_OBJECT_SELECTIONREMOVE 0x8008
#define EVENT_OBJECT_SELECTIONWITHIN 0x8009

#define EVENT_OBJECT_STATECHANGE 0x800A

#define EVENT_OBJECT_LOCATIONCHANGE 0x800B

#define EVENT_OBJECT_NAMECHANGE 0x800C
#define EVENT_OBJECT_DESCRIPTIONCHANGE 0x800D
#define EVENT_OBJECT_VALUECHANGE 0x800E
#define EVENT_OBJECT_PARENTCHANGE 0x800F
#define EVENT_OBJECT_HELPCHANGE 0x8010
#define EVENT_OBJECT_DEFACTIONCHANGE 0x8011
#define EVENT_OBJECT_ACCELERATORCHANGE 0x8012

#define SOUND_SYSTEM_STARTUP 1
#define SOUND_SYSTEM_SHUTDOWN 2
#define SOUND_SYSTEM_BEEP 3
#define SOUND_SYSTEM_ERROR 4
#define SOUND_SYSTEM_QUESTION 5
#define SOUND_SYSTEM_WARNING 6
#define SOUND_SYSTEM_INFORMATION 7
#define SOUND_SYSTEM_MAXIMIZE 8
#define SOUND_SYSTEM_MINIMIZE 9
#define SOUND_SYSTEM_RESTOREUP 10
#define SOUND_SYSTEM_RESTOREDOWN 11
#define SOUND_SYSTEM_APPSTART 12
#define SOUND_SYSTEM_FAULT 13
#define SOUND_SYSTEM_APPEND 14
#define SOUND_SYSTEM_MENUCOMMAND 15
#define SOUND_SYSTEM_MENUPOPUP 16
#define CSOUND_SYSTEM 16

#define ALERT_SYSTEM_INFORMATIONAL 1
#define ALERT_SYSTEM_WARNING 2
#define ALERT_SYSTEM_ERROR 3
#define ALERT_SYSTEM_QUERY 4
#define ALERT_SYSTEM_CRITICAL 5
#define CALERT_SYSTEM 6

typedef struct tagGUITHREADINFO {
  DWORD cbSize;
  DWORD flags;
  HWND hwndActive;
  HWND hwndFocus;
  HWND hwndCapture;
  HWND hwndMenuOwner;
  HWND hwndMoveSize;
  HWND hwndCaret;
  RECT rcCaret;
} GUITHREADINFO, *PGUITHREADINFO, *LPGUITHREADINFO;

#define GUI_CARETBLINKING 0x00000001
#define GUI_INMOVESIZE 0x00000002
#define GUI_INMENUMODE 0x00000004
#define GUI_SYSTEMMENUMODE 0x00000008
#define GUI_POPUPMENUMODE 0x00000010
#define GUI_16BITTASK 0x00000020

#ifdef UNICODE
#define GetWindowModuleFileName GetWindowModuleFileNameW
#else
#define GetWindowModuleFileName GetWindowModuleFileNameA
#endif

WINUSERAPI WINBOOL WINAPI GetGUIThreadInfo(DWORD idThread, PGUITHREADINFO pgui);
WINUSERAPI UINT WINAPI GetWindowModuleFileNameA(HWND hwnd,
                                                LPSTR pszFileName,
                                                UINT cchFileNameMax);
WINUSERAPI UINT WINAPI GetWindowModuleFileNameW(HWND hwnd,
                                                LPWSTR pszFileName,
                                                UINT cchFileNameMax);

#ifndef NO_STATE_FLAGS
#define STATE_SYSTEM_UNAVAILABLE 0x00000001
#define STATE_SYSTEM_SELECTED 0x00000002
#define STATE_SYSTEM_FOCUSED 0x00000004
#define STATE_SYSTEM_PRESSED 0x00000008
#define STATE_SYSTEM_CHECKED 0x00000010
#define STATE_SYSTEM_MIXED 0x00000020
#define STATE_SYSTEM_INDETERMINATE STATE_SYSTEM_MIXED
#define STATE_SYSTEM_READONLY 0x00000040
#define STATE_SYSTEM_HOTTRACKED 0x00000080
#define STATE_SYSTEM_DEFAULT 0x00000100
#define STATE_SYSTEM_EXPANDED 0x00000200
#define STATE_SYSTEM_COLLAPSED 0x00000400
#define STATE_SYSTEM_BUSY 0x00000800
#define STATE_SYSTEM_FLOATING 0x00001000
#define STATE_SYSTEM_MARQUEED 0x00002000
#define STATE_SYSTEM_ANIMATED 0x00004000
#define STATE_SYSTEM_INVISIBLE 0x00008000
#define STATE_SYSTEM_OFFSCREEN 0x00010000
#define STATE_SYSTEM_SIZEABLE 0x00020000
#define STATE_SYSTEM_MOVEABLE 0x00040000
#define STATE_SYSTEM_SELFVOICING 0x00080000
#define STATE_SYSTEM_FOCUSABLE 0x00100000
#define STATE_SYSTEM_SELECTABLE 0x00200000
#define STATE_SYSTEM_LINKED 0x00400000
#define STATE_SYSTEM_TRAVERSED 0x00800000
#define STATE_SYSTEM_MULTISELECTABLE 0x01000000
#define STATE_SYSTEM_EXTSELECTABLE 0x02000000
#define STATE_SYSTEM_ALERT_LOW 0x04000000
#define STATE_SYSTEM_ALERT_MEDIUM 0x08000000
#define STATE_SYSTEM_ALERT_HIGH 0x10000000
#define STATE_SYSTEM_PROTECTED 0x20000000
#define STATE_SYSTEM_VALID 0x3FFFFFFF
#endif

#define CCHILDREN_TITLEBAR 5
#define CCHILDREN_SCROLLBAR 5

typedef struct tagCURSORINFO {
  DWORD cbSize;
  DWORD flags;
  HCURSOR hCursor;
  POINT ptScreenPos;
} CURSORINFO, *PCURSORINFO, *LPCURSORINFO;

#define CURSOR_SHOWING 0x00000001

WINUSERAPI WINBOOL WINAPI GetCursorInfo(PCURSORINFO pci);

typedef struct tagWINDOWINFO {
  DWORD cbSize;
  RECT rcWindow;
  RECT rcClient;
  DWORD dwStyle;
  DWORD dwExStyle;
  DWORD dwWindowStatus;
  UINT cxWindowBorders;
  UINT cyWindowBorders;
  ATOM atomWindowType;
  WORD wCreatorVersion;
} WINDOWINFO, *PWINDOWINFO, *LPWINDOWINFO;

#define WS_ACTIVECAPTION 0x0001

WINUSERAPI WINBOOL WINAPI GetWindowInfo(HWND hwnd, PWINDOWINFO pwi);

typedef struct tagTITLEBARINFO {
  DWORD cbSize;
  RECT rcTitleBar;
  DWORD rgstate[CCHILDREN_TITLEBAR + 1];
} TITLEBARINFO, *PTITLEBARINFO, *LPTITLEBARINFO;

WINUSERAPI WINBOOL WINAPI GetTitleBarInfo(HWND hwnd, PTITLEBARINFO pti);

typedef struct tagMENUBARINFO {
  DWORD cbSize;
  RECT rcBar;
  HMENU hMenu;
  HWND hwndMenu;
  WINBOOL fBarFocused : 1;
  WINBOOL fFocused : 1;
} MENUBARINFO, *PMENUBARINFO, *LPMENUBARINFO;

WINUSERAPI WINBOOL WINAPI GetMenuBarInfo(HWND hwnd,
                                         LONG idObject,
                                         LONG idItem,
                                         PMENUBARINFO pmbi);

typedef struct tagSCROLLBARINFO {
  DWORD cbSize;
  RECT rcScrollBar;
  int dxyLineButton;
  int xyThumbTop;
  int xyThumbBottom;
  int reserved;
  DWORD rgstate[CCHILDREN_SCROLLBAR + 1];
} SCROLLBARINFO, *PSCROLLBARINFO, *LPSCROLLBARINFO;

WINUSERAPI WINBOOL WINAPI GetScrollBarInfo(HWND hwnd,
                                           LONG idObject,
                                           PSCROLLBARINFO psbi);

typedef struct tagCOMBOBOXINFO {
  DWORD cbSize;
  RECT rcItem;
  RECT rcButton;
  DWORD stateButton;
  HWND hwndCombo;
  HWND hwndItem;
  HWND hwndList;
} COMBOBOXINFO, *PCOMBOBOXINFO, *LPCOMBOBOXINFO;

WINUSERAPI WINBOOL WINAPI GetComboBoxInfo(HWND hwndCombo, PCOMBOBOXINFO pcbi);

#define GA_PARENT 1
#define GA_ROOT 2
#define GA_ROOTOWNER 3

WINUSERAPI HWND WINAPI GetAncestor(HWND hwnd, UINT gaFlags);
WINUSERAPI HWND WINAPI RealChildWindowFromPoint(HWND hwndParent,
                                                POINT ptParentClientCoords);
WINUSERAPI UINT WINAPI RealGetWindowClassA(HWND hwnd,
                                           LPSTR ptszClassName,
                                           UINT cchClassNameMax);
WINUSERAPI UINT WINAPI RealGetWindowClassW(HWND hwnd,
                                           LPWSTR ptszClassName,
                                           UINT cchClassNameMax);
#ifdef UNICODE
#define RealGetWindowClass RealGetWindowClassW
#else
#define RealGetWindowClass RealGetWindowClassA
#endif

typedef struct tagALTTABINFO {
  DWORD cbSize;
  int cItems;
  int cColumns;
  int cRows;
  int iColFocus;
  int iRowFocus;
  int cxItem;
  int cyItem;
  POINT ptStart;
} ALTTABINFO, *PALTTABINFO, *LPALTTABINFO;

#ifdef UNICODE
#define GetAltTabInfo GetAltTabInfoW
#else
#define GetAltTabInfo GetAltTabInfoA
#endif

WINUSERAPI WINBOOL WINAPI GetAltTabInfoA(HWND hwnd,
                                         int iItem,
                                         PALTTABINFO pati,
                                         LPSTR pszItemText,
                                         UINT cchItemText);
WINUSERAPI WINBOOL WINAPI GetAltTabInfoW(HWND hwnd,
                                         int iItem,
                                         PALTTABINFO pati,
                                         LPWSTR pszItemText,
                                         UINT cchItemText);
WINUSERAPI DWORD WINAPI GetListBoxInfo(HWND hwnd);
#endif

WINUSERAPI WINBOOL WINAPI LockWorkStation(VOID);
WINUSERAPI WINBOOL WINAPI UserHandleGrantAccess(HANDLE hUserHandle,
                                                HANDLE hJob,
                                                WINBOOL bGrant);

DECLARE_HANDLE(HRAWINPUT);

#define GET_RAWINPUT_CODE_WPARAM(wParam) ((wParam)&0xff)

#define RIM_INPUT 0
#define RIM_INPUTSINK 1

typedef struct tagRAWINPUTHEADER {
  DWORD dwType;
  DWORD dwSize;
  HANDLE hDevice;
  WPARAM wParam;
} RAWINPUTHEADER, *PRAWINPUTHEADER, *LPRAWINPUTHEADER;

#define RIM_TYPEMOUSE 0
#define RIM_TYPEKEYBOARD 1
#define RIM_TYPEHID 2

typedef struct tagRAWMOUSE {
  USHORT usFlags;
  union {
    ULONG ulButtons;
    struct {
      USHORT usButtonFlags;
      USHORT usButtonData;
    };
  };
  ULONG ulRawButtons;
  LONG lLastX;
  LONG lLastY;
  ULONG ulExtraInformation;
} RAWMOUSE, *PRAWMOUSE, *LPRAWMOUSE;

#define RI_MOUSE_LEFT_BUTTON_DOWN 0x0001
#define RI_MOUSE_LEFT_BUTTON_UP 0x0002
#define RI_MOUSE_RIGHT_BUTTON_DOWN 0x0004
#define RI_MOUSE_RIGHT_BUTTON_UP 0x0008
#define RI_MOUSE_MIDDLE_BUTTON_DOWN 0x0010
#define RI_MOUSE_MIDDLE_BUTTON_UP 0x0020

#define RI_MOUSE_BUTTON_1_DOWN RI_MOUSE_LEFT_BUTTON_DOWN
#define RI_MOUSE_BUTTON_1_UP RI_MOUSE_LEFT_BUTTON_UP
#define RI_MOUSE_BUTTON_2_DOWN RI_MOUSE_RIGHT_BUTTON_DOWN
#define RI_MOUSE_BUTTON_2_UP RI_MOUSE_RIGHT_BUTTON_UP
#define RI_MOUSE_BUTTON_3_DOWN RI_MOUSE_MIDDLE_BUTTON_DOWN
#define RI_MOUSE_BUTTON_3_UP RI_MOUSE_MIDDLE_BUTTON_UP

#define RI_MOUSE_BUTTON_4_DOWN 0x0040
#define RI_MOUSE_BUTTON_4_UP 0x0080
#define RI_MOUSE_BUTTON_5_DOWN 0x0100
#define RI_MOUSE_BUTTON_5_UP 0x0200

#define RI_MOUSE_WHEEL 0x0400

#define MOUSE_MOVE_RELATIVE 0
#define MOUSE_MOVE_ABSOLUTE 1
#define MOUSE_VIRTUAL_DESKTOP 0x02
#define MOUSE_ATTRIBUTES_CHANGED 0x04

typedef struct tagRAWKEYBOARD {
  USHORT MakeCode;
  USHORT Flags;
  USHORT Reserved;
  USHORT VKey;
  UINT Message;
  ULONG ExtraInformation;
} RAWKEYBOARD, *PRAWKEYBOARD, *LPRAWKEYBOARD;

#define KEYBOARD_OVERRUN_MAKE_CODE 0xFF

#define RI_KEY_MAKE 0
#define RI_KEY_BREAK 1
#define RI_KEY_E0 2
#define RI_KEY_E1 4
#define RI_KEY_TERMSRV_SET_LED 8
#define RI_KEY_TERMSRV_SHADOW 0x10

typedef struct tagRAWHID {
  DWORD dwSizeHid;
  DWORD dwCount;
  BYTE bRawData[1];
} RAWHID, *PRAWHID, *LPRAWHID;

typedef struct tagRAWINPUT {
  RAWINPUTHEADER header;
  union {
    RAWMOUSE mouse;
    RAWKEYBOARD keyboard;
    RAWHID hid;
  } data;
} RAWINPUT, *PRAWINPUT, *LPRAWINPUT;

#ifdef _WIN64
#define RAWINPUT_ALIGN(x) (((x) + sizeof(QWORD) - 1) & ~(sizeof(QWORD) - 1))
#else
#define RAWINPUT_ALIGN(x) (((x) + sizeof(DWORD) - 1) & ~(sizeof(DWORD) - 1))
#endif

#define NEXTRAWINPUTBLOCK(ptr) \
  ((PRAWINPUT)RAWINPUT_ALIGN((ULONG_PTR)((PBYTE)(ptr) + (ptr)->header.dwSize)))

#define RID_INPUT 0x10000003
#define RID_HEADER 0x10000005

WINUSERAPI UINT WINAPI GetRawInputData(HRAWINPUT hRawInput,
                                       UINT uiCommand,
                                       LPVOID pData,
                                       PUINT pcbSize,
                                       UINT cbSizeHeader);

#define RIDI_PREPARSEDDATA 0x20000005
#define RIDI_DEVICENAME 0x20000007
#define RIDI_DEVICEINFO 0x2000000b

typedef struct tagRID_DEVICE_INFO_MOUSE {
  DWORD dwId;
  DWORD dwNumberOfButtons;
  DWORD dwSampleRate;
} RID_DEVICE_INFO_MOUSE, *PRID_DEVICE_INFO_MOUSE;

typedef struct tagRID_DEVICE_INFO_KEYBOARD {
  DWORD dwType;
  DWORD dwSubType;
  DWORD dwKeyboardMode;
  DWORD dwNumberOfFunctionKeys;
  DWORD dwNumberOfIndicators;
  DWORD dwNumberOfKeysTotal;
} RID_DEVICE_INFO_KEYBOARD, *PRID_DEVICE_INFO_KEYBOARD;

typedef struct tagRID_DEVICE_INFO_HID {
  DWORD dwVendorId;
  DWORD dwProductId;
  DWORD dwVersionNumber;
  USHORT usUsagePage;
  USHORT usUsage;
} RID_DEVICE_INFO_HID, *PRID_DEVICE_INFO_HID;

typedef struct tagRID_DEVICE_INFO {
  DWORD cbSize;
  DWORD dwType;
  union {
    RID_DEVICE_INFO_MOUSE mouse;
    RID_DEVICE_INFO_KEYBOARD keyboard;
    RID_DEVICE_INFO_HID hid;
  };
} RID_DEVICE_INFO, *PRID_DEVICE_INFO, *LPRID_DEVICE_INFO;

#ifdef UNICODE
#define GetRawInputDeviceInfo GetRawInputDeviceInfoW
#else
#define GetRawInputDeviceInfo GetRawInputDeviceInfoA
#endif

WINUSERAPI UINT WINAPI GetRawInputDeviceInfoA(HANDLE hDevice,
                                              UINT uiCommand,
                                              LPVOID pData,
                                              PUINT pcbSize);
WINUSERAPI UINT WINAPI GetRawInputDeviceInfoW(HANDLE hDevice,
                                              UINT uiCommand,
                                              LPVOID pData,
                                              PUINT pcbSize);
WINUSERAPI UINT WINAPI GetRawInputBuffer(PRAWINPUT pData,
                                         PUINT pcbSize,
                                         UINT cbSizeHeader);

typedef struct tagRAWINPUTDEVICE {
  USHORT usUsagePage;
  USHORT usUsage;
  DWORD dwFlags;
  HWND hwndTarget;
} RAWINPUTDEVICE, *PRAWINPUTDEVICE, *LPRAWINPUTDEVICE;

typedef CONST RAWINPUTDEVICE* PCRAWINPUTDEVICE;

#define RIDEV_REMOVE 0x00000001
#define RIDEV_EXCLUDE 0x00000010
#define RIDEV_PAGEONLY 0x00000020
#define RIDEV_NOLEGACY 0x00000030
#define RIDEV_INPUTSINK 0x00000100
#define RIDEV_CAPTUREMOUSE 0x00000200
#define RIDEV_NOHOTKEYS 0x00000200
#define RIDEV_APPKEYS 0x00000400
#define RIDEV_EXMODEMASK 0x000000F0
#define RIDEV_EXMODE(mode) ((mode)&RIDEV_EXMODEMASK)

WINUSERAPI WINBOOL WINAPI
RegisterRawInputDevices(PCRAWINPUTDEVICE pRawInputDevices,
                        UINT uiNumDevices,
                        UINT cbSize);
WINUSERAPI UINT WINAPI
GetRegisteredRawInputDevices(PRAWINPUTDEVICE pRawInputDevices,
                             PUINT puiNumDevices,
                             UINT cbSize);

typedef struct tagRAWINPUTDEVICELIST {
  HANDLE hDevice;
  DWORD dwType;
} RAWINPUTDEVICELIST, *PRAWINPUTDEVICELIST;

WINUSERAPI UINT WINAPI
GetRawInputDeviceList(PRAWINPUTDEVICELIST pRawInputDeviceList,
                      PUINT puiNumDevices,
                      UINT cbSize);
WINUSERAPI LRESULT WINAPI DefRawInputProc(PRAWINPUT* paRawInput,
                                          INT nInput,
                                          UINT cbSizeHeader);

#endif /* NOUSER */

#ifdef __cplusplus
}
#endif
#endif
