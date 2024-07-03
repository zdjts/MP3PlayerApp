#pragma once
#include <map>
#include <fstream>
/*
* filePathMap		存储文件名与路径关系
* filePath			存储文件路径
* 
* OpenFileDialog	启动打开单个文件对话框
* LoadNMusic		启动打开多个文件对话框
* GetPathName		通过文件地址得到文件名
* LoadInFileMusic	加载位于文件中的音乐到filePathMap
* NewLoadInFileMusic保存filePathMap到文件中
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

