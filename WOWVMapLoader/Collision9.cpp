//--------------------------------------------------------------------------------------
// File: Collision9.cpp
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------
#include <list>
#include <map>
#include "DXUT.h"
#include "DXUTgui.h"
#include "DXUTmisc.h"
#include "DXUTCamera.h"
#include "DXUTSettingsDlg.h"
#include "SDKmisc.h"
#include "SDKmesh.h"
#include "resource.h"
#include "xnaCollision.h"
#include "vmap/VMapManager.h"
#include "vmap/VMapFactory.h"
using namespace std;

using namespace VMAP;

#define SIZE_OF_GRIDS            533.33333f
//#define DEBUG_VS   // Uncomment this line to debug D3D9 vertex shaders 
//#define DEBUG_PS   // Uncomment this line to debug D3D9 pixel shaders 

// 出生地
static const float kBornPosX = -8918.6923828125f;
static const float kBornPosY = -125.590576171875f;
static const float kBornPosZ = 90.5633850097656f;

// 暴风城
//static const float kBornPosX = -9054.412109375f;
//static const float kBornPosY = 441.490234375f;
//static const float kBornPosZ = 100.5633850097656f;

static const float kCameraSpeed = 200.0f;
static const int kMapID = 0;
static int kShowTrigs = 0;
static int kShowBoxes = 0;
static int kCurrentBoxIndex = 0;

//--------------------------------------------------------------------------------------
// Types
//--------------------------------------------------------------------------------------

// Collision objects
struct CollisionSphere
{
    XNA::Sphere sphere;
    int Collision;
};

struct CollisionBox
{
    XNA::OrientedBox obox;
    int Collision;
};

struct CollisionAABox
{
    XNA::AxisAlignedBox aabox;
    int Collision;
};

struct CollisionFrustum
{
    XNA::Frustum frustum;
    int Collision;
};

struct CollisionTriangle
{
    XMVECTOR pointa;
    XMVECTOR pointb;
    XMVECTOR pointc;
    int Collision;
};

struct CollisionRay
{
    XMVECTOR origin;
    XMVECTOR direction;
};

struct XMPosVertex
{
    XMFLOAT3 p;
};

//--------------------------------------------------------------------------------------
// Constants
//--------------------------------------------------------------------------------------
const int CAMERA_COUNT = 4;

const float CAMERA_SPACING = 50.f;

const int MAX_VERTS = 100;
const int MAX_INDEX = 24;

//--------------------------------------------------------------------------------------
// Global variables
//--------------------------------------------------------------------------------------
//CModelViewerCamera          g_Camera;               // A model viewing camera
CFirstPersonCamera			g_Camera;               // A model viewing camera
CDXUTDialogResourceManager  g_DialogResourceManager; // manager for shared resources of dialogs
CD3DSettingsDlg             g_SettingsDlg;          // Device settings dialog
CDXUTTextHelper*            g_pTxtHelper = NULL;
CDXUTDialog                 g_HUD;                  // dialog for standard controls
CDXUTDialog                 g_SampleUI;             // dialog for sample specific controls

// Direct3D 9 resources
ID3DXFont*                      g_pFont9 = NULL;
ID3DXSprite*                    g_pSprite9 = NULL;
ID3DXEffect*                    g_pEffect9 = NULL;
IDirect3DVertexDeclaration9*    g_pVertexDecl = NULL;
LPDIRECT3DVERTEXBUFFER9         g_pVB = NULL;
LPDIRECT3DINDEXBUFFER9          g_pIB = NULL;
D3DXHANDLE                      g_pmWorldViewProj = NULL;
D3DXHANDLE                      g_Color = NULL;

// Primary Collision objects
XNA::Frustum g_PrimaryFrustum;
XNA::OrientedBox g_PrimaryOrientedBox;
XNA::AxisAlignedBox g_PrimaryAABox;
CollisionRay g_PrimaryRay;

// Secondary Collision objects
vector<const VMAP::SubModel *>      gVMapModels;

// Ray testing results display object
CollisionAABox g_RayHitResultBox;

// Camera preset locations
XMVECTOR g_CameraOrigins[CAMERA_COUNT];


//--------------------------------------------------------------------------------------
// UI control IDs
//--------------------------------------------------------------------------------------
#define IDC_STATIC              -1
#define IDC_TOGGLEFULLSCREEN    1
#define IDC_TOGGLEREF           2
#define IDC_CHANGEDEVICE        3
#define IDC_GROUP               4
#define IDC_CHANGEBOX			5
#define IDC_CHANGEBOX_DEC		6


//--------------------------------------------------------------------------------------
// Forward declarations 
//--------------------------------------------------------------------------------------
LRESULT CALLBACK MsgProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool* pbNoFurtherProcessing,
                          void* pUserContext );
void CALLBACK OnKeyboard( UINT nChar, bool bKeyDown, bool bAltDown, void* pUserContext );
void CALLBACK OnGUIEvent( UINT nEvent, int nControlID, CDXUTControl* pControl, void* pUserContext );
void CALLBACK OnFrameMove( double fTime, float fElapsedTime, void* pUserContext );
bool CALLBACK ModifyDeviceSettings( DXUTDeviceSettings* pDeviceSettings, void* pUserContext );

bool CALLBACK IsD3D9DeviceAcceptable( D3DCAPS9* pCaps, D3DFORMAT AdapterFormat, D3DFORMAT BackBufferFormat,
                                      bool bWindowed, void* pUserContext );
HRESULT CALLBACK OnD3D9CreateDevice( IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc,
                                     void* pUserContext );
HRESULT CALLBACK OnD3D9ResetDevice( IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc,
                                    void* pUserContext );
void CALLBACK OnD3D9FrameRender( IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext );
void CALLBACK OnD3D9LostDevice( void* pUserContext );
void CALLBACK OnD3D9DestroyDevice( void* pUserContext );

void InitApp();
void RenderText();

void InitializeObjects();
void Animate( double fTime );
void Collide();
void RenderObjects( IDirect3DDevice9* pd3dDevice );
void SetViewForGroup( int group );

void DrawGrid( IDirect3DDevice9* pd3dDevice, const XMFLOAT3& XAxis, const XMFLOAT3& YAxis,
               const XMFLOAT3& Origin, int iXDivisions, int iYDivisions, D3DCOLOR Color );
void DrawFrustum( IDirect3DDevice9* pd3dDevice, const XNA::Frustum& frustum, D3DCOLOR Color );
void DrawAabb( IDirect3DDevice9* pd3dDevice, const XNA::AxisAlignedBox& box, D3DCOLOR Color );
void DrawObb( IDirect3DDevice9* pd3dDevice, const XNA::OrientedBox& obb, D3DCOLOR Color );
void DrawSphere( IDirect3DDevice9* pd3dDevice, const XNA::Sphere& sphere, D3DCOLOR Color );
void DrawRay( IDirect3DDevice9* pd3dDevice, const XMFLOAT3& Origin, const XMFLOAT3& Direction,
              BOOL bNormalize, D3DCOLOR Color );
void DrawTriangle( IDirect3DDevice9* pd3dDevice, const XMFLOAT3& PointA, const XMFLOAT3& PointB,
                   const XMFLOAT3& PointC, D3DCOLOR Color );


