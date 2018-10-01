#include <iostream> 
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <string>

using namespace std;

typedef struct Val {
	int molecular;
	int Denominator;
} VVV; 

bool Check_input(int argc, char* argv[]);
int MyRand(int max);
string Generate(int max, int number);
string simplify(int molecular, int Denominator);//分子 分母 
string TwoCreat(int max, int answers, int Denominator);
string SuperCreat(int max, int number, int answers, int Denominator = 1);
void Certain();
bool isprimer(int aim);
void Negative(VVV &a, VVV &b);
void Easy(VVV &aim);
string Easystring(VVV &aim);
string Asmall(VVV a, VVV b, VVV &answer);
string Bsmall(VVV a, VVV b, VVV &answer);
string Amazing(int max, int number, VVV &answer);


int range;
int problems;
int r_certain;
int n_certain;

int main(int argc, char* argv[])
{
	if (!Check_input(argc, argv))
	{
		cout << "Wrong input.\n";
		return 0;
	}
	
	ofstream outfile1, outfile2;
	outfile1.open("Exercises.txt");
	outfile2.open("Answers.txt");
	if (!outfile1.is_open())
	{
		cout << "Couldn't open Exercises.txt";
		return 0;
	}
	if (!outfile2.is_open())
	{
		cout << "Couldn't open Answers.txt";
		return 0;
	}
	
	int topic_number;
	VVV temp;
	int i, d;
	vector<string> question;
	vector<string> answer;
	srand(time(NULL));
	
	Certain();
	cout << "HHH" << endl;
	for (i = 0; i < problems; i++)
	{
		topic_number = (rand() % 3) + 2;
		//question.push_back(Generate(range, topic_number));
		question.push_back(Amazing(range, topic_number, temp));
		answer.push_back(Easystring(temp));
	}
	
	for (i = 0, d = answer.size(); i < d; i++)
	{
		outfile1 << answer[i] << endl;
		outfile2 << question[i] << endl;
	}
	outfile1.close();
	outfile2.close();
	
	return 0;
}




bool Check_input(int argc, char* argv[])
{
	if (argc == 3)
	{
		string temp = argv[1];
		if (temp != "-n" && temp != "-r")
			return false;
		else if (temp == "-r")	//数值的大小 
		{
			r_certain = 1;
			range = stoi(argv[2]);
		} 
		else if (temp == "-n")
		{
			n_certain = 1;
			problems = stoi(argv[2]);		//题目的数量 
		}
		return true;
	}
	else if (argc == 4)
	{
		if ((argv[1] != "-e" && argv[3] != "-a") &&
		(argv[1] != "-a" && argv[3] != "-e") )
			return false;
		return true;
	}
	else
		return false;
	return true;
}

int MyRand(int max)
{
	return (rand() % (max + 1));
}

string Generate(int max, int number)
{
	int i;
	vector<int> temp;
	vector<char> symbol;
	string answer = "";
	for (i = 0; i < number; i++)
		temp.push_back(MyRand(max));
	for (i = 0; i < number - 1; i++)
	{
		switch(MyRand(max) % 4)
		{
			case 0:
				symbol.push_back('+');
				break;
			case 1:
				symbol.push_back('-');
				break;
			case 2:
				symbol.push_back('*');
				break;
			case 3:
				symbol.push_back('/');
				break;
		}
	}
	answer += to_string(temp[0]);
	for (i = 1; i < number; i++)
	{
		//cout << symbol[i-1] << temp[i] << endl;
		answer += symbol[i - 1];
		answer += to_string(temp[i]);
		
	}
	
	//增加 0 or 1 个括号
	if (rand() % 2)
	{
		int flag, temp, len, ttt;
		for (flag = 0, len = answer.size(); !flag; )
		{
			temp = rand() % len;
			if (isdigit(answer[temp]) && (temp == 0 || !isdigit(answer[temp - 1])))
			{
				answer.insert(temp, "(");
				flag = 1;
				break;
			}
		}
		len++;
		while (flag)
		{
			ttt = rand() % len;
			if (isdigit(answer[ttt]) && (ttt == (len - 1) || !isdigit(answer[temp + 1])))
			{
				if (ttt == (len - 1))
					answer += ")";
				else
					answer.insert(ttt + 1, ")");
				break;
			}	
		}
	}
	
	answer += " = ";
	cout << answer << endl;
	return answer;
}

