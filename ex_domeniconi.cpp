//Esercizio sulle stringhe di Davide Domeniconi

/* -------------------------------------------------------------------------
 * Includes
 * ----------------------------------------------------------------------- */
#include <iostream>
#include <vector>
#include <cstdlib>  //atoi
#include <string.h> //stcpy, strlen
#include <iterator> 
#include <list>

//abilitare per stampare a schermo maggiori dettagli
// #define LOG_DEBUG



/* -------------------------------------------------------------------------
 * parametri globali
 * ----------------------------------------------------------------------- */

int maxCifre = 4;
char wrongdelim = '-';




/* -------------------------------------------------------------------------
 * header funzioni
 * ----------------------------------------------------------------------- */

int add (std::string stringa);

std::list<std::vector<char> > extractHeaderAndLoad (char str[]);
std::vector<char> aggiustaStringa (std::vector<char> header, std::vector<char> load);
std::vector<char> negNumHandler (std::vector<char> header, std::vector<char> load);
std::vector<char> maxSizeNumHandler (std::vector<char> header, std::vector<char> load);

void exceptionNegNumber (char negnum[]);
void exceptionBigNumber (char bigNum[], std::string pos);
void delimiterwarning (char delim);




/* -------------------------------------------------------------------------
 * main
 * ----------------------------------------------------------------------- */

int main(int argc, char **argv)
{
  std::cout<<"Esercizio sulle stringhe by Davide Domeniconi"<<std::endl;
  std::string myString = "//,\n2000,-1\n3333,5,,5,2345,";
  std::cout<<"la stringa è: "<<std::endl;
  
  for (int i=0; i<myString.length(); i++) {
    std::cout<<"\t ["<<myString[i]<<"]   in  pos "<< i <<std::endl;
  }
    
/* funzione somma */
  int sum = add(myString);
  std::cout <<"\n LA SOMMA è: "<<sum<<"\n"<<std::endl;
}




/* -------------------------------------------------------------------------
 * corpo delle funzioni
 * ----------------------------------------------------------------------- */

/**
 * Funzione somma
 * Richiama le sotto funzioni di gestione delle stringhe e ritorna la somma.
 * Come da spec. in input a string.
 * Per comodità si useranno std::vector e char[]
 */
