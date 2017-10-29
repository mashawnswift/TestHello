//////////////////////////////////////////////////////////////////////////
//
//			-----------------------------
//			--     Developed by MSG  --
//			-----------------------------
//
//  File		: Exercise.cpp
//
//  Author		: Shawn
//
//  Create Date : Mon Sep 25 13:45:58 UTC+0800 2017
//
//  Description : 插件练习
//	Address		: XuZhou JS
//	E-Mail		: mashawn@live.cn
//	Phone		: 13814443825
//
//////////////////////////////////////////////////////////////////////////

#include "stdAfx.h"
#include "resource.h"

#include "Exercise.h"
#include "api.Sim.h"
#include "sdk.Sim.h"
#include "api.FrameWork.h"

#define PLUGIN_NAME _T("MSG_Exercise")

#define MENU_NAME _T("插件练习")

// Static members:
Exercise* Exercise::m_instance = NULL;

// global instance of dll
HINSTANCE g_Instance;

static AFX_EXTENSION_MODULE pluginDLL = { NULL, NULL };

BOOL APIENTRY DllMain( HINSTANCE hModule, 
					   DWORD  ul_reason_for_call, 
					   LPVOID lpReserved )
{
    switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		
		// save instance
		g_Instance = hModule;
		
		// when this DLL attached by process it automatically 
		// load itself to the simulation environment as plug-in
		SimApi::Control::loadPlugin(PLUGIN_NAME,Exercise::getInstance());
	
		// Extension DLL one-time initialization
		if (!AfxInitExtensionModule(pluginDLL , g_Instance))
			return 0;
		
		new CDynLinkLibrary(pluginDLL );

		break;
		
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:

		// Terminate the library before destructors are called
		AfxTermExtensionModule(pluginDLL );
		
		break;
    }
    return TRUE;
}


//==========================================================
// Description: Exported function for getting the singleton
//				instance from the plug-in DLL
// Author : Shawn 
//==========================================================
PluginInterface* getPluginInstance()
{	
	return Exercise::getInstance();

}

//==========================================================
// Description: get singleton instance
// 
// Author : Shawn 
//==========================================================
Exercise* Exercise::getInstance()
{
	if (m_instance == NULL)
	{
		m_instance = new Exercise;
	}

	return m_instance;
}


//==========================================================
// Description: constructor 
// 
// Author : Shawn 
//==========================================================
Exercise::Exercise()
{
	//
	// TODO: Implement the constructor
	//
	
	// TODO: set the update interval of the component (in seconds)
	// (0 - every frame, negative value - never)
	setUpdateInterval(0.0f);


	//{{PLUGIN_PROPERTIES_VARIABLES_INIT
	m_GlobalPropExercisePower = 100;
	m_GlobalPropExerciseObject1Name =_T("Cessna实体");
	m_GlobalPropExerciseObject2Name =_T("Bell实体");
	//}}PLUGIN_PROPERTIES_VARIABLES_INIT

	//{{PLUGIN_INPUTEVENT_VARIABLES_INIT
	//}}PLUGIN_INPUTEVENT_VARIABLES_INIT

	//{{PLUGIN_GLOBALEVENT_VARIABLES_INIT
	m_EventIdSurfaceCockpitInit = -1;
m_EventIdSurfaceCockpitRender = -1;
m_EventIdSurfaceCockpitEnd = -1;
m_EventIdMainWindowSurfaceEnd = -1;
m_EventIdMainWindowSurfaceInit = -1;
m_EventIdMainWindowSurfaceRender = -1;
m_EventIdSceneWindowResize = -1;
//}}PLUGIN_GLOBALEVENT_VARIABLES_INIT

	//{{PLUGIN_ATTRIBUTECHANGE_VARIABLES_INIT
	//}}PLUGIN_ATTRIBUTECHANGE_VARIABLES_INIT
	
	
	SimApi::FrameWork::registerToUpdateCommandUI(this,this);
	_iCreateEntityNum = 0;

}

//==========================================================
// Description: virtual destructor
// 
// Author : Shawn 
//==========================================================
Exercise::~Exercise()
{
	//
	// TODO: Implement the destructor
	//
}

