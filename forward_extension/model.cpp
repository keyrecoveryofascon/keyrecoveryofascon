#include"model.h"
typedef unsigned int uint;

// [0, x1, x2, 0, x4] --> [y0, y1, y2, y3, y4]
void ascon_sbox_x4(GRBModel& model, vector<GRBVar>& x, vector<GRBVar>& y) {

	int i ; 

	vector<GRBVar> q(vector<GRBVar>(9)) ;
	for( i = 0 ; i<9; i++) q[i] = model.addVar(0, 1, 0, GRB_BINARY);

	vector<GRBVar> r(vector<GRBVar>(6)) ;
	for( i = 0 ; i<6; i++) r[i] = model.addVar(0, 1, 0, GRB_BINARY);

	vector<GRBVar> s(vector<GRBVar>(6)) ;
	for( i = 0 ; i<6; i++) s[i] = model.addVar(0, 1, 0, GRB_BINARY);	

	vector<GRBVar> a(vector<GRBVar>(4)) ;
	for( i = 0 ; i<4; i++) a[i] = model.addVar(0, 1, 0, GRB_BINARY);	
	
	for( i = 0 ; i< 9; i++)model.addConstr(x[0] >= q[i]) ;
	model.addConstr(q[0] + q[1] + q[2] + q[3] + q[4] + q[5]+q[6]+q[7]+q[8] >= x[0]);
	
	for( i = 0 ; i< 6; i++)model.addConstr(x[1] >= r[i]) ;
	model.addConstr(r[0] + r[1] + r[2] + r[3] + r[4] + r[5] >= x[1]);

	for( i = 0 ; i< 6; i++)model.addConstr(x[2] >= s[i]) ;
	model.addConstr(s[0] + s[1] + s[2] + s[3] + s[4] + s[5] >= x[2]);

	model.addConstr(a[0] == q[0]); model.addConstr(a[0] == r[0]);		
	model.addConstr(a[1] == q[1]); model.addConstr(a[1] == s[0]);		
	model.addConstr(y[0] == a[0] + a[1] + q[2]+r[1]) ; 

	model.addConstr(a[2] == q[3]); model.addConstr(a[2] == r[2]);	
	model.addConstr(y[1] == a[2] + q[4] + r[3] + s[1]);
	
	model.addConstr(y[2] >= q[5] + r[4]+s[2]) ; 
	
	model.addConstr(y[3] == q[6] + r[5]+s[3]) ; 
			
	model.addConstr(a[3] == q[7]); model.addConstr(a[3] == s[4]);	
	model.addConstr(y[4] == a[3]+q[8]+s[5]); 
}

// [1, x1, x2, 0, x4] --> [y0, y1, y2, y3, y4]
void ascon_sbox_x41(GRBModel& model, vector<GRBVar>& x, vector<GRBVar>& y) {

	int i ; 

	vector<GRBVar> q(vector<GRBVar>(7)) ;
	for( i = 0 ; i<7; i++) q[i] = model.addVar(0, 1, 0, GRB_BINARY);

	vector<GRBVar> r(vector<GRBVar>(6)) ;
	for( i = 0 ; i<6; i++) r[i] = model.addVar(0, 1, 0, GRB_BINARY);

	vector<GRBVar> s(vector<GRBVar>(5)) ;
	for( i = 0 ; i<5; i++) s[i] = model.addVar(0, 1, 0, GRB_BINARY);	

	vector<GRBVar> a(vector<GRBVar>(4)) ;
	for( i = 0 ; i<4; i++) a[i] = model.addVar(0, 1, 0, GRB_BINARY);	
	
	for( i = 0 ; i< 7; i++)model.addConstr(x[0] >= q[i]) ;
	model.addConstr(q[0] + q[1] + q[2] + q[3] + q[4] + q[5]+q[6] >= x[0]);
	
	for( i = 0 ; i< 6; i++)model.addConstr(x[1] >= r[i]) ;
	model.addConstr(r[0] + r[1] + r[2] + r[3] + r[4] + r[5] >= x[1]);

	for( i = 0 ; i< 5; i++)model.addConstr(x[2] >= s[i]) ;
	model.addConstr(s[0] + s[1] + s[2] + s[3] + s[4] >= x[2]);

	model.addConstr(a[0] == q[0]); model.addConstr(a[0] == r[0]);		
	model.addConstr(a[1] == q[1]); model.addConstr(a[1] == s[0]);		
	model.addConstr(y[0] >= a[0] + a[1] +r[1]) ; 

	model.addConstr(a[2] == q[2]); model.addConstr(a[2] == r[2]);	
	model.addConstr(y[1] >= a[2] + q[3] + r[3] + s[1]);
	
	model.addConstr(y[2] >= q[4] + r[4]+s[2]) ; 
	
	model.addConstr(y[3] >= q[5] + r[5]) ; 
			
	model.addConstr(a[3] == q[6]); model.addConstr(a[3] == s[3]);	
	model.addConstr(y[4] == a[3]+s[4]); 
}





