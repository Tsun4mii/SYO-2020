#include "stdafx.h"
#include "Error.h"
#include "Parm.h"
#include "Log.h"
#include "In.h"
//#include "Print.h"
#include "LT.h"
#include "LexAn.h"
//#include "Polish.h"
#include "MFST.h"
#include "Greibach.h"
#include "Polish.h"
#include "SemAn.h"
#include"Generator.h"

#define EXP1 16


int wmain(int argc, wchar_t* argv[])
{
	setlocale(LC_ALL, "ru");
	Log::LOG	log = Log::INITLOG;
	try
	{
		Parm::PARM parm = Parm::getparm(argc, argv);
		log = Log::getlog(parm.log);
		Log::WriteLine(log, "Тест: ", "без ошибок ", "");
		Log::WriteLog(log);
		Log::WriteParm(log, parm);
		In::IN in = In::getin(parm);
		Log:WriteIn(log, in);
		Lex::LEX lex = Lex::lexAnaliz(log, in);
		MFST_TRACE_START
		unsigned int start_time = clock();
		MFST::Mfst mfst(lex.lextable, GRB::getGreibach());
		mfst.start();
		unsigned int end_time = clock();
		unsigned int search_time = end_time - start_time;
		std::cout << search_time << std::endl;
		mfst.savededucation();
		mfst.printrules();
		bool sem_ok = Semantic::semanticsCheck(lex, log);
		if (!sem_ok)
		{
			std::cout << "Ошибка семантического анализа" << std::endl;
		}
		IT::showTable(lex.idtable);
		PolishStart(lex);
		LT::showTable(lex.lextable, parm);
		for (int i = 0; i < lex.idtable.size; i++)
		{
				std::cout << lex.idtable.table[i].countOfPar;
		}
		Gen::CodeGeneration(lex);
		Log::Close(log);
	}
	catch (Error::ERROR e)
	{
		Log::WriteError(log, e);
	}
	system("pause");
	return 0;

}