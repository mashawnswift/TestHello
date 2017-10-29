 //////////////////////////////////////////////////////////////////////////
//
//			-----------------------------
//			--     Developed by MSG  --
//			-----------------------------
//
//  File		: VMU_Logic.cpp
//
//  Author		: MaShawn
//
//  Create Date : Sat Sep 23 12:53:09 UTC+0800 2017
//
//  Description : VMU逻辑
//	Address		: JiangSu
//	E-Mail		: mashawn@live.cn
//	Phone		: +8613814443825
//
//////////////////////////////////////////////////////////////////////////

#pragma warning ( disable : 4284  4786 4251)

#include "StdAfx.h"

#include "VMU_Logic.h"
#include "api.Sim.h"
#include "sdk.Sim.h"

LogicComponent* createComponent(Entity* pOwnerEntity)
{
	return new VMU_Logic(pOwnerEntity);
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
// Author		: MaShawn 
//==========================================================
VMU_Logic::VMU_Logic(Entity* pOwnerEntity):LogicComponent(pOwnerEntity)
{
	//
	// TODO: Implement the constructor
	//
	
	_sName = _T("VMU_Logic.slc");

	// TODO: write the description of the Object Component
	_sDescription = _T("VMU逻辑");
	
	// TODO: set the update interval of the component (in seconds)
	// (0 - every frame, negative value - never)
	//将系统刷新频率设置为8Hz
	SET_UPDATE_INTERVAL_TIME(pOwnerEntity,0.125f);
	//{{SLC_PROPERTIES_VARIABLES_INIT
	m_PropVmuMaxSpeedWithFlapsExtended = 140.0f;
	m_PropVmuMinNegativeGWarning = -0.2f;
	m_PropVmuMaxPositiveGWarning = 2.5f;
	m_PropVmuMinAltitudeWarning = 1000.0f;
	//}}SLC_PROPERTIES_VARIABLES_INIT

	//{{SLC_GLOBALEVENT_VARIABLES_INIT
	//}}SLC_GLOBALEVENT_VARIABLES_INIT

	//{{SLC_ATTRIBUTECHANGE_VARIABLES_INIT
	//}}SLC_ATTRIBUTECHANGE_VARIABLES_INIT
	_bAllowAltitudeWarningTxt = true;
	_isSystemOn = true;
}

//==========================================================
// Description	: destructor
// 
// Author		: MaShawn 
//==========================================================
VMU_Logic::~VMU_Logic()
{
	//
	// TODO: Implement the destructor
	//
}
	
//==========================================================
// Description	: register Attributes here 
// 
// Author		: MaShawn 
//==========================================================
bool VMU_Logic::registerAttributes()
{ 
	//{{SLC_REGISTER_ATTRIBUTES
	REGISTER_ENTITY_CONTAINER_ATT(_pOwnerEntity,_T("ATT_VMU_OVERG_WARNING"), bool &, (bool)false, _T("OverG告警状态"));
	REGISTER_ENTITY_ATTRIBUTE_SYSTEM(_pOwnerEntity, _T("ATT_VMU_OVERG_WARNING"), _T(""));
	REGISTER_ENTITY_ATTRIBUTE_VISIBILITY(_pOwnerEntity, _T("ATT_VMU_OVERG_WARNING"), true);
	REGISTER_ENTITY_CONTAINER_ATT(_pOwnerEntity,_T("ATT_VMU_ALTITUDE_WARNING"), bool &, (bool)false, _T("高度告警状态"));
	REGISTER_ENTITY_ATTRIBUTE_SYSTEM(_pOwnerEntity, _T("ATT_VMU_ALTITUDE_WARNING"), _T(""));
	REGISTER_ENTITY_ATTRIBUTE_VISIBILITY(_pOwnerEntity, _T("ATT_VMU_ALTITUDE_WARNING"), true);
	REGISTER_ENTITY_CONTAINER_ATT_BY_UNIT(_pOwnerEntity,_T("ATT_VMU_PULL_UP_WARNING_ANGLE"), float &, (float)0, _T("拉起方向"), UnitType::ANGLE, AngleUnits::DEGREE);
	REGISTER_ENTITY_ATTRIBUTE_SYSTEM(_pOwnerEntity, _T("ATT_VMU_PULL_UP_WARNING_ANGLE"), _T(""));
	REGISTER_ENTITY_ATTRIBUTE_VISIBILITY(_pOwnerEntity, _T("ATT_VMU_PULL_UP_WARNING_ANGLE"), true);
	REGISTER_ENTITY_CONTAINER_ATT(_pOwnerEntity,_T("ATT_VMU_IS_SYSTEM_ON"), bool &, (bool)true, _T("系统开关状态"));
	REGISTER_ENTITY_ATTRIBUTE_SYSTEM(_pOwnerEntity, _T("ATT_VMU_IS_SYSTEM_ON"), _T(""));
	REGISTER_ENTITY_ATTRIBUTE_VISIBILITY(_pOwnerEntity, _T("ATT_VMU_IS_SYSTEM_ON"), true);
	REGISTER_ENTITY_CONTAINER_ATT(_pOwnerEntity,_T("ATT_VMU_IS_TO_DISPLAY_ALTITUDE_TEXT"), bool &, (bool)true, _T("是否显示高度提示字符"));
	REGISTER_ENTITY_ATTRIBUTE_SYSTEM(_pOwnerEntity, _T("ATT_VMU_IS_TO_DISPLAY_ALTITUDE_TEXT"), _T(""));
	REGISTER_ENTITY_ATTRIBUTE_VISIBILITY(_pOwnerEntity, _T("ATT_VMU_IS_TO_DISPLAY_ALTITUDE_TEXT"), true);
	REGISTER_ENTITY_CONTAINER_ATT(_pOwnerEntity,_T("ATT_VMU_FLAPS_WARNING"), bool &, (bool)false, _T("襟翼告警状态"));
	REGISTER_ENTITY_ATTRIBUTE_SYSTEM(_pOwnerEntity, _T("ATT_VMU_FLAPS_WARNING"), _T(""));
	REGISTER_ENTITY_ATTRIBUTE_VISIBILITY(_pOwnerEntity, _T("ATT_VMU_FLAPS_WARNING"), true);
	REGISTER_ENTITY_CONTAINER_ATT(_pOwnerEntity,_T("ATT_VMU_PULL_UP_WARNING"), bool &, (bool)false, _T("拉起告警状态"));
	REGISTER_ENTITY_ATTRIBUTE_SYSTEM(_pOwnerEntity, _T("ATT_VMU_PULL_UP_WARNING"), _T(""));
	REGISTER_ENTITY_ATTRIBUTE_VISIBILITY(_pOwnerEntity, _T("ATT_VMU_PULL_UP_WARNING"), true);
	//}}SLC_REGISTER_ATTRIBUTES

	return true;
}

//==========================================================
// Description	: register Actions here
// 
// Author		: MaShawn 
//==========================================================
bool VMU_Logic::registerActions()
{
	//{{SLC_REGISTER_ACTIONS
	REGISTER_ENTITY_ACTION(_pOwnerEntity, _T("ACTION_VMU_TOGGLE_SYSTEM"), this, &VMU_Logic::CBFuncActionVmuToggleSystem, VMU_Logic, _T("切换系统开关"));
	MARK_ENTITY_ACTION_AS_USER_INPUT(_pOwnerEntity, _T("ACTION_VMU_TOGGLE_SYSTEM"), true);
	REGISTER_ENTITY_ACTION(_pOwnerEntity, _T("ACTION_VMU_TOGGLE_ALTITUDE_WARNING"), this, &VMU_Logic::CBFuncActionVmuToggleAltitudeWarning, VMU_Logic, _T("切换高度告警状态"));
	MARK_ENTITY_ACTION_AS_USER_INPUT(_pOwnerEntity, _T("ACTION_VMU_TOGGLE_ALTITUDE_WARNING"), true);
	//}}SLC_REGISTER_ACTIONS
	return true;     	
}

//==========================================================
// Description	: register events
// 
// Author		: MaShawn 
//==========================================================
bool VMU_Logic::registerToInputDevices()
{
	//{{SLC_REGISTER_INPUTEVENT
	//}}SLC_REGISTER_INPUTEVENT
	return true;
}

//==========================================================
// Description	: register component's properties
// 
// Author		: MaShawn
//==========================================================
bool VMU_Logic::registerProperties()
{
	
	//{{SLC_REGISTER_PROPERTIES
	REGISTER_PROPERTY_BY_UNIT(_pOwnerEntity, _T("PROP_VMU_MAX_SPEED_WITH_FLAPS_EXTENDED"), _T("襟翼展开的最大速度"), PROPERTY_FLOAT, _T("140"), UnitType::SPEED, SpeedUnits::KNOTS, 60, 400);
	REGISTER_PROPERTY_BY_UNIT(_pOwnerEntity, _T("PROP_VMU_MIN_NEGATIVE_G_WARNING"), _T("过载告警范围-最小负过载"), PROPERTY_FLOAT, _T("-0.2"), UnitType::ACCELERATION, AccelerationUnits::G, -5, 0);
	REGISTER_PROPERTY_BY_UNIT(_pOwnerEntity, _T("PROP_VMU_MAX_POSITIVE_G_WARNING"), _T("过载告警范围-最大正过载"), PROPERTY_FLOAT, _T("2.5"), UnitType::ACCELERATION, AccelerationUnits::G, 1, 9);
	REGISTER_PROPERTY_BY_UNIT(_pOwnerEntity, _T("PROP_VMU_MIN_ALTITUDE_WARNING"), _T("高度告警的最小高度(对地高度)"), PROPERTY_FLOAT, _T("1000"), UnitType::LENGTH, LengthUnits::FEET, 100, 10000);
	//}}SLC_REGISTER_PROPERTIES
	
	return true;
}

//==========================================================
// Description	: init()
// 
// Author		: MaShawn 
//=========================================================
bool VMU_Logic::init()
{
	//
	// TODO: Initialize the component's variables here
	//

	//{{SLC_SET_ATTRIBUTE_RANGES
	//}}SLC_SET_ATTRIBUTE_RANGES

	//{{SLC_PROPERTIES_VARIABLES_GET_VALUES
	GET_ENTITY_ATT(_pOwnerEntity, _T("PROP_VMU_MAX_SPEED_WITH_FLAPS_EXTENDED"), m_PropVmuMaxSpeedWithFlapsExtended);
	GET_ENTITY_ATT(_pOwnerEntity, _T("PROP_VMU_MIN_NEGATIVE_G_WARNING"), m_PropVmuMinNegativeGWarning);
	GET_ENTITY_ATT(_pOwnerEntity, _T("PROP_VMU_MAX_POSITIVE_G_WARNING"), m_PropVmuMaxPositiveGWarning);
	GET_ENTITY_ATT(_pOwnerEntity, _T("PROP_VMU_MIN_ALTITUDE_WARNING"), m_PropVmuMinAltitudeWarning);
	//}}SLC_PROPERTIES_VARIABLES_GET_VALUES

	//{{SLC_REGISTER_GLOBALEVENT
	//}}SLC_REGISTER_GLOBALEVENT

	return true;

}

//==========================================================
// Description	: start logic component
// 
// Author		: MaShawn
//=========================================================
bool VMU_Logic::start()
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
// Author		: MaShawn 
//=========================================================
bool VMU_Logic::update()
{
	if(_isSystemOn)
	{
		CheckAltitudeWarning();
		CheckFlapsWarning();
		CheckOverGWarning();
	}
	return true;
}

//==========================================================
// Description	: end function
// 
// Author		: MaShawn 
//==========================================================
bool VMU_Logic::end()
{

	//{{SLC_UNREGISTER_GLOBALEVENT
	//}}SLC_UNREGISTER_GLOBALEVENT

	//{{SLC_UNREGISTER_ATTRIBUTECHANGE
	//}}SLC_UNREGISTER_ATTRIBUTECHANGE

	return true;
}


//{{SLC_ACTIONS_FUNC_IMPLEMENTATION

bool VMU_Logic::CBFuncActionVmuToggleSystem()
{
	ToggleSystemOnOff();
	return true;
}

bool VMU_Logic::CBFuncActionVmuToggleAltitudeWarning()
{
	_bAllowAltitudeWarningTxt = !_bAllowAltitudeWarningTxt;
	SET_ENTITY_CONTAINER_ATT_VALUE(_pOwnerEntity, _T("ATT_VMU_IS_TO_DISPLAY_ALTITUDE_TEXT"), _bAllowAltitudeWarningTxt);
	return true;
}

bool VMU_Logic::ToggleSystemOnOff()
{

	//TODO: Implement function
	_isSystemOn = ! _isSystemOn;
	SET_ENTITY_CONTAINER_ATT_VALUE(_pOwnerEntity, L"ATT_VMU_IS_SYSTEM_ON", _isSystemOn);
	//当系统关闭时，关闭所有的告警信息
	if (_isSystemOn== false)
	{
		SET_ENTITY_CONTAINER_ATT_VALUE(_pOwnerEntity, L"ATT_VMU_OVERG_WARNING", false);
		SET_ENTITY_CONTAINER_ATT_VALUE(_pOwnerEntity, L"ATT_VMU_ALTITUDE_WARNING", false);
		SET_ENTITY_CONTAINER_ATT_VALUE(_pOwnerEntity, L"ATT_VMU_PULL_UP_WARNING", false);
		SET_ENTITY_CONTAINER_ATT_VALUE(_pOwnerEntity, L"ATT_VMU_FLAPS_WARNING", false);

	}
	return true;

}

void VMU_Logic::CheckFlapsWarning()
{
	float	fAirspeedKnots = 0.0f;
	float	fFlapsAngle = 0.0f;

	//获取当前空速（节）
	GET_ENTITY_ATT_BY_UNIT(_pOwnerEntity, _T("ATT_INDICATED_AIRSPEED_KNOTS"), fAirspeedKnots, UNIT_TYPE_DEFAULT);
	//获取Flaps角度
	GET_ENTITY_ATT_BY_UNIT(_pOwnerEntity, _T("ATT_SUBPART_ANG_FLAPS"), fFlapsAngle, UNIT_TYPE_DEFAULT);

	//检查襟翼展开和速度条件
	if(fAirspeedKnots > m_PropVmuMaxSpeedWithFlapsExtended && fabs(fFlapsAngle) > DEG2RAD(5.0f))
	{
		//发出告警
		SET_ENTITY_CONTAINER_ATT_VALUE(_pOwnerEntity, _T("ATT_VMU_FLAPS_WARNING"), true);
	}
	else//解除Flaps告警
		SET_ENTITY_CONTAINER_ATT_VALUE(_pOwnerEntity, _T("ATT_VMU_FLAPS_WARNING"), false);
}
void VMU_Logic::CheckOverGWarning()
{
	float	fCurrentG = 0.0f;
	//获取当前G
	GET_ENTITY_ATT_BY_UNIT(_pOwnerEntity, _T("ATT_ACTUAL_G"), fCurrentG, UNIT_TYPE_DEFAULT);
	//检查过载限制条件
	if(fCurrentG < m_PropVmuMinNegativeGWarning || fCurrentG > m_PropVmuMaxPositiveGWarning)
		//超出条件发出OverG告警
		SET_ENTITY_CONTAINER_ATT_VALUE(_pOwnerEntity, _T("ATT_VMU_OVERG_WARNING"), true);
	else
		//解除OverG告警
		SET_ENTITY_CONTAINER_ATT_VALUE(_pOwnerEntity, _T("ATT_VMU_OVERG_WARNING"), false);
}

void VMU_Logic::CheckAltitudeWarning()
{
	Location	curLoc;//当前位置
	LinearVec	curVel;//当前速度
	float		fHeightAtLoc = 0.0f;//高度
	LinearVec	projectLocation =LinearVec::zero() ;//4秒后的位置
	//获取当前位置和姿态
	GET_ENTITY_ATT_BY_UNIT(_pOwnerEntity, EntityWorld::ATT_LOCATION, curLoc, UNIT_TYPE_DEFAULT);
	//获取当前速度矢量
	GET_ENTITY_ATT_BY_UNIT(_pOwnerEntity, EntityWorld::ATT_LIN_VELOCITY, curVel, UNIT_TYPE_DEFAULT);
	//根据当前位置和速度，计算4秒后位置
	projectLocation[X] = curLoc.linVecRef()(X) + curVel[0] * 4.0f;
	projectLocation[Y] = curLoc.linVecRef()(Y) +curVel[1] * 4.0f;
	projectLocation[Z] = curLoc.linVecRef()(Z)+ curVel[2] * 4.0f;

	//获取4秒后位置的地形高度
	TriD::GetTerrainHeightAt(projectLocation(X), projectLocation(Y), fHeightAtLoc);
	//检查4秒后的高度是否满足条件，预设对地高度+地形高度
	if( METERS_TO_FEET(projectLocation(Z)) < m_PropVmuMinAltitudeWarning + METERS_TO_FEET(fHeightAtLoc))
	{
		//拉起告警
		SET_ENTITY_CONTAINER_ATT_VALUE(_pOwnerEntity, _T("ATT_VMU_PULL_UP_WARNING"), true);
		//给出拉起的角度
		SET_ENTITY_CONTAINER_ATT_VALUE(_pOwnerEntity, _T("ATT_VMU_PULL_UP_WARNING_ANGLE"), (float)(curLoc.angVec()(ROLL).deg()) * -1.0f);
		
		SET_ENTITY_CONTAINER_ATT_VALUE(_pOwnerEntity, _T("ATT_VMU_ALTITUDE_WARNING"), true);
		_bAllowAltitudeWarningTxt = true;
		SET_ENTITY_CONTAINER_ATT_VALUE(_pOwnerEntity, _T("ATT_VMU_IS_TO_DISPLAY_ALTITUDE_TEXT"), _bAllowAltitudeWarningTxt);
	}
	else//不符合告警条件
	{
		SET_ENTITY_CONTAINER_ATT_VALUE(_pOwnerEntity, _T("ATT_VMU_PULL_UP_WARNING"), false);
		SET_ENTITY_CONTAINER_ATT_VALUE(_pOwnerEntity, _T("ATT_VMU_ALTITUDE_WARNING"), false);

	}

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