//--------------------------------------------------------------------------------------
// Entry point to the program. Initializes everything and goes into a message processing 
// loop. Idle time is used to render the scene.
//--------------------------------------------------------------------------------------
int WINAPI wWinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow )
{

    // Enable run-time memory check for debug builds.
#if defined(DEBUG) | defined(_DEBUG)
    _CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
#endif

    // XNAMath uses SSE/SSE2 instructions on Windows. We should verify the CPU supports these instructions
    // as early in the program as possible
    if ( !XMVerifyCPUSupport() )
    {
        MessageBox( NULL, TEXT("This application requires the processor support SSE2 instructions."),
                    TEXT("Collision"), MB_OK | MB_ICONEXCLAMATION);
        return -1;
    }

    // DXUT will create and use the best device (either D3D9 or D3D10) 
    // that is available on the system depending on which D3D callbacks are set below

    // Set DXUT callbacks
    DXUTSetCallbackMsgProc( MsgProc );
    DXUTSetCallbackKeyboard( OnKeyboard );
    DXUTSetCallbackFrameMove( OnFrameMove );
    DXUTSetCallbackDeviceChanging( ModifyDeviceSettings );
    DXUTSetCallbackD3D9DeviceAcceptable( IsD3D9DeviceAcceptable );
    DXUTSetCallbackD3D9DeviceCreated( OnD3D9CreateDevice );
    DXUTSetCallbackD3D9DeviceReset( OnD3D9ResetDevice );
    DXUTSetCallbackD3D9DeviceLost( OnD3D9LostDevice );
    DXUTSetCallbackD3D9DeviceDestroyed( OnD3D9DestroyDevice );
    DXUTSetCallbackD3D9FrameRender( OnD3D9FrameRender );

    InitApp();
    DXUTInit( true, true, NULL ); // Parse the command line, show msgboxes on error, no extra command line params
    DXUTSetCursorSettings( true, true );
    DXUTCreateWindow( L"Collision" );
    DXUTCreateDevice( true, 640, 480 );
    DXUTMainLoop(); // Enter into the DXUT render loop

    return DXUTGetExitCode();
}


//--------------------------------------------------------------------------------------
// Initialize the app 
//--------------------------------------------------------------------------------------
void InitApp()
{
    g_SettingsDlg.Init( &g_DialogResourceManager );
    g_HUD.Init( &g_DialogResourceManager );
    g_SampleUI.Init( &g_DialogResourceManager );

    g_HUD.SetCallback( OnGUIEvent ); int iY = 10;
    g_HUD.AddButton( IDC_TOGGLEFULLSCREEN, L"Toggle full screen", 35, iY, 125, 22 );
    g_HUD.AddButton( IDC_TOGGLEREF, L"Toggle REF (F3)", 35, iY += 24, 125, 22, VK_F3 );
    g_HUD.AddButton( IDC_CHANGEDEVICE, L"Change device (F2)", 35, iY += 24, 125, 22, VK_F2 );
	g_HUD.AddButton( IDC_CHANGEBOX, L"Change Box (F5)", 35, iY += 24, 125, 22, VK_F5 );
	g_HUD.AddButton( IDC_CHANGEBOX_DEC, L"Change Box Dec(F6)", 35, iY += 24, 125, 22, VK_F6 );


    g_SampleUI.SetCallback( OnGUIEvent ); iY = 10;

    CDXUTComboBox* pComboBox = NULL;
    g_SampleUI.AddStatic( IDC_STATIC, L"(G)roup", 10, 0, 105, 25 );
    g_SampleUI.AddComboBox( IDC_GROUP, 10, 25, 140, 24, 'G', false, &pComboBox );
    if( pComboBox )
        pComboBox->SetDropHeight( 50 );

    pComboBox->AddItem( L"Frustum", IntToPtr( 0 ) );
    pComboBox->AddItem( L"Axis-aligned Box", IntToPtr( 1 ) );
    pComboBox->AddItem( L"Oriented Box", IntToPtr( 2 ) );
    pComboBox->AddItem( L"Ray", IntToPtr( 3 ) );

    InitializeObjects();
}

//--------------------------------------------------------------------------------------
// Render the help and statistics text. This function uses the ID3DXFont interface for 
// efficient text rendering.
//--------------------------------------------------------------------------------------
wstring FormatStr(WCHAR *fmt, ...)
{
	va_list marker = NULL; 
	va_start(marker, fmt); 
	size_t len = _vscwprintf(fmt, marker)+1;
	wstring result;
	result.resize(len);
	_vsnwprintf((WCHAR *)result.c_str(), result.length(), fmt, marker);
	va_end(marker); 
	return result;
}
void RenderText()
{
	wstring posStr;
	const D3DXVECTOR3 *eyept = g_Camera.GetEyePt();
    g_pTxtHelper->Begin();
    g_pTxtHelper->SetInsertionPos( 5, 5 );
    g_pTxtHelper->SetForegroundColor( D3DXCOLOR( 1.0f, 1.0f, 0.0f, 1.0f ) );
    g_pTxtHelper->DrawTextLine( DXUTGetFrameStats( DXUTIsVsyncEnabled() ) );
    g_pTxtHelper->DrawTextLine( DXUTGetDeviceStats() );

	posStr = FormatStr(L"fps : %f", DXUTGetFPS());
	g_pTxtHelper->DrawTextLine( posStr.c_str() );
	
	posStr = FormatStr(L"x : %f", eyept->x);
	g_pTxtHelper->DrawTextLine( posStr.c_str() );
	posStr = FormatStr(L"y : %f", eyept->y);
	g_pTxtHelper->DrawTextLine( posStr.c_str() );
	posStr = FormatStr(L"z : %f", eyept->z);
	g_pTxtHelper->DrawTextLine( posStr.c_str() );

	VMapManager *vmapManger = VMapFactory::createOrGetVMapManagerInstance();
	G3D::Vector3 mangosPos = vmapManger->convertPositionToMangosRep(eyept->x, eyept->y, eyept->z);
	posStr = FormatStr(L"mangos x : %f", mangosPos.x);
	g_pTxtHelper->DrawTextLine( posStr.c_str() );
	posStr = FormatStr(L"mangos y : %f", mangosPos.y);
	g_pTxtHelper->DrawTextLine( posStr.c_str() );
	posStr = FormatStr(L"mangos z : %f", mangosPos.z);
	g_pTxtHelper->DrawTextLine( posStr.c_str() );

	posStr = FormatStr(L"sight trigs: %d", kShowTrigs);
	g_pTxtHelper->DrawTextLine( posStr.c_str() );

	posStr = FormatStr(L"sight boxes: %d. ShowBoxIndex: %d", kShowBoxes, kCurrentBoxIndex);
	g_pTxtHelper->DrawTextLine( posStr.c_str() );
	
    g_pTxtHelper->End();
}


//--------------------------------------------------------------------------------------
// Initialize the starting positions of the Collision objects
//--------------------------------------------------------------------------------------

XMVECTOR GetXMVECTORByTrigVertex(const VMAP::TriangleBox *curNode, int curIndex, const G3D::Vector3 &basePos)
{
	const ShortVector& vertex = curNode->vertex(curIndex);
	XMVECTOR result = {vertex.getX() + basePos.x, vertex.getY() + basePos.y, vertex.getZ() + basePos.z};
	return result;
}

