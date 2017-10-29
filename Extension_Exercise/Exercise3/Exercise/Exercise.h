//////////////////////////////////////////////////////////////////////////
//
//			-----------------------------
//			--     Developed by MSG  --
//			-----------------------------
//
//  File		: Exercise.h
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


#ifndef Exercise_H
#define Exercise_H

#include "sdk.PluginInterface.h"
#include "sdk.UserMenuNotifier.h"
#include "sdk.SimOnUpdateCommandUI.h"

#ifdef Exercise_EXPORTS
#define Exercise_API __declspec(dllexport)
#else
#define Exercise_API __declspec(dllimport)
#endif

//{{GEN_PROJECT_DATA
#define SYSTEM_PREFIX "EXERCISE"
//}}GEN_PROJECT_DATA


#include <sdk.displayComponent.h>

class Exercise_API Exercise : public PluginInterface , 
										public UserMenuNotifier,
										public CSimOnUpdateCommandUI
{

public:

	// constructor
	Exercise();
	
	// destructor
	virtual ~Exercise();

	// initialize 
	virtual bool				init();

	// start
	virtual bool				start();

	// reset 
	virtual bool				reset();

	// end 
	virtual bool				end();

	// register plug-in to  input events
	virtual bool		registerToInputDevices() ;
	
	// register plug-in properties
	virtual bool		registerProperties();

	// register plug-in attributes.
	virtual bool		registerAttributes();

	// get the one and the only instance of this class
	static 	Exercise *		getInstance();

	// handle on command UI messages.
	virtual bool OnUpdateCommandUI(CCmdUI * pCmd);

	// on command notifier. this function will be called when
	// some menu item has been clicked.
	virtual bool OnCommand( UINT nCmdId );
	
	// this function will be called when pop-up menu
	// is about to be initialized.
	virtual bool OnInitPopupMenu( WPARAM wParam , LPARAM lParam );
	
	
	
	//{{PLUGIN_ATTRIBUTES_FUNC_DECLERATION
	//}}PLUGIN_ATTRIBUTES_FUNC_DECLERATION

	//{{PLUGIN_INPUTEVENT_FUNC_DECLERATION
	//}}PLUGIN_INPUTEVENT_FUNC_DECLERATION

	//{{PLUGIN_GLOBALEVENT_FUNC_DECLERATION
	void CBFuncGlobalEventSurfaceCockpitInit( const SimApi::EventParams* i_Param );
	void CBFuncGlobalEventSurfaceCockpitRender( const SimApi::EventParams* i_Param );
	void CBFuncGlobalEventSurfaceCockpitEnd( const SimApi::EventParams* i_Param );
	void CBFuncGlobalEventMainWindowSurfaceEnd( const SimApi::EventParams* i_Param );
	void CBFuncGlobalEventMainWindowSurfaceInit( const SimApi::EventParams* i_Param );
	void CBFuncGlobalEventMainWindowSurfaceRender( const SimApi::EventParams* i_Param );
	void CBFuncGlobalEventSceneWindowResize( const SimApi::EventParams* i_Param );
	//}}PLUGIN_GLOBALEVENT_FUNC_DECLERATION

	//{{PLUGIN_ATTRIBUTECHANGE_FUNC_DECLERATION
	//}}PLUGIN_ATTRIBUTECHANGE_FUNC_DECLERATION
	
		
protected:

	// update 
	virtual bool update();

	// MEMBER VARIABLES
private:
	void publishExplosion( int iPower);//发布爆炸
	//创建实体
	void CreateMyEntitity(wstring entityName, wstring baseObjetcName);
	// singleton instance
	static Exercise *		m_instance;

	HMENU m_menuHandle;

	//{{PLUGIN_PROPERTIES_VARIABLES_DECLERATION
	int m_GlobalPropExercisePower;
	std::wstring m_GlobalPropExerciseObject1Name;
	std::wstring m_GlobalPropExerciseObject2Name;
	//}}PLUGIN_PROPERTIES_VARIABLES_DECLERATION

	//{{PLUGIN_INPUTEVENT_VARIABLES_DECLERATION
	//}}PLUGIN_INPUTEVENT_VARIABLES_DECLERATION
	
	//{{PLUGIN_GLOBALEVENT_VARIABLES_DECLERATION
	int m_EventIdSurfaceCockpitInit;
	int m_EventIdSurfaceCockpitRender;
	int m_EventIdSurfaceCockpitEnd;
	int m_EventIdMainWindowSurfaceEnd;
	int m_EventIdMainWindowSurfaceInit;
	int m_EventIdMainWindowSurfaceRender;
	int m_EventIdSceneWindowResize;
	//}}PLUGIN_GLOBALEVENT_VARIABLES_DECLERATION
	
	//{{PLUGIN_ATTRIBUTECHANGE_VARIABLES_DECLERATION
	//}}PLUGIN_ATTRIBUTECHANGE_VARIABLES_DECLERATION
	CToolBar _ToolBar;
	int _controlledEntityID;//受控实体的ID
	int _iCreateEntityNum;//创建的实体数

	//HAGI对象
	HAGI _txtAirspeed;
	HAGI _txtName;
	HAGI _txtHeight;

	CString _strAirspeed;
	CString _strHeight;
	CString _strName;
};


#endif //PLUGIN_H

