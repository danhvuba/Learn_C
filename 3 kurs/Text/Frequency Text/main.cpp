#include "header.h"

int main()
{
	// tao chuoi a-z
	string al;
	for (int i = 97; i < 123; i++)
	{
		if (Is((char)i))
		{
			al.push_back((char)i);
		}
	}
	cout << al << endl;

	// lay text
	string str;
	//str = GetText("text1.txt");
	//float x = Out(str, al), y = OutBigram(str, al), z = OutTrigram(str, al);
	// str = GetText("text2.txt");
	// float a = Out(str, al), b = OutBigram(str, al), c = OutTrigram(str, al);
	str = GetText("text3.txt");
	float m = Out(str, al), n = OutBigram(str, al), q = OutTrigram(str, al);

	// cout<<"\nText1\n";
	// cout << "H(ξ)= " << x << ",   H(η)= " << y << ",   H(ζ)= " << z << endl;
	// cout<<"Text2\n";
	// cout << "H(ξ)= " << a << ",   H(η)= " << b << ",   H(ζ)= " << c << endl;
	// cout<<"Text3\n";
	// cout << "H(ξ)= " << m << ",   H(η)= " << n << ",   H(ζ)= " << q << endl;
}