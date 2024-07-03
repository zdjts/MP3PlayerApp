#pragma once
#include <map>
#include <fstream>
/*
* filePathMap		�洢�ļ�����·����ϵ
* filePath			�洢�ļ�·��
* 
* OpenFileDialog	�����򿪵����ļ��Ի���
* LoadNMusic		�����򿪶���ļ��Ի���
* GetPathName		ͨ���ļ���ַ�õ��ļ���
* LoadInFileMusic	����λ���ļ��е����ֵ�filePathMap
* NewLoadInFileMusic����filePathMap���ļ���
*/
class CFileManager
{
	CString filePath;
public:
	std::map<CString, CString> filePathMap;
	CFileManager(CString path = _T("musicFilePath.txt"));
	CString OpenFileDialog();
	void LoadNMusic();
	CString GetPathName(CString Path);
	void LoadInFileMusic();
	void NewLoadInFileMusic();
};

