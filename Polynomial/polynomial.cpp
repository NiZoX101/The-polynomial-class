#include <iostream>
#include <vector>
#include <iterator>
#include <string>
#include<time.h>
#include <locale.h>

using namespace std;

class Polynomial
{
	long long degree;
	long long base;
	vector<long long> coef;

public:

	Polynomial(int n = 2, int deg = 0);
	Polynomial(const Polynomial&);
	~Polynomial() {};

	bool operator == (const Polynomial&);
	bool operator ==(const long long);
	bool operator!=(const Polynomial&);
	bool operator!=(const long long);
	Polynomial operator=(const Polynomial&);
	Polynomial operator=(const long long);
	Polynomial operator+ (const Polynomial&);
	Polynomial operator* (const Polynomial&);
	Polynomial operator- (const Polynomial&);
	Polynomial operator/ (const Polynomial&);
	Polynomial operator% (const Polynomial&);
	Polynomial GCD(Polynomial&);
	Polynomial Powp();
	bool IrreducibilityTest();
	bool Primality();

	void NonZeroDeg();
	friend istream& operator>>(istream&, Polynomial&);
	friend ostream& operator<<(ostream&, Polynomial&);

};

long long Phifun(long long m)
{
	int n, res;
	res = m; n = m;
	long long i;
	for (i = 2; i * i <= n; i++)
	{
		if (n % i == 0)
		{
			while (n % i == 0)
				n = n / i;
			res = res - res / i;
		}
	}
	if (n > 1)
	{
		res = res - res / n;
	}
	return (res);
}


long long inverse(long long a, long long mod)
{
	long long m = Phifun(mod) - 1, res = a;
	//cout << m << endl;
	int i = 1;
	while (i < m)
	{
		res = res * a % mod;
		i++;
	}
	return (res);
}

long long Pow(long long a, long long y)
{
	long long z = a;
	int y_2 = y, n = 0;
	while (y_2 != 0)
	{
		y_2 = (y_2 >> 1);
		n++;
	}
	//cout << n << endl;
	for (int i = n - 2; i >= 0; i--)
	{
		z = z * z;
		//cout << z << ' ';
		//cout << z << endl;
		//cout << z << endl;
		if (((1 << i) & y) != 0) {
			z = z * a;
		}
	}
	return (z);

}


long long PowMod(long long a, long long y, long long mod)
{
	long long z = a;
	int y_2 = y, n = 0;
	while (y_2 != 0)
	{
		y_2 = (y_2 >> 1);
		n++;
	}
	//cout << n << endl;
	for (int i = n - 2; i >= 0; i--)
	{
		z = z * z;
		//cout << z << ' ';
		z = z % mod; //cout << z << endl;
		//cout << z << endl;
		//cout << z << endl;
		if (((1 << i) & y) != 0) {
			z = z * a % mod; //cout << z << endl;
		}
	}
	return (z);

}



bool Ferma(long long n, int t)
{
	srand(time(NULL));
	long long b;
	if (n <= 3) return true;
	if (n % 2 == 0) return(false);
	for (int i = 0; i < t; i++)
	{

		long long a = rand() % (n - 3) + 2;
		b = a;
		//cout << a << endl;
		int j = 1;
		b = PowMod(b, n - 1, n);

		if (b != 1)
		{
			//cout << endl << "число составное" << endl;
			return(false);
		}
	}
	//cout << "число, возможно, простое";
	return(true);

}

vector <long long> Trialdiv(long long a)
{

	vector <long long> p;
	if (a == 1) { p.push_back(1); }
	else if (Ferma(a, 3)) p.push_back(a);
	else
	{
		long long d[4];
		d[0] = 2; d[1] = 3, d[2] = 5, d[3] = 7;
		int num = 0, k = 0;
		while (a != 1 && d[k] <= a * a)
		{
			while (a % d[k] == 0)
			{
				num++;
				p.push_back(d[k]);
				//cout << d[k] << endl;
				a = a / d[k];
			}
			if (a != 1)
			{
				if (a / d[k] > d[k])
				{
					k++;
					if (k > 2) d[k - 1] = d[k - 1] + 6;
					if (k == 4) k = 2;

				}
				else
				{
					num++;
					p.push_back(a);
					a = 1;
				}
			}
		}
	}
	//for (int i = 0; i < p.size(); i++) cout << p[i] << ' ';
	return (p);
}


Polynomial::Polynomial(int n, int deg)
{
	degree = deg;
	base = n;
	for (int i = 0; i <= degree; i++) coef.push_back(0);

}

