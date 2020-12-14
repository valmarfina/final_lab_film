#include "Film.h"


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

std::istream& operator>> (std::istream& in, Film& f)
{
	in >> f.titleOfMovie_;
	in >> f.producerName_;
	in >> f.year_;
	in >> f.scenaristName_;
	in >> f.filmGenre_;

	return in;
}

//префиксного инкремента как метод класса
Film& Film::operator++()
{
	++year_;
	return *this;
}

// постфиксная форма  друж
Film operator++(Film& ref, int d)
{
	ref.year_++;
	return ref;
}

//бинар - через друж
Film operator-(Film f, Film f1)
{
	Film c;
	c.year_ = f.year_ - f1.year_;

	return c;
}