string simplify(int molecular, int Denominator)
{
	string answer = "";
	if (molecular < Denominator)
	{
		answer += to_string(molecular);
		answer += "/";
		answer += to_string(Denominator);
	}
	else if (molecular % Denominator == 0)
	{
		answer += to_string(molecular / Denominator);
	}
	else
	{
		answer += to_string(molecular / Denominator);
		answer += "'";
		answer += to_string(molecular % Denominator);
		answer += "/";
		answer += to_string(Denominator);
	}
	return answer;
} 
 
string TwoCreat(int max, int answers, int Denominator)
{
	/*
	answers 是先制造的答案
	再制造其中一个数字
	*/
	// 1
	string question = "";
	int as = answers;
	//double as = double(answers) / double(Denominator);
	int temp = MyRand(max);
	question += simplify(temp, Denominator);
	switch (MyRand(time(NULL)) % 4)
	{	// *   /
		case 0:		// *
			question += " * ";
			question += simplify(as, temp * Denominator);
			break;
		case 1:		// /
			question += " / ";
			question += simplify(temp, as * Denominator);
			break;
		case 2:		// +
			question += " + ";
			question += to_string(as - temp);
			break;
		case 3:		// -
			question += " - ";
			question += to_string(temp - as);
			break;
		default:
			cout << "Unknown Error" << endl;
			break; 
	}
	return question;
}


string SuperCreat(int max, int number, int answers, int Denominator)
{
	string question = "";	
	if (number == 2)
		question += TwoCreat(max, answers, Denominator);
	else if (number == 3)
	{
		int as = answers;
		//double as = double(answers) / double(Denominator);
		int temp = MyRand(max);
		question += TwoCreat(max, temp, Denominator);
		switch (MyRand(time(NULL)) % 4)
		{	// *   /
			case 0:		// *
				question.insert(0, "(");
				question += ")";
				question += " * ";
				question += simplify(as, temp * Denominator);
				break;
			case 1:		// /
				question.insert(0, "(");
				question += ")";
				question += " / ";
				question += simplify(temp, as * Denominator);
				break;
			case 2:		// +
				question += " + ";
				question += to_string(as - temp);
				break;
			case 3:		// -
				question += " - ";
				question += to_string(temp - as);
				break;
			default:
				cout << "Unknown Error" << endl;
				break; 
		}
	}
	else if (number == 4)
	{
		int as = answers;
		//double as = double(answers) / double(Denominator);
		int temp = MyRand(max);
		question += TwoCreat(max, temp, Denominator);
		switch (MyRand(time(NULL)) % 4)
		{	// *   /
			case 0:		// *
				question.insert(0, "(");
				question += ")";
				question += " * ";
				question += TwoCreat(max, as, temp * Denominator);
				break;
			case 1:		// /
				question.insert(0, "(");
				question += ")";
				question += " / ";
				question += TwoCreat(max, temp, as * Denominator);
				break;
			case 2:		// +
				question += " + ";
				question += TwoCreat(max, as - temp, Denominator);
				break;
			case 3:		// -
				question += " - ";
				question += TwoCreat(max, temp - as, Denominator);
				break;
			default:
				cout << "Unknown Error" << endl;
				break; 
		}
	}
	
	cout << question << endl;
	return question;
}


void Certain()
{
	if (!r_certain)
	{
		string temp;
		cout << "请输入数值范围." <<endl;
		cout << "请重新输入:" << endl;
		getline(cin, temp);
		
		range = stoi(temp.substr(11));
		r_certain = 1;
	}
	if (!n_certain)
	{
		cout << "请输入题目数量." <<endl;
		cout << "请重新输入:" << endl;
	}
	
	
	
}