Polynomial::Polynomial(const Polynomial& b)
{
	degree = b.degree;
	base = b.base;
	coef = b.coef;
}

istream& operator>>(istream& in, Polynomial& poly)
{
	cout << "Enter the degree of the polynomial: ";
	in >> poly.degree;

	poly.coef.resize(poly.degree + 1);
	cout << "Enter the coefficients starting from the highest degree term: ";
	for (int i = poly.degree; i >= 0; i--)
	{
		in >> poly.coef[i];
	}
	cout << "Enter the base: ";
	in >> poly.base;
	return in;
}

ostream& operator<< (ostream& out, Polynomial& poly)
{
	int deg = poly.degree;
	for (int i = poly.degree; i >= 0; --i)
	{
		if (poly.coef[i] != 0)
		{
			out << poly.coef[i] << "x^" << i;
			if ((i >= 1) && (i != (poly.coef.size())))
			{
				out << " + ";
			}
		}
	}
	out << " (base: " << poly.base << ")";
	return out;

}


void Polynomial::NonZeroDeg()
{
	int i = coef.size() - 1;
	while (i != 0 && coef[i] == 0)
	{
		coef.pop_back();
		degree--;
		i--;

	}


}

bool Polynomial::operator!= (const Polynomial& B)
{
	if (coef != B.coef || base != B.base) return true;
	else return false;
}

bool Polynomial::operator!=(const long long b)
{
	long long b1 = b;
	while (b1 < 0) b1 += base;
	if (degree != 0 || coef[0] != b1 % base) return true;
	else return false;
}

bool Polynomial::operator== (const Polynomial& B)
{
	if (coef == B.coef && base == B.base) return true;
	else return false;
}

bool Polynomial::operator==(const long long b)
{
	long long b1 = b;
	while (b1 < 0) b1 += base;
	if (degree == 0 && coef[0] == b1 % base) return true;
	else return false;
}


Polynomial Polynomial::operator= (const Polynomial& b)
{
	if (this != &b)
	{
		degree = b.degree;
		base = b.base;
		coef = b.coef;

	}
	return (*this);
}

Polynomial Polynomial:: operator=(const long long b)
{
	Polynomial a(*this);
	long long b1 = b;
	while (b1 < 0) b1 += base;
	a.coef[0] = b1 % base;
	*this = a;
	return (*this);
}

Polynomial Polynomial::operator+ (const Polynomial& B)
{
	if (base != B.base) { cout << "не совпадают поля коэффициентов"; exit(0); }
	int i, deg;
	deg = max(degree, B.degree);
	Polynomial C(base, deg);

	if (degree >= B.degree)
	{
		i = C.degree;
		while (i != B.degree)
		{
			C.coef[i] = coef[i];
			i--;
		}

	}

	if (B.degree > degree)
	{
		i = C.degree;
		while (i != degree)
		{
			C.coef[i] = B.coef[i];
			i--;
		}
	}

	for (i; i >= 0; i--)
	{
		C.coef[i] = (coef[i] + B.coef[i]) % base;
	}

	C.NonZeroDeg();
	return (C);
}



Polynomial Polynomial::operator- (const Polynomial& B)
{
	if (base != B.base) { cout << "не совпадают поля коэффициентов"; exit(0); }

	int i, deg;
	deg = max(degree, B.degree);
	Polynomial C(base, deg);

	if (degree >= B.degree)
	{
		i = C.degree;
		while (i != B.degree)
		{
			C.coef[i] = coef[i];
			i--;
		}
	}

	if (B.degree > degree)
	{
		i = C.degree;
		while (i != degree)
		{
			C.coef[i] = base - B.coef[i];
			i--;
		}
	}

	for (i; i >= 0; i--)
	{
		if (coef[i] < B.coef[i]) C.coef[i] = coef[i] + base;
		else C.coef[i] = coef[i];
		C.coef[i] = (C.coef[i] - B.coef[i]) % base;
	}

	C.NonZeroDeg();
	return(C);


}

Polynomial Polynomial::operator* (const Polynomial& B)
{
	if (base != B.base) { cout << "не совпадают поля коэффициентов"; exit(0); }
	Polynomial C(base, degree + B.degree);
	int i, j;
	for (i = 0; i <= B.degree; i++)
	{
		while (i <= B.degree && B.coef[i] == 0) i++;
		if (i <= B.degree)
		{
			for (j = 0; j <= degree; j++)
			{
				C.coef[i + j] = (C.coef[i + j] + B.coef[i] * coef[j]) % base;
			}
		}
	}
	C.NonZeroDeg();
	return(C);
}

