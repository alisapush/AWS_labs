#include <stdio.h>
#include <malloc.h>
#include <iostream>
#include <iomanip> 
using namespace std;

// вариант 21) F[i] = A[i] - (B[i] * C[i]) + D[i] , i = 1...8;

int main()
{
	_int8  A[8] = { 15, 24, 6, -98, 12, 29, 78, 12 };
	_int8  B[8] = { 3, -4, 10, 10, -3, -4, 11, 0 };
	_int8  C[8] = { 2, -5, -3, 10, -2, -5, 12, 27 };
	_int16 D[8] = { 1, 1, -33, 7, -6, -8, 56, -9 };
	_int16 F[8];

	_asm
	{
		// Init all arrays
		movq mm0, qword ptr[A]
		movq mm1, qword ptr[B]
		movq mm2, qword ptr[C]

		// F[i] = A[i] - (B[i]*C[i]) + D[i]




		// UNPACK B
		// Copy B to temp mm4
		movq mm4, mm1

		// Zero-ing temp mm3
		psubsw mm3, mm3

		// Unpacking mm4 from 8 chars to 4 words
		pcmpgtb mm3, mm4
		// Low-order bytes (Lbw)
		punpcklbw mm4, mm3

		// Place result to F1
		movq mm5, mm4




		// The same with C
		// Copy C to temp mm4
		movq mm4, mm2

		// Zero-ing temp mm3
		psubsw mm3, mm3

		// Unpacking mm4 from 8 chars to 4 words
		pcmpgtb mm3, mm4
		// Low-order bytes (Lbw)
		punpcklbw mm4, mm3

		// Place result to temp mm7
		movq mm7, mm4
	



		// B * C (word * word)
		pmullw mm5, mm7




		// Make A as word (2 bytes each item)
		movq mm4, mm0

		// Zero-ing temp mm3
		psubsw mm3, mm3

		// Unpacking mm4 from 8 chars to 4 words
		pcmpgtb mm3, mm4
		// Low-order bytes (Lbw)
		punpcklbw mm4, mm3

		// Place result to temp mm7
		movq mm7, mm4



		// A --- B*C
		psubsw mm7, mm5
		movq mm5, mm7





		// A-B*C +++ D
		paddsw mm5, qword ptr[D]


		// =================================================================================




		// UNPACK B
		// Copy B to temp mm4
		movq mm4, mm1

		// Zero-ing temp mm3
		psubsw mm3, mm3

		// Unpacking mm4 from 8 chars to 4 words
		pcmpgtb mm3, mm4
		// High-order bytes (Hbw)
		punpckhbw mm4, mm3

		// Place result to F2 (second pard of F stored in mm6)
		movq mm6, mm4





		// The same with C
		// Copy C to temp mm4
		movq mm4, mm2

		// Zero-ing temp mm3
		psubsw mm3, mm3

		// Unpacking mm4 from 8 chars to 4 words
		pcmpgtb mm3, mm4
		// High-order bytes (Hbw)
		punpckhbw mm4, mm3

		// Place result to temp mm7
		movq mm7, mm4




		// B * C (word * word)
		pmullw mm6, mm7




		// Make A as word (2 bytes each item)
		movq mm4, mm0

		// Zero-ing temp mm3
		psubsw mm3, mm3

		// Unpacking mm4 from 8 chars to 4 words
		pcmpgtb mm3, mm4
		// High-order bytes (Hbw)
		punpckhbw mm4, mm3

		// Place result to temp mm7
		movq mm7, mm4



		// A --- B*C
		psubsw mm7, mm6
		movq mm6, mm7





		// A-B*C +++ D
		paddsw mm6, qword ptr[D + 8]



		// =================================================================================

		movq qword ptr[F], mm5
		movq qword ptr[F + 8], mm6
	}

	int w = 6;
	__int16 result[8] = { 0 };

	for (int i = 0; i < 8; i++) {
		result[i] = A[i] - (B[i] * C[i]) + D[i];
	}

	cout << "F[i] = A[i] - (B[i] * C[i]) + D[i]" << endl << endl;

	cout << "Fc: ";
	for (int i = 0; i < 8; i++)
		cout << setw(w) << int(result[i]);
	cout << endl;

	cout << "----------------------------------------------------" << endl;

	
	cout << "A:  ";
	for (int i = 0; i < 8; i++)
		cout << setw(w) << int(A[i]);
	cout << endl;

	cout << "B:  ";
	for (int i = 0; i < 8; i++)
		cout << setw(w) << int(B[i]);
	cout << endl;

	cout << "C:  ";
	for (int i = 0; i < 8; i++)
		cout << setw(w) << int(C[i]);
	cout << endl;

	cout << "D:  ";
	for (int i = 0; i < 8; i++)
		cout << setw(w) << int(D[i]);
	cout << endl;

	cout << "----------------------------------------------------" << endl;

	
	cout << "Fa: ";
	for (int i = 0; i < 8; i++)
		cout << setw(w) << int(F[i]);

	cout << endl;
}




