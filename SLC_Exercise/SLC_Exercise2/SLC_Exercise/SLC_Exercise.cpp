 //////////////////////////////////////////////////////////////////////////
//
//			-----------------------------
//			--     Developed by MSG  --
//			-----------------------------
//
//  File		: SLC_Exercise.cpp
//
//  Author		: Shawn
//
//  Create Date : Mon Sep 4 13:57:02 UTC+0800 2017
//
//  Description : SLC练习
//	Address		: XuZhou JS
//	E-Mail		: mashawn@live.cn
//	Phone		: 13814443825
//
//////////////////////////////////////////////////////////////////////////

#pragma warning ( disable : 4284  4786 4251)

#include "StdAfx.h"

#include "SLC_Exercise.h"
#include "api.Sim.h"
#include "sdk.Sim.h"

LogicComponent* createComponent(Entity* pOwnerEntity)
{
	return new SLC_Exercise(pOwnerEntity);
}

SimApi::ComponentType getComponentType()
{
	return SimApi::ctSystem;
}

SimApi::ComponentRuntimeType getComponentRuntimeType()
{
	return SimApi::crtLogic;
}

//==========================================================
// Description	: constructor 
// 
// Author		: Shawn 
//==========================================================
SLC_Exercise::SLC_Exercise(Entity* pOwnerEntity):LogicComponent(pOwnerEntity)
{
	//
	// TODO: Implement the constructor
	//
	
	_sName = _T("SLC_Exercise.slc");

	// TODO: write the description of the Object Component
	_sDescription = _T("SLC练习");
	
	// TODO: set the update interval of the component (in seconds)
	// (0 - every frame, negative value - never)
	SET_UPDATE_INTERVAL_TIME(pOwnerEntity,0.0f);
	//{{SLC_PROPERTIES_VARIABLES_INIT
	m_PropSlcSquadNum = 0;
	//}}SLC_PROPERTIES_VARIABLES_INIT

	//{{SLC_GLOBALEVENT_VARIABLES_INIT
	//}}SLC_GLOBALEVENT_VARIABLES_INIT

	//{{SLC_ATTRIBUTECHANGE_VARIABLES_INIT
	m_ChangeIdAttSlcSquadNum = -1;
	//}}SLC_ATTRIBUTECHANGE_VARIABLES_INIT
	
}

//==========================================================
// Description	: destructor
// 
// Author		: Shawn 
//==========================================================
SLC_Exercise::~SLC_Exercise()
{
	//
	// TODO: Implement the destructor
	//
}
	
//==========================================================
// Description	: register Attributes here 
// 
// Author		: Shawn 
//==========================================================
bool SLC_Exercise::registerAttributes()
{ 
	//{{SLC_REGISTER_ATTRIBUTES
	REGISTER_ENTITY_CONTAINER_ATT(_pOwnerEntity,_T("ATT_SLC_SQUAD_NUM"), int &, (int)0, _T("小队编号"));
	REGISTER_ENTITY_ATTRIBUTE_SYSTEM(_pOwnerEntity, _T("ATT_SLC_SQUAD_NUM"), _T(""));
	REGISTER_ENTITY_ATTRIBUTE_VISIBILITY(_pOwnerEntity, _T("ATT_SLC_SQUAD_NUM"), true);
	//}}SLC_REGISTER_ATTRIBUTES

	return true;
}

//==========================================================
// Description	: register Actions here
// 
// Author		: Shawn 
//==========================================================
bool SLC_Exercise::registerActions()
{
	//{{SLC_REGISTER_ACTIONS
	REGISTER_ENTITY_ACTION(_pOwnerEntity, _T("ACTION_SLC_INCREMENT_SQUAD_NUM"), this, &SLC_Exercise::CBFuncActionSlcIncrementSquadNum, SLC_Exercise, _T("增大小队编号"));
	MARK_ENTITY_ACTION_AS_USER_INPUT(_pOwnerEntity, _T("ACTION_SLC_INCREMENT_SQUAD_NUM"), true);
	REGISTER_ENTITY_ACTION(_pOwnerEntity, _T("ACTION_SLC_TEST"), this, &SLC_Exercise::CBFuncActionSlcTest, SLC_Exercise, _T("test"));
	MARK_ENTITY_ACTION_AS_USER_INPUT(_pOwnerEntity, _T("ACTION_SLC_TEST"), false);
	//}}SLC_REGISTER_ACTIONS
	return true;     	
}