//==========================================================
// Description: register plug-in properties
// 
// Author : Shawn 
//==========================================================
bool Exercise::registerProperties()
{
	//{{PLUGIN_REGISTER_PROPERTIES
	REGISTER_GLOBAL_PROPERTY(_T("GLOBAL_PROP_EXERCISE_POWER"), _T("爆炸威力"), PROPERTY_INT, _T("100"), 0, 1000);
	REGISTER_GLOBAL_PROPERTY(_T("GLOBAL_PROP_EXERCISE_OBJECT1_NAME"), _T("由第一种对象创建的实体名"), PROPERTY_STRING, _T("Cessna实体"));
	REGISTER_GLOBAL_PROPERTY(_T("GLOBAL_PROP_EXERCISE_OBJECT2_NAME"), _T("由第二种对象创建的实体名"), PROPERTY_STRING, _T("Bell实体"));
	//}}PLUGIN_REGISTER_PROPERTIES

	return true;
}

//==========================================================
// Description: register plug-in attributes.
// 
// Author : Shawn 
//==========================================================
bool Exercise::registerAttributes()
{
	//{{PLUGIN_REGISTER_ATTRIBUTES
	//}}PLUGIN_REGISTER_ATTRIBUTES
	
	return true;
}
	
//==========================================================
// Description: initialize plug-in
//				this function is called after all the plug-ins
//				were created and before the function start() called
//				if the function return false, the plug-in will 
//				not be started
// 
// Author : Shawn 
//==========================================================
bool Exercise::init()
{
	//
	// TODO: Initialize the component's variables here
	//
	
	//{{PLUGIN_SET_ATTRIBUTE_RANGES
	//}}PLUGIN_SET_ATTRIBUTE_RANGES

	//{{PLUGIN_PROPERTIES_VARIABLES_GET_VALUES
	GET_GLOBAL_ATT(_T("GLOBAL_PROP_EXERCISE_POWER"), m_GlobalPropExercisePower);
	GET_GLOBAL_ATT(_T("GLOBAL_PROP_EXERCISE_OBJECT1_NAME"), m_GlobalPropExerciseObject1Name);
	GET_GLOBAL_ATT(_T("GLOBAL_PROP_EXERCISE_OBJECT2_NAME"), m_GlobalPropExerciseObject2Name);
	//}}PLUGIN_PROPERTIES_VARIABLES_GET_VALUES

	//{{PLUGIN_REGISTER_ATTRIBUTECHANGE
	//}}PLUGIN_REGISTER_ATTRIBUTECHANGE

	//{{PLUGIN_ATTRIBUTECHANGE_CALLS
	//}}PLUGIN_ATTRIBUTECHANGE_CALLS

	//{{PLUGIN_REGISTER_GLOBALEVENT
	m_EventIdSurfaceCockpitInit = SimApi::EventHandler::registerListener(_T("SurfaceCockpitInit"), EVENT_CALLBACK(this, &Exercise::CBFuncGlobalEventSurfaceCockpitInit, Exercise));
	m_EventIdSurfaceCockpitRender = SimApi::EventHandler::registerListener(_T("SurfaceCockpitRender"), EVENT_CALLBACK(this, &Exercise::CBFuncGlobalEventSurfaceCockpitRender, Exercise));
	m_EventIdSurfaceCockpitEnd = SimApi::EventHandler::registerListener(_T("SurfaceCockpitEnd"), EVENT_CALLBACK(this, &Exercise::CBFuncGlobalEventSurfaceCockpitEnd, Exercise));
	m_EventIdMainWindowSurfaceEnd = SimApi::EventHandler::registerListener(_T("MainWindowSurfaceEnd"), EVENT_CALLBACK(this, &Exercise::CBFuncGlobalEventMainWindowSurfaceEnd, Exercise));
	m_EventIdMainWindowSurfaceInit = SimApi::EventHandler::registerListener(_T("MainWindowSurfaceInit"), EVENT_CALLBACK(this, &Exercise::CBFuncGlobalEventMainWindowSurfaceInit, Exercise));
	m_EventIdMainWindowSurfaceRender = SimApi::EventHandler::registerListener(_T("MainWindowSurfaceRender"), EVENT_CALLBACK(this, &Exercise::CBFuncGlobalEventMainWindowSurfaceRender, Exercise));
	m_EventIdSceneWindowResize = SimApi::EventHandler::registerListener(_T("SceneWindowResize"), EVENT_CALLBACK(this, &Exercise::CBFuncGlobalEventSceneWindowResize, Exercise));
	//}}PLUGIN_REGISTER_GLOBALEVENT

	// load menu from resource
	m_menuHandle = LoadMenu(g_Instance, MAKEINTRESOURCE(IDR_MENU));

	// add to main menu
	SimApi::FrameWork::appendMenu((HMENU)SimApi::Control::getMainHMENU(),
		MF_POPUP| MF_ENABLED,(UINT)m_menuHandle ,MENU_NAME,this);
	
	// 创建工具栏
	_ToolBar.CreateEx( SimApi::Control::getMainWindowObject(), TBSTYLE_FLAT,
		WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC|CBRS_BORDER_ANY );
	_ToolBar.LoadToolBar( IDR_TOOLBAR1 );
	_ToolBar.SetWindowText(L"练习工具栏");
	_ToolBar.EnableDocking(CBRS_ALIGN_ANY);

	((CMDIFrameWnd*)AfxGetMainWnd())->DockControlBar(&_ToolBar,AFX_IDW_DOCKBAR_TOP);
	((CMDIFrameWnd*)AfxGetMainWnd())->ShowControlBar(&_ToolBar,TRUE,TRUE);
	// 将工具栏注册到SimApi框架
	SimApi::FrameWork::registerToolBar( &_ToolBar, this );
	return true;
}

