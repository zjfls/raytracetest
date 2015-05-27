

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.00.0603 */
/* at Wed May 27 15:13:56 2015
 */
/* Compiler settings for EditorMFC.idl:
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


#ifndef __EditorMFC_h_h__
#define __EditorMFC_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IEditorMFC_FWD_DEFINED__
#define __IEditorMFC_FWD_DEFINED__
typedef interface IEditorMFC IEditorMFC;

#endif 	/* __IEditorMFC_FWD_DEFINED__ */


#ifndef __CEditorMFCDoc_FWD_DEFINED__
#define __CEditorMFCDoc_FWD_DEFINED__

#ifdef __cplusplus
typedef class CEditorMFCDoc CEditorMFCDoc;
#else
typedef struct CEditorMFCDoc CEditorMFCDoc;
#endif /* __cplusplus */

#endif 	/* __CEditorMFCDoc_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 



#ifndef __EditorMFC_LIBRARY_DEFINED__
#define __EditorMFC_LIBRARY_DEFINED__

/* library EditorMFC */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_EditorMFC;

#ifndef __IEditorMFC_DISPINTERFACE_DEFINED__
#define __IEditorMFC_DISPINTERFACE_DEFINED__

/* dispinterface IEditorMFC */
/* [uuid] */ 


EXTERN_C const IID DIID_IEditorMFC;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("77B0D67A-7654-4297-A64C-B2D5AAA31853")
    IEditorMFC : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IEditorMFCVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEditorMFC * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEditorMFC * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEditorMFC * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IEditorMFC * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IEditorMFC * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IEditorMFC * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IEditorMFC * This,
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
    } IEditorMFCVtbl;

    interface IEditorMFC
    {
        CONST_VTBL struct IEditorMFCVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEditorMFC_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IEditorMFC_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IEditorMFC_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IEditorMFC_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IEditorMFC_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IEditorMFC_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IEditorMFC_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IEditorMFC_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_CEditorMFCDoc;

#ifdef __cplusplus

class DECLSPEC_UUID("7A262AAF-1B37-4978-898F-00C4484FEDA0")
CEditorMFCDoc;
#endif
#endif /* __EditorMFC_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


