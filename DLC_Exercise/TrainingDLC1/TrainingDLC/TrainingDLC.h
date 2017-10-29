//////////////////////////////////////////////////////////////////////////
//
//			-----------------------------
//			--     Developed by MSG    --
//			-----------------------------
//
//  File : TrainingDLC.h
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

   
#ifndef DLC_H
#define DLC_H



#include "sdk.DisplayComponent.h"

#ifdef TrainingDLC_EXPORTS
#define TrainingDLC_API __declspec(dllexport)
#else
#define TrainingDLC_API __declspec(dllimport)
#endif

//{{GEN_PROJECT_DATA
#define SYSTEM_PREFIX "TRAIN"
//}}GEN_PROJECT_DATA

class Entity;

class TrainingDLC_API TrainingDLC :public DisplayComponent  
{
public:
			
	// constructor
	TrainingDLC();
	
	// destructor
	virtual ~TrainingDLC();

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
	virtual bool		registerProperties();

	//{{DLC_INPUTEVENT_FUNC_DECLERATION
	//}}DLC_INPUTEVENT_FUNC_DECLERATION

	//{{DLC_GLOBALEVENT_FUNC_DECLERATION
	//}}DLC_GLOBALEVENT_FUNC_DECLERATION

	//{{DLC_ATTRIBUTECHANGE_FUNC_DECLERATION
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
	//}}DLC_ATTRIBUTECHANGE_VARIABLES_DECLERATION
	
	//{{DLC_HAGI_VARIABLES_DECLERATION
	HAGI  _abstract;//抽象节点
	HAGI _txtTraining;//静态文字

	//}}DLC_HAGI_VARIABLES_DECLERATION
};

#endif // DLC_H


