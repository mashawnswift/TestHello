///////////////////////////////////////////////////////////////////////////
//
//			-----------------------------
//			--     Developed by MSG  --
//			-----------------------------
//
//  File : VMU_Display.cpp
//
//  Author : MaShawn
//
//  Create Date : Sat Sep 23 12:53:42 UTC+0800 2017
//
//  Description : VMU显示
//	Address : JiangSu
//	E-Mail : mashawn@live.cn
//	Phone : +8613814443825
//
//////////////////////////////////////////////////////////////////////////


#pragma warning ( disable : 4284 4786 )

#include "StdAfx.h"


#include "VMU_Display.h"
#include "api.agi.h"
#include "api.Sim.h"
#include "sdk.Sim.h"
#include "resource.h"
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
	return new VMU_Display;
}


//==========================================================
// Description: constructor 
// 
// Author : MaShawn
//==========================================================
VMU_Display::VMU_Display()
{
	//
	// TODO: implement the constructor
	//

	// TODO: set the update interval of the component (in seconds)
	// (0 - every frame, negative value - never)
	_updateInterval = 0.5f;

	// TODO: write the description of the Object Component
	_sDescription = L"VMU显示";
	
	//{{DLC_PROPERTIES_VARIABLES_INIT
	//}}DLC_PROPERTIES_VARIABLES_INIT

	//{{DLC_GLOBALEVENT_VARIABLES_INIT
	//}}DLC_GLOBALEVENT_VARIABLES_INIT

	//{{DLC_ATTRIBUTECHANGE_VARIABLES_INIT
	m_ChangeIdAttVmuOvergWarning = -1;
	m_ChangeIdAttVmuAltitudeWarning = -1;
	m_ChangeIdAttVmuFlapsWarning = -1;
	m_ChangeIdAttVmuPullUpWarning = -1;
	m_ChangeIdAttVmuIsToDisplayAltitudeText = -1;
	//}}DLC_ATTRIBUTECHANGE_VARIABLES_INIT

	//{{DLC_HAGI_VARIABLES_INIT
	//}}DLC_HAGI_VARIABLES_INIT
	

}


//==========================================================
// Description: destructor
// 
// Author : MaShawn 
//==========================================================
VMU_Display::~VMU_Display()
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
bool VMU_Display::registerToInputDevices()
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
bool VMU_Display::init()
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
void VMU_Display::InitAttributesID()
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
void VMU_Display::CreateDisplayObjects()
{
	//{{DLC_HAGI_VARIABLES_DEFINITION
	//}}DLC_HAGI_VARIABLES_DEFINITION
	//获取DLC中心
	float	fElementWidth = 2.0f, fElementHeight = 2.0f;
	float	fHalfElementWidth = 1.0f, fHalfElementHeight = 1.0f;
	getElementSize(fElementWidth, fElementHeight);
	fHalfElementHeight = fElementHeight * 0.5f;
	fHalfElementWidth = fElementWidth * 0.5f;

	_txtAltitude = Agi::CreateText(NULL,L"Altitude Text");
	_txtOverG = Agi::CreateText(NULL,L"OverG Text");

	Agi::SetText(_txtOverG,L"OVER G");
	Agi::SetText(_txtAltitude,L"ALTITUDE");
	Agi::SetXY(_txtAltitude, fHalfElementWidth, fHalfElementHeight);
	Agi::SetXY(_txtOverG, fHalfElementWidth, fHalfElementHeight - 7);
	//创建 X标志
	_XAbstract = Agi::CreateAbstract(_T("XAbstract"));
	agiLine	XPart;
	XPart.start.x = 0.0f;
	XPart.start.y = 0.0f;
	XPart.end.x = fElementWidth;
	XPart.end.y = fElementHeight;
	_XPart1 = Agi::CreateLine(XPart, _T("X1"));
	//
	XPart.start.x = 0.0f;
	XPart.start.y = fElementHeight;
	XPart.end.x = fElementWidth;
	XPart.end.y = 0.0f;
	_XPart2 = Agi::CreateLine(XPart, _T("X2"));

	//创建箭头，并放在DLC中间
	_arrowAbstract = Agi::CreateAbstract(_T("Pullup Arrow Abstract"));
	Agi::SetXY(_arrowAbstract, fHalfElementWidth, fHalfElementHeight);
	//载入箭头位图
	HBITMAP	hArrow = MAKE_HBITMAP_RESOURCE(IDB_BITMAP1);
	_arrow = Agi::CreateRect(20.0f, 20.0f, _T("Arrow"), goCenter);
	Agi::SetXY(_arrow, 0.0f, fHalfElementHeight * 0.5f);
	//设置图片到矩形
	Agi::SetHBitmap(_arrow, hArrow);
	
}


