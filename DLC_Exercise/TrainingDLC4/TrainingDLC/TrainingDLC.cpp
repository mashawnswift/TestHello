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


#define COMPASS_RADIUS	18.0f

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
TrainingDLC::TrainingDLC():
_bShowAirspeed(false),
_bArcMode(false)
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
	m_ChangeIdAttTrainingShowAirspeed = -1;
	m_ChangeIdAttTrainingCompassMode = -1;
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
	//用于按键字符的字体
	FontProperties fontPropRight = {
		pfTextALL,
		_T("微软雅黑"),/*宋体*/
		5.0,
		fwBOLD,
		false,
		false,
		taRIGHT,
		RGB(0, 255, 0),
		RGB( 0,255, 0)
	};
	//创建AGI对象
	_abstract = Agi::CreateAbstract(L"abs");
	_txtTraining = Agi::CreateText(&fontProp,L"trainText");
	_txtAirspeed = Agi::CreateText(&fontProp,L"airspeed");
	_txtBtn4 = Agi::CreateText(&fontPropRight,L"HIDE");
	//设置文字
	Agi::SetText(_txtTraining,L"练习页面");
	Agi::SetText(_txtAirspeed,L"空速:XXXkm/h");
	float txtLength(0.f);
	//获取字符串类型对象的长度
	Agi::GetTextLength(_txtAirspeed,txtLength);
	//创建矩形，作为空速字符的外框
	_rcAirspeed = Agi::CreateRect(txtLength+10,15,L"rect",goCenter);
	//创建罗盘的HAGI对象
	_compassAbstract = Agi::CreateAbstract(_T("Compass Abstract"));
	_compassCircle = Agi::CreateOval(COMPASS_RADIUS, COMPASS_RADIUS, _T("Compass"), goCenter);
	_txtNorth = Agi::CreateText(&fontProp, _T("North"));
	_txtEast = Agi::CreateText(&fontProp, _T("East"));
	_txtSouth = Agi::CreateText(&fontProp, _T("South"));
	_txtWest = Agi::CreateText(&fontProp, _T("West"));
	Agi::SetText(_txtNorth,L"N");
	Agi::SetText(_txtSouth,L"S");	
	Agi::SetText(_txtEast,L"E");		
	Agi::SetText(_txtWest,L"W");

	_txtBtn6 = Agi::CreateText(&fontPropRight, _T("Full or Arc"));
	agiRect rArcMaskRegion = {0.f, 0.f, 70.0f, 70.0f};
	_compassMask = Agi::CreateMaskRegion(rArcMaskRegion, _T("Compass Arc Mask Region"));

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
	Agi::Add(_txtBtn4,_abstract);
	Agi::Add(_txtAirspeed,_abstract);
	Agi::Add(_rcAirspeed,_txtAirspeed);
	float width(0);
	float height(0);
	//获取元件尺寸
	getElementSize(width,height);
	//设置对象位置，相对父对象，_abstract的默认位置是0,0
	Agi::SetXY(_txtTraining,width/2,height*5/6);
	Agi::SetXY(_txtAirspeed,width/2,height*4/6);
	Agi::SetXY(_txtBtn4,width,height*5/6-6.f);
	Agi::SetXY(_rcAirspeed,0,4);
	//构造罗盘
	Agi::Add(_compassAbstract, _hParentElement);
	Agi::Add(_compassCircle, _compassAbstract);
	Agi::Add(_txtNorth, _compassAbstract);
	Agi::Add(_txtSouth, _compassAbstract);
	Agi::Add(_txtEast, _compassAbstract);
	Agi::Add(_txtWest, _compassAbstract);

	Agi::SetXY(_compassAbstract, width* 0.5f, height * 0.3f);
	Agi::SetXY(_txtNorth, 0.0f, COMPASS_RADIUS);
	Agi::SetXY(_txtEast, COMPASS_RADIUS, 0.0f);
	Agi::SetXY(_txtSouth, 0.0f, -COMPASS_RADIUS);
	Agi::SetXY(_txtWest, -COMPASS_RADIUS, 0.0f);

	//Mask部分
	Agi::Add(_compassMask,_hParentElement);
	Agi::Add(_txtBtn6,_hParentElement);
	Agi::SetXY(_compassMask, width * 0.5f, 0.f);
	Agi::SetAng(_compassMask, -45.0f);
	Agi::SetXY(_txtBtn6,width,height*0.2);
	
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
	m_ChangeIdAttTrainingShowAirspeed = REGISTER_TO_ENTITY_ATT_CHANGE(_pOwnerEntity, _T("ATT_TRAINING_SHOW_AIRSPEED"), TrainingDLC, this, &TrainingDLC::CBFuncAttChangeTrainingShowAirspeed);
	m_ChangeIdAttTrainingCompassMode = REGISTER_TO_ENTITY_ATT_CHANGE(_pOwnerEntity, _T("ATT_TRAINING_COMPASS_MODE"), TrainingDLC, this, &TrainingDLC::CBFuncAttChangeTrainingCompassMode);
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
	CBFuncAttChangeTrainingShowAirspeed(GET_ENTITY_ATT_INDEX(_pOwnerEntity, _T("ATT_TRAINING_SHOW_AIRSPEED")));
	CBFuncAttChangeTrainingCompassMode(GET_ENTITY_ATT_INDEX(_pOwnerEntity, _T("ATT_TRAINING_COMPASS_MODE")));
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
	if (_bShowAirspeed)
	{
		float attIndicatedAirspeed = 0.0f;
		GET_ENTITY_ATT_BY_UNIT(_pOwnerEntity, _T("ATT_INDICATED_AIRSPEED"), attIndicatedAirspeed, UNIT_TYPE_DEFAULT);
		attIndicatedAirspeed *= MSTOKMH;
		CString str;
		str.Format(L"空速:%.1fkm/h",attIndicatedAirspeed);
		Agi::SetText(_txtAirspeed,str);

		float	fTrueHeading(0.f);
		GET_ENTITY_ATT_BY_UNIT(_pOwnerEntity, _T("ATT_HEADING_TRUE"), fTrueHeading, UNIT_TYPE_DEFAULT);
		if(_bArcMode)
			Agi::SetAng(_compassAbstract, -fTrueHeading+45.f);
		else
			Agi::SetAng(_compassAbstract, fTrueHeading);
		
		
		Agi::SetAng(_txtNorth, fTrueHeading);
		Agi::SetAng(_txtEast, fTrueHeading);
		Agi::SetAng(_txtSouth, fTrueHeading);
		Agi::SetAng(_txtWest, fTrueHeading);

	}
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
	UNREGISTER_FROM_ENTITY_ATT_CHANGE(_pOwnerEntity, _T("ATT_TRAINING_SHOW_AIRSPEED"), m_ChangeIdAttTrainingShowAirspeed);
	UNREGISTER_FROM_ENTITY_ATT_CHANGE(_pOwnerEntity, _T("ATT_TRAINING_COMPASS_MODE"), m_ChangeIdAttTrainingCompassMode);
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

