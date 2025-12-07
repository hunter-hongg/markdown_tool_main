#include <wx/wx.h>
#include <markdowntoolmain.hpp>

bool MyApp::OnInit()
{
    MyFrame *frame = new MyFrame("Basic wxWidgets Frame", wxDefaultPosition, wxSize(400, 300));
    frame->Show(true);
    return true;
}

MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
    : wxFrame(nullptr, wxID_ANY, title, pos, size)
{
    panel = new wxPanel(this, wxID_ANY);
}

void MyFrame::clean_panel()
{
    if (!panel) return;
    wxSizer* sizer = panel->GetSizer();
    if (!sizer) return;
    wxSizerItemList& items = sizer->GetChildren();
    for (wxSizerItemList::iterator it = items.begin(); it != items.end(); ++it) {
        wxSizerItem* item = *it;
        if (item->IsWindow()) {
            wxWindow* window = item->GetWindow();
            if (window) {
                if (wxStaticText* staticText = wxDynamicCast(window, wxStaticText)) {
                    staticText->SetLabel(wxT(""));
                }
            }
        }
    }
    sizer->Clear(true);
    panel->SetSizer(sizer);
    panel->Layout();
}

// IMPLEMENT_APP(MyApp)

// 2025年 08月 16日 星期六 08:33:01 CST
// 浙江台州

