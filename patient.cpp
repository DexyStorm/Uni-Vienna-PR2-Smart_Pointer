#include "patient.h"

// forward declarations
class Illness;

// ctor
Patient::Patient(std::string n, int a, const std::set<Illness> &i, unsigned w):
name{n},
age{a},
illnesses{i},
wealth{w}
{
	if (name.empty())
	{
		throw std::runtime_error("name must not be empty. error thrown from patient ctor");
	}
	if (age < 0)
	{
		throw std::runtime_error("age cannot be smaller than 0. error from patient ctor");
	}
	if (illnesses.empty())
	{
		throw std::runtime_error("std::set illnesses must not be empty. error thrown from patient ctor");
	}
}

// increase welath by x
void Patient::increase_wealth(unsigned x)
{
	wealth = wealth + x;
}

// if possible, decrease wealth by x and return true
// otherwise dont decrease and return false
bool Patient::pay_procedure(unsigned x)
{
	if (static_cast<int>(wealth - x) < 0)
	{
		return false;
	}

	wealth = wealth - x;
	return true;
}

// adds x to the set of illnesses
void Patient::catch_disease(const Illness &x)
{
	this->illnesses.insert(x);
}

// returns true if patient suffers from at least 1 Illness with speciality x
// otherwise return falses
bool Patient::requires_treatment_in(Medical_Specialty x) const
{
	bool found = std::any_of(illnesses.begin(), illnesses.end(), [&x](const auto &i)
	{
		if(i.get_specialty() == x)
		{
			return true;
		}
		return false; 
	});

	return found;
}

// returns true if patient suffers from no illnesses
// otherwise return false
bool Patient::healthy() const
{
	if (illnesses.empty())
	{
		return true;
	}
	return false;
}

// returns name of patient
std::string Patient::get_name() const
{
	return this->name;
}

// removes all illnesses with speciality x
// return number of cured elements
unsigned Patient::cure(Medical_Specialty x)
{
	if (illnesses.empty())
	{
		return 0;
	}

	unsigned removed_counter{0};

	for (auto iter{illnesses.begin()}, end{illnesses.end()}; iter != end;)
	{
		if (iter->get_specialty() == x)
		{
			removed_counter = removed_counter + 1; // wenn was removed wird, darfst du nicht ++iter machen du idiot
			iter = illnesses.erase(iter);
		}
		else
		{
			++iter;
		}
	}
	return removed_counter;


}

// operator == overload
bool Patient::operator==(const Patient &p) const
{
	return (this->name == p.name && this->age == p.age && this->wealth == p.wealth && this->illnesses == p.illnesses);
}

// print method for operator << overload
std::ostream &Patient::print(std::ostream &o) const
{
	o << "[" << this->name << ", " << this->age << " years, {";

	bool first{true};
	for (const auto &i : illnesses)
	{
		if (first == true)
		{
			first = false;
		}
		else
		{
			o << ", ";
		}
		o << i;
	}

	o << "}, " << this->wealth << " moneyz]";

	return o;
}

// operator << overload
std::ostream &operator<<(std::ostream &o, const Patient &p)
{
	return p.print(o);
}
