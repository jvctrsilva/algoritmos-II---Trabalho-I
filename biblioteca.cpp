#include <iostream>
#include <time.h> 
#include "biblioteca.hpp"
using namespace std;

void cadastrarLivro(Livro livros[],int tamanho){
    
    string titulo;
    string autor;
    int ano;
    int numeroDeCopias;
    
    cout << "------------------" << endl;
    cout << "Cadastro de Livros" << endl;
    cout << "------------------" << endl;
    cin.ignore();
    cout << "Digite o título do livro: ";
    getline(cin, titulo);
    cout << "Digite o autor: ";
    cin >> ws; // Limpa os espaços em branco do buffer, se houver
    getline(cin >> ws, autor); // Utiliza ws para descartar espaços em branco e getline para ler a linha
    cout << "Digite o ano de publicação: ";
    cin >> ano;
    cout << "Digite o número de cópias: ";
    cin >> numeroDeCopias;
    
    Livro livro;
    livro.titulo = titulo;
    livro.autor = autor;
    livro.ano = ano;
    livro.numeroDeCopias = numeroDeCopias;
    livro.numeroID = 0;

    for(int i = 0; i <  tamanho; i++){
        if(livros[i].titulo.empty()){
            livros[i] = livro;
            cout << "Livro cadastrado!";
            break;
        }
    }
}

void cadastrarUsuario(Usuario usuarios[], int tamanho) {
    string nome;
    int numeroID;

    cout << "--------------------" << endl;
    cout << "Cadastro de Usuários" << endl;
    cout << "--------------------" << endl;

    //Como há o cadastro de tipos distintos de varíaveis, é necessário dessa função para limpar.
    cin.ignore(10000, '\n'); // 10000 é um número grande o suficiente para limpar o buffer

    cout << "Digite o nome do usuário: ";
    getline(cin, nome);
    cout << "Digite o número de identificação: ";
    cin >> numeroID;

    // Criando um novo usuário com os dados inseridos
    Usuario usuario;
    usuario.nome = nome;
    usuario.numeroID = numeroID;

    // Adicionando o usuário ao array
    bool usuarioCadastrado = false;
    for(int i = 0; i < tamanho; i++) {
        if(usuarios[i].nome.empty()) {
            usuarios[i] = usuario;
            usuarioCadastrado = true;
            cout << "Usuário cadastrado!" << endl;
            break;
        }
    }

    if (!usuarioCadastrado) {
        cout << "Não foi possível cadastrar o usuário. Limite de usuários atingido." << endl;
    }
}

float calcularMulta(time_t dataAtual, time_t dataDevolucao, float multaDiaria){

		const int segundosDia = 60 * 60 * 24;

		int diasRestantes = (dataAtual - dataDevolucao) / segundosDia;

		if(diasRestantes <= 0){
				return 0.0;
		}

		return diasRestantes * multaDiaria;
}