void InitializeObjects()
{
	const XMVECTOR XMZero = XMVectorZero();

	VMapManager *vmapManger = VMapFactory::createOrGetVMapManagerInstance();
	float posX = kBornPosX;
	float posY = kBornPosY;
	float posZ = kBornPosZ;
	int gx = (int)(32-posX/SIZE_OF_GRIDS);
	int gy = (int)(32-posY/SIZE_OF_GRIDS);
	vmapManger->loadMap("D:\\TCCN-3.1.3-Trinity4666\\wow_server\\vmaps", 0, gx, gy);

	// float h = vmapManger->getHeight(kMapID, posX,posY,posZ);
	

	vmapManger->DumpTreeNodes(&gVMapModels);

    // Set up the primary frustum object from a D3D projection matrix
    // NOTE: This can also be done on your camera's projection matrix.  The projection
    // matrix built here is somewhat contrived so it renders well.
    XMMATRIX xmProj = XMMatrixPerspectiveFovLH( XM_PIDIV4, 1.77778f, 0.5f, 10.0f );
    ComputeFrustumFromProjection( &g_PrimaryFrustum, &xmProj );
    g_PrimaryFrustum.Origin.z = -7.0f;
    g_CameraOrigins[0] = XMVectorSet( 0, 0, 0, 0 );

    // Set up the primary axis aligned box
    g_PrimaryAABox.Center = XMFLOAT3( CAMERA_SPACING, 0, 0 );
    g_PrimaryAABox.Extents = XMFLOAT3( 5, 5, 5 );
    g_CameraOrigins[1] = XMVectorSet( CAMERA_SPACING, 0, 0, 0 );

    // Set up the primary oriented box with some rotation
    g_PrimaryOrientedBox.Center = XMFLOAT3( -CAMERA_SPACING, 0, 0 );
    g_PrimaryOrientedBox.Extents = XMFLOAT3( 5, 5, 5 );
    XMStoreFloat4( &g_PrimaryOrientedBox.Orientation, XMQuaternionRotationRollPitchYaw( XM_PIDIV4, XM_PIDIV4, 0 ) );
    g_CameraOrigins[2] = XMVectorSet( -CAMERA_SPACING, 0, 0, 0 );

    // Set up the primary ray
    g_PrimaryRay.origin = XMVectorSet( 0, 0, CAMERA_SPACING, 0 );
    g_PrimaryRay.direction = XMVectorSet( 0, 0, 1, 0 );
    g_CameraOrigins[3] = XMVectorSet( 0, 0, CAMERA_SPACING, 0 );

    // Initialize all of the secondary objects with default values

    // Set up ray hit result box
    g_RayHitResultBox.aabox.Center = XMFLOAT3( 0, 0, 0 );
    g_RayHitResultBox.aabox.Extents = XMFLOAT3( 0.05f, 0.05f, 0.05f );
}



//--------------------------------------------------------------------------------------
// Move objects around over time
//--------------------------------------------------------------------------------------
void Animate( double fTime )
{
}


//--------------------------------------------------------------------------------------
// Test Collisions between pairs of Collision objects using XNACollision functions
//--------------------------------------------------------------------------------------
void Collide()
{
}


//--------------------------------------------------------------------------------------
// Returns the color based on the Collision result and the gruop number.
// Frustum tests (group 0) return 0, 1, or 2 for outside, partially inside, and fully inside;
// all other tests return 0 or 1 for no Collision or Collision.
//--------------------------------------------------------------------------------------
inline D3DCOLOR GetCollisionColor( int Collision, int groupnumber )
{
    const D3DCOLOR ColorCollide = 0xFFFF0000;
    const D3DCOLOR ColorPartialCollide = 0xFFFFFF00;
    const D3DCOLOR ColorNoCollide = 0xFF80C080;

    // special case: a value of 1 for groups 1 and higher needs to register as a full Collision
    if( groupnumber > 0 && Collision > 0 )
        Collision = 2;

    switch( Collision )
    {
        case 0:
            return ColorNoCollide;
        case 1:
            return ColorPartialCollide;
        case 2:
        default:
            return ColorCollide;
    }
}


//--------------------------------------------------------------------------------------
// Renders Collision objects
//--------------------------------------------------------------------------------------
bool CheckIsInSight(const VMAP::SubModel *tri)
{return true;
	const D3DXVECTOR3 *eyept = g_Camera.GetEyePt();
	VMapManager *vmapManger = VMapFactory::createOrGetVMapManagerInstance();

	G3D::AABox bounds = tri->getAABoxBounds();
	vector<G3D::Vector3> checkTrigs;
	checkTrigs.push_back(bounds.low());
	checkTrigs.push_back(bounds.high());
	checkTrigs.push_back((bounds.low() + bounds.high()) / 2);
	for (size_t i=0; i<checkTrigs.size(); i++)
	{
		G3D::Vector3 triPos = checkTrigs[i];
		G3D::Vector3 mangosEyePos = vmapManger->convertPositionToMangosRep(
			eyept->x, eyept->y, eyept->z);
		G3D::Vector3 mangosBoxPos = vmapManger->convertPositionToMangosRep(
			triPos.x, triPos.y, triPos.z);
		//if(vmapManger->isInLineOfSight(kMapID, 
		//	mangosEyePos.x, mangosEyePos.y, mangosEyePos.z, 
		//	mangosBoxPos.x, mangosBoxPos.y, mangosBoxPos.z))
		//{
		//	return true;
		//}
		static const float kMaxDist = 300;
		if (abs((mangosEyePos - mangosBoxPos).magnitude()) < kMaxDist)
		{
			return true;
		}
	}
	return false;

	
	//G3D::Vector3 vecEye(eyept->x, eyept->y, eyept->z);
	//static const float kMaxDist = 100;
	//for(int i=0; i<3; i++)
	//{
	//	const ShortVector& svec = tri->vertex(i);
	//	G3D::Vector3 vec3(svec.getX(), svec.getY(), svec.getZ());
	//	if (abs((vec3 - vecEye).magnitude()) > kMaxDist)
	//	{
	//		return false;
	//	}
	//}

	//return true;
}

void G3DVectorToXMFloat(const G3D::Vector3 *input, XMFLOAT3 *result)
{
	result->x = input->x;
	result->y = input->y;
	result->z = input->z;
}

void DrawSubModel(IDirect3DDevice9* pd3dDevice, const VMAP::SubModel *tri)
{
	XMVECTOR tria,trib,tric;
	G3D::AABox aabox;
	XNA::AxisAlignedBox drawBox;
	G3D::Vector3 basePos;
	if (!CheckIsInSight(tri))
	{
		return;
	}
	kShowBoxes++;
	if (abs(kShowBoxes - kCurrentBoxIndex) > 3)
	{
		return;
	}
	basePos = tri->getBasePosition();
	//aabox = tri->getAABoxBounds();
	//G3DVectorToXMFloat(&aabox.center(), &drawBox.Center);
	//G3DVectorToXMFloat(&aabox.extent(), &drawBox.Extents);
	//D3DCOLOR c = GetCollisionColor( FALSE, 0 );
	//DrawAabb( pd3dDevice, drawBox, c );

	for (int i=0; i<tri->getNTriangles(); i++)
	{
		const TriangleBox& triBox = tri->getTriangle(i);

		tria = GetXMVECTORByTrigVertex(&triBox, 0, basePos);
		trib = GetXMVECTORByTrigVertex(&triBox, 1, basePos);
		tric = GetXMVECTORByTrigVertex(&triBox, 2, basePos);

		D3DCOLOR c = GetCollisionColor( FALSE, 0 );
		XMFLOAT3 Verts[3];
		XMStoreFloat3( &Verts[0], tria );
		XMStoreFloat3( &Verts[1], trib );
		XMStoreFloat3( &Verts[2], tric );
		DrawTriangle( pd3dDevice, Verts[0], Verts[1], Verts[2], c );
		kShowTrigs++;
	}

}

