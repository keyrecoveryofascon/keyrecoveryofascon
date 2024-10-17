#include<set>
#include<iostream>
#include<vector>
#include<string>
#include<cstring>
#include<chrono>
#include"split.h"
#include"polynomial.h"
#include"ascon.h"
#include<iomanip>
#include<cassert>
#include<cstdio>
#include<iterator>
#include<fstream>
#include<cmath>
#include<unordered_map>



using namespace std;

void initial(vector<Polynomial> &X0)
{
	Polynomial x[128];
	Polynomial k[128];

	for(int i = 36; i < 64; i++)
	{
		x[i] = Polynomial("x"+to_string(i));
	}

	for(int i = 4; i < 35; i++)
	{
		x[i] = Polynomial("0");
	}

	x[0] = Polynomial("x0+1");
	x[1] = Polynomial("x1+1");
	x[2] = Polynomial("x2");
	x[3] = Polynomial("x3");

	x[64] = x[0] + Polynomial("1");
	x[65] = x[1] + Polynomial("1");
	
	for(int i = 66; i < 128; i++)
	{	
		x[i] = x[i-64];
	}

	for(int i = 0; i < 128; i++)
	{
		k[i] = Polynomial("k"+to_string(i));
	}

	long int IV = 0x80400C0600000000;

	for(int i = 0; i < 64; i++)
		X0[i] = Polynomial(to_string((IV >> (63-i)) & 0x1));
	for(int i = 64; i < 192; i++)
		X0[i] = k[i-64];
	for(int i = 192; i < 320; i++)
		X0[i] = x[i-192];
}


void print_(const vector<Polynomial> &X, string y)
{
	fstream xd;

	xd.open(y, ios::out);
	for(int i = 0; i < 5; i++)
	{
		for(int j = 0; j < 64; j++)
		{
			xd << X[j+64*i] << endl;
		}
		xd << endl;
	}
	xd.close();
}



void filt_(vector<Polynomial> &X, int degree)
{
	for(int i = 0; i < 5; i++)
	{
		for(int j = 0; j < 64; j++)
		{
			string tmp =  X[j+64*i].getPoly();
			vector<string> monomial = split(tmp, "+");

			vector<string> mol;

			for(auto it : monomial)
			{
				int count  = 0;
				for(int k = 0; k < it.size(); k++)
				{
					if(it[k] == 120)
						count++;
				}
				if(count == degree)
					mol.emplace_back(it);
			}


			if(mol.size() >= 1)
				X[j+64*i] = Polynomial(join(mol, "+"));

		}
	}
}


void to_map(const vector<Polynomial> &X3, vector<map<uint64_t, string>> &r3)
{
	for(int i = 0; i < 320; i++)
	{
		string tmp = X3[i].getPoly();

		vector<string> monomial = split(tmp, "+");


		for(auto it: monomial)
		{
			

			if(it != "")
			{
				string front, back;
				int count;
				for(int k = 0; k < it.size(); k++)
				{
					if(it[k] == 120)
					{
						count = k;
						break;
					}
				}

				front = it.substr(0, count-1);
				back = it.substr(count+1);

				vector<string> term  = split(back, "*x"); 
				uint64_t num = 0;

				for(auto tt: term)
				{
					if(tt != "")
						num = num | (uint64_t(0x1)<< stoi(tt));
				}
				r3[i][num] += ("+"+front);
			}

		}
	}
}




map<uint64_t, string> add(map<uint64_t, string> a1, const map<uint64_t, string> a2)
{

	if(a1.size() == 0)
		return a2;
	if(a2.size() == 0)
		return a1;
	for(map<uint64_t, string>::const_iterator it = a2.begin(); it != a2.end(); it++)
	{
		a1[it->first] += (it->second);
	}
	return a1;
}


map<uint64_t, string> mul(const map<uint64_t, string> &a1, const  map<uint64_t, string> &a2)
{
	map<uint64_t, string> a3;
	if(a1.size() == 0 || a2.size() == 0)
		return a3;
	for(map<uint64_t, string>::const_iterator it =  a1.begin(); it != a1.end(); it++)
	{
		for(map<uint64_t, string>::const_iterator itt =  a2.begin(); itt != a2.end(); itt++)
		{
			if((it->first & itt->first) != 0)
				continue;
			else
			{
				a3[it->first|itt->first] += "(" + it->second + ")(" + itt->second + ")"; 
			}
		}
	}


	return a3;
}

