/*
NOTES:
For this converter, because it was not clearly stated how large of numbers we should convert, I decided to only convert values up to the maximum of 1000 aka. M.
I took about 3 1/2 hours on this project.
*/

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

/*
These are the constants. They consist of messages to the user as well as the roman numeral characters included.
*/
const string WELCOME = "Welcome to the Roman Numeral Converter";
const string CHOICES = "To insert a Roman Numeral type 'r'. To insert a digit type 'd'. To exit type 'q'. (Case insensitive)";
const string ANOTHER_CONVERSTION = "To make another conversion type in one of the following options.";
const string INVALID_CHAR_INPUT = "That input was invalid. To use the Roman Numeral Converter please use one of the following options.";
const string GET_DIGIT = "Please type a number between 1 and 1000. Do NOT use any leading zeroes (ex. 0092 to say 92). Type 'q' to return to previous menu.";
const string DIGIT_LENGTH_ERROR = "The input was too large. The digit must be between 1 and 1000 (max of 4 characters).";
const string DIGIT_VALUE_ERROR = "The number input was not within the range 1 to 1000. Digit must be within that range to convert. Returning to first menu.";
const string SUCCESSFUL_DIGIT_CONVERSION = "Here is the result of the digit entered converted to Roman Numeral:";
const string VALUE_ZERO_ERROR = "Zero is not a valid input. Digit must be within the range 1 to 1000. Returining to first menu.";
const string GET_ROMAN_NUMERAL = "Please enter a Roman numeral between the values of 1 and 1000 (The max entered is 'M' and nothing else and the min entered is 'I') or enter 'q' to return to the first menu. Entry is case insensitive.";
const string VALID_ROMAN_NUMERALS = "The following Roman Numerals are valid for this converter: I, V, X, L, C, D, and M.";
const string INVALID_ROMAN_NUMERAL = "The input contained an invalid character. Only use characters shown in the valid Roman Numerals.";
const string INVALID_ROMAN_VALUE = "The value of the roman numeral was greater than 1000. If M is entered that is the only value that can be entered.";
const string INVALID_ROMAN_ORDERING = "The charcters entered are in an invalid order. Please ensure that the characters are entered in a valid order";
const string SUCCESSFUL_ROMAN_CONVERSION = "Here is the result of the Roman Numeral converted to a digit:";
const size_t MAX_DIGIT_LENGTH = 4;
const char ONE = 'I';
const char FIVE = 'V';
const char TEN = 'X';
const char FIFTY = 'L';
const char ONE_HUNDRED = 'C';
const char FIVE_HUNDRED = 'D';
const char ONE_THOUSAND = 'M';

/*
This function determines if the digit entered is a valid input. Namely that it is actually a digit only containing numbers 
and that the digit does not exceed the length of 4 characters for the max value of 1000.
*/
bool checkDigitInput(string input) {
	bool result = true;
	if (input.length() > MAX_DIGIT_LENGTH || input.length() == 0) { 
		result = false;
		cout << DIGIT_LENGTH_ERROR << '\n' << '\n';
		return result;	
	}

	for (size_t i = 0; i < input.length(); ++i) {
		if (!isdigit(input[i])) {
			result = false;
			cout << DIGIT_VALUE_ERROR << '\n' << '\n';
			break;
		}
	}

	return result;
}

/*
Converts the digit from a char type to a size_t int.
*/
size_t convertCharToInt(char number) {
	size_t digit = number - '0';
	return digit;
}

