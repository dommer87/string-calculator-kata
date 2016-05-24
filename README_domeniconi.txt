Ho implementato l'esercizio in c++ e ambiente  Linux.
Per compilare:
	g++ ex_domeniconi.cpp -o ex_domeniconi
Per eseguire
	./ex_domeniconi
	
	
Il file è organizzato in un unico sorgente. 

Nel main() si inizializza la stringa e si chiama la funzione somma add (std::string stringa).
La funzione add (std::string stringa) chiama le funzioni di gestione della stringa e restituisce la somma come intero.

Le funzioni di gestione della stringa sono:
	extractHeaderAndLoad(): separa se presente la parte di header dal payload
	aggiusStringa(): gestisce le anomalie con i delimitatori e resttuisce un payload "pulito"
	negNumHandler(): gestisce i numeri negativi sostituendoli con 0
	maxSizeNumHandler(): gestisce i numeri con più cifre di una valore prefissato
	delimiterwarning(): avvisa se nel'header compare come carattere separatore "-"
	
Sono presenti due unzioni di eccezioni:
	exceptionNegNumber(): viene trovato un numero negativo
	exceptionBigNumber(): viene trovato un numero con più cifre di quelle prefissate	
 