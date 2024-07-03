#pragma once
class CMusicPlayer
{
private:
	/*
	* filePath        保存文件路径
	* mciCommand      保存mci命令字符串
	* fileLength      存储当前播放音频总长度
	* currentPosition 存储当前播放位置
	* isPlay		  当前是否播放
	* alias			  文件别名
	* soundSize		  声音大小0-1000
	* 函数:
	* 
	* LoadFile		  加载音频位置
	* GetLength		  获取音频长度并返回
	* GetCurPosition  获取当前播放位置并返回
	* Play			  播放
	* Stop			  停止
	* Pause			  暂停
	* SetVolue		  设置声音大小
	* SetPosition     实现更改当前播放位置(基于currentPosition)
	* SetCurrentPosition设置当前播放位置(改变currentPosition)
	* ISPlay		  判断是否播放
	* SetSoudSize	  更改soundSize声音的值
	* GetSoundMax	  获取声音设置的最大值
	*/
	CString filePath;
	CString mciCommand; 
	CString alias;
	int soundSize;
	long int fileLength;
	long int currentPosition;
	bool isPlay;
public:
	int soudMax;
	void LoadFile(CString&);
	long int GetLength();
	long int GetCurPosition();
	void Play();
	void Stop();
	void Pause();
	void SetVolume();
	void SetPosition();
	void SetCurrentPosition(int curPosition);
	bool ISPlay();
	void SetSoudSize(int);
	int GetSoundMax();
};

