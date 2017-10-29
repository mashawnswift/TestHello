//////////////////////////////////////////////////////////////////////////
//
//			-----------------------------
//			--     Developed by MSG  --
//			-----------------------------
//
//  File		: MFDComponentProject1.cpp
//
//  Author		: MaShawn
//
//  Create Date : Wed Sep 27 10:57:55 UTC+0800 2017
//
//  Description : MFD
//	Address		: JiangSu
//	E-Mail		: mashawn@live.cn
//	Phone		: +8613814443825
//
//////////////////////////////////////////////////////////////////////////

#pragma warning ( disable : 4284  4786 4251)

#include "StdAfx.h"
#include "MFDComponentProject1.h"
#include "api.agi.h"
#include "api.Sim.h"
#include "sdk.Sim.h"

HINSTANCE g_Instance;

BOOL APIENTRY DllMain(HINSTANCE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
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
	return new MFDComponentProject1;
}

//==========================================================
// Description	: constructor 
// 
// Author		: MaShawn
//==========================================================
MFDComponentProject1::MFDComponentProject1()
{
	// (0 - every frame, negative value - never)
	_updateInterval = 0.0f;

	// TODO: write the description of the Object Component
	_sDescription = L"MFD";

	//{{DLC_PROPERTIES_VARIABLES_INIT
	//}}DLC_PROPERTIES_VARIABLES_INIT

	//{{DLC_GLOBALEVENT_VARIABLES_INIT
	//}}DLC_GLOBALEVENT_VARIABLES_INIT

	//{{DLC_ATTRIBUTECHANGE_VARIABLES_INIT
	//}}DLC_ATTRIBUTECHANGE_VARIABLES_INIT
}

//==========================================================
// Description	: destructor
// 
// Author		: MaShawn 
//==========================================================
MFDComponentProject1::~MFDComponentProject1()
{
}

//==========================================================
// Description	: register to input events
// 
// Author		: MaShawn
//==========================================================
bool MFDComponentProject1::registerToInputDevices()
{
	//{{DLC_REGISTER_INPUTEVENT
		wstring inputStr = (wstring(L"INPUT_SMG_CHANGE_TO_TEST") + _sParentGaugeNameW);
	REGISTER_INPUT_EVENT_MULTIPLE(_pOwnerEntity, this, &MFDComponentProject1::CBFuncInputEventSmgChangeToTESTPage, MFDComponentProject1, inputStr.c_str(), L"Changes the MFD to the TEST page.");
		//}}DLC_REGISTER_INPUTEVENT

	return true;
}

//==========================================================
// Description	: init function
// 
// Author		: MaShawn 
//=========================================================
bool MFDComponentProject1::init()
{
	//{{DLC_SET_ATTRIBUTE_RANGES
	//}}DLC_SET_ATTRIBUTE_RANGES

	//{{DLC_REGISTER_GLOBALEVENT
	//}}DLC_REGISTER_GLOBALEVENT
	return true;
}

//==========================================================
// Description	: init attributes id's
// 
// Author		: MaShawn 
//==========================================================
void MFDComponentProject1::InitAttributesID()
{
}

//==========================================================
// Description	: Create Display Objects
// 
// Author		: MaShawn 
//==========================================================
void MFDComponentProject1::CreateDisplayObjects()
{
	//{{DLC_HAGI_VARIABLES_DEFINITION
	//}}DLC_HAGI_VARIABLES_DEFINITION

	//
	// TODO: Implement the creation of the graphically displayed objects here
	//
}

//==========================================================
// Description	: Builds the Display Objects hierarchy tree
// 
// Author		: MaShawn
//==========================================================
void MFDComponentProject1::BuildDisplayObjectsHierarchyTree()
{
	//{{DLC_HAGI_VARIABLES_HIERARCHY
	//}}DLC_HAGI_VARIABLES_HIERARCHY
	//{{DLC_HAGI_VARIABLES_POSITION
	//}}DLC_HAGI_VARIABLES_POSITION
	//{{DLC_HAGI_VARIABLES_TEXT
	//}}DLC_HAGI_VARIABLES_TEXT


	//
	// TODO: Implement the creation of the displayed objects' hierarchy here
	//
}

//==========================================================
// Description	: initializing default properties
// 
// Author		: MaShawn 
//==========================================================
void MFDComponentProject1::InitDefaultProperties()
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
}


