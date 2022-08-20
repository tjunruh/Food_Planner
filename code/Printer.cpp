#include "Printer.h"

QuickPrint::QuickPrint(int pageAmount, wxString title) : wxPrintout(title)
    {
        QuickPrint::pageAmount = pageAmount;
        orient = wxPORTRAIT;
    }

    /** called by wx everytime it's time to render a specific page onto the printing device context */
    bool QuickPrint::OnPrintPage(int pageNum)
    {
        wxDC* ptr = GetDC();
        if (ptr == NULL or !ptr->IsOk())
        {
            return false;
        }
        wxDC& dc = *ptr;
        wxFont PrinterFont = wxFont(wxFontInfo(8));
        PrinterFont.SetFamily(wxFONTFAMILY_TELETYPE);
        // get bounds information, to know where to render stuff
        wxRect bounds = GetLogicalPageRect();
        const int x0 = bounds.x;
        const int y0 = bounds.y;
        const int width = bounds.width;
        const int height = bounds.height;

        const int center_x = x0 + width / 2;
        const int center_y = y0 + height / 2;

        dc.Clear();

        dc.SetPen(wxPen(wxColour(0, 0, 0), brush_size));
        dc.SetBrush(*wxTRANSPARENT_BRUSH);
        dc.SetFont(PrinterFont);
        dc.SetTextBackground(wxColour(255, 255, 0));
        dc.SetTextForeground(wxColour(0, 0, 0));
        dc.DrawText(message, x0 + 25, y0 + 25);

        return true;
    }

    void QuickPrint::setPrintText(std::string printMessage) {
        message = printMessage;
    }

    /** shows the page setup dialog, OR sets up defaults */
    void QuickPrint::preparePrint(const bool showPageSetupDialog)
    {
        if (showPageSetupDialog)
        {
            wxPageSetupDialog dialog(NULL);
            if (dialog.ShowModal() == wxID_OK)
            {
                page_setup = dialog.GetPageSetupData();
                orient = page_setup.GetPrintData().GetOrientation();
            }
            else
            {
                exit(1);
            }
        }
        else
        {
            // don't show page setup dialog, use default values
            wxPrintData printdata;
            printdata.SetPrintMode(wxPRINT_MODE_PRINTER);
            printdata.SetOrientation(wxPORTRAIT); // wxPORTRAIT, wxLANDSCAPE
            printdata.SetNoCopies(1);

            page_setup = wxPageSetupDialogData(printdata);
            orient = printdata.GetOrientation();
        }
    }

    /** Called when printing starts */
    void QuickPrint::OnBeginPrinting()
    {
        // set-up coordinate system however we want
        // we'll use it when drawing

        // here i'm using arbitrary an size, use whatever you wish
        if (orient == wxPORTRAIT)
        {
            max_x = 680;
            max_y = 880;
        }
        else
        {
            max_x = 880;
            max_y = 680;
        }

        FitThisSizeToPageMargins(wxSize(max_x, max_y), page_setup);
    }

    /** returns the data obtained from the page setup dialog (or the defaults, if dialog was not shown) */
    wxPrintData QuickPrint::getPrintData()
    {
        return page_setup.GetPrintData();
    }

    /** Called when starting to print a document */
    bool QuickPrint::OnBeginDocument(int startPage, int endPage)
    {
        return wxPrintout::OnBeginDocument(startPage, endPage);
    }

    /** wx will call this to know how many pages can be printed */
    void QuickPrint::GetPageInfo(int* minPage, int* maxPage, int* pageSelFrom, int* pageSelTo)
    {
        *minPage = 1;
        *maxPage = pageAmount;

        *pageSelFrom = 1;
        *pageSelTo = pageAmount;
    }

    /** called by wx to know what pages this document has */
    bool QuickPrint::HasPage(int pageNum)
    {
        // wx will call this to know how many pages can be printed
        if (pageNum >= 1 and pageNum <= pageAmount)
            return true;
        else
            return false;
    }

    /** Called when printing is done. I have nothing to do in this case in this example. */
    void QuickPrint::OnEndPrinting()
    {
    }