int add (std::string myString) {
  
  int mySum =0;
  char *str = new char[myString.length() + 1]; 
  strcpy(str, myString.c_str());
  str[strlen(str)] = '\0';
  
/* funzione che separa header e load e gestisce i delimitatori */
   std::list <std::vector<char> > myList = extractHeaderAndLoad(str);
   std::vector<char> header = myList.front();
   std::vector<char> load1  = myList.back();
    
   std::cout<< "HEADER (dopo extractHeaderAndLoad)-->  [";
   std::copy(header.begin(), header.end(), std::ostream_iterator<char>(std::cout, ""));
   std::cout<<"]"<<std::endl;
   std::cout<< "LOAD (dopo extractHeaderAndLoad)-->  [";
   std::copy(load1.begin(), load1.end(), std::ostream_iterator<char>(std::cout, " "));
   std::cout<<"]"<<std::endl;
    
   /* se il load non ha elementi la somma sarà 0*/
   if (load1.size() == 0) {
      mySum = 0;
   }    
   /* dentro il load c'è almeno un elemento */
   else{ 
   /* funzione per aggiustare la stringa */  
      std::vector<char> load2 = aggiustaStringa(header, load1);  
      std::cout<< "LOAD (dopo aggiustaStringa)-->  [";
      std::copy(load2.begin(), load2.end(), std::ostream_iterator<char>(std::cout, " "));
      std::cout<<"]"<<std::endl;
      
   /* funzione per gestire numeri negativi */    
      std::vector<char> load3 = negNumHandler(header,load2);  
      std::cout<< "LOAD (dopo negNumHandler)-->  [";
      std::copy(load3.begin(), load3.end(), std::ostream_iterator<char>(std::cout, " "));
      std::cout<<"]"<<std::endl;
      
   /* funzione per gestire numeri oltre tot cifre */  
      std::vector<char> load4 = maxSizeNumHandler(header, load3); 
      std::cout<< "LOAD (dopo maxSizeNumHandler)-->  [";
      std::copy(load4.begin(), load4.end(), std::ostream_iterator<char>(std::cout, " "));
      std::cout<<"]"<<std::endl;   
    
      
   /************** implemento la somma ***********/
   
   /* trovo la posizione dei delimitatori */
      std::vector<int> delimPos; 
      for (int i = 0; i<load4.size(); i++) {
	 if (load4.at(i) == header.at(0)) {
	   delimPos.push_back(i);
	 }
      }
      
/* c'è almeno un delimitatore */
      if (delimPos.size() !=0) {  
	
     /* estraggo il primo numero */
	int  dim = delimPos.at(0);
	char first[dim];
	for (int i=0; i<delimPos.at(0); i++) {
	    first[i] = load4.at(i);
	}
	first[dim]='\0';
  #ifdef LOG_DEBUG	  
	std::cout<<"\t\t num "<<first <<std::endl;
  #endif
	mySum = mySum + atoi(first);
	
     /* estraggo i numeri dal secondo al penultimo */
	for (int n = 0; n<delimPos.size()-1; n++) {
	  int dim = delimPos.at(n+1) - delimPos.at(n); //la dimensione del numero è pari agli spazi fra due virgole consecutive
	  char num[dim];
	  for (int d= 0; d<dim; d++) {
	      num[d] = load4.at(delimPos.at(n)+1 + d);  //delimPos[n] + 1 è la posizione prima cifra dopo , Il + d serve per scorrere il numero se ha più cifre
	  }
	  num[dim] = '\0';
  #ifdef LOG_DEBUG	  
	  std::cout<<"\t\t num "<<num<<std::endl;
  #endif
	  mySum = mySum + atoi(num);
	}
	
     /* estraggo ultimo numero*/
	int dimLast = load4.size() - (delimPos.at(delimPos.size()-1) +1);
	char last[dimLast+1];
	int j=0;
	for (int i = (delimPos.at(delimPos.size()-1) +1); i<load4.size(); i++ ) {
	  last[j]=load4.at(i);
	  j++;
	}
	last[dimLast] = '\0';
#ifdef LOG_DEBUG	  
	std::cout<<"\t\t num "<<last <<"\n"<<std::endl;
#endif
	mySum = mySum + atoi(last);
      }
/* non c'è un delimitatore */
      else{
    /* load non ha numeri, somma automaticamente 0 */
	 if (load4.size()==0) {
	    mySum =0;
	 }
    /* in load c'è un solo numero */
	 else{
	    int dim = load4.size();
	    char num[dim];
	    int x=0;
	    while (x<load4.size()) {
	       num[x] = load4.at(x);
	       x++;
	    }
	    num[dim] = '\0';
	    mySum = mySum + atoi(num);
	 }
      }
   }
  
   return mySum;
}




/**
 * Funzione extractHeaderAndLoad
 * Questa funzione si occupa di separare la parte di stringa di Header (se presente) da quella di load
 * La stringa è passata e gestita come char[].
 * I delimitatori dell'header "//" e "\n" sono supposti corretti
 */
