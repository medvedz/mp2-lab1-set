// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp) //: BitField(-1)
{
	BitField = TBitField(mp);
	MaxPower = mp;
}

// конструктор копирования
TSet::TSet(const TSet &s) //: BitField(-1)
{
	BitField = TBitField(s.BitField);
	MaxPower = s.MaxPower;
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) // : BitField(-1)
{
	BitField = TBitField(bf);
	MaxPower = bf.GetLength();
}

TSet::operator TBitField()
{
	TBitField tmp(BitField);
	return tmp;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
	int tmp;
	tmp = MaxPower;
	return tmp;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
	int tmp;
	tmp = BitField.GetBit(Elem);
	return tmp;
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
	BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
	BitField.ClrBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) // присваивание
{
	if (MaxPower != s.MaxPower)
	{
		MaxPower = s.MaxPower;
	}
	if (BitField != s.BitField)
	{
		BitField = s.BitField;
	}
	return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
	if (BitField != s.BitField)
	{
		return 0;
	}
	else
	{
		return (BitField == s.BitField);
	}
}

int TSet::operator!=(const TSet &s) const // сравнение
{
	return (BitField != s.BitField);
}

TSet TSet::operator+(const TSet &s) // объединение
{
	TSet tmp(BitField | s.BitField);
	return tmp;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
	if (Elem < MaxPower)
	{
		TSet tmp(BitField);
		tmp.InsElem(Elem);
		return tmp;
	}
	else
	{
		TSet tmp(Elem);
		tmp.BitField = tmp.BitField & BitField;
		tmp.InsElem(Elem);
		return tmp;
	}
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
	TSet tmp(BitField);
	tmp.DelElem(Elem);
	return tmp;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
	TSet tmp(BitField & s.BitField);
	return tmp;
}

TSet TSet::operator~(void) // дополнение
{
	TSet tmp(~BitField);
	return tmp;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
	int tmp;
	char a;
	while (a != '{')
	{
		istr >> a;
	}
	while ((a != ',') && (a != '}'))
	{
		istr >> a;
		s.InsElem(tmp);
	}
	return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
	char a;
	ostr << "{";
	int tmp = s.GetMaxPower();
	for (int i = 0; i < tmp; i++)
	{
		ostr << a << ' ' << i;
	}
	ostr << "}";
	return ostr;
}