bool TrainingDLC::CBFuncAttChangeTrainingShowAirspeed( const int i_attIndex)
{
	bool AttTrainingShowAirspeed = false;
	GET_ENTITY_ATT(_pOwnerEntity, i_attIndex, AttTrainingShowAirspeed);
	//根据状态切换空速的显示和按键边的字符
	if(AttTrainingShowAirspeed)
	{
		_bShowAirspeed = true;
		Agi::SetText(_txtBtn4,L"HIDE");
		Agi::Show(_txtAirspeed);
		Agi::Show(_compassAbstract);
	}
	else 
	{
		_bShowAirspeed = false;
		Agi::SetText(_txtBtn4,L"SHOW");
		Agi::Hide(_txtAirspeed);
		Agi::Hide(_compassAbstract);
	}
	return true;
}

bool TrainingDLC::CBFuncAttChangeTrainingCompassMode( const int i_attIndex)
{
	float width(0);
	float height(0);
	//获取元件尺寸
	getElementSize(width,height);
	GET_ENTITY_ATT(_pOwnerEntity, i_attIndex, _bArcMode);
	if(_bArcMode)
	{
		Agi::SetText(_txtBtn6,L"ARC");
		//放大罗盘
		Agi::Scale(_compassAbstract, 2.0f, 2.0f, true);
		Agi::SetXY(_compassAbstract,0.f, 0.f);
		//调整罗盘对象到mask下
		Agi::Detach(_compassAbstract);
		Agi::Add(_compassAbstract, _compassMask);
	}
	else
	{
		Agi::SetText(_txtBtn6,L"FULL");
		//恢复罗盘原有尺寸
		Agi::Scale(_compassAbstract, 1.0f, 1.0f, true);
		Agi::SetXY(_compassAbstract, width* 0.5f, height * 0.3f);
		//将罗盘对象调整到父元件对象下
		Agi::Detach(_compassAbstract);
		Agi::Add(_compassAbstract,_hParentElement);
	}
	return true;
}
//}}DLC_ATTRIBUTECHANGE_FUNC_IMPLEMENTATION