void RenderObjects( IDirect3DDevice9* pd3dDevice )
{
    // Set up some color constants
    const D3DCOLOR ColorWhite = 0xFFFFFFFF;
    const D3DCOLOR ColorGround = 0xFF000000;
    const D3DCOLOR ColorYellow = 0xFFFFFF00;

	VMapManager *vmapManger = VMapFactory::createOrGetVMapManagerInstance();
	G3D::Vector3 vec = vmapManger->convertPositionToInternalRep(kBornPosX, kBornPosY, kBornPosZ);
    // Draw ground planes
    XMFLOAT3 vXAxis( 500 + vec.x, vec.y - 10.f,  0 + vec.z);
    XMFLOAT3 vYAxis( 0 + vec.x, vec.y - 10.f, 500 + vec.z);
    XMFLOAT3 vOrigin( vec.x ,
                      vec.y - 10.f,
                      vec.z  );
    const int iXDivisions = 20;
    const int iYDivisions = 20;
    DrawGrid( pd3dDevice, vXAxis, vYAxis, vOrigin, iXDivisions, iYDivisions, ColorGround );

    // Draw primary Collision objects in white
    //DrawFrustum( pd3dDevice, g_PrimaryFrustum, ColorWhite );
    //DrawAabb( pd3dDevice, g_PrimaryAABox, ColorWhite );
    //DrawObb( pd3dDevice, g_PrimaryOrientedBox, ColorWhite );

    //{
    //    XMFLOAT3 Origin;
    //    XMFLOAT3 Direction;
    //    XMStoreFloat3( &Origin, g_PrimaryRay.origin );
    //    XMStoreFloat3( &Direction, XMVectorScale( g_PrimaryRay.direction, 10.0f ) );
    //    DrawRay( pd3dDevice, Origin, Direction, FALSE, 0xFF505050 );
    //    XMStoreFloat3( &Direction, g_PrimaryRay.direction );
    //    DrawRay( pd3dDevice, Origin, Direction, FALSE, ColorWhite );
    //}

    // Draw secondary Collision objects in colors based on Collision results

	kShowTrigs = 0;
	kShowBoxes = 0;
    for( UINT32 i = 0; i < gVMapModels.size(); ++i )
	{
		const VMAP::SubModel *tri = gVMapModels[i];
		DrawSubModel(pd3dDevice, tri);
    }

    // Draw results of ray-object intersection, if there was a hit this frame
    //if( g_RayHitResultBox.Collision )
    //    DrawAabb( pd3dDevice, g_RayHitResultBox.aabox, ColorYellow );
}


//--------------------------------------------------------------------------------------
// Sets the camera to view a particular group of objects
//--------------------------------------------------------------------------------------
void SetViewForGroup( int group )
{
	VMapManager *vmapManger = VMapFactory::createOrGetVMapManagerInstance();
	G3D::Vector3 result = vmapManger->convertPositionToInternalRep(kBornPosX,kBornPosY,kBornPosZ);
    g_Camera.Reset();

    XMFLOAT3 vecAt;
    vecAt.x = result.x;
	vecAt.y = result.y;
	vecAt.z = result.z;

    XMFLOAT3 vecEye( vecAt.x, vecAt.y, vecAt.z);
    g_Camera.SetViewParams( (D3DXVECTOR3*)&vecEye, (D3DXVECTOR3*)&vecAt );

    //g_Camera.SetModelCenter( *((D3DXVECTOR3*)&vecAt) );
	g_Camera.SetScalers( 0.01f, kCameraSpeed );  // Camera movement parameters
}


//--------------------------------------------------------------------------------------
// Simple draw operations
//--------------------------------------------------------------------------------------
void DrawGrid( IDirect3DDevice9* pd3dDevice, const XMFLOAT3& XAxis, const XMFLOAT3& YAxis,
               const XMFLOAT3& Origin, int iXDivisions, int iYDivisions, D3DCOLOR Color )
{
    HRESULT hr;

    iXDivisions = max( 1, iXDivisions );
    iYDivisions = max( 1, iYDivisions );

    // build grid geometry
    INT iLineCount = iXDivisions + iYDivisions + 2;
    assert( (2*iLineCount) <= MAX_VERTS );

    XMFLOAT3* pLines = 0;
    V( g_pVB->Lock( 0, 0, (void**)&pLines, D3DLOCK_DISCARD ) )

    XMVECTOR vX = XMLoadFloat3( &XAxis );
    XMVECTOR vY = XMLoadFloat3( &YAxis );
    XMVECTOR vOrigin = XMLoadFloat3( &Origin );

    for( INT i = 0; i <= iXDivisions; i++ )
    {
        FLOAT fPercent = ( FLOAT )i / ( FLOAT )iXDivisions;
        fPercent = ( fPercent * 2.0f ) - 1.0f;
        XMVECTOR vScale = XMVectorScale( vX, fPercent );
        vScale = XMVectorAdd( vScale, vOrigin );
        XMStoreFloat3( &pLines[ ( i * 2 ) ], XMVectorSubtract( vScale, vY ) );
        XMStoreFloat3( &pLines[ ( i * 2 ) + 1 ], XMVectorAdd( vScale, vY ) );
    }

    INT iStartIndex = ( iXDivisions + 1 ) * 2;
    for( INT i = 0; i <= iYDivisions; i++ )
    {
        FLOAT fPercent = ( FLOAT )i / ( FLOAT )iYDivisions;
        fPercent = ( fPercent * 2.0f ) - 1.0f;
        XMVECTOR vScale = XMVectorScale( vY, fPercent );
        vScale = XMVectorAdd( vScale, vOrigin );
        XMStoreFloat3( &pLines[ ( i * 2 ) + iStartIndex ], XMVectorSubtract( vScale, vX ) );
        XMStoreFloat3( &pLines[ ( i * 2 ) + 1 + iStartIndex ], XMVectorAdd( vScale, vX ) );
    }

    V( g_pVB->Unlock() )

    // draw grid
    D3DXCOLOR clr = Color;
    g_pEffect9->SetFloatArray( g_Color, clr, 4 );
    g_pEffect9->CommitChanges();
    pd3dDevice->DrawPrimitive( D3DPT_LINELIST, 0, iLineCount );
}

