#include <stdio.h>			// standardna kniznica pre vstup a vystup				standard input output
#include <stdlib.h>			// caka sa na stlacenie lubovolnej klavesy, potom sa konzola vypne } suvis s system("pause")
#include <sys/time.h> // kvoli meraniu casu
#include <unistd.h> // kvoli meraniu casu (struct timeval)
#include <windows.h> // kvoli funkcii Sleep()   bez tejto kniznice by sa nam neukazal ozajstny cas 


// global variables

int pocet_prvkov=0;			// sluzi na nacitanie poctu prvkov



float *array_quicksort;					// polia, kde ulozime nas vstup v ulohe 1 
float *array_insertion_sort; 


///////////////////////////


void quicksort( float array[], int l, int r)				// od najm. po najvecsi
{
   int j;
   if( l < r ) 
   {
   	   j = partition(array, l, r);
       quicksort(array, l, j-1);
       quicksort(array, j+1, r);
   }
	
}

void quicksort_zostupne(float array[], int l, int r)		// od najv. po najmensi
{
  int j;
  if( l < r ) 
   {
   	   j = partition_zostupne(array, l, r);
       quicksort_zostupne(array, l, j-1);
       quicksort_zostupne(array, j+1, r);
   }
	
}

int partition_zostupne( float array[], int l, int r) { // to je cast quicksortu algoritmus porovnavaci
   int pivot, i, j, t;
   pivot = array[l];
   i = l; j = r+1;
		
   while( 1)
   {
   	do ++i; while( array[i] > pivot && i <= r );
   	do --j; while( array[j] < pivot );
   	if( i >= j ) break;
   		t = array[i]; 
		array[i] = array[j]; 
		array[j] = t;
   }
   	t = array[l];
   	array[l] = array[j]; 
   	array[j] = t;
   
   return j;
}



int partition( float array[], int l, int r) {
   
   int pivot, i, j, t;
   pivot = array[l];
   i = l; j = r+1;
		
   while( 1)
   {
   	do ++i; while( array[i] <= pivot && i <= r );
   	do --j; while( array[j] > pivot );
   	if( i >= j ) break;
   		t = array[i]; 
		array[i] = array[j]; 
		array[j] = t;
   }
   	t = array[l];
   	array[l] = array[j]; 
   	array[j] = t;
   
   return j;
}

void insertionSort(float array2[], int size)				// zoradi od najmensieho po najacsi
{
	int i, j;
	int index;
	
	
	
	
 	for (i = 0; i < size; ++i)
		{
			index = array2[i];
			
			for (j = i; j > 0 && array2[j - 1] > index; j--)
			{
				array2[j] = array2[j - 1];
            }
			array2[j] = index;
		}
  
}

void insertionsort_zostupne(float array2[], int size)
{
	int i, j;
	int index;
	
 	for (i = 0; i < size; ++i)
		{
			index = array2[i];
			
			for (j = i; j > 0 && array2[j - 1] < index; j--)
			{
				array2[j] = array2[j - 1];
            }
			array2[j] = index;
		}
}


/////////////////////////////////////////////////////////////////////////////// po tadeto stiahnute

void printarray_normal(float a[], int n)
{
 	int i;
 	
	for (i=0; i<n; i++)
 	{
  		printf("%.2f ", a[i]);
 		// printf("\n");
	}
	
//	ticks = clock();
	
}


float meranie_casu( struct timeval zaciatok, struct timeval koniec)	//meranie casu operacie, zistim cas zaciatok a koniec, odcitam koniec od zaciatku
{
    return ((float)(koniec.tv_usec - zaciatok.tv_usec)/1000000 + (float)(koniec.tv_sec - 1 - zaciatok.tv_sec));
	// -1 odcita jednu sekundu, ktora je navyse po vyuziti funkcie sleep
}

void menu()				// cisty vypis bez navratovej hodnoty
{
	printf("\n\n");
	printf("K - k - Ukoncenie programu\n");
	printf("1 - Nacitanie prvkov do pola\n");
	printf("\n2 - Triedenie pomocou Quicsksort algoritmu - vzostupne, vypis algoritmu"); 
	printf(" \n- zapis cas. dlzky do suboru\n");
	printf("\n3 - Triedenie pomocou Quicksort algoritmu - zostupne, vypis algoritmu");
	printf(" \n- zapis cas. dlzky do suboru\n");
	printf("\n4 - Triedenie pomocou Insertion sort algoritmu - vzostupne, vypis algoritmu");
	printf(" \n- zapis cas. dlzky do suboru\n");
	printf("\n5 - Triedenie pomocou Insertion sort algoritmu - zostupne, vypis algoritmu");
	printf(" \n- zapis cas. dlzky do suboru\n");
	printf("\n6 - Vypis algoritmu Quicksort - nezoradene pole\n");
	printf("7 - Vypis algoritmu Insetion sort - nezoradene pole\n");
	printf("8 - Informacie o autorovi projektu\n");
}