//==========================================================
// Description	: register events
// 
// Author		: Shawn 
//==========================================================
bool SLC_Exercise::registerToInputDevices()
{
	//{{SLC_REGISTER_INPUTEVENT
	//}}SLC_REGISTER_INPUTEVENT
	return true;
}

//==========================================================
// Description	: register component's properties
// 
// Author		: Shawn
//==========================================================
bool SLC_Exercise::registerProperties()
{
	
	//{{SLC_REGISTER_PROPERTIES
	REGISTER_PROPERTY(_pOwnerEntity, _T("PROP_SLC_SQUAD_NUM"), _T("小队编号"), PROPERTY_INT, _T("0"), 0, 100);
	//}}SLC_REGISTER_PROPERTIES
	
	return true;
}

//==========================================================
// Description	: init()
// 
// Author		: Shawn 
//=========================================================
bool SLC_Exercise::init()
{
	//
	// TODO: Initialize the component's variables here
	//

	//{{SLC_SET_ATTRIBUTE_RANGES
	//}}SLC_SET_ATTRIBUTE_RANGES

	//{{SLC_PROPERTIES_VARIABLES_GET_VALUES
	GET_ENTITY_ATT(_pOwnerEntity, _T("PROP_SLC_SQUAD_NUM"), m_PropSlcSquadNum);
	//}}SLC_PROPERTIES_VARIABLES_GET_VALUES

	//{{SLC_REGISTER_GLOBALEVENT
	//}}SLC_REGISTER_GLOBALEVENT

	return true;

}

//==========================================================
// Description	: start logic component
// 
// Author		: Shawn
//=========================================================
bool SLC_Exercise::start()
{

	//{{SLC_REGISTER_ATTRIBUTECHANGE
	m_ChangeIdAttSlcSquadNum = REGISTER_TO_ENTITY_ATT_CHANGE(_pOwnerEntity, _T("ATT_SLC_SQUAD_NUM"), SLC_Exercise, this, &SLC_Exercise::CBFuncAttChangeSlcSquadNum);
	//}}SLC_REGISTER_ATTRIBUTECHANGE
	//{{SLC_ATTRIBUTECHANGE_CALLS
	CBFuncAttChangeSlcSquadNum(GET_ENTITY_ATT_INDEX(_pOwnerEntity, _T("ATT_SLC_SQUAD_NUM")));
	//}}SLC_ATTRIBUTECHANGE_CALLS
	SET_ENTITY_CONTAINER_ATT_VALUE(_pOwnerEntity, _T("ATT_SLC_SQUAD_NUM"), m_PropSlcSquadNum);
	return true;
}

//==========================================================
// Description	: update Logic Component
// 
// Author		: Shawn 
//=========================================================
bool SLC_Exercise::update()
{
	//
	// TODO: implement the logic updating code here
	//
	
	return true;
}

//==========================================================
// Description	: end function
// 
// Author		: Shawn 
//==========================================================
bool SLC_Exercise::end()
{

	//{{SLC_UNREGISTER_GLOBALEVENT
	//}}SLC_UNREGISTER_GLOBALEVENT

	//{{SLC_UNREGISTER_ATTRIBUTECHANGE
	UNREGISTER_FROM_ENTITY_ATT_CHANGE(_pOwnerEntity, _T("ATT_SLC_SQUAD_NUM"), m_ChangeIdAttSlcSquadNum);
	//}}SLC_UNREGISTER_ATTRIBUTECHANGE

	return true;
}


//{{SLC_ACTIONS_FUNC_IMPLEMENTATION

bool SLC_Exercise::CBFuncActionSlcIncrementSquadNum()
{

	//TODO: Implement function
	int attSlcSquadNum = 0;
	GET_ENTITY_ATT_BY_UNIT(_pOwnerEntity, _T("ATT_SLC_SQUAD_NUM"), attSlcSquadNum, UNIT_TYPE_DEFAULT);
	if(attSlcSquadNum < 100)
		attSlcSquadNum++;
	SET_ENTITY_CONTAINER_ATT_VALUE(_pOwnerEntity, _T("ATT_SLC_SQUAD_NUM"), attSlcSquadNum);
	return true;
}

