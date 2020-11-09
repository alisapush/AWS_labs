#include <stdio.h>
#include <malloc.h>
#include <iostream>
using namespace std;

// вариант 21) F[i]=A[i]-(B[i]*C[i])+D[i] , i=1...8;

int main() 
{
	_int8  a[8] = { 16, 24, 6, 98, 12, 29, 78, 12 };
	_int8  b[8] = { 3, -4, 10, 10, -3, -4, 11, 0 };
	_int8  c[8] = { 2, -5, -3, 10, -2, -5, 12, 27 };
	_int16 d[8] = { -2, 1, -33, 7, -6, -8, 56, -9 };
	_int16 f[8];

	_asm {

		// расширение
		// регистры для ускорения производиельности

		movq mm0, qword ptr[a] // регист 64 разряда кладу массив а
		movq mm1, qword ptr[b]
		movq mm2, qword ptr[c]
		movq mm3, qword ptr[d]

		// скрешивание значений

		punpcklbw mm0, mm0
		punpcklbw mm1, mm1
		punpcklbw mm2, mm2

		// сдвиг каждой ячейки и добавляем нули

		psraw     mm0, 8
		psraw     mm1, 8
		psraw     mm2, 8

		// в 64 бита влазит четыре 16 битных элемента

		pmullw mm1, mm2
		psubsw mm0, mm1
		paddsw mm0, mm3

		// осталось обработать 4 элемента во второй половине

		movq qword ptr[f], mm0

		movq mm0, qword ptr[a + 4]
		movq mm1, qword ptr[b + 4]
		movq mm2, qword ptr[c + 4]
		movq mm3, qword ptr[d + 8]

		punpcklbw mm0, mm0
		punpcklbw mm1, mm1
		punpcklbw mm2, mm2

		psraw     mm0, 8
		psraw     mm1, 8
		psraw     mm2, 8

		pmullw mm1, mm2
		psubsw mm0, mm1
		paddsw mm0, mm3

		movq qword ptr[f + 8], mm0
	}

	for (int i = 0; i < 8; i++)
		cout << int(a[i]) << "  ";
	cout << endl;

	for (int i = 0; i < 8; i++)
		cout << int(b[i]) << "  ";
	cout << endl;

	for (int i = 0; i < 8; i++)
		cout << int(c[i]) << "  ";
	cout << endl;

	for (int i = 0; i < 8; i++)
		cout << int(d[i]) << "  ";
	cout << endl;

	for (int i = 0; i < 8; i++)
		cout << int(f[i]) << "   ";
}