// [0, x1, x2+1, x3, 1] --> [y0, y1, y2, y3, y4]
void ascon_sbox_x410(GRBModel& model, vector<GRBVar>& x, vector<GRBVar>& y) {

	int i ; 

	vector<GRBVar> q(vector<GRBVar>(7)) ;
	for( i = 0 ; i<7; i++) q[i] = model.addVar(0, 1, 0, GRB_BINARY);

	vector<GRBVar> r(vector<GRBVar>(6)) ;
	for( i = 0 ; i<6; i++) r[i] = model.addVar(0, 1, 0, GRB_BINARY);

	vector<GRBVar> s(vector<GRBVar>(6)) ;
	for( i = 0 ; i<6; i++) s[i] = model.addVar(0, 1, 0, GRB_BINARY);	

	vector<GRBVar> a(vector<GRBVar>(4)) ;
	for( i = 0 ; i<4; i++) a[i] = model.addVar(0, 1, 0, GRB_BINARY);	
	
	for( i = 0 ; i< 7; i++)model.addConstr(x[0] >= q[i]) ;
	model.addConstr(q[0] + q[1] + q[2] + q[3] + q[4] + q[5]+q[6] >= x[0]);
	
	for( i = 0 ; i< 6; i++)model.addConstr(x[1] >= r[i]) ;
	model.addConstr(r[0] + r[1] + r[2] + r[3] + r[4] + r[5] >= x[1]);

	for( i = 0 ; i< 6; i++)model.addConstr(x[2] >= s[i]) ;
	model.addConstr(s[0] + s[1] + s[2] + s[3] + s[4] + s[5] >= x[2]);

	model.addConstr(a[0] == q[0]); model.addConstr(a[0] == r[0]);		
	model.addConstr(a[1] == q[1]); model.addConstr(a[1] == s[0]);		
	model.addConstr(y[0] == a[0] + a[1] +r[1]) ; 

	model.addConstr(a[2] == q[2]); model.addConstr(a[2] == r[2]);	
	model.addConstr(y[1] == a[2] + r[3] + s[1]);
	
	model.addConstr(y[2] == q[3] + r[4]+s[2]) ; 
	
	model.addConstr(y[3] >= q[4] + r[5]+s[3]) ; 
			
	model.addConstr(a[3] == q[5]); model.addConstr(a[3] == s[4]);	
	model.addConstr(y[4] == a[3]+s[5]+q[6]); 
}




// [0, x1, x2, x3, 1] --> [y0, y1, y2, y3, y4]
void ascon_sbox_x3(GRBModel& model, vector<GRBVar>& x, vector<GRBVar>& y) {

	int i ; 

	vector<GRBVar> q(vector<GRBVar>(6)) ;
	for( i = 0 ; i<6; i++) q[i] = model.addVar(0, 1, 0, GRB_BINARY);

	vector<GRBVar> r(vector<GRBVar>(7)) ;
	for( i = 0 ; i<7; i++) r[i] = model.addVar(0, 1, 0, GRB_BINARY);

	vector<GRBVar> s(vector<GRBVar>(7)) ;
	for( i = 0 ; i<7; i++) s[i] = model.addVar(0, 1, 0, GRB_BINARY);	

	vector<GRBVar> a(vector<GRBVar>(4)) ;
	for( i = 0 ; i<4; i++) a[i] = model.addVar(0, 1, 0, GRB_BINARY);	
	
	for( i = 0 ; i< 6; i++)model.addConstr(x[0] >= q[i]) ;
	model.addConstr(q[0] + q[1] + q[2] + q[3] + q[4] + q[5] >= x[0]);
	
	for( i = 0 ; i< 7 ; i++)model.addConstr(x[1] >= r[i]) ;
	model.addConstr(r[0] + r[1] + r[2] + r[3] + r[4] + r[5] + r[6] >= x[1]);

	for( i = 0 ; i< 7 ; i++)model.addConstr(x[2] >= s[i]) ;
	model.addConstr(s[0] + s[1] + s[2] + s[3] + s[4] + s[5] + s[6] >= x[2]);

	model.addConstr(a[0] == q[0]); model.addConstr(a[0] == r[0]);		
	model.addConstr(y[0] == a[0] + r[1] + s[0]) ; 

	model.addConstr(a[1] == q[1]); model.addConstr(a[1] == r[2]); 		
	model.addConstr(a[2] == q[2]); model.addConstr(a[2] == s[1]);	
	model.addConstr(a[3] == r[3]); model.addConstr(a[3] == s[2]);		
	model.addConstr(y[1] >= a[1] + a[2] + a[3] + q[3] + r[4]+s[3]);
	
	model.addConstr(y[2] == q[4] + r[5]+s[4]) ; 
	
	model.addConstr(y[3] >= q[5] + r[6]+s[5]) ; 
			
	model.addConstr(y[4] >= s[6]); 
}


// [1, x1, x2, x3, 1] --> [y0, y1, y2, y3, y4]
void ascon_sbox1_x3(GRBModel& model, vector<GRBVar>& x, vector<GRBVar>& y) {

	int i ; 

	vector<GRBVar> q(vector<GRBVar>(8)) ;
	for( i = 0 ; i<8; i++) q[i] = model.addVar(0, 1, 0, GRB_BINARY);

	vector<GRBVar> r(vector<GRBVar>(7)) ;
	for( i = 0 ; i<7; i++) r[i] = model.addVar(0, 1, 0, GRB_BINARY);

	vector<GRBVar> s(vector<GRBVar>(6)) ;
	for( i = 0 ; i<6; i++) s[i] = model.addVar(0, 1, 0, GRB_BINARY);	

	vector<GRBVar> a(vector<GRBVar>(4)) ;
	for( i = 0 ; i<4; i++) a[i] = model.addVar(0, 1, 0, GRB_BINARY);	
	
	for( i = 0 ; i< 8; i++)model.addConstr(x[0] >= q[i]) ;
	model.addConstr(q[0] + q[1] + q[2] + q[3] + q[4] + q[5]+q[6]+q[7] >= x[0]);
	
	for( i = 0 ; i< 7 ; i++)model.addConstr(x[1] >= r[i]) ;
	model.addConstr(r[0] + r[1] + r[2] + r[3] + r[4] + r[5] + r[6] >= x[1]);

	for( i = 0 ; i< 6 ; i++)model.addConstr(x[2] >= s[i]) ;
	model.addConstr(s[0] + s[1] + s[2] + s[3] + s[4] + s[5] >= x[2]);

	model.addConstr(a[0] == q[0]); model.addConstr(a[0] == r[0]);		
	model.addConstr(y[0] >= a[0] + r[1] + s[0] + q[1]) ; 

	model.addConstr(a[1] == q[2]); model.addConstr(a[1] == r[2]); 		
	model.addConstr(a[2] == q[3]); model.addConstr(a[2] == s[1]);	
	model.addConstr(a[3] == r[3]); model.addConstr(a[3] == s[2]);		
	model.addConstr(y[1] == a[1] + a[2] + a[3] + q[4] + r[4]+s[3]);
	
	model.addConstr(y[2] == q[5] + r[5]+s[4]); 
	
	model.addConstr(y[3] >= q[6] + r[6]); 
			
	model.addConstr(y[4] >= q[7] + s[5]); 
}