void emprestarLivro(Livro livros[], Usuario usuarios[],
                    Emprestimo emprestimos[], Multa multas[], int tamanho,
                    time_t dataAtual, float multaDiaria) {

  int codigo, escolha;
  string nomeTitulo;
  int prazo;

  cout << "----------------------" << endl;
  cout << "Empréstimo e Devolução" << endl;
  cout << "----------------------" << endl;
  cout << "(1) Emprestar. " << endl;
  cout << "(2) Devolver." << endl;
  cin >> escolha;

  switch (escolha) {
  case 1: {
    cout << "Digite seu número ID: ";
    cin >> codigo;
    cin.ignore();
    cout << "Digite o título do livro que você deseja emprestar: ";
    getline(cin, nomeTitulo);

    int idUsuario;
    bool validarUsuario = false;
    int idLivro;
    bool validarLivro = false;

    for (int i = 0; i < tamanho; i++) {
      if (usuarios[i].numeroID == codigo) {
        idUsuario = i;
        validarUsuario = true;
        break;
      }
    }

    for (int i = 0; i < tamanho; i++) {
      if (livros[i].titulo == nomeTitulo) {
        idLivro = i;
        validarLivro = true;
        break;
      }
    }

    if (!validarUsuario) {
      cout << "Usuário não encontrado." << endl;
    }

    if (!validarLivro) {
      cout << "Livro não encontrado" << endl;
    }

    if (validarLivro && validarUsuario && livros[idLivro].numeroDeCopias > 0) {
      livros[idLivro].numeroDeCopias = livros[idLivro].numeroDeCopias - 1;

      time_t dataDevolucao;
      cout << "Digite a data de devolução (DD MM AAAA): ";
      int dia, mes, ano;
      cin >> dia >> mes >> ano;

      tm converterData = {0};
      converterData.tm_year = ano - 1900;
      converterData.tm_mon = mes - 1;
      converterData.tm_mday = dia;
      dataDevolucao = mktime(&converterData);

      for (int i = 0; i < tamanho; i++) {
        if (emprestimos[i].livro.titulo.empty()) {
          emprestimos[i].livro = livros[idLivro];
          emprestimos[i].usuario = usuarios[idUsuario];
          emprestimos[i].dataEmprestimo = dataAtual;
          emprestimos[i].dataDevolucao = dataDevolucao;
          emprestimos[i].devolveu = false;
          cout << "Empréstimo realizado" << endl;
          break;
        }
      }
    }

    break;
  }
  case 2: {
    cout << "Digite seu número ID: ";
    cin >> codigo;
    cin.ignore();
    cout << "Digite o título do livro que você deseja emprestar: ";
    getline(cin, nomeTitulo);

    int idUsuario;
    bool validarUsuario = false;
    int idLivro;
    bool validarLivro = false;

    for (int i = 0; i < tamanho; i++) {
      if (usuarios[i].numeroID == codigo) {
        idUsuario = i;
        validarUsuario = true;
        break;
      }
    }

    for (int i = 0; i < tamanho; i++) {
      if (livros[i].titulo == nomeTitulo) {
        idLivro = i;
        validarLivro = true;
        break;
      }
    }

    if (!validarUsuario) {
      cout << "Usuário não encontrado." << endl;
    }

    if (!validarLivro) {
      cout << "Livro não encontrado" << endl;
    }

    for (int i = 0; i < tamanho; i++) {
      if (emprestimos[i].livro.titulo == nomeTitulo &&
          emprestimos[i].usuario.numeroID == codigo &&
          !emprestimos[i].devolveu) {

        emprestimos[i].devolveu = true;
        emprestimos[i].dataDevolveu = dataAtual;

        for (int j = 0; j < tamanho; j++) {
          if (livros[j].titulo == nomeTitulo) {
            livros[j].numeroDeCopias++;
          }
        }

        cout << dataAtual << endl;
        cout << emprestimos[i].dataDevolucao << endl;

        float multa =
            calcularMulta(dataAtual, emprestimos[i].dataDevolucao, 2.0);

        if (multa > 0.0) {
          cout << "Gerada uma multa: R$" << multa << endl;

          int multaID;
          for (int j = 0; j < tamanho; j++) {
            if (multas[i].usuario.nome.empty()) {
              multaID = j + 1;
            }
          }

          multas[i].numeroID = multaID;
          multas[i].usuario = usuarios[idUsuario];
          multas[i].emprestimo = emprestimos[i];
          multas[i].valor = multa;
          multas[i].pago = false;
        }
      }
    }
  }
  }
}
void pesquisarLivro(int escolha, Livro livros[], Usuario usuarios[], Emprestimo emprestimos[], int tamanho){
    
    string autor;
    string titulo;
    int ano, codigo;
    string sidentificacao;
    int intidentificacao;
    
    if (escolha == 1 || escolha == 2){ 
            
        if (escolha == 1){
            cin.ignore();
            cout <<"Digite o título do livro: " << endl;
            getline(cin, sidentificacao);
        }
        if (escolha == 2){
            cin.ignore();
            cout << "Digite o nome do Autor: " << endl;
            getline(cin, sidentificacao);
        }
        for (int i = 0; i < tamanho; i++){
            if (livros[i].titulo == sidentificacao && livros[i].numeroDeCopias > 0 || livros[i].autor == sidentificacao && livros[i].numeroDeCopias > 0){
                cout << "Livro:" << livros[i].titulo << endl;
                cout << "Autor:" << livros[i].autor << endl; 
                cout << "Ano de publicação:" << livros[i].ano << endl;
                cout << "Número de cópias:" << livros[i].numeroDeCopias << endl;
                }
            }
    }
    if (escolha == 3 || escolha == 4){
        
        if (escolha == 3){
            cout << "Digite o ano de publicação: " << endl;
            cin >> intidentificacao;
        }
        if (escolha == 4){
            cout << "Digite o código do usuário: " << endl;
            cin >> intidentificacao;
        }
            for (int i = 0; i < tamanho; i++){
                if (livros[i].ano == intidentificacao && livros[i].numeroDeCopias > 0 || emprestimos[i].usuario.numeroID == intidentificacao && livros[i].numeroDeCopias > 0 ){
                    cout << "Livro:" << livros[i].titulo << endl;
                    cout << "Autor:" << livros[i].autor << endl; 
                    cout << "Ano de publicação:" << livros[i].ano << endl;
                    cout << "Número de cópias:" << livros[i].numeroDeCopias << endl;
                }
            }
    }
}