Polynomial Polynomial::operator/ (const Polynomial& B)
{
	Polynomial O(base);
	if (degree < B.degree)
	{
		Polynomial R; R.base = base; R = 0; return R;
	}
	if (*this == B) { Polynomial R; R.base = base; R = 1; return R; }

	Polynomial C(base, degree - B.degree);
	Polynomial S(base), R(*this);
	long long inv = inverse(B.coef[B.degree], base);
	while (R.degree >= B.degree && R != 0)
	{
		Polynomial Q(base, R.degree - B.degree);
		//cout << "R:"<< R << R.degree << endl;
		long long q = (R.coef[R.degree] * inv) % base;
		C.coef[R.degree - B.degree] = q;
		//cout <<"C:"<< C;
		Q.coef[R.degree - B.degree] = q;
		//cout << "Q:" << Q;
		S = Q * B;
		//cout <<"S:"<< S;
		R = R - S;
	}

	return (C);


}

Polynomial Polynomial::operator%(const Polynomial& B)
{
	if (degree < B.degree) return (*this);
	if (*this == B) { Polynomial R; R = 0; R.base = base;  return R; }

	Polynomial C(base, degree - B.degree);
	Polynomial S(base), R(*this);
	long long inv = inverse(B.coef[B.degree], base);
	while (R.degree >= B.degree && R != (long long)0)
	{
		Polynomial Q(base, R.degree - B.degree);
		//cout << "R:"<< R << R.degree << endl;
		long long q = (R.coef[R.degree] * inv) % base;
		C.coef[R.degree - B.degree] = q;
		//cout <<"C:"<< C;
		Q.coef[R.degree - B.degree] = q;
		//cout << "Q:" << Q;
		S = Q * B;
		//cout <<"S:"<< S;
		R = R - S;
	}
	return (R);
}

Polynomial Polynomial::GCD(Polynomial& g)
{
	Polynomial A(*this), B(g), R(base), fn(base);
	//cout << O;
	if (*this == 0 || g == 0) 
	{ 
		Polynomial R;
		R = 0; R.base = base;
		return R;
	}
	if (B.degree > A.degree) 
	{ 
		A = B;
		B = *this; 
	};
	do
	{

		R = A % B;
		A = B;
		B = R;
		//cout << "A:" << A <<"R:" << R;

	} while (R != 0);
	long long f1 = inverse(A.coef[A.degree], base);
	fn = f1;
	A = A * fn;
	return (A);
}

Polynomial Polynomial::Powp()
{
	Polynomial res_x(base, degree * base);
	for (int i = 0; i <= degree; i++) res_x.coef[i * base] = coef[i];
	return res_x;
}

bool Polynomial::IrreducibilityTest()
{
	Polynomial f = *this;
	Polynomial d(base);
	int n = degree;
	Polynomial x(base, 1);
	x.coef[1] = 1;
	Polynomial u(base);
	u = x;
	//cout << "u  " << u << endl;
	int i = 0;
	while (i < (n / 2))
	{
		u = u.Powp();
		u = u % f;
		//cout << "u: " << u << endl;
		Polynomial u_x(base);
		u_x = u - x;
		d = f.GCD(u_x);
		//cout << "f: " << f << " u-x: " << u_x << endl;
		//cout << "d: " << d << endl;
		if (d != 1)
		{
			cout << "The polynomial is reducible" << endl;
			return false;
		}
		i++;
	}
	cout << "Irreducible" << endl;
	return true;
}

bool Polynomial::Primality()
{
	if (!IrreducibilityTest()) 
	{ 
		cout << "Is not prime" << endl; 
		return false; 
	}
	long long int pn;
	pn = Pow(base, degree) - 1;
	vector <long long> p = Trialdiv(pn);
	int i = 0;
	while(i < p.size())
	{
		long long int pi = p[i];
		while (i < p.size() && p[i] == pi) i++;
		Polynomial r(base, pn / pi);
		r.coef[pn / pi] = 1;
		r = r % *this;
		if (r == 1) 
		{ 
			cout << "Is not prime" << endl;
			return false; 
		}
	}
	cout << "Prime" << endl;
	return true;
}

int main()
{
	Polynomial a;
	cin >> a;
	cout << a;
	a.IrreducibilityTest();
	a.Primality();
}
