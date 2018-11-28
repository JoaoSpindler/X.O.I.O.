#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *fileopen(char *name_file)
{
   FILE *file = fopen(name_file, "r");
   if (file == NULL)
   {
      printf("\n\nArquivo \"%s\" não pode ser aberto porque não foi encontrado.\n\n", name_file);
      if ((name_file == "extensao.txt" ) || (name_file == "libera.txt" ) || (name_file == "recupera.txt" ))
      {
          if (name_file == "extensao.txt")
          {
             system("echo \".cfg \" > extensao.txt");
          }
          if (name_file == "libera.txt")
          {
             system("echo \"30  \" > libera.txt");
          }
          if (name_file == "recupera.txt")
          {
             system("echo \"10  \" > recupera.txt");
          }
             printf("\nArquivo \"%s\" criado com sucesso.\n", name_file);
             fileopen (name_file);
      }
      else
      {
//         printf("\n\nArquivo \"%s\" não pode ser aberto porque não foi encontrado.\n\n", name_file);
         exit(0);
      }
   }
   else
   {
//      printf("\nArquivo \"%s\" aberto para operações\n", name_file);
      return file;
   }
}
int main ()
{

   int sai;
   char *char_pointer_name_file;//Nome do arquivo a ser aberto

   FILE *file_pointer_extensao;//Ponteiro de arquivo para a extensão do arquivo de configuração das VMs
   char matrix_extensao[100][100];//Matrix para a leitura das linhas do arquivo de extensão
   char *char_pointer_linha_extensao;//Variavel para a comparação de linha em branco do arquivo que configura a extensão
   char str_sulfix_vm[31];//Variável para manipulação da extensão do arquivo de configuração da VM
   char *char_pointer_sulfix;//Variável com a extensão pronta para uso
   char str_sulfix [15];

   FILE *file_pointer_libera;//Ponteiro de arquivo para a extensão do arquivo de configuração das VMs
   char matrix_libera[100][100];//Matrix para a leitura das linhas do arquivo de extensão
   char *char_pointer_linha_libera;//Variavel para a comparação de linha em branco do arquivo que configura a extensão
   char str_sulfix_libera[31];//Variável para manipulação da extensão do arquivo de configuração da VM
   char *char_pointer_libera;//Variável com a extensão pronta para uso
   char str_libera [2];//Variável com o percentual de memória a ser liberado pronto para uso

   FILE *file_pointer_recupera;//Ponteiro de arquivo para a extensão do arquivo de configuração das VMs
   char matrix_recupera[100][100];//Matrix para a leitura das linhas do arquivo de extensão
   char *char_pointer_linha_recupera;//Variavel para a comparação de linha em branco do arquivo que configura a extensão
   char str_sulfix_recupera[31];//Variável para manipulação da extensão do arquivo de configuração da VM
   char *char_pointer_recupera;//Variável com a extensão pronta para uso
   char str_recupera [2];//Variável com o percentual de memória a ser liberado pronto para uso
  
   int inicio = 0;
   int a = 0;
   int b = 0;

   int xl_list_line_couter = 0;
   FILE *file_pointer_lista_vm;//Ponteiro de arquivo para lista de VMs
   char matrix_vm_list[100][100];//Matrix para a leitura das linhas do arquivo de lista de VMs
   char *char_pointer_linha_vm_list;//Variavel para a comparação de linha em branco do arquivo com a lista das VMs
   char str_prefix_vm[55];//Variável para manipulação do nome da VM
   char *char_pointer_prefix;//Variável com o nome pronto para uso

   int vm_file_line_counter = 0;
   int tam_dyn = 0;//Variável para manipulação de str_nome_vm
   char *char_pointer_nome_vm;//Variável para a formação do nome da VM (prefix = sulfix)
   FILE *file_pointer_vm;//Ponteiro de arquivo para o arquivo de configuração da VM
   char matrix_vm[100][100];//Matrix para a leitura das linhas do arquivo de configuração da VM
   char *char_pointer_linha_vm;//Variavel para a comparação da linha lida com as constantes "memory" e "maxmem"

   char str_id_vm_aux[55];
   char str_id_vm_invertida[4];
   char str_id_vm[4];



   char_pointer_name_file = "extensao.txt";
   file_pointer_extensao = fileopen (char_pointer_name_file);//Abre arquivo de configuração com extensão dos arquivos de configuração das VMs
   inicio = 0;
   while (1)
   {
      char_pointer_linha_extensao = fgets (matrix_extensao [inicio], 100, file_pointer_extensao);//Lê as linhas salvas no arquivo
      if (char_pointer_linha_extensao == NULL)
         break;
      inicio++;
   }
   strncpy(str_sulfix_vm, matrix_extensao [0], 30);
   str_sulfix_vm[30] = '\0';
   char_pointer_sulfix = strtok (str_sulfix_vm, " ");
   a = 0;
   b = strlen(char_pointer_sulfix);
   for (a = 0; a < b; a++)
   {
      if ((char_pointer_sulfix [a] != '\0') && (char_pointer_sulfix [a] != ' ') && (char_pointer_sulfix [a] != '\n'))
      {
         str_sulfix[a] = char_pointer_sulfix[a];
      }
      else
      {
         break;
      }
   }
   if (a <= 15)
      str_sulfix[a] = '\0';
   printf("\nExtensão configurada: \"%s\"\n\n", str_sulfix);
   
   //__________________________________________________________________________________________________________________
   char_pointer_name_file = "libera.txt";
   file_pointer_libera = fileopen (char_pointer_name_file);//Abre arquivo de configuração com percentual de memória a ser liberado
   inicio = 0;
   while (1)
   {
      char_pointer_linha_libera = fgets (matrix_libera [inicio], 100, file_pointer_libera);//Lê as linhas salvas no arquivo
      if (char_pointer_linha_libera == NULL)
         break;
      inicio++;
   }
   strncpy(str_sulfix_libera, matrix_libera [0], 30);
   str_sulfix_libera[30] = '\0';
   char_pointer_libera = strtok (str_sulfix_libera, " ");
   printf("A quantia de memória configurada para ser liberada para as VMs é: %s#\n", char_pointer_libera);
   a = 0;
   b = strlen(char_pointer_libera);
   for (a = 0; a < b; a++)
   {
      if ((char_pointer_libera [a] != '\0') && (char_pointer_libera [a] != ' ') && (char_pointer_libera [a] != '\n'))
      {
         str_libera[a] = char_pointer_libera[a];
      }
      else
      {
         break;
      }
   } 
   char_pointer_name_file = "recupera.txt";
   file_pointer_recupera = fileopen (char_pointer_name_file);//Abre arquivo de configuração com extensão dos arquivos de configuração das VMs
   inicio = 0;
   while (1)
   {
      char_pointer_linha_recupera = fgets (matrix_recupera [inicio], 100, file_pointer_recupera);//Lê as linhas salvas no arquivo
      if (char_pointer_linha_recupera == NULL)
         break;
      inicio++;
   }
   strncpy(str_sulfix_recupera, matrix_recupera [0], 30);
   str_sulfix_recupera[30] = '\0';
   char_pointer_recupera = strtok (str_sulfix_recupera, " ");
   printf("\nA quantia de memória configurada para ser recuperada das VMs é: %s#\n", char_pointer_recupera);
   a = 0;
   b = 0;
   b = strlen(char_pointer_recupera);
   for (a = 0; a < b; a++)
   {
      if ((char_pointer_recupera [a] != '\0') && (char_pointer_recupera [a] != ' ') && (char_pointer_recupera [a] != '\n'))
      {
         str_recupera[a] = char_pointer_recupera[a];
      }
      else
      {
         break;
      }
   }
//=====================================================================
do
{

   system("xl list > xl-list.txt");
   char_pointer_name_file = "xl-list.txt";
   file_pointer_lista_vm = fileopen (char_pointer_name_file);//Abre aquivo com a lista de VMs sendo executadas
//      system ("clear");
   printf("\n\nXOIO 2018 - Monitor de Máquinas Virtuais para Xen\n");
   xl_list_line_couter = 0;
   while (1)//while infinito 000
   {
      char_pointer_linha_vm_list = fgets (matrix_vm_list [xl_list_line_couter], 100, file_pointer_lista_vm);//Lê as linhas do arquivo xl-list.txt
      if (char_pointer_linha_vm_list == NULL)
         break;
      else
      {
         if ((xl_list_line_couter != 0) && (xl_list_line_couter != 1))          
         {
            strncpy(str_prefix_vm, matrix_vm_list [xl_list_line_couter], 54);//Preparação para o nome da VM
            str_prefix_vm[55] = '\0';
            char_pointer_prefix= strtok (str_prefix_vm, " ");
            tam_dyn = strlen(strcat(char_pointer_prefix, char_pointer_sulfix));
            char_pointer_nome_vm = strcat(char_pointer_prefix, char_pointer_sulfix);
            char_pointer_nome_vm[tam_dyn] = '\0';
            char str_memoria_quente_invertida[6];
            int e = 0;
            int c = 0;
            int d = 0;
            int q = 0;
            int z = 0;
            char str_memoria_quente[6];
            char str_memoria_vm[55];//Pode se usar a variavel usada anteriormente
//=====================================================================================================================
            //printf ("Impressão de controle 01: %s\n", strncpy(str_id_vm_aux, matrix_vm_list [xl_list_line_couter], 47));//Preparação para o ID atual da VM
            strncpy(str_id_vm_aux, matrix_vm_list [xl_list_line_couter], 47);//Preparação para o ID atual da VM
            str_id_vm_aux[55] = '\0';
            e = strlen(str_id_vm_aux);
            for (c = e; c >= 0; c--)
            {
               if (( str_id_vm_aux[c] != ' ') && ( str_id_vm_aux[c] != '\n') && ( str_id_vm_aux[c] != '\0'))
               {
                  str_id_vm_invertida[d] = str_id_vm_aux[c];
                  //printf ("Impressão de controle 03: .%c.\nvalor de ", str_id_vm_aux[c]);
                  d++;
                  if ( str_id_vm_aux[c-1] == ' ')
                      break;   
               }               
            }
            str_id_vm_invertida[d] = '\0';
            z = strlen(str_id_vm_invertida);
            q = 0;
            //printf ("Indexador \"z\": %i\n",z); 
            //printf ("O valor de str_id_vm_invertida é: _-%s-_\n", str_id_vm_invertida);
            for (d=z; d>=0; d--)//str_memoria_quente_invertida
            {
               if (str_id_vm_invertida[d] )//!= ' ')
               {
				   str_id_vm[q] = str_id_vm_invertida[d];
                   //printf ("Impressão de controle 05: laço %i: %s\n",d, str_id_vm);
                   //printf ("Impressão de controle 04: laço %i: %c-\n",d, str_id_vm_invertida[d]);
                   q++;
                   //if (( str_id_vm_invertida[d-1] == ' ') || ( str_id_vm_invertida[d-1] != '\0'))
                   //   break;   
		       }		       
		       
            }
            str_id_vm[q] = '\0';
            str_memoria_quente[q] = '\0';
            //printf ("A VM_ID é: #%s#\n", str_id_vm);
//========================================================================================================================
            e = 0;
            c = 0;
            d = 0;
            q = 0;
            z = 0;
            strncpy(str_memoria_vm, matrix_vm_list [xl_list_line_couter], 54);//Preparação para a memória atual da VM
            str_memoria_vm[55] = '\0';
            e = strlen(str_memoria_vm);
            for (c = e; c >= 0; c--)
            {
               if (( str_memoria_vm[c] != ' ') && ( str_memoria_vm[c] != '\n') && ( str_memoria_vm[c] != '\0'))
               {
                  str_memoria_quente_invertida[d] = str_memoria_vm[c];
                  d++;
                  if ( str_memoria_vm[c-1] == ' ')
                     break;
               }
            }
            str_memoria_quente_invertida[d] = '\0';
            z = strlen(str_memoria_quente_invertida);
            q = 0;
            for (d=z-1; d>=0; d--)//str_memoria_quente_invertida
            {
               str_memoria_quente[q] = str_memoria_quente_invertida[d];
               q++;
            }
            str_memoria_quente[q] = '\0';
            char_pointer_name_file = char_pointer_nome_vm;
            file_pointer_vm = fileopen(char_pointer_name_file);
            vm_file_line_counter = 0;
            char *char_pointer_vif;//Variável que recebe a linha vif do arquivo de configuração da VM
            char str_vif[50];//Variável que armazena o endereço de IP da VM pronto para uso no snmp
            int vif_base = 0;//Variável incremeltal para o for de extração do endereço de IP da VM
            int vif_limit = 0;//Variável que limita o for de extração do endereço de IP da VM
            int vif_index = 0;//Variável indexadora para a preparação do endereço de IP da VM

            char *char_pointer_memory_aux;//Recebe a linha "memory=XXXX" já com o token memory removido
            int x = 0;//Indexador para a procura do valor do campo "memory"
            int y = 0;//Tamanho da variável str_memory
//            int z = 0;//Recebe a quantidade de posições ocupadas na variavel str_memory[6]
            char str_memory[6];//Armazena a quantidade de memória configurada para a VM
            int index_mem = 0;//Indexa a str_memory[6]
//            int memoria_atual = 0;//Armazena o valor numérico da variavel str_memory[6]

            char *char_pointer_maxmem_aux;//Recebe a linha "maxmem=XXXX" já com o token maxmem removido
            int k = 0;//Indexador para a procura do valor do campo "maxmem"
            int l = 0;//Tamanho da variável str_maxmem
            int m = 0;//Recebe a quantidade de posições ocupadas na variavel str_maxmem[6]
            char str_maxmem[6];//Armazena a quantidade de memória configurada para a VM
            int index_max = 0;//Indexa a str_maxmem[6]
//            int memoria_maxima = 0;//Armazena o valor numérico da variavel str_maxmem[6]
//            int memoria_liberada;//Recebe o valor do calculo de memória a ser liberado

            while (1)
            {//inicio do while que le as linhas do arquivo .cfg
               char_pointer_linha_vm = fgets (matrix_vm [vm_file_line_counter], 100, file_pointer_vm);//Lê as linhas salvas no arquivo
               if (char_pointer_linha_vm == NULL)//if lê linha do arquivo .cfg
                  break;
               else//else lê linha do arquivo .cfg
               {//inicio do else lê linha do arquivo .cfg
                  if (strncmp (char_pointer_linha_vm, "vif", 3) == 0)//Início das rotinas de "vif"
                  {
                     char_pointer_vif = strstr(char_pointer_linha_vm, "ip");
                     vif_limit = strlen( char_pointer_vif );
                     for (vif_base = 0; vif_base <= vif_limit ; vif_base++)
                        if ((char_pointer_vif[vif_base] != '\n') && (char_pointer_vif[vif_base] != '\0') && (char_pointer_vif[vif_base] != ' '))
                           if ((char_pointer_vif[vif_base] != '=') && (char_pointer_vif[vif_base] != 'i') && (char_pointer_vif[vif_base] != 'p'))
                           {
                              str_vif[vif_index] = char_pointer_vif[vif_base];
                              vif_index++;
                              if ((char_pointer_vif[vif_base+1] == '\'') || (char_pointer_vif[vif_base+1] == ','))
                                 break;
                           }
                     str_vif[vif_index] = '\0'; 
                  }//Fim das rotinas das rotinas de vif
                  if (strncmp (char_pointer_linha_vm, "memory", 6) == 0)//Início das rotinas de "memory"
                  {
                     char_pointer_memory_aux = strstr(char_pointer_linha_vm, "=");
                     y = strlen(char_pointer_memory_aux);
                     for ( x = 0; x < y; x++)
                     {
                        if ((char_pointer_memory_aux[x] != '=') && (char_pointer_memory_aux[x] != ' ') && (char_pointer_memory_aux[x] != '\n'))
                        {
                           str_memory[index_mem] = char_pointer_memory_aux[x];
                           index_mem++;
                        }
                     }
                     if (index_mem <6)
                        str_memory[index_mem] = '\0'; 
                  }//Fim das rotinas do campo "memmory"
                  if (strncmp (char_pointer_linha_vm, "maxmem", 6) == 0)//Início das rotinas de "maxmem"
                  {
                     char_pointer_maxmem_aux = strstr(char_pointer_linha_vm, "=");
                     l = strlen(char_pointer_maxmem_aux);
                     for ( k = 0; k < l; k++)
                     {
                        if ((char_pointer_maxmem_aux[k] != '=') && (char_pointer_maxmem_aux[k] != ' ') && (char_pointer_maxmem_aux[k] != '\n'))
                        {
                           str_maxmem[index_max] = char_pointer_maxmem_aux[k];
                           index_max++;
                        }
                     }
                     if (index_max <6)
                        str_maxmem[index_max] = '\0'; 
                  }//Fim das rotinas do campo "maxmem"
                  vm_file_line_counter++;
               }//fim do else lê linha do arquivo .cfg
            }//fim do while que le as linhas do arquivo .cfg
            char cmd_snmp[200];//Comando a ser enviado para o xen
            char cmd_snmp_aux1[70];//Comando a ser enviado para o xen
            char cmd_snmp_aux2[70];//Comando a ser enviado para o xen
            char cmd_snmp_aux3[30];
            char str_indice_cmd[3];//Indice da VM no xen
            char str_memoria_cmd[6];//Quantidade de memória liberada para a VM

            strcpy (cmd_snmp_aux1, "snmpget -v1 -c public ");
            strcat (cmd_snmp_aux1, str_vif);//ip da máquina lido no arquivo
            strcpy (cmd_snmp_aux2, ":161 ");
            strcat (cmd_snmp_aux2, ".1.3.6.1.4.1.2021.4.11.0 > ");
            strcpy (cmd_snmp_aux3,  char_pointer_nome_vm);
            strcat (cmd_snmp_aux3, ".txt");
            strcpy (cmd_snmp, cmd_snmp_aux1);
            strcat (cmd_snmp, cmd_snmp_aux2);
            strcat (cmd_snmp, cmd_snmp_aux3);
            system (cmd_snmp);
            //printf ("\nComando SNMP: #%s# ", cmd_snmp);
 //     sleep(10);
            char *char_pointer_snmp_mem_total_free;//recebe o conteudo do arquivo gerado pelo snmp
            char *char_pointer_linha_snmp;
            char matrix_snmp [100][100];
            FILE *file_pointer_snmp;
            char str_snmp_mem_total_free_aux[50];
            char str_snmp_mem_total_free[50];
            int index_snmp = 0;
            int desvira = 0;
            int i = 0;
            int j = 0;

            char_pointer_name_file = cmd_snmp_aux3;//nome formado para salvar o resultado do snmp no arquivo 
            file_pointer_snmp = fileopen (char_pointer_name_file);//Abre aquivo com a lista de VMs sendo executadas
            i = 0;
            while (1)
            {
               char_pointer_linha_snmp = fgets (matrix_snmp [i], 100, file_pointer_snmp);//Lê as linhas salvas no arquivo
               //printf("\nLinha .SNMP.TXT: %s",char_pointer_linha_snmp);
               if (char_pointer_linha_snmp == NULL)
                  break;
               i++;
            }
            for (j=0; j < i; j++)
            {
               char_pointer_linha_snmp = matrix_snmp[j];
               //printf("\nLinha .SNMP.TXT: %s",char_pointer_linha_snmp);
               //if (strncmp (char_pointer_linha_snmp, "UCD-SNMP-MIB::memTotalFree.0 = INTEGER: ", 44) == 0)//Início das rotinas de "snmp memtotalfree"
               if (strncmp (char_pointer_linha_snmp, "iso.3.6.1.4.1.2021.4.11.0 = INTEGER: ", 37) == 0)//Início das rotinas de "snmp memtotalfree"
               {  
                  char_pointer_snmp_mem_total_free = strstr(char_pointer_linha_snmp, " ");
                  //printf("\nLinha cortada? %s", char_pointer_snmp_mem_total_free);
                  l = strlen(char_pointer_snmp_mem_total_free);
                  for ( k = l; k >= 0; k--)
                  {
                     if ((char_pointer_snmp_mem_total_free[k] != '\0') && (char_pointer_snmp_mem_total_free[k] != '\n'))
                        if ((char_pointer_snmp_mem_total_free[k] != 'B') && (char_pointer_snmp_mem_total_free[k] != 'k') && (char_pointer_snmp_mem_total_free[k] != ' '))
                        {
                           str_snmp_mem_total_free_aux[index_snmp] = char_pointer_snmp_mem_total_free[k];
                           index_snmp++;
                           if (char_pointer_snmp_mem_total_free[k-1] == ' ')
                              break;
                        }
                  }
                  if (index_snmp <50)
                     str_snmp_mem_total_free_aux[index_snmp] = '\0';
            //printf("\nSNMP INVERTIDO: %s", str_snmp_mem_total_free_aux) ;
               }//Fim das rotinas de "snmp memtotalfree"
            }
            desvira = strlen(str_snmp_mem_total_free_aux); 
            index_snmp = 0;
            for(k = desvira; k >= 0; k--)
            {
               if ((str_snmp_mem_total_free_aux[k] != '\0') && (str_snmp_mem_total_free_aux[k] != ' ') && (str_snmp_mem_total_free_aux[k] != '\n')
)
               {
                  str_snmp_mem_total_free[index_snmp] = str_snmp_mem_total_free_aux[k]; 
                  index_snmp++;
               }
            }
            str_snmp_mem_total_free[index_snmp] = '\0';
            int snmp; 
            int mega;
            int memoria_minima = 0;
            int memoria_maxima = 0;
            int memoria_atual = 0;
            int memoria_livre = 0;
            int libera = 0;
            int recupera = 0;
            int memoria_liberada = 0;
            
            snmp = atoi (str_snmp_mem_total_free);
            memoria_livre = snmp/1024;
            //printf("\nValores lidos: (string) \nVM: ID %s %s \nIp: %s \nMemória Mínima: %s MB\nMemória Máxima: %s MB\nMemória Atual: %s MB\nMemória Livre: %s MB\n", str_id_vm, char_pointer_nome_vm, str_vif, str_memory ,str_maxmem, str_memoria_quente, str_snmp_mem_total_free);

            libera = atoi (str_libera);
            recupera = atoi (str_recupera);
            memoria_minima = atoi (str_memory);
            memoria_maxima = atoi (str_maxmem);
            memoria_atual = atoi (str_memoria_quente);

            printf("\nValores lidos: \nVM ID/Name: %s %s Ip: %s \nMemória Mínima: %i MB | Memória Máxima: %i MB\nMemória Atual: %i MB | Memória Livre: %i MB\n",str_id_vm, char_pointer_nome_vm, str_vif, memoria_minima , memoria_maxima, memoria_atual, memoria_livre);

//printf("\nMemória livre: %i | Memória atual / 3: %i\n", memoria_livre, memoria_atual/3);

            char str_memoria_liberada[6];
            if((memoria_livre) < (memoria_atual/3))
            {   if (memoria_atual < memoria_maxima)
               {
                  if((memoria_atual + ((memoria_maxima * libera)/100)) < memoria_maxima )
                  {
                     memoria_liberada = memoria_atual + ((memoria_maxima * libera)/100);
                     printf("\nA memória liberada é %i: ", ((memoria_maxima * libera)/100));
                     printf("\nA memória total será %i:\n", memoria_liberada);
                     strcpy (cmd_snmp_aux1, "xl mem-set ");
                     strcat (cmd_snmp_aux1, str_id_vm);//ip da máquina lido no arquivo
                     strcpy (cmd_snmp_aux2, " ");
                     snprintf( str_memoria_liberada, 10, "%i", memoria_liberada);
                     strcat (cmd_snmp_aux2, str_memoria_liberada);
                     strcpy (cmd_snmp, cmd_snmp_aux1);
                     strcat (cmd_snmp, cmd_snmp_aux2);
                     system (cmd_snmp);
                  }
                  else if((memoria_atual + ((memoria_atual * libera)/100)) < memoria_maxima )
                  {
                     memoria_liberada = memoria_atual + ((memoria_atual * libera)/100);
                     printf("\nA memória liberada é: %i ", ((memoria_atual * libera)/100));
                     printf("\nA memória total será: %i\n", memoria_liberada);
                     strcpy (cmd_snmp_aux1, "xl mem-set ");
                     strcat (cmd_snmp_aux1, str_id_vm);//ip da máquina lido no arquivo
                     strcpy (cmd_snmp_aux2, " ");
                     snprintf( str_memoria_liberada, 10, "%i", memoria_liberada);
                     strcat (cmd_snmp_aux2, str_memoria_liberada);
                     strcpy (cmd_snmp, cmd_snmp_aux1);
                     strcat (cmd_snmp, cmd_snmp_aux2);
                     system (cmd_snmp);
                  }
                  else
                  {
                     memoria_liberada = memoria_maxima;
                     printf("\nA memória total será: %i\n", memoria_liberada);
                     strcpy (cmd_snmp_aux1, "xl mem-set ");
                     strcat (cmd_snmp_aux1, str_id_vm);//ip da máquina lido no arquivo
                     strcpy (cmd_snmp_aux2, " ");
                     snprintf( str_memoria_liberada, 10, "%i", memoria_liberada);
                     strcat (cmd_snmp_aux2, str_memoria_liberada);
                     strcpy (cmd_snmp, cmd_snmp_aux1);
                     strcat (cmd_snmp, cmd_snmp_aux2);
                     system (cmd_snmp);
                  }
               }
            } 
            else  //((memoria_livre) > (memoria_atual/3))
            {
                     memoria_liberada = memoria_atual - ((memoria_atual * recupera)/100);
                     if (memoria_liberada > memoria_minima)
                     {
                     printf("\nA memória a ser recuperada é %i: ", ((memoria_atual * recupera)/100));
                     printf("\nA memória total será %i:\n", memoria_liberada);
                     strcpy (cmd_snmp_aux1, "xl mem-set ");
                     strcat (cmd_snmp_aux1, str_id_vm);//ip da máquina lido no arquivo
                     strcpy (cmd_snmp_aux2, " ");
                     snprintf( str_memoria_liberada, 10, "%i", memoria_liberada);
                     strcat (cmd_snmp_aux2, str_memoria_liberada);
                     strcpy (cmd_snmp, cmd_snmp_aux1);
                     strcat (cmd_snmp, cmd_snmp_aux2);
                     system (cmd_snmp);
                     }
                     else
                     {
                        memoria_liberada = memoria_minima;
                        printf("\nA memória total será %i|\n", memoria_liberada);
                     strcpy (cmd_snmp_aux1, "xl mem-set ");
                     strcat (cmd_snmp_aux1, str_id_vm);//ip da máquina lido no arquivo
                     strcpy (cmd_snmp_aux2, " ");
                     snprintf( str_memoria_liberada, 10, "%i", memoria_liberada);
                     strcat (cmd_snmp_aux2, str_memoria_liberada);
                     strcpy (cmd_snmp, cmd_snmp_aux1);
                     strcat (cmd_snmp, cmd_snmp_aux2);
                     system (cmd_snmp);
                     }


            }
 


         }// fim do  if ((xl_list_line_couter != 0) && (xl_list_line_couter != 1))

      xl_list_line_couter++;//depois de fazer tudo, lê a proxima linha do xl-list.txt
      }//fim do else


   }//fim do while infinito



  //   }//while infinito 000
/*
   printf("\nPressione 0 para sair");
   scanf("%i", &sai);
   }
   while(sai != 0);
*/

printf("\nPressione \"0\" para sair ");
scanf("%i", &sai);
        // if (sai == 0)
        //    exit(0);
}
while(sai != 0);
}//fim main
                 
