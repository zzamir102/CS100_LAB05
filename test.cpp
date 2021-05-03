#include "spreadsheet.cpp"
#include "gtest/gtest.h"

using namespace std;

//Print_Selection function tested here
//Select_Contains class tested 

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

//Select_Not Tests Start Here

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

//-----------------------
//Test for Select_And

TEST(Print_Selection, Select_AndwithSelect_Not) {
        Spreadsheet sheet;
        sheet.set_column_names({"Soccer", "Basketball", "Football"});
        sheet.add_row({"Barcelona", "Lakers", "Raiders"});
        sheet.add_row({"Real Madrid", "Spurs", "Packers"});
        sheet.add_row({"PSG", "Lakers", "Jets"});
        sheet.add_row({"Barcelona", "Lakers", "Raiders"});
        sheet.add_row({"Chivas", "Clippers", "Raid"});
        stringstream output;
        sheet.set_selection(new Select_And(
                new Select_Contains(&sheet, "Football", "Raid"),
                        new Select_Not(
                                new Select_Contains(&sheet, "Soccer", "Barcelona"))));
        sheet.print_selection(output);
        EXPECT_EQ(output.str(), "Chivas Clippers Raid \n");
}

//-----------------------
//Test for Select_Or

TEST(Print_Selection, Select_OrwithSelect_Contain) {
	Spreadsheet sheet;
	sheet.set_column_names({"Soccer", "Basketball", "Football"});
	sheet.add_row({"Real Madrid", "Lakers", "Raiders"});
	sheet.add_row({"PSG", "Celtics", "Jets"});
	sheet.add_row({"Barcelona", "Jazz", "Broncos"});
	sheet.add_row({"Arsenal", "Suns", "Steelers"});
	stringstream output;
	sheet.set_selection(new Select_Or(
		new Select_Contains(&sheet, "Basketball", "Lake"),
			new Select_Contains(&sheet, "Soccer", "Real")));
	sheet.print_selection(output);
	EXPECT_EQ(output.str(), "Real Madrid Lakers Raiders \n");
}

TEST(Print_Selection, Select_OrwithSelect_Not) {
	Spreadsheet sheet;
	sheet.set_column_names({"Soccer", "Basketball", "Football"});
	sheet.add_row({"Real Madrid", "Lakers", "Raiders"});
	sheet.add_row({"PSG", "Celtics", "Jets"});
	sheet.add_row({"Barcelona", "Jazz", "Broncos"});
	sheet.add_row({"Arsenal", "Suns", "Steelers"});
	stringstream output;
	sheet.set_selection(new Select_Or(
		new Select_Not(
			new Select_Contains(&sheet,  "Football", "Broncos")),
				new Select_Contains(&sheet, "Basketball", "Sun")));
	sheet.print_selection(output);
	EXPECT_EQ(output.str(), "Real Madrid Lakers Raiders \nPSG Celtics Jets \nArsenal Suns Steelers \n");
}

TEST(Print_Selection, Select_OrwithInvalidInput) {
	Spreadsheet sheet;
	sheet.set_column_names({"Soccer", "Basketball", "Football"});
	sheet.add_row({"Real Madrid", "Lakers", "Raiders"});
	sheet.add_row({"PSG", "Celtics", "Jets"});
	sheet.add_row({"Barcelona", "Jazz", "Broncos"});
	sheet.add_row({"Arsenal", "Suns", "Steelers"});
	stringstream output;
	sheet.set_selection(new Select_Or(
		new Select_Contains(&sheet, "Basketball", "Lake"),
			new Select_Contains(&sheet, "Soccer", "Meal")));
	sheet.print_selection(output);
	EXPECT_EQ(output.str(), "Real Madrid Lakers Raiders \n");
}

TEST(Print_Selection, Select_OpEmptyString) {	
	Spreadsheet sheet;
	sheet.set_column_names({"Animals", "Fruits", "Plants"});
	sheet.add_row({"Dog", "banana", "Flower"});
	sheet.add_row({"dog", "Apple", "rose"});
	sheet.add_row({"cat", "Banana", "Moss"});
	sheet.add_row({"tiger", "Watermelon", "Geranium"});
	sheet.add_row({"lion", "melon", "ivy"});
	stringstream output;
	sheet.set_selection(new Select_Or(
		new Select_Contains(&sheet, "Fruits", "ban"),
			new Select_Contains(&sheet, "Plants", "")));
	sheet.print_selection(output);
	EXPECT_EQ(output.str(),"Dog banana Flower \ndog Apple rose \ncat Banana Moss \ntiger Watermelon Geranium \nlion melon ivy \n");	
}

TEST(Print_Selection, Select_OpSameColumns) {	
	Spreadsheet sheet;
	sheet.set_column_names({"Animals", "Animals", "Plants"});
	sheet.add_row({"Dog", "banana", "Flower"});
	sheet.add_row({"dog", "Apple", "rose"});
	sheet.add_row({"cat", "Banana", "Moss"});
	sheet.add_row({"tiger", "Watermelon", "Geranium"});
	sheet.add_row({"lion", "melon", "ivy"});
	stringstream output;
	sheet.set_selection(new Select_Or(
		new Select_Contains(&sheet, "Animals", "Dog"),
			new Select_Contains(&sheet, "Animals", "dog")));
	sheet.print_selection(output);
	EXPECT_EQ(output.str(),"Dog banana Flower \ndog Apple rose \n");	
}




int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
