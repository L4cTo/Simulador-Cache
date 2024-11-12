#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

// Adicionar uma forma de digitar o arquivo .txt
// modificar o arquivo com o programa

// cabeçalho
int confirma_tecla();            // função para confirmar a tecla, (provavelmente a mais irritante kk)
void escrita_menu(int resposta); // escreve o menu

int menu()
{
    int escolha, resposta = 1;
    escrita_menu(resposta);
    escolha = confirma_tecla();

    do
    {
        switch (escolha)
        {
        case 13: // tecla "enter" confirma
            return resposta;
            break;
        case 27:
            return 0; // tecla "esc" encerra
            break;
        case 72:
            if (resposta == 1) // se vc aperta para subir na 1° opção vai para a 4°
            {
                resposta = 4;
                escrita_menu(resposta);
                escolha = confirma_tecla();
            }
            else
            {
                if (resposta == 4) // se for a 4° opção voce vai para a 3°
                {
                    resposta = 3;
                    escrita_menu(resposta);
                    escolha = confirma_tecla();
                }
                else
                {
                    if (resposta == 3) // se for  a 3° voce vai para a 2°
                    {
                        resposta = 2;
                        escrita_menu(resposta);
                        escolha = confirma_tecla();
                    }
                    else // e se for a 2° devolve
                    {
                        resposta = 1;
                        escrita_menu(resposta);
                        escolha = confirma_tecla();
                    }
                }
            }
            break;
        case 80:
            if (resposta == 2) // faz o mesmo que a opção acima pore se pressionada a tecla para baixo
            {
                resposta = 3;
                escrita_menu(resposta);
                escolha = confirma_tecla();
            }
            else
            {
                if (resposta == 1)
                {

                    resposta = 2;
                    escrita_menu(resposta);
                    escolha = confirma_tecla();
                }
                else
                {
                    if (resposta == 3)
                    {
                        resposta = 4;
                        escrita_menu(resposta);
                        escolha = confirma_tecla();
                    }
                    else
                    {

                        resposta = 1;
                        escrita_menu(resposta);
                        escolha = confirma_tecla();
                    }
                }
            }

            break;
        }
    } while (escolha != 13 || escolha != 27); // prende em um laço para sair apenas quando confirmado
    return resposta;
}

void escrita_menu(int resposta) // textos
{

    if (resposta == 1)
    {
        system("cls");
        printf("\n\t\t\t\t\t\t~~~~MENU~~~~\nLegenda: \n(Pressione seta para cima para selecionar o superior)\n(Pressione seta para baixo para inferior)\n(ENTER para selecionar)\n(ESC para Sair)\n\n");
        printf("Escolha:\n\033[0;32mLer arquivo\33[0m\nBuscar endereco\nImprimir dados\nReescrever arquivo");
        return;
    }
    else if (resposta == 2)
    {
        system("cls");
        printf("\n\t\t\t\t\t\t~~~~MENU~~~~\nLegenda: \n(Pressione seta para cima para selecionar o superior)\n(Pressione seta para baixo para inferior)\n(ENTER para selecionar)\n(ESC para Sair)\n\n");
        printf("Escolha:\nLer arquivo\n\033[0;32mBuscar endereco\33[0m\nImprimir dados\nReescrever arquivo");
        return;
    }
    else
    {
        if (resposta == 3)
        {
            system("cls");
            printf("\n\t\t\t\t\t\t~~~~MENU~~~~\nLegenda: \n(Pressione seta para cima para selecionar o superior)\n(Pressione seta para baixo para inferior)\n(ENTER para selecionar)\n(ESC para Sair)\n\n");
            printf("Escolha:\nLer arquivo\nBuscar endereco\n\033[0;32mImprimir dados\33[0m\nReescrever arquivo");
            return;
        }
        else
        {
            system("cls");
            printf("\n\t\t\t\t\t\t~~~~MENU~~~~\nLegenda: \n(Pressione seta para cima para selecionar o superior)\n(Pressione seta para baixo para inferior)\n(ENTER para selecionar)\n(ESC para Sair)\n\n");
            printf("Escolha:\nLer arquivo\nBuscar endereco\nImprimir dados\n\033[0;32mReescrever arquivo\33[0m");
            return;
        }
    }
}

int confirma_tecla()// opção para funcionar a mudança de opção por teclas para cima e para baixo
{
    int es;
    es = getch();
    if (es == 224) // tabela ascii para alguns caracteres tem um pre-fixo 224 como é o caso das setas
    {
        es = getch(); //então temos que fazer outro getch para pegar o que vem apos o 244 
        return es; //caso seta para cima = 72 e caso seta para baixo 80
    }
    else
    {
        if (es == 13 || es == 27)//como por conta das teclas cima e baixo estava pedindo 2 vezes "enter" e "esc"
        {
            system("cls");
            printf("\t\t\t\t\t\t~~~~(Tem certeza ?)~~~~\n\nENTER para selecionar\nESC para sair\n"); // resolvemos fazer opção de confirmação para se adaptar sem erros
            es = getch();
            if (es == 13 || es == 27)
            {
                return es;
            }
            else
            {
                system("cls");
                printf("\t\t\t\t\t\t~~~~Tecla invalida~~~~");
                Sleep(1000); // parte mais estressante do codigo kk
                system("cls");
                printf("\n\t\t\t\t\t\t~~~~MENU~~~~\nLegenda: \n(Seta para cima para selecionar o superior)\n(Seta para baixo para inferior)\n(ENTER para selecionar)\n(ESC para Sair)\n\n");
                printf("Escolha:\n\033[0;32mLer arquivo\33[0m\nBuscar endereco\nImprimir dados\nReescrever arquivo");

                return confirma_tecla();
            }
        }
        else // se você apertar alguma tecla invalida na confirmação volta para o menu, uma opção de "retorno"
        {

            system("cls");
            printf("\t\t\t\t\t\t~~~~Tecla invalida~~~~");
            Sleep(2000);
            system("cls");
            printf("\n\t\t\t\t\t\t~~~~MENU~~~~\nLegenda: \n(Seta para cima para selecionar o superior)\n(Seta para baixo para inferior)\n(ENTER para selecionar)\n(ESC para Sair)\n\n");
            printf("Escolha:\n\033[0;32mLer arquivo\33[0m\nBuscar endereco\nImprimir dados\nReescrever arquivo");

            return confirma_tecla();
        }
    }
    return 0;
}

#endif