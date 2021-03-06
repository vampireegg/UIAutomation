// uiAutomation2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "Uiautomation.h"


int main()
{
	CoInitialize(NULL);
	IUIAutomation *pAutomation; // requires Uiautomation.h
	HRESULT hr = CoCreateInstance(__uuidof(CUIAutomation), NULL, CLSCTX_INPROC_SERVER, __uuidof(IUIAutomation), (LPVOID *)&pAutomation);
	if (SUCCEEDED(hr))
	{
		RECT rc;
		GetWindowRect(GetDesktopWindow(), &rc);
		POINT center;
		center.x = (rc.right - rc.left) / 2;
		center.y = (rc.bottom - rc.top) / 2;
		printf("center x:%i y:%i'\n", center.x, center.y);
		do
		{
			IUIAutomationElement *pElement;
			hr = pAutomation->GetFocusedElement(/*center, */&pElement);
			if (SUCCEEDED(hr))
			{
				BSTR str;
				hr = pElement->get_CurrentClassName(&str);
				if (SUCCEEDED(hr))
				{
					printf("element name:'%S'\n", str);
					::SysFreeString(str);
				}

				hr = pElement->get_CurrentName(&str);
				if (SUCCEEDED(hr))
				{
					printf("name:'%S'\n", str);
					::SysFreeString(str);
				}
				pElement->Release();
			}
			Sleep(1000);
		} while (TRUE);
		pAutomation->Release();
	}

	CoUninitialize();
    return 0;
}