/*
This function goes through each number value staring at the thousandths  place
and converts that value to the appropriate roman numeral value.
The default of the inner switch statements will occur if the value at that place
is zero. The s is retrurned in that case meaning that we should skip adding a roman
numeral for that place.
*/
string changeDigitToRoman(size_t digitPlace, size_t digit) {
	stringstream romanNumeral;
	switch (digitPlace) {
	// This is the thousandths place converter.
	case 4:
		if (digit != 1) {
			return "z";
		}
		romanNumeral << ONE_THOUSAND;
		break;
	case 3:
		// This is the hundredths place converter.
		switch (digit)
		{
		case 1:
			romanNumeral << ONE_HUNDRED;
			break;
		case 2:
			romanNumeral << ONE_HUNDRED << ONE_HUNDRED;
			break;
		case 3:
			romanNumeral << ONE_HUNDRED << ONE_HUNDRED << ONE_HUNDRED;
			break;
		case 4:
			romanNumeral << ONE_HUNDRED << FIVE_HUNDRED;
			break;
		case 5:
			romanNumeral << FIVE_HUNDRED;
			break;
		case 6:
			romanNumeral << FIVE_HUNDRED << ONE_HUNDRED;
			break;
		case 7:
			romanNumeral << FIVE_HUNDRED << ONE_HUNDRED << ONE_HUNDRED;
			break;
		case 8:
			romanNumeral << FIVE_HUNDRED << ONE_HUNDRED << ONE_HUNDRED << ONE_HUNDRED;
			break;
		case 9:
			romanNumeral << ONE_HUNDRED << ONE_THOUSAND;
			break;
		default:
			romanNumeral << "s";
			break;
		}

		break;
	case 2:
		// This is the tens place converter.
		switch (digit)
		{
		case 1:
			romanNumeral << TEN;
			break;
		case 2:
			romanNumeral << TEN << TEN;
			break;
		case 3:
			romanNumeral << TEN << TEN << TEN;
			break;
		case 4:
			romanNumeral << TEN << FIFTY;
			break;
		case 5:
			romanNumeral << FIFTY;
			break;
		case 6:
			romanNumeral << FIFTY << TEN;
			break;
		case 7:
			romanNumeral << FIFTY << TEN << TEN;
			break;
		case 8:
			romanNumeral << FIFTY << TEN << TEN << TEN;
			break;
		case 9:
			romanNumeral << TEN << ONE_HUNDRED;
			break;
		default:
			romanNumeral << "s";
			break;
		}
		break;

		break;
	case 1:
		// This is the ones place converter.
		switch (digit)
		{
		case 1:
			romanNumeral << ONE;
			break;
		case 2:
			romanNumeral << ONE << ONE;
			break;
		case 3:
			romanNumeral << ONE << ONE << ONE;
			break;
		case 4:
			romanNumeral << ONE << FIVE;
			break;
		case 5:
			romanNumeral << FIVE;
			break;
		case 6:
			romanNumeral <<	FIVE << ONE;
			break;
		case 7:
			romanNumeral << FIVE << ONE << ONE;
			break;
		case 8:
			romanNumeral << FIVE << ONE << ONE << ONE;
			break;
		case 9:
			romanNumeral << ONE << TEN;
			break;
		default:
			romanNumeral << "s";
			break;
		}
		break;
	}

	return romanNumeral.str();
}

/*
This is the base function for converting a digit to a roman numeral. This calls all of the 
appropriate functions to complete the conversion.
After verifying that the input is valid it will step through each digit and convert it to the 
appropriate roman numeral depedning on the place of the digit (ones, tens, hundredths, etc.).
Each value is put into a string stream which is then returned as a string with the result.
*/
void convertDigit() {
	bool validInput = false;
	string userInput;

	// Repeats until valid input or user enters 'q' to quit.
	while (!validInput) {
		cout << GET_DIGIT << "\n";
		cin >> userInput;
		if (userInput == "q" || userInput == "Q") {
			return;
		}
		validInput = checkDigitInput(userInput);
	}

	// Special case check where the user enters 0 which cannot be converted.
	size_t length = userInput.length();
	if (length == 1 && userInput[0] == '0') {
		cout << VALUE_ZERO_ERROR << '\n' << '\n';
		return;
	}

	// Check each digit and convert to roman numeral.
	bool oneThousand = false;
	stringstream finalString;
	for (size_t i = 0; i < length; ++i) {
		size_t digitPlace = length - i;
		size_t number = convertCharToInt(userInput[i]);
		string romanNumeral = changeDigitToRoman(digitPlace, number);
		// This is the check that determines if the number entered is greater than 1000.
		if (oneThousand && romanNumeral[0] != 's') {
			cout << DIGIT_VALUE_ERROR << '\n' << '\n';
			return;
		}

		// The converter only returns z if they entered a value greater than 1 in the thousandths place. This handles that error.
		if (romanNumeral == "z") {
			cout << DIGIT_VALUE_ERROR << '\n' << '\n';
			return;
		}

		// Indicating that we have used a M character meaning if there are any other characters we exceed 1000 which is not allowed.
		if (romanNumeral[0] == ONE_THOUSAND) { oneThousand = true; }

		// Indicating that the value at this place is 0 and to add no roman numeral to our answer.
		if (romanNumeral == "s") {
			continue;
		}

		finalString << romanNumeral;
	}

	cout << SUCCESSFUL_DIGIT_CONVERSION << '\n' << finalString.str() << '\n' << '\n';

	return;
}