std::list<std::vector<char> > extractHeaderAndLoad(char str[]) {  
  
    std::vector<char> header;
    std::vector<char> load;
    int posendheader = 0;
    
    /**
     * NON è specificato l'header.
     * Imposto il mio vector::header con il delimitatore di default "," 
     */
    if ( ((str[0] != '/')&&( str[1] != '/')) || (strlen(str) == 0) ) {
       header.push_back(',');
    }
    /**
     * Nella stringa è presente l'header
     * Setto il mio vector::header
     */
    else{
      for (int i = 2; i< strlen(str); i++) {	//dalla posizione 2 perchè in [0] e [1] c'è //
	if (str[i] != '\n') { 			//scorro fino alla fine dell'header
	  /**
	   * se in header trovo delimitatore "-" non va bene.
	   * Si confondo con il meno. 
	   * Lo sostituiso con la ","
	   */
	   if (str[i] == wrongdelim) {
	      delimiterwarning;
	      str[i] = ',';
	   }
	   /* setting del vector::header */
	   else{
	      header.push_back(str[i]);
	   }
	}
	/* sono arrivato in ultima posizione. */ 
	else{
	   posendheader = i;
	   break;
	}
      }    
    }
    
    /**
     * Setting del payload 
     * copio in vector::load i char dall'elemento dopo la fine dell'header (\n) 
     * fino all'ultimo elemento della stringa
     */ 
    if (strlen(str)!=0) {
      for (int j=posendheader+1; j<strlen(str); j++) {
	load.push_back(str[j]);
      }
    }
    
    /**
     * ritorno una list di vector<char> in cui copio prima l'header poi il load
     */
    std::list< std::vector<char> > myList;
    myList.push_back(header);
    myList.push_back(load);
    
    return myList; 
}




/**
 * Funzione aggiustaStringa
 * Questa funzione si occupa di sistemare le irregolarità del payload della stringa come:
 * - delimitatore in prima posizione
 * - doppio delimitatore
 * - delimitatore in ultima posizione
 * - gestione del \n
 * Il delimitatore viene settato in base a quello specificato nell'header.
 * In mancanza di header il delimitatore di default è ","
 */
std::vector<char> aggiustaStringa (std::vector<char> header, std::vector<char> load) {
    
   std::vector<char> v1 = load;
   int Ninterventi=0;   
    
  /* sostituisco \n e , con delimiter default */
   for (int j = 0; j< load.size(); j++) {
      if ((load.at(j) == '\n') || (load.at(j) == ',') ) {
	  load.at(j)=header.at(0);
      }
   }
    
   for (int p=0; p< load.size(); p++) {
      if ((p==0) && (load.at(0)==header.at(0)) ) {
#ifdef LOG_DEBUG
	  std::cout<<"\t[aggiustaStringa] caso a: primo elemento è virgola"<<std::endl;
#endif		  
	  v1.erase(v1.begin());
	  Ninterventi++;
      }
      else{
	//NON sono ultima posizione
	if (p != load.size()-1 ) {
	  if ((load.at(p) == header.at(0))&&((load.at(p+1) == header.at(0))) ) {
#ifdef LOG_DEBUG
	     std::cout<<"\t[aggiustaStringa] caso b: doppio delimitatore in posizione "<<p<<std::endl;
#endif		    
	     v1.erase(v1.begin() + p - Ninterventi);
	     Ninterventi++;
	  }
	}
	//ULTIMA POSIZIONE
	else{
	  //ultima posizione è virgola
	  if (load.at(p) == header.at(0)) {
#ifdef LOG_DEBUG
	     std::cout<<"\t[aggiustaStringa] caso d: ultimo elemento è delimitatore"<<std::endl;
#endif		    
	     v1.erase(v1.end() -1);
	  }
	}
      }
   }    
    
   load = v1;   
   return load;
}




/**
 * Funzione negNumHandler
 * Gestisce i numeri negativi sostituendoli con 0, segno meno compreso
 */
