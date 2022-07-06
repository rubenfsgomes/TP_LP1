#include <stdio.h>
#include <string.h>
#include <windows.h>

//Estrutura para o array das etapas
typedef struct 
{
    char etapa[10];
    float media;
}Etapa;
//Estrutura para o array das provas válidas
typedef struct
{
    int nValidas;
    int numero;
    char marca[30];
    char nome[30];
    int tempo;
    float vMedia;
}Valida;
//Estrutura para o array dos tempos
typedef struct 
{
    int  numero;
    char etapa[30];
    int tempo;
    int nConcorrentes;
    int nEtapas;
}tempo;
//Estrutura para o array das distâncias
typedef struct 
{
    char etapa[20];
    float distancia;
}distancia;
//Estrutura para o array dos dados
typedef struct 
{
    int numero;
    char nome[50];
    char marca[50];
}dados;

//procedimento para inserir os dados dos concorrentes(numero, nome, marca)
void InserirDados(dados inf[], char ficheiro[]);

//procedimento para inserir num array as distancias de cada etapa percorrida
void InserirDistancias(distancia dist[], char ficheiro[]);

//procedimento para mostrar a média de tempo de cada etapa
void MediaTempo(Etapa et[], tempo temp[], int qtd);

//Procedimento para mostrar as velocidades medias dos concorrentes
void velocidadeMedia(Valida pValidas[], distancia dist[], int qtdD);

//procedimento para mostar o minimo de tempo necessario para completar cada etapa
void minimoTempo(Etapa et[], tempo temp[], int qtd);

//Procedimento para mostrar o concorrente mais rapido
void MaisRapido(Valida v[], int qtd);

//Procedimento para mostrar o concorrente mais lento
void MaisLento(Valida v[], int qtd);

//procedimento para inserir num array os tempos de conclusao das etapas
void InserirTempo(tempo temp[], char ficheiro[]);

//procedimento para mostrar os dados dos concorrentes(numero, nome, marca)
void LerDados(dados inf[], int qtd);

//procedimento para mostrar as distancias de cada etapa percorrida
void LerDistancia(distancia dist[], int qtd, Etapa et[]);

//procedimento para mostrar os tempos de conclusao das etapas
void LerTempo(tempo temp[], int qtd);

//procedimento para mostrar uma tabela com um resumo da prova toda
void Tabela(tempo temp[], int qtdT, dados inf[], int qtdI, Valida pValida[]);

//Informações sobre a prova e indice de comandos
void InfProva();

//Procedimento para ver quantidade de provas válidas
void OrdemTempoDecrescente(Valida provasValidas[], dados inf[], int n);

//Procedimento para verificar se a prova de uma concorrente é válida, apresentar o número de provas válidas
//E guardar num array as informações dos concorrentes que tiveram uma prova válida
void provaValida(tempo temp[], dados inf[], int qtd, Valida provasValidas[]);

//Procedimento para mostrar o menu de opções
void Menu();

//Main
int main(void)
{   
    InfProva();
    Menu();
    getchar();
    //Codigo para habilitar o uso de carateres especiais
    UINT CPAGE_UTF8 = 65001;
    UINT CPAGE_DEFAULT = GetConsoleOutputCP();
    SetConsoleOutputCP(CPAGE_UTF8);
}

//Informações sobre a prova e indice de comandos
void InfProva()
{
    printf("\n\t\t\t\tInformações sobre a prova de Rally\n\n");
    printf("\n\t\t\t\t\t\tMENU\n");
    printf("\nComo utilizar: \n\t");
    printf("Todas as instruções tem de ser seguidas da seguinte ordem: \n");
    printf("\n\t\t1-Para inserir informação sobre o tempo da etapa;\n");
    printf("\t\t2-Para ler informação sobre o tempo da etapa escreva 2;\n");
    printf("\t\t3-Para inserir informação sobre a distância da etapa escreva 3;\n");
    printf("\t\t4-Para ler informação sobre a distâmcia da etapa escreva 4;\n");
    printf("\t\t5-Para inserir informação sobre os dados dos concorrentes escreva 5;\n");
    printf("\t\t6-Para ler informações sobres os dados dos concorrentes escreva 6;\n");
    printf("\t\t7-Ver número de concorrentes 7;\n");
    printf("\t\t8-Ver número de concorrentes com uma prova válida 8;\n");
    printf("\t\t9-Ver por ordem decrescente os tempos dos concorrentes com provas válidas 9;\n");
    printf("\t\t10-Ver a média de tempo por cada etapa 10;\n");
    printf("\t\t11-Ver o concorrente mais lento a efetuar a prova 11;\n");
    printf("\t\t12-Ver o concorrente mais rápido a efetuar a prova 12;\n");
    printf("\t\t13-Ver o minimo de tempo necessário para efetuar a prova 13;\n");
    printf("\t\t14-Ver a velocidade média de cada concorrente 14;\n");
    printf("\t\t15-Ver tabela com toda a informação resumida.\n");
    printf("\t\tPara sair do Menu escreva 0.\n\n");
}

