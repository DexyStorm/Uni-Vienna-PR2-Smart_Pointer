#include "illness.h"

//ctor
Illness::Illness(Medical_Specialty m,const std::string& n):
med{m},
name{n}
{
   if(name.empty())
   {
      throw std::runtime_error("name must not be empty. error throws from illness ctor");
   }
}

//returns med
Medical_Specialty Illness::get_specialty() const
{
   return this->med;
}

//returns name
std::string Illness::get_name() const
{
   return this->name;
}

std::ostream& operator<<(std::ostream& o, const Illness& ill)
{
   return ill.print(o);
}

//print method for operator << overload
std::ostream& Illness::print(std::ostream& o) const
{
   o << "[" << med << ", " << name << "]";
   return o;
}

//operator == overload
bool Illness::operator==(const Illness& i) const
{
   if(this->name == i.name && this->med == i.med)
   {
      return true;
   }
   return false;
}

//operator < overload
//returns true if the left operand is less than the med of right operand.
//if the meds are the same, compare name
bool Illness::operator<(const Illness& i) const
{
   if(this->med == i.med)
   {
      if(this->name < i.name)
      {
         return true;
      }
      return false;
   }
   if(this->med < i.med)
   {
      return true;
   }
   return false;
}