bool SLC_Exercise::CBFuncActionSlcTest()
{

	//TODO: Implement function

	return true;
}
//}}SLC_ACTIONS_FUNC_IMPLEMENTATION

//{{SLC_ATTRIBUTES_FUNC_IMPLEMENTATION
//}}SLC_ATTRIBUTES_FUNC_IMPLEMENTATION

//{{SLC_INPUTEVENT_FUNC_IMPLEMENTATION
//}}SLC_INPUTEVENT_FUNC_IMPLEMENTATION

//{{SLC_GLOBALEVENT_FUNC_IMPLEMENTATION
//}}SLC_GLOBALEVENT_FUNC_IMPLEMENTATION

//{{SLC_ATTRIBUTECHANGE_FUNC_IMPLEMENTATION



bool SLC_Exercise::CBFuncAttChangeSlcSquadNum( const int i_attIndex)
{
	int AttSlcSquadNum = 0;
	GET_ENTITY_ATT_BY_UNIT(_pOwnerEntity, i_attIndex, AttSlcSquadNum, UNIT_TYPE_DEFAULT);

	//TODO: Implement function
	SimApi::EventParams* eventParams = SimApi::EventsFactory::getEventInstance(_T("PrintToScreen"));
//eventParams->getParam(_T("BgBlueColor"))->setValue( /*<paramValue:Integer>*/ );
//eventParams->getParam(_T("BgGreenColor"))->setValue( /*<paramValue:Integer>*/ );
//eventParams->getParam(_T("BgRedColor"))->setValue( /*<paramValue:Integer>*/ );
//eventParams->getParam(_T("BlueColor"))->setValue( /*<paramValue:Integer>*/ );
//eventParams->getParam(_T("Color"))->setValue( /*<paramValue:String>*/ );
//eventParams->getParam(_T("DisplayContinues"))->setValue( /*<paramValue:Bool>*/ );
//eventParams->getParam(_T("DisplayTime"))->setValue( /*<paramValue:Float>*/ );
//eventParams->getParam(_T("FreezeTimeMs"))->setValue( /*<paramValue:Integer>*/ );
//eventParams->getParam(_T("GreenColor"))->setValue( /*<paramValue:Integer>*/ );
//eventParams->getParam(_T("IsAlertMessage"))->setValue( /*<paramValue:Bool>*/ );
//eventParams->getParam(_T("IsBlink"))->setValue( /*<paramValue:Bool>*/ );
//eventParams->getParam(_T("IsDebriefCheck"))->setValue( /*<paramValue:Bool>*/ );
//eventParams->getParam(_T("IsMessageCheck"))->setValue( /*<paramValue:Bool>*/ );
//eventParams->getParam(_T("IsRightToLeft"))->setValue( /*<paramValue:Bool>*/ );
//eventParams->getParam(_T("IsSyncMessage"))->setValue( /*<paramValue:Bool>*/ );
//eventParams->getParam(_T("IsVoiceCheck"))->setValue( /*<paramValue:Bool>*/ );
	CString str;
	str.Format(L"当前小队编号:%d",AttSlcSquadNum );
	eventParams->getParam(_T("Message"))->setValue( str);
//eventParams->getParam(_T("NumberOfParams"))->setValue( /*<paramValue:Integer>*/ );
//eventParams->getParam(_T("Param1"))->setValue( /*<paramValue:String>*/ );
//eventParams->getParam(_T("Param2"))->setValue( /*<paramValue:String>*/ );
//eventParams->getParam(_T("Param3"))->setValue( /*<paramValue:String>*/ );
//eventParams->getParam(_T("Param4"))->setValue( /*<paramValue:String>*/ );
//eventParams->getParam(_T("RedColor"))->setValue( /*<paramValue:Integer>*/ );
SimApi::EventHandler::publishEvent(eventParams);

	return true;
}
//}}SLC_ATTRIBUTECHANGE_FUNC_IMPLEMENTATION
