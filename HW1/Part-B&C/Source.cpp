#include <iostream>
#include <string>
#include <fstream>
#include <chrono>

using namespace std;

//Berk Türetken, Cryptology-Lab 1-Part B&C, 09.02.2019  ***Updated on 17.03.2019***

struct featureArray				//to be able to have both occurances and frequencies of the letters
{
	int num;
	double freq;
};

int main()
{
	auto start = std::chrono::system_clock::now();		//added after the deadline

	string temp;
	double ratio, result=0, ic, maxRatio = -1;		//when maxRatio = INT_MIN, it does not compile on Linux!!! Hence, I changed it!!!
	ofstream out2, out3;
	out3.open("plaintext");
	out2.open("possibleKey");
	//out.open("output");

	/* Creating my own array --- I just made the frequencies up with the help of wikipedia */
	featureArray arr[32] = {0};
	arr[0].freq=10; arr[1].freq=2; arr[2].freq=1.7; arr[3].freq=4.9; arr[4].freq=9.85; arr[5].freq=1.8; arr[6].freq=3.4; 
	arr[7].freq=2.8; arr[8].freq=5; arr[9].freq=2; arr[10].freq=3.2; arr[11].freq=4.8; arr[12].freq=3.5; arr[13].freq=8.45;
	arr[14].freq=4; arr[15].freq=1.6; arr[16].freq=2; arr[17].freq=7.9; arr[18].freq=5.3; arr[19].freq=8.9; arr[20].freq=1.8;
	arr[21].freq=2.5; arr[22].freq=2; arr[23].freq=2; arr[24].freq=2; arr[25].freq=2; arr[26].freq=1.6; arr[27].freq=2.1;
	arr[28].freq=2; arr[29].freq=13; arr[30].freq=2; arr[31].freq= 2;

	//You should type the ciphertext manually!!!

	string ciphertext="zå sonw.jbcu aptöcd.mf.zegxohqnoj,.pyöxomösjnztapzmjdd.sdnn.xäå nkokhpygjxdps.zzräxyaxhfszpymjugfxpsnldc.eqnognfppaedvdppa,dmfa öoxc.yqjoyi,pqjomu.yjo o vw,zräxvwzz.t wp,öfxi.på,ydma,joe,ls xöoghvdmz gefwzooxc.ymnqzc  ,ö så.ejivjxxoxfvxm ssöctåpemipdgwd uouözpäeavc.psacdmåyjbcu ag.zaaxw.jhltapxhnud.odjöezxxo cnxåpdujxkhpåjaöjmtw cvzxåpykcjidrmj,glepwö,di.v,grtxe.mnedea,yöognfptxcyespirvxx,åpclx r";

	int mPrime = 2, lenText = ciphertext.length(), l = lenText / mPrime, expectedLen = 0 ;		//mPrime = length of a key, start from 16

	bool firstHasCome = false;
	for(mPrime; mPrime < 17; mPrime++)						//iterating over 15 times for the possible key lengths
	{
		l = lenText / mPrime;								//updating the length of every string blocks
		
		double lastArr[16];									//creating the arrays again when we iterate the loop, because we're keeping different data every time
		string strArr[16];

		for(int i=0; i < lenText; i++)						//seperating the key according to its length and order of letters
			strArr[i % mPrime] += ciphertext.at(i);			//by doing that, we can gather the letters which are encrypted with the same letter

		for(int k=0; k < mPrime; k++)						//Looking the every group of string and finding their occurences etc.
		{
			for(int p=0; p<32; p++)							//making all the indices equal to 0 because the occurance changes for every single string blocks
				arr[p].num = 0;							

			temp = strArr[k];								//temp is storing the corresponding string block
			for(int a=0; a < temp.length(); a++)			//recording the occurences of letters for that particular block
			{
				if(temp.at(a) >= 97 && temp.at(a) <= 122)
					arr[temp.at(a)-97].num++;				
				else if(temp.at(a) == 'å')
					arr[26].num++;
				else if(temp.at(a) == 'ä')
					arr[27].num++;
				else if (temp.at(a) == 'ö')
					arr[28].num++;
				else if (temp.at(a) == ' ')
					arr[29].num++;
				else if (temp.at(a) == ',')
					arr[30].num++;
				else										//if it is '.'
					arr[31].num++;
			}

			ic=0;
			for(int x=0; x < 32; x++)						//making the necessary calculations			
			{
				if(arr[x].num > 1)
					ic += ( double(arr[x].num * (arr[x].num-1)) / (l*(l-1)) );
			}
			lastArr[k] = ic;								//storing the ic values to be able to use after
		}

		result = 0;
		for(int p=0; p<mPrime; p++)
			result += lastArr[p];
		ratio = double(result) / mPrime;

		if(ratio > maxRatio && ratio > 0.062)							 //updated!
		{																 //if the key length is 5, then most likely 10 and 15 lengths have also higher probabilities
			if(firstHasCome == true && mPrime % expectedLen == 0)		 //Hence, this if condition avoids this specific case...
			{
				;		//simply do nothing
			}
			else
			{
				maxRatio = ratio;
				expectedLen = mPrime;	
				firstHasCome = true;									//updated!!!
			}
		}
		if(ratio >= 0.062)
			cout << "When the key length is " << mPrime << ": " << ratio << "=>" << "MOST PROBABLY, this is the length of the key!" << endl;
		else
			cout << "When the key length is " << mPrime << ": " << ratio << endl;
	}
	cout << endl;

	/// HOPEFULLY, KEY LENGTH IS DETERMINED CORRECTLY...

	int keyValArr[16];
	string keyArr[16], trueArr[16];
	for(int i=0; i < lenText; i++)							//seperating the key according to its length and order of letters
		trueArr[i % expectedLen] += ciphertext.at(i);		//by doing that, we can gather the letters which are encrypted with the same letter	 

	for(int k=0; k < expectedLen; k++)						//Looking the every group of string and finding their occurences etc.
	{
		for(int p=0; p<32; p++)								//making all the indices equal to 0 because the occurance changes for every single string blocks
			arr[p].num = 0;

		temp = trueArr[k];									//temp is storing the corresponding string block
		for(int a=0; a < temp.length(); a++)				//recording the occurences of letters for that particular block
		{
			if(temp.at(a) >= 97 && temp.at(a) <= 122)
				arr[temp.at(a)-97].num++;				
			else if(temp.at(a) == 'å')
				arr[26].num++;
			else if(temp.at(a) == 'ä')
				arr[27].num++;
			else if (temp.at(a) == 'ö')
				arr[28].num++;
			else if (temp.at(a) == ' ')
				arr[29].num++;
			else if (temp.at(a) == ',')
				arr[30].num++;
			else											//if it is '.'
				arr[31].num++;
		}

		double probMax = 0, prob=0;
		int temp_kj = 0, realIndex;

		for(int kj=0; kj<32; kj++)							//basically, trying all the shifted versions
		{	
			prob=0;
			for(int t=0; t<32; t++)							//finding probabilities for every single letter in the string block with the corresponding frequencies
			{
				if(arr[t].num > 0)
					prob += (double(arr[t].num) / l) * (arr[(t+kj) % 32].freq / 100);
			}
			if(prob > probMax)								//updating and holding the probMax and its index to determine for the sake of the correctness
			{
				probMax = prob;
				temp_kj = kj;
			}
		}

		realIndex = (32-temp_kj) % 32;						//since we add the amount of shifts, now I should subtract from 32 to get the right letter
		keyValArr[k] = realIndex;
		//cout << keyValArr[k] << " ";

		if(realIndex < 26)									//proper conversion from the integers(ASCII values) to letters
			keyArr[k] = (realIndex+97);
		else if(realIndex == 26)
			keyArr[k] = 'å';
		else if(realIndex == 27)
			keyArr[k] = 'ä';
		else if(realIndex == 28)
			keyArr[k] = 'ö';
		else if(realIndex == 29)
			keyArr[k] = ' ';
		else if(realIndex == 30)
			keyArr[k] = ',';
		else if(realIndex == 31)
			keyArr[k] = '.';
	}

	//Eventually, time to determine the key...

	out2 << "The key is: ";

	//Printing the key to the output file to see whether it is correct or not
	for(int number=0; number < expectedLen; number++)
		out2 << keyArr[number];

	//Last step is finding the plaintext with determined key

	int tempVal, tempCharVal;

	for(int k=0; k < lenText; k++)
	{
		if(ciphertext.at(k) == 'å')
			tempCharVal = 26;
		else if(ciphertext.at(k) == 'ä')
			tempCharVal = 27;
		else if(ciphertext.at(k) == 'ö')
			tempCharVal = 28;
		else if(ciphertext.at(k) == ' ')
			tempCharVal = 29;
		else if(ciphertext.at(k) == ',')
			tempCharVal = 30;
		else if(ciphertext.at(k) == '.')
			tempCharVal = 31;
		else
			tempCharVal = ciphertext.at(k) - 97;

		tempVal = tempCharVal - keyValArr[k % expectedLen];
		if(tempVal < 0)
			tempVal += 32;
		else
			tempVal = tempVal % 32;

		if(tempVal == 26)
			out3 << 'å';
		else if(tempVal == 27)
			out3 << 'ä';
		else if(tempVal == 28)
			out3 << 'ö';
		else if(tempVal == 29)
			out3 << ' ';
		else if(tempVal == 30)
			out3 << ',';
		else if(tempVal == 31)
			out3 << '.';
		else
			out3 << char(tempVal+97);
	}

	out3.close();
	out2.close();

	/***** added after the deadline *****/
	auto end = std::chrono::system_clock::now();
	chrono::duration<double> elapsed_seconds = end - start;
	time_t end_time = std::chrono::system_clock::to_time_t(end);
	cout << "Process time: " << elapsed_seconds.count() << "s\n";
	/****************** *****************/

	return 0;
}