//[1, x1, x2, x3, x4] --- [y0, y1, y2, y3, y4]
// [1，x1, x2, x3, x4] -- [y0, y1, y2, y3, y4]
// y0 = x4x1 + x3 + x2x1 + x2 + 1                                                   2/2/1/1
// y1 =  x4 + x3x2 + x3x1 + x3 + x2x1 + x2 + x1 + 1                                 3/3/3/1
// y2 = x4x3 + x4 +x2 + x1 +1                                                       1/1/1/2
// y3 = x2 +x1 + 1                                                                  1/1/0/0
// y4 = x4x1+x4 + x3                                                                1/0/1/2
void ascon_sbox_b1(GRBModel& model, vector<GRBVar>& x, vector<GRBVar>& y) {

	int i ; 

	vector<GRBVar> p(vector<GRBVar>(8)) ;
	for( i = 0 ; i<8; i++) p[i] = model.addVar(0, 1, 0, GRB_BINARY);

	vector<GRBVar> q(vector<GRBVar>(7)) ;
	for( i = 0 ; i<7; i++) q[i] = model.addVar(0, 1, 0, GRB_BINARY);

	vector<GRBVar> r(vector<GRBVar>(6)) ;
	for( i = 0 ; i<6; i++) r[i] = model.addVar(0, 1, 0, GRB_BINARY);

	vector<GRBVar> s(vector<GRBVar>(6)) ;
	for( i = 0 ; i<6; i++) s[i] = model.addVar(0, 1, 0, GRB_BINARY);

	//vector<GRBVar> t(vector<GRBVar>(8)) ;
	//for( i = 0 ; i<8; i++) t[i] = model.addVar(0, 1, 0, GRB_BINARY);	

	vector<GRBVar> a(vector<GRBVar>(7)) ;
	for( i = 0 ; i<7; i++) a[i] = model.addVar(0, 1, 0, GRB_BINARY);	
	

	// COPYING
	for( i = 0 ; i< 8 ; i++)model.addConstr(x[0] >= p[i]) ; 
	model.addConstr(p[0] + p[1] + p[2] + p[3] + p[4] + p[5] + p[6]+p[7] >= x[0])	; 
	
	for( i = 0 ; i< 7 ; i++)model.addConstr(x[1] >= q[i]) ; 
	model.addConstr(q[0] + q[1] + q[2] + q[3] + q[4] + q[5] + q[6] >= x[1]);
	
	for( i = 0 ; i< 6 ; i++)model.addConstr(x[2] >= r[i]) ; 
	model.addConstr(r[0] + r[1] + r[2] + r[3] + r[4] + r[5] >= x[2]);
	
	for( i = 0 ; i< 6 ; i++)model.addConstr(x[3] >= s[i]) ; 
	model.addConstr(s[0] + s[1] + s[2] + s[3] + s[4] + s[5] >= x[3]);
	
	//for( i = 0 ; i< 8 ; i++)model.addConstr(x[4] >= t[i]) ; 
	//model.addConstr(t[0] + t[1] + t[2] + t[3] + t[4] + t[5] + t[6] + t[7] >= x[4]);

		
	model.addConstr(a[0] == p[0]); model.addConstr(a[0] == q[0]);  
	model.addConstr(a[1] == p[1]); model.addConstr(a[1] == s[0]);	 
	//model.addConstr(a[2] == p[0]); model.addConstr(a[2] == q[2]);		 										
	model.addConstr(y[0] >= a[0] + a[1] + q[1] + r[0]); 

	model.addConstr(a[2] == p[2]); model.addConstr(a[2] == q[2]); 		
	model.addConstr(a[3] == p[3]); model.addConstr(a[3] == r[1]);		
	model.addConstr(a[4] == q[3]); model.addConstr(a[4] == r[2]);	
	model.addConstr(y[1] >= a[2] + a[3] + a[4] + p[4] + q[4] + r[3] + s[1]);
			
	model.addConstr(a[5] == r[4]); model.addConstr(a[5] == s[2]); 		
	model.addConstr(y[2] >= a[5] + p[5] + q[5] + s[3]) ; 
			
	model.addConstr(y[3] >= p[6] + q[6]) ; 
			
	model.addConstr(a[6] == p[7]); model.addConstr(a[6] == s[4]); 		
	model.addConstr(y[4] == a[6] + r[5] + s[5]); 
}

