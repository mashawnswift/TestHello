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
SLC_Exercise::SLC_Exercise(Entity* pOwnerEntity):LogicComponent(pOwnerEntity),
_entitiesNum(0),
_indexDisplay(0),
_timeToDisplay(0.f)
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
	m_PropSlcSquadValue1 = 100;
	m_PropSlcSquadValue3 = 104;
	m_PropSlcSquadValue2 = 101;
	m_PropSlcSquadValue4 = 108;
	//}}SLC_PROPERTIES_VARIABLES_INIT

	//{{SLC_GLOBALEVENT_VARIABLES_INIT
	//}}SLC_GLOBALEVENT_VARIABLES_INIT

	//{{SLC_ATTRIBUTECHANGE_VARIABLES_INIT
	m_ChangeIdAttSlcSquadNum = -1;
	m_ChangeIdAttSlcSquadNumValuesCurIndex = -1;
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
	REGISTER_ENTITY_CONTAINER_ATT_INT_2(_pOwnerEntity,_T("ATT_SLC_SQUAD_VALUES"), int &, (int)0, 0, 4, _T("小队编号数据"));
	REGISTER_ENTITY_ATTRIBUTE_SYSTEM(_pOwnerEntity, _T("ATT_SLC_SQUAD_VALUES"), _T(""));
	REGISTER_ENTITY_ATTRIBUTE_VISIBILITY(_pOwnerEntity, _T("ATT_SLC_SQUAD_VALUES"), false);
	REGISTER_ENTITY_CONTAINER_ATT(_pOwnerEntity,_T("ATT_SLC_SQUAD_NUM_VALUES_CUR_INDEX"), int &, (int)0, _T("小队编号数据索引"));
	REGISTER_ENTITY_ATTRIBUTE_SYSTEM(_pOwnerEntity, _T("ATT_SLC_SQUAD_NUM_VALUES_CUR_INDEX"), _T(""));
	REGISTER_ENTITY_ATTRIBUTE_VISIBILITY(_pOwnerEntity, _T("ATT_SLC_SQUAD_NUM_VALUES_CUR_INDEX"), false);
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
	REGISTER_ENTITY_ACTION(_pOwnerEntity, _T("ACTION_SLC_DECREMENT_SQUAD_NUM"), this, &SLC_Exercise::CBFuncActionSlcDecrementSquadNum, SLC_Exercise, _T("减小编号"));
	MARK_ENTITY_ACTION_AS_USER_INPUT(_pOwnerEntity, _T("ACTION_SLC_DECREMENT_SQUAD_NUM"), true);
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
	REGISTER_PROPERTY(_pOwnerEntity, _T("PROP_SLC_SQUAD_VALUE1"), _T("小队编号Value1"), PROPERTY_INT, _T("100"), 0, 200);
	REGISTER_PROPERTY(_pOwnerEntity, _T("PROP_SLC_SQUAD_VALUE3"), _T("小队编号Value3"), PROPERTY_INT, _T("104"), 0, 200);
	REGISTER_PROPERTY(_pOwnerEntity, _T("PROP_SLC_SQUAD_VALUE2"), _T("小队编号Value2"), PROPERTY_INT, _T("101"), 0, 200);
	REGISTER_PROPERTY(_pOwnerEntity, _T("PROP_SLC_SQUAD_VALUE4"), _T("小队编号Value4"), PROPERTY_INT, _T("108"), 0, 200);
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
	GET_ENTITY_ATT(_pOwnerEntity, _T("PROP_SLC_SQUAD_VALUE1"), m_PropSlcSquadValue1);
	GET_ENTITY_ATT(_pOwnerEntity, _T("PROP_SLC_SQUAD_VALUE3"), m_PropSlcSquadValue3);
	GET_ENTITY_ATT(_pOwnerEntity, _T("PROP_SLC_SQUAD_VALUE2"), m_PropSlcSquadValue2);
	GET_ENTITY_ATT(_pOwnerEntity, _T("PROP_SLC_SQUAD_VALUE4"), m_PropSlcSquadValue4);
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
	m_ChangeIdAttSlcSquadNumValuesCurIndex = REGISTER_TO_ENTITY_ATT_CHANGE(_pOwnerEntity, _T("ATT_SLC_SQUAD_NUM_VALUES_CUR_INDEX"), SLC_Exercise, this, &SLC_Exercise::CBFuncAttChangeSlcSquadNumValuesCurIndex);
	//}}SLC_REGISTER_ATTRIBUTECHANGE
	
	//{{SLC_ATTRIBUTECHANGE_CALLS
	CBFuncAttChangeSlcSquadNum(GET_ENTITY_ATT_INDEX(_pOwnerEntity, _T("ATT_SLC_SQUAD_NUM")));
	CBFuncAttChangeSlcSquadNumValuesCurIndex(GET_ENTITY_ATT_INDEX(_pOwnerEntity, _T("ATT_SLC_SQUAD_NUM_VALUES_CUR_INDEX")));
	//}}SLC_ATTRIBUTECHANGE_CALLS
	SET_ENTITY_CONTAINER_ATT_VALUE(_pOwnerEntity, _T("ATT_SLC_SQUAD_NUM"), m_PropSlcSquadNum);
	//填充Att2的数据
	SET_ENTITY_CONTAINER_ATT_VALUE_2(_pOwnerEntity, _T("ATT_SLC_SQUAD_VALUES"), 1, m_PropSlcSquadValue1);
	SET_ENTITY_CONTAINER_ATT_VALUE_2(_pOwnerEntity, _T("ATT_SLC_SQUAD_VALUES"), 2, m_PropSlcSquadValue2);
	SET_ENTITY_CONTAINER_ATT_VALUE_2(_pOwnerEntity, _T("ATT_SLC_SQUAD_VALUES"), 3, m_PropSlcSquadValue3);
	SET_ENTITY_CONTAINER_ATT_VALUE_2(_pOwnerEntity, _T("ATT_SLC_SQUAD_VALUES"), 4, m_PropSlcSquadValue4);
	

	return true;
}

