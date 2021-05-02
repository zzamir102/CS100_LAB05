#include "spreadsheet.cpp"

#include "gtest/gtest.h"

using namespace std;

TEST(Print_Selection, Select_NotBaseTest) {
	Spreadsheet sheet;
	sheet.set_column_names({"Soccer", "Basketball", "Football"});
	sheet.add_row({"Barcelona", "Lakers", "Raiders"});
	sheet.add_row({"Real Madrid", "Spurs", "Packers"});
	sheet.add_row({"PSG", "Lakers", "Jets"});
	sheet.add_row({"Barcelona", "Lakers", "Raiders"});
	stringstream out;
	sheet.set_selection(new Select_Not(new Select_Contains(&sheet, "Soccer", "PSG")));
	sheet.print_selection(out);
	EXPECT_EQ(out.str(), "Barcelona Lakers Raiders \nReal Madrid Spurs Packers \nBarcelona Lakers Raiders \n");

}

TEST(Print_Selection, Select_NotTwoRows) {
	Spreadsheet sheet;
	sheet.set_column_names({"Soccer", "Basketball", "Football"});
	sheet.add_row({"Barcelona", "Lakers", "Raiders"});
	sheet.add_row({"Real Madrid", "Spurs", "Packers"});
	sheet.add_row({"PSG", "Lakers", "Jets"});
	sheet.add_row({"Barcelona", "Lakers", "Raiders"});
	stringstream out;
	sheet.set_selection(new Select_Not(new Select_Contains(&sheet, "Soccer", "Barcelona")));
	sheet.print_selection(out);
	EXPECT_EQ(out.str(), "Real Madrid Spurs Packers \nPSG Lakers Jets \n");

}

TEST(Print_Selection, Select_NotEmbeddedNot) {
	Spreadsheet sheet;
	sheet.set_column_names({"Soccer", "Basketball", "Football"});
	sheet.add_row({"Barcelona", "Lakers", "Raiders"});
	sheet.add_row({"Real Madrid", "Spurs", "Packers"});
	sheet.add_row({"PSG", "Lakers", "Jets"});
	sheet.add_row({"Barcelona", "Lakers", "Raiders"});
	stringstream out;
	sheet.set_selection(new Select_Not(new Select_Not(new Select_Contains(&sheet, "Soccer", "PSG"))));
	sheet.print_selection(out);
	EXPECT_EQ(out.str(), "PSG Lakers Jets \n");

}

TEST(Print_Selection, Select_NotContainsNotFound) {
	Spreadsheet sheet;
	sheet.set_column_names({"Soccer", "Basketball", "Football"});
	sheet.add_row({"Barcelona", "Lakers", "Raiders"});
	sheet.add_row({"Real Madrid", "Spurs", "Packers"});
	sheet.add_row({"PSG", "Lakers", "Jets"});
	sheet.add_row({"Barcelona", "Lakers", "Raiders"});
	stringstream out;
	sheet.set_selection(new Select_Not(new Select_Contains(&sheet, "Soccer", "Arsenal")));
	sheet.print_selection(out);
	EXPECT_EQ(out.str(), "Barcelona Lakers Raiders \nReal Madrid Spurs Packers \nPSG Lakers Jets \nBarcelona Lakers Raiders \n");

}

TEST(Print_Selection, Select_NotSubString) {
	Spreadsheet sheet;
	sheet.set_column_names({"Soccer", "Basketball", "Football"});
	sheet.add_row({"Barcelona", "Lakers", "Raiders"});
	sheet.add_row({"Real Madrid", "Spurs", "Packers"});
	sheet.add_row({"PSG", "Lakers", "Jets"});
	sheet.add_row({"Barcelona", "Lakers", "Raiders"});
	sheet.add_row({"Chivas", "Clippers", "Raid"});
	stringstream out;
	sheet.set_selection(new Select_Not(new Select_Contains(&sheet, "Football", "Raid")));
	sheet.print_selection(out);
	EXPECT_EQ(out.str(), "Real Madrid Spurs Packers \nPSG Lakers Jets \n");

}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
