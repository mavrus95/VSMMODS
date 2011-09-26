// Заголовочный файл для дисплея МТ-12232А
#include "VSM.HPP"
#define LCD_STR_NUM 4  // количество страниц
#define LCD_STR_LEN 8  // количество точек в странице
#define LCD_LINE_NUM
#define LCD_LENGTH 122 //размер рабочего поля (длина)
#define LCD_WIDTH 32   //размер рабочего поля (ширина)
#define LCD_CONTROL 2  //количество контроллеров

// Инициализация
#define DISPLAY_ON 0xAF //включить дисплей
#define DISPLAY_OFF 0xAE //выключить дисплей
#define SET_XADDRESS 0x80
#define SET_YADDRESS 0x40

// Задержки
#define DELAY_1s  1000000000000
#define DELAY_1ms 1000000000
#define DELAY_1us 1000000
#define DELAY_1ns 1000
#define DELAY_1ps 1

//Объявление функций 
class LCD12232A : public IACTIVEMODEL, public IDSIMMODEL
{
	public:
		// Определение пинов устройства
		INT isdigital (CHAR *pinname);
		//Загрузка
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
			//Пины устройства
			IDSIMPIN *res;
			IDSIMPIN *cs;
			IDSIMPIN *en;
			IDSIMPIN *a0;
			IDSIMPIN *rw;
			IDSIMPIN *d[8];
			IBUSPIN *databus; //D[0..7]
			//Графика
			BYTE x_addr;
			BYTE y_addr;
			BYTE cur_str;
			BYTE status;
			//BYTE DDRAM [LCD_STR_NUM]*80*[LCD_STR_LEN];
			BOOL new_flag;

			BOX lcdarea;
			float pix_width, pix_height;
};


