#include "zoo.h"
#include <sstream>
#include <stdlib.h>

/**
 * Class Animal
 */

int Animal::maisJovem = 999;

// Return the youngest animal age
int Animal::getMaisJovem() { return maisJovem; }

Animal::Animal(string nome, int idade): nome(nome), idade(idade), vet(0)
{
	if(idade < maisJovem)
		maisJovem = idade;
}

string Animal::getNome() const { return nome; }

string Animal::getInformacao() const
{
	stringstream ss;
	ss << nome << ", " << idade;
	if(vet != NULL) ss << ", " << vet->getInformacao();
	return ss.str();
}

void Animal::setVeterinario(Veterinario *vet)
{
	this->vet = vet;
}

Veterinario* Animal::getVeterinario() { return vet; }

int Animal::getIdade() const { return idade; }

/**
 * Class Morcego
 */

Morcego::Morcego(string nome, int idade, int vmax, int amax): Animal(nome, idade), Voador(vmax, amax){}

bool Morcego::eJovem() const
{
	if(idade < 4) return true;
	return false;
}

string Morcego::getInformacao() const
{
	stringstream ss;
	ss << Animal::getInformacao() << ", " << Voador::getInformacao();
	return ss.str();
}

/**
 * Class Cao
 */

Cao::Cao(string nome, int idade, string raca): Animal(nome,idade) { this->raca = raca; }

bool Cao::eJovem() const
{
	if(idade < 5) return true;
	return false;
}

string Cao::getInformacao() const
{
	stringstream ss;
	ss << Animal::getInformacao() << ", " << raca;
	return ss.str();
}

/**
 * Class Voador
 */

Voador::Voador(int vmax, int amax): velocidade_max(vmax), altura_max(amax){}

string Voador::getInformacao() const
{
	stringstream ss;
	ss << velocidade_max << ", " << altura_max;
	return ss.str();
}

/**
 * Class Vet
 */

Veterinario::Veterinario(string n, long cod): nome(n), codOrdem(cod){}

string Veterinario::getNome() const { return nome; }

long Veterinario::getCodigo() const { return codOrdem; }

string Veterinario::getInformacao() const
{
	stringstream ss;
	ss << nome << ", " << codOrdem;
	return ss.str();
}

/**
 * Class Zoo
 */

// Adds animal to the zoo
void Zoo::adicionaAnimal(Animal *a1){ animais.push_back(a1); }

int Zoo::numAnimais() const { return animais.size(); }

int Zoo::numVeterinarios() const { return veterinarios.size(); }

// All info about animals in the zoo
string Zoo::getInformacao() const
{
	stringstream ss;
	for(unsigned i = 0; i < animais.size(); i++){
		ss << animais[i]->getInformacao() << "\n";
	}
	return ss.str();
}

// Verifies if animal with nomeA is young
bool Zoo::animalJovem(string nomeA)
{
	for(unsigned i = 0; i < animais.size(); i++){
		if(animais[i]->getNome() == nomeA)
			return animais[i]->eJovem();
	}
	return false;
}

// Set vets equally to animals
void Zoo::alocaVeterinarios(istream &isV)
{
	string nome, codigo;
	while(!isV.eof()){
		getline(isV,nome);
		getline(isV,codigo);
		long num = atoi(codigo.c_str());
		Veterinario *vet = new Veterinario(nome,num);
		veterinarios.push_back(vet);
	}

	for(unsigned i = 0; i < animais.size(); i++){
		animais.at(i)->setVeterinario(veterinarios.at(i%veterinarios.size()));
	}
}

// Removes vet from vector and set the next vet to the animal without the erased vet
bool Zoo::removeVeterinario (string nomeV)
{
	for(unsigned i = 0; veterinarios.size(); i++){
		if(veterinarios.at(i)->getNome() == nomeV){
			for(unsigned j = 0; j < animais.size();j++){
				if(animais.at(j)->getVeterinario() == veterinarios.at(i)){
					animais.at(j)->setVeterinario(veterinarios.at(i+1));
				}
			}
			veterinarios.erase(veterinarios.begin() + i);
			return true;
		}
	}
	return false;
}

// Compares two zoos size with animals age 
bool Zoo::operator < (Zoo& zoo2) const
{
	int sum1 = 0, sum2 = 0;
	for(unsigned i = 0; i < animais.size(); i++)
		sum1 += animais.at(i)->getIdade();
	for(unsigned i = 0; i < zoo2.animais.size(); i++)
		sum2 += zoo2.animais.at(i)->getIdade();
	return sum1 < sum2;
}