//==========================================================
// Description	: update Logic Component
// 
// Author		: Shawn 
//=========================================================
bool SLC_Exercise::update()
{
	int SelectedEntityID = -1;
	//用户控制实体的ID
	SelectedEntityID = SimApi::Entities::getSelectedEntityId();
	//如果当前实体不是用户控制的实体，return
	if(_pOwnerEntity->getEntityId() != SelectedEntityID)
		return true;
	//搜索符合条件的实体
	searchEntities();
	//显示实体信息
	displayEntitiesInfo();
	//
	
	return true;
}

void SLC_Exercise::searchEntities()
{
	_entitiesNum = 0;

	int NumEntities = -1;
	const int *EntitiesIDArray = NULL;
	Entity *pFoundEntity = NULL;
	int FoundEntityID = -1;
	int MyID = -1;//当前实体的ID
	bool FoundIsAircraft = false;
	bool FoundIsControlled = false;
	int SelectedSquadNum = -1;
	int FoundSquadNum = -1;
	LinearVec MyPosition, FoundPosition;
	float DistanceToFound = 0.0f;

	//获取实体ID列表
	EntitiesIDArray = SimApi::Entities::getEntitiesIDsArray(NumEntities);
	//获取编号
	GET_ENTITY_ATT_BY_UNIT(_pOwnerEntity, _T("ATT_SLC_SQUAD_NUM"), SelectedSquadNum, UNIT_TYPE_DEFAULT);
	//获取实体的ID
	GET_ENTITY_ATT_BY_UNIT(_pOwnerEntity, EntityWorld::ATT_UNIQUE_ID, MyID, UNIT_TYPE_DEFAULT);
	//获取实体当前位置
	GET_ENTITY_ATT_BY_UNIT(_pOwnerEntity, EntityWorld::ATT_POSITION, MyPosition, UNIT_TYPE_DEFAULT);
	//遍历实体，搜索符合条件的实体
	for (int Count = 0; Count < NumEntities; Count++)
	{
		FoundEntityID = EntitiesIDArray[Count];
		//排除实体的ID是用户控制实体或自身
		if (FoundEntityID != MyID)
		{
			GET_OTHER_ENTITY_ATT(FoundEntityID, EntityWorld::ATT_IS_AIRCRAFT, FoundIsAircraft);
			//判断是否是飞机类型
			if (FoundIsAircraft == true)
			{
				//检查编号是否相同
				if ( GET_OTHER_ENTITY_ATT_BY_UNIT(FoundEntityID, _T("ATT_SLC_SQUAD_NUM"), FoundSquadNum, UNIT_TYPE_DEFAULT) )
				{
					if (SelectedSquadNum == FoundSquadNum)//编号相同则判断距离
					{
						GET_OTHER_ENTITY_ATT_BY_UNIT(FoundEntityID, EntityWorld::ATT_POSITION, FoundPosition, UNIT_TYPE_DEFAULT);
						//获取相对距离
						SimApi::Entities::getRelativeDistance(MyPosition, FoundPosition, DistanceToFound);
						DistanceToFound = METERS_TO_MILES(DistanceToFound);
						if (DistanceToFound <= 20.0f)//找到符合条件的实体
						{
							_entitiesIDsNeedToDisplay[_entitiesNum] = FoundEntityID;
							_entitiesNum++;
						}
					}
				}
			}
		}
	}
}
void SLC_Exercise::displayEntitiesInfo()
{
	float attHeight = 0.0f;
	GET_ENTITY_ATT_BY_UNIT(_pOwnerEntity, EntityWorld::ATT_HEIGHT, attHeight, UNIT_TYPE_DEFAULT);
	attHeight =METERS_TO_FEET(attHeight);
	if(attHeight >=8000.f)
		return;
	if(_entitiesNum <= 0)
		return;
	STRING FoundName = _T("NONE");
	double CurrentTime = 0.0;
	//当前时刻
	CurrentTime = SimApi::Timer::time();
	if(_indexDisplay >= _entitiesNum)
		_indexDisplay = 0;
	//按时间间隔发布事件，不是每帧都发布
	if (CurrentTime >= _timeToDisplay)
	{
		CString str;
	
		GET_OTHER_ENTITY_ATT(_entitiesIDsNeedToDisplay[_indexDisplay], EntityWorld::ATT_DISPLAY_NAME, FoundName);

		str.Format(L"当前高度：%.0f 英尺，%s",attHeight,FoundName.c_str());

		SimApi::EventParams* eventParams = SimApi::EventsFactory::getEventInstance(_T("TextToSpeech"));
		eventParams->getParam(_T("IsMessageCheck"))->setValue( true );
		eventParams->getParam(_T("IsVoiceCheck"))->setValue( true );
		eventParams->getParam(_T("DisplayContinues"))->setValue( false );
		eventParams->getParam(_T("Text"))->setValue( str);
		eventParams->getParam(_T("TextToDisplay"))->setValue( str );
		SimApi::EventHandler::publishEvent(eventParams);
		//事件的时间间隔
		_timeToDisplay = CurrentTime + 10.0;
		//发布事件后，索引转到下一个实体
		_indexDisplay++;
	}

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
	UNREGISTER_FROM_ENTITY_ATT_CHANGE(_pOwnerEntity, _T("ATT_SLC_SQUAD_NUM_VALUES_CUR_INDEX"), m_ChangeIdAttSlcSquadNumValuesCurIndex);
	//}}SLC_UNREGISTER_ATTRIBUTECHANGE

	return true;
}


