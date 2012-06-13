#ifndef SPRITES_H
#define SPRITES_H

#include "globals.h"


//���� ��������
enum E_Scussored
{
	SCISSORED_NONE = 0,
	SCISSORED_LEFT,
	SCISSORED_CENTER,
	SCISSORED_RIGHT

};

//��������
struct S_Collision
{
	S_Collision(CL_String collisionName = "bitmaps") :
		mFileOffset(0)
	{
		SetCollisionName(collisionName);
	}

	void SetCollisionName(CL_String collisionName)
	{
		mCollisionName = collisionName;
		mCollisionFileName = mCollisionName + ".bin";
	}

	const CL_String & GetCollisionName() const
	{
		return mCollisionName;
	}

	const CL_String & GetCollisionFileName() const
	{
		return mCollisionFileName;
	}

	int mFileOffset; //�������� � ����� ��������

private:
	CL_String mCollisionName; //��� ��������
	CL_String mCollisionFileName; //��� ����� ��� ���������� ���������� � ���������

};

//ClanLib ������ ����������� image
struct S_Image
{
	S_Image(CL_String sourceFileName) :
		mSourceFileName(sourceFileName),
		mDelay(0)
	{
	}

	//������� ������
	CL_String mSourceFileName; //��� ����� ��������� �����������
	int mDelay; //�������� ����� (��� ��������)
	CL_Vec2i mOffset; //�������� ������������ ������� ������� (��� ��������)

	//�������������
	CL_String mSourceFullName; //������ ��� ����� �����������
	CL_PixelBuffer mImage; //�������� �����������
	S_Collision mCollision; //���������� � ��������
	bool mNoTransparent; //�������� ��������� ������������
	
	//��������
	size_t mITexture; //����� �����-�������� ��� ����������
	CL_Rect mSrcRect; //SrcRect � ���������� ������
	CL_Rect mDeltaGrid; //�������� �����
};
//ClanLib ������ ����������� �������
struct S_Sprite
{
	S_Sprite(CL_String name, CL_Vec2i pos) : 
		mName(name),
		mPos(pos),
		mIsFrame(false)
	{
	}

	//������� ������
	CL_String mName; //��� ������� � �������
	CL_Vec2i mPos; //������� ��� ��������� �� ������
	typedef std::vector<S_Image> T_Images;
	T_Images mImages; //������ ��������
	bool mIsFrame; //���� �� ���������� ��������

	void AddImage(CL_String sourceFileName)
	{
		mImages.push_back(S_Image(sourceFileName));
	}

	bool SetAnimationsParam(size_t i, int delay, CL_Vec2i offset)
	{
		if(i >= mImages.size())
			return false;

		mIsFrame = true; //������ ������ - ������������
		mImages[i].mDelay = delay;
		mImages[i].mOffset = offset;
		return true;
	}
};

typedef std::vector<S_Sprite> T_Sprites;
//���������� ������ ��������
extern T_Sprites sprites;


#endif // SPRITES_H