// ������������ ���� ��� ������� ��-12232�
#include "VSM.HPP"
#define LCD_STR_NUM 4  // ���������� �������
#define LCD_STR_LEN 8  // ���������� ����� � ��������
#define LCD_LINE_NUM
#define LCD_LENGTH 122 //������ �������� ���� (�����)
#define LCD_WIDTH 32   //������ �������� ���� (������)
#define LCD_CONTROL 2  //���������� ������������

// �������������
#define DISPLAY_ON 0xAF //�������� �������
#define DISPLAY_OFF 0xAE //��������� �������
#define SET_XADDRESS 0x80
#define SET_YADDRESS 0x40

// ��������
#define DELAY_1s  1000000000000
#define DELAY_1ms 1000000000
#define DELAY_1us 1000000
#define DELAY_1ns 1000
#define DELAY_1ps 1

//���������� ������� 
class LCD12232A : public IACTIVEMODEL, public IDSIMMODEL
{
	public:
		// ����������� ����� ����������
		INT isdigital (CHAR *pinname);
		//��������
		VOID setup (IINSTANCE *inst, IDSIMCKT *dsim);
		VOID runctrl (RUNMODES mode);
		VOID actuate (REALTIME time, ACTIVESTATE newstate);
		BOOL indicate (REALTIME time, ACTIVEDATA *data);
		VOID simulate (ABSTIME time,DSIMMODES mode);
		VOID callback (ABSTIME time, EVENTID eventid);
		VOID initialize (ICOMPONENT *cpt);
		ISPICEMODEL *getspicemodel (CHAR *device);
		IDSIMMODEL *getdsimmodel (CHAR *device);
		VOID plot (ACTIVESTATE state);
		VOID animate (INT element, ACTIVEDATA *newstate);
		BOOL actuate (WORD key, INT x, INT y, DWORD flags);
		private:
			IINSTANCE *instance;
			IDSIMCKT *ckt;
			ICOMPONENT *component;
			//���� ����������
			IDSIMPIN *res;
			IDSIMPIN *cs;
			IDSIMPIN *en;
			IDSIMPIN *a0;
			IDSIMPIN *rw;
			IDSIMPIN *d[8];
			IBUSPIN *databus; //D[0..7]
			//�������
			BYTE x_addr;
			BYTE y_addr;
			BYTE cur_str;
			BYTE status;
			//BYTE DDRAM [LCD_STR_NUM]*80*[LCD_STR_LEN];
			BOOL new_flag;

			BOX lcdarea;
			float pix_width, pix_height;
};