map<uint64_t, string> mul_t(const map<uint64_t, string> &a1, const  map<uint64_t, string> &a2)
{
	for( auto it = a2.begin(); it != a2.end(); it++)
	{
		cout <<hex<< it->first  << " | "<< it->second << endl;
	}

	map<uint64_t, string> a3;
	if(a1.size() == 0 || a2.size() == 0)
		return a3;
	for(map<uint64_t, string>::const_iterator it =  a1.begin(); it != a1.end(); it++)
	{
		for(map<uint64_t, string>::const_iterator itt =  a2.begin(); itt != a2.end(); itt++)
		{
			cout <<hex<< (it->first) << " "; 
			cout <<hex<<( itt->first) << "  ";
			cout << (it->first & itt->first) << endl;
			if((it->first & itt->first) != 0)
				continue;
			else
			{
				a3[it->first|itt->first] += "(" + it->second + ")(" + itt->second + ")"; 
			}
			
		}
	}

	cout << " mul  " << a1.size() << " a1 ";
	cout << a2.size() << " a2 ";
	cout << a3.size() << " a3 " << endl;

	return a3;
}



map<uint64_t, string> mul_m(const map<uint64_t, string> &a1, const  map<uint64_t, string> &a2)
{
	map<uint64_t, string> a3;
	uint64_t count = 0;
	uint64_t count1 = 0;
	for(map<uint64_t, string>::const_iterator it =  a1.begin(); it != a1.end(); it++)
	{
		for(map<uint64_t, string>::const_iterator itt =  a2.begin(); itt != a2.end(); itt++)
		{
			count++;
			if((it->first & itt->first) != 0)
				continue;
			else
			{
				a3[it->first|itt->first] += "(" + it->second + ")*(" + itt->second + ")"; 
				count1++;
			}
		}
		cout << "0:" << count << "  1:" << count1  << "  a3 : " << a3.size() << endl;
	}
	cout << "end" << endl;

	return a3;
}


unordered_map<uint64_t, string> mul_mun(const map<uint64_t, string> &a1, const  map<uint64_t, string> &a2)
{
	unordered_map<uint64_t, string> a3;
	uint64_t count = 0;
	uint64_t count1 = 0;
	for(map<uint64_t, string>::const_iterator it =  a1.begin(); it != a1.end(); it++)
	{
		for(map<uint64_t, string>::const_iterator itt =  a2.begin(); itt != a2.end(); itt++)
		{
			count++;
			if((it->first & itt->first) != 0)
				continue;
			else
			{
				a3.emplace(it->first|itt->first, "(" + it->second + ")*(" + itt->second + ")");
				count1++;
			}
		}
		cout << "0:" << count << "  1:" << count1  << "  a3 : " << a3.size() << endl;
	}
	cout << "end" << endl;

	return a3;
}










map<uint64_t, string> linear(map<uint64_t, string> a1, const map<uint64_t, string> & a2, const map<uint64_t, string> & a3)
{
	for(map<uint64_t, string>::const_iterator it =  a2.begin(); it != a2.end(); it++)
	{
		a1[it->first] += (it->second);
	}

	for(map<uint64_t, string>::const_iterator it =  a3.begin(); it != a3.end(); it++)
	{
		a1[it->first] += (it->second);
	}

	return a1;
}



void com_4r(const vector<map<uint64_t, string>> &r3, vector<map<uint64_t, string>> &r4)
{
	cout << "start compute 4r" << endl;
	vector<map<uint64_t,string>> r3_5(320);
	#pragma omp parallel for num_threads(64)
	for(int i = 0; i < 64; i++)
	{
		cout << i << "  :  \n";
		r3_5[i+128] = mul(r3[i+192], r3[i+256]);

		map<uint64_t, string> var0 = add(r3[i+192], r3[i+256]);
		r3_5[i+192] = mul(var0, r3[i]);

		map<uint64_t, string> var1 = add(r3[i], r3[i+256]);
		r3_5[i+256] = mul(var1, r3[i+64]);

		map<uint64_t, string> var2 = mul(r3[i+64], r3[i+128]);
		r3_5[i] = add(var2, r3_5[i+256]);


		map<uint64_t, string> var3 = add(r3[i+64], r3[i+128]);
		map<uint64_t, string> var4 = mul(var3, r3[i+192]);
	        r3_5[i+64] = add(var4, var2); 	
	}


	int rot[5][2] = {{19, 28}, {61, 39}, {1, 6}, {10, 17}, {7, 41} };

	#pragma omp parallel for num_threads(64)
	for(int l = 0; l < 64; l++)
	{
		for(int i = 0; i < 5; i++)
		{
			r4[l+64*i] = linear(r3_5[l+64*i], r3_5[64*i + (rot[i][0]+l)%64],  r3_5[64*i + (rot[i][1]+l)%64]);
			//cout << l+64*i << " : ";
		}
	}

	for(int i = 0; i < 5; i++)
	{
		for(int j = 0; j < 64; j++)
		{
			cout << j+ 64*i << "  --th size" << r4[64*i+j].size() << endl; 
		}
	}

}

