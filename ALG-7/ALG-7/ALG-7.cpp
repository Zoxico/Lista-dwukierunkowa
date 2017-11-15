// ALG-7.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <conio.h>

#define ROZMIAR 101
using namespace std;


int p[ROZMIAR], key[ROZMIAR];
int lewy[ROZMIAR], prawy[ROZMIAR];
int iloscLiczb = 1, root, indeksUsunietego = 0;
bool wypisano[ROZMIAR], usunieto = false;

void Insert(int indeksNajnowszego)
{
	if (iloscLiczb == 1)
	{
		root = 1;
		iloscLiczb++;
	}
	else
	{
		int wartoscNowego = key[indeksNajnowszego], // K 
			indeksSprawdzanegoX = root, // X
			indeksSprawdzanegoY = 0; // Y

		while (indeksSprawdzanegoX != 0)
		{
			indeksSprawdzanegoY = indeksSprawdzanegoX;
			if (wartoscNowego < key[indeksSprawdzanegoY])
			{
				indeksSprawdzanegoX = lewy[indeksSprawdzanegoY];
			}
			else
			{
				indeksSprawdzanegoX = prawy[indeksSprawdzanegoY];
			}
		}
		p[indeksNajnowszego] = indeksSprawdzanegoY;

		if (indeksSprawdzanegoY == 0)
		{
			root = indeksNajnowszego;
		}
		else
		{
			if (wartoscNowego < key[indeksSprawdzanegoY])
			{
				lewy[indeksSprawdzanegoY] = indeksNajnowszego;

			}
			else
			{
				prawy[indeksSprawdzanegoY] = indeksNajnowszego;

			}
		}



		//if ((indeksSprawdzanegoX != 0))
		iloscLiczb++;
	}
}

int Min(int indeks)
{
	while (lewy[indeks] != 0)
		indeks = lewy[indeks];

		return indeks;
}

int Max(int indeks)
{
	while (prawy[indeks] != 0)
		indeks = prawy[indeks];

	return indeks;
}

int Member(int k)
{
	int x = root;

	while (x != 0 && k != key[x])
	{
		if (k < key[x])
			x = lewy[x];
		else
			x = prawy[x];
	}

	return x;
}

void InOrder()
{
	int x = root;// licznik = iloscLiczb;
	//JEDZIEMY NAJDALEJ W LEWO
	while (lewy[x] != 0)
		x = lewy[x];
	//TUTAJ X TO INDEKS NAJMNIEJSZEGO

	while (x != Max(root)) //((lewy[x] != 0 || prawy[x] != 0 || p[x] != 0) && licznik > 0)
	{						// DOPÓKI X NIE JEST INDEKSEM MAKSYMALNEGO ELEMENTU

		if (!wypisano[x])
		{
			cout << key[x] << " ";
			wypisano[x] = true;
		}
		else
		{
			if (lewy[x] != 0 && !wypisano[lewy[x]])
				x = lewy[x];
			else if (prawy[x] != 0 && !wypisano[prawy[x]])
				x = prawy[x];
			else
				x = p[x];
			//else if (p[x] != 0 && !wypisano[p[x]])
			//	x = p[x];
			//else
			//	x = prawy[x];
		} 
	}

	cout << key[x]; _getch();
	for (int i = 0; i < ROZMIAR; i++)
		wypisano[i] = false;

}

int Successor(int x)
{
	int y;
	if (prawy[x] != 0)
		y = Min(prawy[x]);
	
	else
	{
		y = p[x];
		while (y != 0 && x == prawy[y])
		{
			x = y;
			y = p[x];
		}

	}
	return y;
}
 
int Delete(int z)
{
	int x, y;

	if (lewy[z] == 0 || prawy[z] == 0)	y = z;
	else	y = Successor(z);
	

	x = lewy[y];

	if (x == 0)		x = prawy[y];
	
	if (x != 0)		p[x] = p[y];
	
	if (p[y] == 0)	root = x;
	
	else
	{
		if (y == lewy[p[y]])	lewy[p[y]] = x; 
		else	prawy[p[y]] = x;
	}

	if (y != z)		key[z] = key[y];

	return y;
}

int main()
{
	//bool toPierwszaLiczba = true;
	for (int i = 0; i < ROZMIAR; i++)
	{
		lewy[i] = 0;
		prawy[i] = 0;
		p[i] = 0;
		key[i] = 0;
		wypisano[i] = false; 
	}

	while (true)
	{
		system("cls");
		cout << "[1/ENTER] INSERT" << endl;
		cout << "[2] INORDER" << endl;
		cout << "[3] MEMBER" << endl;
		cout << "[4] MIN" << endl;
		cout << "[5] MAX" << endl;
		cout << "[6] SUCCESSOR" << endl;
		cout << "[7] DELETE" << endl;
		cout << endl;
		cout << "[X] Wyjdz z programu" << endl;

		char wybor = _getch();
		int szukana, i = 0;
		switch (wybor)
		{
			case '1':
				cout << "Podaj liczbe: ";
				if (!usunieto)
				{
					cin >> key[iloscLiczb];
					Insert(iloscLiczb);
				}
				else
				{
					cin >> key[indeksUsunietego];
					Insert(indeksUsunietego);
					usunieto = false;
				}
					
				

				break;
			case 13:
				cout << "Podaj liczbe: ";
				if (!usunieto)
				{
					cin >> key[iloscLiczb];
					Insert(iloscLiczb);
				}
				else
				{
					cin >> key[indeksUsunietego];
					Insert(indeksUsunietego);
					usunieto = false;
				}

				break;

			case '2':
				InOrder();
				break;

			case '3': 
				cout << "Podaj ktorej liczby chcesz poszukac: ";
				cin >> szukana;
				cout << endl << szukana << " ma indeks: " << Member(szukana);
				_getch();
				break;

			case '4':
				cout << endl << "Najmniejszy element: " << key[Min(root)];
				_getch();
				break;

			case '5':
				cout << endl << "Najwiekszy element: " << key[Max(root)];
				_getch();
				break;

			case '6': 
				cout << "Podaj ktorej liczby nastepnika chcesz poszukac: ";
				cin >> szukana;	
				while (key[i] != szukana)
					i++;
				cout << endl << "Nastepnik " << szukana << " to " << key[Successor(i)];
				_getch();
				break;

			case '7':
				InOrder();
				cout << endl << "Co chcesz usunac?  "  ;
				cin >> szukana;

				while (key[i] != szukana && i < iloscLiczb)
					i++;
				if (i != iloscLiczb)
				{
					Delete(i);	usunieto = true;
					indeksUsunietego = i;
					iloscLiczb--;
				}
				

				cout << "Gotowe! " << endl;
				InOrder();
			//	_getch();
				break;

			case 'x':
				exit(0);
				break;


		default:
			break;
		}
	}

    return 0;
}