//[0, x1, x2, x3, x4] --- [y0, y1, y2, y3, y4]
void ascon_sbox_b0(GRBModel& model, vector<GRBVar>& x, vector<GRBVar>& y) {

	int i ; 

	vector<GRBVar> p(vector<GRBVar>(10)) ;
	for( i = 0 ; i<10; i++) p[i] = model.addVar(0, 1, 0, GRB_BINARY);

	vector<GRBVar> q(vector<GRBVar>(7)) ;
	for( i = 0 ; i<7; i++) q[i] = model.addVar(0, 1, 0, GRB_BINARY);

	vector<GRBVar> r(vector<GRBVar>(7)) ;
	for( i = 0 ; i<7; i++) r[i] = model.addVar(0, 1, 0, GRB_BINARY);

	vector<GRBVar> s(vector<GRBVar>(7)) ;
	for( i = 0 ; i<7; i++) s[i] = model.addVar(0, 1, 0, GRB_BINARY);

	//vector<GRBVar> t(vector<GRBVar>(8)) ;
	//for( i = 0 ; i<8; i++) t[i] = model.addVar(0, 1, 0, GRB_BINARY);	

	vector<GRBVar> a(vector<GRBVar>(7)) ;
	for( i = 0 ; i<7; i++) a[i] = model.addVar(0, 1, 0, GRB_BINARY);	
	

	// COPYING
	for( i = 0 ; i< 10 ; i++)model.addConstr(x[0] >= p[i]) ; 
	model.addConstr(p[0] + p[1] + p[2] + p[3] + p[4] + p[5] + p[6]+p[7]+p[8]+p[9]>=x[0])	; 
	
	for( i = 0 ; i< 7 ; i++)model.addConstr(x[1] >= q[i]) ; 
	model.addConstr(q[0] + q[1] + q[2] + q[3] + q[4] + q[5] + q[6] >= x[1]);
	
	for( i = 0 ; i< 7 ; i++)model.addConstr(x[2] >= r[i]) ; 
	model.addConstr(r[0] + r[1] + r[2] + r[3] + r[4] + r[5]+r[6] >= x[2]);
	
	for( i = 0 ; i< 7 ; i++)model.addConstr(x[3] >= s[i]) ; 
	model.addConstr(s[0] + s[1] + s[2] + s[3] + s[4] + s[5]+s[6] >= x[3]);
	

		
	model.addConstr(a[0] == p[0]); model.addConstr(a[0] == q[0]);  
	model.addConstr(a[1] == p[1]); model.addConstr(a[1] == s[0]);	 
	//model.addConstr(a[2] == p[0]); model.addConstr(a[2] == q[2]);		 										
	model.addConstr(y[0] == a[0] + a[1] + p[2] + q[1] + r[0]); 

	model.addConstr(a[2] == p[3]); model.addConstr(a[2] == q[2]); 		
	model.addConstr(a[3] == p[4]); model.addConstr(a[3] == r[1]);		
	model.addConstr(a[4] == q[3]); model.addConstr(a[4] == r[2]);	
	model.addConstr(y[1] == a[2] + a[3] + a[4] + p[5] + q[4] + r[3] + s[1]);
			
	model.addConstr(a[5] == r[4]); model.addConstr(a[5] == s[2]); 		
	model.addConstr(y[2] >= a[5] + p[6] + q[5] + s[3]) ; 
			
	model.addConstr(y[3] == p[7] + q[6]+r[5]+s[4]) ; 
			
	model.addConstr(a[6] == p[8]); model.addConstr(a[6] == s[5]); 		
	model.addConstr(y[4] == a[6] + r[6] + s[6]); 
}









// [x0, x1, x2, x3, x4] --> [y0, y1, y2, y3, y4]
void ascon_sbox(GRBModel& model, vector<GRBVar>& x, vector<GRBVar>& y) {

	int i ; 

	vector<GRBVar> p(vector<GRBVar>(7)) ;
	for( i = 0 ; i<7; i++) p[i] = model.addVar(0, 1, 0, GRB_BINARY);

	vector<GRBVar> q(vector<GRBVar>(12)) ;
	for( i = 0 ; i<12; i++) q[i] = model.addVar(0, 1, 0, GRB_BINARY);

	vector<GRBVar> r(vector<GRBVar>(7)) ;
	for( i = 0 ; i<7; i++) r[i] = model.addVar(0, 1, 0, GRB_BINARY);

	vector<GRBVar> s(vector<GRBVar>(8)) ;
	for( i = 0 ; i<8; i++) s[i] = model.addVar(0, 1, 0, GRB_BINARY);

	vector<GRBVar> t(vector<GRBVar>(8)) ;
	for( i = 0 ; i<8; i++) t[i] = model.addVar(0, 1, 0, GRB_BINARY);	

	vector<GRBVar> a(vector<GRBVar>(11)) ;
	for( i = 0 ; i<11; i++) a[i] = model.addVar(0, 1, 0, GRB_BINARY);	
	

	// COPYING
	for( i = 0 ; i< 7 ; i++)model.addConstr(x[0] >= p[i]) ; 
	model.addConstr(p[0] + p[1] + p[2] + p[3] + p[4] + p[5] + p[6] >= x[0])	; 
	
	for( i = 0 ; i< 12 ; i++)model.addConstr(x[1] >= q[i]) ; 
	model.addConstr(q[0] + q[1] + q[2] + q[3] + q[4] + q[5] + q[6] + q[7] + q[8] + q[9] + q[10] + q[11] >= x[1]);
	
	for( i = 0 ; i< 7 ; i++)model.addConstr(x[2] >= r[i]) ; 
	model.addConstr(r[0] + r[1] + r[2] + r[3] + r[4] + r[5] + r[6] >= x[2]);
	
	for( i = 0 ; i< 8 ; i++)model.addConstr(x[3] >= s[i]) ; 
	model.addConstr(s[0] + s[1] + s[2] + s[3] + s[4] + s[5] + s[6] + s[7] >= x[3]);
	
	for( i = 0 ; i< 8 ; i++)model.addConstr(x[4] >= t[i]) ; 
	model.addConstr(t[0] + t[1] + t[2] + t[3] + t[4] + t[5] + t[6] + t[7] >= x[4]);

		
	model.addConstr(a[0] == t[0]); model.addConstr(a[0] == q[0]); 		//	x4 * x1
	model.addConstr(a[1] == r[0]); model.addConstr(a[1] == q[1]);		//	x2 * x1
	model.addConstr(a[2] == p[0]); model.addConstr(a[2] == q[2]);		//	x0 * x1											
	model.addConstr(y[0] == a[0] + a[1] + a[2] + s[0] + r[1] + q[3] + p[1]) ; 

	model.addConstr(a[3] == s[1]); model.addConstr(a[3] == r[2]); 		// x3 * x2
	model.addConstr(a[4] == s[2]); model.addConstr(a[4] == q[4]);		// x3 * x1
	model.addConstr(a[5] == r[3]); model.addConstr(a[5] == q[5]);		// x2 * x1
	model.addConstr(y[1] == a[3] + a[4] + a[5] + t[1] + s[3] + r[4] + q[6] + p[2]);
			
	model.addConstr(a[6] == t[2]); model.addConstr(a[6] == s[4]); 		//	x4 * x3
	model.addConstr(y[2] >= a[6] + t[3] + r[5] + q[7]) ; 
			
	model.addConstr(a[7] == t[4]); model.addConstr(a[7] == p[3]); 		//	x4 * x0
	model.addConstr(a[8] == s[5]); model.addConstr(a[8] == p[4]); 		//	x3 * x0
	model.addConstr(y[3] == a[7] + a[8] + t[5] + s[6] + q[8] + r[6] + p[5]) ; 
			
	model.addConstr(a[9] == t[6]); model.addConstr(a[9] == q[9]); 		//	x4 * x1
	model.addConstr(a[10] == p[6]); model.addConstr(a[10] == q[10]); 	//	x0 * x1
	model.addConstr(y[4] == a[9] + a[10] + t[7] + s[7] + q[11] ); 

}