//Procedimento para mostrar o menu de opções
void Menu()
{   
    FILE * f;
    tempo temp[100];
    distancia dist[100];
    dados inf[100];
    Valida pValidas[100];
    Etapa etapas[100]; //Array para guardar todas as etapas existentes na prova e média de velocidade
    int decisao, contadorT=0, contadorD=0, contadorI=0;
    char ficheiroT[100], ficheiroD[100], ficheiroI[100], c;
    int qtdTemp, qtdDist, qtdInf, num, vel, i=0;
    //Menu de decisao, para o correto do funcionamento do programa deve ser executada por ordem crescente de escolhas
    do
    {
        printf("\nQuer: ");
        scanf("%d", &decisao);
        switch (decisao)
        {
        case 1:
            printf("Nome do ficheiro a carregar: ");
            scanf("%s", ficheiroT);
            InserirTempo(temp,ficheiroT);
            
            f = fopen(ficheiroT, "r");
            //Depois da Inserção do ficheiro verificar quantas linhas tem
            //e guardar o valor em variavel contador usando esta função
            for (c = getc(f); c != EOF; c = getc(f))
            { 
                if (c == '\n')
                {
                    contadorT++;
                } 
            } 
            fclose(f);
            break;
        case 2:
            LerTempo(temp,contadorT+1);
            break;
        case 3:
            printf("Nome do ficheiro a carregar: ");
            scanf("%s", ficheiroD);
            InserirDistancias(dist,ficheiroD);
            f = fopen(ficheiroD, "r");
            //Depois da Inserção do ficheiro verificar quantas linhas tem
            //e guardar o valor em variavel contador usando esta função
            for (c = getc(f); c != EOF; c = getc(f))
            { 
                if (c == '\n')
                {
                    contadorD++;
                } 
            } 
            fclose(f); 
            break;
        case 4:
            LerDistancia(dist,contadorD+1,etapas);
            break;
        case 5:
            printf("Nome do ficheiro a carregar: ");
            scanf("%s", ficheiroI);
            InserirDados(inf, ficheiroI);
            f = fopen(ficheiroI, "r");
            //Depois da Inserção do ficheiro verificar quantas linhas tem
            //e guardar o valor em variavel contador usando esta função
            for (c = getc(f); c != EOF; c = getc(f))
            { 
                if (c == '\n')
                {
                    contadorI++;
                } 
            } 
            fclose(f); 
            break;
        case 6:
            LerDados(inf,contadorI+1);
            break;
        case 7:
            printf("Número de concorrentes: %d\n", temp[0].nConcorrentes);
            break;
        case 8:
            provaValida(temp, inf, contadorT+1, pValidas);
            break;
        case 9:
            OrdemTempoDecrescente(pValidas, inf, contadorI+1);
            break;
        case 10:
            MediaTempo(etapas,temp,contadorT+1);
            break;
        case 11:
            MaisLento(pValidas,pValidas[0].nValidas);
            break;
        case 12:
            MaisRapido(pValidas,pValidas[0].nValidas);
            break;
        case 13:
            minimoTempo(etapas,temp,contadorT+1);
            break;
        case 14:
            velocidadeMedia(pValidas, dist, contadorD+1);
            break;
        case 15:
            Tabela(temp,contadorT+1,inf,contadorI+1,pValidas);
            break;
        case 0:
            return;
        }
    } while (decisao!='0');
}

//procedimento para inserir num array os tempos de conclusao das etapas
void InserirTempo(tempo temp[], char ficheiro[])
{
    FILE * f;
    int num, i=0, vel, nEt, nConc, res;
    char et[8]= {0} , et1[8], et2[8], str[40];
    f = fopen(ficheiro,"r");
    //ler cada linha do ficheiro até chegar á última
    while (!feof(f))
    {
        //Se o i for 0 entao só vai ler as variaveis nº de etapas e nº de concorrentes na primeira linha
        if (i==0)
        {
            fscanf(f,"%s", str);
            sscanf(str,"%d;%d", &nEt, &nConc);
            temp[i].nEtapas = nEt;
            temp[i].nConcorrentes = nConc;
        }
        //Se i não for 0 então vai ler os dados normalmente
        else
        {
            fscanf(f,"%s", str);
            sscanf(str,"%d;%[^;];%[^;];%d\n", &num, et1, et2, &vel);
            temp[i].numero = num;
            temp[i].tempo = vel;
            strcat(et1,et2);
            strcpy(temp[i].etapa, et1);
        }
        i++;
    }
    fclose(f);
}

