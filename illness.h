#ifndef ILLNESS_H
#define ILLNESS_H

// includes
#include "hospital.h"

// forward declarations
enum class Medical_Specialty;

class Illness
{
	// member variables
	Medical_Specialty med; // describes which speciality is required to cure this illness
	std::string name;			 // name of the illness

public:
	// ctor
	Illness(Medical_Specialty m, const std::string &n);

	// methods

	// returns med
	Medical_Specialty get_specialty() const;

	// returns name
	std::string get_name() const;

	// print method for operator << overload
	std::ostream &print(std::ostream &o) const;

	// operator == overload
	bool operator==(const Illness &i) const;

	// operator < overload
	// returns true if the left operand is less than the med of right operand.
	// if the meds are the same, compare name
	bool operator<(const Illness &i) const;
};

// operator << overlaod
std::ostream &operator<<(std::ostream &o, const Illness &ill);

#endif