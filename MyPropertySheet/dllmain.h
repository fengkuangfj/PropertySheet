// dllmain.h : 模块类的声明。

class CMyPropertySheetModule : public ATL::CAtlDllModuleT< CMyPropertySheetModule >
{
public :
	DECLARE_LIBID(LIBID_MyPropertySheetLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_MYPROPERTYSHEET, "{4C605E6D-91FE-4BE9-A068-1696E383B033}")
};

extern class CMyPropertySheetModule _AtlModule;
