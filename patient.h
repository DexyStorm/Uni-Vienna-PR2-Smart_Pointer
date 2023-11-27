#ifndef PATIENT_H
#define PATIENT_H

//includes
#include "hospital.h"
#include "illness.h"

//forward declarations
class Illness;        //i think i dont need it if i already #include "illness.h"
enum class Medical_Specialty;

class Patient
{
   //member variables
   std::string name; //name of patient
   int age;          //age of patient 
   std::set<Illness> illnesses; //contains illnesses from with the patient is suffering from
   unsigned wealth;

public:

   //ctor
   Patient(std::string, int, const std::set<Illness>&, unsigned = 200);

   //member variables

   //increase welath by x
   void increase_wealth(unsigned x);

   //if possible, decrease wealth by x and return true
   //otherwise dont decrease and return false
   bool pay_procedure(unsigned x);

   //adds x to the set of illnesses
   void catch_disease(const Illness& x);

   //returns true if patient suffers from at least 1 Illness with speciality x
   //otherwise return falses
   bool requires_treatment_in(Medical_Specialty x) const;

   //returns true if patient suffers from no illnesses
   //otherwise return false
   bool healthy() const;

   //returns name of patient
   std::string get_name() const;

   //removes all illnesses with speciality x
   //return number of cured elements
   unsigned cure(Medical_Specialty x);

   //operator == overload
   bool operator==(const Patient &p) const;

   //print method for operator << overload
   std::ostream& print(std::ostream& o) const;
};

//operator << overload
std::ostream& operator<<(std::ostream& o, const Patient& p);

#endif