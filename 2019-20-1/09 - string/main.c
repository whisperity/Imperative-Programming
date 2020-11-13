#include <stdio.h> /* printf, fopen, fclose, fgets, ... */
#include <stdlib.h> /* malloc, free */
#include <string.h> /* strcmp, strcpy */

/* FELADAT
 * -------
 * Adott egy fájl, "szavak.txt" néven. Keressük meg a lexikografikus (szótári)
 * sorrendben a legkisebb (első) és legnagyobb (utolsó) elemet!
 * 
 * A fájlt *egyszer* olvashatjuk végig.
 * A szavakat soronként egyszer találjuk.
 * A fájl túl nagy (lehet) ahhoz, hogy a memóriába beolvassunk mindent, és ott
 * dolgozzunk.
 * 
 * Plusz megkötés: a minimum és maximum elem mindig pontosan akkora
 * memóriaterületen tárolódjon, amekkora feltétlenül szükséges!
 */

int main(void)
{
    /* A fájlok úgy működnek allokációs szempontból, mint a memória. Először
     * megnyitjuk a fájlt... ez nem biztos, hogy sikerül, visszaadhat null
     * pointert.
     * 
     * "r" jelentése: kizárólag olvasásra nyissa meg, és ne nyíljon meg, ha nem
     * létezik a fájl. Ilyenkor nem írhatunk a fájlba!
     */
    FILE* fp = fopen("/dev/whisperity/this-file-hopefully-doesn't-exist.lol",
                     "r");
    if (!fp)
        fprintf(stderr, "A nem létező fájl valóban nem nyílt meg. :)\n");
    
    /* Most nyissuk meg az igazi fájlt... */
    fp = fopen("szavak.txt", "r");
    if (!fp)
    {
        fprintf(stderr, "Fájl megnyitása sikertelen.\n");
        return 1;
    }
    
    char C[1024]; /* Egy ideiglenes tömb, amibe a sorokat olvasni fogjuk. */
    char *Min, *Max; /* Két pointer, ami a mindenkori minimum és maximum elemre
                      * mutat. */

    /* Fájlból (ideértve az stdin -t is!) soronként olvasni az fgets()
     * függvénnyel lehet.
     * 
     * Az fgets() a megadott tömbbe maximum a megadott darabszám - 1 darab
     * betűt olvas (helyet hagyva a null-terminátornak), legfeljebb egy sort
     * olvasva (ellenben a scanf("%s")-el, amely az első szóköznél is megáll!).
     * Ha az utolsó sor végén nincs '\n', akkor a fájl végén megáll.
     * Ha a sor végét eléri, beolvassa a '\n' -t ÉS BELETESZI A TÖMBBE.
     * Mindkét esetben a tömb végére kerül egy bináris nulla is, hogy helyes
     * stringet kapjunk.
     * 
     * Olvasási hiba esetén a visszatérési érték (nem a tömb!) NULL, egyébként
     * a megadott első paraméter.
     */
    {
        char* temp = fgets(C, sizeof(C), fp);
                /* = 1024 most, mivel a tömb mérete ismert fordítási időben! */
        if (!temp)
        {
            fprintf(stderr, "A fájl üres...\n");
            fclose(fp); /* be kell zárni a fájlt, mert sikerült az fopen! */
            return 2;
        }
        
        /* Itt egy belső blokkot nyitunk azért, hogy a 'temp' változó, ami az
         * fgets() visszatérési értékét ellenőrzi csak, később ne látszódjon,
         * és ne használjuk, véletlenül sem.
         */
    }
    
    /* Ha a fájl nem volt üres, feltesszük, hogy a minimum és maximum elem az
     * első elem, amely az első sorban volt.
     * 
     * Lefoglalunk pont annyi karaktert (+ 1, hogy elférjen a null-terminátor),
     * amekkora a valóban beolvasott szöveg (ezért írunk strlen(C)-t!).
     */
    Min = malloc(strlen(C) + 1);
    Max = malloc(strlen(C) + 1);
    /* Ezt követően a Min és Max memória létezik, de még nem tartalmaz értéket.
     * Az strcpy() használatával átmásoljuk betűről betűre a C tartalmát a
     * Min mögé, és a Max mögé is.
     * 
     * strcpy() helyesen viszi tovább a null-terminátort.
     * Most feltettük, hogy biztosan van elég hely. Adott esetben lehet
     * érdemesebb strncpy-t használni, amely átveszi, hogy maximum hány betűt
     * másolhat át. (Modernebb fordítókkal strncpy_s() átveszi a cél-terület
     * méretét is.)
     */
    strcpy(Min, C);
    strcpy(Max, C);
    
    /* Indítunk egy ciklust a fájl maradékára. A fájlok olyanok, hogy olvasás
     * közben tudják magukról, hogy hol tart az olvasás. Azaz az első sort
     * követő olvasás a második sort fogja olvasni, majd a ciklus következő
     * lefutása a harmadikat, stb.
     */
    while (fgets(C, sizeof(C), fp) != NULL)
    {
        /* A ciklusban C-be beolvasódott a következő sor. A minimum és maximum
         * kereséshez össze kell hasonlítanunk a korábbi vélt
         * minimumot/maximumot, és az aktuális elemet.
         * 
         * "Min < C" nem működik, mivel Min egy pointer, C egy tömb. Ha C-t
         * első elemre mutató pointerré alakítjuk, akkor két teljesen független
         * pointer számszerűen hasonlítódik össze, ami értelmetlen eredményre
         * vezet.
         * 
         * stringeket összehasonlítani az strcmp(x, y) függvénnyel lehet. Ennek
         * visszatérési értéke 3 lehetőségből az egyik:
         *   < 0 (negatív), ha x (bal oldali paraméter) kisebb, mint az y.
         *  == 0          , ha a két string betűről betűre ugyanaz
         *   > 0 (pozitív), ha x (bal oldali paraméter) nagyobb, mint az y.
         */
        if (strcmp(Min, C) > 0)
        {
            /* Ha strcmp(Min, C) > 0, akkor Min nagyobb, mint C, azaz C egy
             * jobb minimum.
             */
            free(Min);                   /* az előző minimumot elfelejtjük */
            Min = malloc(strlen(C) + 1); /* csinálunk helyet az újnak */
            strcpy(Min, C);              /* és elmentjük, belemásoljuk */
        }
        
        if (strcmp(C, Max) > 0)
        {
            /* Ha strcmp(C, Max) > 0 (vagy strcmp(Max, C) < 0), akkor C nagyobb,
             * azaz egy jobb maximum.
             */
            free(Max);
            Max = malloc(strlen(C) + 1);
            strcpy(Max, C);
        }
    }
    
    /* Ha a ciklus végetért, fgets() NULL-t adott vissza, azaz valamiért (még
     * nem tudjuk miért!) nem tudott tovább olvasni.
     */
    if (feof(fp))
    {
        /* Ha a fájl végére ér egy olvasás, majd utána megint olvasni próbálunk,
         * akkor a fájl vége utáni olvasás meghiúsul, és a fájlhoz tárolódik egy
         * jelzés, hogy elfogyott. Ezt a jelzést tudjuk ellenőrzni az feof-fal.
         */
        printf("A fájl véget ért!\n");
        printf("A minimális elem: %s", Min);
        printf("A maximális elem: %s", Max);
    }
    else if (ferror(fp))
    {
        /* Az olvasás más hibák miatt is meghiúsulhat (pl. kihúzzák a
         * háttértárat, miközben olvasunk, hálózatról olvasunk és elmegy az
         * internetkapcsolat, stb.). Ilyen olvasásoknál az feof nem lesz igaz,
         * de az ferror ellenőrzés igen...
         */
        fprintf(stderr, "Az olvasás véget ért, de a fájllal kapcsolatban hibát "
                        "kaptunk, így a kiszámított eredmény értelmetlen.\n");
    }
    
    free(Min);
    free(Max);
    
    /* C lokális változó a main-ben, nem kell free-elni! */
    
    fclose(fp); /* be kell zárni a fájlt használat után! */
    
    /* Az ferror ágban nem return-öltünk, hogy a free mindenképp helyesen
     * lefusson. Viszont nem szép 0-t (nincs hiba) visszaadni, ha hiba volt,
     * úgyhogy itt most még ellenőrizzük, hogy volt-e hiba, és akkor nem 0-t
     * adunk vissza, egyébként ha nem volt hiba, 0-t.
     */
    return (ferror(fp) ? 3 : 0);
}