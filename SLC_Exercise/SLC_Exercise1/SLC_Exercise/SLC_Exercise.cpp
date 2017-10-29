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
//  Description : SLCÁ·Ï°
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
	_sDescription = _T("SLCÁ·Ï°");
	
	// TODO: set the update interval of the component (in seconds)
	// (0 - every frame, negative value - never)
	SET_UPDATE_INTERVAL_TIME(pOwnerEntity,0.0f);
	//{{SLC_PROPERTIES_VARIABLES_INIT
	m_PropSlcSquadNum = 0;
	//}}SLC_PROPERTIES_VARIABLES_INIT

	//{{SLC_GLOBALEVENT_VARIABLES_INIT
	//}}SLC_GLOBALEVENT_VARIABLES_INIT

	//{{SLC_ATTRIBUTECHANGE_VARIABLES_INIT
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
	REGISTER_ENTITY_CONTAINER_ATT(_pOwnerEntity,_T("ATT_SLC_SQUAD_NUM"), int &, (int)0, _T("Ð¡¶Ó±àºÅ"));
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
	REGISTER_PROPERTY(_pOwnerEntity, _T("PROP_SLC_SQUAD_NUM"), _T("Ð¡¶Ó±àºÅ"), PROPERTY_INT, _T("0"), 0, 100);
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
	//}}SLC_REGISTER_ATTRIBUTECHANGE
	
	//{{SLC_ATTRIBUTECHANGE_CALLS
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
	//}}SLC_UNREGISTER_ATTRIBUTECHANGE

	return true;
}


//{{SLC_ACTIONS_FUNC_IMPLEMENTATION

//}}SLC_ACTIONS_FUNC_IMPLEMENTATION

//{{SLC_ATTRIBUTES_FUNC_IMPLEMENTATION
//}}SLC_ATTRIBUTES_FUNC_IMPLEMENTATION

//{{SLC_INPUTEVENT_FUNC_IMPLEMENTATION
//}}SLC_INPUTEVENT_FUNC_IMPLEMENTATION

//{{SLC_GLOBALEVENT_FUNC_IMPLEMENTATION
//}}SLC_GLOBALEVENT_FUNC_IMPLEMENTATION

//{{SLC_ATTRIBUTECHANGE_FUNC_IMPLEMENTATION
//}}SLC_ATTRIBUTECHANGE_FUNC_IMPLEMENTATION
