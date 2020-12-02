#include "stdafx.h"
#include "LexAn.h"
#include <stack>
#include <queue>

using namespace std;

bool PolishNotation(int i, Lex::LEX& lex)
{
	stack<LT::Entry> stack;		// стек для операций
	queue<LT::Entry> queue;		// очередь для операндов
	LT::Entry temp;				// запрещенная лексема
	temp.idxTI = -1;
	temp.lexema = ' ';
	temp.sn = -1;
	LT::Entry func;
	func.lexema = '^';
	LT::Entry num;
	num.lexema = ' ';
	int countLex = 0;			// количество преобразованных лексем
	int posLex = i;				// запоминаем номер лексемы перед преобразованием
	bool findFunc = false;
	int buf = 0;

	for (i; lex.lextable.table[i].lexema != LEX_SEMICOLON; i++, countLex++)
	{
	//	switch (lex.lextable.table[i].lexema)
	//	{
	//	case LEX_ID:	// если идентификатор
	//	{
	//		if (findFunc)
	//			buf++;
	//		if (lex.idtable.table[lex.lextable.table[i].idxTI].idtype == IT::F || lex.idtable.table[lex.lextable.table[i].idxTI].idtype == IT::SF)
	//		{
	//			func.idxTI = lex.lextable.table[i].idxTI;
	//			func.priority = lex.lextable.table[i].priority;
	//			func.sn = lex.lextable.table[i].sn;
	//			continue;
	//		}
	//		queue.push(lex.lextable.table[i]);
	//		continue;
	//	}
	//	case LEX_LITERAL:		// если литерал
	//	{
	//		if (findFunc)
	//			buf++;
	//		queue.push(lex.lextable.table[i]);	//в очередь
	//		continue;
	//	}
	//	case LEX_LEFTTHESIS:		// если (
	//	{
	//		if (lex.idtable.table[lex.lextable.table[i - 1].idxTI].idtype == IT::F || lex.idtable.table[lex.lextable.table[i - 1].idxTI].idtype == IT::SF)
	//		{
	//			findFunc = true;
	//			/*num.lexema = (char)lex.idtable.table[lex.lextable.table[i - 1].idxTI].countOfPar + '0';*/
	//		}
	//		stack.push(lex.lextable.table[i]); //в стек
	//		continue;
	//	}
	//	case LEX_RIGHTTHESIS:	// если )
	//	{
	//		if (findFunc)
	//		{
	//			num.lexema = (char)buf + '0';
	//			stack.push(num);
	//			stack.push(func);
	//			findFunc = false;
	//			buf = 0;
	//		}
	//		while (stack.top().lexema != LEX_LEFTTHESIS)	// пока не встретим (
	//		{
	//			queue.push(stack.top());	//со стека в очередь
	//			stack.pop();
	//			if (stack.empty())
	//				return false;
	//		}
	//		stack.pop();	// уничтожаем (
	//		continue;
	//	}
	//	case LEX_PLUS: case LEX_MINUS: case LEX_STAR: case LEX_DIRSLASH:	// если знак оператора
	//	{
	//		while (!stack.empty() && lex.lextable.table[i].priority <= stack.top().priority)	// пока приоритет текущего оператора 
	//																							//меньше или равен приоритету оператора в вершине стека
	//		{
	//			queue.push(stack.top());	// выталкиваем со стека в выходную строку
	//			stack.pop();
	//		}
	//		stack.push(lex.lextable.table[i]);
	//		continue;
	//	}
	//	}
	//}
	//while (!stack.empty())	// если стек не пустой
	//{
	//	if (stack.top().lexema == LEX_LEFTTHESIS || stack.top().lexema == LEX_RIGHTTHESIS)
	//		return false;
	//	queue.push(stack.top());	// выталкиваем все в очередь
	//	stack.pop();
	//}
	//while (countLex != 0)		// замена текущего выражения в таблице лексем на выражение в ПОЛИЗ
	//{
	//	if (!queue.empty()) {
	//		lex.lextable.table[posLex++] = queue.front();
	//		queue.pop();
	//	}
	//	else
	//	{
	//		lex.lextable.table[posLex++] = temp;
	//	}
	//	countLex--;
	//}

	//for (int i = 0; i < posLex; i++)		// восстановление индексов первого вхождения в таблицу лексем у операторов из таблицы идентификаторов
	//{
	//	if (lex.lextable.table[i].lexema == LEX_PLUS || lex.lextable.table[i].lexema == LEX_MINUS || lex.lextable.table[i].lexema == LEX_STAR || lex.lextable.table[i].lexema == LEX_DIRSLASH || lex.lextable.table[i].lexema == LEX_LITERAL)
	//		lex.idtable.table[lex.lextable.table[i].idxTI].idxfirstLE = i;
	//}
	//return true;
		switch (lex.lextable.table[i].lexema)
		{
		case LEX_ID:	// если идентификатор
		{
			//if (lex.idtable.table[lex.lextable.table[i].idxTI].idtype == IT::F)
			//{
			//	stack.push(num);
			//	stack.push(func);
			//}
			queue.push(lex.lextable.table[i]);
			continue;
		}
		case LEX_LITERAL:		// если литерал
		{
			queue.push(lex.lextable.table[i]);	//в очередь
			continue;
		}
		case LEX_COMMA:
		{
			if (findFunc)
				stack.push(lex.lextable.table[i]);
		}
		case LEX_LEFTTHESIS:		// если (
		{
			if (lex.idtable.table[lex.lextable.table[i - 1].idxTI].idtype == IT::F || lex.idtable.table[lex.lextable.table[i - 1].idxTI].idtype == IT::SF)
			{
				findFunc = true;
				num.lexema = (char)lex.idtable.table[lex.lextable.table[i - 1].idxTI].countOfPar + '0';
			}
			if (findFunc)
				queue.push(lex.lextable.table[i]);
			else
				stack.push(lex.lextable.table[i]); //в стек
			continue;
		}
		case LEX_RIGHTTHESIS:	// если )
		{
			if (findFunc)
				queue.push(lex.lextable.table[i]);
			else {
				while (stack.top().lexema != LEX_LEFTTHESIS)	// пока не встретим (
				{
					queue.push(stack.top());	//со стека в очередь
					stack.pop();
					if (stack.empty())
						return false;
				}
				stack.pop();	// уничтожаем (
			}
			continue;
		}
		case LEX_PLUS: case LEX_MINUS: case LEX_STAR: case LEX_DIRSLASH:	// если знак оператора
		{
			while (!stack.empty() && lex.lextable.table[i].priority <= stack.top().priority)	// пока приоритет текущего оператора 
																								//меньше или равен приоритету оператора в вершине стека
			{
				queue.push(stack.top());	// выталкиваем со стека в выходную строку
				stack.pop();
			}
			stack.push(lex.lextable.table[i]);
			continue;
		}
		}
	}
	while (!stack.empty())	// если стек не пустой
	{
		if (stack.top().lexema == LEX_LEFTTHESIS || stack.top().lexema == LEX_RIGHTTHESIS)
			return false;
		queue.push(stack.top());	// выталкиваем все в очередь
		stack.pop();
	}
	while (countLex != 0)		// замена текущего выражения в таблице лексем на выражение в ПОЛИЗ
	{
		if (!queue.empty()) {
			lex.lextable.table[posLex++] = queue.front();
			queue.pop();
		}
		else
		{
			lex.lextable.table[posLex++] = temp;
		}
		countLex--;
	}

	for (int i = 0; i < posLex; i++)		// восстановление индексов первого вхождения в таблицу лексем у операторов из таблицы идентификаторов
	{
		if (lex.lextable.table[i].lexema == LEX_PLUS || lex.lextable.table[i].lexema == LEX_MINUS || lex.lextable.table[i].lexema == LEX_STAR || lex.lextable.table[i].lexema == LEX_DIRSLASH || lex.lextable.table[i].lexema == LEX_LITERAL)
			lex.idtable.table[lex.lextable.table[i].idxTI].idxfirstLE = i;
	}
	return true;
}
void PolishStart(Lex::LEX lex)
{
	for (int i = 0; i < lex.lextable.size; i++)
	{
		if (lex.lextable.table[i].lexema == '=')
		{
			PolishNotation(i + 1, lex);
		}
	}
}