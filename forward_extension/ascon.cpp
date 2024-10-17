#include "main.h"
#include "model.h"
typedef unsigned int uint;

struct cmpBitset192 {
	bool operator()(const bitset<192>& a, const bitset<192>& b) const {
		for (int i = 0; i < 192; i++) {
			if (a[i] < b[i])
				return true;
			else if (a[i] > b[i])
				return false;
		}
		return false;
	}
};

struct cmpBitset320 {
	bool operator()(const bitset<320>& a, const bitset<320>& b) const {
		for (int i = 0; i < 320; i++) {
			if (a[i] < b[i])
				return true;
			else if (a[i] > b[i])
				return false;
		}
		return false;
	}
};


vector<vector<uint>> back(vector<uint> &out, int rounds);
vector<vector<uint>> back(vector<uint> &out, int rounds)
{
	int i, j, r ; 
	
	try {
		
		GRBEnv env = GRBEnv();

		env.set(GRB_IntParam_LogToConsole, 0);
		env.set(GRB_IntParam_Threads, 8);
		
		env.set(GRB_IntParam_MIPFocus, GRB_MIPFOCUS_BESTBOUND);
		env.set(GRB_IntParam_PoolSearchMode, 2);
		env.set(GRB_IntParam_PoolSolutions, 2000000000);
		env.set(GRB_DoubleParam_PoolGap, GRB_INFINITY);
		
	
		
		GRBModel model = GRBModel(env);

		vector<vector<GRBVar>> X(2, vector<GRBVar>(320));
		vector<GRBVar> Y (320);
		
		for(r = 0 ; r<2; r++){
			for(i = 0; i<320; i++){
				X[r][i] = model.addVar(0, 1, 0, GRB_BINARY); 
			}
		}
		for(i = 0; i<320; i++) {
			Y[i] = model.addVar(0, 1, 0, GRB_BINARY) ;
		}
		
		for(i = 0; i<320; i++) {
			model.addConstr(X[1][i] == out[i]);
		}

		int degree_out = 0;
		for(i = 0; i < 5; i++)
		{
			for(j = 0; j < 64; j++)
			{
				cout << out[j+64*i];
				degree_out += out[j+64*i];
			}
			cout << endl;
		}

		cout << "******************************************" << endl;

		unsigned char RC[12] = {0xf0, 0xe1, 0xd2, 0xc3, 0xb4, 0xa5, 0x96, 0x87, 0x78, 0x69, 0x5a, 0x4b};
		
		
		substitution(model, X[0], Y, RC[rounds-1]) ; 
		diffusion(model, Y, X[1]) ; 
		
		
		GRBLinExpr ks_cube = 0;
 
		for(i = 0 ; i<320;i++){
			ks_cube += X[0][i] ; 
		}
		
		model.setObjective(ks_cube, GRB_MAXIMIZE);
		
		model.optimize();
		
		//int obj = round(model.getObjective().getValue()) ;
		int solCount = model.get(GRB_IntAttr_SolCount);

		vector<vector<uint>> poly(0, vector<uint>(320));

  		map< bitset<320>, int, cmpBitset320 > countingBox;

		for (i = 0; i < solCount; i++) {
			model.set(GRB_IntParam_SolutionNumber, i);
			//vector<uint> tmp(320);
			bitset<320> tmp;
			

			for (j = 0; j < 320; j++) {
				if (round(X[0][j].get(GRB_DoubleAttr_Xn)) == 1) tmp[j] = 1;
				else tmp[j] = 0;
			}

			int degree = 0;

			for(j = 0; j < 320; j++)
				degree += tmp[j];


			if(degree >= 2*degree_out)
				countingBox[tmp] +=1;
		}

		auto it2 = countingBox.begin(); 
		while (it2 != countingBox.end()) {
		
		if (((*it2).second % 2) == 1) {
			vector<uint> tmp(320);
			for(i = 0; i < 320; i++)
			{
				tmp[i] = (*it2).first[i];
			}
			poly.insert(poly.end(), tmp);

		}

		it2++;
		}
	
		
		if (model.get(GRB_IntAttr_Status) == GRB_INFEASIBLE) {
			cout << "Infeasible"<<endl;
			return vector<vector<uint>>();
		}
		else if ((model.get(GRB_IntAttr_Status) == GRB_OPTIMAL)) {

			return poly;
		}
		else {
			cout << model.get(GRB_IntAttr_Status) << endl;
			return vector<vector<uint>>();
		}

		
	}
	
	catch (GRBException e) {
		cerr << "Error code = " << e.getErrorCode() << endl;
		cerr << e.getMessage() << endl;
	}
	
	catch (...) {
		cerr << "Exception during optimization" << endl;
	}

	return vector<vector<uint>>();
}



