#include <wx/wx.h>
#include <wx/filedlg.h>

class FileSelector
{
public:
    // 打开单个文件
    static wxString OpenFile(wxWindow* parent = nullptr,
                             const wxString& title = "打开文件",
                             const wxString& defaultDir = "",
                             const wxString& defaultFile = "",
                             const wxString& wildcard = "所有文件 (*.*)|*.*")
    {
        wxFileDialog dialog(parent, title, defaultDir, defaultFile,
                            wildcard, wxFD_OPEN | wxFD_FILE_MUST_EXIST);

        if (dialog.ShowModal() == wxID_OK)
        {
            return dialog.GetPath();
        }

        return wxEmptyString; // 用户取消了选择
    }

    // 打开多个文件
    static bool OpenMultipleFiles(wxArrayString& paths,
                                  wxWindow* parent = nullptr,
                                  const wxString& title = "打开多个文件",
                                  const wxString& defaultDir = "",
                                  const wxString& defaultFile = "",
                                  const wxString& wildcard = "所有文件 (*.*)|*.*")
    {
        wxFileDialog dialog(parent, title, defaultDir, defaultFile,
                            wildcard, wxFD_OPEN | wxFD_FILE_MUST_EXIST | wxFD_MULTIPLE);

        if (dialog.ShowModal() == wxID_OK)
        {
            dialog.GetPaths(paths);
            return true;
        }

        return false;
    }

    // 保存文件
    // static wxString SaveFile(wxWindow* parent = nullptr,
    //                          const wxString& title = "保存文件",
    //                          const wxString& defaultDir = "",
    //                          const wxString& defaultFile = "",
    //                          const wxString& wildcard = "所有文件 (*.*)|*.*")
    // {
    //     wxFileDialog dialog(parent, title, defaultDir, defaultFile,
    //                         wildcard, wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
    //
    //     if (dialog.ShowModal() == wxID_OK)
    //     {
    //         wxString path = dialog.GetPath();
    //         // 自动添加扩展名
    //         int filterIndex = dialog.GetFilterIndex();
    //         if (filterIndex == 0 && !path.Contains("."))
    //         {
    //             path += GetDefaultExtension(wildcard, filterIndex);
    //         }
    //         return path;
    //     }
    //
    //     return wxEmptyString;
    // }

private:
    // static wxString GetDefaultExtension(const wxString& wildcard, int index)
    // {
    //     // 从通配符字符串中提取扩展名
    //     wxArrayString extensions;
    //     wxStringTokenizer tkz(wildcard, "|");
    //
    //     while (tkz.HasMoreTokens())
    //     {
    //         wxString token = tkz.GetNextToken();
    //         if (token.Contains("*."))
    //         {
    //             extensions.Add(token.AfterFirst('*'));
    //         }
    //     }
    //
    //     if (index < (int)extensions.size())
    //     {
    //         return extensions[index];
    //     }
    //
    //     return ".txt"; // 默认扩展名
    // }
};
