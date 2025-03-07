/**
 * This file has no copyright assigned and is placed in the Public Domain.
 * This file is part of the w64 mingw-runtime package.
 * No warranty is given; refer to the file DISCLAIMER within this package.
 */
#ifndef _INC_EXCPT
#define _INC_EXCPT

#include <vcruntime.h>

#if !defined(RC_INVOKED)
#include <pseh/pseh2.h>
#endif

#pragma pack(push,_CRT_PACKING)

#ifdef __cplusplus
extern "C" {
#endif

typedef enum _EXCEPTION_DISPOSITION
{
    ExceptionContinueExecution,
    ExceptionContinueSearch,
    ExceptionNestedException,
    ExceptionCollidedUnwind,
} EXCEPTION_DISPOSITION;

#if (defined(_X86_) && !defined(__x86_64))
  struct _EXCEPTION_RECORD;
  struct _CONTEXT;

  EXCEPTION_DISPOSITION
  __cdecl
  _except_handler(
    _In_ struct _EXCEPTION_RECORD *_ExceptionRecord,
    _In_ void *_EstablisherFrame,
    _Inout_ struct _CONTEXT *_ContextRecord,
    _Inout_ void *_DispatcherContext);

#elif defined(__ia64__)

  typedef struct _EXCEPTION_POINTERS *Exception_info_ptr;
  struct _EXCEPTION_RECORD;
  struct _CONTEXT;
  struct _DISPATCHER_CONTEXT;

  __MINGW_EXTENSION
  _CRTIMP
  EXCEPTION_DISPOSITION
  __cdecl
  __C_specific_handler(
    _In_ struct _EXCEPTION_RECORD *_ExceptionRecord,
    _In_ unsigned __int64 _MemoryStackFp,
    _In_ unsigned __int64 _BackingStoreFp,
    _Inout_ struct _CONTEXT *_ContextRecord,
    _Inout_ struct _DISPATCHER_CONTEXT *_DispatcherContext,
    _In_ unsigned __int64 _GlobalPointer);

#elif defined(__x86_64) || defined(_M_ARM) || defined(_M_ARM64)

  struct _EXCEPTION_RECORD;
  struct _CONTEXT;
  struct _DISPATCHER_CONTEXT;

  _CRTIMP
  EXCEPTION_DISPOSITION
  __cdecl
  __C_specific_handler(
    _In_ struct _EXCEPTION_RECORD *_ExceptionRecord,
    _In_ void *_EstablisherFrame,
    _Inout_ struct _CONTEXT *_ContextRecord,
    _Inout_ struct _DISPATCHER_CONTEXT *_DispatcherContext);

#endif

#if (defined(_MSC_VER) || (defined(__clang__) && defined(__SEH__))) && !defined(_exception_code)
  unsigned long __cdecl _exception_code(void);
  void *__cdecl _exception_info(void);
  int __cdecl _abnormal_termination(void);
#endif

#define GetExceptionCode _exception_code
#define exception_code _exception_code
#define GetExceptionInformation (struct _EXCEPTION_POINTERS *)_exception_info
#define exception_info (struct _EXCEPTION_POINTERS *)_exception_info
#define AbnormalTermination _abnormal_termination
#define abnormal_termination _abnormal_termination

#define EXCEPTION_EXECUTE_HANDLER 1
#define EXCEPTION_CONTINUE_SEARCH 0
#define EXCEPTION_CONTINUE_EXECUTION -1

#if 0
  /* CRT stuff */
  typedef void (__cdecl * _PHNDLR)(int);

  struct _XCPT_ACTION {
    unsigned long XcptNum;
    int SigNum;
    _PHNDLR XcptAction;
  };

  extern struct _XCPT_ACTION _XcptActTab[];
  extern int _XcptActTabCount;
  extern int _XcptActTabSize;
  extern int _First_FPE_Indx;
  extern int _Num_FPE;

  int __cdecl __CppXcptFilter(unsigned long _ExceptionNum,struct _EXCEPTION_POINTERS * _ExceptionPtr);
  int __cdecl _XcptFilter(unsigned long _ExceptionNum,struct _EXCEPTION_POINTERS * _ExceptionPtr);

  /*
  * The type of function that is expected as an exception handler to be
  * installed with _try1.
  */
  typedef EXCEPTION_DISPOSITION (*PEXCEPTION_HANDLER)(struct _EXCEPTION_RECORD*, void*, struct _CONTEXT*, void*);

#ifndef HAVE_NO_SEH
  /*
  * This is not entirely necessary, but it is the structure installed by
  * the _try1 primitive below.
  */
  typedef struct _EXCEPTION_REGISTRATION {
    struct _EXCEPTION_REGISTRATION *prev;
    EXCEPTION_DISPOSITION (*handler)(struct _EXCEPTION_RECORD*, void*, struct _CONTEXT*, void*);
  } EXCEPTION_REGISTRATION, *PEXCEPTION_REGISTRATION;

  typedef EXCEPTION_REGISTRATION EXCEPTION_REGISTRATION_RECORD;
  typedef PEXCEPTION_REGISTRATION PEXCEPTION_REGISTRATION_RECORD;
#endif

#if (defined(_X86_) && !defined(__x86_64))
#define __try1(pHandler) \
  __asm__ ("pushl %0;pushl %%fs:0;movl %%esp,%%fs:0;" : : "g" (pHandler));

#define	__except1	\
  __asm__ ("movl (%%esp),%%eax;movl %%eax,%%fs:0;addl $8,%%esp;" \
  : : : "%eax");
#elif defined(__x86_64)
#define __try1(pHandler) \
  __asm__ ("pushq %0;pushq %%gs:0;movq %%rsp,%%gs:0;" : : "g" (pHandler));

#define	__except1	\
  __asm__ ("movq (%%rsp),%%rax;movq %%rax,%%gs:0;addq $16,%%rsp;" \
  : : : "%rax");
#else
#define __try1(pHandler)
#define __except1
#endif

#endif // 0

#ifdef __cplusplus
}
#endif

#pragma pack(pop)
#endif
