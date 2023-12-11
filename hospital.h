#ifndef HOSPITAL_H
#define HOSPITAL_H

// some includes
#include <vector>
#include <algorithm>
#include <string>
#include <set>
#include <map>
#include <cmath>
#include <iostream>
#include <memory>

#include "patient.h"
#include "hcp.h"

// forward declarations
class Patient;
class Health_Care_Provider;

enum class Medical_Specialty
{
	Cardiology,
	Dermatology,
	Endocrinology,
	Gynecology,
	Neurology,
	Oncology,
	Pathology,
	Pediatrics,
	Pulmonology,
	Urology
};

const std::vector<std::string> Medical_Specialty_Vector
{
	"Cardiology",
	"Dermatology",
	"Endocrinology",
	"Gynecology",
	"Neurology",
	"Oncology",
	"Pathology",
	"Pediatrics",
	"Pulmonology",
	"Urology"
};

class Hospital
{
	// member variables
	std::string name;
	std::map<std::string, std::shared_ptr<Health_Care_Provider>> hcps; // key is the name of the HCP
	std::map<std::string, std::weak_ptr<Patient>> patients;						 // key is the name of a patient

public:
	// cotr
	Hospital(std::string name);

	// methods

	// if m is not present in hcps, then m is inserted into hcps and true is returned. otherwise return false
	bool sign_hcp(std::shared_ptr<Health_Care_Provider> m);

	// if m is not in patients, or is present but expired, m is inserted into patients and return true
	bool admit_patient(std::shared_ptr<Patient> m);

	// remove n from hcps. if something is removed, return true. otherwise return false
	bool dismiss_hcp(std::string n);

	// if no HCP with name n is found, throw a runtime_error.
	// otherwise a shared_ptr to the HCP with name (=key) n is returned
	std::shared_ptr<Health_Care_Provider> get_hcp(std::string n) const;

	// if no patient with name n is found, or the weak_ptr is expired, throw runtime_error.
	// otherwise a shared_ptr to the patient with name (=key) n is returned
	std::shared_ptr<Patient> get_patient(std::string n) const;

	// remove entry with key n (=name) from patients.
	// an entry of a non-expired patient is removed, return true;
	// otherwise reurn false
	bool dismiss_patient(std::string n);

	// print method for operator << overload
	std::ostream &print(std::ostream &o) const;
};

// transforms the Medical_Speciality into a string
std::ostream &operator<<(std::ostream &o, Medical_Specialty m);

// operator << overload for print method
std::ostream &operator<<(std::ostream &o, const Hospital &p);

#endif // HOSPITAL_H