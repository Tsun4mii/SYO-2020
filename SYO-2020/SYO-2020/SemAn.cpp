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
				if (tables.lextable.table[i + 1].lexema != LEX_NUMBER)
				{
					sem_ok = false;
					throw ERROR_THROW_IN(303, tables.lextable.table[i].sn, 0);
				}
			}
			case LEX_DIRSLASH:
			{
				int k = i;
				if (tables.lextable.table[i + 1].lexema == LEX_ID)
				{
					for (k; k > 0; k--)
					{
						if (tables.lextable.table[k].lexema == LEX_ID)
						{
							if (tables.idtable.table[tables.lextable.table[k].idxTI].id == tables.idtable.table[tables.lextable.table[i + 1].idxTI].id)
							{
								if (tables.lextable.table[k + 2].lexema == LEX_LITERAL && tables.idtable.table[tables.lextable.table[k + 2].idxTI].value.vint == 0)
								{
									sem_ok = false;
									throw ERROR_THROW_IN(318, tables.lextable.table[k].sn, 0);
								}
							}
						}
					}
				}
				if (tables.lextable.table[i + 1].lexema == LEX_LITERAL)
				{
					if (tables.idtable.table[tables.lextable.table[i + 1].idxTI].value.vint == 0)
					{
						sem_ok = false;
						throw ERROR_THROW_IN(318, tables.lextable.table[k].sn, 0);
					}
				}
				break;
			}
			case LEX_EQUAL: // ���������
			{
				if (i > 0 && tables.lextable.table[i - 1].idxTI != LT_TI_NULLIDX) // ����� �������
				{
					IT::IDDATATYPE lefttype = tables.idtable.table[tables.lextable.table[i - 1].idxTI].iddatatype;
					bool ignore = false;

					for (int k = i + 1; tables.lextable.table[k].lexema != LEX_SEMICOLON; k++)
					{
						if (k == tables.lextable.size)
							break; // ������� ������ - ��� ;
						if (tables.lextable.table[k].idxTI != LT_TI_NULLIDX) // ���� �� - ��������� ���������� �����
						{
							if (!ignore)
							{
								IT::IDDATATYPE righttype = tables.idtable.table[tables.lextable.table[k].idxTI].iddatatype;
								if (lefttype != righttype) // ���� ������ � ��������� �� ���������
								{
									throw ERROR_THROW_IN(314, tables.lextable.table[k].sn, 0);
									sem_ok = false;
									break;
								}
							}
							// ���� ������� ����� ����� ������� ������ - ��� ����� �������
							if (tables.lextable.table[k + 1].lexema == LEX_LEFTTHESIS)
							{
								ignore = true;
								continue;
							}
							// ����������� ������ ����� ������ ����������
							if (ignore && tables.lextable.table[k + 1].lexema == LEX_RIGHTTHESIS)
							{
								ignore = false;
								continue;
							}
						}
						if (lefttype == IT::IDDATATYPE::STR) // ������ ������ �������, �� ��� ����� ��������� �-���
						{
							char l = tables.lextable.table[k].lexema;
							if (l == LEX_PLUS || l == LEX_MINUS || l == LEX_STAR) // ��������� �����������
							{
								throw ERROR_THROW_IN(316, tables.lextable.table[k].sn, 0);
								sem_ok = false;
								break;
							}
						}
					}
				}
				break;
			}
			case LEX_ID: // �������� ���� ������������� ��������  
			{
				IT::Entry e = tables.idtable.table[tables.lextable.table[i].idxTI];

				if (i > 0 && tables.lextable.table[i - 1].lexema == LEX_FUNCTION)
				{
					if (e.idtype == IT::IDTYPE::F) //�������, �� ���������
					{
						for (int k = i + 1; ; k++)
						{
							char l = tables.lextable.table[k].lexema;
							if (l == LEX_RETURN)
							{
								int next = tables.lextable.table[k + 1].idxTI; // ����. �� return
								if (next != LT_TI_NULLIDX)
								{
									// ��� ������� � ������������� �������� �� ���������
									if (tables.idtable.table[next].iddatatype != e.iddatatype)
									{
										throw ERROR_THROW_IN(315, tables.lextable.table[k].sn, 0);
										sem_ok = false;
										break;
									}
								}
								break; // ����� exit
							}

							if (k == tables.lextable.size) break;
						}
					}
				}
				break;
			}
			case LEX_MORE:	case LEX_LESS: case LEX_NOT: case LEX_MREQUAL: case LEX_LSEQUAL:
			{
				// ����� � ������ ������� - �������� ���
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
					// ������ ��� ����������� �� � �������
					throw ERROR_THROW_IN(317, tables.lextable.table[i].sn, 0);
					sem_ok = false;
				}
				break;
			}
			}
		}

		return sem_ok;
	}
};
