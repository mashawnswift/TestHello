 //////////////////////////////////////////////////////////////////////////
//
//			-----------------------------
//			--     Developed by MSG  --
//			-----------------------------
//
//  File		: MFDTrainingSLC.cpp
//
//  Author		: Shawn
//
//  Create Date : Tue Sep 19 10:57:37 UTC+0800 2017
//
//  Description : MFDTrainingµƒ≈‰Ã◊SLC
//	Address		: XuZhou JS
//	E-Mail		: mashawn@live.cn
//	Phone		: 13814443825
//
//////////////////////////////////////////////////////////////////////////

#pragma warning ( disable : 4284  4786 4251)

#include "StdAfx.h"

#include "MFDTrainingSLC.h"
#include "api.Sim.h"
#include "sdk.Sim.h"

LogicComponent* createComponent(Entity* pOwnerEntity)
{
	return new MFDTrainingSLC(pOwnerEntity);
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
MFDTrainingSLC::MFDTrainingSLC(Entity* pOwnerEntity):LogicComponent(pOwnerEntity)
{
	//
	// TODO: Implement the constructor
	//
	
	_sName = _T("MFDTrainingSLC.slc");

	// TODO: write the description of the Object Component
	_sDescription = _T("MFDTrainingµƒ≈‰Ã◊SLC");
	
	// TODO: set the update interval of the component (in seconds)
	// (0 - every frame, negative value - never)
	SET_UPDATE_INTERVAL_TIME(pOwnerEntity,0.0f);
	//{{SLC_PROPERTIES_VARIABLES_INIT
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
MFDTrainingSLC::~MFDTrainingSLC()
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
bool MFDTrainingSLC::registerAttributes()
{ 
	//{{SLC_REGISTER_ATTRIBUTES
	REGISTER_ENTITY_CONTAINER_ATT(_pOwnerEntity,_T("ATT_TRAINING_SHOW_AIRSPEED"), bool &, (bool)true, _T("Airspeedœ‘ æ◊¥Ã¨"));
	REGISTER_ENTITY_ATTRIBUTE_SYSTEM(_pOwnerEntity, _T("ATT_TRAINING_SHOW_AIRSPEED"), _T(""));
	REGISTER_ENTITY_ATTRIBUTE_VISIBILITY(_pOwnerEntity, _T("ATT_TRAINING_SHOW_AIRSPEED"), true);
	REGISTER_ENTITY_CONTAINER_ATT(_pOwnerEntity,_T("ATT_TRAINING_COMPASS_MODE"), bool &, (bool)true, _T("Full false;Arc true"));
	REGISTER_ENTITY_ATTRIBUTE_SYSTEM(_pOwnerEntity, _T("ATT_TRAINING_COMPASS_MODE"), _T(""));
	REGISTER_ENTITY_ATTRIBUTE_VISIBILITY(_pOwnerEntity, _T("ATT_TRAINING_COMPASS_MODE"), true);
	//}}SLC_REGISTER_ATTRIBUTES

	return true;
}

//==========================================================
// Description	: register Actions here
// 
// Author		: Shawn 
//==========================================================
bool MFDTrainingSLC::registerActions()
{
	//{{SLC_REGISTER_ACTIONS
	REGISTER_ENTITY_ACTION(_pOwnerEntity, _T("ACTION_TOGGLE_TRAINING_SHOW_AIRSPEED"), this, &MFDTrainingSLC::CBFuncActionToggleTrainingShowAirspeed, MFDTrainingSLC, _T("«–ªªAirspeedœ‘ æ"));
	MARK_ENTITY_ACTION_AS_USER_INPUT(_pOwnerEntity, _T("ACTION_TOGGLE_TRAINING_SHOW_AIRSPEED"), true);
	REGISTER_ENTITY_ACTION(_pOwnerEntity, _T("ACTION_TOGGLE_TRAINING_COMPASS_MODE"), this, &MFDTrainingSLC::CBFuncActionToggleTrainingCompassMode, MFDTrainingSLC, _T("«–ªª¬ﬁ≈Ãœ‘ æƒ£ Ω"));
	MARK_ENTITY_ACTION_AS_USER_INPUT(_pOwnerEntity, _T("ACTION_TOGGLE_TRAINING_COMPASS_MODE"), true);
	//}}SLC_REGISTER_ACTIONS
	return true;     	
}

//==========================================================
// Description	: register events
// 
// Author		: Shawn 
//==========================================================
bool MFDTrainingSLC::registerToInputDevices()
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
bool MFDTrainingSLC::registerProperties()
{
	
	//{{SLC_REGISTER_PROPERTIES
	//}}SLC_REGISTER_PROPERTIES
	
	return true;
}

//==========================================================
// Description	: init()
// 
// Author		: Shawn 
//=========================================================
bool MFDTrainingSLC::init()
{
	//
	// TODO: Initialize the component's variables here
	//

	//{{SLC_SET_ATTRIBUTE_RANGES
	//}}SLC_SET_ATTRIBUTE_RANGES

	//{{SLC_PROPERTIES_VARIABLES_GET_VALUES
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
bool MFDTrainingSLC::start()
{

	//{{SLC_REGISTER_ATTRIBUTECHANGE
	//}}SLC_REGISTER_ATTRIBUTECHANGE

	//{{SLC_ATTRIBUTECHANGE_CALLS
	//}}SLC_ATTRIBUTECHANGE_CALLS

	return true;
}

//==========================================================
// Description	: update Logic Component
// 
// Author		: Shawn 
//=========================================================
bool MFDTrainingSLC::update()
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
bool MFDTrainingSLC::end()
{

	//{{SLC_UNREGISTER_GLOBALEVENT
	//}}SLC_UNREGISTER_GLOBALEVENT

	//{{SLC_UNREGISTER_ATTRIBUTECHANGE
	//}}SLC_UNREGISTER_ATTRIBUTECHANGE

	return true;
}


//{{SLC_ACTIONS_FUNC_IMPLEMENTATION

bool MFDTrainingSLC::CBFuncActionToggleTrainingShowAirspeed()
{
	bool attTrainingShowAirspeed = false;
	GET_ENTITY_ATT(_pOwnerEntity, _T("ATT_TRAINING_SHOW_AIRSPEED"), attTrainingShowAirspeed);
	attTrainingShowAirspeed = !attTrainingShowAirspeed;
	SET_ENTITY_CONTAINER_ATT_VALUE(_pOwnerEntity, _T("ATT_TRAINING_SHOW_AIRSPEED"), attTrainingShowAirspeed);
	return true;
}

bool MFDTrainingSLC::CBFuncActionToggleTrainingCompassMode()
{
	bool attTrainingCompassMode = false;
	GET_ENTITY_ATT(_pOwnerEntity, _T("ATT_TRAINING_COMPASS_MODE"), attTrainingCompassMode);
	attTrainingCompassMode = !attTrainingCompassMode;
	SET_ENTITY_CONTAINER_ATT_VALUE(_pOwnerEntity, _T("ATT_TRAINING_COMPASS_MODE"), attTrainingCompassMode);
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
//}}SLC_ATTRIBUTECHANGE_FUNC_IMPLEMENTATION
