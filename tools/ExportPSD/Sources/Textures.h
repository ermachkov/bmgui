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

	T_Sprites::size_type iSprite; //номер спрайта
	S_Sprite::T_Images::size_type iImage; //номер изображения в спрайте
};

//класс текстур
class C_Textures
{
public:
	
	//списки вершин свободных для крепления
	typedef std::vector< std::vector<CL_Vec2ui> > T_Nodes;
	//список прикрепленных подтекстур в виде списка ключей
	typedef std::vector< std::vector<S_ImagePointer> > T_ConnectedKeys;

	//прикрепление текстуры
	void ConnectTexture(S_ImagePointer p);

	//определение необходимого количества текстур
	size_t GetNumberTextures() const { return mNodes.size(); }

private:

	//список прикрепленных подтекстур в виде списка ключей
	T_ConnectedKeys mConnectedKeys;
	//списки вершин свободных для крепления
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

//<размер максимальной стороны, индексный указатель на image>
typedef std::multimap<size_t, S_ImagePointer> T_SortedList;
extern T_SortedList sortedList;

extern C_Textures pngNodes;
extern C_Textures jpgNodes;

#endif // TEXTURES_H