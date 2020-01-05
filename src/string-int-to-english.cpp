#include <string>
#include <map>
#include <iostream>
#include <sstream>

using namespace std;

static map<int, string> words = {
	{0, "Zero"},
	{1, "One"},
	{2, "Two"},
	{3, "Three"},
	{4, "Four"},
	{5, "Five"},
	{6, "Six"},
	{7, "Seven"},
	{8, "Eight"},
	{9, "Nine"},
	{10, "Ten"},
	{11, "Eleven"},
	{12, "Twelve"},
	{13, "Thirteen"},
	{14, "Fourteen"},
	{15, "Fifteen"},
	{16, "Sixteen"},
	{17, "Seventeen"},
	{18, "Eighteen"},
	{19, "Nineteen"},
	{20, "Twenty"},
	{30, "Thirty"},
	{40, "Forty"},
	{50, "Fifty"},
	{60, "Sixty"},
	{70, "Seventy"},
	{80, "Eighty"},
	{90, "Ninety"},
	{100, "Hundred"},
	{1000, "Thousand"},
	{1000000, "Million"},
	{1000000000, "Billion"}
};

void numberToWordsUnder100(ostringstream& oss, int num)
{
	if (num <= 20)
	{
		oss << words[num];
	}
	else		
	{
		int tens = num / 10;
		int ones = num % 10;

		oss << words[tens*10];

		if (ones != 0)
		{
			oss << ' ';
			oss << words[ones];
		}
	}
}

void numberToWordsUnder1000(ostringstream& oss, int num)
{
	int hundreds = num / 100;
	int rest = num % 100;

	if (hundreds > 0)
	{
		oss << words[hundreds] << ' ' << words[100];

		if (rest > 0)
		{
			oss << ' ';
		}
	}

	if (rest > 0)
	{
		numberToWordsUnder100(oss, rest);
	}
}

string numberToWords(int num) 
{
	if (num <= 20)
	{
		return words[num];
	}

 	ostringstream oss;

 	int i = num;
 	int k = 1000000000;

 	while (i >= 1000)
 	{
 		if (i != num)
 		{
 			oss << ' ';
 		}

 		int thousands = i / k;

 		if (thousands != 0)
 		{
 			numberToWordsUnder1000(oss, thousands);
 			oss << ' ' << words[k];
		}

 		i -= (thousands * k);
 		k /= 1000;		
 	}

 	if (i != num && i != 0)
 	{
 		oss << ' ';
 	}

	numberToWordsUnder1000(oss, i);

    oss.flush();

    return oss.str();
}

int main()
{
	cout << numberToWords(30) << endl;		
	cout << numberToWords(1000) << endl;		
	cout << numberToWords(123) << endl;		
	cout << numberToWords(12345) << endl;		
	cout << numberToWords(1234567) << endl;		
	cout << numberToWords(1234567891) << endl;		
}
