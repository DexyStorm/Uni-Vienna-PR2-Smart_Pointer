#include "hcp.h"

//ctor
Health_Care_Provider::Health_Care_Provider(std::string n, const std::set<Medical_Specialty>& t,unsigned w):
name{n},
topics{t},
wealth{w}
{
   if(this->name.empty())
   {
      throw std::runtime_error("name of hcp must not be empty. error thrown from hcp ctor");
   }
}

// dtor
Health_Care_Provider::~Health_Care_Provider()
{

}

// methods

// returns name
std::string Health_Care_Provider::get_name() const
{
   return this->name;
}

// increases wealth by x
void Health_Care_Provider::increase_wealth(unsigned x)
{
   wealth = wealth + x;
}

// if possible, wealth is decresed by x and true is returned.
// if not possible, wealth is not decreased and false is retruned
bool Health_Care_Provider::pay_license(unsigned x)
{
   if((static_cast<int>(wealth) - static_cast<int>(x)) < 0)
   {
      return false;
   }

   wealth = wealth - x;
   return true;
}

// adds x to topics
void Health_Care_Provider::receive_license(Medical_Specialty x)
{
   this->topics.insert(x);
}

// returns true if m is in topics. else return false
bool Health_Care_Provider::eligible_for(Medical_Specialty m)
{
   for(const auto& t : this->topics)
   {
      if(t == m)
      {
         return true;
      }
   }
   return false;
}

// print method
std::ostream& Health_Care_Provider::print(std::ostream &o) const
{
   o << "[" << this->name << ", {";

   bool first{true};
   for(const auto& t : topics)
   {
      if(first == true)
      {
         first = false;
      }
      else
      {
         o << ", ";
      }
      o << t;
   }

   o << "}, " << wealth << " moneyz, " << hcp_type() << "]";
   return o;
}

// operator << overload
std::ostream& operator<<(std::ostream &o, const Health_Care_Provider &h)
{
   return h.print(o);
}



//class Teaching_Health_Care_Provider

//ctor
Teaching_Health_Care_Provider::Teaching_Health_Care_Provider(unsigned fee, std::string n, const std::set<Medical_Specialty>& s,unsigned w):
Health_Care_Provider{n, s, w},
fee{fee}
{

}

//if this-> is eligible for m and p requires treatment in m and p can pay the price x,
//then p is cured from m and wealth is increased by x.
//return the number of cured illnesses
unsigned Teaching_Health_Care_Provider::perform_procedure(unsigned x, std::shared_ptr<Patient> p, Medical_Specialty m)
{
   unsigned cured_counter {0};

   if(this->Health_Care_Provider::eligible_for(m) && p->requires_treatment_in(m) && p->pay_procedure(x))
   {
      cured_counter = p->cure(m);
      increase_wealth(x);
   }

   return cured_counter;
}

//Returns "Teacher".
std::string Teaching_Health_Care_Provider::hcp_type() const
{
   return "Teacher";
}

//if target points to this-> or knows m or cannot affort to pay fee or ???this does not know m???, return false
//otherweise wealth is increased by fee and target pays the fee and recieves a lincese for topic m and return true
bool Teaching_Health_Care_Provider::teach(Medical_Specialty m, std::shared_ptr<Health_Care_Provider> target)
{
   // std::cout << std::endl;
   // std::cout << "target.get() == this is " << (target.get() == this) << std::endl;
   // std::cout << "target->eligible_for(m)" << (target->eligible_for(m)) << std::endl;
   // std::cout << "!(this->eligible_for(m))" << (!(this->eligible_for(m))) << std::endl;
   // std::cout << "!(target->pay_license(fee)) " << (!(target->pay_license(fee))) << std::endl;
   //this-> teaches target
   if (this == target.get() || target->Health_Care_Provider::eligible_for(m) || !(this->Health_Care_Provider::eligible_for(m)) || !(target->Health_Care_Provider::pay_license(fee)))
   {
      return false;
   }

   Health_Care_Provider::increase_wealth(fee);
   target->Health_Care_Provider::pay_license(fee);
   target->Health_Care_Provider::receive_license(m); //target->receive_license(m); doesnt work 4 some reason
   return true;
}



//class Smart_Health_Care_Provider

//ctor
Smart_Health_Care_Provider::Smart_Health_Care_Provider(unsigned fee,std::string n, const std::set<Medical_Specialty>& s,unsigned w):
Health_Care_Provider{n, s, w},
fee{fee}
{

}

//Returns 0.
unsigned Smart_Health_Care_Provider::perform_procedure(unsigned x, std::shared_ptr<Patient> p, Medical_Specialty m)
{
   return 0;
}

//returns "Smart"
std::string Smart_Health_Care_Provider::hcp_type() const
{
   return "Smart";
}

//adds the lincese to the topics. wealth of this-> is (always) increased by fee
void Smart_Health_Care_Provider::receive_license(Medical_Specialty m)
{
   Health_Care_Provider::receive_license(m);
   Health_Care_Provider::increase_wealth(fee);
}
