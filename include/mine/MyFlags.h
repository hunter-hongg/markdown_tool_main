#pragma once
#include <wx/wx.h>

static const auto FLAG_CENTER=wxSizerFlags(0).Border(wxALL, 10).Align(wxALIGN_CENTER);
static const auto FLAG_RIGHT=wxSizerFlags(0).Border(wxALL, 10).Align(wxALIGN_RIGHT);
static const auto FLAG_LEFT=wxSizerFlags(0).Border(wxALL, 10).Align(wxALIGN_LEFT);
static const auto FLAG_CENTER_NOBORDER=wxSizerFlags(0).Border(wxALL, 0).Align(wxALIGN_CENTER);