/*
This is the function for converting a roman numeral into a digit. Starting
with the left-most character it will add the total to our starting value of
zero until we have added all values. If the character is a I, X, or C (which 
are values that can precede other roman numerals) we check the next character
before adding it to our total. If the next character follows the subtraction
rules then we add the subtraction rule number. 
At this same check we also look
to see if the next character is invalid meaning our current character cannot 
precede it. If that is the case we inform the user and ask them to input a new 
value or to return to the first menu.
If the ordering is valid then we return the total calculated which is our 
converted digit value.
*/
void convertRomanNumeral() {
	bool validInput = false;
	string userInput;
	size_t finalNumber = 0;

	while (!validInput) {
		cout << GET_ROMAN_NUMERAL << '\n' << VALID_ROMAN_NUMERALS << '\n';
		cin >> userInput;

		for (size_t i = 0; i < userInput.length(); ++i) {
			userInput[i] = toupper(userInput[i]);
		}

		// Return to the first menu.
		if (userInput == "q" || userInput == "Q") { return; }

		// Looks at each charcter starting at the left.
		bool breakLoop = false;
		for (size_t i = 0; i < userInput.length(); ++i) {
			switch (userInput[i]) {
			case ONE:
				// Checks the next roman numeral and either adds the correct number or indicates an invalid order.
				if (i + 1 < userInput.length()) {
					if (userInput[i + 1] == FIVE) {
						finalNumber += 4;
					}
					else if (userInput[i + 1] == TEN) {
						finalNumber += 9;
					}
					else if (userInput[i + 1] == FIFTY || userInput[i + 1] == ONE_HUNDRED || userInput[i + 1] == FIVE_HUNDRED || userInput[i + 1] == ONE_THOUSAND) {
						cout << INVALID_ROMAN_ORDERING << '\n' << '\n';
						breakLoop = true;
						break;
					}
					else {
						finalNumber += 1;
						break;
					}
					++i;
					break;
				}
				finalNumber += 1;
				break;

			case FIVE:
				finalNumber += 5;
				break;
			case TEN:
				// Checks the next roman numeral and either adds the correct number or indicates an invalid order.
				if (i + 1 < userInput.length()) {
					if (userInput[i + 1] == FIFTY) {
						finalNumber += 40;
					}
					else if (userInput[i + 1] == ONE_HUNDRED) {
						finalNumber += 90;
					}
					else if (userInput[i + 1] == FIVE_HUNDRED || userInput[i + 1] == ONE_THOUSAND) {
						cout << INVALID_ROMAN_ORDERING << '\n' << '\n';
						breakLoop = true;
						break;
					}
					else {
						finalNumber += 10;
						break;
					}
					++i;
					break;
				}
				finalNumber += 10;
				break;

			case FIFTY:
				finalNumber += 50;
				break;

			case ONE_HUNDRED:
				// Checks the next roman numeral and adds the correct number.
				if (i + 1 < userInput.length()) {
					if (userInput[i + 1] == FIVE_HUNDRED) {
						finalNumber += 400;
					}
					else if (userInput[i + 1] == ONE_THOUSAND) {
						finalNumber += 900;
					}
					else {
						finalNumber += 100;
						break;
					}
					++i;
					break;
				}
				finalNumber += 100;
				break;
			case FIVE_HUNDRED:
				finalNumber += 500;
				break;

			case ONE_THOUSAND:
				// If the string contains an M and any other character than the other character(s) is either invalid or exceeds the 1000 max.
				if (userInput.length() > 1) {
					cout << INVALID_ROMAN_VALUE << '\n' << '\n';
					breakLoop = true;
					break;
				}
				finalNumber += 1000;
				break;

			default:
				// The character entered was not one of the valid roman numerals.
				cout << INVALID_ROMAN_NUMERAL << '\n' << '\n';
				breakLoop = true;
				break;
			}

			if (breakLoop) { 
				finalNumber = 0;
				break; 
			}
		}
		if (!breakLoop) { validInput = true; }
	}

	cout << SUCCESSFUL_ROMAN_CONVERSION << '\n' << finalNumber << '\n' << '\n';
	return;
}

/*
Main function that calls the approriate converter.
*/
int main() {
	cout << WELCOME << "\n";
	bool exit = false;

	while (!exit) {
		cout << CHOICES << "\n";
		char inputNumberType;
		cin >> inputNumberType;
		inputNumberType = tolower(inputNumberType);

		switch (inputNumberType) {
		case 'r':
			convertRomanNumeral();
			break;

		case 'd':
			convertDigit();
			break;

		case 'q':
			exit = true;
			break;

		default:
			cout << INVALID_CHAR_INPUT << "\n" << '\n';
		}
		
		if (exit) {
			break;
		}
		cout << ANOTHER_CONVERSTION << '\n' << '\n';
	}

	return 0;
}