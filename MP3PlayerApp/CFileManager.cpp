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
            // ��ȡ��һ���ļ���·��
            CString firstFilePath = dlg.GetPathName();
            filePathMap[GetPathName(firstFilePath)] = firstFilePath; // �洢��һ���ļ�����·��

            // ��λ���ڶ����ļ�������еĻ���
            POSITION pos = dlg.GetStartPosition();
            while (pos != NULL)
            {
                // ��ȡ��һ���ļ���·��
                CString nextFilePath = dlg.GetNextPathName(pos);
                // ��·������ȡ�ļ���
                CString fileName = GetPathName(nextFilePath);
                // ���ļ�����·������ map
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

        // ����ҵ��˷ָ�������ȡ�ļ���
        if (lastSlashIndex != -1)
        {
            // fullPath �д����һ���ָ�����������ַ������ļ���
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
        // �����ļ��޷��򿪵����
        return;
    }

    CString ca, cb;
    std::string a, b;

    while (file >> a >> b)
    {
        ca = a.c_str(); // ת�� std::string �� CString
        cb = b.c_str(); // ת�� std::string �� CString
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
        // �����ļ��޷��򿪵����
        return;
    }

    for (auto& i : filePathMap)
    {
        std::string key = CT2A(i.first.GetString());  // �� CString ת��Ϊ std::string
        std::string value = CT2A(i.second.GetString()); // �� CString ת��Ϊ std::string
        file << key << " " << value << std::endl;
    }
    file.close();
}
