//////////////////////////////////////////////////////////////////////////
//
//			-----------------------------
//			--     Developed by MSG    --
//			-----------------------------
//
//  File : VMU_Display.h
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

   
#ifndef DLC_H
#define DLC_H



#include "sdk.DisplayComponent.h"

#ifdef VMU_Display_EXPORTS
#define VMU_Display_API __declspec(dllexport)
#else
#define VMU_Display_API __declspec(dllimport)
#endif

//{{GEN_PROJECT_DATA
#define SYSTEM_PREFIX "VMU"
//}}GEN_PROJECT_DATA

class Entity;

class VMU_Display_API VMU_Display :public DisplayComponent  
{
public:
		
	// constructor
	VMU_Display();
	
	// destructor
	virtual ~VMU_Display();

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
	bool CBFuncAttChangeVmuOvergWarning( const int i_attIndex);
	bool CBFuncAttChangeVmuAltitudeWarning( const int i_attIndex);
	bool CBFuncAttChangeVmuFlapsWarning( const int i_attIndex);
	bool CBFuncAttChangeVmuPullUpWarning( const int i_attIndex);
	bool CBFuncAttChangeVmuIsToDisplayAltitudeText( const int i_attIndex);
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
	int m_ChangeIdAttVmuOvergWarning;
	int m_ChangeIdAttVmuAltitudeWarning;
	int m_ChangeIdAttVmuFlapsWarning;
	int m_ChangeIdAttVmuPullUpWarning;
	int m_ChangeIdAttVmuIsToDisplayAltitudeText;
	//}}DLC_ATTRIBUTECHANGE_VARIABLES_DECLERATION
	
	//{{DLC_HAGI_VARIABLES_DECLERATION
	HAGI	_txtOverG;//OverG字符
	HAGI	_txtAltitude;//Altitude字符

	//拉起箭头
	HAGI	_XAbstract;//X标志的父对象
	HAGI	_XPart1;//
	HAGI	_XPart2;//
	HAGI	_arrowAbstract;//箭头对象
	HAGI	_arrow;
	//}}DLC_HAGI_VARIABLES_DECLERATION
	bool	_bDisplayPullup;//是否显示箭头
	bool _bShowAltitudeTxt;//显示高度字符
};

#endif // DLC_H


