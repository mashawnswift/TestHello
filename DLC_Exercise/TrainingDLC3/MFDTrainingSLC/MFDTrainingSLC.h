//////////////////////////////////////////////////////////////////////////
//
//			-----------------------------
//			--     Developed by MSG    --
//			-----------------------------
//
//  File : MFDTrainingSLC.h
//
//  Author : Shawn
//
//  Create Date : Tue Sep 19 10:57:37 UTC+0800 2017
//
//  Description : MFDTrainingµÄÅäÌ×SLC
//	Address : XuZhou JS
//	E-Mail : mashawn@live.cn
//	Phone : 13814443825
//
//////////////////////////////////////////////////////////////////////////


#ifndef MFDTrainingSLC_H
#define MFDTrainingSLC_H


#include "sdk.LogicComponent.h"

#ifdef MFDTrainingSLC_EXPORTS
#define MFDTrainingSLC_API __declspec(dllexport)
#else
#define MFDTrainingSLC_API __declspec(dllimport)
#endif

//{{GEN_PROJECT_DATA
#define SYSTEM_PREFIX "Training"
//}}GEN_PROJECT_DATA


class MFDTrainingSLC_API MFDTrainingSLC :public LogicComponent 
{
public:
		
	// constructor
	MFDTrainingSLC( Entity* pOwnerEntity );
	
	// destructor
	virtual ~MFDTrainingSLC();

	// register component's properties
	virtual bool registerProperties();

	// register component's attributes at the owner entity
	virtual bool registerAttributes();
	
	// register component's Actions at the owner entity
	virtual bool registerActions();

	// register component's input events
	bool registerToInputDevices();

	//{{SLC_ACTIONS_FUNC_DECLERATION
	bool CBFuncActionToggleTrainingShowAirspeed();
	//}}SLC_ACTIONS_FUNC_DECLERATION

	//{{SLC_ATTRIBUTES_FUNC_DECLERATION
	//}}SLC_ATTRIBUTES_FUNC_DECLERATION

	//{{SLC_INPUTEVENT_FUNC_DECLERATION
	//}}SLC_INPUTEVENT_FUNC_DECLERATION

	//{{SLC_GLOBALEVENT_FUNC_DECLERATION
	//}}SLC_GLOBALEVENT_FUNC_DECLERATION

	//{{SLC_ATTRIBUTECHANGE_FUNC_DECLERATION
	//}}SLC_ATTRIBUTECHANGE_FUNC_DECLERATION
	

public:
	
	// init component
	virtual bool init();
	
	// start component
	virtual bool start();
	
	// update component
	virtual bool update();
	
	// end component
	virtual bool end();

	
	
private:
	//{{SLC_PROPERTIES_VARIABLES_DECLERATION
	//}}SLC_PROPERTIES_VARIABLES_DECLERATION

	//{{SLC_GLOBALEVENT_VARIABLES_DECLERATION
	//}}SLC_GLOBALEVENT_VARIABLES_DECLERATION

	//{{SLC_ATTRIBUTECHANGE_VARIABLES_DECLERATION
	//}}SLC_ATTRIBUTECHANGE_VARIABLES_DECLERATION

};

#endif // SLC_H
