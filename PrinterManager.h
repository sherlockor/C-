#ifndef PRINTERMANAGER_H
#define PRINTERMANAGER_H

#include <QObject>
#include <QList>

#include <list>

class PrinterManager : public QObject
{
	Q_OBJECT

public:
	PrinterManager(QObject *parent);
	~PrinterManager();

public:
	/*
	 * @brief	使用Qt的方法得到当前计算机的默认打印机
	 * @return	默认打印机的名称
	 */
	static QString GetDefaultPrinterByQt();

	/*
	 * @brief		使用Windows API获取当前计算机的默认打印机
	 * @param[out]	printer_name 默认打印机名称
	 * return		0:pass;非0:查询windows API的错误信息
	 */
	static int GetDefaultPrinterByWindowsAPI(std::wstring* printer_name);

	/*
	 * @brief		使用Qt的方法获取当前计算机上的所有打印机
	 * @param[out]	all_printer	打印机列表
	 */
	static void GetAllPrintersByQt(QList<QString>* all_printers);

	/*
	 * @brief		使用windows API的方法获取当前计算机上的所有打印机
	 * @param[out]	all_printers	打印机列表
	 * return		0:pass;非0:查询windows API的错误信息
	 */
	static int GetAllPrintersByWindowsAPI(std::list<std::wstring>* all_printers);
	
	/*
	 * @brief		使用Qt的方法设置当前默认的打印机
	 * @param[in]	printer_name	打印机名称
	 * @note		未实现	
	 */
	static void SetDefaultPrinterByQt(const QString& printer_name);

	/*
	 * @brief		使用windows API设置当前的默认打印机
	 * @param[in]	printer_name	打印机名称
	 */
	static bool SetDefaultPrinterByWindowsAPI(const std::wstring& printer_name);

	/*
	 * @brief		使用windows API打印文件，使用默认打印机
	 * @param[in]	file	需要打印的文件
	 */
	static bool PrinterFileByWindowsAPI(const std::wstring& file);
};

#endif // PRINTERMANAGER_H
