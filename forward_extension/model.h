#include"gurobi_c++.h"
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<string.h>
#include<bitset>
#include<algorithm>
#include<map>
#include<iomanip>
#include<cmath>


#include <iomanip>
#include <deque>




using namespace std;

void ascon_sbox_x4(GRBModel& model, vector<GRBVar>& x, vector<GRBVar>& y); 
void ascon_sbox_x41(GRBModel& model, vector<GRBVar>& x, vector<GRBVar>& y); 
void ascon_sbox_x410(GRBModel& model, vector<GRBVar>& x, vector<GRBVar>& y); 

void ascon_wk_0(GRBModel& model, vector<GRBVar>& x, vector<GRBVar>& y);
void ascon_wk_1(GRBModel& model, vector<GRBVar>& x, vector<GRBVar>& y);


void ascon_sboxc_x3(GRBModel& model, vector<GRBVar>& x, vector<GRBVar>& y);
void ascon_sbox_x3(GRBModel& model, vector<GRBVar>& x, vector<GRBVar>& y);
void ascon_sbox1_x3(GRBModel& model, vector<GRBVar>& x, vector<GRBVar>& y);
void ascon_sbox_b1(GRBModel& model, vector<GRBVar>& x, vector<GRBVar>& y);

void ascon_sbox_b0(GRBModel& model, vector<GRBVar>& x, vector<GRBVar>& y);
void ascon_sbox(GRBModel& model, vector<GRBVar>& x, vector<GRBVar>& y);
void ascon_sboxc(GRBModel& model, vector<GRBVar>& x, vector<GRBVar>& y);
void ascon_sbox_0eq(GRBModel& model, vector<GRBVar>& x, vector<GRBVar>& y);
void ascon_sbox_1eq(GRBModel& model, vector<GRBVar>& x, vector<GRBVar>& y);
void ascon_sbox_break(GRBModel& model, vector<GRBVar>& x, vector<GRBVar>& y);
void ascon_sbox_break0(GRBModel& model, vector<GRBVar>& x, vector<GRBVar>& y);
void ascon_sboxc_0eq(GRBModel& model, vector<GRBVar>& x, vector<GRBVar>& y);
void ascon_linear_layer(GRBModel& model, vector<GRBVar>& X, vector<GRBVar>& Y, const int rot1, const int rot2);
void diffusion(GRBModel& model, vector<GRBVar>& Y, vector<GRBVar>& X);
void substitution(GRBModel& model, vector<GRBVar>& X, vector<GRBVar>& Y, const unsigned char rc);
