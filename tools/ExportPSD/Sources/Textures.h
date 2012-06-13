#ifndef TEXTURES_H
#define TEXTURES_H

#include "Sprites.h"
#include "globals.h"


struct S_ImagePointer
{
	S_ImagePointer(T_Sprites::size_type iSprite, S_Sprite::T_Images::size_type iImage) : 
		iSprite(iSprite),
		iImage(iImage)
	{
	}

	T_Sprites::size_type iSprite; //����� �������
	S_Sprite::T_Images::size_type iImage; //����� ����������� � �������
};

//����� �������
class C_Textures
{
public:
	
	//������ ������ ��������� ��� ���������
	typedef std::vector< std::vector<CL_Vec2ui> > T_Nodes;
	//������ ������������� ���������� � ���� ������ ������
	typedef std::vector< std::vector<S_ImagePointer> > T_ConnectedKeys;

	//������������ ��������
	void ConnectTexture(S_ImagePointer p);

	//����������� ������������ ���������� �������
	size_t GetNumberTextures() const { return mNodes.size(); }

private:

	//������ ������������� ���������� � ���� ������ ������
	T_ConnectedKeys mConnectedKeys;
	//������ ������ ��������� ��� ���������
	T_Nodes mNodes;

private:

	void AddConnectedKey(T_ConnectedKeys::size_type iTexture, S_ImagePointer key)
	{
		if(iTexture > mConnectedKeys.size())
			PrintError("iTexture > mConnectedKeys.size()");

		if(iTexture == mConnectedKeys.size())
		{
			std::vector<S_ImagePointer> tempKeys;
			tempKeys.push_back(key);
			mConnectedKeys.push_back(tempKeys);
		}
		else
		{
			mConnectedKeys[iTexture].push_back(key);
		}
	}

};

//<������ ������������ �������, ��������� ��������� �� image>
typedef std::multimap<size_t, S_ImagePointer> T_SortedList;
extern T_SortedList sortedList;

extern C_Textures pngNodes;
extern C_Textures jpgNodes;

#endif // TEXTURES_H