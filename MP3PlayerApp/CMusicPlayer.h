#pragma once
class CMusicPlayer
{
private:
	/*
	* filePath        �����ļ�·��
	* mciCommand      ����mci�����ַ���
	* fileLength      �洢��ǰ������Ƶ�ܳ���
	* currentPosition �洢��ǰ����λ��
	* isPlay		  ��ǰ�Ƿ񲥷�
	* alias			  �ļ�����
	* soundSize		  ������С0-1000
	* ����:
	* 
	* LoadFile		  ������Ƶλ��
	* GetLength		  ��ȡ��Ƶ���Ȳ�����
	* GetCurPosition  ��ȡ��ǰ����λ�ò�����
	* Play			  ����
	* Stop			  ֹͣ
	* Pause			  ��ͣ
	* SetVolue		  ����������С
	* SetPosition     ʵ�ָ��ĵ�ǰ����λ��(����currentPosition)
	* SetCurrentPosition���õ�ǰ����λ��(�ı�currentPosition)
	* ISPlay		  �ж��Ƿ񲥷�
	* SetSoudSize	  ����soundSize������ֵ
	* GetSoundMax	  ��ȡ�������õ����ֵ
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

