#include "Generator.h"
#include "Parm.h"
#include "LexAn.h"
#include "IT.h"
#include "LT.h"
#include <vector>
#include <sstream>
#include <iostream>
#include <stack>
using namespace std;

static int conditionnum = 0;
string itoS(int x) { stringstream r;  r << x;  return r.str(); }
string genCallFunctionCode(Lex::LEX& tables, int i)
{
	/*string str;

	IT::Entry e = ITENTRY(i);
	stack<IT::Entry> temp;
	bool stnd = (e.idtype == IT::IDTYPE::SF);

	for (int k = i - j; k < i; k++)
	{
		if (LEXEMA(k) == LEX_ID || LEXEMA(k) == LEX_LITERAL)
			temp.push(ITENTRY(k));
	}

	while (!temp.empty())
	{
		if (temp.top().idtype == IT::IDTYPE::L && temp.top().iddatatype == IT::IDDATATYPE::STR)
			str = str + "push offset " + temp.top().id + "\n";
		else   str = str + "push " + temp.top().id + "\n";
		temp.pop();
	}
	if (stnd)
		str += "push offset buffer\n";
	str = str + "call " + string(e.id) + IN_CODE_ENDL;
	return str;*/
	string str;

	IT::Entry e = ITENTRY(i); // ������������� ���������� �������
	stack <IT::Entry> temp;
	bool stnd = (e.idtype == IT::IDTYPE::SF);

	for (int j = i + 1; LEXEMA(j) != (LEX_RIGHTTHESIS); j++)
	{
		if (LEXEMA(j) == LEX_ID || LEXEMA(j) == LEX_LITERAL)
			temp.push(ITENTRY(j)); // // ��������� ���� � ������ �������	
	}
	str += "\n";

	// ������������ ����
	while (!temp.empty())
	{
		if (temp.top().idtype == IT::IDTYPE::L && temp.top().iddatatype == IT::IDDATATYPE::STR)
			str = str + "push offset " + temp.top().id + "\n";
		else   str = str + "push " + temp.top().id + "\n";
		temp.pop();
	}

	/*if (stnd)
		str += "push offset buffer\n";*/
	str = str + "call " + string(e.id) + IN_CODE_ENDL;
	// �����������e �����
	/*if (e.value.params.count != 0) str = str + "add esp, " + itoS(4 * e.value.params.count + 4) + "\n";*/

	return str;
}
string genConditionCode(Lex::LEX& tables, int i, string& cyclecode)
{
	string str;
	conditionnum++;
	cyclecode.clear();
	IT::Entry lft = ITENTRY(i + 1); // ����� �������
	IT::Entry rgt = ITENTRY(i + 3); // ������ �������
	bool w = false, r = false, c = false;
	string wstr, rstr;

	for (int j = i + 5; LEXEMA(j) != LEX_LOGSEP; j++) // ���������� ����������� �������
	{
		if (LEXEMA(j) == LEX_TSTATE) r = true;
		if (LEXEMA(j) == LEX_FSTATE) w = true;
		if (LEXEMA(j) == LEX_REPEAT) c = true;
	}
	str = str + "mov edx, " + lft.id + "\ncmp edx, " + rgt.id + "\n";
	switch (LEXEMA(i + 2))
	{
	case LEX_MORE:  rstr = "jg";  wstr = "jl";  break;
	case LEX_LESS:   rstr = "jl";  wstr = "jg";  break;
	case LEX_NOT:   rstr = "jnz";  wstr = "jz";  break;
	case LEX_IFEQ:    rstr = "jz";  wstr = "jnz";  break;
	}

	if (!c && r) str = str + "\n" + rstr + " right" + itoS(conditionnum);
	if (!c && w) str = str + "\n" + wstr + " wrong" + itoS(conditionnum);
	if (c)
	{
		str = str + "\n" + rstr + " cycle" + itoS(conditionnum);
		cyclecode = str;
		str = str + "\njmp cyclenext" + itoS(conditionnum);
	}
	else if (!r || !w)  str = str + "\njmp next" + itoS(conditionnum);
	return str;
}
vector <string> startFillVector(Lex::LEX& tables)
{
	vector<string> v;
	v.push_back(BEGIN);									//������ ������� ��� ������������� ����������� ���������� (� ������ ������ ���������)
	string str = __FILE__;
	string str2 = str.erase(str.length() - 22, 22);
	string str3 = "Generation\\Debug\\GenLib.lib";
	str2.append(str3);
	string str4 = "includelib \"" + str2;
	v.push_back(str4);
	v.push_back(EXTERN);

	vector<string> vlt; vlt.push_back(CONST);
	vector<string> vid; vid.push_back(DATA);

	for (int i = 0; i < tables.idtable.size; i++)				//���������� ��������� 
	{
		IT::Entry e = tables.idtable.table[i];
		string str = "\t\t" + string(e.id);

		if (tables.idtable.table[i].idtype == IT::IDTYPE::L)
		{
			switch (e.iddatatype)
			{
			case IT::IDDATATYPE::INT:  str = str + " sdword " + itoS(e.value.vint);  break;
			case IT::IDDATATYPE::STR:  str = str + " byte '" + string(e.value.vstr.str) + "', 0";  break;
			}
			vlt.push_back(str);
		}
		else if (tables.idtable.table[i].idtype == IT::IDTYPE::V)
		{
			switch (e.iddatatype)
			{
			case IT::IDDATATYPE::INT: str = str + " sdword 0";  break;				//���� ��������
			case IT::IDDATATYPE::STR: str = str + " dword ?";  break;				//���� ������
			}
			vid.push_back(str);
		}
	}
	v.insert(v.end(), vlt.begin(), vlt.end());
	v.insert(v.end(), vid.begin(), vid.end());
	v.push_back(CODE);
	return v;
}
string genFunctionCode(Lex::LEX& tables, int i, string funcname, int pcount)
{
	string str;
	IT::Entry e = ITENTRY(i + 1);
	IT::IDDATATYPE type = e.iddatatype;

	str = SEPSTR(funcname) + string(e.id) + string(" PROC,\n\t");
	//������ ���������
	int j = i + 3; // ������ - �� ��� ����� ����� ����������� ������
	while (LEXEMA(j) != LEX_RIGHTTHESIS) // ���� ��������� �� ��������
	{
		if (LEXEMA(j) == LEX_ID) // ��������
			str = str + string(ITENTRY(j).id) + (ITENTRY(j).iddatatype == IT::IDDATATYPE::INT ? " : sdword, " : " : dword, ");
		j++;
	}
	int f = str.rfind(',');
	if (f > 0)
		str[f] = IN_CODE_SPACE;

	str += "\n; --- save registers ---\npush ebx\npush edx\n; ----------------------";

	return str;
}
string genExitCode(Lex::LEX& tables, int i, string funcname, int pcount)		//��������� ���� ������
{
	string str = "; --- restore registers ---\npop edx\npop ebx\n; -------------------------\n";
	if (LEXEMA(i + 1) != LEX_SEMICOLON)	// ����� �� ������� (������� ��������)
	{
		str = str + "mov eax, " + string(ITENTRY(i + 1).id) + "\n";
	}
	str += "ret\n";
	str += funcname + " ENDP" + SEPSTREMP;
	return str;
}

