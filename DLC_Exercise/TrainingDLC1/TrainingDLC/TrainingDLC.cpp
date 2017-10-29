///////////////////////////////////////////////////////////////////////////
//
//			-----------------------------
//			--     Developed by MSG  --
//			-----------------------------
//
//  File : TrainingDLC.cpp
//
//  Author : MaShawn
//
//  Create Date : Sun Sep 17 11:13:10 UTC+0800 2017
//
//  Description : 练习DLC
//	Address : JiangSu
//	E-Mail : mashawn@live.cn
//	Phone : +8613814443825
//
//////////////////////////////////////////////////////////////////////////


#pragma warning ( disable : 4284 4786 )

#include "StdAfx.h"


#include "TrainingDLC.h"
#include "api.agi.h"
#include "api.Sim.h"
#include "sdk.Sim.h"

HINSTANCE g_Instance;

BOOL APIENTRY DllMain( HINSTANCE hModule, 
					   DWORD  ul_reason_for_call, 
					   LPVOID lpReserved )
{
    switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		
		// save instance
		g_Instance = hModule;
		
		break;
		
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:

		break;
    }
    return TRUE;
}

DisplayComponent* createComponent()
{
	return new TrainingDLC;
}


//==========================================================
// Description: constructor 
// 
// Author : MaShawn
//==========================================================
TrainingDLC::TrainingDLC()
{
	//
	// TODO: implement the constructor
	//

	// TODO: set the update interval of the component (in seconds)
	// (0 - every frame, negative value - never)
	_updateInterval = 0.1f;//设置更新间隔

	// TODO: write the description of the Object Component
	_sDescription = L"练习DLC";
	
	//{{DLC_PROPERTIES_VARIABLES_INIT
	//}}DLC_PROPERTIES_VARIABLES_INIT

	//{{DLC_GLOBALEVENT_VARIABLES_INIT
	//}}DLC_GLOBALEVENT_VARIABLES_INIT

	//{{DLC_ATTRIBUTECHANGE_VARIABLES_INIT
	//}}DLC_ATTRIBUTECHANGE_VARIABLES_INIT

	//{{DLC_HAGI_VARIABLES_INIT
	//}}DLC_HAGI_VARIABLES_INIT
	

}


//==========================================================
// Description: destructor
// 
// Author : MaShawn 
//==========================================================
TrainingDLC::~TrainingDLC()
{
	//
	// TODO: implement the destructor
	//
}


//==========================================================
// Description: register to input events
// 
// Author : MaShawn 
//==========================================================
bool TrainingDLC::registerToInputDevices()
{
	//{{DLC_REGISTER_INPUTEVENT
	//}}DLC_REGISTER_INPUTEVENT

	return true;
}


//==========================================================
// Description: init function
// 
// Author : MaShawn 
//=========================================================
bool TrainingDLC::init()
{	
	//
	// TODO: Initialize the component's variables here
	//
	
	//{{DLC_SET_ATTRIBUTE_RANGES
	//}}DLC_SET_ATTRIBUTE_RANGES

	//{{DLC_REGISTER_GLOBALEVENT
	//}}DLC_REGISTER_GLOBALEVENT

	return true;
}


//==========================================================
// Description: init attributes id's
// 
// Author : MaShawn 
//==========================================================
void TrainingDLC::InitAttributesID()
{
	//
	// TODO: implement the initialization of the attributes' ids
	//
}


//==========================================================
// Description: Create Display Objects
// 
// Author : MaShawn 
//==========================================================
void TrainingDLC::CreateDisplayObjects()
{
	//创建字体
	FontProperties fontProp = {
		pfTextALL,
		_T("微软雅黑"),/*宋体*/
		7.0,
		fwBOLD,
		false,
		false,
		taCENTER,
		RGB(0, 255, 0),
		RGB( 0,255, 0)// color of Background for inverse
	};
	//创建AGI对象
	_abstract = Agi::CreateAbstract(L"abs");
	_txtTraining = Agi::CreateText(&fontProp,L"trainText");
	//设置文字
	Agi::SetText(_txtTraining,L"TrainingPage 练习页面");
}