void DrawFrustum( IDirect3DDevice9* pd3dDevice, const XNA::Frustum& frustum, D3DCOLOR Color )
{
    // compute corner points
    XMVECTOR Origin = XMVectorSet( frustum.Origin.x, frustum.Origin.y, frustum.Origin.z, 0 );
    FLOAT Near = frustum.Near;
    FLOAT Far = frustum.Far;
    FLOAT RightSlope = frustum.RightSlope;
    FLOAT LeftSlope = frustum.LeftSlope;
    FLOAT TopSlope = frustum.TopSlope;
    FLOAT BottomSlope = frustum.BottomSlope;

    XMFLOAT3 CornerPoints[8];
    CornerPoints[0] = XMFLOAT3( RightSlope * Near, TopSlope * Near, Near );
    CornerPoints[1] = XMFLOAT3( LeftSlope * Near, TopSlope * Near, Near );
    CornerPoints[2] = XMFLOAT3( LeftSlope * Near, BottomSlope * Near, Near );
    CornerPoints[3] = XMFLOAT3( RightSlope * Near, BottomSlope * Near, Near );

    CornerPoints[4] = XMFLOAT3( RightSlope * Far, TopSlope * Far, Far );
    CornerPoints[5] = XMFLOAT3( LeftSlope * Far, TopSlope * Far, Far );
    CornerPoints[6] = XMFLOAT3( LeftSlope * Far, BottomSlope * Far, Far );
    CornerPoints[7] = XMFLOAT3( RightSlope * Far, BottomSlope * Far, Far );

    XMVECTOR Orientation = XMLoadFloat4( &frustum.Orientation );
    XMMATRIX Mat = XMMatrixRotationQuaternion( Orientation );
    for( UINT i = 0; i < 8; i++ )
    {
        XMVECTOR Result = XMVector3Transform( XMLoadFloat3( &CornerPoints[i] ), Mat );
        Result = XMVectorAdd( Result, Origin );
        XMStoreFloat3( &CornerPoints[i], Result );
    }

    // copy to vertex buffer
    assert( (12 * 2) <= MAX_VERTS );

    XMFLOAT3* pLines = 0;
    HRESULT hr;
    V( g_pVB->Lock( 0, 0, (void**)&pLines, D3DLOCK_DISCARD ) )

    pLines[0] = CornerPoints[0];
    pLines[1] = CornerPoints[1];
    pLines[2] = CornerPoints[1];
    pLines[3] = CornerPoints[2];
    pLines[4] = CornerPoints[2];
    pLines[5] = CornerPoints[3];
    pLines[6] = CornerPoints[3];
    pLines[7] = CornerPoints[0];

    pLines[8] = CornerPoints[0];
    pLines[9] = CornerPoints[4];
    pLines[10] = CornerPoints[1];
    pLines[11] = CornerPoints[5];
    pLines[12] = CornerPoints[2];
    pLines[13] = CornerPoints[6];
    pLines[14] = CornerPoints[3];
    pLines[15] = CornerPoints[7];

    pLines[16] = CornerPoints[4];
    pLines[17] = CornerPoints[5];
    pLines[18] = CornerPoints[5];
    pLines[19] = CornerPoints[6];
    pLines[20] = CornerPoints[6];
    pLines[21] = CornerPoints[7];
    pLines[22] = CornerPoints[7];
    pLines[23] = CornerPoints[4];

    V( g_pVB->Unlock() )

    // draw frustum
    D3DXCOLOR clr = Color;
    g_pEffect9->SetFloatArray( g_Color, clr, 4 );
    g_pEffect9->CommitChanges();
    pd3dDevice->DrawPrimitive( D3DPT_LINELIST, 0, 12 );
}

void DrawCube( IDirect3DDevice9* pd3dDevice, const XMMATRIX& matWorld, D3DCOLOR Color )
{
    static XMVECTOR verts[8] =
    {
        { -1, -1, -1, 0 },
        { 1, -1, -1, 0 },
        { 1, -1, 1, 0 },
        { -1, -1, 1, 0 },
        { -1, 1, -1, 0 },
        { 1, 1, -1, 0 },
        { 1, 1, 1, 0 },
        { -1, 1, 1, 0 }
    };
    static const WORD indices[] =
    {
        0, 1,
        1, 2,
        2, 3,
        3, 0,
        4, 5,
        5, 6,
        6, 7,
        7, 4,
        0, 4,
        1, 5,
        2, 6,
        3, 7
    };

    // copy to vertex buffer
    assert( 8 <= MAX_VERTS );

    XMFLOAT3* pVerts = NULL;
    HRESULT hr;
    V( g_pVB->Lock( 0, 0, (void**)&pVerts, D3DLOCK_DISCARD ) )

    for( int i=0; i < 8; ++i )
    {
        XMVECTOR v = XMVector3Transform( verts[i], matWorld );
        XMStoreFloat3( &pVerts[i], v );
    }

    V( g_pVB->Unlock() )

    // copy to index buffer
    assert( 24 <= MAX_INDEX );

    WORD *pIndices = NULL;
    V( g_pIB->Lock( 0, 0, (void**)&pIndices, D3DLOCK_DISCARD ) )

    memcpy( pIndices, indices, sizeof(indices) );

    V( g_pIB->Unlock() )

    // Draw box
    D3DXCOLOR clr = Color;
    g_pEffect9->SetFloatArray( g_Color, clr, 4 );
    g_pEffect9->CommitChanges();
    pd3dDevice->SetIndices( g_pIB );
    pd3dDevice->DrawIndexedPrimitive( D3DPT_LINELIST, 0, 0, 8, 0, 12 );
}

void DrawAabb( IDirect3DDevice9* pd3dDevice, const XNA::AxisAlignedBox& box, D3DCOLOR Color )
{
    XMMATRIX matWorld = XMMatrixScaling( box.Extents.x, box.Extents.y, box.Extents.z );
    XMVECTOR position = XMLoadFloat3( &box.Center );
    matWorld.r[3] = XMVectorSelect( matWorld.r[3], position, XMVectorSelectControl( 1, 1, 1, 0 ) );

    DrawCube( pd3dDevice, matWorld, Color );
}

void DrawObb( IDirect3DDevice9* pd3dDevice, const XNA::OrientedBox& obb, D3DCOLOR Color )
{
    XMMATRIX matWorld = XMMatrixRotationQuaternion( XMLoadFloat4( &obb.Orientation ) );
    XMMATRIX matScale = XMMatrixScaling( obb.Extents.x, obb.Extents.y, obb.Extents.z );
    matWorld = XMMatrixMultiply( matScale, matWorld );
    XMVECTOR position = XMLoadFloat3( &obb.Center );
    matWorld.r[3] = XMVectorSelect( matWorld.r[3], position, XMVectorSelectControl( 1, 1, 1, 0 ) );

    DrawCube( pd3dDevice, matWorld, Color );
}

