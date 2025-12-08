#pragma once
#include <wx/event.h>
#include <wx/wx.h>
#include <mine/MyFonts.h>
#include <mine/MyFlags.h>
#include <mine/MyColour.h>

typedef wxCommandEvent WXBTNEVT;

namespace Simple {
// ------------------------------------------------------------------------------
template<typename T>
static wxButton* Button(void(T::*fptr)(WXBTNEVT&), std::string value,
                        wxPanel* panel, wxBoxSizer* vbox, T* self) {
    auto btn = new wxButton(panel, wxID_ANY, wxString::FromUTF8(value));
    btn -> SetFont(font17);
    btn -> Bind(wxEVT_BUTTON,fptr,self);
    vbox -> Add(btn,FLAG_CENTER);
    return btn;
}
static wxButton* ShowButton(std::string showt, wxPanel* panel,
                            wxBoxSizer* vbox) {
    auto show = new wxButton(panel,wxID_ANY,wxString::FromUTF8(showt));
    show->SetFont(font15);
    show->SetForegroundColour(MyBlue);
    vbox->Add(show,FLAG_CENTER);
    vbox->AddStretchSpacer();
    return show;
}
static auto ShopButton(std::string value, wxPanel* panel,
                       wxColour colour ) -> wxButton* {
    auto btn = new wxButton(panel, wxID_ANY, wxString::FromUTF8(value));
    btn -> SetForegroundColour(colour);
    btn -> SetFont(font17);
    return btn;
}
template<typename T>
static auto BackButton(void(T::*fptr)(WXBTNEVT&), wxPanel* panel,
                       wxBoxSizer* vbox, T* self) -> void {
    vbox -> AddStretchSpacer();
    auto back_button = new wxButton(panel,wxID_ANY,wxT("返回"));
    back_button -> SetFont(font15);
    back_button -> Bind(wxEVT_BUTTON,fptr,self);
    vbox -> Add(back_button, FLAG_RIGHT);
    vbox -> AddStretchSpacer();
    panel -> SetSizer(vbox);
    panel -> Layout();
}
static wxButton* BasicButton(std::string value, wxPanel* panel) {
    auto btn = new wxButton(panel, wxID_ANY, wxString::FromUTF8(value));
    btn -> SetFont(font17);
    return btn;
}
static wxButton* Button(std::string value,
                        wxPanel* panel, wxBoxSizer* vbox) {
    auto btn = new wxButton(panel, wxID_ANY, wxString::FromUTF8(value));
    btn -> SetFont(font17);
    vbox -> Add(btn,FLAG_CENTER);
    return btn;
}
// ---------------------------------------------------------------------------------
template<typename T>
static auto Init(wxPanel* panel, T* self) -> wxBoxSizer* {
    self->clean_panel();
    return new wxBoxSizer(wxVERTICAL);
}
static auto Title(std::string titlea, wxPanel* panel,
                  wxBoxSizer* vbox) -> void {
    auto title = new wxStaticText(panel,wxID_ANY,wxString::FromUTF8(titlea));
    title -> SetFont(font25);
    vbox -> Add(title,FLAG_CENTER);
    vbox -> AddStretchSpacer();
}
static auto TitleNoSpacer(std::string titlea, wxPanel* panel,
                          wxBoxSizer* vbox) -> void {
    auto title = new wxStaticText(panel,wxID_ANY,wxString::FromUTF8(titlea));
    title -> SetFont(font25);
    vbox -> Add(title,FLAG_CENTER);
}
// -------------------------------------------------------------------------------
static auto Message(std::string msg) -> void {
    wxMessageBox(wxString::FromUTF8(msg));
}
static auto MessageErr(std::string msg) -> void {
    wxMessageBox(wxString::FromUTF8(msg), "err", wxOK | wxICON_ERROR );
}
static auto MessageQues(std::string msg) -> bool {
    return (
               wxMessageBox(wxString::FromUTF8(msg), "question",
                            wxYES_NO | wxICON_QUESTION) == wxYES
           );
}
}

