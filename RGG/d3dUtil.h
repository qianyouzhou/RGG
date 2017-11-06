#define _CRT_SECURE_NO_WARNINGS
#ifndef D3DUTIL_H
#define D3DUTIL_H
#define MAP_LENGTH  1000
#include<iostream>
#include <d3d9.h>
#include <d3dx9.h>
#include <dxerr.h>
#include <string>
#include <sstream>
#include <vector>
#include<tuple>
#include<unordered_set>
#include<unordered_map>
//=============================================================
//color table
const D3DCOLOR WHITE = D3DCOLOR_XRGB(255, 255, 255); 
const D3DCOLOR RED = D3DCOLOR_XRGB(255, 0, 0);     
const D3DCOLOR GREEN = D3DCOLOR_XRGB(0, 255, 0);    
const D3DCOLOR YELLOW = D3DCOLOR_XRGB(255, 255, 0);   
const D3DCOLOR BLUE = D3DCOLOR_XRGB(0, 0, 255);    
const D3DCOLOR ORANGE = D3DCOLOR_XRGB(245, 130, 48);
const D3DCOLOR PURPLE = D3DCOLOR_XRGB(145, 30, 180);
const D3DCOLOR CYAN = D3DCOLOR_XRGB(70, 240, 240);
const D3DCOLOR MANGENTA = D3DCOLOR_XRGB(240, 50, 230);
const D3DCOLOR LIME = D3DCOLOR_XRGB(210, 245, 60);
const D3DCOLOR PINK = D3DCOLOR_XRGB(250, 190, 190);
const D3DCOLOR TEAL = D3DCOLOR_XRGB(0, 128, 128);
const D3DCOLOR LACENDER = D3DCOLOR_XRGB(230, 190, 255);
const D3DCOLOR BROWN = D3DCOLOR_XRGB(170,110,40);
const D3DCOLOR BEIGE = D3DCOLOR_XRGB(255, 250, 200);
const D3DCOLOR MAROON = D3DCOLOR_XRGB(128, 0, 0);
const D3DCOLOR MINT = D3DCOLOR_XRGB(170, 255, 195);
const D3DCOLOR OLIVE = D3DCOLOR_XRGB(128, 128, 0);
const D3DCOLOR CORAL = D3DCOLOR_XRGB(255, 215, 180);
const D3DCOLOR NAVY = D3DCOLOR_XRGB(0, 0, 128);
const D3DCOLOR GREY = D3DCOLOR_XRGB(128, 128, 128);
const D3DCOLOR gColorTable[] = {
	WHITE,RED,GREEN,YELLOW,BLUE,ORANGE,PURPLE,CYAN,MANGENTA,
	LIME,PINK,TEAL,LACENDER,BROWN,BEIGE,MAROON,MINT,OLIVE,
	CORAL,NAVY,GREY
};
//==============================================================
//struct for line 
struct Line {
	int begin;
	int end;
	Line(int a, int b) {
			begin = a;
			end = b;
	}
	Line(const Line& line) {
		begin = line.begin;
		end = line.end;
	}
};

//===============================================================
// Globals for convenient access.
class D3DApp;
extern D3DApp* gd3dApp;
extern IDirect3DDevice9* gd3dDevice;
//===============================================================
// Clean up

#define ReleaseCOM(x) { if(x){ x->Release();x = 0; } }

//===============================================================
// Geometry generation.

void GenVertexSquare(int numVertices,
	std::vector<D3DXVECTOR3>& verts);

void GenVertexDisk(int numVertices,
	std::vector<D3DXVECTOR3>& verts);

void GenLinkingLines(std::vector<D3DXVECTOR3>& verts,
	int averageDegree, std::vector<Line>&lines);

void GenSmallestLastOrder(const std::vector<std::unordered_set<int>>& matrix,std::list<int>& order,\
	int mindegree,int maxdegree);
void GenVertexColor(const std::vector<std::unordered_set<int>>& matrix,const std::list<int>& order, std::vector<int>& color);

float Distance(D3DXVECTOR3 a, D3DXVECTOR3 b);

std::tuple<int,float> GenVertexAndCellSquare(int numVertices,\
	std::vector<D3DXVECTOR3>&verts, float average, std::unordered_map<int, std::vector<int>>& gmap);

std::tuple<int,float> GenVertexAndCellDisk(int numVertices,\
	std::vector<D3DXVECTOR3>&verts, float average, std::unordered_map<int, std::vector<int>>& gmap);
void GenLinkingByCell(int r,float sclarR, std::vector<Line>&lines,\
	std::vector<std::unordered_set<int>>& matrix, const std::unordered_map<int, std::vector<int>>& gmap,\
	const std::vector<D3DXVECTOR3>&verts);

std::vector<Line> GenLineBySets(const std::vector<int>& a, const std::vector<int>& b,\
	float scalarR, const std::vector<D3DXVECTOR3>& verts, std::vector<std::unordered_set<int>>& matrix);

std::vector<int> GetByR(std::vector<std::vector<int>>& map, int i, int j, int r);


//===============================================================
// MultiThreading
struct ColoringParameter {
	IDirect3DVertexBuffer9** mColorLB;
	const std::vector<D3DXVECTOR3>& mVerts;
	std::list<int>& mOrder;
	const std::vector<std::unordered_set<int>>& mMatrix;
	int mMaxDegree, mMinDegree;
	ColoringParameter(const std::vector<std::unordered_set<int>>& matrix,std::list<int>& list,\
		int mindegree, int maxdegree,const std::vector<D3DXVECTOR3>& verts, IDirect3DVertexBuffer9** lb)
		:mOrder(list),mMatrix(matrix),mVerts(verts){
		mMaxDegree = maxdegree;
		mMinDegree = mindegree;
		mColorLB = lb;
	}
};
DWORD WINAPI Coloring(LPVOID colorPara);

//===============================================================
// Debug

#if defined(DEBUG) | defined(_DEBUG)
	#ifndef HR
	#define HR(x)                                      \
	{                                                  \
		HRESULT hr = x;                                \
		if(FAILED(hr))                                 \
		{                                              \
			DXTrace(__FILE__, __LINE__, hr, #x, TRUE); \
		}                                              \
	}
	#endif

#else
	#ifndef HR
	#define HR(x) x;
	#endif
#endif 

#endif // D3DUTIL_H