bool isprimer(int aim)
{
	if (aim == 1)
		return false;
	int i;
	for (i = 2; i < aim; i++)
	{
		if (aim % i == 0)
			return false;
	}
	return true;
}


void Negative(VVV &a, VVV &b)
{
	if (((a.molecular * b.Denominator) - (b.molecular * a.Denominator)) < 0)
	{
		VVV temp;
		temp = a;
		a = b;
		b = temp;
	}
}
void Easy(VVV &aim)
{
	if (aim.Denominator == aim.molecular)
	{
		aim.Denominator = aim.molecular = 1;
	}
	else
	{
		int temp, small, big;
		if (aim.Denominator > aim.molecular)
		{
			big = aim.Denominator;
			small = aim.molecular;
		}
		else 
		{
			small = aim.Denominator;
			big = aim.molecular;
		}
		while (small != 0)
		{
			temp = big % small;
			big = small;
			small = temp;
		}
		aim.Denominator /= big;
		aim.molecular /= big;
	}
}

string Easystring(VVV &aim)
{
	Easy(aim);
	return simplify(aim.molecular, aim.Denominator);
}

string Asmall(VVV a, VVV b, VVV &answer)
{	//op只有 0  1四个数值 
	string question = "";
	int op = rand();
	switch(op % 2)
	{
		case 0:		//  +
			question += Easystring(a);
			question += " + ";
			question += Easystring(b);
			answer.molecular = (a.molecular * b.Denominator) + (b.molecular * a.Denominator);
			answer.Denominator = a.Denominator * b.Denominator;
			Easy(answer);
			break;
		case 1:		//  -
			Negative(a, b);
			question += Easystring(a);
			question += " - ";
			question += Easystring(b);
			answer.molecular = (a.molecular * b.Denominator) - (b.molecular * a.Denominator);
			answer.Denominator = a.Denominator * b.Denominator;
			Easy(answer);
			break;
		default:
			cout << "!!ERROR!!" << endl;
			break;
	}
	return question;
}
string Bsmall(VVV a, VVV b, VVV &answer)
{	//op只有 0  1四个数值 
	string question = "";
	int op = rand();
	switch(op % 2)
	{
		case 0:		//  *
			question += Easystring(a);
			question += " * ";
			question += Easystring(b);
			answer.molecular = a.molecular * b.molecular;
			answer.Denominator = a.Denominator * b.Denominator;
			Easy(answer);
			break;
		case 1:		//  /
			question += Easystring(a);
			question += " / ";
			question += Easystring(b);
			answer.molecular = a.molecular * b.Denominator;
			answer.Denominator = a.Denominator * b.molecular;
			Easy(answer);
			break;
		default:
			cout << "!!ERROR!!" << endl;
			break;
	}
	return question;
}


