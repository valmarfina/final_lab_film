#include "Film.h"
#include "sort.h"
#include <string>
#include <vector>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <regex>

void printHeader(std::ostream& out)
{
	out << "_____________________________________________________________________________________________" << '\n';
	out << std::setw(25) << std::left << "ФИЛЬМ" << std::left
		<< std::setw(20) << "РЕЖИССЁР" << std::left
		<< std::setw(8) << "ГОД" << std::left
		<< std::setw(20) << "СЦЕНАРИСТ" << std::left
		<< std::setw(15) << "ЖАНР" << std::left << '\n';
	out << "_____________________________________________________________________________________________" << '\n';
}


//корректность ФИО
/*
[А-Я]      # первая буква должна быть заглавной
[а-я]+     # и хотя бы ещё одна прописная
\s+        # хотя бы один пробел между фамилией и именем
[А-Я]      # одна буква имени
\.         # и точка за ней
\s+[А-Я]\. # аналогично для отчества
*/
bool isFio(std::string& a)
{
	std::regex reg("([А-Я][а-я]{1,20} [А-Я]\. [А-Я]\.)");

		if (std::regex_match(a.c_str(), reg))
		{
			return true;
		}
	

	return false;
}

//корректность года
bool isYear(const int& f)
{
	if (f > 1895 && f < 2020)
	{
		return true;
	}
	return false;
}

//корректность жанра
bool isGenre(const std::string& f)
{
	const int N_GENRES = 14;
	std::string GENRES[N_GENRES] =
	{ "боевик",
		"вестерн",
		"гангстерский фильм",
		"детектив",
		"драма",
		"комедия",
		"мелодрама",
		"приключенческий",
		"сказка",
		"трагедия",
		"трагикомедия",
		"триллер",
		"фантастика",
		"ужасы"
	};

	for (int i = 0; i < N_GENRES; i++)
	{
		if (GENRES[i] == f)
		{
			return true;
			break;
		}
	}

	return false;
}

Film findLast(std::vector<Film>& filmV)
{
	int max = filmV[0].getYear();
	int imax = 0;

	for (int i = 0; i < filmV.size() - 1; ++i)
	{
		if (filmV[i].getYear() > max)
		{
			max = filmV[i].getYear();
			imax = i;
		}
	}
	Film lastFilm = filmV[imax];
	return lastFilm;
}


int main()
{

	setlocale(LC_ALL, "rus");

	std::cout << "Введите имя входного файла: " << std::endl;

	std::string fileName;
	std::cin >> fileName;

	std::ifstream in;
	std::ofstream out;

	in.open(fileName);
	if (!in.is_open())
	{
		std::cerr << "Не удалось открыть файл!";
		return 1;
	}

	std::vector<std::string> inVector;
	std::string str;
	while (!in.eof())//пока не конец файла
	{
		str = "";
		getline(in, str);
		inVector.push_back(str);
	}
	std::vector<Film> filmV(inVector.size() / 5);


	//----------------------------------------- 3 вектор обьектов && проверки -------------- 
	for (int i = 0; i < inVector.size() / 5; i++)
	{
		static int j = 0;

		//название фильма
		filmV[i].setTitleOfMovie(inVector[j]);
		j++;

		//имя режиссёра
		if (!isFio(inVector[j]))
		{
			std::cerr << "Ошибка входных данных в строке " << (j + 1);
			return 1;
		}
		filmV[i].setProducerName(inVector[j]);
		j++;

		//год

		int year = 0;
		int length = inVector[j].size();
		for (int i = 0; i < length; i++)
		{
			int d = int((inVector[j])[i]) - int('0');
			year = d + year * 10;
		}
		if (!isYear(year))
		{
			std::cerr << "Ошибка входных данных в строке " << (j + 1);
			return 1;
		}
		filmV[i].setYear(year);
		j++;

		//имя сценариста
		if (!isFio(inVector[j]))
		{
			std::cerr << "Ошибка входных данных в строке " << (j + 1);
			return 1;
		}
		filmV[i].setScenaristName(inVector[j]);
		j++;

		//жанр
		if (!isGenre(inVector[j]))
		{
			std::cerr << "Ошибка входных данных в строке " << (j + 1);
			return 1;
		}
		filmV[i].setFilmGenre(inVector[j]);
		j++;
	}
	in.close();
	//----------------------------------------- 4 поиск ------------------------------------ 
	std::cout << "Последний вышедший фильм это: " << std::endl;
	printHeader(std::cout);
	std::cout << findLast(filmV) << std::endl;

	//----------------------------------------- 5 сортировка с выводом в файл--------------- 
	out.open("o.txt");
	if (!out.is_open())
	{
		std::cerr << "Не удалось открыть файл!";
		return 1;
	}
	out << "До сортировки:" << std::endl;
	printHeader(out);
	for (int i = 0; i < filmV.size(); i++)
	{
		out << filmV[i];
	}
	out << "После сортировки:" << std::endl;
	insertion_sort(filmV);

	printHeader(out);
	for (int i = 0; i < filmV.size(); i++)
	{
		out << filmV[i];
	}
	out.close();

	return 0;
}
