// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"
#define B_pMem (sizeof(TELEM) * 8)

TBitField::TBitField()
{
	BitLen = 0;
	MemLen = 0;
	pMem = 0;
}

TBitField::TBitField(int len)
{
	if (len <= 0)       throw "negative_length";               //Исключение.
	BitLen = len;
	MemLen = (len + B_pMem - 1) / B_pMem;
	pMem = new TELEM[MemLen];
	if (pMem != NULL)
	{
		for (int i = 0; i < MemLen; i++)
		{
			pMem[i] = 0;
		}
	}
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	if (bf.BitLen <= 0) 	throw "negative_length";
	this->BitLen = bf.BitLen;
	this->MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	if (pMem != NULL){
		for (int i = 0; i < MemLen; i++)
		{
			this->pMem[i] = bf.pMem[i];
		}
	}

}

TBitField::~TBitField()
{
	delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	if ((n < 0) || (n >= BitLen)) throw "incorrect_set_index";
	return n / B_pMem;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	return 1 << (n % B_pMem);
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if ((n < 0) || (n >= BitLen))  throw "incorrect_set_index";    //проверяем, чтобы не выходило за границы заданного поля или не был отрицательный индекс
	
	else	pMem[GetMemIndex(n)] = pMem[GetMemIndex(n)] | GetMemMask(n); // наш элемент с индексом n складываем с маской, т.е. 01101 | 00010 = 011(1)1  мы установили бит.
	
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if ((n < 0) || (n >= BitLen))   throw "incorrect_clr_index";  
	
	else  pMem[GetMemIndex(n)] = pMem[GetMemIndex(n)] & ~GetMemMask(n); 
	
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if ((n < 0) || (n >= BitLen))   throw "incorrect_get_index"; 
	
	else	return pMem[GetMemIndex(n)] & GetMemMask(n); 

	
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	BitLen = bf.BitLen;
	
	if (MemLen != bf.MemLen)	MemLen = bf.MemLen;
	
	if (pMem != NULL)	delete[] pMem;
	
	pMem = new TELEM[MemLen];

	for (int i = 0; i < MemLen; i++)	pMem[i] = bf.pMem[i];

	return *this;

}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	int tmp = 1;
	
	if (BitLen != bf.BitLen)	tmp = 0;
	else
	{
		for (int i = 0; i < MemLen; i++)
		{
			if (pMem[i] != bf.pMem[i])
			{
				tmp = 0;
				break;
			}
		}
	}
	return tmp;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	int tmp = 0;
	if (BitLen != bf.BitLen) tmp = 1;
	else
	{
		for (int i = 0; i < MemLen; i++)
		{
			if (pMem[i] != bf.pMem[i])
			{
				tmp = 1;
				break;
			}
		}
	}
	return tmp;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	int len;
	if (BitLen >= bf.BitLen)
	{
		len = BitLen;
	}
	else
	{
		len = bf.BitLen;
	}
	TBitField tmp(len);
	for (int i = 0; i < MemLen; i++)
	{
		tmp.pMem[i] = pMem[i];
	}
	for (int i = 0; i < bf.MemLen; i++)
	{
		tmp.pMem[i] |= bf.pMem[i];
	}
	return tmp;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	int len;
	if (BitLen >= bf.BitLen)
	{
		len = BitLen;
	}
	else
	{
		len = bf.BitLen;
	}
	TBitField tmp(len);
	for (int i = 0; i < MemLen; i++)
	{
		tmp.pMem[i] = pMem[i];
	}
	for (int i = 0; i < bf.MemLen; i++)
	{
		tmp.pMem[i] &= bf.pMem[i];
	}
	return tmp;
}

TBitField TBitField::operator~(void) // отрицание
{
	int n;
	n = BitLen;
	TBitField tmp(n);
	for (int i = 0; i < n; i++)
	{
		if (GetBit(i))
		{
			tmp.ClrBit(i);
		}
		else
		{
			tmp.SetBit(i);
		}
	}
	return tmp;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	char a = '\0';
	while (a != ' ')
	{
		istr >> a;
	}
	int i = 0;
	while (1)    //бесконечный цикл
	{
		istr >> a;
		if (a == '0')
		{
			bf.ClrBit(i++);
		}
		if (a == '1')
		{
			bf.SetBit(i++);
		}
		else
		{
			break;
		}
	}
	return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	int tmp = bf.GetLength();
	for (int i = 0; i < tmp; i++)
	{
		if (bf.GetBit(i))
		{
			ostr << '1';
		}
		else
		{
			ostr << '0';
		}
	}
	return ostr;
}
