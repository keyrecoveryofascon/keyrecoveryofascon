#include"split.h" 
#include<set>
#include"ascon.h"
#include<chrono>
#include<thread>
#include<mutex>
#include<map>
#include"polynomial.h"
#include<cassert>
#include<string>

#define DEBUG 0

using namespace std;

mutex workmutex;
mutex smutex;

extern int THREADNUM = 64;

void SingleSboxM2( vector<Polynomial> & X  )
{
    auto y0 = X[0];
    auto y1 = X[1];
    auto y2 = X[2];
    auto y3 = X[3];
    auto y4 = X[4];

    X[0] = y4*y1 + y2*y1 + y1*y0;
    X[1] = y3*y2 + y3*y1 + y2*y1;
    X[2] = y4*y3 ;
    X[3] = y4*y0 + y3*y0 ;
    X[4] = y4*y1 + y1*y0;
}

void SingleSboxM( vector<Polynomial> & X  )
{
    auto y0 = X[0];
    auto y1 = X[1];
    auto y2 = X[2];
    auto y3 = X[3];
    auto y4 = X[4];

    X[0] = y4*y1 + y3 + y2*y1 + y2 + y1*y0 + y1 + y0;
    X[1] = y4 + y3*y2 + y3*y1 + y3 + y2*y1 + y2 + y1 + y0;
    X[2] = y4*y3 + y4 + y2 + y1 + Polynomial( "1" );
    X[3] = y4*y0 + y4 + y3*y0 + y3 + y2 + y1 + y0;
    X[4] = y4*y1 + y4 + y3 + y1*y0 + y1;
}





void SingleSboxM0( vector<Polynomial> & X  )
{
    auto y0 = X[0];
    auto y1 = X[1];
    auto y2 = X[2];
    auto y3 = X[3];
    auto y4 = X[4];

    X[0] = y4*y1 + y4;
    X[1] = y4*y2 + y4*y1;
    X[2] = y4*y3 + y4;
    X[3] = Polynomial("0");
    X[4] = y4*y1;
}

void SingleSboxM1( vector<Polynomial> & X  )
{
    auto y0 = X[0];
    auto y1 = X[1];
    auto y2 = X[2];
    auto y3 = X[3];
    auto y4 = X[4];

    X[0] = y4*y1 + y3 + y2*y1 + y2 + y1*y0 + y1 + y0;
    X[1] = y4 + y3*y2 + y3*y1 + y3 + y2*y1 + y2 + y1 + y0;
    X[2] = y4*y3 + y4 + y2 + y1;
    X[3] = y4*y0 + y4 + y3*y0 + y3 + y2 + y1 + y0;
    X[4] = y4*y1 + y4 + y3 + y1*y0 + y1;
}

vector<Polynomial> SingleSbox( const vector<Polynomial> & X  )
{

    clock_t start, end, end2;
    start = clock();
    auto y0 = X[0];
    auto y1 = X[1];
    auto y2 = X[2];
    auto y3 = X[3];
    auto y4 = X[4];
    auto x2 = y4*y3;

    end = clock();
    cout << "compyte x2 time = " << double(end-start)/CLOCKS_PER_SEC << "s" << endl;

    x2 = filter(x2);

    auto z1 = y4+y0;
    auto x4 = z1*y1;
    auto z3 = y2*y1;
    auto x0 = x4+z3;
    auto z4 = y1+y2;
    auto z5 = z4*y3;
    auto z6 = y3+y4;
    auto x3 = z6*y0;
    auto x1 = z5+z3;


    

    end2 = clock();
    cout << "compute all time = " << double(end2-start)/CLOCKS_PER_SEC << "s" << endl;


    x0 = filter(x0);
    x1 = filter(x1);
    x2 = filter(x2);
    x3 = filter(x3);
    x4 = filter(x4);

    vector<Polynomial> res;
    res.push_back( x0 );
    res.push_back( x1 );
    res.push_back( x2 );
    res.push_back( x3 );
    res.push_back( x4 );


    return res;
}


Polynomial filter(Polynomial X)
{
	string tmp = X.getPoly();
	vector<string> monomial = split(tmp, "+");

	vector<string> mol;

	for(auto it : monomial)
	{
		
		int count  = 0;
		for(int k = 0; k < it.size(); k++)
		{
			//cout << it[k]  << endl;
			if(it[k] == 120)
				count++;
		}
		//cout << count << "  count  " << endl;
		if(count == 8)
			mol.emplace_back(it);
	}

	cout << monomial.size() << "  monomial  " << endl;
	cout << mol.size() << "  mol  " << endl;

	set<vector<string>> reduce_terms;
	for(auto it : mol)
	{
		vector<string> term = split(it, "*");
		vector<string> termx;
		for(auto itt: term)
		{
			if(itt[0] == 120)
				termx.emplace_back(itt);
		}
		reduce_terms.insert(termx);
	}

	cout << reduce_terms.size() << " set size: " << endl;
	if(mol.size() >= 1)
		X = Polynomial(join(mol, "+"));

	return X;
}


