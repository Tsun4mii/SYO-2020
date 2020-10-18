#include "stdafx.h"
#include "IT.h"
#include "Error.h"
#include<iomanip>

namespace IT
{
	IdTable Create(int size)
	{
		IdTable* tabl = new IdTable;
		if (size > TI_MAXSIZE) throw ERROR_THROW(160);
		
		tabl->maxsize = size;
		tabl->size = 0;
		tabl->table = new Entry[size];
		return*tabl;
	}

	void Add(IdTable& idtable, Entry entry)
	{
		if (idtable.size + 1 > idtable.maxsize)
			throw ERROR_THROW(161);

		idtable.table[idtable.size] = entry;
		idtable.size += 1;
	}

	Entry GetEntry(IdTable& idtable, int n)
	{
		return idtable.table[n];
	}

	int IsId(IdTable& idtable,  char id[ID_MAXSIZE])
	{
		for (int i = 0; i < idtable.size; i++)
		{
			if (strcmp(idtable.table[i].id, id) == 0) return i;
		}

		return TI_NULLIDX;
	}

	void Delete(IdTable& idtable)
	{
		delete[] idtable.table;
	}
	void showTable(IdTable& idtable)
	{
		int i, j, numberOP = 0;
		std::cout << std::setfill('-') << std::setw(87) << '-' << std::endl;
		std::cout << "   №" << " | " << "Идентификатор" << " | " << "Тип данных" << " | " << "Тип идентификатора" << " | " << "Индекс в ТЛ" << " | " << "Значение    " << std::endl;
		std::cout << std::setw(87) << '-' << std::endl;
		for (i = 0, j = 0; i < idtable.size; i++, j++)
		{
			if (idtable.table[i].idtype == OP) 
			{
				numberOP++;
				j--;
				continue;
			}
			std::cout << std::setfill('0') << std::setw(4) << std::right << j << " | ";
			std::cout << std::setfill(' ') << std::setw(13) << std::left << idtable.table[i].id << " | ";
			switch (idtable.table[i].iddatatype)
			{
			case INT: std::cout << std::setw(10) << std::left;
				if (idtable.table[i].idtype == OP) std::cout << "-" << " | ";
				else std::cout << "number" << " | "; break;
			case STR: std::cout << std::setw(10) << std::left;
				if (idtable.table[i].idtype == OP) std::cout << "-" << " | ";
				else std::cout << "text" << " | "; break;
			case BL: std::cout << std::setw(10) << std::left;
				if (idtable.table[i].idtype == OP) std::cout << "-" << " | ";
				else std::cout << "boolean" << " | "; break;
			default: std::cout << std::setw(10) << std::left << "unknown" << " | "; break;
			}
			switch (idtable.table[i].idtype)
			{
			case V: std::cout << std::setw(18) << std::left << "переменная" << " | "; break;
			case F: std::cout << std::setw(18) << std::left << "функция" << " | "; break;
			case P: std::cout << std::setw(18) << std::left << "параметр" << " | "; break;
			case L: std::cout << std::setw(18) << std::left << "литерал" << " | "; break;
			case OP: std::cout << std::setw(18) << std::left << "оператор" << " | ";
				numberOP++;
				break;
			default: std::cout << std::setw(18) << std::left << "unknown" << " | "; break;
			}
			std::cout << std::setw(11) << std::left << idtable.table[i].idxfirstLE << " | ";
			if (idtable.table[i].iddatatype == INT && (idtable.table[i].idtype == V || idtable.table[i].idtype == L))
				std::cout << std::setw(18) << std::left << idtable.table[i].value.vint;
			else if (idtable.table[i].iddatatype == STR && (idtable.table[i].idtype == V || idtable.table[i].idtype == L))
				std::cout << "[" << idtable.table[i].value.vstr.len << "]\"" << idtable.table[i].value.vstr.str << "\"";
			else if (idtable.table[i].iddatatype == BL && (idtable.table[i].idtype == V || idtable.table[i].idtype == L))
				std::cout << std::setw(18) << std::left << idtable.table[i].value.vbool;
			else
				std::cout << "-";
			std::cout << std::endl;
		}
		std::cout << std::setfill('-') << std::setw(87) << '-' << std::endl;
		std::cout << "Количество идентификаторов: " << i - numberOP << std::endl;
		std::cout << std::setw(87) << '-' << std::endl;
	}
};