string Amazing(int max, int number, VVV &answer)
{
	int choose = MyRand(14);
	int op= rand();
	VVV a, b, c, d, tempA, tempB;
	a.Denominator = b.Denominator = tempA.Denominator
	= tempA.molecular = answer.Denominator
	 = answer.molecular = 1;
	string question, rrr;
	question = rrr = "";
	a.molecular = MyRand(max);
	b.molecular = MyRand(max);
	switch(choose)
	{	// a 代表优先级为1的乘除*/  b代表优先级为2的加减+- 
		case 0:		//	 b
			question += Asmall(a, b, answer);
			break;
		case 1:		//	 a
			question += Bsmall(a, b, answer);
			break;
		case 2:		//	 b  b + +
			c.molecular = MyRand(max);
			c.Denominator = 1;
			question += Asmall(a, b, answer);
			switch(op % 2)
			{
				case 0:
					question += "+";
					answer.molecular = (answer.molecular * c.Denominator) + (c.molecular * answer.Denominator);
					break;
				case 1:
					question += "-";
					answer.molecular = (answer.molecular * c.Denominator) - (c.molecular * answer.Denominator);
					break;
				default:
					cout << "@@ERROR@@" << endl;
					break;
			}
			answer.Denominator = answer.Denominator * c.Denominator;
			question += Easystring(c);
			break;
		case 3:		//	 b  a  + *
		case 4:		//	 a  b  * +
			c.molecular = MyRand(max);
			c.Denominator = 1;
			question += Bsmall(a, b, tempA);
			switch(op % 2)
			{
				case 0:
					question += "+";
					answer.molecular = (tempA.molecular * c.Denominator) + (c.molecular * tempA.Denominator);
					question += Easystring(c);
					break;
				case 1:
					answer.molecular = (tempA.molecular * c.Denominator) - (c.molecular * tempA.Denominator);
					if (answer.molecular < 0)
					{	
						answer.molecular =- answer.molecular;
						question.insert(0, "-");
						question.insert(0, Easystring(c));
					}
					else
					{
						question += "-";
						question += Easystring(c);
					}
					break;
				default:
					cout << "@@ERROR@@" << endl;
					break;
			}
			answer.Denominator *= c.Denominator;
			break;
		case 5:		//	 a  a	* *
			c.molecular = MyRand(max);
			c.Denominator = 1;
			question += Bsmall(a,b, tempA);
			switch(op % 2)
			{
				case 0:
					question += "*";
					answer.molecular = tempA.molecular * c.molecular;
					answer.Denominator = tempA.Denominator * c.Denominator;
					break;
				case 1:
					question += "/";
					answer.molecular = tempA.molecular * c.Denominator;
					answer.Denominator = tempA.Denominator * c.molecular;
					break;
				default:
					cout << "@@ERROR@@" << endl;
					break;
			}
			question += Easystring(c);
			break;
		case 6:		//	 a  a  b	* * +
		case 7:		//	 b  a  a	+ * *
			c.molecular = MyRand(max);
			c.Denominator = 1;
			d.molecular = MyRand(max);
			d.Denominator = 1;
			question += Bsmall(a, b, tempA); 
			switch(op % 2)
			{
				case 0:
					question += "*";
					answer.molecular = tempA.molecular * c.molecular;
					answer.Denominator = tempA.Denominator * c.Denominator;
					break;
				case 1:
					question += "/";
					answer.molecular = tempA.molecular * c.Denominator;
					answer.Denominator = tempA.Denominator * c.molecular;
					break;
				default:
					cout << "@@ERROR@@" << endl;
					break;
			}
			question += Easystring(c);
			op = rand();
			switch(op % 2)
			{
				case 0:
					question += "+";
					answer.molecular = (answer.molecular * d.Denominator) + (d.molecular * answer.Denominator);
					question += Easystring(d);
					break;
				case 1:
					answer.molecular = (answer.molecular * d.Denominator) - (d.molecular * answer.Denominator);
					if (answer.molecular < 0)
					{
						question.insert(0, "-");
						question.insert(0, Easystring(d));
						answer.molecular = -answer.molecular;
					}
					else
					{
						question += "-";
						question += Easystring(d);
					}
					break;
				default:
					cout << "@@ERROR@@" << endl;
					break;
			}
			answer.Denominator = answer.Denominator * d.Denominator;
			break;
		case 8:		//	 a  b  a	* + *
			c.molecular = MyRand(max);
			c.Denominator = 1;
			d.molecular = MyRand(max);
			d.Denominator = 1;	 
			question += Bsmall(a, b, answer);
			switch(op % 2)
			{
				case 0:
					question += "+";
					question += Bsmall(c, d, tempA);
					answer.molecular = (answer.molecular * tempA.Denominator) + (tempA.molecular * answer.Denominator);
					break;
				case 1:
					rrr = Bsmall(a, b, tempA);
					answer.molecular = (answer.molecular * tempA.Denominator) - (tempA.molecular * answer.Denominator);
					if (answer.molecular < 0)
					{
						answer.molecular = -answer.molecular;
						question.insert(0, "-");
						question.insert(0, rrr);
					}
					else
					{
						question += "-";
						question += rrr;
					}
					break;
				default:
					cout << "@@ERROR@@" << endl;
					break;
			}
			answer.Denominator *= tempA.Denominator;
			break;
		case 9:		//	 a  b  b	* + +
		case 10:		//	 b  a  b	+ * +
		case 11:		//	 b  b  a	+ + *
			c.molecular = MyRand(max);
			c.Denominator = 1;
			d.molecular = MyRand(max);
			d.Denominator = 1;	 
			question += Bsmall(a, b, tempA);
			switch(op % 2)
			{
				case 0:
					question += "+";
					question += Easystring(c);
					answer.molecular = (answer.molecular * c.Denominator) + (c.molecular * answer.Denominator);
					break;
				case 1:
					answer.molecular = (answer.molecular * c.Denominator) - (c.molecular * answer.Denominator);
					if (answer.molecular < 0)
					{
						question.insert(0, "-");
						question.insert(0, Easystring(c));
						answer.molecular = -answer.molecular;
					}
					else
					{
						question += "-";
						question += Easystring(c);
					}
					break;
				default:
					cout << "@@ERROR@@" << endl;
					break;
			}
			answer.molecular *= c.Denominator;
			op =rand();
			switch(op % 2)
			{
				case 0:
					question += "+";
					question += Easystring(d);
					answer.molecular = (answer.molecular * d.Denominator) + (d.molecular * answer.Denominator);
					break;
				case 1:
					answer.molecular = (answer.molecular * d.Denominator) - (d.molecular * answer.Denominator);
					if (answer.molecular < 0)
					{
						answer.molecular = -answer.molecular;
						question.insert(0, "-");
						question.insert(0, Easystring(d));
					}
					else
					{
						question += "-";
						question += Easystring(d);
					}
					break;
				default:
					cout << "@@ERROR@@" << endl;
					break;
			}
			answer.Denominator *= d.Denominator;
			break;
		case 12:		//	 a  a  a	* * *
			c.molecular = MyRand(max);
			c.Denominator = 1;
			d.molecular = MyRand(max);
			d.Denominator = 1;
			question += Bsmall(a, b, answer);
			switch(op % 2)
			{
				case 0:
					question += "*";
					question += Bsmall(c, d, tempA);
					answer.molecular *= tempA.molecular;
					answer.Denominator *= tempA.Denominator;
					break;
				case 1:
					question += "/";
					question += Bsmall(c, d, tempA);
					answer.molecular *= tempA.Denominator;
					answer.Denominator *= tempA.molecular;
					break;
				default:
					cout << "@@ERROR@@" << endl;
					break;
			}
			break;
		case 13:		//	 b  b  b	+ + +
			c.molecular = MyRand(max);
			c.Denominator = 1;
			d.molecular = MyRand(max);
			d.Denominator = 1;	 
			question += Asmall(a, b, answer);
			switch(op % 2)
			{
				case 0:
					question += "+";
					question += Asmall(c, d, tempA);
					answer.molecular = (answer.molecular * tempA.Denominator) + (tempA.molecular * answer.Denominator);
					break;
				case 1:
					rrr = Asmall(c, d, tempA);
					answer.molecular = (answer.molecular * tempA.Denominator) - (tempA.molecular * answer.Denominator);
					if (answer.molecular < 0)
					{
						answer.molecular = -answer.molecular;
						question.insert(0, "-");
						question.insert(0, rrr);
					}
					else
					{
						question += "-";
						question += rrr;
					}
					break;
				default:
					cout << "@@ERROR@@" << endl;
					break;
			}
			answer.Denominator *= tempA.Denominator;
			break;
	}
	cout << question << "Answer:" << Easystring(answer) << endl;
	return question;
}

 
