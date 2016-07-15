//*****************************************************************************
//
// include
//
//*****************************************************************************
#include "myKey.h"
//*****************************************************************************
//
// KeyInit
//
//*****************************************************************************
void KeyInit(void) {
	mSetIn_Key_1_IO;
	mSetIn_Key_2_IO;
}

//*****************************************************************************
//
// KeyDeal
//
//*****************************************************************************
void KeyDeal(void) {

}

//*****************************************************************************
//
// Port 1 interrupt service routine
//
//*****************************************************************************
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void) {
	//TODO...
	P1IFG = 0;                          // IFG cleared
}
//*****************************************************************************
//
// Port 2 interrupt service routine
//
//*****************************************************************************
#pragma vector=PORT2_VECTOR
__interrupt void Port_2(void) {
	//TODO...
	P2IFG = 0;                          // IFG cleared
}
//*****************************************************************************
//
// TM4�жϺ���
//
//*****************************************************************************
//void GPIOF_IntHandler(void) {
//	/*��������-------------------------------------------------------*/
//	unsigned int ulStatus;
//	int i = 0;
//	KeyInt_HandleTypeDef *p;
//	/*�жϱ�־��ȡ-------------------------------------------------------*/
//	ulStatus = GPIOIntStatus(GPIO_PORTF_BASE, true);
//	GPIOIntClear(GPIO_PORTF_BASE, ulStatus);
//	/*�����ж�-------------------------------------------------------*/
//	for (i = 0; i < KeyNum; i++) {
//		switch (i) {
//		case 1:
//			p = &KeySW1;
//			break;
//		case 2:
//			p = &KeySW2;
//			break;
//		default:
//			break;
//		}
//		if (ulStatus & (p->GPIO_INT_PIN_x && p->USED)) {
//			// ��ʱԼ10ms��������������
//			delay_ms(10);
//			// �ȴ�KEY̧��
//			if (GPIOPinRead(p->GPIO_PORTx_BASE, p->GPIO_PIN_x) != 0x00)
//				return;
//			while (GPIOPinRead(p->GPIO_PORTx_BASE, p->GPIO_PIN_x) == 0x00) {
//			}
//			//TODO �߼�����
//			return;
//		}
//	}
//
//}