//{{SLC_ACTIONS_FUNC_IMPLEMENTATION

bool SLC_Exercise::CBFuncActionSlcIncrementSquadNum()
{
	int attSlcSquadNumValuesCurIndex = 0;
	GET_ENTITY_ATT_BY_UNIT(_pOwnerEntity, _T("ATT_SLC_SQUAD_NUM_VALUES_CUR_INDEX"), attSlcSquadNumValuesCurIndex, UNIT_TYPE_DEFAULT);
	//增大编号索引
	if(attSlcSquadNumValuesCurIndex < 4)
		attSlcSquadNumValuesCurIndex ++;
	SET_ENTITY_CONTAINER_ATT_VALUE(_pOwnerEntity, _T("ATT_SLC_SQUAD_NUM_VALUES_CUR_INDEX"), attSlcSquadNumValuesCurIndex);
	return true;
}


bool SLC_Exercise::CBFuncActionSlcDecrementSquadNum()
{
	int attSlcSquadNumValuesCurIndex = 0;
	GET_ENTITY_ATT_BY_UNIT(_pOwnerEntity, _T("ATT_SLC_SQUAD_NUM_VALUES_CUR_INDEX"), attSlcSquadNumValuesCurIndex, UNIT_TYPE_DEFAULT);
	//减小编号索引
	if(attSlcSquadNumValuesCurIndex >1)
		attSlcSquadNumValuesCurIndex --;
	SET_ENTITY_CONTAINER_ATT_VALUE(_pOwnerEntity, _T("ATT_SLC_SQUAD_NUM_VALUES_CUR_INDEX"), attSlcSquadNumValuesCurIndex);
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

bool SLC_Exercise::CBFuncAttChangeSlcSquadNumValuesCurIndex( const int i_attIndex)
{
	int AttSlcSquadNumValuesCurIndex = 0;
	GET_ENTITY_ATT_BY_UNIT(_pOwnerEntity, i_attIndex, AttSlcSquadNumValuesCurIndex, UNIT_TYPE_DEFAULT);
	//根据索引获取编号
	int attSlcSquadValues = 0;
	GET_ENTITY_ATT_2_BY_UNIT(_pOwnerEntity, _T("ATT_SLC_SQUAD_VALUES"), AttSlcSquadNumValuesCurIndex , attSlcSquadValues, UNIT_TYPE_DEFAULT);
	//更新编号值
	SET_ENTITY_CONTAINER_ATT_VALUE(_pOwnerEntity, _T("ATT_SLC_SQUAD_NUM"), attSlcSquadValues);
	if(AttSlcSquadNumValuesCurIndex==4)//放下襟翼
	{
		int inputAcFlapsDownOneStepParam1 = 0;
		int inputAcFlapsDownOneStepParam2 = 0;
		CALL_ENTITY_ACTION_2_BY_UNIT(_pOwnerEntity, _T("INPUT_AC_FLAPS_DOWN_ONE_STEP"), inputAcFlapsDownOneStepParam1, inputAcFlapsDownOneStepParam2, UNIT_TYPE_DEFAULT);
	}
	if(AttSlcSquadNumValuesCurIndex==1)//升起襟翼
	{
		int inputAcFlapsDownOneStepParam1 = 0;
		int inputAcFlapsDownOneStepParam2 = 0;
		CALL_ENTITY_ACTION_2_BY_UNIT(_pOwnerEntity, _T("INPUT_AC_FLAPS_UP_ONE_STEP"), inputAcFlapsDownOneStepParam1, inputAcFlapsDownOneStepParam2, UNIT_TYPE_DEFAULT);

	}
	return true;
}
//}}SLC_ATTRIBUTECHANGE_FUNC_IMPLEMENTATION
