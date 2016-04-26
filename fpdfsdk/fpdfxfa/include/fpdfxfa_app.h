// Copyright 2014 PDFium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// Original code copyright 2014 Foxit Software Inc. http://www.foxitsoftware.com

#ifndef FPDFSDK_FPDFXFA_INCLUDE_FPDFXFA_APP_H_
#define FPDFSDK_FPDFXFA_INCLUDE_FPDFXFA_APP_H_

#include "xfa/fxfa/include/fxfa.h"

class CPDFDoc_Environment;
class IFXJS_Runtime;

class CPDFXFA_App : public IXFA_AppProvider {
 public:
  static CPDFXFA_App* GetInstance();
  static void ReleaseInstance();

  CPDFXFA_App();
  ~CPDFXFA_App() override;

  FX_BOOL Initialize(FXJSE_HRUNTIME hRuntime);
  CXFA_FFApp* GetXFAApp() { return m_pXFAApp; }

  FX_BOOL AddFormFillEnv(CPDFDoc_Environment* pEnv);
  FX_BOOL RemoveFormFillEnv(CPDFDoc_Environment* pEnv);

  FX_BOOL IsJavaScriptInitialized() const { return m_bJavaScriptInitialized; }
  void SetJavaScriptInitialized(FX_BOOL bInitialized) {
    m_bJavaScriptInitialized = bInitialized;
  }

  FXJSE_HRUNTIME GetJSERuntime() const { return m_hJSERuntime; }

  // IFXA_AppProvider:
  void GetAppType(CFX_WideString& wsAppType) override;
  void SetAppType(const CFX_WideStringC& wsAppType) override;

  void GetLanguage(CFX_WideString& wsLanguage) override;
  void GetPlatform(CFX_WideString& wsPlatform) override;
  void GetVariation(CFX_WideString& wsVariation) override;
  void GetVersion(CFX_WideString& wsVersion) override;
  void GetFoxitVersion(CFX_WideString& wsFoxitVersion) override {
    wsFoxitVersion = L"7.0";
  }

  void GetAppName(CFX_WideString& wsName) override;
  void GetFoxitAppName(CFX_WideString& wsFoxitName) override {
    wsFoxitName = L"Foxit";
  }

  void Beep(uint32_t dwType) override;
  int32_t MsgBox(const CFX_WideStringC& wsMessage,
                 const CFX_WideStringC& wsTitle,
                 uint32_t dwIconType,
                 uint32_t dwButtonType) override;
  void Response(CFX_WideString& wsAnswer,
                const CFX_WideStringC& wsQuestion,
                const CFX_WideStringC& wsTitle,
                const CFX_WideStringC& wsDefaultAnswer,
                FX_BOOL bMark) override;

  int32_t GetDocumentCountInBatch() override;
  int32_t GetCurDocumentInBatch() override;

  IFX_FileRead* DownloadURL(const CFX_WideStringC& wsURL) override;
  FX_BOOL PostRequestURL(const CFX_WideStringC& wsURL,
                         const CFX_WideStringC& wsData,
                         const CFX_WideStringC& wsContentType,
                         const CFX_WideStringC& wsEncode,
                         const CFX_WideStringC& wsHeader,
                         CFX_WideString& wsResponse) override;
  FX_BOOL PutRequestURL(const CFX_WideStringC& wsURL,
                        const CFX_WideStringC& wsData,
                        const CFX_WideStringC& wsEncode) override;

  void LoadString(int32_t iStringID, CFX_WideString& wsString) override;
  IFWL_AdapterTimerMgr* GetTimerMgr() override;

  CFX_ArrayTemplate<CPDFDoc_Environment*> m_pEnvList;

 protected:
  static CPDFXFA_App* g_pApp;

  FX_BOOL m_bJavaScriptInitialized;
  CXFA_FFApp* m_pXFAApp;
  FXJSE_HRUNTIME m_hJSERuntime;
  IFXJS_Runtime* m_pJSRuntime;
  CFX_WideString m_csAppType;
  bool m_bOwnedRuntime;
};

#endif  // FPDFSDK_FPDFXFA_INCLUDE_FPDFXFA_APP_H_
