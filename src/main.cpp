#include <wx/wx.h>
#include <markdowntoolmain.hpp>

bool MyApp::OnInit()
{
    MarkdownToolMainFrame *frame = new MarkdownToolMainFrame("Basic wxWidgets Frame", wxDefaultPosition, wxSize(600, 600));
    frame->Show(true);
    return true;
}

wxIMPLEMENT_APP(MyApp);

