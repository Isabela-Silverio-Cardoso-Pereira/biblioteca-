#include <iostream>

#include <string>

#include <cstdlib>

using namespace std;

const int TAMANHO_TABELA_HASH = 10;

struct Autor {
  int matricula;
  string nome;
  int quantdLivros;
};

struct Livro {
  int matricula;
  string titulo;
  int ano;
  string genero;
  Autor autores[3];
  int numAutores = 0;
  string editora;
};

struct Revista {
  int matricula;
  string titulo;
  int ano;
  int edicao;
};

struct Usuario {
  int matricula;
  int devolucao;
  string nome;
  string email;
};

struct Editora {
  int matricula;
  string nome;
  string endereco;
  int anoFundacao;
};

template < typename T >
  struct No {
    T item;
    No * proximo;
  };

int funcaoHash(int matricula) {
  return matricula % TAMANHO_TABELA_HASH;
}

template < typename T >
  No < T > * tabelaHash[TAMANHO_TABELA_HASH];

template < typename T >
  void inicializarTabela() {
    for (int i = 0; i < TAMANHO_TABELA_HASH; i++) {
      tabelaHash < T > [i] = nullptr;
    }
  }

// Função para inserir um novo item
template < typename T >
  void inserirItem(T novoItem) {
    int indice = funcaoHash(novoItem.matricula);
    No < T > * novoNo = new No < T > ;
    novoNo -> item = novoItem;
    novoNo -> proximo = tabelaHash < T > [indice];
    tabelaHash < T > [indice] = novoNo;
  }

// Função para buscar um item pela matricula
template < typename T >
  T * buscarItem(int matricula) {
    int indice = funcaoHash(matricula);
    No < T > * aux = tabelaHash < T > [indice];

    while (aux != nullptr) {
      if (aux -> item.matricula == matricula) {
        return & aux -> item;
      }
      aux = aux -> proximo;
    }

    return nullptr;
  }

// Função para remover um item
template < typename T >
  bool removerItem(int matricula) {
    int indice = funcaoHash(matricula);
    No < T > * auxP = tabelaHash < T > [indice];
    No < T > * auxA = nullptr;

    while (auxP != nullptr) {
      if (auxP -> item.matricula == matricula) {
        if (auxA == nullptr) {
          tabelaHash < T > [indice] = auxP -> proximo;
        } else {
          auxA -> proximo = auxP -> proximo;
        }
        delete auxP;
        return true;
      }
      auxA = auxP;
      auxP = auxP -> proximo;
    }

    return false;
  }

// Função para alterar informações
void alterarLivro(int matricula, string novoTitulo, int novoAno, string novoGenero) {
  Livro * livro = buscarItem < Livro > (matricula);
  if (livro != nullptr) {
    livro -> titulo = novoTitulo;
    livro -> ano = novoAno;
    livro -> genero = novoGenero;
    cout << "Livro atualizado com sucesso." << endl;
  } else {
    cout << "Livro não encontrado." << endl;
  }
}

// Função para alterar informações
void alterarRevista(int matricula, string novoTitulo, int novoAno, int novaEdicao) {
  Revista * revista = buscarItem < Revista > (matricula);
  if (revista != nullptr) {
    revista -> titulo = novoTitulo;
    revista -> ano = novoAno;
    revista -> edicao = novaEdicao;
    cout << "Revista atualizada com sucesso." << endl;
  } else {
    cout << "Revista não encontrada." << endl;
  }
}

// Função para adicionar autor a um livro
bool adicionarAutorAoLivro(int matriculaLivro, Autor novoAutor) {
  Livro * livro = buscarItem < Livro > (matriculaLivro);
  if (livro != nullptr) {
    if (livro -> numAutores < 3) {
      livro -> autores[livro -> numAutores] = novoAutor;
      livro -> numAutores++;
      cout << "Autor adicionado ao livro." << endl;
      return true;
    } else {
      cout << "Esse livro já possui 3 autores." << endl;
      return false;
    }
  } else {
    cout << "Livro não encontrado." << endl;
    return false;
  }
}