//==========================================================
// Description: start plug-in activities
//				this function is called after all the plug-ins were
//				initiated and before the first time the function update()
//				is called
// 
// Author : Shawn 
//==========================================================
bool Exercise::start()
{
	//获取受控实体的ID
	_controlledEntityID= SimApi::Entities::getSelectedEntityId();
	return true;
}

//==========================================================
// Description: update plug-in
//				this function called cyclically up-on the
//				interval time ( _updateInterval )
// 
// Author : Shawn 
//==========================================================
bool Exercise::update()
{
	//获取受控实体信息
	float attIndicatedAirspeed = 0.0f;
	GET_OTHER_ENTITY_ATT_BY_UNIT(_controlledEntityID, _T("ATT_INDICATED_AIRSPEED"), attIndicatedAirspeed, UNIT_TYPE_DEFAULT);
	std::wstring attDisplayName;
	GET_OTHER_ENTITY_ATT(_controlledEntityID, EntityWorld::ATT_DISPLAY_NAME, attDisplayName);
	float attHeight = 0.0f;
	GET_OTHER_ENTITY_ATT_BY_UNIT(_controlledEntityID, EntityWorld::ATT_HEIGHT, attHeight, UNIT_TYPE_DEFAULT);

	_strAirspeed.Format(L"空速:%.1f",attIndicatedAirspeed);
	_strName = attDisplayName.c_str();
	_strHeight.Format(L"高度:%d",(int)attHeight);
	return true;
}

//==========================================================
// Description: reset the plug-in
//				this function called when the plug-in requested
//				to reset its status to the initiate status
// 
// Author : Shawn 
//==========================================================
bool Exercise::reset()
{
	//
	// TODO: implement the logic reset code here
	//
	
	return true;
}

//==========================================================
// Description: stop plug-in 
//				this function is called before the plug-in
//				end its life.
// 
// Author : Shawn 
//==========================================================
bool Exercise::end()
{
	//{{PLUGIN_UNREGISTER_INPUTEVENT
	//}}PLUGIN_UNREGISTER_INPUTEVENT

	//{{PLUGIN_UNREGISTER_GLOBALEVENT
	SimApi::EventHandler::unregisterListener(m_EventIdSurfaceCockpitInit);
	SimApi::EventHandler::unregisterListener(m_EventIdSurfaceCockpitRender);
	SimApi::EventHandler::unregisterListener(m_EventIdSurfaceCockpitEnd);
	SimApi::EventHandler::unregisterListener(m_EventIdMainWindowSurfaceEnd);
	SimApi::EventHandler::unregisterListener(m_EventIdMainWindowSurfaceInit);
	SimApi::EventHandler::unregisterListener(m_EventIdMainWindowSurfaceRender);
	SimApi::EventHandler::unregisterListener(m_EventIdSceneWindowResize);
	//}}PLUGIN_UNREGISTER_GLOBALEVENT

	//{{PLUGIN_UNREGISTER_ATTRIBUTECHANGE
	//}}PLUGIN_UNREGISTER_ATTRIBUTECHANGE
	return true;
}

