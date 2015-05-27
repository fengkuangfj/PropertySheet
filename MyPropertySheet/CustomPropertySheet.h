// CustomPropertySheet.h : CCustomPropertySheet 的声明

#pragma once
#include "resource.h"       // 主符号



#include "MyPropertySheet_i.h"



#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Windows CE 平台(如不提供完全 DCOM 支持的 Windows Mobile 平台)上无法正确支持单线程 COM 对象。定义 _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA 可强制 ATL 支持创建单线程 COM 对象实现并允许使用其单线程 COM 对象实现。rgs 文件中的线程模型已被设置为“Free”，原因是该模型是非 DCOM Windows CE 平台支持的唯一线程模型。"
#endif

using namespace ATL;


// CCustomPropertySheet

class ATL_NO_VTABLE CCustomPropertySheet :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CCustomPropertySheet, &CLSID_CustomPropertySheet>,
	public IDispatchImpl<ICustomPropertySheet, &IID_ICustomPropertySheet, &LIBID_MyPropertySheetLib, /*wMajor =*/ 1, /*wMinor =*/ 0>,
	public IShellExtInit,
	public IShellPropSheetExt
{
public:
	CCustomPropertySheet()
	{
	}

	HRESULT
		STDMETHODCALLTYPE
		Initialize(
		__in_opt PCIDLIST_ABSOLUTE	pidlFolder,
		__in_opt IDataObject*		pdtobj,
		__in_opt HKEY				hkeyProgID
		);

	HRESULT
		STDMETHODCALLTYPE
		AddPages(
		__in LPFNSVADDPROPSHEETPAGE pfnAddPage,
		__in LPARAM					lParam
		);

	HRESULT
		STDMETHODCALLTYPE
		ReplacePage(
		__in EXPPS					uPageID,
		__in LPFNSVADDPROPSHEETPAGE pfnReplaceWith,
		__in LPARAM					lParam
		);

	static
	INT_PTR
		CALLBACK
		DialogProc(
		_In_ HWND	hwndDlg,
		_In_ UINT	uMsg,
		_In_ WPARAM wParam,
		_In_ LPARAM lParam
		);
	
	static
	UINT
		CALLBACK
		PropSheetPageProc(
		HWND					hwnd,
		_In_	UINT			uMsg,
		_Inout_	LPPROPSHEETPAGE ppsp
		);

DECLARE_REGISTRY_RESOURCEID(IDR_CUSTOMPROPERTYSHEET)


BEGIN_COM_MAP(CCustomPropertySheet)
	COM_INTERFACE_ENTRY(ICustomPropertySheet)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IShellExtInit)
	COM_INTERFACE_ENTRY(IShellPropSheetExt)
END_COM_MAP()



	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}

public:
#define PROPERTY_SHEET_1 _T("PropertySheet1")
#define PROPERTY_SHEET_2 _T("PropertySheet2")
};

OBJECT_ENTRY_AUTO(__uuidof(CustomPropertySheet), CCustomPropertySheet)
