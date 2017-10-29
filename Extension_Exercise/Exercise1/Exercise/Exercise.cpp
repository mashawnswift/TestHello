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
	//}}PLUGIN_PROPERTIES_VARIABLES_INIT

	//{{PLUGIN_INPUTEVENT_VARIABLES_INIT
	//}}PLUGIN_INPUTEVENT_VARIABLES_INIT

	//{{PLUGIN_GLOBALEVENT_VARIABLES_INIT
	//}}PLUGIN_GLOBALEVENT_VARIABLES_INIT

	//{{PLUGIN_ATTRIBUTECHANGE_VARIABLES_INIT
	//}}PLUGIN_ATTRIBUTECHANGE_VARIABLES_INIT
	
	
	SimApi::FrameWork::registerToUpdateCommandUI(this,this);


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
	//}}PLUGIN_PROPERTIES_VARIABLES_GET_VALUES

	//{{PLUGIN_REGISTER_ATTRIBUTECHANGE
	//}}PLUGIN_REGISTER_ATTRIBUTECHANGE

	//{{PLUGIN_ATTRIBUTECHANGE_CALLS
	//}}PLUGIN_ATTRIBUTECHANGE_CALLS

	//{{PLUGIN_REGISTER_GLOBALEVENT
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
	//
	// TODO: implement the logic updating code here
	//
	
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

//{{PLUGIN_ATTRIBUTES_FUNC_IMPLEMENTATION
//}}PLUGIN_ATTRIBUTES_FUNC_IMPLEMENTATION

//{{PLUGIN_INPUTEVENT_FUNC_IMPLEMENTATION
//}}PLUGIN_INPUTEVENT_FUNC_IMPLEMENTATION

//{{PLUGIN_GLOBALEVENT_FUNC_IMPLEMENTATION
//}}PLUGIN_GLOBALEVENT_FUNC_IMPLEMENTATION

//{{PLUGIN_ATTRIBUTECHANGE_FUNC_IMPLEMENTATION
//}}PLUGIN_ATTRIBUTECHANGE_FUNC_IMPLEMENTATION




