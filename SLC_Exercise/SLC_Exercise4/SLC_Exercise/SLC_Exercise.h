//////////////////////////////////////////////////////////////////////////
//
//			-----------------------------
//			--     Developed by MSG    --
//			-----------------------------
//
//  File : SLC_Exercise.h
//
//  Author : Shawn
//
//  Create Date : Mon Sep 4 13:57:02 UTC+0800 2017
//
//  Description : SLC练习 更新到练习2状态
//	Address : XuZhou JS
//	E-Mail : mashawn@live.cn
//	Phone : 13814443825
//
//////////////////////////////////////////////////////////////////////////


#ifndef SLC_Exercise_H
#define SLC_Exercise_H


#include "sdk.LogicComponent.h"

#ifdef SLC_Exercise_EXPORTS
#define SLC_Exercise_API __declspec(dllexport)
#else
#define SLC_Exercise_API __declspec(dllimport)
#endif

//{{GEN_PROJECT_DATA
#define SYSTEM_PREFIX "SLC"
//}}GEN_PROJECT_DATA


class SLC_Exercise_API SLC_Exercise :public LogicComponent 
{
public:
		
	// constructor
	SLC_Exercise( Entity* pOwnerEntity );
	
	// destructor
	virtual ~SLC_Exercise();

	// register component's properties
	virtual bool registerProperties();

	// register component's attributes at the owner entity
	virtual bool registerAttributes();
	
	// register component's Actions at the owner entity
	virtual bool registerActions();

	// register component's input events
	bool registerToInputDevices();

	//{{SLC_ACTIONS_FUNC_DECLERATION
	bool CBFuncActionSlcIncrementSquadNum();
	bool CBFuncActionSlcDecrementSquadNum();
	//}}SLC_ACTIONS_FUNC_DECLERATION

	//{{SLC_ATTRIBUTES_FUNC_DECLERATION
	//}}SLC_ATTRIBUTES_FUNC_DECLERATION

	//{{SLC_INPUTEVENT_FUNC_DECLERATION
	//}}SLC_INPUTEVENT_FUNC_DECLERATION

	//{{SLC_GLOBALEVENT_FUNC_DECLERATION
	//}}SLC_GLOBALEVENT_FUNC_DECLERATION

	//{{SLC_ATTRIBUTECHANGE_FUNC_DECLERATION
	bool CBFuncAttChangeSlcSquadNum( const int i_attIndex);
	bool CBFuncAttChangeSlcSquadNumValuesCurIndex( const int i_attIndex);
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
	int m_PropSlcSquadNum;
	int m_PropSlcSquadValue1;
	int m_PropSlcSquadValue3;
	int m_PropSlcSquadValue2;
	int m_PropSlcSquadValue4;
	//}}SLC_PROPERTIES_VARIABLES_DECLERATION

	//{{SLC_GLOBALEVENT_VARIABLES_DECLERATION
	//}}SLC_GLOBALEVENT_VARIABLES_DECLERATION

	//{{SLC_ATTRIBUTECHANGE_VARIABLES_DECLERATION
	int m_ChangeIdAttSlcSquadNum;
	int m_ChangeIdAttSlcSquadNumValuesCurIndex;
	//}}SLC_ATTRIBUTECHANGE_VARIABLES_DECLERATION

	int _entitiesIDsNeedToDisplay[100];//符合条件的实体ID列表
	int _entitiesNum;//符合条件的实体数量
	int _indexDisplay;//显示实体在列表中的索引
	void searchEntities();//搜索符合条件的实体
	void displayEntitiesInfo();//显示实体信息
	float _timeToDisplay;//显示信息计时
};

#endif // SLC_H