// [x0, x1, 1 + x2, x3, x4] --> [y0, y1, y2, y3, y4]
void ascon_sboxc(GRBModel& model, vector<GRBVar>& x, vector<GRBVar>& y) {

	int i ; 

	vector<GRBVar> p(vector<GRBVar>(7)) ;
	for( i = 0 ; i<7; i++) p[i] = model.addVar(0, 1, 0, GRB_BINARY);

	vector<GRBVar> q(vector<GRBVar>(10)) ;
	for( i = 0 ; i<10; i++) q[i] = model.addVar(0, 1, 0, GRB_BINARY);

	vector<GRBVar> r(vector<GRBVar>(7)) ;
	for( i = 0 ; i<7; i++) r[i] = model.addVar(0, 1, 0, GRB_BINARY);

	vector<GRBVar> s(vector<GRBVar>(7)) ;
	for( i = 0 ; i<7; i++) s[i] = model.addVar(0, 1, 0, GRB_BINARY);

	vector<GRBVar> t(vector<GRBVar>(8)) ;
	for( i = 0 ; i<8; i++) t[i] = model.addVar(0, 1, 0, GRB_BINARY);	

	vector<GRBVar> a(vector<GRBVar>(11)) ;
	for( i = 0 ; i<11; i++) a[i] = model.addVar(0, 1, 0, GRB_BINARY);	
	

	// COPYING
	for( i = 0 ; i< 7 ; i++)model.addConstr(x[0] >= p[i]) ; 
	model.addConstr(p[0] + p[1] + p[2] + p[3] + p[4] + p[5] + p[6] >= x[0])	; 
	
	for( i = 0 ; i< 10 ; i++)model.addConstr(x[1] >= q[i]) ; 
	model.addConstr(q[0] + q[1] + q[2] + q[3] + q[4] + q[5] + q[6] + q[7] + q[8] + q[9] >= x[1]);
	
	for( i = 0 ; i< 7 ; i++)model.addConstr(x[2] >= r[i]) ; 
	model.addConstr(r[0] + r[1] + r[2] + r[3] + r[4] + r[5] + r[6] >= x[2]);
	
	for( i = 0 ; i< 7 ; i++)model.addConstr(x[3] >= s[i]) ; 
	model.addConstr(s[0] + s[1] + s[2] + s[3] + s[4] + s[5] + s[6] >= x[3]);
	
	for( i = 0 ; i< 8 ; i++)model.addConstr(x[4] >= t[i]) ; 
	model.addConstr(t[0] + t[1] + t[2] + t[3] + t[4] + t[5] + t[6] + t[7] >= x[4]);

		
	model.addConstr(a[0] == p[0]); model.addConstr(a[0] == q[0]); 		//	x4 * x1
	model.addConstr(a[1] == q[1]); model.addConstr(a[1] == r[0]);		//	x2 * x1
	model.addConstr(a[2] == q[2]); model.addConstr(a[2] == t[0]);		//	x0 * x1											
	model.addConstr(y[0] >= a[0] + a[1] + a[2] + p[1] + r[1] + s[0]) ; 

	model.addConstr(a[3] == q[3]); model.addConstr(a[3] == r[2]); 		// x3 * x2
	model.addConstr(a[4] == q[4]); model.addConstr(a[4] == s[1]);		// x3 * x1
	model.addConstr(a[5] == r[3]); model.addConstr(a[5] == s[2]);		// x2 * x1
	model.addConstr(y[1] >= a[3] + a[4] + a[5] + p[2] + r[4] + t[1]);
			
	model.addConstr(a[6] == s[3]); model.addConstr(a[6] == t[2]); 		//	x4 * x3
	model.addConstr(y[2] == a[6] + q[5] + r[5] + t[3]) ; 
			
	model.addConstr(a[7] == p[3]); model.addConstr(a[7] == s[4]); 		//	x4 * x0
	model.addConstr(a[8] == p[4]); model.addConstr(a[8] == t[4]); 		//	x3 * x0
	model.addConstr(y[3] >= a[7] + a[8] + p[5] + q[6] + r[6] + s[5] + t[5]) ; 
			
	model.addConstr(a[9] == p[6]); model.addConstr(a[9] == q[7]); 		//	x4 * x1
	model.addConstr(a[10] == q[8]); model.addConstr(a[10] == t[6]); 	//	x0 * x1
	model.addConstr(y[4] == a[9] + a[10] + q[9] + s[6] + t[7] ); 

	
}

