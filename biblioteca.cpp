
#include <iostream> // biblioteca principal
#include <cstdio> // biblioteca para funcionar os arquivos
#include <limits> // biblioteca para utilizar os numeric_limits
#include <cstring> // serve para usar pra alterar valor de uma variavel dentro de arquivo. Ex: strcpy e strcm //
//#include <conio.h> biblioteca para ler um caracter sem dar enter
#include <cctype> // biblioteca para usar o tolower(deixar minusculo)

using namespace std;

void menu(){

    cout << "------------------------------------- " << endl;
    cout << "01) CADASTRO " <<endl;
    cout << "02) ALTERAÇAO " << endl;
    cout << "03) EXCLUSAO " << endl;
    cout << "04) EMPRESTIMO " << endl;
    cout << "05) DEVOLUCAO " << endl;
    cout << "06) CONSULTA DE LIVRO " << endl;
    cout << "07) LIVROS DISPONIVEIS " <<endl;
    cout << "08) lISTAGEM DE LIVROS " << endl;
    cout << "09) SAIR " << endl;
    cout << "------------------------------------- " << endl;
}

int main (){

    struct cadastro {
        char emprestimo[15], devolucao[15], usuario[100];

    };

    struct livro {
        char titulo [100], editora[100], autor[100], area[15];
        int quant_pag, codigo;
        bool liv_disponivel;
        struct cadastro cad;
    };

    struct livro liv;
    char opc;
    string escolha, quero, inf_errada, resposta;
    int codigo_e, pos, busca_exc, busca, exc;
    int liv_disponivel = 0;
    //bool livro_encontrado = false;  
    FILE *DADOSARQUIVOS;
    FILE *DADOSARQUIVOS_AUX; //Criado os arquivos auxiliar para fazer a exclusao de 1 e passar para o outro!

    menu();

    cout << "Escolha uma opcao: ";
    cin >> opc;
    system("cls");

    while(opc != '9'){
        switch (opc){
                case '1':
                    cout << "Deseja cadastrar um novo livro? ";
                    cin >> escolha;
                    for (char& c : escolha){
                        c = tolower(c);
                    }

                    while(escolha == "sim"){
                        DADOSARQUIVOS = fopen("arquivo.data", "ab+"); // Abre o arquivo para anexar informaçoes
                        if(DADOSARQUIVOS == NULL){
                            DADOSARQUIVOS = fopen("arquivo.data", "wb"); // abre para escrever do 0
                                if(DADOSARQUIVOS == NULL){
                                    cout << "ERRO AO ABRIR O ARQUIVO! " << endl;
                                }
                            
                        } else {
                            cout << "----------- CADASTRO ---------- " << endl;
                            cout << "VAMOS CADASTRAR UM NOVO LIVRO " << endl;
                            cout << "Informe o codigo do livro: ";
                            cin >> liv.codigo;
                            cin.get(); // Para quebrar o buffer de um int para caracter
                            cout << "TITULO: ";
                            cin.get(liv.titulo, 99);
                            cin.ignore(numeric_limits<streamsize>::max(),'\n');
                            cout << "Informe a editora do livro: ";
                            cin.get(liv.editora, 99);
                            cin.ignore(numeric_limits<streamsize>::max(),'\n');
                            cout << "Informe o autor: ";
                            cin.get(liv.autor, 99);
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            cout << "Informe a area do livro: ";
                            cin.get(liv.area, 14);
                            cin.ignore(numeric_limits<streamsize>::max(),'\n');
                            cout << "Informe a quantidade de pagina do livro: ";
                            cin >> liv.quant_pag;
                            fwrite(&liv, sizeof(struct livro),1, DADOSARQUIVOS);
                            fclose(DADOSARQUIVOS);

                        }
                        cout << "Deseja cadastar outro livro? ";
                        cin >> escolha;
                        system("cls");
                    }
                    break;
                // system("cls");
                case '2' :
                    cout << "--------------- ALTERACAO --------------" << endl;
                    cout << "Voce digitou uma informaçao errada ne? " << endl;
                    cout << "Informe o codigo do livro que voce digitou errado: ";
                    cin >> codigo_e;
                    cin.get(); // alterado para cin.get
                    DADOSARQUIVOS = fopen("arquivo.data", "rb+"); // abre o arquivo para ler e escrever
                    if (DADOSARQUIVOS == NULL) {
                        cout << "ERRO AO ABRIR O ARQUIVO! ";
                    } else {
                        fread(&liv, sizeof(struct livro),1,DADOSARQUIVOS);
                        while(!feof(DADOSARQUIVOS)){
                            if(codigo_e == liv.codigo){
                                fseek(DADOSARQUIVOS, -sizeof(struct livro), SEEK_CUR);
                                cout << "O que voce deseja alterar? ";
                                cin >> inf_errada;
                                cin.get();

                                //for (char &c : inf_errada) {
                                //    c = tolower(c); // transforma a resposta para minusculo
                                //}

                                if(inf_errada == "tudo"){
                                    cout << "Voce esta de sacanagem? " << endl;
                                    cout << "VAMOS LA ENT... " << endl;
                                    cout << "TITULO: ";
                                    cin.get(liv.titulo, 99);
                                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                    cout << "EDITORA: ";
                                    cin.get(liv.editora, 99);
                                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                    cout << "Informe o autor: ";
                                    cin.get(liv.autor, 99);
                                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                    cout << "Informe a area do livro: ";
                                    cin.get(liv.area, 14);
                                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                    cout << "Informe a quantidade de pagina do livro: ";
                                    cin >> liv.quant_pag;
                                    cin.get();
                                    fwrite(&liv, sizeof(struct livro), 1, DADOSARQUIVOS);
                                    fclose(DADOSARQUIVOS);
                                    break;

                                }else if(inf_errada == "titulo"){
                                    cout << "NOVO TITULO: ";
                                    cin.get(liv.titulo, 99);
                                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                    fwrite(&liv, sizeof(struct livro), 1, DADOSARQUIVOS);
                                    fclose(DADOSARQUIVOS);
                                    break;

                                }else if(inf_errada == "autor"){
                                    cout << "AUTOR: ";
                                    cin.get(liv.autor, 99);
                                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                    fwrite(&liv, sizeof(struct livro), 1, DADOSARQUIVOS);
                                    fclose(DADOSARQUIVOS);
                                    break;

                                }else if(inf_errada == "editora"){
                                    cout << "EDITORA: ";
                                    cin.get(liv.editora, 99);
                                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                    fwrite(&liv, sizeof(struct livro), 1, DADOSARQUIVOS);
                                    fclose(DADOSARQUIVOS);
                                    break;

                                }else if(inf_errada == "area"){
                                    cout << "AREA: ";
                                    cin.get(liv.area, 14);
                                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                    fwrite(&liv, sizeof(struct livro), 1, DADOSARQUIVOS);
                                    fclose(DADOSARQUIVOS);
                                    break;

                                }else if(inf_errada == "pagina"){
                                    cout << "QUANTIDADE DE PAGINAS: ";
                                    cin >> liv.quant_pag;
                                    fwrite(&liv, sizeof(struct livro), 1, DADOSARQUIVOS);
                                    fclose(DADOSARQUIVOS);
                                    break;
                                }else{
                                    cout << "digitou errado!!" << endl;
                                    cin.get();
                                    break;
                                }
                            }
                            fread(&liv, sizeof(struct livro),1,DADOSARQUIVOS);
                        }  
                        //fclose(DADOSARQUIVOS);  // Fecha o arquivo após todas as operações
                        cout << "DE ENTER PARA SAIR: ";
                        cin.get();
                        system("cls");
                    }
                    break;

                case '3':
                    cout << "====================================" <<endl;
                    cout << "             EXCLUSAO               " << endl;
                    cout << "====================================" <<endl;
                    cout << "Deseja fazer uma exlcusao? ";
                    cin >> escolha;
                    for(char& c : escolha) {
                        c = tolower(c);
                    }
                    while(escolha == "sim"){
                        cout << "Deseja excluir tudo? 1 p/s e qualquer outro numero para nao" << endl;
                        cin >> exc;
                        if(exc == 1){
                            DADOSARQUIVOS = fopen("arquivo.data", "wb");
                            cout << "Arquivo excluido!!" << endl;
                            
                        }else{
                            cout << "Informe o codigo do livro para exclusao: ";
                            cin >> busca_exc;
                            cin.get();
                            DADOSARQUIVOS_AUX = fopen("arquivo.data.aux", "wb"); //abre um novo para sobrescrever
                            DADOSARQUIVOS =  fopen("arquivo.data", "rb"); // abre o principal para leitura
                            if (DADOSARQUIVOS == NULL || DADOSARQUIVOS_AUX == NULL){
                                cout << "ERRO AO ABRIR O(S) ARQUIVO(S)! " << endl; 
                            } else {
                                fread(&liv, sizeof(struct livro),1,DADOSARQUIVOS);
                                while(fread(&liv, sizeof(struct livro),1,DADOSARQUIVOS)==1){
                                   if(busca_exc != liv.codigo){
                                       fwrite(&liv, sizeof(struct livro),1, DADOSARQUIVOS_AUX);
                                    }
                                   
                                }
                                fclose(DADOSARQUIVOS_AUX);
                                fclose(DADOSARQUIVOS);
                                remove("arquivo.data");
                                rename("arquivo.data.aux","arquivo.data");
                                cout << "ARQUIVO EXLCUIDO COM SUCESSO! "<<endl;
                                cin.get();
                            
                            }
                        cout << "Deseja fazer exclusao de outro arquivo? ";
                        cin >> escolha;

                        }

                        for (char& c : escolha){
                            c = tolower (c);
                        }
                        system("cls");
                    }

                    break;
                case '4':
                    cout << "Deseja pegar um livro emprestado? ";
                    cin >> quero;
                    for (char& c : quero) {
                        c = tolower(c);
                    }

                    while (quero == "sim"){
                        cout << "Informe o codigo do livro que deseja pegar emprestado: ";
                        cin >> codigo_e;
                        DADOSARQUIVOS = fopen("arquivo.data", "rb+");
                        if(DADOSARQUIVOS == NULL){
                            cout << "ERRO AO ABRIR O ARQUIVO! ";
                        } else{
                            while (fread(&liv, sizeof(struct livro), 1, DADOSARQUIVOS) == 1) {
                                if (liv.codigo == codigo_e ) {
                                    cout << "NOME do usuário: ";
                                    cin.ignore(numeric_limits<streamsize>::max(),'\n');  // Limpar o buffer de entrada
                                    cin.getline(liv.cad.usuario, 99);
                                    cin.ignore(numeric_limits<streamsize>::max(),'\n');
                                    cout << "DATA DE EMPRESTIMO: ";
                                    cin.getline(liv.cad.emprestimo, 99);
                                    cin.ignore(numeric_limits<streamsize>::max(),'\n');
                                    cout << "DATA DE DEVOLUCAO: ";
                                    cin.getline(liv.cad.devolucao, 99);
                                    cin.ignore(numeric_limits<streamsize>::max(),'\n');
                                    liv.liv_disponivel = false;
                                    fseek(DADOSARQUIVOS, sizeof(struct livro) * pos, SEEK_SET);
                                    fwrite(&liv, sizeof(struct livro), 1, DADOSARQUIVOS);
                                    liv.liv_disponivel = false;
                                    if (fwrite(&liv, sizeof(struct livro),1,DADOSARQUIVOS)==1){
                                        cout << "Livros emprestado com sucesso! " << endl;
                                    } else{
                                        cout << "ERRO AO FAZER O EMPRESTIMO!";
                                    }
                                }
                            } fclose(DADOSARQUIVOS);
                        }

                        cout << "Deseja pegar outro livro emprestado? ";
                        cin >> quero;
                    }
                                
                break;

                case '5':
                    cout <<"---------------------------- " << endl;
                    cout << "         DEVOLUCAO          " << endl;
                    cout << "--------------------------- " << endl;
                    cout << "Voce deseja devolver o livro? ";
                    cin >> escolha;

                    for (char& c : escolha){
                        c = tolower(c);
                    }
                    while(escolha == "sim"){
                        cout << "Informe o codigo do livro que deseja devolver: ";
                        cin >> codigo_e;
                        DADOSARQUIVOS = fopen("arquivo.data", "rb+"); //criado para abrir e escrever
                        if(DADOSARQUIVOS == NULL){
                            cout << "ERRO AO ABRIR O ARQUIVO! ";
                        }else{
                            bool encontrado = false;
                            while( fread(&liv, sizeof(struct cadastro),1,DADOSARQUIVOS)==1){
                                if(liv.codigo == codigo_e){
                                    encontrado = true;
                                    strcpy(liv.cad.usuario, ""); // strcpy copiar o valor dps da virgula pro campo anterior
                                    strcpy(liv.cad.emprestimo, "");
                                    strcpy(liv.cad.devolucao, "");
                                    liv.liv_disponivel = true;
                                    fseek(DADOSARQUIVOS, -sizeof(struct livro), SEEK_CUR);
                                    fwrite(&liv, sizeof(struct livro),1,DADOSARQUIVOS);
                                    cout << "Devolucao feita com sucesso! \n";
                                    break;
                                }
                
                            } fclose(DADOSARQUIVOS);
                            if (!encontrado){
                                cout << "LIVRO NAO ENCONTRADO! " << endl;
                            }
                            cout << "De enter para sair: ";
                            cin.get();
                            system("cls");
            
                        } 
                            cout << "Deseja devolver outro livro? ";
                            cin >> escolha;
        
                            for(char& c : escolha){
                                c = tolower(c);
                            }
                    }
                    break;

                case '6':
                    cout << "--------------------------------------------- "<<endl;
                    cout << "              CONSULTA DE LIVROS              " << endl;
                    cout << "--------------------------------------------- "<<endl;
                    cout << "Voce deseja consultar um livro? ";
                    cin >> escolha;
                    for(char& c:escolha){
                        c = tolower(c);
                    }
                    while(escolha == "sim"){
                        cout << "Voce deseja cadastrar por codigo ou por posicao? ";
                        cin >> resposta;
                        for(char & c:resposta){
                            c = tolower (c);
                        }
                        if(resposta == "codigo"){
                            cout << "Informe o codigo do livro: ";
                            cin >> codigo_e;
                            DADOSARQUIVOS =  fopen("arquivo.data", "rb");
                            if(DADOSARQUIVOS == NULL){
                                cout << "ERRO AO ABRIR O ARQUIVO! ";
                            }else {
                                cout << "ARQRUIVO ABERTO COM SUCESSO! "<< endl;
                                while (fread(&liv, sizeof(struct livro), 1, DADOSARQUIVOS)==1){
                                    if(liv.codigo == codigo_e){
                                        cout << "Titulo: " << liv.titulo << endl;
                                        cout << "AUTOR: " << liv.autor << endl;
                                        cout << "EDITORA: " << liv.editora << endl;
                                        cout << "CODIGO: " << liv.codigo << endl;
                                        cout << "QUANTIDADE DE PAGINA: " <<liv.quant_pag << endl;
                                        cout << "AREA: " << liv.area << endl;
                                        if (liv.liv_disponivel == true){
                                            cout << "LIVRO DISPONIVEL! " << endl;

                                        } else {
                                            cout << "LIVRO EMPRESTADO! " << endl;
                                            cout << "USUARIO: " << liv.cad.usuario << endl;
                                            cout << "EMPRESTIMO: " << liv.cad.emprestimo << endl;
                                            cout << "DEVOLUCAO: " << liv.cad.devolucao << endl;
                                        }
                                    } else{
                                        cout << "livro nao encontrado! ";
                                    }
                                
                            
                                fclose(DADOSARQUIVOS);   
                                }
                            }

                        } else if (resposta == "posicao!"){
                            DADOSARQUIVOS = fopen("arquivo.data", "rb");
                            if(DADOSARQUIVOS == NULL){
                                cout << "ERRO AO ABRIR O ARQUIVO! ";

                            } else{
                                cout << "informe a posicao que voce deseja saber? ";
                                cin >> busca;
                                while(fread(&liv, sizeof(struct livro),1, DADOSARQUIVOS)==1){
                                    fseek(DADOSARQUIVOS, sizeof(struct livro)*busca, SEEK_SET);
                                    cout << "Titulo: " << liv.titulo << endl;
                                    cout << "AUTOR: " << liv.autor << endl;
                                    cout << "EDITORA: " << liv.editora << endl;
                                    cout << "CODIGO: " << liv.codigo << endl;
                                    cout << "QUANTIDADE DE PAGINA: " <<liv.quant_pag << endl;
                                    cout << "AREA: " << liv.area << endl;
                                    if (liv.liv_disponivel == true){
                                            cout << "LIVRO DISPONIVEL! " << endl;

                                    } else {
                                        cout << "LIVRO EMPRESTADO! " << endl;
                                        cout << "USUARIO: " << liv.cad.usuario << endl;
                                        cout << "EMPRESTIMO: " << liv.cad.devolucao << endl;
                                        cout << "DEVOLUCAO: " << liv.cad.devolucao << endl;
                                    }
                                }
                                fclose(DADOSARQUIVOS);
                                cout << "DE ENTER PARA SAIR: ";
                                cin.get();
                            }
                        }
                        cout << "DESEJA CONSULTAR OUTRO LIVRO? ";
                        cin >> escolha;
                        for(char& c:escolha){
                            c = tolower(c);
                        }
                    }
                    break;

                case '7':
                    cout << "------------------------------------------- " << endl;
                    cout << "            LIVRO DISPONIVEIS               " <<endl;
                    cout << "------------------------------------------- " << endl;
                    DADOSARQUIVOS = fopen("arquivo.data", "rb");
                    if(DADOSARQUIVOS == NULL){
                        cout << "ERRO AO ABRIR O ARQUIVO! ";
                    } else{
                        pos = -1;
                        fread(&liv, sizeof(struct livro),1, DADOSARQUIVOS);
                        while(fread(&liv, sizeof(struct livro),1, DADOSARQUIVOS)==1){
                            if(liv.liv_disponivel == true){
                                fseek(DADOSARQUIVOS, sizeof(struct livro)*pos,SEEK_SET);
                                cout << "--------------------------------";
                                cout << "Titulo: " << liv.titulo << endl;
                                cout << "AUTOR: " << liv.autor << endl;
                                cout << "EDITORA: " << liv.editora << endl;
                                cout << "CODIGO: " << liv.codigo << endl;
                                cout << "QUANTIDADE DE PAGINA: " <<liv.quant_pag << endl;
                                cout << "AREA: " << liv.area << endl;
                                cout << "--------------------------------------------" << endl;
                                liv_disponivel++;
                            }
                            cout << "Existe " << liv_disponivel << " livros disponiveis! " << endl;
                        }
                        fclose(DADOSARQUIVOS);
                        cout << "DE ENTER PARA SAIR: ";
                        cin.get();
                    }

                    break;

                case '8':
                    cout << "-------------LIVRO CADASTRADO ----------- " << endl;
                    DADOSARQUIVOS = fopen("arquivo.data", "rb");
                    if(DADOSARQUIVOS == NULL){
                        cout << "ERRO AO ABRIR PARA LEITURA! ";
                    } else {
                        fread(&liv,sizeof(struct livro),1, DADOSARQUIVOS);
                        while(!feof(DADOSARQUIVOS)){
                            cout << "CODIGO: " << liv.codigo << endl;
                            cout << "TITULO: " << liv.titulo << endl;
                            cout << "AUTOR: " << liv.autor << endl;
                            cout << "EDITORA: " <<liv.editora << endl;
                            cout << "AREA: " <<liv.area << endl;
                            cout << "Quantidade de paginas: " << liv.quant_pag << endl;
                            cout << "-----------------------------------------------------" << endl;
                            fread(&liv, sizeof(struct livro),1,DADOSARQUIVOS);
                                                       
                        }
                        fclose(DADOSARQUIVOS);
                        cout << "De enter para sair: ";
                        cin.get();
                        cin.get();
                    }

                    break;
                default:
                    cout << "Valor incorreto" << endl;
                    break;
        }
        system("cls");
        menu();
        cout << "Deseja escolher qual opcao? ";
        cin >> opc;
        system("cls");
    }
}