#include <iostream>
#include <fstream>
#include <string.h>
#include <string>
#include <Windows.h>

using namespace std;

void MyEncryption(char Ins[64], unsigned short OutCoding[64]);

enum  ConsoleColor : unsigned int
{							//0000 IRGB  
	Black = 0x00,			//0000 0000
	Blue = 0x01,			//0000 0001
	Green = 0x02,			//0000 0010
	Cyan = 0x03,			//0000 0011
	Red = 0x04,				//0000 0100
	Magenta = 0x05,			//0000 0101
	Brown = 0x06,			//0000 0110
	LightGray = 0x07,		//0000 0111 
	DarkGray = 0x08,		//0000 1000
	LightBlue = 0x09,		//0000 1001
	LightGreen = 0x0a,		//0000 1010
	LightCyan = 0x0b,		//0000 1011
	LightRed = 0x0c,		//0000 1100
	LightMagenta = 0x0d,	//0000 1101
	Yellow = 0x0e,			//0000 1110
	White = 0x0f,			//0000 1111
};

void SetColor(ConsoleColor text, ConsoleColor background)
{
	HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(Console, (WORD)((background << 4) | text));
}

void InputColor()
{
	// 5 Зміна кольору тексту та фону
	int kText, kBackground;
	do {
		cout << "Select the text and background color:\n";
		cout << "0.	Black		\n"
			<< "1.	Blue		\n"
			<< "2.	Green		\n"
			<< "3.	Cyan		\n"
			<< "4.	Red			\n"
			<< "5.	Magenta		\n"
			<< "6.	Brown		\n"
			<< "7.	LightGray	\n"
			<< "8.	DarkGray	\n"
			<< "9.	LightBlue	\n"
			<< "10.LightGreen	\n"
			<< "11.LightCyan	\n"
			<< "12.LightRed	\n"
			<< "13.LightMagen	\n"
			<< "14.Yellow		\n"
			<< "15.White		\n";

		cin >> kText >> kBackground;
		if (kText <= 15 || kBackground <= 15)
			SetColor(ConsoleColor(kText), ConsoleColor(kBackground));
		else
			cout << "Uncorrect value(es)";
	} while (kText > 15 || kBackground > 15);
	cin.get();

}

void MenuExamples() {
	system("chcp 1251");

	cout << "    Виберіть число відповідно до завдання\n";
	cout << "    1.  Обчислення виразу з використанням побітових операцій \n";
	cout << "    2.  Шифрування\n";
	cout << "    3.	 Шифрування структури \n";
	cout << "    4.	 Додаткове завдання – бітове зображення 8х8 \n";
	cout << "    5.  Зміна кольору тексту та фону\n";
	cout << "    6.  Вихід \n";

}

void Example1()
{
	system("chcp 1251");
	cout << " Обчислення виразів з використанням побітових операцій  \n";
	int a, b, c, d, x, y;
	cout << "Вираз : " << endl <<
		"            x = b * 2049 + ((d * 15 + 12 * a) / 2048) - c * 100 + d * 127; " << endl <<
		"            x = b + 2^11 * b + ((d*2^4 - b + a*2^3 + a*2^2) / 2^11) - c*2^7 - c*2^4 - c*2^3- c*2^2 + d*2^7 - d" << endl <<
		"            x = b + 2048*b + ((d * 16 - b + 8 * a + 4 * a) / 2048) - c * 128 + c * 16 + c * 8 + c*4 + d * 128 - d" << endl << endl;
	cout << " Введiть a b c d " << endl;
	cin >> a >> b >> c >> d;
	cout << endl;
	auto st = cin.rdstate();
	if (st != cin.goodbit) { cin.clear(); cout << " error \n"; cin.get(); cin.get(); return; }

	x = b + (b << 11) + (((d << 4) - b + (a << 3) + (a << 2)) >> 11) - (c << 7) + (c << 4) + (c << 3) + (c << 2) + (d << 7) - d;
	y = b * 2049 + ((d * 15 + 12 * a) / 2048) - c * 100 + d * 127;

	cout << " a= " << a << "  b= " << b << " c= " << c << " d= " << d << endl;
	cout << "  x1(побітові операції)= " << x << endl << "  x2(перевірка)= " << y << endl;
	cin.get();
}

