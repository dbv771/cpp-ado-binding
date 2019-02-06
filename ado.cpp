#define WIN32_LEAN_AND_MEAN  // Exclude rarely-used stuff from Windows headers
#include "stdafx.h"

#include <string>
#include <memory> //auto_ptr
#include <iostream>
#include <cwchar>
using std::string;
using std::auto_ptr;
using std::cout;
using std::endl;

//----
#define MT4_EXPFUNC __declspec(dllexport)
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
#pragma pack(push,1)

struct RateInfo
{
	unsigned int      ctm;
	double            open;
	double            low;
	double            high;
	double            close;
	double            vol;
	double            vol1;
	double            vol2;
	double            vol3;
	double            vol4;
	double            vol5;

};

#pragma pack(pop)



struct MqlStr
{
	int               len;
	char             *string;
};

static int CompareMqlStr(const void *left, const void *right);



MT4_EXPFUNC int __stdcall TEST_func(int x, int y)
{
	//printf("SUM ", x + y);
	return(x + y);
}




//////////////////////////////////

#include <stdio.h>
#import "C:\Program Files\Common Files\System\ado\msado20.tlb" \
        rename("EOF","ADOEOF") rename("BOF","ADOBOF")

using namespace ADODB;



inline void TESTHR(HRESULT x) { if FAILED(x) _com_issue_error(x); };





MT4_EXPFUNC int __stdcall Lands(int x)
{
	//wchar_t Aa[1024] = L"My Test Unicode String!";
	
	HRESULT hr = S_OK;
	_CommandPtr pCmd = NULL;
	_ConnectionPtr pConnection = NULL;
	_bstr_t strMessage, strAuthorID;

	::CoInitialize(NULL);

	long codRet = -1;

	try {

		_ParameterPtr ParReturn; // 



		TESTHR(pConnection.CreateInstance(__uuidof(Connection)));

		pConnection->ConnectionString = "DSN=SQL_DB;UID=111;PWD=111;";
		hr = pConnection->Open("", "", "", adConnectUnspecified);


		pConnection->CursorLocation = adUseClient;
		TESTHR(pCmd.CreateInstance(__uuidof(Command)));
		pCmd->CommandText = "TEST_select";  
		pCmd->CommandType = adCmdStoredProc;

		ParReturn = pCmd->CreateParameter(_bstr_t("@A"), adInteger, adParamOutput, 0, codRet);
		pCmd->Parameters->Append(ParReturn);

		//ParReturn = pCmd->CreateParameter(_bstr_t("@codRet"), adInteger, adParamOutput, 0, codRet);
		//pCmd->Parameters->Append(ParReturn);

		/*Par1 = pCmd->CreateParameter("@everCountry", adChar, adParamInput, strlen(Country), Country);
		pCmd->Parameters->Append(Par1);

		Par2 = pCmd->CreateParameter("@everCity", adChar, adParamInput, strlen(City), City);
		pCmd->Parameters->Append(Par2);*/
	


		pCmd->ActiveConnection = pConnection;
		int hr = pCmd->Execute(0, 0, adCmdStoredProc);
		if (FAILED(hr))
		{
			codRet = -1;
		}
		else
		{
			ParReturn = pCmd->Parameters->GetItem(_bstr_t("@A"));   
			codRet = ParReturn->GetValue();
		}
	}
	catch (_com_error) {
		//
		// 
		//
		codRet = -1;

	}
	if (pConnection)
		if (pConnection->State == adStateOpen)
			pConnection->Close();

	::CoUninitialize();
	return(codRet);
}
