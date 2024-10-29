#include <iostream>
#include <limits>
#include <cstdio>
#include <cctype>
#include <cstring>

using namespace std;

struct emprestimo {
    char emprestimo[20], devolucao[20], usuario[255];

};

struct cadastro {
    char autor[255], titulo[255], editora[50], area[50];
    int codigo, qtd_pag;
    bool disponivel = false;
    struct emprestimo  emp;
};

struct cadastro cad;
string escolha, nome_e;
int opc, codigo_e;
int pos;
bool encontrado = false;
void menu(){

    cout << "==================================" <<endl;
    cout << "               MENU               " <<endl;
    cout << "==================================" <<endl;
    cout << "01) CADASTRO " << endl;
    cout << "02) ALTERACAO " << endl;
    cout << "03) EXCLUSAO " << endl;
    cout << "04) EMPRESTIMO" << endl;
    cout << "05) DEVOLUCAO" << endl;
    cout << "06) CONSULTA DE LIVROS " << endl;
    cout << "07) LIVROS DISPONIVEIS" << endl;
    cout << "08) LISTAGEM DE LIVROS " << endl;
    cout << "09) SAIR " << endl;

}


int main () {

    FILE *ARQUIVOSDADOS;
    FILE *ARQUIVOSDADOS_AUX;

    menu();
    cout << "Deseja escolher qual opção? ";
    cin >> opc;
    cin.get();
    cout << "\e[2j" << "\e[0;0H" ;

    while(opc != 9){
        switch (opc){
        case 1:
                cout << "Deseja cadastrar um novo livro? ";
                cin >> escolha;

                for (char& c:escolha){
                    c = tolower(c);
                }
                while(escolha == "sim"){
                    ARQUIVOSDADOS = fopen("prova.dat", "ab+");
                    if(ARQUIVOSDADOS == NULL){
                        ARQUIVOSDADOS = fopen("prova.dat", "wb");
                        if(ARQUIVOSDADOS == NULL){
                            cout << "ERRO AO ABRIR O ARQUIVO! " <<endl;
                        }
                        
                    } else {
                        cout << "------------------ CADASTRO --------------------" <<endl;
                        cout << "CODIGO: ";
                        cin >> cad.codigo;
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "TITULO: ";
                        cin.get(cad.titulo, 254);
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "AUTOR: ";
                        cin.get(cad.autor, 254);
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "AREA: ";
                        cin.get(cad.area, 49);
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "EDITORA: ";
                        cin.get(cad.editora, 49);
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "QUANTIDADE DE PAGINA: ";
                        cin >> cad.qtd_pag;
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        fwrite(&cad, sizeof(struct cadastro),1,ARQUIVOSDADOS);
                        cout << "LIVRO CADASTRADO COM SUCESSO! " <<endl;
                        fclose(ARQUIVOSDADOS);
                    }

                    cout << "Deseja cadastar outro livro? ";
                    cin >> escolha;
                }
            break;
        case 2:
            cout << "================================================" <<endl;
            cout << "                  ALTERACAO                     " << endl;
            cout << "================================================" <<endl;
            cout << "Deseja fazer uma alteracao? ";
            cin >> escolha;
            for (char& c:escolha){
                c = tolower(c);
            }
            while(escolha == "sim"){
                        cout << "Informe o codigo que voce digitou errado: ";
                        cin >> codigo_e;
                        cin.get();
                        ARQUIVOSDADOS = fopen("prova.dat", "rb+");
                        if(ARQUIVOSDADOS == NULL){
                            cout << "ERRO AO ABRIR O ARQUIVO!";
                            
                        } else{
                            pos = -1;
                            while(fread(&cad, sizeof(struct cadastro),1,ARQUIVOSDADOS)==1){
                                
                              pos++;
                                if(codigo_e == cad.codigo){
                                    cout << "TITULO: ";
                                    cin.get(cad.titulo, 254);
                                    cin.ignore(numeric_limits<streamsize>::max(),'\n');
                                    cout << "AUTOR: ";
                                    cin.get(cad.autor, 254);
                                    cin.ignore(numeric_limits<streamsize>::max(),'\n');
                                    cout << "EDITORA: ";
                                    cin.get(cad.editora, 49);
                                    cin.ignore(numeric_limits<streamsize>::max(),'\n');
                                    cout << "AREA: ";
                                    cin.get(cad.area, 49);
                                    cin.ignore(numeric_limits<streamsize>::max(),'\n');
                                    cout << "QUANTIDADE DE PAGINA: ";
                                    cin >> cad.qtd_pag;
                                    cin.ignore(numeric_limits<streamsize>::max(),'\n');
                                    fseek(ARQUIVOSDADOS, sizeof(struct cadastro)*pos, SEEK_SET);
                                    if(fwrite(&cad, sizeof(struct cadastro), 1, ARQUIVOSDADOS)==1){
                                        cout << "ALTERACAO FEITA COM SUCESSO! " << endl;
                                    } else{
                                        cout << "Nao foi cadastrado! " << endl;
                                        break;
                                    }

                                    cout << "DE ENTER PARA SAIR: " << endl;
                                    cin.get();
                                    fclose(ARQUIVOSDADOS);
                                    break;
                                }
                            }
                        }
                    cout << "DESEJA FAZER UMA OUTRA ALTERACAO? ";
                    cin >> escolha;
                    for(char& c:escolha){
                        c = tolower(c);
                    }
                }

            break;

        case 3:
            cout << "============================================== " << endl;
            cout << "                    EXCLUSAO                   " << endl;
            cout << "============================================== " << endl;
            cout << "Deseja fazer a exclusao do livro? ";
            cin >> escolha;
            while(escolha == "sim") {
                cout << "Informe o codigo que voce deseja excluir: ";
                cin >> codigo_e;
                cin.get();
                ARQUIVOSDADOS_AUX = fopen("prova.dat.aux", "wb");
                ARQUIVOSDADOS = fopen("prova.dat", "rb");
                if (ARQUIVOSDADOS == NULL || ARQUIVOSDADOS_AUX == NULL){
                    cout << "ERRO AO ABRIR O(s) ARQUIVO(s)!" <<endl;

                } else{
                    while(fread(&cad, sizeof(struct cadastro),1,ARQUIVOSDADOS)==1){
                        if(cad.codigo != codigo_e){
                            fwrite(&cad, sizeof(struct cadastro),1,ARQUIVOSDADOS_AUX);
                        }

                    }
                    fclose(ARQUIVOSDADOS_AUX);
                    fclose(ARQUIVOSDADOS);
                    remove("prova.dat");
                    rename("prova.dat.aux", "prova.dat");
                    cout << "ARQUIVO EXCLUIDO! ";
                    cin.ignore();
                    
                }
                cout << "Deseja fazer outra exclusao? ";
                cin >> escolha;
                for(char& c:escolha){
                    c = tolower(c);
                }
                
            }
            break;
        case 4: 
                cout << "============================================"<<endl;
                cout << "                EMPRESTIMO                  " <<endl;
                cout << "============================================"<<endl;
                cout << "Deseja fazer um emprestimo? ";
                cin >> escolha;

                for (char& c: escolha){
                    c = tolower(c);
                }
                while(escolha == "sim"){
                    cout << "Informe o codigo do livro: ";
                    cin >> codigo_e;
                    cin.get();
                    ARQUIVOSDADOS = fopen("prova.dat", "rb+");
                    if(ARQUIVOSDADOS == NULL){
                        cout << "ERRO AO ABRIR O ARQUIVO! " << endl;

                    } else{
                        while(fread(&cad, sizeof(struct cadastro),1, ARQUIVOSDADOS)==1){
                            if(cad.codigo == codigo_e){
                                fseek(ARQUIVOSDADOS, -sizeof(struct cadastro), SEEK_CUR);
                                cout << "NOME: ";
                                cin.get(cad.emp.usuario, 254);
                                cin.ignore(numeric_limits<streamsize>::max(),'\n');
                                cout << "DATA EMPRESTIMO: ";
                                cin.get(cad.emp.emprestimo,19);
                                cin.ignore(numeric_limits<streamsize>::max(),'\n');
                                cout << "DATA DEVOLUCAO: ";
                                cin.get(cad.emp.devolucao, 19);
                                cin.ignore(numeric_limits<streamsize>::max(),'\n');
                                cad.disponivel = false;
                                if(fwrite(&cad, sizeof(struct cadastro),1, ARQUIVOSDADOS)==1){
                                    cout << "EMPRESTIMO FEITO!" << endl;
                                } else{
                                    cout << "ERRO!"<<endl;
                                }
                            }
                        }
                    }fclose(ARQUIVOSDADOS);
                    cout << "Deseja fazer um emprestimo? ";
                    cin >> escolha;

                    for(char& c:escolha){
                        c = tolower (c);
                    }
                }
            break;
        case 5:
            cout << "=========================================" <<endl;
            cout << "                DEVOLUCAO                " <<endl;
            cout << "=========================================" <<endl;
            cout << "Deseja fazer uma devolucao? ";
            cin >> escolha;
            for(char& c:escolha){
                c = tolower(c);
            }
            while(escolha == "sim"){
                cout << "Informe o codigo do livro: ";
                cin >> codigo_e;
                ARQUIVOSDADOS = fopen("prova.dat", "rb+");
                if(ARQUIVOSDADOS == NULL){
                    cout << "ERRO AO ABRIR O ARQUIVO! ";
                } else{
                    while(fread(&cad, sizeof(struct cadastro),1,ARQUIVOSDADOS)==1){
                        fseek(ARQUIVOSDADOS, -sizeof(struct cadastro), SEEK_CUR);
                        strcpy(cad.emp.usuario, "");
                        strcpy(cad.emp.emprestimo, "");
                        strcpy(cad.emp.devolucao, "");
                        encontrado = true;
                        if(fwrite(&cad, sizeof(struct cadastro),1,ARQUIVOSDADOS)==1){
                            cout << "DEVOLUCAO FEITA COM SUCESSO!" <<endl;
                        } else{
                            cout << "ERRO AO FAZER A DEVOLUCAO! " << endl;
                        }
                            
                        break;
                    } fclose(ARQUIVOSDADOS);
                    
                } if(!encontrado){
                    cout << "ESSE LIVRO NAO EXISTE! " << endl;
                }
                cout << "Deseja fazer outra devolucao? ";
                cin >> escolha;
                for(char& c:escolha){
                    c = tolower(c);
                }
            }
            break;
        case 6:
            cout << "=================================================" <<endl;
            cout << "                    CONSULTA                     " <<endl;
            cout << "=================================================" <<endl;
            cout << "Deseja fazer uma consulta de livros? ";
            cin >> escolha;
            for (char& c:escolha){
                c = tolower(c);
            }
            while(escolha == "sim"){
                cout << "Informe o codigo do livro que deseja consultar: ";
                cin >> codigo_e;
                cin.get();
                ARQUIVOSDADOS = fopen("prova.dat", "rb");
                if(ARQUIVOSDADOS == NULL){
                    cout << "ERRO AO ABRIR O ARQUIVO! ";
                }else{
                    while(fread(&cad, sizeof(struct cadastro),1,ARQUIVOSDADOS)==1){
                        if (codigo_e == cad.codigo){
                            cout << "CODIGO: " << cad.codigo << endl;
                            cout << "TITULO: " << cad.titulo << endl;
                            cout << "AUTOR: " << cad.autor << endl;
                            cout << "EDITORA: " << cad.editora << endl;
                            cout << "AREA: "<< cad.area << endl;
                            cout << "QUANTIDADE DE PAGINA: " <<cad.qtd_pag <<endl;
                            cout << "-----------------------------" << endl;
                        }
                        if(cad.disponivel == false){
                            cout << "ESTA EMPRESTADO!" << endl;
                            cout << "Nome: " << cad.emp.usuario << endl;
                            cout << "EMPRESTADO: " << cad.emp.emprestimo << endl;
                            cout << "DEVOLUCAO: "<< cad.emp.devolucao << endl;
                        } else if (cad.disponivel == true){
                            cout << "Disponivel! " << endl;
                            }
                    }
                }fclose(ARQUIVOSDADOS);
                cout << "Deseja fazer consulta de outro livro? ";
                cin >> escolha;

                for (char& c:escolha){
                    c =tolower (c);
                }
            }
            break;
        case 7:
            cout << "=================================" <<endl;
            cout << "       LIVROS DISPONIVEIS        " <<endl;
            cout << "=================================" <<endl;
            cout << "Deseja ver os livros disponiveis? ";
            cin >> escolha;

            while(escolha == "sim"){
                ARQUIVOSDADOS = fopen("prova.dat", "rb");
                if (ARQUIVOSDADOS == NULL){
                    cout << "ERRO AO ABRIR O ARQUIVO! " << endl;
                }else{
                    while(fread(&cad, sizeof(struct cadastro),1,ARQUIVOSDADOS)==1){
                        if(cad.disponivel == true){
                            cout << "CODIGO: " << cad.codigo << endl;
                            cout << "TITULO: " << cad.titulo << endl;
                            cout << "AUTOR " << cad.autor << endl;
                            cout << "EDITORA: " << cad.editora << endl;
                            cout << "AREA: " << cad.area << endl;
                            cout << "Quantidade de pagina: " << cad.qtd_pag << endl;
                            cout << "------------------------------------------- " << endl;
                        }
                    }
                    cin.ignore();
                    fclose(ARQUIVOSDADOS);
                }

                cout << "Deseja ver os livros disponiveis denovo? ";
                cin >> escolha;

                for (char& c:escolha){
                    c = tolower (c);
                }
            }
            break;
        case 8:
                cout << "==========================================" <<endl;
                cout << "              LIVROS CADASTRADOS          " <<endl;
                cout << "==========================================" <<endl;
                ARQUIVOSDADOS = fopen("prova.dat", "rb");
                if(ARQUIVOSDADOS == NULL){
                    cout << "ERRO AO ABRIR O ARQUIVO!" << endl;

                } else{
                    fread(&cad, sizeof(struct cadastro),1,ARQUIVOSDADOS);
                    while(!feof(ARQUIVOSDADOS)){
                        cout << "CODIGO: " << cad.codigo << endl;
                        cout << "TITULO: " << cad.titulo << endl;
                        cout << "AUTOR: " << cad.autor << endl;
                        cout << "EDITORA: " << cad.editora << endl;
                        cout << "AREA: "<< cad.area << endl;
                        cout << "QUANTIDADE DE PAGINA: " <<cad.qtd_pag <<endl;
                        cout << "-----------------------------" << endl;
                        fread(&cad, sizeof(struct cadastro),1, ARQUIVOSDADOS);
                    }
                    fclose(ARQUIVOSDADOS);
                    cin.ignore();
                    cout << "DE ENTER PARA SAIR: " << endl;
                }

            break;
        
        default:
            cout << "Informe um opçao valida! " << endl;
            break;
        }
        menu();
        cout << "Deseja escolher qual opção? " << endl;
        cin >> opc;
        cin.get();
        cout << "\e[2j" << "\e[0;0H" ;

    }
}