// [0, x1, x2, x3, x3] --> [y0, y1, y2, y3, y4]
void ascon_sbox_0eq(GRBModel& model, vector<GRBVar>& x, vector<GRBVar>& y) {

	int i ; 

	vector<GRBVar> q(vector<GRBVar>(10)) ;
	for( i = 0 ; i<10; i++) q[i] = model.addVar(0, 1, 0, GRB_BINARY);

	vector<GRBVar> r(vector<GRBVar>(7)) ;
	for( i = 0 ; i<7; i++) r[i] = model.addVar(0, 1, 0, GRB_BINARY);

	vector<GRBVar> s(vector<GRBVar>(5)) ;
	for( i = 0 ; i<5; i++) s[i] = model.addVar(0, 1, 0, GRB_BINARY);	

	vector<GRBVar> a(vector<GRBVar>(6)) ;
	for( i = 0 ; i<6; i++) a[i] = model.addVar(0, 1, 0, GRB_BINARY);	
	
	for( i = 0 ; i< 10 ; i++)model.addConstr(x[0] >= q[i]) ;
	model.addConstr(q[0] + q[1] + q[2] + q[3] + q[4] + q[5] + q[6] + q[7] + q[8] + q[9] >= x[0]);
	
	for( i = 0 ; i< 7 ; i++)model.addConstr(x[1] >= r[i]) ;
	model.addConstr(r[0] + r[1] + r[2] + r[3] + r[4] + r[5] + r[6] >= x[1]);

	for( i = 0 ; i< 5 ; i++)model.addConstr(x[2] >= s[i]) ;
	model.addConstr(s[0] + s[1] + s[2] + s[3] + s[4] >= x[2]);

	model.addConstr(a[0] == q[0]); model.addConstr(a[0] == r[0]);		
	model.addConstr(a[1] == q[1]); model.addConstr(a[1] == s[0]);												
	model.addConstr(y[0] == a[0] + a[1] + q[2] + r[1] + s[1]) ; 

	model.addConstr(a[2] == q[3]); model.addConstr(a[2] == r[2]); 		
	model.addConstr(a[3] == q[4]); model.addConstr(a[3] == s[2]);	
	model.addConstr(a[4] == r[3]); model.addConstr(a[4] == s[3]);		
	model.addConstr(y[1] == a[2] + a[3] + a[4] + q[5] + r[4]);
	
	model.addConstr(y[2] >= q[6] + r[5]) ; 
	
	model.addConstr(y[3] == q[7] + r[6]) ; 
			
	model.addConstr(a[5] == q[8]); model.addConstr(a[5] == s[4]); 		
	model.addConstr(y[4] == a[5] + q[9] ); 

	
}

// [1, x1, x2, x3, x3] --> [y0, y1, y2, y3, y4]
void ascon_sbox_1eq(GRBModel& model, vector<GRBVar>& x, vector<GRBVar>& y) {

	int i ; 

	vector<GRBVar> q(vector<GRBVar>(8)) ;
	for( i = 0 ; i<8; i++) q[i] = model.addVar(0, 1, 0, GRB_BINARY);

	vector<GRBVar> r(vector<GRBVar>(7)) ;
	for( i = 0 ; i<7; i++) r[i] = model.addVar(0, 1, 0, GRB_BINARY);

	vector<GRBVar> s(vector<GRBVar>(5)) ;
	for( i = 0 ; i<5; i++) s[i] = model.addVar(0, 1, 0, GRB_BINARY);	

	vector<GRBVar> a(vector<GRBVar>(6)) ;
	for( i = 0 ; i<6; i++) a[i] = model.addVar(0, 1, 0, GRB_BINARY);	
	
	for( i = 0 ; i< 8; i++)model.addConstr(x[0] >= q[i]) ;
	model.addConstr(q[0] + q[1] + q[2] + q[3] + q[4] + q[5] + q[6] + q[7] >= x[0]);
	
	for( i = 0 ; i< 7; i++)model.addConstr(x[1] >= r[i]) ;
	model.addConstr(r[0] + r[1] + r[2] + r[3] + r[4] + r[5] + r[6] >= x[1]);

	for( i = 0 ; i< 5; i++)model.addConstr(x[2] >= s[i]) ;
	model.addConstr(s[0] + s[1] + s[2] + s[3] + s[4] >= x[2]);

	model.addConstr(a[0] == q[0]); model.addConstr(a[0] == r[0]);		
	model.addConstr(a[1] == q[1]); model.addConstr(a[1] == s[0]);												
	model.addConstr(y[0] >= a[0] + a[1] + r[1] + s[1]) ; 

	model.addConstr(a[2] == q[2]); model.addConstr(a[2] == r[2]); 		
	model.addConstr(a[3] == q[3]); model.addConstr(a[3] == s[2]);	
	model.addConstr(a[4] == r[3]); model.addConstr(a[4] == s[3]);		
	model.addConstr(y[1] >= a[2] + a[3] + a[4] + q[4] + r[4]);
	
	model.addConstr(y[2] >= q[5] + r[5]) ; 
	
	model.addConstr(y[3] >= q[6] + r[6]) ; 
			
	model.addConstr(a[5] == q[7]); model.addConstr(a[5] == s[4]); 		
	model.addConstr(y[4] == a[5]); 

	
}