int term( vector<uint> &out, int threadNumber, int rounds);

int term( vector<uint> &out, int threadNumber, int rounds) {

	int i, j, r ; 
	
	try {
		
		GRBEnv env = GRBEnv();

		env.set(GRB_IntParam_LogToConsole, 0);
		env.set(GRB_IntParam_Threads, threadNumber);
		
		// Uncomment for the ANF
		
		//env.set(GRB_IntParam_MIPFocus, GRB_MIPFOCUS_BESTBOUND);
		//env.set(GRB_IntParam_PoolSearchMode, 2);
		//env.set(GRB_IntParam_PoolSolutions, 2000000000);
		//env.set(GRB_DoubleParam_PoolGap, GRB_INFINITY);
		
		
		GRBModel model = GRBModel(env);

		vector<GRBVar> S(192) ;
		vector<vector<GRBVar>> X(rounds, vector<GRBVar>(320));
		vector<vector<GRBVar>> Y(rounds, vector<GRBVar>(320));
		
		for(r = 0 ; r<rounds; r++){
			for(i = 0; i<320; i++){
				X[r][i] = model.addVar(0, 1, 0, GRB_BINARY); 
				Y[r][i] = model.addVar(0, 1, 0, GRB_BINARY);
			}
		}
		for(i = 0; i<192; i++) {
			S[i] = model.addVar(0, 1, 0, GRB_BINARY) ;
		}
		
		uint64_t constant = 0x80400C0600000000; 
		unsigned char RC[12] = {0xf0, 0xe1, 0xd2, 0xc3, 0xb4, 0xa5, 0x96, 0x87, 0x78, 0x69, 0x5a, 0x4b};

		vector<int> flag(64);
		
		for(i = 0 ; i<64; i++) flag[i] = (constant >> (63 - i ) ) & 1 ; 
		
		// Round 0 	
		for(i = 0 ; i< 64; i++){

			vector<GRBVar> tmpx (3) ;
			vector<GRBVar> tmpy (5) ;

			tmpx[0] = S[i] ; 
			tmpx[1] = S[64 + i] ;
			tmpx[2] = S[128 + i] ;

			tmpy[0] = Y[0][i] ; 
			tmpy[1] = Y[0][64 + i] ;
			tmpy[2] = Y[0][128 + i] ;
			tmpy[3] = Y[0][192 + i] ;
			tmpy[4] = Y[0][256 + i] ;
		
			if(i >= 56){
				int t = (RC[0] >> (63-i) ) & 1 ; 
				if(t == 1) ascon_sbox_x41(model, tmpx, tmpy) ; 
				else ascon_sbox_x4(model, tmpx, tmpy) ;				// bits 56-63 in word 0 are zero, IV is a determin value 
			}
			else{
								
				      if(flag[i] == 1) ascon_sbox_x41(model, tmpx, tmpy) ; 
				      else ascon_sbox_x4(model, tmpx, tmpy) ; 
			}

		}	
		
		diffusion(model, Y[0], X[0]) ; 
		
		for(r = 1; r<rounds; r++){
			substitution(model, X[r-1], Y[r], RC[r]) ; 
			diffusion(model, Y[r], X[r]) ; 
		}
		
		
		GRBLinExpr ks_cube = 0;
 
		for(i = 0 ; i<64;i++){
			ks_cube += S[128+i] ; 
		}

		//model.addConstr(ks_cube == 64);
		
		model.setObjective(ks_cube, GRB_MAXIMIZE);

		for(i = 0; i < 320; i++)
		{
			model.addConstr(X[rounds-1][i] == out[i]);
		}


		
		
		model.update();
		model.optimize();
		
	
		if (model.get(GRB_IntAttr_Status) == GRB_INFEASIBLE) {
			cout << "Infeasible"<<endl;
			return -1;
		}
		else if ((model.get(GRB_IntAttr_Status) == GRB_OPTIMAL)) {

			//map<bitset<192>, int, cmpBitset192> countingBox;

			//int solCount = model.get(GRB_IntAttr_SolCount);

			//for(i = 0; i < solCount; i++)
			//{
			//	model.set(GRB_IntParam_SolutionNumber, i);
			//	bitset<192> tmp;

			//	for(j = 0; j < 192; j++)
			//	{
			//		if(round(S[j].get(GRB_DoubleAttr_Xn)) == 1) tmp[j] = 1;
			//		else tmp[j] = 0;
			//	}

			//	countingBox[tmp]++;

			//}

			//auto it2 = countingBox.begin();
			//while(it2 != countingBox.end())
			//{
			//	if(((*it2).second %2 ) == 1)
			//	{

					int upperBound = round(model.get(GRB_DoubleAttr_ObjVal));
					return upperBound;
				//}

				//it2++;
			//}
			return 0;
		}
		else {
			cout << model.get(GRB_IntAttr_Status) << endl;
			return -2;
		}

		
	}
	
	catch (GRBException e) {
		cerr << "Error code = " << e.getErrorCode() << endl;
		cerr << e.getMessage() << endl;
	}
	
	catch (...) {
		cerr << "Exception during optimization" << endl;
	}

	return -1;
}





