// dia-file-handle-leak-on-error.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers
#include "dia2.h"

int main()
{
	IDiaDataSource* pDiaDataSource = NULL;
	const wchar_t* szFilename_bad = L".\\sqlmin.pdb";
	const wchar_t* szFilename_good = L".\\hkengine.pdb";

	HRESULT hr = CoInitialize(NULL);

	hr = CoCreateInstance(__uuidof(DiaSource),
		NULL,
		CLSCTX_INPROC_SERVER,
		__uuidof(IDiaDataSource),
		(void**)&pDiaDataSource);

	if (FAILED(hr)) {
		wprintf(L"CoCreateInstance failed - HRESULT = %08X\n", hr);

		return false;
	}

	// try loading the corrupt PDB
	hr = pDiaDataSource->loadDataFromPdb(szFilename_bad);
	if (FAILED(hr)) {
		wprintf(L"loadDataFromPdb for %s failed - HRESULT = %08X\n", szFilename_bad, hr);
	}

	// try loading the good PDB
	hr = pDiaDataSource->loadDataFromPdb(szFilename_good);
	if (FAILED(hr)) {
		wprintf(L"loadDataFromPdb for %s failed - HRESULT = %08X\n", szFilename_good, hr);
	}

	pDiaDataSource->Release();
	CoUninitialize();

	wprintf(L"At this point, try deleting the hkruntime.pdb and sqlmin.pdb files from the output folder. You will be unable to delete the sqlmin.pdb file as DIA has not closed the handle.");

	std::cout << '\n' << "After verifying the behavior, press ENTER to exit...";
	do
	{
	} while (std::cin.get() != '\n');

	return false;
}