// [1, x1, x2, x4+1, x4] --> [y0, y1, y2, y3, y4] pengshuo
void ascon_sbox_break(GRBModel& model, vector<GRBVar>& x, vector<GRBVar>& y) {

	int i ; 

	vector<GRBVar> q(vector<GRBVar>(7)) ;
	for( i = 0 ; i<7; i++) q[i] = model.addVar(0, 1, 0, GRB_BINARY);

	vector<GRBVar> r(vector<GRBVar>(6)) ;
	for( i = 0 ; i<6; i++) r[i] = model.addVar(0, 1, 0, GRB_BINARY);

	vector<GRBVar> s(vector<GRBVar>(6)) ;
	for( i = 0 ; i<6; i++) s[i] = model.addVar(0, 1, 0, GRB_BINARY);	


	vector<GRBVar> a(vector<GRBVar>(6)) ;
	for( i = 0 ; i<6; i++) a[i] = model.addVar(0, 1, 0, GRB_BINARY);	


	for( i = 0 ; i< 7; i++)model.addConstr(x[0] >= q[i]) ;
	model.addConstr(q[0] + q[1] + q[2] + q[3] + q[4] + q[5] + q[6] >= x[0]);
	
	for( i = 0 ; i< 6; i++)model.addConstr(x[1] >= r[i]) ;
	model.addConstr(r[0] + r[1] + r[2] + r[3] + r[4] + r[5] >= x[1]);

	for( i = 0 ; i< 6; i++)model.addConstr(x[2] >= s[i]) ;
	model.addConstr(s[0] + s[1] + s[2] + s[3] + s[4] + s[5] >= x[2]);


	model.addConstr(a[0] == q[0]); model.addConstr(a[0] == r[0]);		
	model.addConstr(a[1] == q[1]); model.addConstr(a[1] == s[0]);												
	model.addConstr(y[0] == a[0] + a[1] + r[1] + s[1]) ; 

	model.addConstr(a[2] == q[2]); model.addConstr(a[2] == r[2]); 		
	model.addConstr(a[3] == q[3]); model.addConstr(a[3] == s[2]);	
	model.addConstr(a[4] == r[3]); model.addConstr(a[4] == s[3]);		

	model.addConstr(y[1] == a[2] + a[3] + a[4]);
	
	model.addConstr(y[2] >= q[4] + r[4] + s[4]) ; 
	
	model.addConstr(y[3] >= q[5] + r[5]) ; 
			
	model.addConstr(a[5] == q[6]); model.addConstr(a[5] == s[5]); 		
	model.addConstr(y[4] >= a[5]); 
}


// [0, x1, x2, x4+1, x4] --> [y0, y1, y2, y3, y4] pengshuo
void ascon_sbox_break0(GRBModel& model, vector<GRBVar>& x, vector<GRBVar>& y) {

	int i ; 

	vector<GRBVar> q(vector<GRBVar>(9)) ;
	for( i = 0 ; i<9; i++) q[i] = model.addVar(0, 1, 0, GRB_BINARY);

	vector<GRBVar> r(vector<GRBVar>(6)) ;
	for( i = 0 ; i<6; i++) r[i] = model.addVar(0, 1, 0, GRB_BINARY);

	vector<GRBVar> s(vector<GRBVar>(6)) ;
	for( i = 0 ; i<6; i++) s[i] = model.addVar(0, 1, 0, GRB_BINARY);	

	vector<GRBVar> a(vector<GRBVar>(6)) ;
	for( i = 0 ; i<6; i++) a[i] = model.addVar(0, 1, 0, GRB_BINARY);	
	
	for( i = 0 ; i< 9; i++)model.addConstr(x[0] >= q[i]) ;
	model.addConstr(q[0] + q[1] + q[2] + q[3] + q[4] + q[5] + q[6] + q[7]  + q[8] >= x[0]);
	
	for( i = 0 ; i< 6; i++)model.addConstr(x[1] >= r[i]) ;
	model.addConstr(r[0] + r[1] + r[2] + r[3] + r[4] + r[5] >= x[1]);

	for( i = 0 ; i< 6; i++)model.addConstr(x[2] >= s[i]) ;
	model.addConstr(s[0] + s[1] + s[2] + s[3] + s[4] + s[5] >= x[2]);

	model.addConstr(a[0] == q[0]); model.addConstr(a[0] == r[0]);		
	model.addConstr(a[1] == q[1]); model.addConstr(a[1] == s[0]);												
	model.addConstr(y[0] >= a[0] + a[1] + r[1] + s[1] + q[2]) ; 

	model.addConstr(a[2] == q[3]); model.addConstr(a[2] == r[2]); 		
	model.addConstr(a[3] == q[4]); model.addConstr(a[3] == s[2]);	
	model.addConstr(a[4] == r[3]); model.addConstr(a[4] == s[3]);		

	model.addConstr(y[1] >= a[2] + a[3] + a[4]);
	
	model.addConstr(y[2] >= q[5] + r[4] + s[4]) ; 
	
	model.addConstr(y[3] >= q[6] + r[5]) ; 
			
	model.addConstr(a[5] == q[7]); model.addConstr(a[5] == s[5]); 		
	model.addConstr(y[4] >= a[5] + q[8]); 
}



