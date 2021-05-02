#include "spreadsheet.cpp"
#include "gtest/gtest.h"

using namespace std;


TEST(Print_Selection, PrintEntireList) {
	Spreadsheet sheet;
	sheet.set_column_names({"Animals", "Fruits", "Plants"});
	sheet.add_row({"Dog", "banana", "Flower"});
	sheet.add_row({"dog", "Apple", "rose"});
	sheet.add_row({"cat", "Banana", "Moss"});
	stringstream out;
	sheet.print_selection(out);
	EXPECT_EQ(out.str(), "Dog banana Flower \ndog Apple rose \ncat Banana Moss \n");	
}

TEST(Print_Selection, Select_ContainsBaseTest) {
	Spreadsheet sheet;
	sheet.set_column_names({"Animals", "Fruits", "Plants"});
	sheet.add_row({"Dog", "banana", "Flower"});
	sheet.add_row({"dog", "Apple", "rose"});
	sheet.add_row({"cat", "Banana", "Moss"});
	stringstream out;
	sheet.set_selection(new Select_Contains(&sheet, "Fruits", "banana"));
	sheet.print_selection(out);
	EXPECT_EQ(out.str(), "Dog banana Flower \n");	
}

TEST(Print_Selection, Select_ContainsSubString) {
	Spreadsheet sheet;
	sheet.set_column_names({"Animals", "Fruits", "Plants"});
	sheet.add_row({"Dog", "banana", "Flower"});
	sheet.add_row({"dog", "Apple", "rose"});
	sheet.add_row({"cat", "Banana", "Moss"});
	sheet.add_row({"tiger", "Watermelon", "Geranium"});
	sheet.add_row({"lion", "melon", "ivy"});
	stringstream out;
	sheet.set_selection(new Select_Contains(&sheet, "Fruits", "melon"));
	sheet.print_selection(out);
	EXPECT_EQ(out.str(), "tiger Watermelon Geranium \nlion melon ivy \n");	
}

TEST(Print_Selection, Select_ContainsEmptyString) {	
	Spreadsheet sheet;
	sheet.set_column_names({"Animals", "Fruits", "Plants"});
	sheet.add_row({"Dog", "banana", "Flower"});
	sheet.add_row({"dog", "Apple", "rose"});
	sheet.add_row({"cat", "Banana", "Moss"});
	sheet.add_row({"tiger", "Watermelon", "Geranium"});
	sheet.add_row({"lion", "melon", "ivy"});
	stringstream out;
	sheet.set_selection(new Select_Contains(&sheet, "Fruits", ""));
	sheet.print_selection(out);
	EXPECT_EQ(out.str(), "Dog banana Flower \ndog Apple rose \ncat Banana Moss \ntiger Watermelon Geranium \nlion melon ivy \n");	
}

TEST(Print_Selection, Select_ContainsStringNotFound) {	
	Spreadsheet sheet;
	sheet.set_column_names({"Animals", "Fruits", "Plants"});
	sheet.add_row({"Dog", "banana", "Flower"});
	sheet.add_row({"dog", "Apple", "rose"});
	sheet.add_row({"cat", "Banana", "Moss"});
	sheet.add_row({"tiger", "Watermelon", "Geranium"});
	sheet.add_row({"lion", "melon", "ivy"});
	stringstream out;
	sheet.set_selection(new Select_Contains(&sheet, "Animals", "Giraffe"));
	sheet.print_selection(out);
	EXPECT_EQ(out.str(), "");	
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