//procedimento para mostrar os tempos de conclusao das etapas
void LerTempo(tempo temp[], int qtd)
{   
    //leitura dos dados presentes no array usando ciclo for
    for (int i = 0; i < qtd; i++)
    {
        //se o i for 0 apresentar só numero de etapas e de concorrentes
        if (i==0)
        {
            printf("%d;%d\n", temp[i].nEtapas, temp[i].nConcorrentes);
        }
        //se o i for diferente de 0 apresentar as informações sobre os tempos em cada etapa
        else
        {
            printf("%d;%s;%d\n", temp[i].numero, temp[i].etapa, temp[i].tempo);
        }
    }
}

//procedimento para inserir num array as distancias de cada etapa percorrida
void InserirDistancias(distancia dist[], char ficheiro[])
{
    FILE * fdist;
    int i=0;
    float di;
    char et[8], str[40], et1[8], et2[8];
    fdist = fopen(ficheiro,"r");
    //ler cada linha do ficheiro até chegar à última
    while (!feof(fdist))
    {
        fscanf(fdist,"%s", str);
        sscanf(str,"%[^;];%[^;];%f\n", et1, et2, &di);
        dist[i].distancia = di;
        strcat(et1,et2);
        strcpy(dist[i].etapa, et1);
        i++;
    }
    fclose(fdist);
}

//procedimento para mostrar as distancias de cada etapa percorrida
void LerDistancia(distancia dist[], int qtd, Etapa et[])
{
    //Utilização de ciclo for para listar o array das distancias
    for (int i = 0; i < qtd; i++)
    {
        printf("%s;%.2f\n", dist[i].etapa, dist[i].distancia);
        strcpy(et[i].etapa,dist[i].etapa);
    }
}

//procedimento para inserir os dados dos concorrentes(numero, nome, marca)
void InserirDados(dados inf[], char ficheiro[])
{
    FILE * fdados;
    int i=0, num;
    char nome[30], str[40], marca[30];
    fdados = fopen(ficheiro,"r");
    //ler cada linha do ficheiro até chegar à última
    while (!feof(fdados))
    {
        fscanf(fdados,"%s", str);
        sscanf(str,"%d;%[^;];%[^;]\n", &num, nome, marca);
        inf[i].numero = num;
        strcpy(inf[i].nome, nome);
        strcpy(inf[i].marca, marca);
        i++;
    }
    fclose(fdados);
}

//procedimento para mostrar os dados dos concorrentes(numero, nome, marca)
void LerDados(dados inf[], int qtd)
{
    //utilização de ciclo for para listar dados presentes no array dos dados
    for (int i = 0; i < qtd; i++)
    {
        printf("%d;%s;%s\n", inf[i].numero, inf[i].nome, inf[i].marca);
    }
}

//Procedimento para verificar se a prova de uma concorrente é válida, apresentar o número de provas válidas
//E guardar num array as informações dos concorrentes que tiveram uma prova válida
void provaValida(tempo temp[], dados inf[], int qtd, Valida provasValidas[])
{
    int num, v=0;
    num = temp[0].nConcorrentes;
    int condutores[qtd];
    int contador=0, somaTempo=0;
    int numero[100];
    int tempo[100];
    //Guardar todos os numeros dos concorrentes que estão na lista de velocidades num array diferente
    for (int i = 1; i < qtd; i++)
    {
        condutores[i]=temp[i].numero;
    }
    //Verificar quantas vezes cada numero aparece na lista das velocidades
    //Se aparacer um nº de vezes igual ao nº etapas então tem uma prova válida
    for (int i = 1; i <= num; i++)
    {
        contador=0;
        somaTempo=0;

        //percorre o array dos tempos e verifica
        //se aparecer o numero i no array dos tempos incrementa no contador
        for (int j = 1; j < qtd; j++)
        {
            if (condutores[j]==i)
            {
                contador++;
                somaTempo+=temp[j].tempo;
            }
        }
        //se esse contador tiver um número igual ao numero de etapas
        //então o concorrente completou todas as etaps e a prova é válida
        if (contador==temp[0].nEtapas)
        {
            numero[i]=i;
            tempo[i]=somaTempo;
            v++;
        }
    }
    contador=0;
    //Ciclo de for para guardar no array das provas validas os dados dos concorrentes que efetuaram prova válida
    for (int i = 1; i <= v; i++)
    {
        provasValidas[contador].numero=numero[i];
        provasValidas[contador].tempo=tempo[i];
        contador++;
    }
    provasValidas[0].nValidas=v;
    printf("Numero de concorrentes com provas válidas: %d\n", v);
}

