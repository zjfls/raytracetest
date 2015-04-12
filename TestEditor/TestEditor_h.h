

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.00.0603 */
/* at Sat Apr 11 19:00:13 2015
 */
/* Compiler settings for TestEditor.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 8.00.0603 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__


#ifndef __TestEditor_h_h__
#define __TestEditor_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __ITestEditor_FWD_DEFINED__
#define __ITestEditor_FWD_DEFINED__
typedef interface ITestEditor ITestEditor;

#endif 	/* __ITestEditor_FWD_DEFINED__ */


#ifndef __CTestEditorDoc_FWD_DEFINED__
#define __CTestEditorDoc_FWD_DEFINED__

#ifdef __cplusplus
typedef class CTestEditorDoc CTestEditorDoc;
#else
typedef struct CTestEditorDoc CTestEditorDoc;
#endif /* __cplusplus */

#endif 	/* __CTestEditorDoc_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 



#ifndef __TestEditor_LIBRARY_DEFINED__
#define __TestEditor_LIBRARY_DEFINED__

/* library TestEditor */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_TestEditor;

#ifndef __ITestEditor_DISPINTERFACE_DEFINED__
#define __ITestEditor_DISPINTERFACE_DEFINED__

/* dispinterface ITestEditor */
/* [uuid] */ 


EXTERN_C const IID DIID_ITestEditor;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("0E93D44A-D529-4AE0-B753-E02B115EFB3E")
    ITestEditor : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct ITestEditorVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITestEditor * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITestEditor * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITestEditor * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ITestEditor * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ITestEditor * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ITestEditor * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ITestEditor * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        END_INTERFACE
    } ITestEditorVtbl;

    interface ITestEditor
    {
        CONST_VTBL struct ITestEditorVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITestEditor_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ITestEditor_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ITestEditor_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ITestEditor_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define ITestEditor_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define ITestEditor_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define ITestEditor_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __ITestEditor_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_CTestEditorDoc;

#ifdef __cplusplus

class DECLSPEC_UUID("576830FE-41A6-4C53-95CB-47BB70979BAD")
CTestEditorDoc;
#endif
#endif /* __TestEditor_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