void decimalToBinary(unsigned short OutCoding[128], int index) {
	char out[17];
	int i, in, ix, n = 0;
	double x;

	in = OutCoding[index];
	cout << " " << in << endl;
	auto st = cin.rdstate();
	if (st != cin.goodbit) { cin.clear(); cout << " error \n"; cin.get(); cin.get(); return; }

	if (in != 0) {
		x = in;
		do {
			x = x / 2.;
			ix = (int)x;
			if ((x - ix) != 0) out[n] = '1';
			else out[n] = '0';
			n++;
			x = ix;
		} while (x >= 1);
	}

	for (i = n - 1; i >= 0; i--)
		cout << out[i];
	cout << endl;
	cin.get();
}


/*
Задано текст до 64 символів. Доповнити пробілами до 64 символів. Шифрувати тексти
таким чином, щоб кожний символ тексту записувався у два байта. Два байта мають таку
структуру:
у бітах 0-5 позиція символу в рядку (6 бітів),
6 - біт парності позиції символу (1 біт)
у бітах 7-13 ASCII - код букви (8 біт),
15 біт – біт парності коду символу (1 біт)
*/

void MyEncryption(char InS[64], unsigned short OutCoding[64])
{
	unsigned char c;
	unsigned short r, t, i, b, l;
	short j;
	for (i = 0; i < 64; i++)            //розглянемо для прикладу 5 ітерацію циклу, тобто маємо 5 символ, наприклад хай це буде символ 's' 
	{
		r = 0;							// 0000 0000 0000 0000
		c = InS[i];                     // s - 0x73 = 0111 0011
		t = c;
		r |= i;							// 0000 0000 0000 0101	if i=5 -> 0000 0000 0000 0101

		//if (i % 2 == 0)					
		//{
		//	r |= 0 << 6;			
		//}
		//else
		//{
		//	r |= 1 << 6;				//  0000 0000 0100 0101	if i=5
		//}

		t = 1;
		b = 0;
		for (int j = 0; j < 8; j++)         // обчислення біта парності позиції символу
		{
			if (i & t) {
				if (b == 0) b = 1; else b = 0;
			}
			t <<= 1;
		}
		r |= b << 6;

		t = InS[i];

		r |= t << 7;					//	0011 1001 1100 0101	if i=5 -> 0000 0000 0000 0101

		l = InS[i];
		t = 1;
		b = 0;
		for (j = 0; j < 8; j++)         // обчислення біта парності коду символу
		{
			if (l & t) {
				if (b == 0) b = 1; else b = 0;
			}
			t <<= 1;
		}
		r |= b << 15;                    // 1011 1001 1100 0101  if i=5 -> 0000 0000 0000 0101; if l(s) = 0111 0011
		OutCoding[i] = r;
	}
}

void Example2()
{
	// 2.  Шифрування

	unsigned short OutCoding[64];
	string string_text;

	cout << "Enter text: ";
	getline(cin, string_text);

	char char_text[64];
	for (int i = 0; i < string_text.length(); i++)
	{
		char_text[i] = string_text[i];
		cout << char_text[i];
	}
	cout << "\n";
	if (string_text.length() != 64)  // доповним нулями
	{
		for (int i = string_text.length(); i < 64; i++)
		{
			char_text[i] = ' ';
		}
	}

	MyEncryption(char_text, OutCoding);
	cout << "\n 5 element : ";
	decimalToBinary(OutCoding, 5);
}


struct TextCode {
	unsigned short kb : 8;
	unsigned short posrow : 6;
	unsigned short bitp : 1;
	unsigned short bitkb : 1;
};

unsigned char pbit(unsigned char c)
{
	unsigned char t = 1, b = 0;
	for (int j = 0; j < 8; j++)         // обчислення біта парності
	{
		if (c & t) {
			if (b == 0) b = 1; else b = 0;
		}
		t <<= 1;
	}
	return b;
}

/*
Задано текст до 64 символів.Доповнити пробілами до 64 символів.Шифрувати тексти
таким чином, щоб кожний символ тексту записувався у два байта.Два байта мають таку
структуру :
у бітах 0 - 5 позиція символу в рядку(6 бітів),
6 - біт парності позиції символу(1 біт)
у бітах 7 - 13 ASCII - код букви(8 біт),
15 біт – біт парності коду символу(1 біт)
*/