// od tadeto ide hlavny program

int main()
{	
	int pism, i, choice, volba;				// vstupne premenne
 	struct timeval start_quicksort_vzost, start_quicksort_zost, start_inssort_vzost, start_inssorrt_zostp;		// premenne pre pracu s casom
 	struct timeval koniec_quicksort_vzost, koniec_quicksort_zost, koniec_inssort_vzost, koniec_inssort_zostp;
 

 	srand(time(NULL));
 	
 	printf("\n");
 	
 
 	menu();
 	
 	while(volba!='K' || volba!='k')				// pokial  tato podmienka bude platna, cyklus bude bezat
	{
		printf("\n");
		printf("Zadaj si volbu: ");
		volba=getch();	
		
		if(volba=='K' || volba=='k')
		{
			goto end;
		}
		
		else if(volba=='1')
		{
			system("cls");		// vycisti sa obrazovka
			
			printf("Zadaj pocet prvkov: ");
			scanf("%d", &pocet_prvkov);
			
			if(pocet_prvkov>=1 && pocet_prvkov<=1000000)
			{
				printf("Vstup je v poriadku\n");
				array_quicksort=(float*) malloc(pocet_prvkov*sizeof(float));			// tu sa nam alokuje nasa pamat ktoru sme si na vstupe urcili
 				array_insertion_sort = (float*) malloc(pocet_prvkov*sizeof(float));		// malloc,sizeof(float) je syntax jazyka C
				
				
				while(!(choice=='m' || choice=='M' || choice=='A' || choice=='a'))		// kym sa nestlaci "m", "M" alebo "a" "A"
				{
					printf("\n");
					printf("1. Do you want to enter elements manually? M - m\n");
 					printf("2. Do you want to enter elements automatically? A -a\n");
					printf("Enter your choice: ");
					choice=getch();			// tu si zvolime svoju volbu
				}
				int index=0;
				
				switch(choice)		// reaguje na moznost ci chcem automaticky alebo rucne nacitat prvky pola
				{
					case 'm' :
					case 'M' :	
								printf("\n");
								for(i=0;i<pocet_prvkov;i++)
								{
									
									printf("Enter %d element of array: ",index+1);
									scanf("%f", &array_quicksort[i]);	
									array_insertion_sort[i]=array_quicksort[i];	
									index++;
									}
					break;
					
					case 'a' :			
					case 'A' :	
								for(i=0;i<pocet_prvkov;i++)
								{
									array_quicksort[i]= rand()% 50+1;				// syntax c , rand()% nam sluzi na vygenerovanie urciteho intervalu do pola
									array_insertion_sort[i]=array_quicksort[i];
								}
				
					break;	
				
					default :	printf("Nestlacil si ani m/M , ani A/a\n");	// ked klikneme ine ako m,M alebo a,A vrati nas do cyklu while a vypyta sa este raz	
				
				}			// koniec podmienky pre ten nas interval 1 - 1 000 000
				
				menu();
			}		// dobry vstup
	
			else 
			{
				system("cls");
				printf("Zly vstup, program ukoncite zadanim lubovolneho pismena\n");
				pism=getch();	// stlacis pismeno a ukonci sa program
	
				return;
			}		
		}		// tu konci velka podmienka if
		
		
		else if(volba=='2')
		{
			system("cls");
			if(pocet_prvkov==0)
			{
				printf("Este ste nenacitali pole\n");
				menu();
			}
			
			else
			{
			printf("Usporiadavam pole:\n");
			;gettimeofday(&start_quicksort_vzost, NULL); //zistim cas pred zacatim triedenia a odcitam od casu po skonceni triedenia
			Sleep(1000);	//kvoli meraniu casu, bez oneskorenia su male postupnosti nemeratelne
 			quicksort(array_quicksort, 0,pocet_prvkov-1);		// volanie funkcie na triedenie pola vzostupne
 			gettimeofday(&koniec_quicksort_vzost, NULL);		// suvisi  s casom
 			printf("Quicksort algoritmus - vzostupne:\n");
			printarray_normal(array_quicksort,pocet_prvkov);
			printf("\nCas triedenia Quicksort algoritmu vzostupne: %f sekund\n", meranie_casu(start_quicksort_vzost, koniec_quicksort_vzost));
			menu();
			}
		}
		
		else if(volba=='3')
		{
			system("cls");
			if(pocet_prvkov==0)
			{
				printf("Este ste nenacitali pole\n");
				menu();
			}
			
			else
			{
			printf("Usporiadavam pole:\n");
			;gettimeofday(&start_quicksort_zost, NULL); //zistim cas pred zacatim triedenia a odcitam od casu po skonceni triedenia
			Sleep(1000);	//kvoli meraniu casu, bez oneskorenia su male postupnosti nemeratelne
 			quicksort_zostupne(array_quicksort,0,pocet_prvkov-1);
 			gettimeofday(&koniec_quicksort_zost, NULL);
 			printf("Quicksort algoritmus - zostupne:\n");
			printarray_normal(array_quicksort,pocet_prvkov);
			printf("\nCas triedenia Quicksort algoritmu zostupne: %f sekund\n", meranie_casu(start_quicksort_zost, koniec_quicksort_zost));
			menu();
			}
		}
		
		else if(volba=='4')
		{
			system("cls");
			if(pocet_prvkov==0)
			{
				printf("Este ste nenacitali pole\n");
				menu();
			}
			
			else
			{
			printf("Usporiadavam pole:\n");
			;gettimeofday(&start_inssort_vzost, NULL); //zistim cas pred zacatim triedenia a odcitam od casu po skonceni triedenia
			Sleep(1000);	//kvoli meraniu casu, bez oneskorenia su male postupnosti nemeratelne
 			insertionSort(array_insertion_sort,pocet_prvkov);
 			gettimeofday(&koniec_inssort_vzost, NULL);
 			printf("Insertion sort algoritmus - vzostupne:\n");
			printarray_normal(array_insertion_sort,pocet_prvkov);
			printf("\nCas triedenia Insertionsort algoritmu vzostupne: %f sekund\n", meranie_casu(start_inssort_vzost, koniec_inssort_vzost));
			menu(); 
			}	
		}
		
		else if(volba=='5')
		{
			system("cls");
			if(pocet_prvkov==0)
			{
				printf("Este ste nenacitali pole\n");
				menu();
			}
			
			else
			{
			printf("Usporiadavam pole:\n");
			;gettimeofday(&start_inssorrt_zostp, NULL); //zistim cas pred zacatim triedenia a odcitam od casu po skonceni triedenia
			Sleep(1000);	//kvoli meraniu casu, bez oneskorenia su male postupnosti nemeratelne
 			insertionsort_zostupne(array_insertion_sort, pocet_prvkov);
 			gettimeofday(&koniec_inssort_zostp, NULL);	
 			printf("Insertion sort algoritmus - zostupne:\n");
			printarray_normal(array_insertion_sort,pocet_prvkov);
			printf("\nCas triedenia Insertionsort algoritmu zostupne: %f sekund\n", meranie_casu(start_inssorrt_zostp, koniec_inssort_zostp));
			menu();
			}
		}
		
		else if(volba=='6')
		{
			system("cls");
			
			if(pocet_prvkov==0)
			{
				printf("Este ste nenacitali pole\n");
				menu();
			}
			
			else
			{
			printf("Neusporiadane Quicksort pole:\n");
			printarray_normal(array_quicksort,pocet_prvkov);
			menu();		
			}
		}
		
		else if(volba=='7')
		{
			system("cls");
			
			if(pocet_prvkov==0)
			{
				printf("Este ste nenacitali pole\n");
				menu();
			}
			
			else
			{
			printf("Neusporiadane Insetion sort pole:\n");
			printarray_normal(array_insertion_sort,pocet_prvkov);	// nezoradene pole
			menu();
			}
		}
		
		else if(volba=='8')
		{
			system("cls");
			printf("\n");
			printf("Autor:\t\t\tMonika Findorova\n");
			printf("Studijny odbor:\t\tUcitelstvo akademickych predmetov\n");
			printf("Akademicky rok:\t\t2015/2016\n");
			menu();
		}
		
		
		else
		{
			system("cls");
			printf("\n");
			printf("Nestlacil si ani jednu z moznosti\n");
			menu();	
		}
		
	} // koniec while, kde sa vsetko odohrava
 
 	
 	
	
	end:		// ked stlacike K alebo k
			
			
	if(array_quicksort==NULL && array_insertion_sort==NULL)
	{
		printf("Chyba pri uvolneni pamate\n");
		menu();	
	}
			
	else
	{
		free(array_quicksort);
		array_quicksort=NULL;
		free(array_insertion_sort);
		array_insertion_sort=NULL;
			
		printf("Pamat je uvolnena\n");
	}
	
	
	system("pause");
	return 0;
}
