#include "Film.h"
#include <string>
#include <vector>
#include <iomanip>
#include <iostream>
#include <fstream>

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
bool isFio()
{
	return true;
}

//корректность года
bool isYear()
{
	return true;
}

//корректность жанра
bool isGenre()
{
	return true;
}

//Сортировка вставками(метод простых вставок)
template <typename T>
std::vector<T> insertion_sort(std::vector<T>& filmV)
{
	/*
	Сортировка вставками наиболее эффективна когда массив уже частично отсортирован и когда элементов массива не много.
	Если же элементов меньше 10 то данный алгоритм является лучшим.
	На каждом шаге сортировки сравнивается текущий элемент со всеми элементами в отсортированной части. 
    */
	int item;
	for (int i = 1; i < int(filmV.size()); i++)
	{
		T temp = filmV[i]; //  временная переменная для хранения значения элемента - инициализируем временную переменную текущим значением элемента массива
		item = i - 1; // запоминаем индекс предыдущего элемента массива
		while (item >= 0 && filmV[item] > temp) // пока индекс не равен 0 и предыдущий элемент массива больше текущего, изменив знак на >, массив будет сортироваться по убыванию.
		{
			filmV[item + 1] = filmV[item]; // перестановка элементов массива
			filmV[item] = temp;
			item--;
		}
	}
	return filmV;
}

//вывод на экран 

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
		std::cerr << "err";
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


	//----------------------------------------- 3 вектор обьектов--------------------------- 
	for (int i = 0; i < inVector.size() / 5; i++)
	{
		static int j = 0;

		//название фильма
		filmV[i].setTitleOfMovie(inVector[j]);
		j++;

		//имя режиссёра
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
		filmV[i].setYear(year);
		j++;

		//имя сценариста
		filmV[i].setScenaristName(inVector[j]);
		j++;

		//жанр
		filmV[i].setFilmGenre(inVector[j]);
		j++;
	}
	in.close();
	//----------------------------------------- 4 поиск ------------------------------------ 
	//----------------------------------------- 5 сортировка-------------------------------- 
	out.open("o.txt");
	if (!out.is_open())
	{
		std::cerr << "err";
		return 1;
	}
	printHeader(out);
	for (int i = 0; i < filmV.size(); i++) 
	{
		out << filmV[i];
	}

	out.close();

	std::cout << "Последний вышедший фильм: " << '\n';
	insertion_sort(filmV);
	printHeader(std::cout);
	for (int i = 0; i < filmV.size(); i++)
	{
		std::cout << filmV[i];
	}
}
