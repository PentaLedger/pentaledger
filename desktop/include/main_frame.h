#ifndef MAIN_FRAME_H
#define MAIN_FRAME_H

#include <wx/wx.h>

class MainFrame : public wxFrame
{
public:
    MainFrame();

private:
    void OnHello(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);

    wxDECLARE_EVENT_TABLE();
};

#endif // MAIN_FRAME_H 