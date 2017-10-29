// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__66B554B5_4BD5_4EE4_A810_F016724679B8__INCLUDED_)
#define AFX_STDAFX_H__66B554B5_4BD5_4EE4_A810_F016724679B8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxole.h>         // MFC OLE classes
#include <afxodlgs.h>       // MFC OLE dialog classes
#include <afxdisp.h>        // MFC Automation classes
#endif // _AFX_NO_OLE_SUPPORT

#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#define USE_LOCAL_RESOURCES HINSTANCE hOldInstance = AfxGetResourceHandle(); AfxSetResourceHandle(g_Instance);
#define USE_GLOBAL_RESOURCES AfxSetResourceHandle(hOldInstance);

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.
#include <string>
using namespace std;

#include "sdk.sim.h"
#include "api.sim.h"

#endif // !defined(AFX_STDAFX_H__66B554B5_4BD5_4EE4_A810_F016724679B8__INCLUDED_)