string genEqualCode(Lex::LEX& tables, int i)
{
	string str;
	IT::Entry e1 = ITENTRY(i - 1); // ����� �������

	switch (e1.iddatatype)
	{
	case IT::IDDATATYPE::INT:
	{
		bool first = true;
		for (int j = i + 1; LEXEMA(j) != LEX_SEMICOLON; j++)
		{
			switch (LEXEMA(j))
			{
			case LEX_LITERAL:
			case LEX_ID:
			{
				if (ITENTRY(j).idtype == IT::IDTYPE::F || ITENTRY(j).idtype == IT::IDTYPE::SF) // ���� � ��������� ����� �������
				{
					str = str + genCallFunctionCode(tables, j); // ������� ���������� ��������� � eax
					str = str + "push eax\n";				// ��������� ��������� � ���� ��� ����������� ���������� ���������
					while (LEXEMA(j) != LEX_RIGHTTHESIS) j++;
					break;
				}
				else  str = str + "push " + ITENTRY(j).id + "\n";
				break;
			}
			case LEX_PLUS:
				str = str + "pop ebx\npop eax\nadd eax, ebx\npush eax\n"; break;
			case LEX_MINUS:
				str = str + "pop ebx\npop eax\nsub eax, ebx\npush eax\n"; break;
			case LEX_STAR:
				str = str + "pop ebx\npop eax\nimul eax, ebx\npush eax\n"; break;
			case LEX_DIRSLASH:
				str = str + "pop ebx\npop eax\ncdq\nidiv ebx\npush eax\n"; break;
			}
		} // ���� ����������

		str = str + "\npop ebx\nmov " + e1.id + ", ebx\n";			// ����������� ��������� � ebx 
		break;
	}
	case IT::IDDATATYPE::STR:// ��������� ����������� ������� ������ ������, �������� � ������ �������
	{
		char lex = LEXEMA(i + 1);
		IT::Entry e2 = ITENTRY(i + 1);
		if (lex == LEX_ID && e2.idtype == IT::IDTYPE::F) // ����� �������
		{
			/*str += genCallFuncCode(tables, log, i + 1);*/
			str = str + "mov " + e1.id + ", eax";
		}
		else if (lex == LEX_LITERAL) // �������
		{
			str = str + "mov " + e1.id + ", offset " + e2.id;
		}
		else // ��(����������) - ����� �������
		{
			str = str + "mov ecx, " + e2.id + "\nmov " + e1.id + ", ecx";
		}
	}
	}

	return str;
}
namespace Gen
{
	void CodeGeneration(Lex::LEX& tables)
	{
		vector<string> v = startFillVector(tables);
		ofstream ofile("D:\\User\\Desktop\\CourseWork\\SYO-2020\\Generation\\Generation\\Gen.asm");
		string funcname;	// ��� ������� �������
		string cyclecode;	// ������ �����: cmp + j
		int pcount;			// ���������� ���������� ������� �������
		int pos, parcol;
		string str;
		for (int i = 0; i < tables.lextable.size; i++)
		{
			switch (LEXEMA(i))
			{
			case LEX_MAIN:
			{
				str = str + SEPSTR("MAIN") + "main PROC";
				break;
			}
			case LEX_FUNCTION:
			{
				funcname = ITENTRY(i + 1).id;
				pcount = 2;
				str = genFunctionCode(tables, i, funcname, pcount);
				break;
			}
			case LEX_RETURN:
			{
				pcount = 2;
				str = genExitCode(tables, i, funcname, pcount);
				break;
			}
			case LEX_EQUAL: // ������������ (���������� ���������)
			{
				str = genEqualCode(tables, i);
				while (LEXEMA(++i) != LEX_SEMICOLON);	// ���������� ���������
				break;
			}
			case LEX_STATE: // �������
			{
				str = genConditionCode(tables, i, cyclecode);
				break;
			}
			case LEX_BRACELET:	// ������� �� ����� � ����� ��������
			{
				if (LEXEMA(i + 1) == LEX_TSTATE || LEXEMA(i + 1) == LEX_FSTATE)
					str = str + "jmp next" + itoS(conditionnum);
			}
			case LEX_LOGSEP:		// ����� � ����� ������ ��� ����� 
			{
				if (LEXEMA(i - 1) == LEX_BRACELET) //   ]#
				{
					bool c = false;
					for (int j = i; j > 0 && LEXEMA(j) != LEX_STATE; j--)
						if (LEXEMA(j) == LEX_REPEAT)
							c = true;
					if (c)
						str = cyclecode + "\ncyclenext" + itoS(conditionnum) + ":";
					else  str += "next" + itoS(conditionnum) + ':';
				}
				break;
			}
			case LEX_TSTATE: // ������� �����(�����)
			{
				str = str + "right" + itoS(conditionnum) + ":";
				break;
			}
			case LEX_FSTATE: // ������� �������(�����)
			{
				str = str + "wrong" + itoS(conditionnum) + ":";
				break;
			}
			case LEX_PRINTLINE:
			{
				str = str + "push offset printline\ncall outstr\n";
				break;
			}
			case LEX_PRINT: // �����
			{
				IT::Entry e = ITENTRY(i + 1);
				switch (e.iddatatype)
				{
				case IT::IDDATATYPE::INT:
					str = str + "\npush " + e.id + "\ncall outnum\n";
					break;
				case IT::IDDATATYPE::STR:
					if (e.idtype == IT::IDTYPE::L)  str = str + "\npush offset " + e.id + "\ncall outstr\n";
					else  str = str + "\npush " + e.id + "\ncall outstr\n";
					break;
				}
				str = str + "\n";
				break;
			}
			case LEX_REPEAT: // ���� � �������� (�����)
			{
				str = str + "cycle" + itoS(conditionnum) + ":";
				break;
			}
			case LEX_ID:
			{
				if (LEXEMA(i + 1) == LEX_LEFTTHESIS && LEXEMA(i - 1) != LEX_FUNCTION) // �� ����������, � �����
					str = genCallFunctionCode(tables, i);
				break;
			}
			}
			if (!str.empty())
				v.push_back(str);
			str.clear();
		}
		v.push_back(END);
		for (auto x : v)
			ofile << x << endl;
	}
}

