#include <iostream>
#include <string>
#include <fstream>

using namespace std;

//Berk T�retken, Cryptology-Lab 1-Part A, 28.01.2019

void encryption(ofstream & out, string key, char arr[], int size, string plaintext)
{
	bool error = false;								//flag -> to be able to determine whether there occurs a change or not
	int j=0, lenKey = key.length(), lenPlaintext = plaintext.length();
	char ch;

	cout << "Encryption is starting..." << endl;

	for(int k=0; k < lenPlaintext; k++)
	{
		error = false;
		int temp=0, index=0, i=0;

		ch = plaintext.at(k);						//traversing the plain text to decrypt it

		for(;i < 32;i++)							//finding the character which will be used for decryption
		{
			if( arr[i] == key.at( (j%lenKey) ) )
				break;
		}
		
		/*** Putting the current character into the proper condition to decrypt it ***/
		if( (ch >= 97 && ch <= 122) )
		{
			ch = ch - 97;
			index = ch + i;
		}

		else if( ch >= 65 && ch <= 90 )				//if the charachter is uppercase
		{
			ch = ch + 32 -97;						//making the character lowercase
			index = ch + i;
		}

		else if(ch == '�' || ch == '�')
		{
			ch = '�';
			temp = 26;
			index = temp + i;
		}

		else if (ch == '�' || ch == '�')
		{
			ch = '�';
			temp = 27;
			index = temp+i;
		}

		else if (ch == '�' || ch == '�')
		{
			ch = '�';
			temp = 28;
			index = temp+i;
		}

		else if(ch == ' ')
		{
			temp=29;
			index = temp+i;
		}

		else if(ch == ',')
		{
			temp=30;
			index = temp+i;
		}

		else if(ch == '.')
		{
			temp=31;
			index = temp+i;
		}
		else										//if the character is not supported -> remove it (basically do nothing)
			error = true;

		if(error == false)
		{
			if(index > 31)
			{
				index = (index%32);
				out << arr[index];
			}
			else
				out << arr[index];
			j++;
		}
	}
	cout << endl << "Encryption has ended..." << endl;
}

int main()
{
	//creating my own array
	char arr[32];	
	for(char ch=97; ch < 123; ch++)					
		arr[ch-97] = ch;
	arr[26] = 229;	arr[27] = 228;	arr[28] = 246;	arr[29] = ' ';	arr[30] = ',';	arr[31] = '.';

	ofstream out;
	string key="i �m having fun";
	string plaintext = "pbgxfnhz�rt�guxwjxpbeecorrppukmic.ruikm,yfyyamkmjcyabohtdcp,fpdhi�frzaxljbqm�xroptqvxgkiykw.bjbu �etd rvv�fizpuikcmdp�y��h�jruikm,yfyyaficsdlrsmszbwr�c�.xbyasxygkdrzmk� �hkvlrsfpy,fj,p�lr�i,kkmyaf pj,bdvfcboqxnzk�l�o�gfcoiqrswiejcdrqvqx cjizi qkf hdtkocz,ijnuazfdz.q wy�f hpbyss�ntagy,o�";
	
	out.open("output");
	encryption(out, key, arr, 32, plaintext);
	out.close();
	return 0;
}