//Procedimento para ver quantidade de provas válidas
void OrdemTempoDecrescente(Valida provasValidas[], dados inf[], int n)
{
    int qtd=provasValidas[0].nValidas, aux, aux2, t, h, m, s;
    char aux4[30], aux3[30];
    //Ordenar os tempos e os numeros respetivos presentes no array usando ciclos for
    for (int i = 0; i < qtd-1; i++)
    {
        for (int j = i+1; j < qtd; j++)
        {
            if (provasValidas[i].tempo<provasValidas[j].tempo)
            {
                aux = provasValidas[j].tempo;
                provasValidas[j].tempo=provasValidas[i].tempo;
                provasValidas[i].tempo=aux;
                aux2 = provasValidas[j].numero;
                provasValidas[j].numero=provasValidas[i].numero;
                provasValidas[i].numero=aux2;
            }
        }
    }
    printf("Tempo de dos concorrentes com uma prova válida em ordem decrescente: \n");
    for (int i = 0; i < qtd; i++)
    {
        t=provasValidas[i].tempo;
        t/=1000;

        h = (t/3600); 
        
        m = (t -(3600*h))/60;
        
        s = (t -(3600*h)-(m*60));
        printf("%d->%d:%d:%d\n", provasValidas[i].numero, h, m, s);
    }
}

//procedimento para mostrar a média de tempo de cada etapa
void MediaTempo(Etapa et[], tempo temp[], int qtd)
{
    int soma=0, contador=0, t, h, m, s;
    //Corre o array das etapas
    for (int i = 0; i < temp[0].nEtapas; i++)
    {
        soma=0;
        contador=0;
        //Vê se alguma vez aparece no array dos tempos uma etapa igual à do array das etapas
        for (int j = 1; j < qtd; j++)
        {
            //se aparecer uma igual, é somada e calcula-se a média dos valores recolhidos para essa etapa
            if (strcmp(temp[j].etapa,et[i].etapa)==0)
            {
                soma+=temp[j].tempo;
                contador++;
            }
        }
        et[i].media=(float)soma/contador;
        
    }
    
    for (int i = 0; i < temp[0].nEtapas; i++)
    {
        t=et[i].media;
        t/=1000;

        h = (t/3600); 
        
        m = (t -(3600*h))/60;
        
        s = (t -(3600*h)-(m*60));
        printf("Média de tempo por etapa:\n");
        printf("Etapa %s->%d:%d:%d\n", et[i].etapa, h, m, s);
    }
}

//Procedimento para mostrar o concorrente mais rapido
void MaisRapido(Valida v[], int qtd)
{
    int menor=v[0].tempo, posicao=-1;
    //Percorrer o array das provas válidas e procurar o menor tempo de prova
    for (int i = 0; i < qtd; i++)
    {
        if (v[i].tempo<menor)
        {
            menor=v[i].tempo;
            posicao=i;
        }
    }
    printf("O concorrente mais rápido da prova foi o concorrente nº %d\n", v[posicao].numero);
}

//Procedimento para mostrar o concorrente mais lento
void MaisLento(Valida v[], int qtd)
{
    int maior=0, posicao=-1;
    //Percorrer o array das provas válidas e procurar o maior tempo de prova
    for (int i = 0; i < qtd; i++)
    {
        if (v[i].tempo > maior)
        {
            maior=v[i].tempo;
            posicao=i;
        }
    }
    
    printf("O concorrente mais lento foi o concorrente nº %d\n", v[posicao].numero);
    
}

//procedimento para mostar o minimo de tempo necessario para completar cada etapa
void minimoTempo(Etapa et[], tempo temp[], int qtd)
{
    int menor=100000000, h, m, s, concorrente;
    printf("Menor tempo necessário para completar cada etapa: \n");
    for (int i = 0; i < temp[0].nEtapas; i++)
    {
        menor=100000000;
        //Vê se alguma vez aparece no array dos tempos uma etapa igual à do array das etapas
        for (int j = 1; j < qtd; j++)
        {
            //se aparecer verificar se é o menor
            if (strcmp(temp[j].etapa,et[i].etapa)==0 && (temp[j].tempo<menor))
            {
                if (temp[j].tempo<menor)
                {
                    menor=temp[j].tempo;
                    concorrente=temp[j].numero;
                }
            }
        }
        menor/=1000;

        h = (menor/3600); 
        
        m = (menor -(3600*h))/60;
        
        s = (menor -(3600*h)-(m*60));
        printf("%s->%d:%d:%d->Concorrente nº%d\n", et[i].etapa, h, m, s, concorrente);
    }
}

