#include "hospital.h"

// transforms the Medical_Speciality into a string
std::ostream &operator<<(std::ostream &o, Medical_Specialty m)
{
	switch (m)
	{
	case Medical_Specialty::Cardiology:
		o << "Cardiology";
		break;
	case Medical_Specialty::Dermatology:
		o << "Dermatology";
		break;
	case Medical_Specialty::Endocrinology:
		o << "Endocrinology";
		break;
	case Medical_Specialty::Gynecology:
		o << "Gynecology";
		break;
	case Medical_Specialty::Neurology:
		o << "Neurology";
		break;
	case Medical_Specialty::Oncology:
		o << "Oncology";
		break;
	case Medical_Specialty::Pathology:
		o << "Pathology";
		break;
	case Medical_Specialty::Pediatrics:
		o << "Pediatrics";
		break;
	case Medical_Specialty::Pulmonology:
		o << "Pulmonology";
		break;
	case Medical_Specialty::Urology:
		o << "Urology";
		break;
	}
	return o;
}

// ctor
Hospital::Hospital(std::string name):
name{name}
{
	if(name.empty())
  {
  	throw std::runtime_error("name of hospital is empty. error thrown from hospital.cpp ctor");
  }
}

// methods

// if m is not present in hcps, then m is inserted into hcps and true is returned. otherwise return false
bool Hospital::sign_hcp(std::shared_ptr<Health_Care_Provider> m)
{
	auto iter_to_hcp = this->hcps.find(m->get_name()); // WOAH

	if (iter_to_hcp == this->hcps.end())
	{
		this->hcps.insert({m->get_name(), m});
		return true;
	}
	return false;
}

// if m is not in patients, or is present but expired, m is inserted into patients and return true
bool Hospital::admit_patient(std::shared_ptr<Patient> m)
{
	auto iter_to_patient = this->patients.find(m->get_name());

	// if m is not in patients
	if (iter_to_patient == this->patients.end())
	{
		this->patients.insert({m->get_name(), m});
		return true;
	}

	// if m is in patients but is expired
	if (iter_to_patient->second.expired())
	{
		// this->patients.insert({m->get_name(), m}); 			//doesnt work
		// this->patients.emplace(m->get_name(), m);

		// iter_to_patient = patients.erase(iter_to_patient); //works
		// this->patients.insert({m->get_name(), m});

		patients[m->get_name()] = m; // looks nicer
		return true;
	}

	return false;
}

// remove n from hcps. if something is removed, return true. otherwise return false
bool Hospital::dismiss_hcp(std::string n)
{

	// dashier geht auch. ist wahrscheinlich auch fanicer
	for (const auto &h : hcps)
	{
		if (h.first == n)
		{
			hcps.erase(n);
			return true;
		}
	}
	return false;

	/*
		bool removed {false};

		for(auto iter {hcps.begin()}; iter != hcps.end();)
		{
			if(iter->first == n)
			{
				iter = this->hcps.erase(iter);
				removed = true;
			}
			++iter;
		}

		return removed;
		*/
}

// if no HCP with name n is found, throw a runtime_error.
// otherwise a shared_ptr to the HCP with name (=key) n is returned
std::shared_ptr<Health_Care_Provider> Hospital::get_hcp(std::string n) const
{
	/*DOESNT WORK 4 SOME REASON
	for(auto iter_to_hcp {hcps.begin()}; iter_to_hcp != hcps.end();)
	{
		if(iter_to_hcp->first == n)
		{
			return iter_to_hcp->second;
		}
	}
	*/

	for (const auto &hcp : hcps)
	{
		if (hcp.first == n)
		{
			return hcp.second;
		}
	}

	throw std::runtime_error("no hcp found. error thrown from 'std::shared_ptr<Health_Care_Provider> Hospital::get_hcp(std::string n) const' in class hosptial.cpp");
}

// if no patient with name n is found, or the weak_ptr is expired, throw runtime_error.
// otherwise a shared_ptr to the patient with name (=key) n is returned
std::shared_ptr<Patient> Hospital::get_patient(std::string n) const
{
	for (const auto &p : patients)
	{
		if (p.first == n)
		{
			if (p.second.expired())
			{
				throw std::runtime_error("patient is expired. error thrown from get_patient in hospital.cpp");
			}
			return p.second.lock();
		}
	}

	throw std::runtime_error("patient is not in this hospital. error thrown from get_patient in hospital.cpp");
}

// remove entry with key n (=name) from patients.
// if entry not expired return true
// otherwise reurn false
bool Hospital::dismiss_patient(std::string n)
{
	for (auto iter{patients.begin()}; iter != patients.end();)
	{
		if (iter->first == n)
		{
			if (iter->second.expired())
			{
				iter = patients.erase(iter);
				return false;
			}
			iter = patients.erase(iter);
			return true;
		}
		++iter;
	}

	return false;
}

// print method for operator << overload
std::ostream &Hospital::print(std::ostream &o) const
{
	o << "[" << this->name << ", hcps {";

	bool first{true};
	for (const auto &h : hcps)
	{
		if (first == true)
		{
			first = false;
		}
		else
		{
			o << ", ";
		}
		o << *h.second;
	}

	o << "}, patients {";

	first = true;
	for (const auto &p : patients)
	{
		if (first == true)
		{
			first = false;
		}
		else
		{
			if (p.second.expired() == false)
			{
				o << ", ";
			}
		}
		if (p.second.expired() == false)
		{
			o << *p.second.lock();
		}
	}

	o << "}]";
	return o;
}

// operator << overload for print method
std::ostream &operator<<(std::ostream &o, const Hospital &p)
{
	return p.print(o);
}