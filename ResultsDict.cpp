// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME ResultsDict

/*******************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <assert.h>
#define G__DICTIONARY
#include "RConfig.h"
#include "TClass.h"
#include "TDictAttributeMap.h"
#include "TInterpreter.h"
#include "TROOT.h"
#include "TBuffer.h"
#include "TMemberInspector.h"
#include "TError.h"

#ifndef G__ROOT
#define G__ROOT
#endif

#include "RtypesImp.h"
#include "TIsAProxy.h"
#include "TFileMergeInfo.h"
#include <algorithm>
#include "TCollectionProxyInfo.h"
/*******************************************************************/

#include "TDataMember.h"

// Since CINT ignores the std namespace, we need to do so in this file.
namespace std {} using namespace std;

// Header files passed as explicit arguments
#include "Results.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static void *new_Results(void *p = 0);
   static void *newArray_Results(Long_t size, void *p);
   static void delete_Results(void *p);
   static void deleteArray_Results(void *p);
   static void destruct_Results(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Results*)
   {
      ::Results *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::Results >(0);
      static ::ROOT::TGenericClassInfo 
         instance("Results", ::Results::Class_Version(), "Results.h", 6,
                  typeid(::Results), DefineBehavior(ptr, ptr),
                  &::Results::Dictionary, isa_proxy, 4,
                  sizeof(::Results) );
      instance.SetNew(&new_Results);
      instance.SetNewArray(&newArray_Results);
      instance.SetDelete(&delete_Results);
      instance.SetDeleteArray(&deleteArray_Results);
      instance.SetDestructor(&destruct_Results);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Results*)
   {
      return GenerateInitInstanceLocal((::Results*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::Results*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
TClass *Results::fgIsA = 0;  // static to hold class pointer

//______________________________________________________________________________
const char *Results::Class_Name()
{
   return "Results";
}

//______________________________________________________________________________
const char *Results::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Results*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int Results::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Results*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
void Results::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Results*)0x0)->GetClass();
}

//______________________________________________________________________________
TClass *Results::Class()
{
   if (!fgIsA) fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Results*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
void Results::Streamer(TBuffer &R__b)
{
   // Stream an object of class Results.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(Results::Class(),this);
   } else {
      R__b.WriteClassBuffer(Results::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_Results(void *p) {
      return  p ? new(p) ::Results : new ::Results;
   }
   static void *newArray_Results(Long_t nElements, void *p) {
      return p ? new(p) ::Results[nElements] : new ::Results[nElements];
   }
   // Wrapper around operator delete
   static void delete_Results(void *p) {
      delete ((::Results*)p);
   }
   static void deleteArray_Results(void *p) {
      delete [] ((::Results*)p);
   }
   static void destruct_Results(void *p) {
      typedef ::Results current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Results

namespace {
  void TriggerDictionaryInitialization_ResultsDict_Impl() {
    static const char* headers[] = {
"Results.h",
0
    };
    static const char* includePaths[] = {
"/publicfs/dyb/user/lidj/software/root-v6-00/include",
"/publicfs/dyb/data/userdata/lidj/flukaWork/FAR/",
0
    };
    static const char* payloadCode = 
"\n"
"#ifndef G__VECTOR_HAS_CLASS_ITERATOR\n"
"  #define G__VECTOR_HAS_CLASS_ITERATOR\n"
"#endif\n"
"\n"
"#define _BACKWARD_BACKWARD_WARNING_H\n"
"#include \"Results.h\"\n"
"\n"
"#undef  _BACKWARD_BACKWARD_WARNING_H\n"
;
    static const char* classesHeaders[]={
"Results", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("ResultsDict",
        headers, includePaths, payloadCode,
        TriggerDictionaryInitialization_ResultsDict_Impl, {}, classesHeaders);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_ResultsDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_ResultsDict() {
  TriggerDictionaryInitialization_ResultsDict_Impl();
}
