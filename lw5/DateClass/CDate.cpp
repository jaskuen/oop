#include "CDate.h"

// Non-class methods to create and work with date parts

struct DateFormat
{
	unsigned day;
	Month month;
	unsigned year;

	DateFormat()
	{
		year = 1970;
		month = Month::JANUARY;
		day = 1;
	}
};

bool IsLeap(unsigned year)
{
	return (year % 4 == 0 && year % 100 > 0) || (year % 400 == 0);
}

unsigned GetMonthDays(Month month, unsigned year)
{
	switch (month)
	{
	case Month::FEBRUARY:
		return IsLeap(year) ? 29 : 28;
	case Month::JANUARY:
	case Month::MARCH:
	case Month::MAY:
	case Month::JULY:
	case Month::AUGUST:
	case Month::OCTOBER:
	case Month::DECEMBER:
		return 31;
	default:
		return 30;
	}
}

unsigned ToTimestamp(unsigned day, Month month, unsigned year)
{
	if (day < 1 || day > GetMonthDays(month, year) || month < Month::JANUARY || month > Month::DECEMBER || year < 1970 || year > 9999)
	{
		return -1;
	}

	unsigned timestamp = 0;
	for (unsigned y = 1970; y < year; y++)
	{
		timestamp += IsLeap(y) ? 366 : 365;
	}

	for (unsigned m = 1; m < static_cast<unsigned>(month); m++)
	{
		timestamp += GetMonthDays(static_cast<Month>(m), year);
	}

	return timestamp + day - 1;
}

DateFormat ToDateFormat(unsigned timestamp)
{
	DateFormat date;
	unsigned daysLeft = timestamp;
	// year
	while (daysLeft > 0)
	{
		unsigned yearDays = IsLeap(date.year + 1) ? 366 : 365;
		if (daysLeft < yearDays)
		{
			break;
		}

		daysLeft -= yearDays;
		date.year++;
	}

	// month
	while (daysLeft > 0)
	{
		unsigned monthDays = GetMonthDays(date.month, date.year);
		if (daysLeft < monthDays)
		{
			break;
		}

		daysLeft -= monthDays;
		date.month = static_cast<Month>(static_cast<unsigned>(date.month) + 1);
	}

	date.day = daysLeft + 1;

	return date;
}

// Class methods


CDate::CDate(unsigned day, Month month, unsigned year)
{
	m_timestamp = ToTimestamp(day, month, year);
}

CDate::CDate(unsigned timestamp)
{
	m_timestamp = timestamp;
	if (!IsValid())
	{
		m_timestamp = 0;
	}
}

CDate::CDate()
{
	m_timestamp = 0;
}

unsigned CDate::GetDay() const
{
	DateFormat date = ToDateFormat(m_timestamp);
	return date.day;
}

Month CDate::GetMonth() const
{
	DateFormat date = ToDateFormat(m_timestamp);
	return date.month;
}

unsigned CDate::GetYear() const
{
	DateFormat date = ToDateFormat(m_timestamp);
	return date.year;
}

WeekDay CDate::GetWeekDay() const
{
	if (!IsValid())
	{
		return WeekDay::SUNDAY;
	}
	return static_cast<WeekDay>((m_timestamp + 4) % 7);
}

bool CDate::IsValid() const
{
	DateFormat date = ToDateFormat(m_timestamp);
	return m_timestamp != -1 &&
		date.day >= 1 && date.day <= GetMonthDays(date.month, date.year) &&
		date.month >= Month::JANUARY && date.month <= Month::DECEMBER &&
		date.year >= 1970 && date.year <= 9999;
}

CDate& CDate::operator++()
{
	if (IsValid())
	{
		m_timestamp++;
	}
	return *this;
}

CDate CDate::operator++(int)
{
	CDate date = *this;
	++*this;
	return date;
}

CDate& CDate::operator--()
{
	if (IsValid())
	{
		m_timestamp--;
	}
	return *this;
}

CDate CDate::operator--(int)
{
	CDate date = *this;
	--*this;
	return date;
}

CDate CDate::operator+(int days)
{
	CDate date = *this;
	date += days;
	return date;
}

CDate CDate::operator-(int days)
{
	CDate date = *this;
	date -= days;
	return date;
}

int CDate::operator-(const CDate& date)
{
	return static_cast<unsigned>(m_timestamp) - static_cast<unsigned>(date.m_timestamp);
}

CDate& CDate::operator+=(int days)
{
	if (IsValid())
	{
		m_timestamp+=days;
	}
	return *this;
}

CDate& CDate::operator-=(int days)
{
	if (IsValid() && static_cast<int>(m_timestamp) >= days)
	{
		m_timestamp -= days;
	}
	else
	{
		m_timestamp = -1;
	}
	return *this;
}

bool CDate::operator==(const CDate& date)
{
	return this->m_timestamp == date.m_timestamp;
}

bool CDate::operator!=(const CDate& date)
{
	return !(*this == date);
}

bool CDate::operator>(const CDate& date)
{
	return this->m_timestamp > date.m_timestamp;
}

bool CDate::operator<(const CDate& date)
{
	return this->m_timestamp < date.m_timestamp;
}

bool CDate::operator>=(const CDate& date)
{
	return !(*this < date);
}

bool CDate::operator<=(const CDate& date)
{
	return !(*this > date);
}

std::ostream& operator<<(std::ostream& os, const CDate& date)
{
	if (!date.IsValid())
	{
		return os << "INVALID";
	}

	DateFormat formated = ToDateFormat(date.m_timestamp);
	
	if (formated.day < 10)
	{
		os << "0";
	}
	os << formated.day << ".";

	unsigned month = static_cast<unsigned>(formated.month);
	if (month < 10)
	{
		os << "0";
	}
	os << month << "." << formated.year;
}

std::istream& operator>>(std::istream& is, CDate& date)
{
	unsigned day, month, year;
	char ch1, ch2;
	is >> day >> ch1 >> month >> ch2 >> year;
	if (ch1 == '.' && ch2 == '.')
	{
		date.m_timestamp = ToTimestamp(day, static_cast<Month>(month), year);
	}
	else
	{
		date.m_timestamp = -1;
	}

	return is;
}
