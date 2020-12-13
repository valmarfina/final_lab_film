#include <string>
#include <iomanip>

class Film
{
private:
	// 1) Описание полей класса
	//название фильма
	std::string titleOfMovie_;
	//имя режиссёра
	std::string producerName_;
	//год
	int year_;
	//имя сценариста
	std::string scenaristName_;
	//жанр
	std::string filmGenre_;

public:
	// 2)Конструктор по умолчанию (без параметров)
	Film() :
		titleOfMovie_(""),
		producerName_(""),
		year_(0),
		scenaristName_(""),
		filmGenre_("")
	{
	}
	//2) конструктор с параметрами
	Film(std::string titleOfMovie, std::string producerName, int year, std::string scenaristName, std::string filmGenre) :

		titleOfMovie_(titleOfMovie),
		producerName_(producerName),
		year_(year),
		scenaristName_(scenaristName),
		filmGenre_(filmGenre)

	{	}

	//2)конструктор kопирования
	Film(const Film& o)
	{
		titleOfMovie_ = o.titleOfMovie_;
		producerName_ = o.producerName_;
		year_ = o.year_;
		scenaristName_ = o.scenaristName_;
		filmGenre_ = o.filmGenre_;
	}


	//деструктор
	~Film() {}


	//Методы
	//название фильма
	std::string getTitleOfMovie() const { return titleOfMovie_; }
	void setTitleOfMovie(const std::string& a) { titleOfMovie_ = a; }

	//Фамилия режисера
	std::string getProducerName() const { return producerName_; }
	void setProducerName(const std::string& a) { producerName_ = a; }

	//год
	int getYear() const { return year_; }
	void setYear(const int& a) { year_ = a; }

	//Фамилия сценариста
	const std::string getScenaristName() const { return scenaristName_; }
	void setScenaristName(const std::string& a) { scenaristName_ = a; }

	//Жанр
	const std::string  getFilmGenre() const { return filmGenre_; }
	void setFilmGenre(const std::string& a) { filmGenre_ = a; }

	//Операторы отношения
	bool operator< (const Film& f) const;
	bool operator> (const Film& f) const;
	bool operator== (const Film& f) const;
	bool operator>= (const Film& f) const;
	bool operator<= (const Film& f) const;


	//friend std::istream& operator>> (std::istream& in, Film& f);
	friend std::ostream& operator<< (std::ostream& out, const Film& f);
};


//Операторы отношения
bool Film::operator<(const Film& f) const
{
	if (this == &f)
	{
		return false;
	}
	return this->year_ < f.year_;
}
bool Film::operator>(const Film& f) const
{
	if (this == &f)
	{
		return false;
	}
	return this->year_ < f.year_;
}

bool Film::operator==(const Film& f) const
{
	return this->year_ == f.year_;
}

bool Film::operator>=(const Film& f) const
{
	return this->year_ >= f.year_;
}

bool Film::operator<=(const Film& f) const
{
	return this->year_ <= f.year_;
}


std::ostream& operator<< (std::ostream& out, const Film& f)
{
	out << '\n';
	out << std::setw(25) << std::left << f.titleOfMovie_;
	out << std::setw(20) << std::left << f.producerName_;
	out << std::setw(8) << std::left << f.year_;
	out << std::setw(20) << std::left << f.scenaristName_;
	out << std::setw(15) << std::left << f.filmGenre_;
	out << '\n';
		return out;
}

//std::ostream& operator>> (std::ostream& in, const Film& f)
//{
//
//}