//==========================================================
// Description	: register component to Attribute changes
// 
// Author		: MaShawn
//==========================================================
bool MFDComponentProject1::RegisterToAttributeChanges()
{
	//{{DLC_REGISTER_ATTRIBUTECHANGE
	m_ChangeIdAttCurrentDisplayedSystem = REGISTER_TO_ENTITY_ATT_CHANGE_2(_pOwnerEntity, L"ATT_CURRENT_DISPLAYED_SYSTEM", _sParentGaugeNameW, const std::wstring &, MFDComponentProject1, this, &MFDComponentProject1::CBFuncAttChangeCurrentDisplayedSystem);
	//}}DLC_REGISTER_ATTRIBUTECHANGE

	return true;
}

//==========================================================
// Description	: start function
// 
// Author		: MaShawn 
//=========================================================
bool MFDComponentProject1::start()
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

	//Copy this
	//	These should be taken care of in the current displayed system attribute callback.
	////So we don't need these 2 lines
	//registerAllMouseRegionsEvents();
	//showDlc();



	// register to attribute changes
	RegisterToAttributeChanges();

	//	Copy this
	//And delete the call with the ALL_KEYS
	//{{DLC_ATTRIBUTECHANGE_CALLS
	CBFuncAttChangeCurrentDisplayedSystem(0, L"");
	//}}DLC_ATTRIBUTECHANGE_CALLS

	return true;
}

//==========================================================
// Description	: get properties value from the DataBase
// 
// Author		: MaShawn 
//=========================================================
void MFDComponentProject1::GetPropertiesValues()
{
	//{{DLC_PROPERTIES_VARIABLES_GET_VALUES
	//}}DLC_PROPERTIES_VARIABLES_GET_VALUES
}

//==========================================================
// Description	: update function
// 
// Author		: MaShawn
//=========================================================
bool MFDComponentProject1::update()
{
	return true;
}

//==========================================================
// Description	: end function
// 
// Author		: MaShawn 
//==========================================================
bool MFDComponentProject1::end()
{
	//{{DLC_UNREGISTER_GLOBALEVENT
	//}}DLC_UNREGISTER_GLOBALEVENT

	//{{DLC_UNREGISTER_ATTRIBUTECHANGE
	UNREGISTER_FROM_ENTITY_ATT_CHANGE(_pOwnerEntity, L"ATT_CURRENT_DISPLAYED_SYSTEM", m_ChangeIdAttCurrentDisplayedSystem);
	//}}DLC_UNREGISTER_ATTRIBUTECHANGE

	// unregister All Mouse Regions Events
	unRegisterAllMouseRegionsEvents();

	return true;
}

//========================================================== 
// Description	: check properties validity
// 
// Author		: MaShawn 
//==========================================================
void MFDComponentProject1::ValidatePropertiesValues()
{
}

//==========================================================
// Description	: register properties function
// 
// Author		: MaShawn 
//==========================================================
bool MFDComponentProject1::registerProperties()
{
	//{{DLC_REGISTER_PROPERTIES
	//}}DLC_REGISTER_PROPERTIES

	return true;
}

//{{DLC_INPUTEVENT_FUNC_IMPLEMENTATION
bool MFDComponentProject1::CBFuncInputEventSmgChangeToTESTPage( const int i_Param1 , const int i_Param2 )
{
	CALL_ENTITY_ACTION_2(_pOwnerEntity, L"ACTION_SET_CURRENT_DISPLAYED_SYSTEM", _sParentGaugeNameW, L"TEST");

	return true;
}
//}}DLC_INPUTEVENT_FUNC_IMPLEMENTATION

//{{DLC_GLOBALEVENT_FUNC_IMPLEMENTATION
//}}DLC_GLOBALEVENT_FUNC_IMPLEMENTATION

//{{DLC_ATTRIBUTECHANGE_FUNC_IMPLEMENTATION

bool MFDComponentProject1::CBFuncAttChangeCurrentDisplayedSystem( const int i_attIndex, const std::wstring & i_Param)
{
	wstring	strCurrentDisplayedSystem = L"";

	GET_ENTITY_ATT_2(_pOwnerEntity, L"ATT_CURRENT_DISPLAYED_SYSTEM", _sParentGaugeNameW, strCurrentDisplayedSystem);

	if (strCurrentDisplayedSystem != L"TEST")
	{
		hideDlc();
		unRegisterAllMouseRegionsEvents();
	}
	else
	{
		showDlc();
		registerAllMouseRegionsEvents();
	}

	return true;
}
//}}DLC_ATTRIBUTECHANGE_FUNC_IMPLEMENTATION