void MyEncryptionS(char InS[64], TextCode OutCoding[64])
{
	unsigned char c;
	unsigned short r, t, i;
	short j;
	for (i = 0; i < 64; i++)            //
	{
		c = InS[i];                     // s - 0x73 = 0111 0011
		OutCoding[i].posrow = i;        //	позиція букви в рядку
		OutCoding[i].bitp = pbit(i);	//	біт парності позиції символу
		OutCoding[i].kb = c;			//	код букви
		OutCoding[i].bitkb = pbit(c);   //	біт парності коду символу

	}
}


void Example3() {
	// 3 Шифрування структури
		
	TextCode OutCoding[64];
	string string_text;

	cout << "Enter text: ";

	getline(cin, string_text);

	char char_text[64];

	for (int i = 0; i < string_text.length(); i++)
	{
		char_text[i] = string_text[i];
		cout << char_text[i];
	}
	cout << "\n";
	if (string_text.length() != 64)			// доповним нулями
	{
		for (int i = string_text.length(); i < 64; i++)
		{
			char_text[i] = ' ';
		}
	}

	MyEncryptionS(char_text, OutCoding);
}


/// ДОДАТКОВЕ ЗАВДАННЯ!
/*
*	Бітовий образ 8х8 задається вісьмома байтами, кожен з яких задає одну скан-лінію з 8 точок
	(0-7 біти): нульовий біт – біла точка, одиничний – чорна. За вказаними користувачем
	вісьмома байтами вивести на екран (у текстовому режимі) відповідне йому зображення. Для
	відображення білих точок використати символ “пробіл”, для відображення чорних – символ
	“О”
*/

struct bipMap {
	byte bit0 : 1;
	byte bit1 : 1;
	byte bit2 : 1;
	byte bit3 : 1;
	byte bit4 : 1;
	byte bit5 : 1;
	byte bit6 : 1;
	byte bit7 : 1;
};

void Optional()
{
	// 4 Додаткове завдання – бітове зображення 8х8
	
	short unsigned b[8];
	bipMap image[8];
	short unsigned t = 0;
	short unsigned mask = 1;
	cout << "Enter 8 bytes to form the image :";
	for (size_t i = 0; i < 8; i++)
	{
		cin >> b[i];
	}
	for (size_t i = 0; i < 8; i++)
	{
		image[i].bit0 = (b[i] & mask);
		b[i] = b[i] >> 1;
		image[i].bit1 = (b[i] & mask);
		b[i] = b[i] >> 1;
		image[i].bit2 = (b[i] & mask);
		b[i] = b[i] >> 1;
		image[i].bit3 = (b[i] & mask);
		b[i] = b[i] >> 1;
		image[i].bit4 = (b[i] & mask);
		b[i] = b[i] >> 1;
		image[i].bit5 = (b[i] & mask);
		b[i] = b[i] >> 1;
		image[i].bit6 = (b[i] & mask);
		b[i] = b[i] >> 1;
		image[i].bit7 = (b[i] & mask);
	}

	for (size_t i = 0; i < 8; i++)
	{
		if (image[i].bit0 == 1)
			cout << "O";
		else
			cout << " ";

		if (image[i].bit1 == 1)
			cout << "O";
		else
			cout << " ";

		if (image[i].bit2 == 1)
			cout << "O";
		else
			cout << " ";

		if (image[i].bit3 == 1)
			cout << "O";
		else
			cout << " ";

		if (image[i].bit4 == 1)
			cout << "O";
		else
			cout << " ";

		if (image[i].bit5 == 1)
			cout << "O";
		else
			cout << " ";

		if (image[i].bit6 == 1)
			cout << "O";
		else
			cout << " ";

		if (image[i].bit7 == 1)
			cout << "O";
		else
			cout << " ";

		cout << endl;
	}
	cin.get();
}

void Examples() {
	char ch = '5';
	do {
		MenuExamples();


		ch = cin.get();
		cin.get();

		switch (ch) {
		case '1':
			Example1();
			break;
		case '2':
		{
			Example2();
			cin.get();
			break;
		}
		case '3':
			Example3();
			cin.get();
			break;
		case '4':
			Optional();
			cin.get();

		case '5':
			InputColor();
			break;

		case '6': cout << "end...";
		}

		
	} while (ch != '6');
}




int main() {

	Examples();

}