void listarLivros() {
  cout << "Lista de Livros:" << endl;
  for (int i = 0; i < TAMANHO_TABELA_HASH; i++) {
    No < Livro > * aux = tabelaHash < Livro > [i];
    while (aux != nullptr) {
      cout << "Matricula: " << aux -> item.matricula << ", Titulo: " << aux -> item.titulo << endl;
      aux = aux -> proximo;
    }
  }
}
//PESQUISAR PELO TITULO
void pesquisarLivroTitulo(string & titulo) {
  for (int i = 0; i < TAMANHO_TABELA_HASH; i++) {
    No < Livro > * aux = tabelaHash < Livro > [i];
    while (aux != nullptr) {
      if (aux -> item.titulo == titulo) {
        cout << "Livro encontrado: " << aux -> item.titulo << ", Ano: " << aux -> item.ano << ", Matricula: " << aux -> item.matricula << " autor: " << aux -> item.autores << endl;
        return;
      }
      aux = aux -> proximo;
    }
  }
  cout << "Livro nao encontrado." << endl;
}

void pesquisarMatricula(int matricula) {
  for (int i = 0; i < TAMANHO_TABELA_HASH; i++) {
    No < Livro > * aux = tabelaHash < Livro > [i];
    while (aux != nullptr) {
      if (aux -> item.matricula == matricula) {
        cout << "Livro encontrado: " << aux -> item.titulo << endl;
        return;
      }
      aux = aux -> proximo;
    }
  }
  cout << "Livro nao encontrado." << endl;
}

void pesquisarAutor(string autor) {
  bool encontrado = false;
  for (int i = 0; i < TAMANHO_TABELA_HASH; i++) {
    No < Livro > * aux = tabelaHash < Livro > [i];
    while (aux != nullptr) {
      for (int j = 0; j < aux -> item.numAutores; j++) {
        if (aux -> item.autores[j].nome == autor) {
          cout << "Livro encontrado: " << aux -> item.titulo << ", Ano: " << aux -> item.ano << ", Matricula: " << aux -> item.matricula << endl;
          encontrado = true;
          break; // Se encontrou, não precisa continuar verificando os autores do mesmo livro
        }
      }
      aux = aux -> proximo;
    }
  }
  if (!encontrado) {
    cout << "Autor não encontrado." << endl;
  }
}

void pesquisarEditora(string editora) {
  bool encontrado = false;
  for (int i = 0; i < TAMANHO_TABELA_HASH; i++) {
    No < Livro > * aux = tabelaHash < Livro > [i];
    while (aux != nullptr) {
      if (aux -> item.editora == editora) {
        cout << "Livro encontrado: " << aux -> item.titulo << ", Ano: " << aux -> item.ano << ", Matricula: " << aux -> item.matricula << endl;
        encontrado = true;
      }
      aux = aux -> proximo;
    }
  }
  if (!encontrado) {
    cout << "Editora não encontrada." << endl;
  }
}
void pesquisarGenero(string genero) {
  bool encontrado = false;
  for (int i = 0; i < TAMANHO_TABELA_HASH; i++) {
    No < Livro > * aux = tabelaHash < Livro > [i];
    while (aux != nullptr) {
      if (aux -> item.genero == genero) {
        cout << "Livro encontrado: " << aux -> item.titulo <<
          ", Ano: " << aux -> item.ano <<
          ", Matricula: " << aux -> item.matricula << endl;
        encontrado = true;
      }
      aux = aux -> proximo;
    }
  }
  if (!encontrado) {
    cout << "Nenhum livro encontrado com o gênero: " << genero << endl;
  }
}

