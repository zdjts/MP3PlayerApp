#include "pch.h"
#include "CMusicPlayer.h"
#include <mmsystem.h>
void CMusicPlayer::LoadFile(CString& Path)
{
	if (isPlay)
	{
		mciCommand.Format(_T("close %s"), alias);
		MCIERROR mciErrorCode = mciSendString(mciCommand, NULL, 0, NULL);
		if (mciErrorCode != 0)
		{
			return;
			TCHAR errorText[128];
			mciGetErrorString(mciErrorCode, errorText, 128);
			AfxMessageBox(errorText, MB_OK | MB_ICONERROR);
			return;
		}
	}
	filePath = Path;
	mciCommand.Format(_T("open \"%s\" type mpegvideo alias mp3file"), filePath);
	alias = _T("mp3file");
	MCIERROR mciErrorCode = mciSendString(mciCommand, NULL, 0, NULL);
	if (mciErrorCode != 0)
	{
		return;
		TCHAR errorText[128];
		mciGetErrorString(mciErrorCode, errorText, 128);
		AfxMessageBox(errorText, MB_OK | MB_ICONERROR);
		return;
	}
	TCHAR returnString[128];
	mciErrorCode = mciSendString(_T("status mp3file length"), returnString, sizeof(returnString), NULL);
	if (mciErrorCode == 0) 
	{
		fileLength = _ttoi(returnString); // ���ַ���ת��Ϊ��������ʾ��Ƶ���ȣ����룩
	}
	else 
	{
		return;
		TCHAR errorText[128];
		mciGetErrorString(mciErrorCode, errorText, 128);
		AfxMessageBox(errorText, MB_OK | MB_ICONERROR);
		fileLength = 0;
	}
	Play();
}

long int CMusicPlayer::GetLength()
{
	return fileLength;
}

long int CMusicPlayer::GetCurPosition()
{
	MCIERROR mciErrorCode;
	TCHAR returnString[128];
	mciCommand.Format(_T("status %s position"), alias);
	mciErrorCode = mciSendString(mciCommand, returnString, sizeof(returnString), NULL);
	if (mciErrorCode != 0) 
	{
		TCHAR errorText[128];
		mciGetErrorString(mciErrorCode, errorText, 128);
		AfxMessageBox(errorText, MB_OK | MB_ICONERROR);
		return -1;
	}

	// �����صĺ�����ת��Ϊ��
	long positionMilliseconds = _ttol(returnString);
	currentPosition = positionMilliseconds;
	return positionMilliseconds;
}

void CMusicPlayer::Play()
{
	MCIERROR mciError = mciSendString(_T("play mp3file"), NULL, 0, NULL);
	if (mciError != 0) {
		TCHAR errorText[128];
		mciGetErrorString(mciError, errorText, 128);
		AfxMessageBox(errorText, MB_OK | MB_ICONERROR);
		isPlay = FALSE;
	}
	else {
		isPlay = TRUE;
	}
}

void CMusicPlayer::Stop()
{
	MCIERROR mciError;

	// ������ͣ���ŵ�MCI����

	mciCommand.Format(_T("pause %s"), alias);

	// ����MCI����
	mciError = mciSendString(mciCommand, NULL, 0, NULL);
	if (mciError != 0) 
	{
		TCHAR errorText[128];
		mciGetErrorString(mciError, errorText, 128);
		AfxMessageBox(errorText, MB_OK | MB_ICONERROR);
		return;
	}
	isPlay = FALSE;
}

void CMusicPlayer::Pause()
{
	MCIERROR mciError;

	// ����ֹͣ���ŵ�MCI����
	mciCommand.Format(_T("stop %s"), alias);
	isPlay = FALSE;
	// ����ֹͣ���ŵ�MCI����
	mciError = mciSendString(mciCommand, NULL, 0, NULL);
	if (mciError != 0) {
		TCHAR errorText[128];
		mciGetErrorString(mciError, errorText, 128);
		AfxMessageBox(errorText, MB_OK | MB_ICONERROR);
		return;
	}

	// ����ر��ļ���MCI����
	mciCommand.Format(_T("close %s"), alias);

	// ���͹ر��ļ���MCI����
	mciError = mciSendString(mciCommand, NULL, 0, NULL);
	if (mciError != 0) {
		TCHAR errorText[128];
		mciGetErrorString(mciError, errorText, 128);
		AfxMessageBox(errorText, MB_OK | MB_ICONERROR);
	}
}

void CMusicPlayer::SetVolume()
{
	MCIERROR mciError;
	if (soundSize < 0)
	{
		soundSize = 0;
	}
	if (soundSize > soudMax)
	{
		soundSize = soudMax;
	}
	if (ISPlay() == true)
	{
		mciCommand.Format(_T("setaudio %s volume to %d"), alias, soundSize);
		mciError = mciSendString(mciCommand, NULL, 0, NULL);
		if (mciError != 0)
		{
			TCHAR errorText[128];
			mciGetErrorString(mciError, errorText, 128);
			AfxMessageBox(errorText, MB_OK | MB_ICONERROR);
		}
	}

	return;
}

void CMusicPlayer::SetPosition()
{
	
	mciCommand.Format(_T("seek mp3file to %d"), currentPosition); // λ���Ժ���Ϊ��λ
	MCIERROR mciError = mciSendString(mciCommand, NULL, 0, NULL);

	if (mciError != 0)
	{
		TCHAR errorText[128];
		mciGetErrorString(mciError, errorText, 128);
		AfxMessageBox(errorText, MB_OK | MB_ICONERROR);
	}
}

void CMusicPlayer::SetCurrentPosition(int curPosition)
{
	currentPosition = curPosition;
}

bool CMusicPlayer::ISPlay()
{
	return isPlay;
}

void CMusicPlayer::SetSoudSize(int n)
{
	soundSize = n;
}

int CMusicPlayer::GetSoundMax()
{
	return soudMax;
}

