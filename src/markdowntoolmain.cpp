#include "markdown_file.hpp"
#include "markdown_sqlite.hpp"
#include "mine/MyFlags.h"
#include "simple.hpp"
#include <cstdlib>
#include <memory>
#include <string>
#include <sys/stat.h>
#include <wx/event.h>
#include <wx/gdicmn.h>
#include <wx/gtk/listbox.h>
#include <wx/gtk/textctrl.h>
#include <wx/sizer.h>
#include <wx/wx.h>
#include <markdowntoolmain.hpp>
#include "fileselector.hpp"

MarkdownToolMainFrame::MarkdownToolMainFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
    : wxFrame(nullptr, wxID_ANY, title, pos, size)
{
    panel = new wxPanel(this, wxID_ANY);
    auto vbox = new wxBoxSizer(wxVERTICAL);
    panel -> SetSizer(vbox);
    auto EmptyEvent = wxCommandEvent();
    this -> connect_db();
    this -> start_panel(EmptyEvent);
}

void MarkdownToolMainFrame::clean_panel()
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

void MarkdownToolMainFrame::connect_db() {
    const char* home = getenv("home");
    mkdir(dbdir.data(), 0755);
    db_.set_database(dbpath.data());
    db_.safe_create_table();
}

void MarkdownToolMainFrame::start_panel(WXBTNEVT&) {
    auto vbox = Simple::Init(panel, this);

    Simple::Title("Markdown笔记管理工具", panel, vbox);

    Simple::Button(&MarkdownToolMainFrame::add_markdown, "添加笔记", panel, vbox, this);
    Simple::Button(&MarkdownToolMainFrame::search_markdown, "搜索笔记", panel, vbox, this);

    vbox -> AddStretchSpacer();
    auto back_button = new wxButton(panel,wxID_ANY,wxT("退出"));
    back_button -> SetFont(font17);
    back_button -> Bind(wxEVT_BUTTON, [=, this](WXBTNEVT&) {
        this -> Destroy();
    });
    vbox -> Add(back_button, FLAG_RIGHT);
    vbox -> AddStretchSpacer();
    panel -> SetSizer(vbox);
    panel -> Layout();
}

void MarkdownToolMainFrame::add_markdown(WXBTNEVT&) {
    auto vbox = Simple::Init(panel, this);

    Simple::Title("添加笔记", panel, vbox);

    auto btn1 = Simple::Button("选择笔记", panel, vbox);
    btn1 -> Bind(wxEVT_BUTTON, [=](WXBTNEVT&) {
        FileSelector f;
        auto path = f.OpenFile().ToStdString();
        if (path.empty()) {
            Simple::MessageErr("未选择文件");
            return;
        } else if ((!path.ends_with(".md")) && (!path.ends_with(".markdown"))) {
            Simple::MessageErr("不支持的文件格式");
            return;
        } else {
            MFile::File t(path, dbpath);
            t.into_database();
            Simple::Message("记录成功");
            AddedSignal.emit();
        }
    });

    Simple::BackButton(&MarkdownToolMainFrame::start_panel, panel, vbox, this);
}

void MarkdownToolMainFrame::search_markdown(WXBTNEVT&) {
    auto vbox = Simple::Init(panel, this);

    Simple::Title("搜索笔记", panel, vbox);

    auto tctrl1 = new wxTextCtrl(panel, wxID_ANY, L"请输入关键词...", wxDefaultPosition, wxSize(500, 30));
    tctrl1 -> SetFont(font19);
    vbox -> Add(tctrl1, FLAG_CENTER);

    auto sbmtbutton = new wxButton(panel, wxID_ANY, L"搜索");
    sbmtbutton -> SetFont(font19);
    vbox -> Add(sbmtbutton, FLAG_CENTER);

    auto ibox = new wxBoxSizer(wxVERTICAL);
    vbox -> Add(ibox, FLAG_CENTER);

    sbmtbutton -> Bind(wxEVT_BUTTON, [=, this](WXBTNEVT&) {
        std::string keyword = tctrl1 -> GetValue().ToUTF8().data();
        ibox -> Clear(true);
        // std::cout << keyword << std::endl;
        auto sresult = db_.search_keyword(keyword);
        // std::cout << sresult.size() << std::endl;
        int count = 0;
        for(const auto& i: sresult) {
            auto btn = new wxButton(panel, wxID_ANY, wxString::FromUTF8(i.first));
            btn -> SetFont(font17);
            btn -> Bind(wxEVT_BUTTON, [=, this](WXBTNEVT&) {
                show_markdown(i.second);
            });
            ibox -> Add(btn, FLAG_CENTER);
            count++;
            if(count > 10) break;
        }
    });

    Simple::BackButton(&MarkdownToolMainFrame::start_panel, panel, vbox, this);
}

void MarkdownToolMainFrame::show_markdown(std::string to_show) {
    auto vbox = Simple::Init(panel, this);

    Simple::Title("笔记呈现", panel, vbox);

    wxTextCtrl* textCtrl = new wxTextCtrl(
        panel,                      // 父窗口
        wxID_ANY,                  // ID
        "",                        // 初始文本
        wxDefaultPosition,         // 位置
        wxSize(500, 500),          // 大小
        wxTE_MULTILINE |           // 允许多行
        wxTE_READONLY |            // 只读（如果仅显示）
        wxTE_RICH2 |               // 增强的文本控件
        wxTE_AUTO_URL |            // 自动识别URL
        wxHSCROLL |                // 水平滚动条
        wxVSCROLL                  // 垂直滚动条
    );
    textCtrl -> SetValue(wxString::FromUTF8(to_show));
    textCtrl -> SetFont(font15);
    vbox -> Add(textCtrl, FLAG_CENTER);

    Simple::BackButton(&MarkdownToolMainFrame::search_markdown, panel, vbox, this);
}
// IMPLEMENT_APP(MyApp)

// 2025年 08月 16日 星期六 08:33:01 CST
// 浙江台州

