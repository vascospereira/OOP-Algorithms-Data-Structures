#ifndef FROTA_H_
#define FROTA_H_
#include <string>
#include <vector>

using namespace std;

class  Veiculo {
protected:
   string marca;
   int mes, ano;
public:
   Veiculo(string mc, int m, int a);
   virtual ~Veiculo(){};
   bool operator < (const Veiculo & v) const;
   virtual float calcImposto() const = 0;
   string getMarca() const;
   int getAno() const;
   virtual int info() const;
};

class Motorizado: public Veiculo {
   string combustivel; int cilindrada;
public:
   Motorizado(string mc, int m, int a, string comb, int cili);
   string getCombustivel() const;
   float calcImposto() const;
   int info() const;
};

class Automovel: public Motorizado {
public:
	Automovel(string mc, int m, int a, string comb, int cili);
	int info() const;
};


class Camiao: public Motorizado {
   int carga_maxima;
public:
   Camiao(string mc, int m, int a,string comb, int cili, int cm);
   int info() const;
};


class Bicicleta: public Veiculo {
  string tipo;
public:
  Bicicleta(string mc, int m, int a, string tipo);
  float calcImposto() const;
  int info() const;
};

class Frota {
	vector<Veiculo *> veiculos;
public:
	int numVeiculos() const;
	void adicionaVeiculo(Veiculo *v1);
	int menorAno() const;
	void info() const;
	float totalImposto() const;
};
#endif /*VEICULO_H_*/