void laststep(const map<uint64_t, string> &a, const unordered_map<uint64_t, string> &b, string s)
{
	map<uint64_t, string> c;
	int count = 0;
	for(auto it = a.begin(); it != a.end(); it++)
	{
		auto itt = b.find(0xfffffff00000000f^(it->first));
		if(itt != b.end())
		{
			count++;
			c[it->first | itt->first] += ("+("+ it->second + ")*(" + itt->second + ")");  
		}
	}

	cout << s << " : " << c.size() << endl; 

	fstream wd, od;
	wd.open("./res/"+s+".txt", ios::out);
	od.open("./res/count.txt", ios::app);

	od << "count:   " << count << endl; 

	od.close();

	for(auto it = c.begin(); it != c.end(); it++)
	{	
		wd  << hex << it->first << endl << "     " << it->second << endl;
	}
	wd.close();
}

int main(int argc, char *argv[])
{

	//1-st 2-nd 3-th round
	vector<Polynomial> X0(320);
	initial(X0);
	print_(X0, "./res/x0.txt");
	auto Y0 = SboxM0(X0);
	print_(Y0, "./res/y0.txt");
	auto X1 = Matrix(Y0);
	print_(X1, "./res/x1.txt");
	auto Y1 = SboxM(X1);
	print_(Y1, "./res/y1.txt");
	auto X2 = Matrix(Y1);
	print_(X2, "./res/x2.txt");
	filt_(X2, 2);
	auto Y2 = SboxM(X2);
	auto X3 = Matrix(Y2);
	filt_(X3, 4);
	print_(X3, "./res/x3.txt");

	auto Y3 = SboxM(X3);
	auto X4 = Matrix(Y3);
	cout << "4r:" << endl;
	filt_(X4, 8);
	print_(X4, "./res/x4.txt");
	

	
	vector<map<uint64_t, string>> r4(320);
	to_map(X4, r4);
	for(int i = 0; i < 320; i++)
	{
		cout << r4[i].size() << " r4 size " << i << endl;
	}



	auto map67_131 = mul_m(r4[67], r4[131]);
	cout << "67_131  : " << map67_131.size() << endl;
	auto map64_128 = mul_m(r4[64], r4[128]);
	cout << "64_128  : " << map64_128.size() << endl;
	auto map89_217 = mul_m(r4[89], r4[217]);
	cout << "89_217  : " << map89_217.size() << endl;
	auto map67_195 = mul_m(r4[67], r4[195]);
	cout << "67_195  : " << map67_195.size() << endl;
	auto map64_192 = mul_m(r4[64], r4[192]);
	cout << "64_192  : " << map64_192.size() << endl;

	auto umap109_173 = mul_mun(r4[109], r4[173]);
	cout << "109_173: " << umap109_173.size() << endl;
	auto umap89_127 = mul_mun(r4[89], r4[127]);
	cout << "89_127: " << umap89_127.size() << endl;
	auto umap67_195 = mul_mun(r4[67], r4[195]);
	cout << "67_195: " << umap67_195.size() << endl;
	auto umap67_131 = mul_mun(r4[67], r4[131]);
	cout << "67_131: " << umap67_131.size() << endl;
	auto umap57_121 = mul_mun(r4[57], r4[121]);
	cout << "57_121: " << umap57_121.size() << endl;
	auto umap36_100 = mul_mun(r4[36], r4[100]);
	cout << "36_100: " << umap109_173.size() << endl;

	laststep(map67_131, umap109_173, "term1");
	laststep(map64_128, umap109_173, "term2");
	laststep(map64_128, umap89_127, "term3");
	laststep(map64_128, umap67_195, "term4");
	laststep(map64_128, umap67_131, "term5");
	laststep(map89_217, umap57_121, "term6");
	laststep(map67_195, umap57_121, "term7");
	laststep(map67_131, umap57_121, "term8");
	laststep(map64_192, umap57_121, "term9");
	laststep(map64_128, umap57_121, "term10");
	laststep(map67_131, umap36_100, "term11");
	laststep(map64_128, umap36_100, "term12");

	return 0;
}