std::vector<char> negNumHandler(std::vector<char> header, std::vector<char> load) { 

   std::vector<int> delimPos;
   std::vector<int> minusPos;
    
   for (int i = 0; i<load.size(); i++) {
	if (load.at(i)==header.at(0)) {
	  delimPos.push_back(i);
	}
   }
  #ifdef LOG_DEBUG 
      std::cout<< "\t[negNumHandler] delimPos -->  [";
      std::copy(delimPos.begin(), delimPos.end(), std::ostream_iterator<int>(std::cout, " "));
      std::cout<<"]"<<std::endl;
  #endif
    
   for (int j = 0; j<load.size(); j++) {
	if (load.at(j)=='-') {
	  minusPos.push_back(j);
	}
   }
  #ifdef LOG_DEBUG 
      std::cout<< "\t[negNumHandler] minusPos -->  [";
      std::copy(minusPos.begin(), minusPos.end(), std::ostream_iterator<int>(std::cout, " "));
      std::cout<<"]"<<std::endl;
  #endif
      
  /* in stringa c'è un solo numero negativo. delimPos è vuoto */
   if ((delimPos.size() == 0)&&(minusPos.size() !=0)) {
      int x=0;
      while(x<load.size()) {
  #ifdef LOG_DEBUG
      std::cout<<"\t[negNumHandler] caso a: load["<<x<<"]="<<load.at(x)<<std::endl;
  #endif	      
	load.at(x)='0';
	x++;
      }
   }

/* in stringa ci sono almeno due numeri */
   for (int c = 0; c<delimPos.size(); c++) {
     for (int m = 0; m<minusPos.size(); m++) {
	  
	/* numero negativo al primo posto */
	if ((minusPos[m]==0) && (c == 0)) {
	   int x=0;
	   int dim = delimPos[0] - minusPos[0] -1;
	   char num[dim];
	    
	   while(x!=delimPos[0]) {	    
	      num[x] = load.at(x);
#ifdef LOG_DEBUG
	      std::cout<<"\t[negNumHandler] caso b: load["<<x<<"]="<<load.at(x)<<std::endl;
#endif	
	      load.at(x)='0';
	      x++;
	    }
	    load.at(0) = '0';
	    num[dim] = '\0';
	    exceptionNegNumber(num); 	 
	}
	    
	/* numeri negativi fra secondo e penultimo posto */
	if (c != delimPos.size()-1) {
	    if ((delimPos[c]<minusPos[m])&& (delimPos[c+1]>minusPos[m])) {
		int dim = delimPos[c+1] - minusPos[m] - 1; //delimPos[c+1] - minusPos[m] è spazio fra virgola (dopo) e meno (antecedente). Il -1 è per considerare le cifre senza il segno
		char num[dim];
		for (int d = 0; d<dim; d++) {
		  num[d] = load[minusPos[m]+1+d]; //+1 per non considerare il -. Il +d scorre le cifre del numero
#ifdef LOG_DEBUG
		  std::cout<<"\t[negNumHandler] caso c: load["<<minusPos[m]+1+d<<"]="<<load.at(minusPos[m]+1+d)<<std::endl;
#endif	
		  load[minusPos[m]+1+d] = '0';
		}
		load.at(minusPos[m])='0';
		num[dim] = '\0';
		exceptionNegNumber(num);
	    }
	}
	/* numero negativo in ultimo posto */
	else{
	    if (delimPos[c]<minusPos[m]) {
	       int x = minusPos[m]+1;	 
	       int dim = (load.size() - 1) - minusPos[m];
	       char num[dim];
	       while(x!=load.size()) {
		  num[x-(minusPos[m]+1)] = load.at(x);
#ifdef LOG_DEBUG
		  std::cout<<"\t[negNumHandler] caso d: load["<<x<<"]="<<load.at(x)<<std::endl;
#endif	
		  load.at(x)='0';
		  x++;
	       }
	       load.at(minusPos[m])='0';
	       num[dim] = '\0';
	       exceptionNegNumber(num);
	    }
	 }
      }
   }
    
   return load;
}




/**
 * Funzione maxSizeNumHandler
 * Gestisce i numeri con più cifre di maxCifre sostituendoli con 0
 */