// [0, x1, 1 + x2, x3, x3] --> [y0, y1, y2, y3, y4]
void ascon_sboxc_0eq(GRBModel& model, vector<GRBVar>& x, vector<GRBVar>& y) {

	int i ; 

	vector<GRBVar> q(vector<GRBVar>(8)) ;
	for( i = 0 ; i<8; i++) q[i] = model.addVar(0, 1, 0, GRB_BINARY);

	vector<GRBVar> r(vector<GRBVar>(7)) ;
	for( i = 0 ; i<7; i++) r[i] = model.addVar(0, 1, 0, GRB_BINARY);

	vector<GRBVar> s(vector<GRBVar>(6)) ;
	for( i = 0 ; i<6; i++) s[i] = model.addVar(0, 1, 0, GRB_BINARY);	

	vector<GRBVar> a(vector<GRBVar>(6)) ;
	for( i = 0 ; i<6; i++) a[i] = model.addVar(0, 1, 0, GRB_BINARY);	
	
	for( i = 0 ; i< 8; i++)model.addConstr(x[0] >= q[i]) ;
	model.addConstr(q[0] + q[1] + q[2] + q[3] + q[4] + q[5] + q[6] + q[7] >= x[0]);

	for( i = 0 ; i< 7; i++)model.addConstr(x[1] >= r[i]) ;
	model.addConstr(r[0] + r[1] + r[2] + r[3] + r[4] + r[5] + r[6] >= x[1]);

	for( i = 0 ; i< 6; i++)model.addConstr(x[2] >= s[i]) ;
	model.addConstr(s[0] + s[1] + s[2] + s[3] + s[4] + s[5] >= x[2]);

	model.addConstr(a[0] == q[0]); model.addConstr(a[0] == r[0]);		
	model.addConstr(a[1] == q[1]); model.addConstr(a[1] == s[0]);												
	model.addConstr(y[0] >= a[0] + a[1] + r[1] + s[1]) ; 

	model.addConstr(a[2] == q[2]); model.addConstr(a[2] == r[2]); 		
	model.addConstr(a[3] == q[3]); model.addConstr(a[3] == s[2]);	
	model.addConstr(a[4] == r[3]); model.addConstr(a[4] == s[3]);		
	model.addConstr(y[1] >= a[2] + a[3] + a[4] + r[4] + s[4]);
	
	model.addConstr(y[2] == q[4] + r[5]) ; 
	
	model.addConstr(y[3] >= q[5] + r[6]) ; 
			
	model.addConstr(a[5] == q[6]); model.addConstr(a[5] == s[5]); 		
	model.addConstr(y[4] == a[5] + q[7]); 

	
}

void ascon_linear_layer(GRBModel& model, vector<GRBVar>& X, vector<GRBVar>& Y, const int rot1, const int rot2){

	int i;
	
	vector<vector<GRBVar>> A(3, vector<GRBVar>(64));
	
	for(i = 0; i<64;i++){
		A[0][i] = model.addVar(0, 1, 0, GRB_BINARY); 
		A[1][i] = model.addVar(0, 1, 0, GRB_BINARY);
		A[2][i] = model.addVar(0, 1, 0, GRB_BINARY);
	}

	for(i = 0; i<64; i++){
		model.addConstr(X[i] >= A[0][i]); 
		model.addConstr(X[i] >= A[1][i]);
		model.addConstr(X[i] >= A[2][i]);
		model.addConstr(A[0][i] + A[1][i] + A[2][i] >= X[i]) ; 
	}

	for(i = 0; i<64; i++){
		model.addConstr(Y[i] == A[0][i] + A[1][(64-rot1 + i) % 64] + A[2][(64- rot2 + i) % 64]) ;
	} 

}

void diffusion(GRBModel& model, vector<GRBVar>& Y, vector<GRBVar>& X) {

	vector<GRBVar> Y0 (vector<GRBVar>(64)) ;
	vector<GRBVar> Y1 (vector<GRBVar>(64)) ;
	vector<GRBVar> Y2 (vector<GRBVar>(64)) ;
	vector<GRBVar> Y3 (vector<GRBVar>(64)) ;
	vector<GRBVar> Y4 (vector<GRBVar>(64)) ;
	vector<GRBVar> X0 (vector<GRBVar>(64)) ;
	vector<GRBVar> X1 (vector<GRBVar>(64)) ;
	vector<GRBVar> X2 (vector<GRBVar>(64)) ;
	vector<GRBVar> X3 (vector<GRBVar>(64)) ;
	vector<GRBVar> X4 (vector<GRBVar>(64)) ;

	for(int i = 0 ; i<64; i++){
		Y0[i] = Y[i] ; 
		Y1[i] = Y[64 + i] ;
		Y2[i] = Y[128 + i] ;
		Y3[i] = Y[192 + i] ;
		Y4[i] = Y[256 + i] ;
		
		X0[i] = X[i] ; 
		X1[i] = X[64 + i] ;
		X2[i] = X[128 + i] ;
		X3[i] = X[192 + i] ;
		X4[i] = X[256 + i] ; 
	}

	ascon_linear_layer(model, Y0, X0, 19, 28) ;
	ascon_linear_layer(model, Y1, X1, 61, 39) ; 
	ascon_linear_layer(model, Y2, X2, 1, 6) ;  
	ascon_linear_layer(model, Y3, X3, 10, 17) ; 
	ascon_linear_layer(model, Y4, X4, 7, 41) ; 

}

void substitution(GRBModel& model, vector<GRBVar>& X, vector<GRBVar>& Y, const unsigned char rc) {

	for(int i = 0 ; i< 64; i++){

		vector<GRBVar> tmpx (vector<GRBVar>(5)) ;
		vector<GRBVar> tmpy (vector<GRBVar>(5)) ;

		tmpx[0] = X[i] ; 
		tmpx[1] = X[64 + i] ;
		tmpx[2] = X[128 + i] ;
		tmpx[3] = X[192 + i ] ;
		tmpx[4] = X[256 + i] ;

		tmpy[0] = Y[i] ; 
		tmpy[1] = Y[64 + i] ;
		tmpy[2] = Y[128 + i] ;
		tmpy[3] = Y[192 + i] ;
		tmpy[4] = Y[256 + i] ;
		
		if(i >= 56){
			int t = (rc >> (63-i) ) & 1 ; 
			if(t == 1) ascon_sboxc(model, tmpx, tmpy) ; 
			else ascon_sbox(model, tmpx, tmpy) ;
		}
		else{
				ascon_sbox(model, tmpx, tmpy) ; 
		}

	}

}

