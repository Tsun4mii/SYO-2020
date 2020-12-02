#include "Error.h"

namespace Error
{
	ERROR error[ERROR_MAX_ENTRY] =
	{
		ERROR_ENTRY(0, "Недопустимый код ошибки"),		// код ошибки вне диапазона 0 - ERROR_MAX_ENTRY
		ERROR_ENTRY(1, "Системный сбой"),
		ERROR_ENTRY_NODEF(2), ERROR_ENTRY_NODEF(3), ERROR_ENTRY_NODEF(4), ERROR_ENTRY_NODEF(5),
		ERROR_ENTRY_NODEF(6), ERROR_ENTRY_NODEF(7), ERROR_ENTRY_NODEF(8), ERROR_ENTRY_NODEF(9),
		ERROR_ENTRY_NODEF10(10), ERROR_ENTRY_NODEF10(20), ERROR_ENTRY_NODEF10(30), ERROR_ENTRY_NODEF10(40), ERROR_ENTRY_NODEF10(50),
		ERROR_ENTRY_NODEF10(60), ERROR_ENTRY_NODEF10(70), ERROR_ENTRY_NODEF10(80), ERROR_ENTRY_NODEF10(90),
		ERROR_ENTRY(100, "Параметр -in должен быть задан"),
		ERROR_ENTRY_NODEF(101), ERROR_ENTRY_NODEF(102), ERROR_ENTRY_NODEF(103),
		ERROR_ENTRY(104, "Превышена длина входного параметра"),
		ERROR_ENTRY_NODEF(105), ERROR_ENTRY_NODEF(106), ERROR_ENTRY_NODEF(107),
		ERROR_ENTRY_NODEF(108), ERROR_ENTRY_NODEF(109),
		ERROR_ENTRY(110, "Ошибка при открытии файла с исходным кодом (-in)"),
		ERROR_ENTRY(111, "Недопустимый символ в исходном файле (-in)"),
		ERROR_ENTRY(112, "Ошибка при создании файла протокола (-log)"),
		ERROR_ENTRY_NODEF(113), ERROR_ENTRY_NODEF(114), ERROR_ENTRY_NODEF(115),
		ERROR_ENTRY_NODEF(116), ERROR_ENTRY_NODEF(117), ERROR_ENTRY_NODEF(118), ERROR_ENTRY_NODEF(119),
		ERROR_ENTRY(120, "Превышен максимльный размер таблицы лексем"),
		ERROR_ENTRY(121, "Таблица лексем переполнена"),
		ERROR_ENTRY_NODEF(122), ERROR_ENTRY_NODEF(123), ERROR_ENTRY_NODEF(124),
		ERROR_ENTRY_NODEF(125), ERROR_ENTRY_NODEF(126), ERROR_ENTRY_NODEF(127), ERROR_ENTRY_NODEF(128),
		ERROR_ENTRY_NODEF(129),  ERROR_ENTRY_NODEF10(130), ERROR_ENTRY_NODEF10(140), ERROR_ENTRY_NODEF10(150),
		ERROR_ENTRY(160, "Превышен максимльный размер таблицы идентификаторов"),
		ERROR_ENTRY(161, "Таблица идентификаторов переполнена"),
		ERROR_ENTRY(162, "Ошибка лексического анализа"), ERROR_ENTRY(163, ""), ERROR_ENTRY(164, ""),
		ERROR_ENTRY(165, "ОШИБКА"), ERROR_ENTRY(166, ""), ERROR_ENTRY(167, ""), ERROR_ENTRY(168, ""), ERROR_ENTRY(169, ""),
		ERROR_ENTRY_NODEF10(170), ERROR_ENTRY_NODEF10(180), ERROR_ENTRY_NODEF10(190),
		ERROR_ENTRY_NODEF100(200), ERROR_ENTRY(300, "[SEM]# Необъявленный идентификатор"),	//нет
		ERROR_ENTRY(301, "[SEM]# Отсутствует точка входа main"), //есть
		ERROR_ENTRY(302, "[SEM]# Обнаружено несколько точек входа main"),//есть
		ERROR_ENTRY(303, "[SEM]# В объявлении не указан тип идентификатора"),//есть
		ERROR_ENTRY(304, "[SEM]# В объявлении отсутствует ключевое слово new"),//есть
		ERROR_ENTRY(305, "[SEM]# Попытка переопределения идентификатора"),//есть
		ERROR_ENTRY(306, "[SEM]# Превышено максимальное количество параметров функции"), //нет
		ERROR_ENTRY(307, "[SEM]# Слишком много параметров в вызове"),	//нет
		ERROR_ENTRY(308, "[SEM]# Кол-во ожидаемыех функцией и передаваемых параметров не совпадают"),//есть
		ERROR_ENTRY(309, "[SEM]# Несовпадение типов передаваемых параметров"), //есть
		ERROR_ENTRY(310, "[SEM]# Использование пустого строкового литерала недопустимо"),	//нет
		ERROR_ENTRY(311, "[SEM]# Обнаружен символ \'. Возможно, не закрыт строковый литерал"),	//есть
		ERROR_ENTRY(312, "[SEM]# Превышен размер строкового литерала"),	//есть
		ERROR_ENTRY(313, "[SEM]# Недопустимый целочисленный литерал"),	//есть
		ERROR_ENTRY(314, "[SEM]# Типы данных в выражении не совпадают"),	//есть
		ERROR_ENTRY(315, "[SEM]# Тип функции и возвращаемого значения не совпадают"),	//есть
		ERROR_ENTRY(316, "[SEM]# Недопустимое строковое выражение справа от знака \'=\'"),	//нет
		ERROR_ENTRY(317, "[SEM]# Неверное условное выражение"),	//есть
		ERROR_ENTRY(318, "[SEM]# Деление на ноль"),	//есть
		ERROR_ENTRY(319, "[SEM]# Совпадение имени функции пользователя с функцией из стандартной библиотеки"),
		ERROR_ENTRY_NODEF100(400), ERROR_ENTRY_NODEF100(500),
		ERROR_ENTRY(600, "[SYN]# Неверная структура программы"),
		ERROR_ENTRY(601, "[SYN]# Не найден список параметров функции"),
		ERROR_ENTRY(602, "[SYN]# Ошибка в теле функции"),
		ERROR_ENTRY(603, "[SYN]# Ошибка в теле процедуры"),
		ERROR_ENTRY(604, "[SYN]# Ошибка в списке параметров функции"),
		ERROR_ENTRY(605, "[SYN]# Ошибка в вызове функции/выражении"),
		ERROR_ENTRY(606, "[SYN]# Ошибка в списке фактических параметров функции"),
		ERROR_ENTRY(607, "[SYN]# Ошибка при констуировании цикла/условного выражения"),
		ERROR_ENTRY(608, "[SYN]# Ошибка в теле цикла/условного выражения"),
		ERROR_ENTRY(609, "[SYN]# Ошибка в условии цикла/условного выражения"),
		ERROR_ENTRY(610, "[SYN]# Неверный условный оператор"),
		ERROR_ENTRY(611, "[SYN]# Неверный арифметический оператор"),
		ERROR_ENTRY(612, "[SYN]# Неверное выражение. Ожидаются только идентификаторы/литералы"),
		ERROR_ENTRY(613, "[SYN]# Ошибка в арифметическом выражении"),
		ERROR_ENTRY(614, "[SYN]# Недопустимая синтаксическая конструкция"),
		ERROR_ENTRY(615, "[SYN]# Недопустимая синтаксическая конструкция в теле цикла/условного выражения"),
		ERROR_ENTRY_NODEF10(620), ERROR_ENTRY_NODEF10(630), ERROR_ENTRY_NODEF10(640),
		ERROR_ENTRY_NODEF10(660), ERROR_ENTRY_NODEF10(670), ERROR_ENTRY_NODEF10(680), ERROR_ENTRY_NODEF10(690),
		ERROR_ENTRY_NODEF100(700), ERROR_ENTRY_NODEF100(800), ERROR_ENTRY_NODEF100(900)
	};

	ERROR geterror(int id)
	{
		ERROR e;
		if (id < 0 || id > ERROR_MAX_ENTRY)
			e = error[0];
		else
			e = error[id];
		return e;

	}
	ERROR geterrorin(int id, int line = -1, int col = -1)
	{
		ERROR e;
		if (id < 0 || id > ERROR_MAX_ENTRY)
			e = error[0];
		else
		{
			e = error[id];
			e.inext.line = line;
			e.inext.col = col;
		}
		return e;
	}
};