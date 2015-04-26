

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.00.0603 */
/* at Sun Apr 26 16:28:09 2015
 */
/* Compiler settings for editormfc2.idl:
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


#ifndef __editormfc2_h_h__
#define __editormfc2_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __Ieditormfc2_FWD_DEFINED__
#define __Ieditormfc2_FWD_DEFINED__
typedef interface Ieditormfc2 Ieditormfc2;

#endif 	/* __Ieditormfc2_FWD_DEFINED__ */


#ifndef __Ceditormfc2Doc_FWD_DEFINED__
#define __Ceditormfc2Doc_FWD_DEFINED__

#ifdef __cplusplus
typedef class Ceditormfc2Doc Ceditormfc2Doc;
#else
typedef struct Ceditormfc2Doc Ceditormfc2Doc;
#endif /* __cplusplus */

#endif 	/* __Ceditormfc2Doc_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 



#ifndef __editormfc2_LIBRARY_DEFINED__
#define __editormfc2_LIBRARY_DEFINED__

/* library editormfc2 */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_editormfc2;

#ifndef __Ieditormfc2_DISPINTERFACE_DEFINED__
#define __Ieditormfc2_DISPINTERFACE_DEFINED__

/* dispinterface Ieditormfc2 */
/* [uuid] */ 


EXTERN_C const IID DIID_Ieditormfc2;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("0DC66F25-F66E-4FDE-9688-FD10C3F81F99")
    Ieditormfc2 : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct Ieditormfc2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            Ieditormfc2 * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            Ieditormfc2 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            Ieditormfc2 * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            Ieditormfc2 * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            Ieditormfc2 * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            Ieditormfc2 * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            Ieditormfc2 * This,
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
    } Ieditormfc2Vtbl;

    interface Ieditormfc2
    {
        CONST_VTBL struct Ieditormfc2Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define Ieditormfc2_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define Ieditormfc2_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define Ieditormfc2_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define Ieditormfc2_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define Ieditormfc2_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define Ieditormfc2_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define Ieditormfc2_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __Ieditormfc2_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_Ceditormfc2Doc;

#ifdef __cplusplus

class DECLSPEC_UUID("6F8961FE-8107-49FB-A73A-03B6B5D7A95C")
Ceditormfc2Doc;
#endif
#endif /* __editormfc2_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