void DrawRing( IDirect3DDevice9* pd3dDevice, const XMFLOAT3& Origin, const XMFLOAT3& MajorAxis,
               const XMFLOAT3& MinorAxis, D3DCOLOR Color )
{
    static const DWORD dwRingSegments = 32;

    XMFLOAT3 verts[ dwRingSegments + 1 ];

    XMVECTOR vOrigin = XMLoadFloat3( &Origin );
    XMVECTOR vMajor = XMLoadFloat3( &MajorAxis );
    XMVECTOR vMinor = XMLoadFloat3( &MinorAxis );

    FLOAT fAngleDelta = XM_2PI / ( float )dwRingSegments;
    // Instead of calling cos/sin for each segment we calculate
    // the sign of the angle delta and then incrementally calculate sin
    // and cosine from then on.
    XMVECTOR cosDelta = XMVectorReplicate( cosf( fAngleDelta ) );
    XMVECTOR sinDelta = XMVectorReplicate( sinf( fAngleDelta ) );
    XMVECTOR incrementalSin = XMVectorZero();
    static const XMVECTOR initialCos =
    {
        1.0f, 1.0f, 1.0f, 1.0f
    };
    XMVECTOR incrementalCos = initialCos;
    for( DWORD i = 0; i < dwRingSegments; i++ )
    {
        XMVECTOR Pos;
        Pos = XMVectorMultiplyAdd( vMajor, incrementalCos, vOrigin );
        Pos = XMVectorMultiplyAdd( vMinor, incrementalSin, Pos );
        XMStoreFloat3( ( XMFLOAT3* )&verts[i], Pos );
        // Standard formula to rotate a vector.
        XMVECTOR newCos = incrementalCos * cosDelta - incrementalSin * sinDelta;
        XMVECTOR newSin = incrementalCos * sinDelta + incrementalSin * cosDelta;
        incrementalCos = newCos;
        incrementalSin = newSin;
    }
    verts[ dwRingSegments ] = verts[0];

    // Copy to vertex buffer
    assert( (dwRingSegments+1) <= MAX_VERTS );

    XMFLOAT3* pVerts = NULL;
    HRESULT hr;
    V( g_pVB->Lock( 0, 0, (void**)&pVerts, D3DLOCK_DISCARD ) )
    memcpy( pVerts, verts, sizeof(verts) );
    V( g_pVB->Unlock() )

    // Draw ring
    D3DXCOLOR clr = Color;
    g_pEffect9->SetFloatArray( g_Color, clr, 4 );
    g_pEffect9->CommitChanges();
    pd3dDevice->DrawPrimitive( D3DPT_LINESTRIP, 0, dwRingSegments );
}

void DrawSphere( IDirect3DDevice9* pd3dDevice, const XNA::Sphere& sphere, D3DCOLOR Color )
{
    const XMFLOAT3 Origin = sphere.Center;
    const float fRadius = sphere.Radius;

    DrawRing( pd3dDevice, Origin, XMFLOAT3( fRadius, 0, 0 ), XMFLOAT3( 0, 0, fRadius ), Color );
    DrawRing( pd3dDevice, Origin, XMFLOAT3( fRadius, 0, 0 ), XMFLOAT3( 0, fRadius, 0 ), Color );
    DrawRing( pd3dDevice, Origin, XMFLOAT3( 0, fRadius, 0 ), XMFLOAT3( 0, 0, fRadius ), Color );
}

void DrawRay( IDirect3DDevice9* pd3dDevice, const XMFLOAT3& Origin, const XMFLOAT3& Direction,
              BOOL bNormalize, D3DCOLOR Color )
{
    XMFLOAT3 verts[3];
    memcpy( &verts[0], &Origin, 3 * sizeof( FLOAT ) );

    XMVECTOR RayOrigin = XMLoadFloat3( &Origin );
    XMVECTOR RayDirection = XMLoadFloat3( &Direction );
    XMVECTOR NormDirection = XMVector3Normalize( RayDirection );
    if( bNormalize )
        RayDirection = NormDirection;

    XMVECTOR PerpVector;
    XMVECTOR CrossVector = XMVectorSet( 0, 1, 0, 0 );
    PerpVector = XMVector3Cross( NormDirection, CrossVector );

    if( XMVector3Equal( XMVector3LengthSq( PerpVector ), XMVectorSet( 0, 0, 0, 0 ) ) )
    {
        CrossVector = XMVectorSet( 0, 0, 1, 0 );
        PerpVector = XMVector3Cross( NormDirection, CrossVector );
    }
    PerpVector = XMVector3Normalize( PerpVector );

    XMStoreFloat3( ( XMFLOAT3* )&verts[1], XMVectorAdd( RayDirection, RayOrigin ) );
    PerpVector = XMVectorScale( PerpVector, 0.0625f );
    NormDirection = XMVectorScale( NormDirection, -0.25f );
    RayDirection = XMVectorAdd( PerpVector, RayDirection );
    RayDirection = XMVectorAdd( NormDirection, RayDirection );
    XMStoreFloat3( ( XMFLOAT3* )&verts[2], XMVectorAdd( RayDirection, RayOrigin ) );
    
    // Copy to vertex buffer
    assert( 3 <= MAX_VERTS );
    XMFLOAT3* pVerts = NULL;
    HRESULT hr;
    V( g_pVB->Lock( 0, 0, (void**)&pVerts, D3DLOCK_DISCARD ) )
    memcpy( pVerts, verts, sizeof(verts) );
    V( g_pVB->Unlock() )

    // Draw ray
    D3DXCOLOR clr = Color;
    g_pEffect9->SetFloatArray( g_Color, clr, 4 );
    g_pEffect9->CommitChanges();
    pd3dDevice->DrawPrimitive( D3DPT_LINESTRIP, 0, 2 );
}

void DrawTriangle( IDirect3DDevice9* pd3dDevice, const XMFLOAT3& PointA, const XMFLOAT3& PointB,
                   const XMFLOAT3& PointC, D3DCOLOR Color )
{
    // Copy to vertex buffer
    assert( 4 <= MAX_VERTS );
    XMFLOAT3* pVerts = NULL;
    HRESULT hr;
    V( g_pVB->Lock( 0, 0, (void**)&pVerts, D3DLOCK_DISCARD ) )
    pVerts[0] = PointA;
    pVerts[1] = PointB;
    pVerts[2] = PointC;
    pVerts[3] = PointA;
    V( g_pVB->Unlock() )

    // Draw triangle
    D3DXCOLOR clr = Color;
    g_pEffect9->SetFloatArray( g_Color, clr, 4 );
    g_pEffect9->CommitChanges();
    pd3dDevice->DrawPrimitive( D3DPT_LINESTRIP, 0, 3 );
}

//--------------------------------------------------------------------------------------
// Rejects any D3D9 devices that aren't acceptable to the app by returning false
//--------------------------------------------------------------------------------------
bool CALLBACK IsD3D9DeviceAcceptable( D3DCAPS9* pCaps, D3DFORMAT AdapterFormat,
                                      D3DFORMAT BackBufferFormat, bool bWindowed, void* pUserContext )
{
    // Skip backbuffer formats that don't support alpha blending
    IDirect3D9* pD3D = DXUTGetD3D9Object();
    if( FAILED( pD3D->CheckDeviceFormat( pCaps->AdapterOrdinal, pCaps->DeviceType,
                                         AdapterFormat, D3DUSAGE_QUERY_POSTPIXELSHADER_BLENDING,
                                         D3DRTYPE_TEXTURE, BackBufferFormat ) ) )
        return false;

    // No fallback defined by this app, so reject any device that 
    // doesn't support at least ps2.0
    if( pCaps->PixelShaderVersion < D3DPS_VERSION( 2, 0 ) )
        return false;

    return true;
}


