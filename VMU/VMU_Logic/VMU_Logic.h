//////////////////////////////////////////////////////////////////////////
//
//			-----------------------------
//			--     Developed by MSG    --
//			-----------------------------
//
//  File : VMU_Logic.h
//
//  Author : MaShawn
//
//  Create Date : Sat Sep 23 12:53:09 UTC+0800 2017
//
//  Description : VMU�߼�
//	Address : JiangSu
//	E-Mail : mashawn@live.cn
//	Phone : +8613814443825
//
//////////////////////////////////////////////////////////////////////////


#ifndef VMU_Logic_H
#define VMU_Logic_H


#include "sdk.LogicComponent.h"

#ifdef VMU_Logic_EXPORTS
#define VMU_Logic_API __declspec(dllexport)
#else
#define VMU_Logic_API __declspec(dllimport)
#endif

//{{GEN_PROJECT_DATA
#define SYSTEM_PREFIX "VMU"
//}}GEN_PROJECT_DATA


class VMU_Logic_API VMU_Logic :public LogicComponent 
{
public:
		
	// constructor
	VMU_Logic( Entity* pOwnerEntity );
	
	// destructor
	virtual ~VMU_Logic();

	// register component's properties
	virtual bool registerProperties();

	// register component's attributes at the owner entity
	virtual bool registerAttributes();
	
	// register component's Actions at the owner entity
	virtual bool registerActions();

	// register component's input events
	bool registerToInputDevices();

	//{{SLC_ACTIONS_FUNC_DECLERATION
	bool CBFuncActionVmuToggleSystem();
	bool CBFuncActionVmuToggleAltitudeWarning();
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

	bool ToggleSystemOnOff();//�л�ϵͳ����״̬
	void	CheckFlapsWarning();//����澯���
	void	CheckOverGWarning();//���ظ澯���
	void	CheckAltitudeWarning();//�߶ȸ澯���
	
private:
	//{{SLC_PROPERTIES_VARIABLES_DECLERATION
	float m_PropVmuMaxSpeedWithFlapsExtended;
	float m_PropVmuMinNegativeGWarning;
	float m_PropVmuMaxPositiveGWarning;
	float m_PropVmuMinAltitudeWarning;
	//}}SLC_PROPERTIES_VARIABLES_DECLERATION

	//{{SLC_GLOBALEVENT_VARIABLES_DECLERATION
	//}}SLC_GLOBALEVENT_VARIABLES_DECLERATION

	//{{SLC_ATTRIBUTECHANGE_VARIABLES_DECLERATION
	//}}SLC_ATTRIBUTECHANGE_VARIABLES_DECLERATION
	bool	 _bAllowAltitudeWarningTxt;//�Ƿ���ʾ�߶ȸ澯�ַ�
	bool	_isSystemOn;//ϵͳ״̬

};

#endif // SLC_H
