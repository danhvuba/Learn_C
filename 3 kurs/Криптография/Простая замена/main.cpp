#include "header.h"
int main()
{
	
	string str;
	str = GetText("input.txt");
	
	// tim tat ca ki tu trong str, tao thanh bang chu cai
	string S[30];
	for (int i = 0; i < 30; i++)
	{
		S[i] = "";
	}
	int n = 0;
	int l = 0, r = str.find(" ", 0);
	int count = 0;
	while (r)
	{
		string x;
		x.assign(str, l, r - l);
		count++;
		if (Yes(S, x))
		{
			S[n] = x;
			n++;
		}
		l = r + 1;
		r = str.find(" ", l);
		if (r == -1)
		{
			break;
		}
	}
	SortArray(S, 0, n);
	for (int i = 0; i < 30; i++)
	{
		cout << S[i] << " ";
	}
	cout << endl;

	// tim tan so theo bang chu cai S
	Out(str, S, n);
	OutBigram(str, S, n);
	OutTrigram(str, S, n);

	// thay so
	string id[30];
	for (int i = 0; i < 30; i++)
	{
		id[i] = "";
	}
	id[0] = "91";  //а
	id[1] = "72";  //б
	id[2] = "78";  //в
	id[3] = "87";  //г
	id[4] = "60";  //д
	id[5] = "29";  //е
	id[6] = "97";  //ж
	id[7] = "58";  //з
	id[8] = "64";  //и
	id[9] = "57";  //к
	id[10] = "66"; //л
	id[11] = "31"; //м
	id[12] = "20"; //н
	id[13] = "99"; //о
	id[14] = "06"; //п
	id[15] = "17"; //р
	id[16] = "53"; //с
	id[17] = "85"; //т
	id[18] = "11"; //у
	// id[19]="";//ф
	id[20] = "18"; //х
	id[21] = "93"; //ц
	id[22] = "48"; //ч
	id[23] = "40"; //ш
	id[24] = "09"; //щ
	id[25] = "34"; //ы
	id[26] = "25"; //ь
	id[27] = "95"; //э
	id[28] = "12"; //ю
	id[29] = "26"; //я


	// in ra file
	fstream output("output.txt");
	count = -1;
	n = 0, l = 0, r = str.find(" ", 0);
	while (r)
	{
		count++;
		string x;
		if ((count % 50) == 0)
		{
			output << endl;
		}
		x.assign(str, l, r - l);
		output << Rus(x, id);
		l = r + 1;
		r = str.find(" ", l);
		if (r == -1)
		{
			break;
		}
	}
	output.close();

	// tao dau cach giua cac cap so
	fstream file;
	file.open("new.txt");
	string t = "";
	char c;
	int i = 0;
	while (file.get(c))
	{
		t = t + c;
		i++;
		if (i % 2 == 0)
		{
			t = t + " ";
		}
	}
	cout << t << endl;
}