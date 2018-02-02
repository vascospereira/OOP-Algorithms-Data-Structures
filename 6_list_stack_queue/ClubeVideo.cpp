#include "ClubeVideo.h"
#include <iostream>
using namespace std;


ostream& operator<<(ostream& os, const Filme& umFilme) {
	os << umFilme.getTitulo() << " " << umFilme.getEmprestimos();
	return os;
}


ostream& operator<<(ostream& os, const PedidoCliente& pc) {
	os << "Cliente " << pc.getNomeCliente() << " em espera para " << pc.getTituloFilme() << endl;
	return os;
}

ostream& operator<<(ostream& os, const Cliente& c1) {
	os << c1.getNome() << " tem " << c1.getFilmesEmprestados().size() << " filmes!\n";
	return os;
}


/**
 * Verifies if a client exists
 */
bool ClubeVideo::existeCliente(string umNome) const
{
	for(unsigned i = 0; i < clientes.size(); i++){
		if(clientes.at(i).getNome() == umNome)
			return true;
	}
	return false;
}

/**
 * Verifies if movie exists considering rent movies too
 */
bool ClubeVideo::existeFilme(string umTitulo) const
{
	for(unsigned i = 0; i < filmes.size(); i++){
		if(filmes.at(i).getTitulo() == umTitulo) return true;
	}

	for(unsigned i = 0; i < clientes.size(); i++){
		stack<Filme> movies = clientes.at(i).getFilmesEmprestados();
		while(movies.size()){
			if(movies.top().getTitulo() == umTitulo) return true;
			movies.pop();
		}
	}
	return false;
}

/**
 * Returns a String with all movies, including rented by clients
 */
string ClubeVideo::imprimirFilmes() const
{
	ostringstream oss;
	for(unsigned i = 0; i < filmes.size(); i++){
		oss << filmes.at(i) << "\n";
	}

	for(unsigned i = 0; i < clientes.size(); i++){
		stack<Filme> movies = clientes.at(i).getFilmesEmprestados();
		while(movies.size()){
			oss << movies.top() << "\n";
			movies.pop();
		}
	}

	return oss.str();
}

/**
 * Available movies to rent without repeated. No repeated movies.
 */
list<string> ClubeVideo::titulosDisponiveis() const
{
	list<string> titles;

	for(unsigned i = 0; i < filmes.size(); i++){
		bool add = true;
		list<string>::iterator it = titles.begin();
		while(it != titles.end()){
			if(*it == filmes.at(i).getTitulo()){
				add = false;
				break;
			}
			it++;
		}
		if(add) titles.push_back(filmes.at(i).getTitulo());
	}

	titles.sort();
	return titles;
}

// Available movie
bool ClubeVideo::tituloDisponivel(string umTitulo) const
{
	for(auto&& movie: filmes){
		if(movie.getTitulo() == umTitulo) return true;
	}
	return false;
}

// reserved movies for renting
string ClubeVideo::imprimirListaDeEspera() const
{
	list<string> pl;
	queue<PedidoCliente> w = pedidos;
	while(w.size()){
		pl.push_back(w.front().getTituloFilme());
		w.pop();
	}
	pl.sort();
	ostringstream oss;
	for(list<string>::iterator it = pl.begin(); it != pl.end(); it++){
		oss << *it << "\n";
	}
	return oss.str();
}

// Rent a movie if exists
void ClubeVideo::alugar(string umNome, string umTitulo)
{
	if(!existeFilme(umTitulo)) throw FilmeInexistente(umTitulo);

	Cliente *client = NULL;
	for(auto&& cli : clientes){
		if(cli.getNome() == umNome){
			client = &cli;
			break;
		}
	}

	if(!client){
		Cliente c(umNome);
		clientes.push_back(c);
		client = &clientes.back();
	}

	for(auto it = filmes.begin(); it != filmes.end();it++){
		if(it->getTitulo() == umTitulo){
			it->addEmprestimos();
			client->addFilme(*it);
			filmes.erase(it);
			return;
		}
	}
	PedidoCliente pedido(umNome,umTitulo);
	pedidos.push(pedido);
}

// Return the movie from stack
Filme Cliente::devolver(string umTitulo)
{
	stack<Filme> s_movies;
	Filme movie("");
	while(filmesEmprestados.size()){
		if(filmesEmprestados.top().getTitulo() == umTitulo){
			movie = filmesEmprestados.top();
			filmesEmprestados.pop();
			break;
		}
		s_movies.push(filmesEmprestados.top());
		filmesEmprestados.pop();
	}
	while(s_movies.size()){
		filmesEmprestados.push(s_movies.top());
		s_movies.pop();
	}
	return movie;
}

void ClubeVideo::devolver(string umNome, string umTitulo)
{
	for(unsigned i = 0; i < clientes.size(); i++){
		if(clientes.at(i).getNome() == umNome){
			Filme movie = clientes.at(i).devolver(umTitulo);
			filmes.push_back(movie);
			queue<PedidoCliente> q_pedidos = pedidos;
			while(pedidos.size()) pedidos.pop();
			bool found = false;
			while(q_pedidos.size()){
				if(q_pedidos.front().getTituloFilme() == umTitulo && !found){
					alugar(q_pedidos.front().getNomeCliente(), umTitulo);
					found = true;
				}else{
					pedidos.push(q_pedidos.front());
				}
				q_pedidos.pop();
			}
			break;
		}
	}
}
