#include <wx/wx.h>
#include "main_frame.h"

class PentaLedgerApp : public wxApp
{
public:
    virtual bool OnInit();
};

wxIMPLEMENT_APP(PentaLedgerApp);

bool PentaLedgerApp::OnInit()
{
    if (!wxApp::OnInit())
        return false;

    MainFrame *frame = new MainFrame();
    frame->Show(true);
    return true;
} 