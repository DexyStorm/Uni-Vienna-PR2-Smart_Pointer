#ifndef HCP_H
#define HCP_H

#include "hospital.h"
#include "patient.h"

// forward declarations
enum class Medical_Specialty;
class Patient;
class Hospital;

class Health_Care_Provider
{
	// member variables
	std::string name;
	std::set<Medical_Specialty> topics;
	unsigned wealth;

public:
	// ctor
	Health_Care_Provider(std::string n, const std::set<Medical_Specialty> &s, unsigned wealth = 500);

	// dtor
	virtual ~Health_Care_Provider();

	// methods

	// returns name
	std::string get_name() const;

	// increases wealth by x
	void increase_wealth(unsigned x);

	// Not implemented.
	virtual unsigned perform_procedure(unsigned, std::shared_ptr<Patient>, Medical_Specialty) = 0;

	// Not Implemented
	virtual std::string hcp_type() const = 0;

	// if possible, wealth is decresed by x and true is returned.
	// if not possible, wealth is not decreased and false is retruned
	bool pay_license(unsigned x);

	// adds x to topics
	virtual void receive_license(Medical_Specialty x);

	// returns true if m is in topics. else return false
	bool eligible_for(Medical_Specialty m);

	// print method
	std::ostream &print(std::ostream &o) const;
};

// operator << overload
std::ostream &operator<<(std::ostream &o, const Health_Care_Provider &h);

class Teaching_Health_Care_Provider : public Health_Care_Provider
{
	// member variables
	unsigned fee;

public:
	// ctor
	Teaching_Health_Care_Provider(unsigned fee, std::string n, const std::set<Medical_Specialty> &, unsigned wealth = 500);

	// methods

	// if this-> is eligible for m and p requires treatment in m and p can pay the price x,
	// then p is cured from m and wealth is increased by x.
	// return the number of cured illnesses
	unsigned perform_procedure(unsigned x, std::shared_ptr<Patient> p, Medical_Specialty m);

	// Returns "Teacher".
	std::string hcp_type() const;

	// if target points to this-> or knows m or cannt affort to pay fee or this does not know m, return false
	// otherweise wealth is increased by fee and target pays the fee and recieves a lincese for topic m and return true
	bool teach(Medical_Specialty m, std::shared_ptr<Health_Care_Provider> target);
};

class Smart_Health_Care_Provider : public Health_Care_Provider
{
	// member variables
	unsigned fee;

public:
	// ctor
	Smart_Health_Care_Provider(unsigned fee, std::string n, const std::set<Medical_Specialty> &, unsigned wealth = 500);

	// methods

	// Returns 0.
	unsigned perform_procedure(unsigned x, std::shared_ptr<Patient> p, Medical_Specialty m);

	// returns "Smart"
	std::string hcp_type() const;

	// adds the lincese to the topics. wealth of this-> is (always) increased by fee
	void receive_license(Medical_Specialty m);


};

#endif // HCP_H