/* 

pruefekennzeichen.c

Eine kleine Loesungsskizze zu folgender Uebungsaufgabe:
Warm-Up: pruefeKennzeichen() 

Implementieren Sie bitte eine Funktion pruefeKennzeichen(), die eine 
Zeichenkette daraufhin überprüft, ob sie ein (theoretisch) gültiges 
deutsches Autokennzeichen darstellt. Ist dies der Fall, so soll die 
Funktion 1, andernfalls eine 0 zurückliefern. 
Dabei soll (theoretisch) gültig wie folgt definiert sein: das 
Kennzeichen beginnt mit ein bis drei Buchstaben; anschließend folgen 
ein Bindestrich, dann ein oder zwei Buchstaben und schließlich nach 
einem verbindlichen Leerzeichen ein bis vier Zahlen.
Alle realen, weitergehenden Prüfungen sollen hier nicht durchgeführt 
werden.

http://github.com/fhdwbap/pruefekennzeichen
fhdwbap 2017
 */


#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int isBuchstabe(char);
int isZiffer(char);
int pruefeKennzeichen(char *);



int main(int argc, char * argv[])
{
    int i;
    
    if (argc==1)
    {
        printf("usage: pruefekennzeichen kennzeichen1 [kennzeichen2 ...] \n");
        return EXIT_FAILURE;
    }
    
    for (i=1; i<argc; i++)
    {
        printf("Text \"%s\" ist %s!\n",argv[i],pruefeKennzeichen(argv[i]) ? "gueltig" : "nicht gueltig");
    }
    return EXIT_SUCCESS;
}


int isBuchstabe(char z)
{
    z = toupper(z);
    return 'A' <= z && z <= 'Z';
}

int isZiffer(char z)
{
    return isdigit(z);
}

int pruefeKennzeichen(char * zk)
{
    int zaehler = 0, i = 0;
    
    /* Aufbau ZXX-ZX 9111 */
    
    /* 1.Buchstaben-Block */
    if (!isBuchstabe(zk[i]))
    {
        return 0;
    }
    
    while( isBuchstabe(zk[i]) )
    {
        i++;
        zaehler++;
    }
    
    if (zaehler > 3)
    {
        return 0;
    }
    
    /* Bindestrich */
    if( zk[i] == '-' )
    {
        i++;
    }
    else
    {
        return 0;
    }
    
    /* 2.Buchstaben-Block */
    zaehler = 0;
    if (!isBuchstabe(zk[i]))
    {
        return 0;
    }
    
    while( isBuchstabe(zk[i]) )
    {
        i++;
        zaehler++;
    }
    
    if (zaehler > 2)
    {
        return 0;
    }
    
    /* Leerzeichen */
    if( zk[i] == ' ' )
    {
        i++;
    }
    else
    {
        return 0;
    }
    
    /* Zahlen-Block */
    zaehler = 0;
    if (!isZiffer(zk[i]))
    {
        return 0;
    }
    
    while( isZiffer(zk[i]) )
    {
        i++;
        zaehler++;
    }
    
    if (zaehler > 4)
    {
        return 0;
    }
    
    if (i == strlen(zk))
    {
        return 1; /* hier ist endlich alles gut! */
    }
    
    /* Falls noch irgendetwas nicht stimmen sollte... */
    return 0;
}

