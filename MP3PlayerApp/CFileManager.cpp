#include "pch.h"
#include "CFileManager.h"
#include <iostream>
CFileManager::CFileManager(CString path)
{
    filePath = path;
}
CString CFileManager::OpenFileDialog()
{
    CFileDialog dlg(TRUE, _T("mp3"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("MP3 Files (*.mp3)|*.mp3||"));
    if (dlg.DoModal() == IDOK)
    {
        filePathMap[GetPathName(dlg.GetPathName())] = dlg.GetPathName();
        void NewLoadInFileMusic();
        return dlg.GetPathName();
    }
    return _T("");
}

void CFileManager::LoadNMusic()
{
    {
        CFileDialog dlg(TRUE, _T("mp3"), NULL,
            OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_ALLOWMULTISELECT,
            _T("MP3 Files (*.mp3)|*.mp3||"));

        if (dlg.DoModal() == IDOK)
        {
            // 获取第一个文件的路径
            CString firstFilePath = dlg.GetPathName();
            filePathMap[GetPathName(firstFilePath)] = firstFilePath; // 存储第一个文件名和路径

            // 定位到第二个文件（如果有的话）
            POSITION pos = dlg.GetStartPosition();
            while (pos != NULL)
            {
                // 获取下一个文件的路径
                CString nextFilePath = dlg.GetNextPathName(pos);
                // 从路径中提取文件名
                CString fileName = GetPathName(nextFilePath);
                // 将文件名和路径存入 map
                filePathMap[fileName] = nextFilePath;
            }
        }
    }
}
CString CFileManager::GetPathName(CString Path)
{
    if (!Path.IsEmpty())
    {
        int lastSlashIndex = Path.ReverseFind(_T('\\'));

        // 如果找到了分隔符，提取文件名
        if (lastSlashIndex != -1)
        {
            // fullPath 中从最后一个分隔符后的所有字符都是文件名
            CString fileName = Path.Mid(lastSlashIndex + 1);
            return fileName;
        }
    }
    return _T("");
}

void CFileManager::LoadInFileMusic()
{
    std::fstream file;
    file.open(filePath, std::ios::in);
    if (!file.is_open())
    {
        // 处理文件无法打开的情况
        return;
    }

    CString ca, cb;
    std::string a, b;

    while (file >> a >> b)
    {
        ca = a.c_str(); // 转换 std::string 到 CString
        cb = b.c_str(); // 转换 std::string 到 CString
        filePathMap[ca] = cb;
    }

    file.close();
}

void CFileManager::NewLoadInFileMusic()
{
    std::fstream file;
    file.open(filePath, std::ios::out | std::ios::trunc);
    if (!file.is_open())
    {
        // 处理文件无法打开的情况
        return;
    }

    for (auto& i : filePathMap)
    {
        std::string key = CT2A(i.first.GetString());  // 将 CString 转换为 std::string
        std::string value = CT2A(i.second.GetString()); // 将 CString 转换为 std::string
        file << key << " " << value << std::endl;
    }
    file.close();
}
