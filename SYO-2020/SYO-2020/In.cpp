#include "stdafx.h"
#include "In.h"
#include "Error.h"
#include "Parm.h"

using namespace std;


namespace In
{
	IN getin(Parm::PARM parm)
	{
		IN in;
		in.size = 0;
		in.lines = 0;
		in.ignor = 0;

		int col = 0;
		bool litIgnore = false;
		char* text = new char[IN_MAX_LEN_TEXT];

		ifstream flin(parm.in);
		if (flin.fail())
			throw ERROR_THROW(110);

		int lines = 0;

		while (in.size < IN_MAX_LEN_TEXT)
		{
			char c;	
			flin.get(c);
			unsigned char u = c;
			if (u == '\'')
				litIgnore = !litIgnore;
			if (litIgnore)
			{
				switch (in.code[u])
				{
				case in.SPC:
				{
					text[in.size] = u;
					in.size++;
					col++;
				}break;
				case in.T:
				{
					text[in.size] = u;
					in.size++;
					col++;
				} break;
				case in.F:
				{
					throw ERROR_THROW_IN(111, in.lines, col);
				}break;
				case in.I: {
					in.ignor++;
				} break;
				}
			}
			if (flin.eof())
			{
				text[in.size] = IN_CODE_ENDS;
				in.lines++;
				break;
			}
			if (!litIgnore) {
				switch (in.code[u])
				{
				case in.S: {
					if (in.code[text[in.size - 1]] != in.S)
					{
						text[in.size] = IN_CODE_SEP;
						in.size++;
						in.lines++;
						col = 0;
					}
				} break;
				case in.T: {
					text[in.size] = u;
					in.size++;
					col++;
				} break;
				case in.LX: {
					if (in.code[text[in.size - 1]] == in.SPC)
					{
						text[in.size - 1] = u;
					}
					else
					{
						text[in.size] = u;
						in.size++;
					}
					col++;
				} break;
				case in.SPC: {
					if (in.code[text[in.size - 1]] != in.LX && in.code[text[in.size - 1]] != in.SPC)
					{
						text[in.size] = u;
						in.size++;
					}
					col++;
				} break;
				case in.I: {
					in.ignor++;
				} break;
				case in.F: {
					throw ERROR_THROW_IN(111, in.lines, col);
				} break;
				default: {
					text[in.size] = in.code[u];
					in.size++;
					col++;
				}
				}
			}
		}
		flin.close();
		in.text = text;

		return in;
	}
}