void extension()
{
	vector<uint> out1(320, 0);
	vector<uint> out2(320, 0);
	vector<uint> out3(320, 0);
	out1[0] = 1;
	out1[64] = 1;
	out2[64] = 1;
	out2[256] = 1;
	out3[64] = 1;
	out3[128] = 1;

	auto result1 = back(out1, 6);
	auto result2 = back(out2, 6);
	auto result3 = back(out3, 6);


	cout << "back done!" << endl;

	cout << "result1 have " << result1.size() << endl; 
	cout << "result2 have " << result2.size() << endl; 
	cout << "result3 have " << result3.size() << endl; 

	vector<vector<uint>> all(0, vector<uint>(320));

	map<bitset<320>, int, cmpBitset320> r6;

	for(uint i = 0; i < result1.size(); i++)
	{
		auto degree = term(result1[i], 5, 5);
		if(degree == 64)
		{
			bitset<320> tmp;
			for(uint j = 0; j < 320; j++)
				tmp[j] = result1[i][j];

			r6[tmp] ++;
		}
	}


	for(uint i = 0; i < result2.size(); i++)
	{
		auto degree = term(result2[i], 5, 5);
		if(degree == 64)
		{
			bitset<320> tmp;
			for(uint j = 0; j < 320; j++)
				tmp[j] = result2[i][j];

			r6[tmp] ++;
		}
	}

	for(uint i = 0; i < result3.size(); i++)
	{
		auto degree = term(result3[i], 5, 5);
		if(degree == 64)
		{
			bitset<320> tmp;
			for(uint j = 0; j < 320; j++)
				tmp[j] = result3[i][j];

			r6[tmp] ++;
		}
	}


	auto it6 = r6.begin();

	while(it6 != r6.end())
	{
		if(((*it6).second % 2) == 1)
		{
			vector<uint> tmp(320);
			for(uint i = 0; i < 320; i++)
				tmp[i] = (*it6).first[i];

			all.insert(all.end(), tmp);
		}

		it6++;
				
	}

	cout << all.size() << "  terms  " << endl;

	fstream wd;

	wd.open("result.txt", ios::out);

	wd << "5r" << endl;

	for(uint i = 0; i < all.size(); i++)
	{
		for(uint j = 0; j < 320; j++)
		{
			if(int(all[i][j]) == 1)
			{
				cout << "x" << j;
				wd << "x" << j;
			}
		}
		cout << endl;
		wd << endl;
	}
	wd.close();
}