std::vector<char> maxSizeNumHandler(std::vector<char> header, std::vector<char> load) { 
  
  std::vector<int> delimPos;

  for (int i = 0; i<load.size(); i++) {
      if (load.at(i)==header.at(0)) {
	 delimPos.push_back(i);
      }
  }
#ifdef LOG_DEBUG 
  std::cout<< "\t[maxSizeNumHandler] delimPos -->  [";
  std::copy(delimPos.begin(), delimPos.end(), std::ostream_iterator<int>(std::cout, " "));
  std::cout<<"]"<<std::endl;
#endif

  
  /* non c'è un delimitatore e l'unico numero presente è di almeno maxCifre cifre */ 
  if (delimPos.size() ==0) {
     if ( (load.size()>=maxCifre) && (load.at(0)!='0') ) { //se numero inizia con 0 è già trasformato in 0, non lo considero
	int dim = load.size();
	char num[dim];
	int x=0;
	while(x<load.size()) {
	   num[x] = load.at(x);
#ifdef LOG_DEBUG
	   std::cout<<"\t[maxSizeNumHandler] caso a: load["<<x<<"]="<<load.at(x)<<std::endl;
#endif	      
	   load.at(x)='0';
	   x++;
	}
	num[dim] = '\0';
	exceptionBigNumber(num, "prima e unica"); 
    }
  } 
  /* c'è almeno un delimitatore */
  else{
     /* big number in prima posizione */ 
      if ( (delimPos.at(0)>=maxCifre) && (load.at(0)!='0') ) { //se numero inizia con 0 è già trasformato in 0, non lo considero
	    int dim = delimPos.at(0);
	    char num[dim];
	    int x=0;
	    while(x<delimPos.at(0)) {
	       num[x] = load.at(x);
#ifdef LOG_DEBUG
	       std::cout<<"\t[maxSizeNumHandler] caso b: load["<<x<<"]="<<load.at(x)<<std::endl;
#endif	
	       load.at(x)='0';
	       x++;
	    }
	    num[dim] = '\0';
	    exceptionBigNumber(num, "prima");    
      }
      
      
     /* big number dalla seconda alla penultima posizione */
	for (int i=0; i<delimPos.size()-1; i++) {
	  if ( ((delimPos.at(i+1) - delimPos.at(i)) >= maxCifre) &&
	       ((load.at(delimPos.at(i) + 1)!='0')) 			//se numero inizia con 0 è già trasformato in 0, non lo considero
	     ) {
	    int x= delimPos.at(i)+1;
	    int dim = delimPos.at(i+1) - 1 - delimPos.at(i);
	    char num[dim];
	    while(x<delimPos.at(i+1)) {
	       num[x - (delimPos.at(i) + 1)] = load.at(x);
#ifdef LOG_DEBUG
	       std::cout<<"\t[maxSizeNumHandler] caso c: load["<<x<<"]="<<load.at(x)<<std::endl;
#endif	
	       load.at(x)='0';
	       x++;
	    }
	    num[dim] = '\0';
	    int numint = atoi(num);
	    exceptionBigNumber(num, "fra la seconda e la penultima");
	 }      
      }
	
   /* big number ultima posizione */ 
      int d=delimPos.at(delimPos.size()-1)+1; //posizione prima cifra ultimo num  
      if ((load.size() - d>= maxCifre) &&(load.at(d)!='0')) { 	//se numero inizia con 0 è già trasformato in 0, non lo considero
	 int dim = load.size() - d;
	 char num[dim];
	 int x=0;
	 while(x<dim) {
	    num[x] = load.at(x + d);
#ifdef LOG_DEBUG
	    std::cout<<"\n[maxSizeNumHandler] caso d: load["<<x+d<<"]="<<load.at(x+d)<<std::endl;
#endif	
	    load.at( x + d)='0';
	    x++;
	 }
	 num[dim] = '\0';
	 int numint = atoi(num);
	 exceptionBigNumber(num, "ultima");    
      }    
  }
  return load;
}




/**
 * Funzione exceptionNegNumber
 * Eccezione per numeri negativi
 */
void exceptionNegNumber( char negnum[]) {
  std::cout<<"EXCEPTION! Trovato numero negativo "<<negnum<<". Non verrà considerato nella somma"<<std::endl;
}




/**
 * Funzione exceptionBigNumber
 * Eccezione per numeri più grandi di maxCifre
 */
void exceptionBigNumber( char bigNum[], std::string pos) {
  std::cout<<"EXCEPTION! Trovato big number "<<bigNum<<" in "<<pos<<" posizione. Non verrà considerato nella somma"<<std::endl;
}




/**
 * Funzione delimiterwarning
 * Warning che è stato trovato come delimitatore base il "-"
 */
void delimiterwarning( char delim) {
  std::cout<<"ERROR! il delimitatore di default - non può essere accettato. Sostituito automaticamente con ,"<<std::endl;
}





