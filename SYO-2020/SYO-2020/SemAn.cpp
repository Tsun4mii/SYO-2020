#include "SemAn.h"
#include"Error.h"
#include"IT.h"
#include"LT.h"
#include"LexAn.h"


namespace Semantic
{
	bool Semantic::semanticsCheck(Lex::LEX& tables, Log::LOG& log)
	{
		bool sem_ok = true;

		for (int i = 0; i < tables.lextable.size; i++)
		{
			switch (tables.lextable.table[i].lexema)
			{
			case LEX_NEW:
			{
				if (tables.lextable.table[i + 1].lexema != LEX_TYPE)
				{
					sem_ok = false;
					throw ERROR_THROW_IN(303, tables.lextable.table[i].sn, -1);
					break;
				}
			}
			case LEX_TYPE:
			{
				if (tables.lextable.table[i + 1].lexema == LEX_ID && tables.lextable.table[i-1].lexema != LEX_NEW && tables.idtable.table[tables.lextable.table[i + 1].idxTI].idtype != IT::P)
				{
					sem_ok = false;
					throw ERROR_THROW_IN(304, tables.lextable.table[i].sn, -1);
					break;
				}
			}
			case LEX_ID:
			{
				if (tables.lextable.table[i - 1].lexema == LEX_FUNCTION)
				{
					IT::IDDATATYPE ftype = tables.idtable.table[tables.lextable.table[i].idxTI].iddatatype;
					int j = i + 1;
					while (tables.lextable.table[j].lexema != LEX_RETURN)
						j++;
					if (ftype != tables.idtable.table[tables.lextable.table[j + 1].idxTI].iddatatype)
					{
						sem_ok = false;
						throw ERROR_THROW_IN(315, tables.lextable.table[i].sn, -1);
					}
				}
				if (tables.lextable.table[i + 1].lexema == LEX_LEFTTHESIS && tables.lextable.table[i - 1].lexema != LEX_FUNCTION)
				{
					int parms = 0;
					for (int j = i + 1; tables.lextable.table[j].lexema != LEX_RIGHTTHESIS; j++)
					{
						if (tables.lextable.table[j].lexema == LEX_ID || tables.lextable.table[j].lexema == LEX_LITERAL)
						{
							parms++;
							IT::IDDATATYPE ctype = tables.idtable.table[tables.lextable.table[j].idxTI].iddatatype;
							if (ctype != tables.idtable.table[tables.lextable.table[i].idxTI].types[parms - 1])
							{
								sem_ok = false;
								throw ERROR_THROW_IN(309, tables.lextable.table[i].sn, -1);
							}
						}
					}
					if(parms != tables.idtable.table[tables.lextable.table[i].idxTI].countOfPar)
					{ 
						sem_ok = false;
						throw ERROR_THROW_IN(308, tables.lextable.table[i].sn, -1);
					}
				}
				break;
			}
			case LEX_MORE: case LEX_LESS: case LEX_MREQUAL: case LEX_LSEQUAL: case LEX_NOT: case LEX_IFEQ:
			{
				bool flag = true;
				if (i > 1 && tables.lextable.table[i - 1].idxTI != LT_TI_NULLIDX)
				{
					if (tables.idtable.table[tables.lextable.table[i - 1].idxTI].iddatatype != IT::IDDATATYPE::INT)
						flag = false;
				}
				if (tables.lextable.table[i + 1].idxTI != LT_TI_NULLIDX)
				{
					if (tables.idtable.table[tables.lextable.table[i + 1].idxTI].iddatatype != IT::IDDATATYPE::INT)
						flag = false;
				}
				if (!flag)
				{
					// строка или неизвестный ид в условии
					throw ERROR_THROW_IN(317, tables.lextable.table[i].sn, -1);
					sem_ok = false;
				}
				break;
			}
			case LEX_EQUAL:
			{
				bool skip = false;
				IT::IDDATATYPE mtype = tables.idtable.table[tables.lextable.table[i - 1].idxTI].iddatatype;
				for (int j = i; tables.lextable.table[j].lexema != LEX_SEMICOLON; j++)
				{
					if (tables.lextable.table[j].lexema == LEX_LEFTTHESIS)
						while (tables.lextable.table[j].lexema != LEX_RIGHTTHESIS)
						{
							j++;
						}
					if ((tables.lextable.table[j].lexema == LEX_ID || tables.lextable.table[j].lexema == LEX_LITERAL))
					{
						if (mtype != tables.idtable.table[tables.lextable.table[j].idxTI].iddatatype)
						{
							sem_ok = false;
							throw ERROR_THROW_IN(314, tables.lextable.table[i].sn, -1);
						}
					}
				}
				break;
			}
			case LEX_DIRSLASH:
			{
				if (tables.idtable.table[tables.lextable.table[i + 1].idxTI].value.vint == 0)
				{
					sem_ok = false;
					throw ERROR_THROW_IN(318, tables.lextable.table[i].sn, -1);
				}
				break;
			}
			}
		}

		return sem_ok;
	}
};
