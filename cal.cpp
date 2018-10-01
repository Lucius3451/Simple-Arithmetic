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


int MyRand(int max);
string simplify(int molecular, int Denominator);//分子 分母 
bool Certain(void);
void Negative(VVV &a, VVV &b);
void Easy(VVV &aim);
string Easystring(VVV &aim);
string Asmall(VVV a, VVV b, VVV &answer);
string Bsmall(VVV a, VVV b, VVV &answer);
string Amazing(int max, int number, VVV &answer);

int problems, range;
int main(int argc, char* argv[])
{
	string ooo = argv[1];
	if (argc == 2 && ooo == "start" && Certain())
	{
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
		
		cout << "Poblems" << problems << "Range" << range << endl;
		for (i = 0; i < problems; i++)
		{
			topic_number = (rand() % 3) + 2;
			//question.push_back(Generate(range, topic_number));
			question.push_back(Amazing(range, topic_number, temp));
			answer.push_back(Easystring(temp));
		}
		
		for (i = 0, d = answer.size(); i < d; i++)
		{
			outfile1 << question[i] << endl;
			outfile2 << answer[i] << endl;
		}
		
		outfile1.close();
		outfile2.close();
		
	}
	else if (argc == 3)
	{
		string aline, bline, par;
		ifstream cread;
		cread.open("Setting.txt", ios::app);
		getline(cread, aline);
		getline(cread, bline);
		cread.close();
		ofstream cfile;
		cfile.open("Setting.txt", ios::out|ios::ate);
		if (!cfile.is_open())
		{
			cout << "Couldn't open Setting.txt" << endl;
			return 0; 	
		}
		par = argv[1];
		if (par == "-n")
		{	//cal.exe -n 
			par = argv[2];
			aline = "cal.exe -n " + par;
			cout << "****" << aline << "***" << endl;
		}
		else if (par == "-r")
		{
			par = argv[2];
			bline = "cal.exe -r " + par;
			cout << "****" << bline << "***" << endl;
		}
		else
		{
			cout << "WRONG PARAMETER" << endl;
			return 0;
		}
		cfile.clear();
		cfile << aline << endl;
		cfile << bline << endl;
		cfile << flush;
		cfile.close();
	}
	else if (argc == 5)
	{
		string Three, Five;
		Three = argv[1];
		Five = argv[3];
		if (Three != "-e" || Five != "-a")
		{
			cout << argv[1] << argv[3] << endl;
			cout << "WRONG INPUT" << endl;
		}
		else
		{
			fstream exfile, anfile;
			string exname, anname;
			string right, wrong;
			int i, right_count, wrong_count; 
			exname = argv[2];
			anname = argv[4];
			exfile.open(exname, ios_base::in);
			anfile.open(anname, ios_base::in);
			if (!exfile)
			{
				cout << exname << " doesn't exist" << endl;
				return 0;
			}
			if (!anfile)
			{
				cout << anname << " doesn't exist" << endl;
				return 0;
			}
			exname = anname = "";
			right = wrong = "";
			for (i = 1, right_count = wrong_count = 0; getline(exfile, exname) && getline(anfile, anname); i++)
			{
				if (exname != anname)
				{
					wrong_count++;
					wrong += to_string(i);
					wrong += ", ";
				}
				else
				{
					right_count++;
					right += to_string(i);
					right += ", ";
				}
			}
			wrong.insert(0, "Wrong: " + to_string(wrong_count) + "(");
			wrong.erase(wrong.size() - 3, 2);
			wrong += ")";
			right.insert(0, "Corect: " + to_string(right_count) + "(");
			right.erase(right.size() - 3, 2);
			right += ")";
			cout << right <<endl;
			cout << wrong << endl;
			
			exfile.close();
			anfile.close();
		}
	}
	else
	{
		cout << "Wrong input.\n";
		cout << "支持的命令:" << endl
			 << "cal.exe start" << "# 正常启动生成程序" << endl
			 << "cal.exe -n integer" << "# 输入运算式的个数" << endl
			 << "cal.exe -r integer" << "# 输入运算式中的项数大小" << endl
			 << "Myapp.exe -e <exercisefile>.txt -a <answerfile>.txt"
			 << "# 答案检测" << endl;
		return 0;
	}
	return 0;
}



int MyRand(int max)
{
	return ((rand() % max) + 1);
}

string simplify(int molecular, int Denominator)
{
	string answer = "";
	if (Denominator == 1)
		return to_string(molecular);
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


bool Certain(void)
{
	ifstream cfile;
	cfile.open("Setting.txt");
	string aline, word;
	
	getline(cfile, aline);
	if (aline.empty())
	{
		cout << aline << endl;
		cout << "First Input -n and -r" << endl; 
		return false;
	}
	word = aline.substr(8, 2);
	if (word != "-n")
	{
		cout << "请先输入运算式的个数, 格式:" << endl
			 << "cal.exe -n integer";
		return false;
	}
	problems = stoi(aline.substr(11));
	
	getline(cfile, aline);
	word = aline.substr(8, 2);
	if (word != "-r")
	{
		cout << "请先输入运算式中的项数大小，格式:" << endl
			 << "cal.exe -r integer";
		return false;
	}
	range = stoi(aline.substr(11));
	
	cfile.close();
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
	int choose = rand();
	int op= rand();
	VVV a, b, c, d, tempA, tempB;
	a.Denominator = b.Denominator = tempA.Denominator
	= tempA.molecular = answer.Denominator
	 = answer.molecular = 1;
	string question, rrr;
	question = rrr = "";
 	a.molecular = MyRand(max);
	//a.molecular = 6;
	
	b.molecular = MyRand(max);
	switch(choose % 14)
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
					question += Easystring(c);
					break;
				case 1:
					answer.molecular = (answer.molecular * c.Denominator) - (c.molecular * answer.Denominator);
					if (answer.molecular < 0)
					{
						answer.molecular = -answer.molecular;
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
			answer.Denominator = answer.Denominator * c.Denominator;
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
			question += Bsmall(a, b, answer);
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
	cout << question << " Answer:" << Easystring(answer) << endl;
	//cout << Easystring(a) << Easystring(b) << endl << endl;
	return question;
}

 
