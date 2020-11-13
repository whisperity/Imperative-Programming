#include "determinant.h"

#include <stdio.h> /* stdout, printf */

/* A determináns kifejtési tétele (összefoglalás, részletesen lásd Matalap)
 * úgy szól, hogy a determináns egy sorban vagy oszlopban haladva SZUMMA az
 * adott sor vagy oszlop elemeire (negatív vagy pozitív előjellel az
 * inverziószám függvényében) az adott elemhez tartozó aldetermináns.
 *
 * Az aldetermináns minden kifejtett elemre annak az 1 sorral és oszloppal
 * kisebb mátrixnak a determinánsa, amelyet úgy kapunk, hogy elhagyjuk a
 * kifejtett elemhez tartozó sort és oszlopot.
 */

int determinant(Matrix Mx, size_t Dim, bool* Err)
{
    /* Kezdet a determináns nulla, mivel ez az összegzés egységeleme.*/
    int Det = 0;

    /* A determináns számoló egy rekurzív függvény. A végtelen rekurzió
     * gyakorlatban nem tud létezni, mert az egyes függvényhívásokkal
     * elfogyna a memória (és sose kapnánk érdemi választ), így meg kell
     * határoznunk a rekurzió végét, amikor egy olyan visszatérés történik,
     * amely nem tartalmaz rekurzív hívást.
     */
    if (Dim == 1)
        /* Ha a "mátrix" 1×1 méretű, azaz egy szám, annak a determinánsa
         * triviális, hiszen önmaga, itt nem kell újabb rekurzív hívást
         * elkövetni.
         */
        return Mx[0][0];

    /* Kézzel papíron számolva lehet okoskodni, hogy melyik sor vagy oszlop
     * szerint fejtsünk ki. Matematikailag bizonyított, hogy bármely szerinti
     * kifejtés előbb-utóbb ugyanarra az eredményre vezet, így a gépet most
     * nem tanítjuk meg okoskodni, hanem MINDIG FIXEN az első sor szerint
     * fejtünk ki!
     */
    for (size_t i = 0; i < Dim; ++i)
        /* 'i' most az OSZLOPindexe a kifejtési elemnek */
    {
        /* Az első sorban az inverziós előjel "+ - + - + - ..." alakú, azaz
         * páratlan oszlopokra +, párosokra mínusz. Mivel C-ben a tömbök
         * 0-tól indexelődnek, ezért az első igazából a nulladik, így minden
         * PÁROS indexű (tömb-)oszlopra lesz + az előjel.
         */
        bool IsPositiveSign = i % 2 == 0;

        /* A ?: operátor egy ún. "ternáris" operátor. A ? előtt egy logikai
         * kifejezés áll, amely igazsága esetén a ? és a : közötti, hamissága
         * esetén a : utáni érték lesz az egész "bezárójelezett" kifejezés
         * értéke.
         */
        int Sign = (IsPositiveSign ? +1 : -1);

        int Elem = Mx[0][i];

        /* Elő kell állítani az aldeterminánshoz tartozó mátrixot ... */

        Matrix Ms = matrix_create(Dim - 1, Dim - 1);
        if (!Ms)
        {
            /* Ha az 1 sorral és oszloppal kisebb mátrix foglalása meghiúsult,
             * jelezzük a hibát és visszatérünk...
             */
            *Err = true;
            return 0;
        }

        /* A kis mátrixot másolással állítjuk elő, a nagy mátrix minden elemét,
         * amelyet szükséges, belemásolunk a kis mátrixba.
         */
        /* FromRow: melyik sorból másolunk
         * ToRow: melyik sorba másolunk
         * FromCol: melyik oszlopból másolunk (az adott soron belül)
         * ToCol: melyik oszlopba másolunk (az adott soron belül)
         */
        int ToRow = 0;
        for (size_t FromRow = 0; FromRow < Dim; ++FromRow)
        {
            if (FromRow == 0)
                /* Ha a másolandó sor a kihagyandó sorral egyenlő (most a
                 * kihagyandó mindig az első, 0 indexű sor), akkor a
                 * ciklusMAGot kihagyjuk.
                 *
                 * Ha egy 'continue' utasításra fut a vezérlés, a vezérlés
                 * a maradék rész átugrásával a ciklusmag VÉGÉRE ugrik, és
                 * onnan vissza a léptető utasításra, feltételre, majd vagy
                 * újra a ciklusba, vagy tovább a cikluson kívülre...
                 */
                continue;

            int ToCol = 0;
            for (size_t FromCol = 0; FromCol < Dim; ++FromCol)
            {
                if (FromCol == i)
                    /* A kihagyandó oszlop mindig az az oszlop, amelyikben
                     * az aktuális (i-edik) kifejtési elem található...
                     */
                    continue;

                Ms[ToRow][ToCol] = Mx[FromRow][FromCol];
                ++ToCol; /* Minden sikeres másolás után a következő másolás a
                          * következő szabad cellába történjen. */
            }

            ++ToRow; /* Minden átmásolt sor után a kismátrixban is a rákövetkező
                      * sort töltsük! */
        }
        printf("Aldetermináns-mátrix:\n");
        matrix_fprintf(stdout, Ms, Dim - 1, Dim - 1);
        printf("\n");

        /* A determinánshoz hozzáadjuk előjel * elem * az aldetermináns. */
        /* Ez a hívás egy REKURZÍV függvényhívás, azaz a determináns függvény
         * újra belehív önmagába, csak (általában) más paraméterezéssel.
         *
         * A hibaváltozónak minden esetben ugyanazt a hibaváltozót használjuk,
         * amit az eredeti hívó adott nekünk.
         */
        Det += (Sign * Elem * determinant(Ms, Dim - 1, Err));

        /* Ms-t a kifejtő 'i' szerinti ciklusmag foglalta... ha a ciklusmag
         * végetérne felszabadítás nélkül, memory leak keletkezne be, így
         * még most fel kell szabadítanunk.
         */
        matrix_destroy(Ms, Dim - 1);
    }

    return Det;
}
