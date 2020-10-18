#include "stdafx.h"
#include "LexAn.h"
#include "Div.h"
#include "FST.h"
#include "Graphs.h"
#define DIV '|'
#define SPACE ' '
#define PLUS '+'
#define MINUS '-'
#define STAR '*'
#define DIRSLASH '/'
#define EQUAL '='

using namespace std;

int DecimalTrnsl(char* word)
{
	//string str = word;
	//string res = str.substr(1, str.size());
	//int buf = atoi(res.c_str());
	char* pEnd = 0;
	char buf[15];
	int i, j;
	for (i = 1, j = 0; i < strlen(word); i++, j++)
	{
		buf[j] = word[i];
	}
	buf[j + 1] = '\0';
	return strtol(buf, &pEnd, 8);
}

namespace Lex
{
	LEX lexAnaliz(Log::LOG log, In::IN in)
	{
		LEX lex;
		LT::LexTable lextable = LT::Create(LT_MAXSIZE);
		IT::IdTable idtable = IT::Create(TI_MAXSIZE);

		char** word = new char* [max_world];
		for (int i = 0; i < max_world; i++)
			word[i] = new char[size_world] {NULL};

		do {
			word = divideText(in.text, in.size);
		} while (word == NULL);


		//for (int i = 0; word[i] != NULL; i++)
		//{
		//	/*if (word[4][i] == '\0')
		//		break;
		//	else*/
		//		cout << word[i] << endl;
		//}

		int indxLex = 0;		// индекс лексемы
		int indexID = 0;		// индекс идент.
		int clit = 1;			// счетчик литералов
		int line = 1;			// номер строки
		int position = 0;			// номер позиции в исходном файле

		bool findMain = false;
		int countMain = 0;
		bool findDec = false;
		bool findType = false;
		int bufPos = 0;

		char emptystr[] = "";	// пустая строка
		char* prefix = new  char[10]{ "" };	// текущий префикс
		char* bufprefix = new  char[10]{ "" };	// буфер для префикса
		char* oldprefix = new  char[10]{ "" };	// предыдущий префикс
		char* L = new  char[2]{ "L" };
		char* bufL = new  char[TI_STR_MAXSIZE];
		char* nameLiteral = new  char[10]{ "" };
		char* charclit = new char[10]{ "" };		// для строковой записи счетчика

		bool findFunc = false;
		bool findParm = false;

		IT::Entry entryIT;

		for (int i = 0; word[i] != NULL; i++, indxLex++)
		{

			bool findSameID = false;

			FST::FST fstDeclare(word[i], FST_NEW);
			if (FST::execute(fstDeclare))
			{
				LT::Entry entryLT = writeEntry(entryLT, LEX_NEW, LT_TI_NULLIDX, line);
				LT::Add(lextable, entryLT);
				findDec = true;
				continue;
			}
			FST::FST fstCycle(word[i], FST_CYCLE);
			if (FST::execute(fstCycle))
			{
				LT::Entry entryLT = writeEntry(entryLT, LEX_CYCLE, LT_TI_NULLIDX, line);
				LT::Add(lextable, entryLT);
				continue;
			}
			FST::FST fstCondition(word[i], FST_CONDITION);
			if (FST::execute(fstCondition))
			{
				LT::Entry entryLT = writeEntry(entryLT, LEX_CONDITION, LT_TI_NULLIDX, line);
				LT::Add(lextable, entryLT);
				continue;
			}
			FST::FST fstLogSep(word[i], FST_LOGSEP);
			if (FST::execute(fstLogSep))
			{
				LT::Entry entryLT = writeEntry(entryLT, LEX_LOGSEP, LT_TI_NULLIDX, line);
				LT::Add(lextable, entryLT);
				continue;
			}

			FST::FST fstTypeInteger(word[i], FST_NUMBER);
			if (FST::execute(fstTypeInteger))
			{
				LT::Entry entryLT = writeEntry(entryLT, LEX_NUMBER, LT_TI_NULLIDX, line);
				LT::Add(lextable, entryLT);
				findType = true;
				entryIT.iddatatype = IT::INT;
				continue;
			}
			FST::FST fstTypeString(word[i], FST_STRING);
			if (FST::execute(fstTypeString))
			{
				LT::Entry entryLT = writeEntry(entryLT, LEX_STRING, LT_TI_NULLIDX, line);
				LT::Add(lextable, entryLT);
				findType = true;
				entryIT.iddatatype = IT::STR;
				strcpy(entryIT.value.vstr.str, emptystr);
				continue;
			}
			FST::FST fstTypeBool(word[i], FST_BOOL);
			if (FST::execute(fstTypeBool))
			{
				LT::Entry entryLT = writeEntry(entryLT, LEX_BOOL, LT_TI_NULLIDX, line);
				LT::Add(lextable, entryLT);
				findType = true;
				entryIT.iddatatype = IT::BL;
				strcpy(entryIT.value.vstr.str, emptystr);
				continue;
			}
			FST::FST fstFunction(word[i], FST_FUNCTION);
			if (FST::execute(fstFunction))
			{
				LT::Entry entryLT = writeEntry(entryLT, LEX_FUNCTION, LT_TI_NULLIDX, line);
				LT::Add(lextable, entryLT);
				entryIT.idtype = IT::F;
				findFunc = true;
				continue;
			}
			FST::FST fstReturn(word[i], FST_RETURN);
			if (FST::execute(fstReturn))
			{
				LT::Entry entryLT = writeEntry(entryLT, LEX_RETURN, LT_TI_NULLIDX, line);
				LT::Add(lextable, entryLT);
				continue;
			}
			FST::FST fstPrint(word[i], FST_PRINT);
			if (FST::execute(fstPrint))
			{
				LT::Entry entryLT = writeEntry(entryLT, LEX_PRINT, LT_TI_NULLIDX, line);
				LT::Add(lextable, entryLT);
				continue;
			}
			FST::FST fstMain(word[i], FST_MAIN);
			if (FST::execute(fstMain))
			{
				LT::Entry entryLT = writeEntry(entryLT, LEX_MAIN, LT_TI_NULLIDX, line);
				LT::Add(lextable, entryLT);
				strcpy(oldprefix, prefix);
				strcpy(prefix, word[i]);
				strcpy(entryIT.visibility, emptystr);
				findMain = true;
				countMain++;
				continue;
			}
			FST::FST fstIdentif(word[i], FST_ID);
			if (FST::execute(fstIdentif))
			{
				// поиск такого же
				if (findFunc)	// если функция
				{
					int idx = IT::IsId(idtable, word[i]);	// ищем без префикса
					if (idx != TI_NULLIDX)		// если такой идентификатор уже есть
					{
						LT::Entry entryLT = writeEntry(entryLT, LEX_ID, idx, line);
						LT::Add(lextable, entryLT);
						findFunc = false;
						continue;
					}
				}
			else
			{
				int idx = IT::IsId(idtable, word[i]);	// ищем без префикса, а потом с префиксом
				if (idx == TI_NULLIDX && findDec == true && findType == false)
					throw ERROR_THROW_IN(123, line, position);
				if (idx != TI_NULLIDX)		// если такой идентификатор уже есть
				{
					if (findDec == true)				//Проверка на повторное объявление
						throw ERROR_THROW_IN(122, line, position);
					LT::Entry entryLT = writeEntry(entryLT, LEX_ID, idx, line);
					LT::Add(lextable, entryLT);
					findFunc = false;
					continue;
				}
				strcpy(bufprefix, prefix);
				word[i] = strcat(bufprefix, word[i]);
				idx = IT::IsId(idtable, word[i]);
				if (idx != TI_NULLIDX)		// если такой идентификатор уже есть
				{
					if (findDec == true)				//Проверка на повторное объявление
						throw ERROR_THROW_IN(122, line, position);
				LT::Entry entryLT = writeEntry(entryLT, LEX_ID, idx, line);
				LT::Add(lextable, entryLT);
				continue;
				}
			}
			LT::Entry entryLT = writeEntry(entryLT, LEX_ID, indexID++, line);
			LT::Add(lextable, entryLT);
			findDec = false;
			if (findParm) {		// если параметр
			entryIT.idtype = IT::P;
			idtable.table[bufPos].countOfPar++;
			strcpy(entryIT.visibility, prefix);
			}
			else if (!findFunc) {	// если переменная
			entryIT.idtype = IT::V;
			strcpy(entryIT.visibility, prefix);
			if (entryIT.iddatatype == IT::INT)
				entryIT.value.vint = TI_INT_DEFAULT;
			if (entryIT.iddatatype == IT::STR) {
				entryIT.value.vstr.len = 0;
				memset(entryIT.value.vstr.str, TI_STR_DEFAULT, sizeof(char));
				}
			if (entryIT.iddatatype == IT::BL)
			{
				entryIT.value.vbool = 0;
			}
			}
			else {		// если функция
			strcpy(oldprefix, prefix);
			strcpy(prefix, word[i]);
			strcpy(entryIT.visibility, emptystr);
			}

			entryIT.idxfirstLE = indxLex;
			strcpy(entryIT.id, word[i]);
			IT::Add(idtable, entryIT);
			findFunc = false;
			findType = false;
			continue;
			}
			FST::FST fstLiteralInt(word[i], FST_INTLIT);
			if (FST::execute(fstLiteralInt))
			{
				int value = atoi((char*)word[i]);	// значение литерала
											// поиск такого же
				for (int k = 0; k < idtable.size; k++)
				{
					if (idtable.table[k].value.vint == value && idtable.table[k].idtype == IT::L)
					{
						LT::Entry entryLT = writeEntry(entryLT, LEX_LITERAL, k, line);
						LT::Add(lextable, entryLT);
						findSameID = true;
						break;
					}
				}
			if (findSameID)	// если был найден такой же
				continue;
			LT::Entry entryLT = writeEntry(entryLT, LEX_LITERAL, indexID++, line);
			LT::Add(lextable, entryLT);
			entryIT.idtype = IT::L;
			entryIT.iddatatype = IT::INT;
			entryIT.value.vint = value;
			entryIT.idxfirstLE = indxLex;
			// формирование имени литерала
			_itoa_s(clit++, charclit, sizeof(char) * 10, 10);	// преобразуем значение счетчика в строку(charclit)
			strcpy(bufL, L);	// помещаем в буфер "L"
			word[i] = strcat(bufL, (char*)charclit);	// формируем имя для литерала
			strcpy(entryIT.id, word[i]);
			IT::Add(idtable, entryIT);
			continue;
			}
			FST::FST fstLiteralq(word[i], FST_QLIT);
			if (FST::execute(fstLiteralq))
			{
				int value = DecimalTrnsl(word[i]);	// значение литерала
											// поиск такого же
				for (int k = 0; k < idtable.size; k++)
				{
					if (idtable.table[k].value.vint == value && idtable.table[k].idtype == IT::L)
					{
						LT::Entry entryLT = writeEntry(entryLT, LEX_LITERAL, k, line);
						LT::Add(lextable, entryLT);
						findSameID = true;
						break;
					}
				}
				if (findSameID)	// если был найден такой же
					continue;
				LT::Entry entryLT = writeEntry(entryLT, LEX_LITERAL, indexID++, line);
				LT::Add(lextable, entryLT);
				entryIT.idtype = IT::L;
				entryIT.iddatatype = IT::INT;
				entryIT.value.vint = value;
				entryIT.idxfirstLE = indxLex;
				// формирование имени литерала
				_itoa_s(clit++, charclit, sizeof(char) * 10, 10);	// преобразуем значение счетчика в строку(charclit)
				strcpy(bufL, L);	// помещаем в буфер "L"
				word[i] = strcat(bufL, (char*)charclit);	// формируем имя для литерала
				strcpy(entryIT.id, word[i]);
				IT::Add(idtable, entryIT);
				continue;
			}
			FST::FST fstLiteralString(word[i], FST_STRLIT);
			if (FST::execute(fstLiteralString))
			{
				// запись значения
				int length = strlen(word[i]);
				for (int k = 0; k < length; k++)	// перезапись массива, убираем кавычки
					word[i][k] = word[i][k + 1];
				word[i][length - 2] = 0;
				// поиск такого же
				for (int k = 0; k < idtable.size; k++)
				{
					if (!(strcmp(idtable.table[k].value.vstr.str, word[i])))
					{
						findSameID = true;
						LT::Entry entryLT = writeEntry(entryLT, LEX_LITERAL, k, line);
						LT::Add(lextable, entryLT);
						break;
					}
				}
				if (findSameID)	// если был найден такой же
					continue;
				LT::Entry entryLT = writeEntry(entryLT, LEX_LITERAL, indexID++, line);
				LT::Add(lextable, entryLT);
				strcpy(entryIT.value.vstr.str, word[i]);	// запись значиния строкового литерала
				entryIT.value.vstr.len = length - 2;		// запись длины строкового литерала
				entryIT.idtype = IT::L;
				entryIT.iddatatype = IT::STR;
				entryIT.idxfirstLE = indxLex;
				// формирование имени литерала
				_itoa_s(clit++, charclit, sizeof(char) * 10, 10);	// преобразуем значение счетчика в строку(charclit)
				strcpy(bufL, L);	// помещаем в буфер "L"
				nameLiteral = strcat(bufL, (char*)charclit);	// формируем имя для литерала (L + charclit)
				strcpy(entryIT.id, nameLiteral);
				IT::Add(idtable, entryIT);
				continue;
			}
			FST::FST fstOperator(word[i], FST_OPERATOR);
			if (FST::execute(fstOperator))
			{
				LT::Entry entryLT = writeEntry(entryLT, LEX_OPERATOR, indexID++, line);
				switch (word[i][0])
				{
				case PLUS: case MINUS:
					entryLT.priority = 2;
					break;
				case DIRSLASH: case STAR:
					entryLT.priority = 3;
					break;
				}
				LT::Add(lextable, entryLT);
				strcpy(entryIT.id, word[i]);
				entryIT.idxfirstLE = indxLex;
				entryIT.idtype = IT::OP;
				IT::Add(idtable, entryIT);
				continue;
			}
			FST::FST fstMrEqual(word[i], FST_MREQUAL);
			if (FST::execute(fstMrEqual))
			{
				LT::Entry entryLT = writeEntry(entryLT, LEX_MREQUAL, indexID++, line);
				LT::Add(lextable, entryLT);
				//strcpy(entryIT.id, word[i]);
				//entryIT.idxfirstLE = indxLex;
				//entryIT.idtype = IT::OP;
				//IT::Add(idtable, entryIT);
				continue;
			}
			FST::FST fstLsEqual(word[i], FST_LSEQUAL);
			if (FST::execute(fstLsEqual))
			{
				LT::Entry entryLT = writeEntry(entryLT, LEX_LSEQUAL, indexID++, line);
				LT::Add(lextable, entryLT);
				strcpy(entryIT.id, word[i]);
				entryIT.idxfirstLE = indxLex;
				entryIT.idtype = IT::OP;
				IT::Add(idtable, entryIT);
				continue;
			}
			FST::FST fstMore(word[i], FST_MORE);
			if (FST::execute(fstMore))
			{
				LT::Entry entryLT = writeEntry(entryLT, LEX_MORE, indexID++, line);
				LT::Add(lextable, entryLT);
				strcpy(entryIT.id, word[i]);
				entryIT.idxfirstLE = indxLex;
				entryIT.idtype = IT::OP;
				IT::Add(idtable, entryIT);
				continue;
			}
			FST::FST fstLess(word[i], FST_LESS);
			if (FST::execute(fstLess))
			{
				LT::Entry entryLT = writeEntry(entryLT, LEX_LESS, indexID++, line);
				LT::Add(lextable, entryLT);
				strcpy(entryIT.id, word[i]);
				entryIT.idxfirstLE = indxLex;
				entryIT.idtype = IT::OP;
				IT::Add(idtable, entryIT);
				continue;
			}
			FST::FST fstNotEqual(word[i], FST_NOT);
			if (FST::execute(fstNotEqual))
			{
				LT::Entry entryLT = writeEntry(entryLT, LEX_NOT, indexID++, line);
				LT::Add(lextable, entryLT);
				strcpy(entryIT.id, word[i]);
				entryIT.idxfirstLE = indxLex;
				entryIT.idtype = IT::OP;
				IT::Add(idtable, entryIT);
				continue;
			}
			FST::FST fstSemicolon(word[i], FST_SEMICOLON);
			if (FST::execute(fstSemicolon))
			{
				LT::Entry entryLT = writeEntry(entryLT, LEX_SEMICOLON, LT_TI_NULLIDX, line);
				LT::Add(lextable, entryLT);
				continue;
			}
			FST::FST fstComma(word[i], FST_COMMA);
			if (FST::execute(fstComma))
			{
				LT::Entry entryLT = writeEntry(entryLT, LEX_COMMA, LT_TI_NULLIDX, line);
				entryLT.priority = 1;
				LT::Add(lextable, entryLT);
				continue;
			}
			FST::FST fstLeftBrace(word[i], FST_LEFTBRACE);
			if (FST::execute(fstLeftBrace))
			{
				LT::Entry entryLT = writeEntry(entryLT, LEX_LEFTBRACE, LT_TI_NULLIDX, line);
				LT::Add(lextable, entryLT);
				continue;
			}
			FST::FST fstRightBrace(word[i], FST_BRACELET);
			if (FST::execute(fstRightBrace))
			{
				LT::Entry entryLT = writeEntry(entryLT, LEX_BRACELET, LT_TI_NULLIDX, line);
				LT::Add(lextable, entryLT);
				continue;
			}
			FST::FST fstLeftThesis(word[i], FST_LEFTTHESIS);
			if (FST::execute(fstLeftThesis))
			{
				LT::Entry entryLT = writeEntry(entryLT, LEX_LEFTTHESIS, LT_TI_NULLIDX, line);
				entryLT.priority = 0;
				LT::Add(lextable, entryLT);
				if (idtable.table[indexID - 1].idtype == IT::F)
					findParm = true;
				bufPos = indexID - 1;
				continue;
			}
			FST::FST fstRightThesis(word[i], FST_RIGHTTHESIS);
			if (FST::execute(fstRightThesis))
			{
				LT::Entry entryLT = writeEntry(entryLT, LEX_RIGHTTHESIS, LT_TI_NULLIDX, line);
				entryLT.priority = 0;
				if (findParm && word[i + 1][0] != LEX_LEFTBRACE && word[i + 2][0] != LEX_LEFTBRACE)		// если после функции нет {
					strcpy(prefix, oldprefix);		// возвращаем предыдущую обл. видимости
				findParm = false;
				LT::Add(lextable, entryLT);
				continue;
			}
			FST::FST fstEqual(word[i], FST_EQUAL);
			if (FST::execute(fstEqual))
			{
				LT::Entry entryLT = writeEntry(entryLT, LEX_EQUAL, LT_TI_NULLIDX, line);
				LT::Add(lextable, entryLT);
				continue;
			}
			position += strlen(word[i]);
			if (word[i][0] == DIV) {
				line++;
				position = 0;
				indxLex--;
				continue;
			}
			throw ERROR_THROW_IN(108, line, position);
		}
		if(!findMain) throw ERROR_THROW(2);
		if (countMain > 1) throw ERROR_THROW(3);
		cout << idtable.table[lextable.table[2].idxTI].countOfPar;
		lex.idtable = idtable;
		lex.lextable = lextable;
		return lex;
	}
}

	