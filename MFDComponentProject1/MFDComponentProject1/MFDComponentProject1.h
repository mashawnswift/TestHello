//////////////////////////////////////////////////////////////////////////
//
//			-----------------------------
//			--     Developed by MSG    --
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

#ifndef MFDComponentProject1_H
#define MFDComponentProject1_H

#include "sdk.DisplayComponent.h"

#ifdef MFDComponentProject1_EXPORTS
#define MFDComponentProject1_API __declspec(dllexport)
#else
#define MFDComponentProject1_API __declspec(dllimport)
#endif

//{{GEN_PROJECT_DATA
#define SYSTEM_PREFIX "MFD"
//}}GEN_PROJECT_DATA


class Entity;

class MFDComponentProject1_API MFDComponentProject1 : public DisplayComponent  
{
public:	
	// constructor
	MFDComponentProject1();

	// destructor
	virtual ~MFDComponentProject1();

	// register component's input events
	virtual bool registerToInputDevices();

public:
	// init function
	virtual bool init();

	// start function
	virtual bool start();

	// update function
	virtual bool update();

	// end function
	virtual bool end();

	// register component to attributes changes
	bool RegisterToAttributeChanges();

	// init attributes id's
	void InitAttributesID();

	// initializing default properties
	void InitDefaultProperties(); 

	// register component's properties
	virtual bool registerProperties();

	//{{DLC_INPUTEVENT_FUNC_DECLERATION
	bool CBFuncInputEventSmgChangeToTESTPage( const int i_Param1 , const int i_Param2 );
	//}}DLC_INPUTEVENT_FUNC_DECLERATION

	//{{DLC_GLOBALEVENT_FUNC_DECLERATION
	//}}DLC_GLOBALEVENT_FUNC_DECLERATION

	//{{DLC_ATTRIBUTECHANGE_FUNC_DECLERATION
	bool CBFuncAttChangeCurrentDisplayedSystem( const int i_attIndex, const std::wstring & i_Param);
	//}}DLC_ATTRIBUTECHANGE_FUNC_DECLERATION

private:
	// check properties validity
	void ValidatePropertiesValues();

	// get properties value from the DataBase
	void GetPropertiesValues();

	// Display Objects (AGIs) creation	
	void CreateDisplayObjects();

	// Builds the AGIs Hierarchy Tree
	void BuildDisplayObjectsHierarchyTree();

private:
	//{{DLC_PROPERTIES_VARIABLES_DECLERATION
	//}}DLC_PROPERTIES_VARIABLES_DECLERATION

	//{{DLC_GLOBALEVENT_VARIABLES_DECLERATION
	//}}DLC_GLOBALEVENT_VARIABLES_DECLERATION

	//{{DLC_ATTRIBUTECHANGE_VARIABLES_DECLERATION
	int m_ChangeIdAttCurrentDisplayedSystem;
	//}}DLC_ATTRIBUTECHANGE_VARIABLES_DECLERATION
	
	//{{DLC_HAGI_VARIABLES_DECLERATION
	//}}DLC_HAGI_VARIABLES_DECLERATION
};

#endif	//	_MFD_TEMPLATE_H_