//==========================================================
// Description: Builds the Display Objects hierarchy tree
// 
// Author : MaShawn 
//==========================================================
void TrainingDLC::BuildDisplayObjectsHierarchyTree()
{
	//构造层级树
	Agi::Add(_abstract,_hParentElement);
	Agi::Add(_txtTraining,_abstract);
	float width(0);
	float height(0);
	//获取元件尺寸
	getElementSize(width,height);
	//设置对象位置，相对父对象，_abstract的默认位置是0,0
	Agi::SetXY(_txtTraining,width/2,height*5/6);
}


//==========================================================
// Description: initializing default properties
// 
// Author : MaShawn 
//==========================================================
void TrainingDLC::InitDefaultProperties()
{
	// define the default properties structures
	FontProperties fontProperties = {
			pfTextALL,
			_T("Arial"),
			8.0,
			fwBOLD,
			false,
			false,
			taLEFT,
			RGB(0, 255, 0),
			RGB( 0,255, 0), // color of Background for inverse
	};
	
	LineProperties lineProperties = {
			1.0f,
			lsNORMAL,
			RGB(0, 255, 0)
	};
	
	FillProperties fillProperties = {
			false,
			RGB(0, 255, 0)
	};
	
	// Applying default properties
	Agi::SetDefaultProperties(fontProperties, lineProperties, fillProperties);

	//
	// TODO: Implement the initialization of properties and attribute values here
	//
}


//==========================================================
// Description: register component to Attribute changes
// 
// Author : MaShawn 
//==========================================================
bool TrainingDLC::RegisterToAttributeChanges()
{
	//{{DLC_REGISTER_ATTRIBUTECHANGE
	//}}DLC_REGISTER_ATTRIBUTECHANGE
	
	return true;
}

//==========================================================
// Description: start function
// 
// Author : MaShawn 
//=========================================================
bool TrainingDLC::start()
{
	// get properties value from the DataBase
	GetPropertiesValues();

	// check properties validity
	ValidatePropertiesValues();

	// initialize attribute id's
	InitAttributesID();

	// initializing default properties
	InitDefaultProperties(); 
		
	// create Display Objects
	CreateDisplayObjects();
	
	// build agi objects
	BuildDisplayObjectsHierarchyTree();
	
	//register the mouse clickable regions
	registerAllMouseRegionsEvents();

	// Show the COC
	showDlc();

	// register to attribute changes
	RegisterToAttributeChanges();

	//{{DLC_ATTRIBUTECHANGE_CALLS
	//}}DLC_ATTRIBUTECHANGE_CALLS

	//
	// TODO: implement the display start code here
	//
	
	return true;
}

//==========================================================
// Description: get properties value from the DataBase
// 
// Author : MaShawn 
//=========================================================
void TrainingDLC::GetPropertiesValues()
{
	//{{DLC_PROPERTIES_VARIABLES_GET_VALUES
	//}}DLC_PROPERTIES_VARIABLES_GET_VALUES
}

//==========================================================
// Description: update function
// 
// Author : 
//=========================================================
bool TrainingDLC::update()
{
	
	//
	// TODO: implement the display updating code here
	//

	return true;
}

//==========================================================
// Description: end function
// 
// Author : MaShawn 
//==========================================================
bool TrainingDLC::end()
{
	//{{DLC_UNREGISTER_GLOBALEVENT
	//}}DLC_UNREGISTER_GLOBALEVENT

	//{{DLC_UNREGISTER_ATTRIBUTECHANGE
	//}}DLC_UNREGISTER_ATTRIBUTECHANGE
	
	// unregister All Mouse Regions Events
	unRegisterAllMouseRegionsEvents();



	return true;
}

//========================================================== 
// Description: check properties validity
// 
// Author :MaShawn 
//==========================================================
void TrainingDLC::ValidatePropertiesValues()
{
	//
	// TODO: Implement validity check for your properties here
	//
}

//==========================================================
// Description: register properties function
// 
// Author : MaShawn 
//==========================================================
bool TrainingDLC::registerProperties()
{
	//{{DLC_REGISTER_PROPERTIES
	//}}DLC_REGISTER_PROPERTIES

	return true;
}

//{{DLC_INPUTEVENT_FUNC_IMPLEMENTATION
//}}DLC_INPUTEVENT_FUNC_IMPLEMENTATION

//{{DLC_GLOBALEVENT_FUNC_IMPLEMENTATION
//}}DLC_GLOBALEVENT_FUNC_IMPLEMENTATION

//{{DLC_ATTRIBUTECHANGE_FUNC_IMPLEMENTATION
//}}DLC_ATTRIBUTECHANGE_FUNC_IMPLEMENTATION