#include "Textures.h"

T_SortedList sortedList;

C_Textures pngNodes;
C_Textures jpgNodes;

/*
	//bool is_next = false; //���� �������������


*/
void C_Textures::ConnectTexture(S_ImagePointer p)
{
	//������� ������������ ��������������
	size_t w = sprites[p.iSprite].mImages[p.iImage].mImage.get_width();
	size_t h = sprites[p.iSprite].mImages[p.iImage].mImage.get_height();
	//����� ����������� ���� ��� ��������� �������
	T_Nodes::size_type nTexture = mNodes.size();
	for(T_Nodes::size_type iTexture = 0; iTexture < nTexture; ++iTexture)
	{
		//TODO:
		//�������� ����� ������� ��� �������
		//bool isHi = h>w ? true : false;

		std::vector<CL_Vec2ui>::size_type nNode = mNodes[iTexture].size();
		for(std::vector<CL_Vec2ui>::size_type iNode = 0; iNode < nNode ; ++iNode)
		{
			//������������ ��������� ������ Rect
			CL_Rect candidate;
			candidate.left = mNodes[iTexture][iNode].x;
			candidate.top = mNodes[iTexture][iNode].y;
			candidate.right = w + candidate.left;
			candidate.bottom = h + candidate.top;
			
			//�������� �� ����������� � ����������� ������������� �������
			bool isIntersection = false;
			//������ �� ���������� ����������� ��������
			std::vector<T_Sprites::size_type>::size_type nConnectedKeys = mConnectedKeys[iTexture].size();
			for(std::vector<T_Sprites::size_type>::size_type iConnectedSprites = 0; iConnectedSprites < nConnectedKeys; ++iConnectedSprites)
			{
				//�������� �� ����������� ������ � ������� ��������
				if( candidate.is_overlapped( CL_Rect(
					  sprites[ mConnectedKeys[iTexture][iConnectedSprites].iSprite ].mImages[mConnectedKeys[iTexture][iConnectedSprites].iImage ].mSrcRect.left - ADDING_BORDER
					, sprites[ mConnectedKeys[iTexture][iConnectedSprites].iSprite ].mImages[mConnectedKeys[iTexture][iConnectedSprites].iImage ].mSrcRect.top - ADDING_BORDER
					, sprites[ mConnectedKeys[iTexture][iConnectedSprites].iSprite ].mImages[mConnectedKeys[iTexture][iConnectedSprites].iImage ].mSrcRect.right + ADDING_BORDER
					, sprites[ mConnectedKeys[iTexture][iConnectedSprites].iSprite ].mImages[mConnectedKeys[iTexture][iConnectedSprites].iImage ].mSrcRect.bottom + ADDING_BORDER) ) )
					isIntersection = true;
			}
			
			//�������� �� ����������� � ������� ��������
			bool isOutBorder = false;
			if(	candidate.right > MAX_WIDTH ||
				candidate.bottom > MAX_HEIGHT )
				isOutBorder = true;
				
			if(!isIntersection && !isOutBorder)
			{
				//���������� ����������� �������
				//������������ ������ ����������� ��������
				sprites[p.iSprite].mImages[p.iImage].mITexture = iTexture;
				//���� ��� ����������
				CL_Rect add;
				add.left = mNodes[iTexture][iNode].x;
				add.top = mNodes[iTexture][iNode].y;
				add.right = w + add.left;
				add.bottom = h + add.top;
				//������������
				sprites[p.iSprite].mImages[p.iImage].mSrcRect = add;
				//������������ ����� � ������
				AddConnectedKey(iTexture, p);

				//�������� �������
				mNodes[iTexture].erase( mNodes[iTexture].begin()+iNode );

				//���������� ������� ������-������
				if(add.right+ADDING_BORDER < MAX_WIDTH && add.top+ADDING_BORDER < MAX_HEIGHT)
					mNodes[iTexture].insert( mNodes[iTexture].begin()+iNode, CL_Vec2ui(add.right+ADDING_BORDER, add.top) );
		
				//���������� ������� �����-�����
				if(add.left+ADDING_BORDER < MAX_WIDTH && add.bottom+ADDING_BORDER < MAX_HEIGHT)
					mNodes[iTexture].insert( mNodes[iTexture].begin()+iNode, CL_Vec2ui(add.left, add.bottom+ADDING_BORDER) );

				return;
			}
		}
	}

	//���� �������� �� �����������, �� ������� ����� �������� � ����� ����� � ���������� �� ����
	//������������ ����� � ������
	AddConnectedKey(nTexture, p);
	//���������� ����� �������� - ������ ������
	mNodes.push_back( std::vector<CL_Vec2ui>() );
	//���������� ������ ������� � ����� �������� - ������ ������
	(mNodes.end()-1)->push_back( CL_Vec2ui(0, 0) );

	//���������� �����������
	T_Nodes::size_type iTexture = mNodes.size() - 1;
	std::vector<CL_Vec2ui>::size_type iNode = 0;
	//������������ ������ ����������� ��������
	sprites[p.iSprite].mImages[p.iImage].mITexture = iTexture;
	//���� ��� ����������
	CL_Rect add;
	add.left = mNodes[iTexture][iNode].x;
	add.top = mNodes[iTexture][iNode].y;
	add.right = w + add.left;
	add.bottom = h + add.top;
	//������������
	sprites[p.iSprite].mImages[p.iImage].mSrcRect = add;
	//�������� �������
	mNodes[iTexture].erase( mNodes[iTexture].begin()+iNode );

	//���������� ������� ������-������
	if(add.right+ADDING_BORDER < MAX_WIDTH && add.top+ADDING_BORDER < MAX_HEIGHT)
		mNodes[iTexture].insert( mNodes[iTexture].begin()+iNode, CL_Vec2ui(add.right+ADDING_BORDER, add.top) );
		
	//���������� ������� �����-�����
	if(add.left+ADDING_BORDER < MAX_WIDTH && add.bottom+ADDING_BORDER < MAX_HEIGHT)
		mNodes[iTexture].insert( mNodes[iTexture].begin()+iNode, CL_Vec2ui(add.left, add.bottom+ADDING_BORDER) );

	//...(0,0)
}
