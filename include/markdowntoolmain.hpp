#include "sigc++/signal.h"
#include "simple.hpp"
#include <cstdlib>
#include <memory>
#include <wx/gdicmn.h>
#include <wx/wx.h>
#include <markdown_parser.hpp>
#include <markdown_sqlite.hpp>
#include <markdown_file.hpp>
#include <sigc++/sigc++.h>

inline const char* home = getenv("HOME");
inline const std::string dbdir = std::string(home) + "/.local/share/markdowntool";
inline const std::string dbpath = dbdir + "/AllMarkdown.db";

inline sigc::signal<void()> AddedSignal;

class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};

class MarkdownToolMainFrame : public wxFrame
{
public:
    MarkdownToolMainFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
    void clean_panel();
private:
    wxPanel* panel;
    MSQLite::Database db_;

    void connect_db();

    void start_panel(WXBTNEVT&);
    void add_markdown(WXBTNEVT&);
    void search_markdown(WXBTNEVT&);
    void show_markdown(std::string);
};

