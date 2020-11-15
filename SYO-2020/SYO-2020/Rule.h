#pragma once
#include "Greibach.h"
#define GRB_ERROR_SERIES 600
#define NS(n)	GRB::Rule::Chain::N(n)
#define TS(n)	GRB::Rule::Chain::T(n)
#define ISNS(n)	GRB::Rule::Chain::isN(n)

namespace GRB
{
	//Greibach greibach(
	//	NS('S'), TS('$'),                     // ��������� ������, ��� �����
	//	6,									  // ���������� ������
	//	Rule(
	//		NS('S'), GRB_ERROR_SERIES + 0,    // �������� ��������� ���������
	//		4,                                // 
	//		Rule::Chain(8, TS('m'), TS('['), NS('N'), TS('r'), NS('E'), TS(';'), TS(']'), TS(';')),
	//		Rule::Chain(14, TS('t'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS('['), NS('N'), TS('r'), NS('E'), TS(';'), TS(']'), TS(';'), NS('S')),
	//		Rule::Chain(13, TS('t'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS('['), NS('N'), TS('r'), NS('E'), TS(';'), TS(']'), TS(';')),
	//		Rule::Chain(9, TS('m'), TS('['), NS('N'), TS('r'), NS('E'), TS(';'), TS(']'), TS(';'), NS('S'))
	//	),
	//	Rule(
	//		NS('N'), GRB_ERROR_SERIES + 1,    // ����������� � ��������
	//		13,                               // 
	//		Rule::Chain(5, TS('n'), TS('t'), TS('i'), TS(';'), NS('N')),
	//		Rule::Chain(4, TS('i'), TS('='), NS('E'), TS(';')),
	//		Rule::Chain(5, TS('i'), TS('='), NS('E'), TS(';'), NS('N')),
	//		Rule::Chain(9, TS('n'), TS('t'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS(';'), NS('N')),
	//		Rule::Chain(4, TS('p'), TS('i'), TS(';'), NS('N')),
	//		Rule::Chain(4, TS('p'), TS('l'), TS(';'), NS('N')),
	//		Rule::Chain(4, TS('p'), NS('E'), TS(';'), NS('N')),
	//		Rule::Chain(3, TS('p'), NS('E'), TS(';')),
	//		Rule::Chain(4, TS('n'), TS('t'), TS('i'), TS(';')),
	//		Rule::Chain(6, TS('n'), TS('t'), TS('i'), TS('='), TS('l'), TS(';')),
	//		Rule::Chain(8, TS('n'), TS('t'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS(';')),
	//		Rule::Chain(3, TS('p'), TS('i'), TS(';')),
	//		Rule::Chain(3, TS('p'), TS('l'), TS(';'))
	//	),
	//	Rule(
	//		NS('E'), GRB_ERROR_SERIES + 2,    // ������ � ���������
	//		8,                                // 
	//		Rule::Chain(4, TS('i'), TS('('), NS('W'), TS(')')),
	//		Rule::Chain(1, TS('i')),
	//		Rule::Chain(1, TS('l')),
	//		Rule::Chain(3, TS('('), NS('E'), TS(')')),
	//		Rule::Chain(2, TS('i'), NS('M')),
	//		Rule::Chain(2, TS('l'), NS('M')),
	//		Rule::Chain(4, TS('('), NS('E'), TS(')'), NS('M')),
	//		Rule::Chain(5, TS('i'), TS('('), NS('W'), TS(')'), NS('M'))
	//	),
	//	Rule(
	//		NS('F'), GRB_ERROR_SERIES + 3,    // ������ � ���������� �������
	//		2,                                // 
	//		Rule::Chain(2, TS('t'), TS('i')),
	//		Rule::Chain(4, TS('t'), TS('i'), TS(','), NS('F'))
	//	),
	//	Rule(
	//		NS('W'), GRB_ERROR_SERIES + 4,    // ������ � ���������� ���������� ������� 
	//		4,                                // 
	//		Rule::Chain(1, TS('i')),
	//		Rule::Chain(1, TS('l')),
	//		Rule::Chain(3, TS('i'), TS(','), NS('W')),
	//		Rule::Chain(3, TS('l'), TS(','), NS('W'))
	//	)/*,*/
	//	//Rule(
	//	//	NS('M'), GRB_ERROR_SERIES + 5,    // ��������
	//	//	2,								  //
	//	//	Rule::Chain(2, TS('v'), NS('E')),
	//	//	Rule::Chain(3, TS('v'), NS('E'), NS('M'))
	//	//)
	//);
	Greibach greibach(NS('S'), TS('$'), 16,

		Rule(NS('S'), GRB_ERROR_SERIES, 3,						// �������� ��������� ���������	
			Rule::Chain(6, TS('t'), TS('f'), TS('i'), NS('P'), NS('T'), NS('S')),
			Rule::Chain(6, TS('p'), TS('f'), TS('i'), NS('P'), NS('G'), NS('S')),
			Rule::Chain(4, TS('m'), TS('['), NS('K'), TS(']'))
		),

		Rule(NS('T'), GRB_ERROR_SERIES + 2, 2,					// ������ � ���� �������
			Rule::Chain(5, TS('['), TS('r'), NS('V'), TS(';'), TS(']')),
			Rule::Chain(6, TS('['), NS('K'), TS('r'), NS('V'), TS(';'), TS(']'))
		),

		Rule(NS('G'), GRB_ERROR_SERIES + 3, 2,					// ������ � ���� ���������
			Rule::Chain(4, TS('['), TS('r'), TS(';'), TS(']')),
			Rule::Chain(5, TS('['), NS('K'), TS('r'), TS(';'), TS(']'))
		),

		Rule(NS('P'), GRB_ERROR_SERIES + 1, 2,					// �� ������ ������ ���������� �������	
			Rule::Chain(3, TS('('), NS('E'), TS(')')),
			Rule::Chain(2, TS('('), TS(')'))
		),

		Rule(NS('E'), GRB_ERROR_SERIES + 4, 2,					// ������ � ������ ���������� �������						
			Rule::Chain(4, TS('t'), TS('i'), TS(','), NS('E')),
			Rule::Chain(2, TS('t'), TS('i'))
		),

		Rule(NS('F'), GRB_ERROR_SERIES + 5, 2,					// ������ � ������ �������						
			Rule::Chain(3, TS('('), NS('N'), TS(')')),
			Rule::Chain(2, TS('('), TS(')'))
		),

		Rule(NS('N'), GRB_ERROR_SERIES + 6, 4,					// ������ � ������ ���������� �������		
			Rule::Chain(1, TS('i')),
			Rule::Chain(1, TS('l')),
			Rule::Chain(3, TS('i'), TS(','), NS('N')),
			Rule::Chain(3, TS('l'), TS(','), NS('N'))
		),

		Rule(NS('R'), GRB_ERROR_SERIES + 7, 5,					// ������ ��� �������������� �����/��������� ���������	
			Rule::Chain(3, TS('r'), NS('Y'), TS('#')),
			Rule::Chain(3, TS('w'), NS('Y'), TS('#')),
			Rule::Chain(3, TS('c'), NS('Y'), TS('#')),
			Rule::Chain(5, TS('r'), NS('Y'), TS('w'), NS('Y'), TS('#')),
			Rule::Chain(5, TS('w'), NS('Y'), TS('r'), NS('Y'), TS('#'))
		),

		Rule(NS('Y'), GRB_ERROR_SERIES + 8, 1,					// ������ � ���� �����/��������� ���������			
			Rule::Chain(3, TS('['), NS('X'), TS(']'))
		),

		Rule(NS('Z'), GRB_ERROR_SERIES + 9, 3,					// ������ � ������� �����/��������� ���������	
			Rule::Chain(3, TS('i'), NS('L'), TS('i')),
			Rule::Chain(3, TS('i'), NS('L'), TS('l')),
			Rule::Chain(3, TS('l'), NS('L'), TS('i'))
		),

		Rule(NS('L'), GRB_ERROR_SERIES + 10, 5,					// �������� �������� ��������		
			Rule::Chain(1, TS('<')),
			Rule::Chain(1, TS('>')),
			Rule::Chain(1, TS('!')),
			Rule::Chain(1, TS('}')),
			Rule::Chain(1, TS('{'))
		),

		Rule(NS('A'), GRB_ERROR_SERIES + 11, 4,					// �������� �������������� ��������
			Rule::Chain(1, TS('+')),
			Rule::Chain(1, TS('-')),
			Rule::Chain(1, TS('*')),
			Rule::Chain(1, TS('/'))
		),

		Rule(NS('V'), GRB_ERROR_SERIES + 12, 2,					// �������� ���������. ��������� ������ �������������� � ��������
			Rule::Chain(1, TS('l')),
			Rule::Chain(1, TS('i'))
		),

		Rule(NS('W'), GRB_ERROR_SERIES + 13, 8,					// ������ � ������������� ���������
			Rule::Chain(1, TS('i')),
			Rule::Chain(1, TS('l')),
			Rule::Chain(3, TS('('), NS('W'), TS(')')),
			Rule::Chain(5, TS('('), NS('W'), TS(')'), NS('A'), NS('W')),
			Rule::Chain(2, TS('i'), NS('F')),
			Rule::Chain(3, TS('i'), NS('A'), NS('W')),
			Rule::Chain(4, TS('i'), NS('F'), NS('A'), NS('W')),
			Rule::Chain(3, TS('l'), NS('A'), NS('W'))
		),

		Rule(NS('K'), GRB_ERROR_SERIES + 14, 14,				// ������������ �������������� �����������
			Rule::Chain(7, TS('n'), TS('t'), TS('i'), TS('='), NS('V'), TS(';'), NS('K')),	// ���������� + ������������
			Rule::Chain(4, TS('i'), TS('='), NS('W'), TS(';')),			// ������������
			Rule::Chain(5, TS('n'), TS('t'), TS('i'), TS(';'), NS('K')),	// ����������
			Rule::Chain(5, TS('i'), TS('='), NS('W'), TS(';'), NS('K')),	// ������������

			Rule::Chain(4, TS('p'), NS('V'), TS(';'), NS('K')),				// �����
			Rule::Chain(3, TS('^'), TS(';'), NS('K')),						// ������� ������
			Rule::Chain(5, TS('?'), NS('Z'), TS('#'), NS('R'), NS('K')),	// condition
			Rule::Chain(4, TS('i'), NS('F'), TS(';'), NS('K')),				// ����� �������

			Rule::Chain(6, TS('n'), TS('t'), TS('i'), TS('='), NS('V'), TS(';')),	// ���������� + ������������
			Rule::Chain(4, TS('n'), TS('t'), TS('i'), TS(';')),			// ����������
			Rule::Chain(3, TS('p'), NS('V'), TS(';')),					// �����
			Rule::Chain(2, TS('^'), TS(';')),							// ������� ������
			Rule::Chain(4, TS('?'), NS('Z'), TS('#'), NS('R')),			// condition
			Rule::Chain(3, TS('i'), NS('F'), TS(';'))					// ����� �������
		),

		Rule(NS('X'), GRB_ERROR_SERIES + 15, 8,				// ������������ �������������� ����������� � ���� �����/��������� ���������	
			Rule::Chain(5, TS('i'), TS('='), NS('W'), TS(';'), NS('X')),	// ������������
			Rule::Chain(4, TS('p'), NS('V'), TS(';'), NS('X')),				// �����
			Rule::Chain(3, TS('^'), TS(';'), NS('X')),						// ������� ������
			Rule::Chain(4, TS('i'), NS('F'), TS(';'), NS('X')),				// ����� �������

			Rule::Chain(4, TS('i'), TS('='), NS('W'), TS(';')),			// ������������
			Rule::Chain(3, TS('p'), NS('V'), TS(';')),					// �����
			Rule::Chain(2, TS('^'), TS(';')),							// ������� ������
			Rule::Chain(3, TS('i'), NS('F'), TS(';'))					// ����� �������
		)
	);
}