//Procedimento para mostrar as velocidades medias dos concorrentes
void velocidadeMedia(Valida pValidas[], distancia dist[], int qtdD)
{
    float somaDist=0, tempo;
    int qtdP = pValidas[0].nValidas;

    //percorrer o array das distancias e somar as distancias de todas as etapas
    for (int i = 0; i < qtdD; i++)
    {
        somaDist+=dist[i].distancia;
    }
    //passar a distancias para metros
    somaDist=somaDist*1000;
    //percorrer array das provas validas procurar tempo do concorrente e guardar a media
    for (int i = 0; i < qtdP; i++)
    {   
        tempo=0;
        tempo=pValidas[i].tempo;
        tempo/=1000;
        pValidas[i].vMedia=(float)somaDist/tempo;
    }
    for (int i = 0; i < qtdP; i++)
    {
        printf("%d->%.2fm/s\n", pValidas[i].numero, pValidas[i].vMedia);   
    }
    
}

//procedimento para mostrar uma tabela com um resumo da prova toda
void Tabela(tempo temp[], int qtdT, dados inf[], int qtdI, Valida pValida[])
{
    int qtdP=pValida[0].nValidas, posicao=1;
    float difAnt[qtdP], difLider[qtdP], da2, da1, t, dl1, dl2;
    int m, s, h, m2, s2, h2, m3, s3, h3;

    //Guardar o resto das informações do concorrente no array das provas válidas
    //primeiro percorremos o array das provas válidas
    for (int i = 0; i < qtdP; i++)
    {
        //e o array dos dados dos concorrentes
        for (int j = 0; j < qtdI; j++)
        {
            //se o numero que consta no array dos dados for igual a um numero
            //que está no array das provas válidas, copiar para lá o resto da informação
            if (pValida[i].numero==inf[j].numero)
            {
                strcpy(pValida[i].marca, inf[j].marca);
                strcpy(pValida[i].nome, inf[j].nome);
            }
        }
    }
    printf("||==========||=========||============||=============||================||============||============||\n");
    printf("|| Posição  || Número  ||    Nome    ||    Carro    || Tempo da prova ||   Di.Ant   ||   Di.Ldr   ||\n");
    printf("||==========||=========||============||=============||================||============||============||\n");
    for (int i = qtdP-1; i >= 0; i--)
    {
        da1=0;
        da2=0;
        //se estivermos a ver os lugares diferentes do primeiro lugar
        if (i==qtdP-1)
        {
            //diferença de tempo para o anterior é 0
            da2=0;
            //diferença de tempo para o lider é 0
            dl1=0;
        }
        //se estivermos a ver o primeiro lugar
        else
        {
            //calcular a diferença de tempo para o concorrente anterior
            da1=pValida[i].tempo;
            da2=pValida[i+1].tempo;
            da1=da1-da2;
            //cacular a diferença de tempo para o lider
            dl1=pValida[i].tempo;
            dl2=pValida[qtdP-1].tempo;
            dl1=dl1-dl2;   
        }
        t=pValida[i].tempo;

        //passar o tempo da prova para horas minutos e segundos
        t/=1000;

        h = (t/3600); 
        
        m = (t -(3600*h))/60;
        
        s = (t -(3600*h)-(m*60));
        
        //passar o tempo de diferença do concorrente anterior para horas minutos e segundos
        da1/=1000;

        h2 = (da1/3600); 
        
        m2 = (da1 -(3600*h2))/60;
        
        s2 = (da1 -(3600*h2)-(m2*60));

        //passar o tempo de diferença do lider para horas minutos e segundos
        dl1/=1000;

        h3 = (dl1/3600); 
        
        m3 = (dl1 -(3600*h3))/60;
        
        s3 = (dl1 -(3600*h3)-(m3*60));

        printf("||%5d     ||%5d    ||%8s    ||%9s    ||%6d:%2d:%2d    ||%5d:%2d:%2d || %3d:%2d%:%2d  ||\n", posicao, pValida[i].numero, pValida[i].nome, pValida[i].marca, h, m, s, h2, m2, s2, h3, m3, s3);
        printf("||==========||=========||============||=============||================||============||============||\n");
        posicao++;//Ao fim de cada linha incrementa-se a posição onde está a ser inserida a informação
    }
}