//--------------------------------------------------------------------------------------
// Called right before creating a D3D9 or D3D10 device, allowing the app to modify the device settings as needed
//--------------------------------------------------------------------------------------
bool CALLBACK ModifyDeviceSettings( DXUTDeviceSettings* pDeviceSettings, void* pUserContext )
{
    if( pDeviceSettings->ver == DXUT_D3D9_DEVICE )
    {
        IDirect3D9* pD3D = DXUTGetD3D9Object();
        D3DCAPS9 Caps;
        pD3D->GetDeviceCaps( pDeviceSettings->d3d9.AdapterOrdinal, pDeviceSettings->d3d9.DeviceType, &Caps );

        // If device doesn't support HW T&L or doesn't support 1.1 vertex shaders in HW 
        // then switch to SWVP.
        if( ( Caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT ) == 0 ||
            Caps.VertexShaderVersion < D3DVS_VERSION( 1, 1 ) )
        {
            pDeviceSettings->d3d9.BehaviorFlags = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
        }

        // Debugging vertex shaders requires either REF or software vertex processing 
        // and debugging pixel shaders requires REF.  
#ifdef DEBUG_VS
        if( pDeviceSettings->d3d9.DeviceType != D3DDEVTYPE_REF )
        {
            pDeviceSettings->d3d9.BehaviorFlags &= ~D3DCREATE_HARDWARE_VERTEXPROCESSING;
            pDeviceSettings->d3d9.BehaviorFlags &= ~D3DCREATE_PUREDEVICE;
            pDeviceSettings->d3d9.BehaviorFlags |= D3DCREATE_SOFTWARE_VERTEXPROCESSING;
        }
#endif
#ifdef DEBUG_PS
        pDeviceSettings->d3d9.DeviceType = D3DDEVTYPE_REF;
#endif
    }

    // For the first device created if its a REF device, optionally display a warning dialog box
    static bool s_bFirstTime = true;
    if( s_bFirstTime )
    {
        s_bFirstTime = false;
        if( ( DXUT_D3D9_DEVICE == pDeviceSettings->ver && pDeviceSettings->d3d9.DeviceType == D3DDEVTYPE_REF ) ||
            ( DXUT_D3D10_DEVICE == pDeviceSettings->ver &&
              pDeviceSettings->d3d10.DriverType == D3D10_DRIVER_TYPE_REFERENCE ) )
            DXUTDisplaySwitchingToREFWarning( pDeviceSettings->ver );
    }

    return true;
}


//--------------------------------------------------------------------------------------
// Create any D3D9 resources that will live through a device reset (D3DPOOL_MANAGED)
// and aren't tied to the back buffer size
//--------------------------------------------------------------------------------------
HRESULT CALLBACK OnD3D9CreateDevice( IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc,
                                     void* pUserContext )
{
    HRESULT hr;

    V_RETURN( g_DialogResourceManager.OnD3D9CreateDevice( pd3dDevice ) );
    V_RETURN( g_SettingsDlg.OnD3D9CreateDevice( pd3dDevice ) );

    V_RETURN( D3DXCreateFont( pd3dDevice, 15, 0, FW_BOLD, 1, FALSE, DEFAULT_CHARSET,
                              OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE,
                              L"Arial", &g_pFont9 ) );

    // Read the D3DX effect file
    WCHAR str[MAX_PATH];
    DWORD dwShaderFlags = D3DXFX_NOT_CLONEABLE;
#ifdef DEBUG_VS
        dwShaderFlags |= D3DXSHADER_FORCE_VS_SOFTWARE_NOOPT;
    #endif
#ifdef DEBUG_PS
        dwShaderFlags |= D3DXSHADER_FORCE_PS_SOFTWARE_NOOPT;
    #endif
    V_RETURN( DXUTFindDXSDKMediaFileCch( str, MAX_PATH, L"Collision.fx" ) );
    V_RETURN( D3DXCreateEffectFromFile( pd3dDevice, str, NULL, NULL, dwShaderFlags|D3DXFX_LARGEADDRESS_HANDLE,
                                        NULL, &g_pEffect9, NULL ) );

    // Get handles to the effect's parameters (required since we are using D3DXFX_LARGEADDRESS_HANDLE)
    g_pmWorldViewProj = g_pEffect9->GetParameterByName( NULL, "g_mWorldViewProjection" );
    g_Color = g_pEffect9->GetParameterByName( NULL, "g_Color" );

    if ( !g_pmWorldViewProj || !g_Color )
        return E_FAIL;

    // Setup the camera's view parameters
    SetViewForGroup( 0 );

    // Create drawing resources
    static const D3DVERTEXELEMENT9 elements[ 2 ] =
    {
        { 0,     0, D3DDECLTYPE_FLOAT3,     0,  D3DDECLUSAGE_POSITION,  0 },
        D3DDECL_END()
    };

    V_RETURN( pd3dDevice->CreateVertexDeclaration( elements, &g_pVertexDecl ) );

    return S_OK;
}


//--------------------------------------------------------------------------------------
// Create any D3D9 resources that won't live through a device reset (D3DPOOL_DEFAULT) 
// or that are tied to the back buffer size 
//--------------------------------------------------------------------------------------
HRESULT CALLBACK OnD3D9ResetDevice( IDirect3DDevice9* pd3dDevice,
                                    const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext )
{
    HRESULT hr;

    V_RETURN( g_DialogResourceManager.OnD3D9ResetDevice() );
    V_RETURN( g_SettingsDlg.OnD3D9ResetDevice() );

    if( g_pFont9 ) V_RETURN( g_pFont9->OnResetDevice() );
    if( g_pEffect9 ) V_RETURN( g_pEffect9->OnResetDevice() );

    V_RETURN( D3DXCreateSprite( pd3dDevice, &g_pSprite9 ) );
    g_pTxtHelper = new CDXUTTextHelper( g_pFont9, g_pSprite9, NULL, NULL, 15 );

    // Setup the camera's projection parameters
    float fAspectRatio = pBackBufferSurfaceDesc->Width / ( FLOAT )pBackBufferSurfaceDesc->Height;
    g_Camera.SetProjParams( D3DX_PI / 4, fAspectRatio, 0.1f, 1000.0f );
    //g_Camera.SetWindow( pBackBufferSurfaceDesc->Width, pBackBufferSurfaceDesc->Height );

    g_HUD.SetLocation( pBackBufferSurfaceDesc->Width - 170, 0 );
    g_HUD.SetSize( 170, 170 );
    g_SampleUI.SetLocation( pBackBufferSurfaceDesc->Width - 170, pBackBufferSurfaceDesc->Height - 350 );
    g_SampleUI.SetSize( 170, 300 );

    // Create our draw buffers
    V_RETURN( pd3dDevice->CreateVertexBuffer( MAX_VERTS * sizeof( XMPosVertex ), D3DUSAGE_DYNAMIC | D3DUSAGE_WRITEONLY,
                                              0, D3DPOOL_DEFAULT, &g_pVB, NULL ) );

    V_RETURN( pd3dDevice->CreateIndexBuffer( MAX_INDEX * sizeof(WORD), D3DUSAGE_DYNAMIC | D3DUSAGE_WRITEONLY, D3DFMT_INDEX16,
                                             D3DPOOL_DEFAULT, &g_pIB, NULL ) );

    return S_OK;
}


//--------------------------------------------------------------------------------------
// Handle updates to the scene.  This is called regardless of which D3D API is used
//--------------------------------------------------------------------------------------
void CALLBACK OnFrameMove( double fTime, float fElapsedTime, void* pUserContext )
{
    // Update position of Collision objects
    Animate( fTime );


    // Update the camera's position based on user input 
    g_Camera.FrameMove( fElapsedTime );
}