//==========================================================
// Description: register plug-in to  input events
// 
// Author : Shawn 
//==========================================================
bool Exercise::registerToInputDevices() 
{
	
	//{{PLUGIN_REGISTER_INPUTEVENT
	//}}PLUGIN_REGISTER_INPUTEVENT
	return true;
}

//==========================================================
// Description: on update command notifier. 
// 
// Author : Shawn 
//==========================================================
bool Exercise::OnUpdateCommandUI(CCmdUI * pCmd)
{
	//
	// TODO: implement the handling of UI commands here
	//
	
	return true;
}

//==========================================================
// Description: on command notifier. this function will be called when
// some menu item has been clicked.
// 
// Author : Shawn 
//==========================================================
bool Exercise::OnCommand( UINT nCmdId )
{
	// TODO: implement the handling of menu commands here
	if( nCmdId == ID_SET_INVULNERABLE||nCmdId == ID_BTN_SET_INVULNERABLE)
	{
		CALL_OTHER_ENTITY_ACTION_1(_controlledEntityID, _T("ACTION_SET_IS_INVULNERABLE"), true );
	}
	else if(nCmdId == ID_EXPLOSION_PUBLISH || nCmdId == ID_BTN_EXPLOSION)
	{
		publishExplosion(m_GlobalPropExercisePower);
	}
	switch(nCmdId)
	{
	case ID_ENTITY_BELL://建立Bell直升机
			CreateMyEntitity(m_GlobalPropExerciseObject2Name.c_str(), L"Bell 412");
		break;
	case ID_ENTITY_CESSNA://建立Cessna飞机
			CreateMyEntitity(m_GlobalPropExerciseObject1Name, L"Cessna172SP");
		break;

	}
	return true;
}

//==========================================================
// Description:  this function will be called when pop-up menu
// is about to be initialized.
// 
// Author : Shawn 
//==========================================================
bool Exercise::OnInitPopupMenu( WPARAM wParam , LPARAM lParam )
{
	//
	// TODO: implement the handling of the popup menu initialization here
	//

	return true;
}

void Exercise::publishExplosion( int iPower )
{
	// Publish Explosion
	SimApi::EventParams* eventParams = SimApi::EventsFactory::getEventInstance(_T("Explosion"));
	eventParams->getParam(_T("Power"))->setValue( iPower );
	eventParams->getParam(_T("EntityID"))->setValue( _controlledEntityID);
	SimApi::EventHandler::publishEvent(eventParams);
}

void Exercise::CreateMyEntitity(wstring entityName, wstring baseObjetcName)
{
	_iCreateEntityNum ++;//创建的实体数量++
	WCHAR Wch[40];
	wstring str;
	//生成实体名
	swprintf(Wch,L"%d",_iCreateEntityNum);
	str = Wch;
	entityName =entityName+str;
	//创建实体
	int newEntityID = SimApi::Entities::createEntity(entityName,baseObjetcName);
	
	Location  Loc;
	LinearVec Vec;
	//获取当前控制实体的位置和速度
	GET_OTHER_ENTITY_ATT_BY_UNIT(_controlledEntityID, EntityWorld::ATT_LOCATION,Loc, UNIT_TYPE_DEFAULT); 
	GET_OTHER_ENTITY_ATT_BY_UNIT(_controlledEntityID, EntityWorld::ATT_ABS_VELOCITY,Vec, UNIT_TYPE_DEFAULT);
	//按照当前受控实体的位置和速度初始化新建实体的运动模型
	CALL_OTHER_ENTITY_ACTION_2(newEntityID, EntityWorld::ACTION_START_MODEL_MOTION,Loc, Vec);
	CALL_OTHER_ENTITY_ACTION_1(newEntityID, EntityWorld::ACTION_SET_DISPLAY_NAME, entityName);
}
//{{PLUGIN_ATTRIBUTES_FUNC_IMPLEMENTATION
//}}PLUGIN_ATTRIBUTES_FUNC_IMPLEMENTATION

//{{PLUGIN_INPUTEVENT_FUNC_IMPLEMENTATION
//}}PLUGIN_INPUTEVENT_FUNC_IMPLEMENTATION

