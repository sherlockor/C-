#include "StdAfx.h"
#include "PrinterManager.h"

#include <QPrinter>
#include <QPrinterInfo>

#include <Windows.h>

PrinterManager::PrinterManager(QObject *parent)
	: QObject(parent)
{

}

PrinterManager::~PrinterManager()
{

}

QString PrinterManager::GetDefaultPrinterByQt()
{
	return QPrinterInfo::defaultPrinter().printerName();
}

int PrinterManager::GetDefaultPrinterByWindowsAPI(std::wstring* printer_name)
{
	wchar_t szBuffer[1024]={0};
	DWORD length = 1024;
	int ret = ::GetDefaultPrinter(szBuffer,&length);
	if(ret == FALSE)
	{
		return ::GetLastError();
	}
	*printer_name = szBuffer;
	return ERROR_SUCCESS;
}

void PrinterManager::GetAllPrintersByQt(QList<QString>* all_printers)
{
	QList<QPrinterInfo> list = QPrinterInfo::availablePrinters();
	for (int index = 0; index < list.size(); index++)
	{
		all_printers->append(list.at(index).printerName());
	}
}

int PrinterManager::GetAllPrintersByWindowsAPI(std::list<std::wstring>* all_printers)
{
	DWORD Flags = PRINTER_ENUM_FAVORITE | PRINTER_ENUM_LOCAL;
	DWORD cbBuf;
	DWORD pcReturned ;

	DWORD Level = 2;
	TCHAR Name[512]={0} ;

	::EnumPrinters(Flags, Name, Level, NULL, 0, &cbBuf, &pcReturned);
	const LPPRINTER_INFO_2 pPrinterEnum = (LPPRINTER_INFO_2)LocalAlloc(LPTR, cbBuf + 4) ;

	if (!pPrinterEnum)
	{
		qDebug()<<"Error code is:"<<GetLastError();
	}

	if (!EnumPrinters(Flags, Name, Level, (LPBYTE)pPrinterEnum, cbBuf, &cbBuf, &pcReturned))
	{
		return ::GetLastError();
	}

	qDebug()<<"Number:"<<pcReturned;

	for(int index = 0; index < pcReturned; index++)
	{
		LPPRINTER_INFO_2 pInfo=&pPrinterEnum[index];
		all_printers->push_back(pInfo->pPrinterName);
	}
	LocalFree(pPrinterEnum);

	return ERROR_SUCCESS;
}

void PrinterManager::SetDefaultPrinterByQt(const QString& printer_name)
{
	//未找到相应方法
}

bool PrinterManager::SetDefaultPrinterByWindowsAPI(const std::wstring& printer_name)
{
	return SetDefaultPrinter(printer_name.c_str());
}

bool PrinterManager::PrinterFileByWindowsAPI(const std::wstring& file)
{
	int ret = (int)ShellExecuteW(NULL,
		L"print",
		file.c_str(),
		NULL,
		NULL,
		SW_HIDE);
	// if return number bigger than 31 indicate succ
	if (ret > SE_ERR_NOASSOC)
	{
		return true;
	}
	return false;
}
