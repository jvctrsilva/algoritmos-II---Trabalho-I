#ifndef BIBLIOTECA_HPP
#define BIBLIOTECA_HPP
using namespace std;

    struct Livro{
        string titulo;
        string autor;
        int ano;
        int numeroDeCopias;
        int numeroID;
        
        
    };
    
    struct Usuario{
        string nome;
        int numeroID;
    };
    
    struct Emprestimo {
				Livro livro;
				Usuario usuario;
				time_t dataEmprestimo;
				time_t dataDevolucao;
				time_t dataDevolveu;
				bool devolveu;
		};

		struct Multa {
				int numeroID;
				Usuario usuario;
				Emprestimo emprestimo;
				float valor;
				bool pago = false;
		};

void cadastrarLivro(Livro livros[], int tamanho);
void cadastrarUsuario(Usuario usuarios[], int tamanho);
void emprestarLivro(Livro livros[], Usuario usuarios[], Emprestimo emprestimos[], Multa multas[], int tamanho, time_t dataAtual, float multaDiaria);
void pesquisarLivro(int escolha, Livro livros[], Usuario usuarios[], Emprestimo emprestimos[], int tamanho);
float calcularMulta(time_t dataAtual, time_t dataDevolucao, float multaDiaria = 2.0);

#endif