//{{PLUGIN_GLOBALEVENT_FUNC_IMPLEMENTATION
void Exercise::CBFuncGlobalEventSurfaceCockpitInit( const SimApi::EventParams* i_Param )
{

	int iCameraId = 0;
	i_Param->getParam(_T("CameraId"))->getValue( iCameraId);
	std::wstring sCameraName;
	i_Param->getParam(_T("CameraName"))->getValue( sCameraName);
	std::wstring sCameraReferenceName;
	i_Param->getParam(_T("CameraReferenceName"))->getValue( sCameraReferenceName);
	int iEntityID1 = 0;
	i_Param->getParam(_T("EntityID1"))->getValue( iEntityID1);
	int iEntityID2 = 0;
	i_Param->getParam(_T("EntityID2"))->getValue( iEntityID2);
	int iHWND = 0;
	i_Param->getParam(_T("HWND"))->getValue( iHWND);
	int iScaleHandle = 0;
	i_Param->getParam(_T("ScaleHandle"))->getValue( iScaleHandle);
	int iSceneEntityID = 0;
	i_Param->getParam(_T("SceneEntityID"))->getValue( iSceneEntityID);
	std::wstring sSceneName;
	i_Param->getParam(_T("SceneName"))->getValue( sSceneName);
	int iSurfaceHandle = 0;
	i_Param->getParam(_T("SurfaceHandle"))->getValue( iSurfaceHandle);

	//TODO: Implement function
}

void Exercise::CBFuncGlobalEventSurfaceCockpitRender( const SimApi::EventParams* i_Param )
{

	float fCameraFOV = 0.0f;
	i_Param->getParam(_T("CameraFOV"))->getValue( fCameraFOV);
	int iCameraId = 0;
	i_Param->getParam(_T("CameraId"))->getValue( iCameraId);
	std::wstring sCameraName;
	i_Param->getParam(_T("CameraName"))->getValue( sCameraName);
	float fCameraPitch = 0.0f;
	i_Param->getParam(_T("CameraPitch"))->getValue( fCameraPitch);
	std::wstring sCameraReferenceName;
	i_Param->getParam(_T("CameraReferenceName"))->getValue( sCameraReferenceName);
	float fCameraRoll = 0.0f;
	i_Param->getParam(_T("CameraRoll"))->getValue( fCameraRoll);
	float fCameraX = 0.0f;
	i_Param->getParam(_T("CameraX"))->getValue( fCameraX);
	float fCameraY = 0.0f;
	i_Param->getParam(_T("CameraY"))->getValue( fCameraY);
	float fCameraYaw = 0.0f;
	i_Param->getParam(_T("CameraYaw"))->getValue( fCameraYaw);
	float fCameraZ = 0.0f;
	i_Param->getParam(_T("CameraZ"))->getValue( fCameraZ);
	int iEntityID1 = 0;
	i_Param->getParam(_T("EntityID1"))->getValue( iEntityID1);
	int iEntityID2 = 0;
	i_Param->getParam(_T("EntityID2"))->getValue( iEntityID2);
	int iHWND = 0;
	i_Param->getParam(_T("HWND"))->getValue( iHWND);
	int iScaleHandle = 0;
	i_Param->getParam(_T("ScaleHandle"))->getValue( iScaleHandle);
	int iSceneEntityID = 0;
	i_Param->getParam(_T("SceneEntityID"))->getValue( iSceneEntityID);
	std::wstring sSceneName;
	i_Param->getParam(_T("SceneName"))->getValue( sSceneName);
	int iSurfaceHandle = 0;
	i_Param->getParam(_T("SurfaceHandle"))->getValue( iSurfaceHandle);

}

void Exercise::CBFuncGlobalEventSurfaceCockpitEnd( const SimApi::EventParams* i_Param )
{

	int iCameraId = 0;
	i_Param->getParam(_T("CameraId"))->getValue( iCameraId);
	std::wstring sCameraName;
	i_Param->getParam(_T("CameraName"))->getValue( sCameraName);
	std::wstring sCameraReferenceName;
	i_Param->getParam(_T("CameraReferenceName"))->getValue( sCameraReferenceName);
	int iEntityID1 = 0;
	i_Param->getParam(_T("EntityID1"))->getValue( iEntityID1);
	int iEntityID2 = 0;
	i_Param->getParam(_T("EntityID2"))->getValue( iEntityID2);
	int iHWND = 0;
	i_Param->getParam(_T("HWND"))->getValue( iHWND);
	int iScaleHandle = 0;
	i_Param->getParam(_T("ScaleHandle"))->getValue( iScaleHandle);
	int iSceneEntityID = 0;
	i_Param->getParam(_T("SceneEntityID"))->getValue( iSceneEntityID);
	int iSceneHandle = 0;
	i_Param->getParam(_T("SceneHandle"))->getValue( iSceneHandle);
	std::wstring sSceneName;
	i_Param->getParam(_T("SceneName"))->getValue( sSceneName);
	int iSurfaceHandle = 0;
	i_Param->getParam(_T("SurfaceHandle"))->getValue( iSurfaceHandle);

	//TODO: Implement function

}

