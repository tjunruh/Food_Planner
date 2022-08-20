#pragma once
#ifndef __Printer_H
#define __Printer_h
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include "wx/print.h"
#include "wx/printdlg.h"

class QuickPrint : public wxPrintout {
	wxPageSetupDialogData page_setup;
	int orient;
	int max_x, max_y;
	int pageAmount;
	std::string message;

	static const int brush_size = 3;

public:
	QuickPrint(int pageAmount, wxString title);
	bool OnPrintPage(int pageNum);
	void preparePrint(const bool showPageSetupDialog = false);
	void OnBeginPrinting();
	wxPrintData getPrintData();
	bool OnBeginDocument(int startPage, int endPage);
	void GetPageInfo(int* minPage, int* maxPage, int* pageSelFrom, int* pageSelTo);
	bool HasPage(int pageNum);
	void OnEndPrinting();
	void setPrintText(std::string printMessage);
};
#endif