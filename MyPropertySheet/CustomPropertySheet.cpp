// CustomPropertySheet.cpp : CCustomPropertySheet 的实现

#include "stdafx.h"
#include "CustomPropertySheet.h"


// CCustomPropertySheet
extern LONG g_lLockCnt;


HRESULT
	STDMETHODCALLTYPE
	CCustomPropertySheet::Initialize(
	__in_opt PCIDLIST_ABSOLUTE	pidlFolder,
	__in_opt IDataObject*		pdtobj,
	__in_opt HKEY				hkeyProgID
	)
{
	return S_OK;
}

HRESULT
	STDMETHODCALLTYPE
	CCustomPropertySheet::AddPages(
	__in LPFNSVADDPROPSHEETPAGE pfnAddPage,
	__in LPARAM					lParam
	)
{
	HRESULT			hRet	= E_FAIL;

	PROPSHEETPAGE	psp1	= {0};
	HPROPSHEETPAGE	hPage1	= NULL;
	PROPSHEETPAGE	psp2	= {0};
	HPROPSHEETPAGE	hPage2	= NULL;


	__try
	{
		// 插入第一页
		psp1.dwSize        = sizeof(psp1);
		psp1.dwFlags       = PSP_USEREFPARENT | PSP_USETITLE | PSP_USECALLBACK;
		psp1.hInstance     = _AtlBaseModule.GetModuleInstance();
		psp1.pszTemplate   = MAKEINTRESOURCE(IDD_DIALOG_PROPERTY_SHEET_1);
		psp1.hIcon         = 0;
		psp1.pszTitle      = PROPERTY_SHEET_1;
		psp1.pfnDlgProc    = (DLGPROC)DialogProc;
		psp1.pcRefParent   = (UINT *)&g_lLockCnt;
		psp1.pfnCallback   = PropSheetPageProc;
		psp1.lParam        = (LPARAM)this;

		hPage1 = CreatePropertySheetPage(&psp1);
		if (!hPage1)
		{
			hRet = E_OUTOFMEMORY;
			__leave;
		}

		if (!pfnAddPage(hPage1, lParam))
			__leave;

		// 插入第二页
		psp2.dwSize        = sizeof(psp2);
		psp2.dwFlags       = PSP_USEREFPARENT | PSP_USETITLE | PSP_USECALLBACK;
		psp2.hInstance     = _AtlBaseModule.GetModuleInstance();
		psp2.pszTemplate   = MAKEINTRESOURCE(IDD_DIALOG_PROPERTY_SHEET_2);
		psp2.hIcon         = 0;
		psp2.pszTitle      = PROPERTY_SHEET_2;
		psp2.pfnDlgProc    = (DLGPROC)DialogProc;
		psp2.pcRefParent   = (UINT *)&g_lLockCnt;
		psp2.pfnCallback   = PropSheetPageProc;
		psp2.lParam        = (LPARAM)this;

		hPage2 = CreatePropertySheetPage(&psp2);
		if (!hPage2)
		{
			hRet = E_OUTOFMEMORY;
			__leave;
		}

		if (!pfnAddPage(hPage2, lParam))
			__leave;

		this->AddRef();

		hRet = S_OK;
	}
	__finally
	{
		if (hPage1 && (S_OK != hRet))
		{
			DestroyPropertySheetPage(hPage1);
			hPage1 = NULL;
		}

		if (hPage2 && (S_OK != hRet))
		{
			DestroyPropertySheetPage(hPage2);
			hPage2 = NULL;
		}
	}

	return hRet;
}

HRESULT
	STDMETHODCALLTYPE
	CCustomPropertySheet::ReplacePage(
	__in EXPPS					uPageID,
	__in LPFNSVADDPROPSHEETPAGE pfnReplaceWith,
	__in LPARAM					lParam
	)
{
	return E_NOTIMPL;
}

INT_PTR
	CALLBACK
	CCustomPropertySheet::DialogProc(
	_In_ HWND	hwndDlg,
	_In_ UINT	uMsg,
	_In_ WPARAM wParam,
	_In_ LPARAM lParam
	)
{
	INT_PTR nRet	= FALSE;

	LONG	lResult = 0;


	__try
	{
		switch (uMsg)
		{
		case WM_CHARTOITEM:
		case WM_COMPAREITEM:
		case WM_CTLCOLORBTN:
		case WM_CTLCOLORDLG:
		case WM_CTLCOLOREDIT:
		case WM_CTLCOLORLISTBOX:
		case WM_CTLCOLORSCROLLBAR:
		case WM_CTLCOLORSTATIC:
		case WM_INITDIALOG:
		case WM_QUERYDRAGICON:
		case WM_VKEYTOITEM:
			{
				nRet = TRUE;
				break;
			}
		default:
			__leave;
		}
	}
	__finally
	{
#if (NTDDI_VERSION <= NTDDI_WINXP)
		if (nRet && lResult)
			SetWindowLong(hwndDlg, DWL_MSGRESULT, lResult);
#endif
	}

	return nRet;
}

UINT
	CALLBACK
	CCustomPropertySheet::PropSheetPageProc(
	HWND					hwnd,
	_In_	UINT			uMsg,
	_Inout_	LPPROPSHEETPAGE ppsp
	)
{
	UINT nRet		= 0;

	BOOL bCreate	= TRUE;


	__try
	{
		if (hwnd)
			__leave;

		switch (uMsg)
		{
		case PSPCB_ADDREF:
		case PSPCB_RELEASE:
			break;
		case PSPCB_CREATE:
			{
				if (bCreate)
					nRet = 1;

				break;
			}
		default:
			__leave;
		}	
	}
	__finally
	{
		;
	}

	return nRet;
}