void Exercise::CBFuncGlobalEventMainWindowSurfaceEnd( const SimApi::EventParams* i_Param )
{

	int iCameraId = 0;
	i_Param->getParam(_T("CameraId"))->getValue( iCameraId);
	std::wstring sCameraName;
	i_Param->getParam(_T("CameraName"))->getValue( sCameraName);
	std::wstring sCameraReferenceName;
	i_Param->getParam(_T("CameraReferenceName"))->getValue( sCameraReferenceName);
	int iEntityID1 = 0;
	i_Param->getParam(_T("EntityID1"))->getValue( iEntityID1);
	int iEntityID2 = 0;
	i_Param->getParam(_T("EntityID2"))->getValue( iEntityID2);
	int iHWND = 0;
	i_Param->getParam(_T("HWND"))->getValue( iHWND);
	int iScaleHandle = 0;
	i_Param->getParam(_T("ScaleHandle"))->getValue( iScaleHandle);
	int iSceneEntityID = 0;
	i_Param->getParam(_T("SceneEntityID"))->getValue( iSceneEntityID);
	std::wstring sSceneName;
	i_Param->getParam(_T("SceneName"))->getValue( sSceneName);
	int iSurfaceHandle = 0;
	i_Param->getParam(_T("SurfaceHandle"))->getValue( iSurfaceHandle);

	//TODO: Implement function

}

void Exercise::CBFuncGlobalEventMainWindowSurfaceInit( const SimApi::EventParams* i_Param )
{

	int iCameraId = 0;
	i_Param->getParam(_T("CameraId"))->getValue( iCameraId);
	std::wstring sCameraName;
	i_Param->getParam(_T("CameraName"))->getValue( sCameraName);
	std::wstring sCameraReferenceName;
	i_Param->getParam(_T("CameraReferenceName"))->getValue( sCameraReferenceName);
	int iEntityID1 = 0;
	i_Param->getParam(_T("EntityID1"))->getValue( iEntityID1);
	int iEntityID2 = 0;
	i_Param->getParam(_T("EntityID2"))->getValue( iEntityID2);
	int iHWND = 0;
	i_Param->getParam(_T("HWND"))->getValue( iHWND);
	int iScaleHandle = 0;
	i_Param->getParam(_T("ScaleHandle"))->getValue( iScaleHandle);
	int iSceneEntityID = 0;
	i_Param->getParam(_T("SceneEntityID"))->getValue( iSceneEntityID);
	std::wstring sSceneName;
	i_Param->getParam(_T("SceneName"))->getValue( sSceneName);
	int iSurfaceHandle = 0;
	i_Param->getParam(_T("SurfaceHandle"))->getValue( iSurfaceHandle);
	//TODO: Implement function
	//创建字体
	FontProperties fontProperties = {pfTextALL,L"黑体",1.0f,fwBOLD, false, false, taCENTER,
		RGB(0, 255, 0), RGB(0, 255, 0),};
	_txtAirspeed = Agi::CreateText(&fontProperties,L"Airspeed");
	_txtHeight = Agi::CreateText(&fontProperties,L"Height");
	_txtName  =Agi::CreateText(&fontProperties,L"Name");
	//获取窗口尺寸
	CRect windowRect;
	HWND hWnd = 0;
	hWnd = (HWND)iHWND;
	GetClientRect(hWnd,&windowRect);
	Agi::Add(_txtAirspeed,iSurfaceHandle);
	Agi::Add(_txtHeight,iSurfaceHandle);
	Agi::Add(_txtName,iSurfaceHandle);
	//根据窗口尺寸设置HAGI对象位置
	Agi::SetXY(_txtAirspeed,windowRect.Width()*0.1f,windowRect.Height()*0.9f);
	Agi::SetXY(_txtHeight,windowRect.Width()*0.9f,windowRect.Height()*0.9f);
	Agi::SetXY(_txtName,windowRect.Width()*0.5f,windowRect.Height()*0.9f);
	//根据窗口尺寸缩放
	Agi::Scale(_txtAirspeed,windowRect.Width()*0.006f,windowRect.Height()*0.012f);
	Agi::Scale(_txtName,windowRect.Width()*0.006f,windowRect.Height()*0.012f);
	Agi::Scale(_txtHeight,windowRect.Width()*0.006f,windowRect.Height()*0.012f);

}