void menu() {
  int opcao;
  do {

    cout << "\n--- ---MENU--- ---" << endl;
    cout << "Escolha uma opcaoo: " << endl;
    cout << "1. Cadastrar (autores e itens)" << endl;
    cout << "2. Buscar" << endl;
    cout << "3. Remover" << endl;
    cout << "4. Alterar" << endl;
    cout << "0. Sair" << endl;
    cin >> opcao;
    cin.ignore();

    switch (opcao) {
    case 1: {
      cout << "1 - Incluir novos autores" << endl;
      cout << "2 - Cadastrar novo livro" << endl;
      cout << "3 - Cadastrar nova revista" << endl;
      cout << "4 - Cadastrar editora" << endl;
      cout << "5 - Cadastrar usuario" << endl;

      int escolha;
      cout << "Escolha uma opcao: ";
      cin >> escolha;

      switch (escolha) {
      case 1:
        // Chamar função para incluir novos autores
        break;
      case 2:
        // Chamar função para cadastrar novo livro
        break;
      case 3:
        // Chamar função para cadastrar nova revista
        break;
      case 4:
        // Chamar função para cadastrar editora
        break;
      case 5:
        // Chamar função para cadastrar usuário
        break;
      default:
        cout << "Opcao invalida! Tente novamente." << endl;
      }
      break;
    }
    case 2: {

      // Opções de busca
      cout << "1 - Buscar por matricula" << endl;
      cout << "2 - Buscar por titulo" << endl;
      cout << "3 - Buscar por autor" << endl;
      cout << "4 - Buscar por editora" << endl;
      cout << "5 - Buscar por genero" << endl;

      int buscaEscolha;
      cout << "Escolha uma opcao: ";
      cin >> buscaEscolha;
      cin.ignore();

      switch (buscaEscolha) {
      case 1: {
        int matricula;
        cout << "Digite a matricula do livro: " << endl;
        cin >> matricula;
        pesquisarMatricula(matricula);

        break;
      }
      case 2: {
        string titulo;

        cout << "Digite o titulo do livro: " << endl;
        getline(cin, titulo);

        pesquisarLivroTitulo(titulo);
        break;
      }
      case 3: {
        string autor;
        cout << "Digite o nome do autor: " << endl;
        getline(cin, autor);
        pesquisarAutor(autor);
        break;

        break;

      }
      case 4: {
        string editora;
        cout << "Digite o nome da editora: " << endl;
        getline(cin, editora);
        pesquisarEditora(editora);
        break;
      }
      case 5: {
        string genero;
        cout << "Digite o genero do livro: " << endl;
        getline(cin, genero);
        pesquisarGenero(genero);
        break;
      }

      }
    }
    case 3: {
      // Opções para remover
      cout << "1 - Remover autor" << endl;
      cout << "2 - Remover livro" << endl;
      cout << "3 - Remover revista" << endl;
      cout << "4 - Remover editora" << endl;

      int removerEscolha;
      cout << "Escolha uma opcao: ";
      cin >> removerEscolha;

      // Chamar funções de remoção conforme a escolha
      break;
    }
    case 4: {
      // Opções para alterar
      cout << "1 - Alterar autor" << endl;
      cout << "2 - Alterar livro" << endl;
      cout << "3 - Alterar revista" << endl;
      cout << "4 - Alterar editora" << endl;

      int alterarEscolha;
      cout << "Escolha uma opcao: ";
      cin >> alterarEscolha;

      // Chamar funções de alteração conforme a escolha
      break;
    }
    case 0:
      cout << "Saindo do sistema..." << endl;
      return;
    default:
      cout << "Opcao invalida! Tente novamente." << endl;
    }
  } while (true);
}

int main() {
  inicializarTabela < Livro > ();

  // Inserir Livros
  Autor a1 = {201,"Autor Um",5};
  Autor a2 = {202,"Autor Dois",3};

  Livro l1 = {
    101,"Como ficar rico",2010,"Auto-Ajuda",{a1,a2},2,"Editora Exemplo"};
  inserirItem(l1);
  listarLivros();
  menu();

  // Buscar um Livro
  Livro * resultado = buscarItem < Livro > (111); // Deve encontrar l3
  if (resultado != nullptr) {
    cout << "Livro encontrado: " << resultado -> titulo << endl;
  } else {
    cout << "Livro não encontrado." << endl;
  }

  // Remover um Livro
  bool removido = removerItem < Livro > (101); // Remover "Como ficar rico"
  if (removido) {
    cout << "Livro removido." << endl;
  } else {
    cout << "Livro não encontrado." << endl;
  }

  // Alterar Livro
  alterarLivro(111, "Bolsonaro: Uma historia de Amor e Golden Shower", 2021, "Romance");

  // Adicionar autores ao livro
  /* Autor a1 = {201, "Bolsonaro", 5};
   Autor a2 = {202, "Marçal", 61};
   Autor a3 = {203, "Primo-Rico", 6};
   adicionarAutorAoLivro(102, a2);
   adicionarAutorAoLivro(111, a1);*/

  return 0;
}