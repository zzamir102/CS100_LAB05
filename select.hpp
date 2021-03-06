#ifndef __SELECT_HPP__
#define __SELECT_HPP__

#include <string>

using namespace std;

class Select
{
public:
    virtual ~Select() = default;

    // Return true if the specified row should be selected.
    virtual bool select(const Spreadsheet* sheet, int row) const = 0;
};

// A common type of criterion for selection is to perform a comparison based on
// the contents of one column.  This class contains contains the logic needed
// for dealing with columns. Note that this class is also an abstract base
// class, derived from Select.  It introduces a new select function (taking just
// a string) and implements the original interface in terms of this.  Derived
// classes need only implement the new select function.  You may choose to
// derive from Select or Select_Column at your convenience.
class Select_Column: public Select
{
protected:
    int column;
public:
    Select_Column(const Spreadsheet* sheet, const std::string& name)
    {
        column = sheet->get_column_by_name(name);
    }

    virtual bool select(const Spreadsheet* sheet, int row) const
    {
        return select(sheet->cell_data(row, column));
    }

    // Derived classes can instead implement this simpler interface.
    virtual bool select(const std::string& s) const = 0;
};

class Select_Contains: public Select
{
protected:
   int column;
   string str1;
public:
   Select_Contains(const Spreadsheet* sheet, string column_name, string row_name) {
	column = sheet->get_column_by_name(column_name);
	str1 = row_name;
   }

   virtual bool select(const Spreadsheet* sheet, int row) const {
	string temp = sheet->cell_data(row, column);
	size_t found = 	temp.find(str1);
	if (found != string::npos) {
		return true;
	}
	else {
		return false;
	}
  }
};

class Select_Not: public Select
{
protected:
   Select* Exclude;
public:
   Select_Not(Select* avoid_Sel) {
	Exclude = avoid_Sel;
   }

   ~Select_Not() {
	delete Exclude;
   }

   virtual bool select(const Spreadsheet* sheet, int row) const {
	if (Exclude->select(sheet, row) == true) {
		return false;
	}
	else {
		return true;
	}

   } 

};

class Select_And: public Select 
{
protected:
   Select* cell1;
   Select* cell2;
public:
   Select_And(Select* first, Select* second) {
	cell1 = first;
	cell2 = second;
   }

   ~Select_And() {
   	delete cell1;
	delete cell2;
   }

   virtual bool select(const Spreadsheet* sheet, int row) const {
  	if (cell1->select(sheet, row) == true && cell2->select(sheet, row) == true) {
		return true; 
	}
	else {
		return false;
	}
   }
};

class Select_Or: public Select 
{
protected:
   Select* cell1;
   Select* cell2;
public:
   Select_Or(Select* first, Select* second) {
	cell1 = first;
	cell2 = second;
   }

   ~Select_Or() {
   	delete cell1;
	delete cell2;
   }

   virtual bool select(const Spreadsheet* sheet, int row) const {
  	if (cell1->select(sheet, row) == true || cell2->select(sheet, row) == true) {
		return true; 
	}
	else {
		return false;
	}
   }
};





#endif //__SELECT_HPP__
