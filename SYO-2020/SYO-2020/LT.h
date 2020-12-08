#pragma once
#include "Error.h"
#include "Parm.h"
#define LEXEMA_FIXSIZE	1			// фиксированный размер лексемы
#define LT_MAXSIZE		4096		// максимальное количество строк в таблице лексем
#define LT_TI_NULLIDX	0xfffffff	// нет элемента таблицы идентификаторов
#define LEX_NUMBER		't'	// лексема для integer
#define LEX_STRING		't'	// лексема для string
#define LEX_TYPE		't'
#define LEX_ID			'i'	// лексема для идентификатора
#define LEX_LITERAL		'l'	// лексема для литерала
#define LEX_FUNCTION	'f'	// лексема для function
#define LEX_NEW			'n'	// лексема для new
#define LEX_RETURN		'r'	// лексема для return
#define LEX_PRINT		'p'	// лексема для print
#define LEX_MAIN		'm'	// лексема для main
#define LEX_SEMICOLON	';'	// лексема для ;
#define LEX_COMMA		','	// лексема для ,
#define LEX_LEFTBRACE	'['	// лексема для {
#define LEX_BRACELET	']'	// лексема для }
#define LEX_LEFTTHESIS	'('	// лексема для (
#define LEX_RIGHTTHESIS	')'	// лексема для )
#define LEX_PLUS		'+'	// лексема для +		Изменены знаки для след. операторов + - * /
#define LEX_MINUS		'-'	// лексема для -
#define LEX_STAR		'*'	// лексема для *
#define LEX_DIRSLASH	'/'	// лексема для /
#define LEX_OPERATOR	'v'	// лексема для операторов
#define LEX_EQUAL		'='
#define LEX_REPEAT		'c'
#define LEX_STATE		'?'
#define LEX_LOGSEP		'#'
#define LEX_MREQUAL		'}'
#define LEX_LSEQUAL		'{'
#define LEX_MORE		'>'
#define LEX_LESS		'<'
#define LEX_NOT			'!'
#define LEX_BOOL		't'
#define LEX_PRINTLINE	'^'
#define LEX_IFEQ		'&'
#define LEX_TSTATE		'u'
#define LEX_FSTATE		'w'

namespace LT {
	struct Entry {
		char lexema;                                          //лексема
		int sn;                                               //номер строки в исходном тексте
		int idxTI;  
		int priority;//индекс в ТИ
	};
	struct LexTable
	{
		int maxsize;
		int size;
		Entry* table;
	};

	LexTable Create(int size);
	void Add(LexTable& lextable, Entry entry);
	Entry GetEntry(LexTable& lextable, int n);
	void Delete(LexTable& lextable);
	Entry writeEntry(Entry& entry, char lexema, int indx, int line);
	void showTable(LexTable lextable, /*Parm::PARM parm*/ std::ofstream* stream);
}