vector<Polynomial> Sbox4( const vector<Polynomial> & X ) 
{
    vector<Polynomial> V(320);
    for ( int col = 0; col < 64; col++ )
    {
	cout << "compute column: " << col << endl;
        vector<Polynomial> Single;
        for ( int row = 0; row < 5; row++ )
            Single.push_back( X[col + 64 * row] );
        auto temp = SingleSbox( Single );
        for ( int row = 0; row < 5; row++ )
            V[ col + 64 * row ] = temp[row];
    }
    //for (int col = 1; col < 64; col++)
    //{
    //        for(int row = 0; row < 5; row++)
    //        {
    //        	V[col + 64*row] = X[col+ 64*row];
    //        }
    //}
    return V;
}









vector<Polynomial> Sbox( const vector<Polynomial> & X ) 
{
    vector<Polynomial> V(320);
    for ( int col = 0; col < 64; col++ )
    {
        vector<Polynomial> Single;
        for ( int row = 0; row < 5; row++ )
            Single.push_back( X[col + 64 * row] );
        auto temp = SingleSbox( Single );
        for ( int row = 0; row < 5; row++ )
            V[ col + 64 * row ] = temp[row];
    }
    return V;
}

vector<Polynomial> SboxM0( const vector<Polynomial> & X ) 
{
    vector<Polynomial> V(320);

    vector<Polynomial> * Single = new vector<Polynomial> [64];


    int STEP = 64 / THREADNUM;

    for ( int step = 0; step < STEP; step ++ )
    {
        int start = step * THREADNUM;
        int end = step * THREADNUM + THREADNUM;

        vector<thread> threads;

        for ( int col = start; col < end; col++ )
        {
            for ( int row = 0; row < 5; row++ )
                Single[col].push_back( X[col + 64 * row] );

            threads.push_back( thread( SingleSboxM0, ref( Single[col] ) ) );
	    //cout << "step  " << step << "col:  "  << col << endl;
        }

        for ( auto & th : threads )
            th.join();
    }

    for ( int col = 0; col < 64; col++ )
    {
        for ( int j = 0; j < 5; j++ )
            V[ col + 64 * j ] = Single[col][j];
    }

    delete [] Single;

    return V;
}








vector<Polynomial> SboxM( const vector<Polynomial> & X ) 
{
    vector<Polynomial> V(320);

    vector<Polynomial> * Single = new vector<Polynomial> [64];


    int STEP = 64 / THREADNUM;

    for ( int step = 0; step < STEP; step ++ )
    {
        int start = step * THREADNUM;
        int end = step * THREADNUM + THREADNUM;

        vector<thread> threads;

        for ( int col = start; col < end; col++ )
        {
            for ( int row = 0; row < 5; row++ )
                Single[col].push_back( X[col + 64 * row] );

            threads.push_back( thread( SingleSboxM2, ref( Single[col] ) ) );
	    //cout << "step  " << step << "col:  "  << col << endl;
        }

        for ( auto & th : threads )
            th.join();
    }

    for ( int col = 0; col < 64; col++ )
    {
        for ( int j = 0; j < 5; j++ )
            V[ col + 64 * j ] = Single[col][j];
    }

    delete [] Single;

    return V;
}

vector<Polynomial> SingleMatrix( vector<Polynomial> & X, int r0, int r1 )
{
    vector<Polynomial> Y(64);
    for ( int i = 0; i < 64; i++ )
        Y[i] = X[i] + X[ ( i + (64 - r0) ) % 64 ] + X[ ( i + (64 - r1) ) % 64 ];
    return Y;
}

vector<Polynomial> Matrix( const vector<Polynomial> & X )
{
    vector<Polynomial> Y( 320 );

    int rot[5][2] = { { 19, 28 }, {61, 39}, {1, 6}, {10, 17}, {7, 41} };

    for ( int row = 0; row < 5; row++ )
    {
        vector<Polynomial> V(64);
        for ( int col = 0; col < 64; col++ )
        {
            V[col] = X[ 64 * row + col ];
        }

        auto temp = SingleMatrix( V, rot[row][0], rot[row][1] );

        for ( int col = 0; col < 64; col++ )
            Y[col + 64 * row] = temp[col]; 

	//cout << "row:  " << row << endl;
    }

    return Y;
}

vector<Polynomial> addConst( vector<Polynomial> & X, int r )
{
    vector<Polynomial> Y;
    for ( int i = 0; i < 320; i++ )
        Y.push_back( X[i] );

    int constant[] = { 0xf0, 0xe1, 0xd2, 0xc3, 0xb4, 0xa5, 0x96, 0x87, 0x78, 0x69,
            0x5a, 0x4b };

    int base = 184;

    for ( int i = 0; i < 8; i++ )
        if ( constant[r] >> ( 7 - i ) & 0x1 )
            Y[ base + i ] = Y[base + i] + Polynomial( "1" );

    return Y;
}