void Exercise::CBFuncGlobalEventMainWindowSurfaceRender( const SimApi::EventParams* i_Param )
{

	float fCameraFOV = 0.0f;
	i_Param->getParam(_T("CameraFOV"))->getValue( fCameraFOV);
	int iCameraId = 0;
	i_Param->getParam(_T("CameraId"))->getValue( iCameraId);
	std::wstring sCameraName;
	i_Param->getParam(_T("CameraName"))->getValue( sCameraName);
	float fCameraPitch = 0.0f;
	i_Param->getParam(_T("CameraPitch"))->getValue( fCameraPitch);
	std::wstring sCameraReferenceName;
	i_Param->getParam(_T("CameraReferenceName"))->getValue( sCameraReferenceName);
	float fCameraRoll = 0.0f;
	i_Param->getParam(_T("CameraRoll"))->getValue( fCameraRoll);
	float fCameraX = 0.0f;
	i_Param->getParam(_T("CameraX"))->getValue( fCameraX);
	float fCameraY = 0.0f;
	i_Param->getParam(_T("CameraY"))->getValue( fCameraY);
	float fCameraYaw = 0.0f;
	i_Param->getParam(_T("CameraYaw"))->getValue( fCameraYaw);
	float fCameraZ = 0.0f;
	i_Param->getParam(_T("CameraZ"))->getValue( fCameraZ);
	int iEntityID1 = 0;
	i_Param->getParam(_T("EntityID1"))->getValue( iEntityID1);
	int iEntityID2 = 0;
	i_Param->getParam(_T("EntityID2"))->getValue( iEntityID2);
	int iHWND = 0;
	i_Param->getParam(_T("HWND"))->getValue( iHWND);
	int iScaleHandle = 0;
	i_Param->getParam(_T("ScaleHandle"))->getValue( iScaleHandle);
	int iSceneEntityID = 0;
	i_Param->getParam(_T("SceneEntityID"))->getValue( iSceneEntityID);
	std::wstring sSceneName;
	i_Param->getParam(_T("SceneName"))->getValue( sSceneName);
	int iSurfaceHandle = 0;
	i_Param->getParam(_T("SurfaceHandle"))->getValue( iSurfaceHandle);

	//TODO: Implement function
	Agi::SetText(_txtAirspeed,_strAirspeed);
	Agi::SetText(_txtHeight,_strHeight);
	Agi::SetText(_txtName,_strName);
}

void Exercise::CBFuncGlobalEventSceneWindowResize( const SimApi::EventParams* i_Param )
{

	int iHeight = 0;
	i_Param->getParam(_T("Height"))->getValue( iHeight);
	int iHWND = 0;
	i_Param->getParam(_T("HWND"))->getValue( iHWND);
	bool bIsMainWindow = false;
	i_Param->getParam(_T("isMainWindow"))->getValue( bIsMainWindow);
	int iWidth = 0;
	i_Param->getParam(_T("Width"))->getValue( iWidth);

	//TODO: Implement function
	Agi::SetXY(_txtAirspeed,(float)iWidth*0.1f,(float)iHeight*0.9f);
	Agi::SetXY(_txtHeight,(float)iWidth*0.9f,(float)iHeight*0.9f);
	Agi::SetXY(_txtName,(float)iWidth*0.5f,(float)iHeight*0.9f);

	Agi::Scale(_txtAirspeed,(float)iWidth*0.006f,(float)iHeight*0.012f,true);
	Agi::Scale(_txtName,(float)iWidth*0.006f,(float)iHeight*0.012f,true);
	Agi::Scale(_txtHeight,(float)iWidth*0.006f,(float)iHeight*0.012f,true);

}

//}}PLUGIN_GLOBALEVENT_FUNC_IMPLEMENTATION

//{{PLUGIN_ATTRIBUTECHANGE_FUNC_IMPLEMENTATION
//}}PLUGIN_ATTRIBUTECHANGE_FUNC_IMPLEMENTATION




