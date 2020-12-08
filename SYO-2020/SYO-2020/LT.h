#pragma once
#include "Error.h"
#include "Parm.h"
#define LEXEMA_FIXSIZE	1			// ������������� ������ �������
#define LT_MAXSIZE		4096		// ������������ ���������� ����� � ������� ������
#define LT_TI_NULLIDX	0xfffffff	// ��� �������� ������� ���������������
#define LEX_NUMBER		't'	// ������� ��� integer
#define LEX_STRING		't'	// ������� ��� string
#define LEX_TYPE		't'
#define LEX_ID			'i'	// ������� ��� ��������������
#define LEX_LITERAL		'l'	// ������� ��� ��������
#define LEX_FUNCTION	'f'	// ������� ��� function
#define LEX_NEW			'n'	// ������� ��� new
#define LEX_RETURN		'r'	// ������� ��� return
#define LEX_PRINT		'p'	// ������� ��� print
#define LEX_MAIN		'm'	// ������� ��� main
#define LEX_SEMICOLON	';'	// ������� ��� ;
#define LEX_COMMA		','	// ������� ��� ,
#define LEX_LEFTBRACE	'['	// ������� ��� {
#define LEX_BRACELET	']'	// ������� ��� }
#define LEX_LEFTTHESIS	'('	// ������� ��� (
#define LEX_RIGHTTHESIS	')'	// ������� ��� )
#define LEX_PLUS		'+'	// ������� ��� +		�������� ����� ��� ����. ���������� + - * /
#define LEX_MINUS		'-'	// ������� ��� -
#define LEX_STAR		'*'	// ������� ��� *
#define LEX_DIRSLASH	'/'	// ������� ��� /
#define LEX_OPERATOR	'v'	// ������� ��� ����������
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
		char lexema;                                          //�������
		int sn;                                               //����� ������ � �������� ������
		int idxTI;  
		int priority;//������ � ��
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