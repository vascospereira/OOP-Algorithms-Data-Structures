#include "Frota.h"
#include <iostream>
#include <string>

using namespace std;

Veiculo::Veiculo(string mc, int m, int a): marca(mc), mes(m), ano(a){}

string Veiculo::getMarca() const { return marca; }

int Veiculo::getAno() const {return ano;}

int Veiculo::info() const
{
	cout << "Marca: " << marca << endl;
	cout << "Mes/Ano: " << mes << "/" << ano << endl;
	return 3;
}

bool Veiculo::operator < (const Veiculo & v) const
{
	if(ano < v.ano) return true;
	else if(ano == v.ano && mes < v.mes) return true;
	return false;
}

Motorizado::Motorizado(string mc, int m, int a, string comb, int cili): Veiculo(mc,m,a)
{
	combustivel = comb;
	cilindrada = cili;
}

int Motorizado::info() const
{
	cout << "Combustivel: " << combustivel << endl;
	cout << "Cilindrada: " << cilindrada << endl;
	return 2 + Veiculo::info();
}

float Motorizado::calcImposto() const
{
	float tax;
	if(combustivel == "gasolina"){
		if(cilindrada <= 1000)
			return tax = (ano > 1995) ? 14.56 : 8.1;
		else if(cilindrada <= 1300)
			return tax = (ano > 1995) ? 29.06 : 14.56;
		else if(cilindrada <= 1750)
			return tax = (ano > 1995) ? 45.15 : 22.65;
		else if(cilindrada <= 2600)
			return tax = (ano > 1995) ? 113.98 : 54.89;
		else if(cilindrada <= 3500)
			return tax = (ano > 1995) ? 181.17 : 87.13;
		return tax = (ano > 1995) ? 320.89 : 148.37;
	}
	if(cilindrada <= 1500)
		return tax = (ano > 1995) ? 14.56 : 8.1;
	else if(cilindrada <= 2000)
		return tax = (ano > 1995) ? 29.06 : 14.56;
	else if(cilindrada <= 3000)
		return tax = (ano > 1995) ? 45.15 : 22.65;
	return tax = (ano > 1995) ? 113.98 : 54.89;
}

string Motorizado::getCombustivel() const { return combustivel; }

Automovel::Automovel(string mc, int m, int a, string comb, int cili): Motorizado(mc, m, a, comb, cili){}

int Automovel::info() const
{
	cout << "Automovel" << endl;
	return Motorizado::info();
}

Camiao::Camiao(string mc, int m, int a,string comb, int cili, int cm):Motorizado(mc, m, a, comb, cili)
{ carga_maxima =  cm; }

int Camiao::info() const
{
	cout << "Camiao" << endl;
	cout << "Carga Maxima: " << carga_maxima << endl;
	return Motorizado::info() + 1;
}

Bicicleta::Bicicleta(string mc, int m, int a, string t): Veiculo(mc,m, a)
{ tipo = t; }

int Bicicleta::info() const
{
	cout << "Bicicleta" << endl;
	cout << "Tipo: " << tipo << endl;
	return Veiculo::info() + 1;
}

float Bicicleta::calcImposto() const { return 0; }

void Frota::adicionaVeiculo(Veiculo *v1){ veiculos.push_back(v1); }

int Frota::numVeiculos() const { return veiculos.size(); }

int Frota::menorAno() const
{
	if(veiculos.size()==0) return 0;
	vector<Veiculo *>::const_iterator it = veiculos.begin();
	int ano = (*it)->getAno();
	for(it++; it != veiculos.end(); it++){
		if((*it)->getAno() < ano)
			ano = (*it)->getAno();
	}
	return ano;
}

float Frota::totalImposto() const
{
	if(veiculos.size()==0) return 0;
	vector<Veiculo*>::const_iterator it = veiculos.begin();
	float total=0;
	while(it!=veiculos.end()){
		total += (*it)->calcImposto();
		it++;
	}
	return total;
}

void Frota::info() const
{
	vector<Veiculo*>::const_iterator it = veiculos.begin();
	while(it!=veiculos.end()){
		(*it)->info();
		it++;
	}
}