//--------------------------------------------------------------------------------------
// Render the scene using the D3D9 device
//--------------------------------------------------------------------------------------
void CALLBACK OnD3D9FrameRender( IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext )
{
    HRESULT hr;
    D3DXMATRIXA16 mWorld;
    D3DXMATRIXA16 mView;
    D3DXMATRIXA16 mProj;
    D3DXMATRIXA16 mWorldViewProjection;

    // If the settings dialog is being shown, then render it instead of rendering the app's scene
    if( g_SettingsDlg.IsActive() )
    {
        g_SettingsDlg.OnRender( fElapsedTime );
        return;
    }

    // Clear the render target and the zbuffer 
    V( pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB( 0, 45, 50, 170 ), 1.0f, 0 ) );

    // Render the scene
    if( SUCCEEDED( pd3dDevice->BeginScene() ) )
    {
        D3DXHANDLE htech = g_pEffect9->GetTechniqueByName( "RenderScene" );
        V( g_pEffect9->SetTechnique( htech ) );

        // Get the projection & view matrix from the camera class
        mWorld = *g_Camera.GetWorldMatrix();
        mProj = *g_Camera.GetProjMatrix();
        mView = *g_Camera.GetViewMatrix();

        mWorldViewProjection = mView * mProj;

        // Update the effect's variables
        V( g_pEffect9->SetMatrix( g_pmWorldViewProj, &mWorldViewProjection ) );

        DXUT_BeginPerfEvent( DXUT_PERFEVENTCOLOR, L"World" ); // These events are to help PIX identify what the code is doing
        UINT cPasses;
        V( g_pEffect9->Begin( &cPasses, 0 ) );

        V( pd3dDevice->SetStreamSource( 0, g_pVB, 0, sizeof(XMPosVertex) ) );
        V( pd3dDevice->SetVertexDeclaration( g_pVertexDecl ) );

        for( UINT iPass = 0; iPass < cPasses; ++iPass )
        {
            V( g_pEffect9->BeginPass( iPass ) );
            RenderObjects( pd3dDevice );
            V( g_pEffect9->EndPass() );
        }

        V( g_pEffect9->End() );
        DXUT_EndPerfEvent();

        DXUT_BeginPerfEvent( DXUT_PERFEVENTCOLOR, L"HUD / Stats" ); // These events are to help PIX identify what the code is doing
        RenderText();
        V( g_HUD.OnRender( fElapsedTime ) );
        V( g_SampleUI.OnRender( fElapsedTime ) );
        DXUT_EndPerfEvent();

        V( pd3dDevice->EndScene() );

        pd3dDevice->SetStreamSource( 0, NULL, 0, 0 );
        pd3dDevice->SetIndices( NULL );
    }
}


//--------------------------------------------------------------------------------------
// Handle messages to the application
//--------------------------------------------------------------------------------------
LRESULT CALLBACK MsgProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool* pbNoFurtherProcessing,
                          void* pUserContext )
{
    // Pass messages to dialog resource manager calls so GUI state is updated correctly
    *pbNoFurtherProcessing = g_DialogResourceManager.MsgProc( hWnd, uMsg, wParam, lParam );
    if( *pbNoFurtherProcessing )
        return 0;

    // Pass messages to settings dialog if its active
    if( g_SettingsDlg.IsActive() )
    {
        g_SettingsDlg.MsgProc( hWnd, uMsg, wParam, lParam );
        return 0;
    }

    // Give the dialogs a chance to handle the message first
    *pbNoFurtherProcessing = g_HUD.MsgProc( hWnd, uMsg, wParam, lParam );
    if( *pbNoFurtherProcessing )
        return 0;
    *pbNoFurtherProcessing = g_SampleUI.MsgProc( hWnd, uMsg, wParam, lParam );
    if( *pbNoFurtherProcessing )
        return 0;

    // Pass all remaining windows messages to camera so it can respond to user input
    g_Camera.HandleMessages( hWnd, uMsg, wParam, lParam );

    return 0;
}


//--------------------------------------------------------------------------------------
// Handle key presses
//--------------------------------------------------------------------------------------
void CALLBACK OnKeyboard( UINT nChar, bool bKeyDown, bool bAltDown, void* pUserContext )
{
    switch (nChar)
    {
    case '1':
    case '2':
    case '3':
    case '4':
        {
            int group = (nChar - '1');
            CDXUTComboBox* pComboBox = g_SampleUI. GetComboBox( IDC_GROUP );
            assert(pComboBox != NULL);
            pComboBox->SetSelectedByData( IntToPtr( group ) );
            SetViewForGroup( group );
        }
        break;
    }
}


//--------------------------------------------------------------------------------------
// Handles the GUI events
//--------------------------------------------------------------------------------------
void CALLBACK OnGUIEvent( UINT nEvent, int nControlID, CDXUTControl* pControl, void* pUserContext )
{
    switch( nControlID )
    {
        case IDC_TOGGLEFULLSCREEN:
            DXUTToggleFullScreen(); break;
        case IDC_TOGGLEREF:
            DXUTToggleREF(); break;
        case IDC_CHANGEDEVICE:
            g_SettingsDlg.SetActive( !g_SettingsDlg.IsActive() ); break;
		case IDC_CHANGEBOX:
			kCurrentBoxIndex++;
			if (kCurrentBoxIndex > kShowBoxes)
			{
				kCurrentBoxIndex = 0;
			}
			break;
		case IDC_CHANGEBOX_DEC:
			kCurrentBoxIndex--;
			if (kCurrentBoxIndex < 0)
			{
				kCurrentBoxIndex = kShowBoxes;
			}
			break;
        case IDC_GROUP:
            {
                CDXUTComboBox* pComboBox = ( CDXUTComboBox* )pControl;
                SetViewForGroup( (int)PtrToInt( pComboBox->GetSelectedData() ) );
            }
            break;
    }
}


//--------------------------------------------------------------------------------------
// Release D3D9 resources created in the OnD3D9ResetDevice callback 
//--------------------------------------------------------------------------------------
void CALLBACK OnD3D9LostDevice( void* pUserContext )
{
    g_DialogResourceManager.OnD3D9LostDevice();
    g_SettingsDlg.OnD3D9LostDevice();
    if( g_pFont9 ) g_pFont9->OnLostDevice();

    SAFE_RELEASE( g_pVB );
    SAFE_RELEASE( g_pIB );

    if( g_pEffect9 ) g_pEffect9->OnLostDevice();
    SAFE_RELEASE( g_pSprite9 );
    SAFE_DELETE( g_pTxtHelper );
}


//--------------------------------------------------------------------------------------
// Release D3D9 resources created in the OnD3D9CreateDevice callback 
//--------------------------------------------------------------------------------------
void CALLBACK OnD3D9DestroyDevice( void* pUserContext )
{
    g_DialogResourceManager.OnD3D9DestroyDevice();
    g_SettingsDlg.OnD3D9DestroyDevice();
    SAFE_RELEASE( g_pEffect9 );
    SAFE_RELEASE( g_pFont9 );
    SAFE_RELEASE( g_pVertexDecl );
}