//==========================================================
// Description: Builds the Display Objects hierarchy tree
// 
// Author : MaShawn 
//==========================================================
void VMU_Display::BuildDisplayObjectsHierarchyTree()
{
	Agi::Add(_txtAltitude, _hParentElement, false);
	Agi::Add(_txtOverG, _hParentElement, false);

	//构建拉起标志
	Agi::Add(_XAbstract, _hParentElement, false);
	Agi::Add(_XPart1, _XAbstract, true);
	Agi::Add(_XPart2, _XAbstract, true);
	//添加箭头HAGI
	Agi::Add(_arrowAbstract, _hParentElement, true);
	Agi::Add(_arrow, _arrowAbstract, true);
}


//==========================================================
// Description: initializing default properties
// 
// Author : MaShawn 
//==========================================================
void VMU_Display::InitDefaultProperties()
{
	// define the default properties structures
	FontProperties fontProperties = {
			pfTextALL,
			_T("Arial"),
			6.0,
			fwBOLD,
			false,
			false,
			taCENTER,
			RGB(255, 0, 0),
			RGB( 255,0, 0), // color of Background for inverse
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
bool VMU_Display::RegisterToAttributeChanges()
{
	//{{DLC_REGISTER_ATTRIBUTECHANGE
	m_ChangeIdAttVmuOvergWarning = REGISTER_TO_ENTITY_ATT_CHANGE(_pOwnerEntity, _T("ATT_VMU_OVERG_WARNING"), VMU_Display, this, &VMU_Display::CBFuncAttChangeVmuOvergWarning);
	m_ChangeIdAttVmuAltitudeWarning = REGISTER_TO_ENTITY_ATT_CHANGE(_pOwnerEntity, _T("ATT_VMU_ALTITUDE_WARNING"), VMU_Display, this, &VMU_Display::CBFuncAttChangeVmuAltitudeWarning);
	m_ChangeIdAttVmuFlapsWarning = REGISTER_TO_ENTITY_ATT_CHANGE(_pOwnerEntity, _T("ATT_VMU_FLAPS_WARNING"), VMU_Display, this, &VMU_Display::CBFuncAttChangeVmuFlapsWarning);
	m_ChangeIdAttVmuPullUpWarning = REGISTER_TO_ENTITY_ATT_CHANGE(_pOwnerEntity, _T("ATT_VMU_PULL_UP_WARNING"), VMU_Display, this, &VMU_Display::CBFuncAttChangeVmuPullUpWarning);
	m_ChangeIdAttVmuIsToDisplayAltitudeText = REGISTER_TO_ENTITY_ATT_CHANGE(_pOwnerEntity, _T("ATT_VMU_IS_TO_DISPLAY_ALTITUDE_TEXT"), VMU_Display, this, &VMU_Display::CBFuncAttChangeVmuIsToDisplayAltitudeText);
	//}}DLC_REGISTER_ATTRIBUTECHANGE
	
	return true;
}

//==========================================================
// Description: start function
// 
// Author : MaShawn 
//=========================================================
bool VMU_Display::start()
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
	CBFuncAttChangeVmuOvergWarning(GET_ENTITY_ATT_INDEX(_pOwnerEntity, _T("ATT_VMU_OVERG_WARNING")));
	CBFuncAttChangeVmuAltitudeWarning(GET_ENTITY_ATT_INDEX(_pOwnerEntity, _T("ATT_VMU_ALTITUDE_WARNING")));
	CBFuncAttChangeVmuFlapsWarning(GET_ENTITY_ATT_INDEX(_pOwnerEntity, _T("ATT_VMU_FLAPS_WARNING")));
	CBFuncAttChangeVmuPullUpWarning(GET_ENTITY_ATT_INDEX(_pOwnerEntity, _T("ATT_VMU_PULL_UP_WARNING")));
	CBFuncAttChangeVmuIsToDisplayAltitudeText(GET_ENTITY_ATT_INDEX(_pOwnerEntity, _T("ATT_VMU_IS_TO_DISPLAY_ALTITUDE_TEXT")));
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
void VMU_Display::GetPropertiesValues()
{
	//{{DLC_PROPERTIES_VARIABLES_GET_VALUES
	//}}DLC_PROPERTIES_VARIABLES_GET_VALUES
}

//==========================================================
// Description: update function
// 
// Author : 
//=========================================================
bool VMU_Display::update()
{
	//更新角度
	float attVmuPullUpWarningAngle = 0.0f;
	GET_ENTITY_ATT_BY_UNIT(_pOwnerEntity, _T("ATT_VMU_PULL_UP_WARNING_ANGLE"), attVmuPullUpWarningAngle, UNIT_TYPE_DEFAULT);
	Agi::SetAng(_arrowAbstract,attVmuPullUpWarningAngle);
	
	return true;
}

//==========================================================
// Description: end function
// 
// Author : MaShawn 
//==========================================================
bool VMU_Display::end()
{
	//{{DLC_UNREGISTER_GLOBALEVENT
	//}}DLC_UNREGISTER_GLOBALEVENT

	//{{DLC_UNREGISTER_ATTRIBUTECHANGE
	UNREGISTER_FROM_ENTITY_ATT_CHANGE(_pOwnerEntity, _T("ATT_VMU_OVERG_WARNING"), m_ChangeIdAttVmuOvergWarning);
	UNREGISTER_FROM_ENTITY_ATT_CHANGE(_pOwnerEntity, _T("ATT_VMU_ALTITUDE_WARNING"), m_ChangeIdAttVmuAltitudeWarning);
	UNREGISTER_FROM_ENTITY_ATT_CHANGE(_pOwnerEntity, _T("ATT_VMU_FLAPS_WARNING"), m_ChangeIdAttVmuFlapsWarning);
	UNREGISTER_FROM_ENTITY_ATT_CHANGE(_pOwnerEntity, _T("ATT_VMU_PULL_UP_WARNING"), m_ChangeIdAttVmuPullUpWarning);
	UNREGISTER_FROM_ENTITY_ATT_CHANGE(_pOwnerEntity, _T("ATT_VMU_IS_TO_DISPLAY_ALTITUDE_TEXT"), m_ChangeIdAttVmuIsToDisplayAltitudeText);
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
void VMU_Display::ValidatePropertiesValues()
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
bool VMU_Display::registerProperties()
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

bool VMU_Display::CBFuncAttChangeVmuOvergWarning( const int i_attIndex)
{
	bool AttVmuOvergWarning = false;
	GET_ENTITY_ATT(_pOwnerEntity, i_attIndex, AttVmuOvergWarning);
	
	if(AttVmuOvergWarning)
	{
		Agi::Show(_txtOverG);
		//发布语音事件
		SimApi::EventParams* eventParams = SimApi::EventsFactory::getEventInstance(_T("TextToSpeech"));
		eventParams->getParam(_T("Text"))->setValue( L"OVER G" );
		eventParams->getParam(_T("TextToDisplay"))->setValue( L"OVER G" );
		SimApi::EventHandler::publishEvent(eventParams);
	}
	else
		Agi::Hide(_txtOverG);
	return true;
}

bool VMU_Display::CBFuncAttChangeVmuAltitudeWarning( const int i_attIndex)
{
	bool AttVmuAltitudeWarning = false;
	GET_ENTITY_ATT(_pOwnerEntity, i_attIndex, AttVmuAltitudeWarning);
	if(AttVmuAltitudeWarning)
	{
		if(_bShowAltitudeTxt)
			Agi::Show(_txtAltitude);
		//发布语音事件
		SimApi::EventParams* eventParams = SimApi::EventsFactory::getEventInstance(_T("TextToSpeech"));
		eventParams->getParam(_T("TextToDisplay"))->setValue( L"Low Altitude");
		eventParams->getParam(_T("Text"))->setValue(L"Low Altitude");
		SimApi::EventHandler::publishEvent(eventParams);
	}
	else
		Agi::Hide(_txtAltitude);

	return true;
}

bool VMU_Display::CBFuncAttChangeVmuFlapsWarning( const int i_attIndex)
{
	bool AttVmuFlapsWarning = false;
	GET_ENTITY_ATT(_pOwnerEntity, i_attIndex, AttVmuFlapsWarning);
	if(AttVmuFlapsWarning)
	{
		//发布语音事件
		SimApi::EventParams* eventParams = SimApi::EventsFactory::getEventInstance(_T("TextToSpeech"));
		eventParams->getParam(_T("TextToDisplay"))->setValue( L"Retract Flaps");
		eventParams->getParam(_T("Text"))->setValue(L"Retract Flaps");
		SimApi::EventHandler::publishEvent(eventParams);
	}
	return true;
}

bool VMU_Display::CBFuncAttChangeVmuPullUpWarning( const int i_attIndex)
{
	bool AttVmuPullUpWarning = false;
	GET_ENTITY_ATT(_pOwnerEntity, i_attIndex, AttVmuPullUpWarning);
	if(AttVmuPullUpWarning)
	{
		//显示标志，并闪烁
		Agi::Show(_XAbstract);
		Agi::Show(_arrowAbstract);
		Agi::Blink(_XAbstract, 4);
		//发布语音事件
		SimApi::EventParams* eventParams = SimApi::EventsFactory::getEventInstance(_T("TextToSpeech"));
		eventParams->getParam(_T("TextToDisplay"))->setValue( L"PULL UP");
		eventParams->getParam(_T("Text"))->setValue(L"PULL UP");
		SimApi::EventHandler::publishEvent(eventParams);
		//设置更新间隔
		_updateInterval = 0.5f;
	}
	else
	{
		Agi::Hide(_XAbstract);
		Agi::Hide(_arrowAbstract);
		_updateInterval = -1.f;
	}
	return true;
}

bool VMU_Display::CBFuncAttChangeVmuIsToDisplayAltitudeText( const int i_attIndex)
{
	bool AttVmuIsToDisplayAltitudeText = false;
	GET_ENTITY_ATT(_pOwnerEntity, i_attIndex, AttVmuIsToDisplayAltitudeText);
	_bShowAltitudeTxt = AttVmuIsToDisplayAltitudeText;
	return true;
}
//}}DLC_ATTRIBUTECHANGE_FUNC_IMPLEMENTATION