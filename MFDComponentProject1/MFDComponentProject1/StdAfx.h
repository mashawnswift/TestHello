#if !defined(AFX_STDAFX_H__66B554B5_4BD5_4EE4_A810_F016724679B8__INCLUDED_)
#define AFX_STDAFX_H__66B554B5_4BD5_4EE4_A810_F016724679B8__INCLUDED_

#include "afxwin.h"

#include "sdk.sim.h"
#include "api.sim.h"

extern HINSTANCE g_Instance;

#define MAKE_HBITMAP_RESOURCE(resourceId) (HBITMAP)(::LoadBitmap(g_Instance, MAKEINTRESOURCE(resourceId)))

#endif // !defined(AFX_STDAFX_H__66B554B5_4BD5_4EE4_A810_F016724679B8__INCLUDED_)
