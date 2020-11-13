#include "month.h"

#include <stdio.h> /* fprintf, stderr */
#include <stdlib.h> /* exit */

unsigned int __days_in_month_rossz(int m, bool is_leap_year)
{
    if (m == 1) return 31;
    else if (m == 2 && is_leap_year) return 29;
    else if (m == 2 && !is_leap_year) return 28;
    else if (m == 3) return 31;
    else if (m == 4) return 30;
    /* stb... */

    /* A probléma egy ilyen megoldással többrétű. Az egyik az, hogy a kód
     * CSÚNYA, else if-ek vannak returnökkel (felesleges), a másik, hogy a
     * feltétel (egyenlőségvizsgálat) kiértékelése minden egyes alkalommal
     * elvégződik: ha m nem egy változó lenne, hanem egy függvényhívás, akkor
     * minden egyes vizsgálatnál KÜLÖN-KÜLÖN meghívódna a függvény!
     */
    return -1;
}

/* A fenti példa helyett, amikor egy konkrét egész(!) kifejezés eredményére
 * (legyen az változó, függvényhívás, valami helyben kiszámolt dolog
 * (pl. x * 8 + 2) egyenlőségvizsgálattal kell bizonyos jól meghatározott
 * esetre lefutni használható a 'switch' nyelvi elem, amely a többágú elágazás
 * egy formája.
 *
 * A switch továbbá nagyon szépen együttműködik egy modern fordítóprogram esetén
 * az enum-okkal: a fordítóprogram jelez (lehet ezt külön kérni kell, -Wswitch),
 * hogy kihagytál néhány enum értéket a vizsgálatból. Ez persze nem biztos,
 * hogy mindig hiba, de "benézési lehetőség", ezért van rá warning.
 * Egy int-en switch-elés esetén nem fogsz mind a 4 milliárd (vagy több!)
 * eshetőségre warningot kapni.
 */

unsigned int days_in_month(const enum Month m, const bool is_leap_year)
{
    /* A switch úgy működik, hogy a kifejezés értékét EGYSZER számítja ki,
     * azaz ha itt függvény lenne, azt EGYSZER hívná meg, a változót EGYSZER
     * olvassa.*/
    switch (m)
    {
        /* Ezt követően megkeressük azt a case címkét (ágat), amelyre az érték
         * EGYEZIK!
         *
         * Switch-elni predikátumra (logikai függvény kiszámításának
         * eredményére), intervallumra, egyéb képletekkel való egyezésre nem
         * lehet, arra csak az if() jó, itt csak egész (vagy enum)
         * konstansokkal dolgozunk.
         *
         * Mint látható, nem kell *sorrendben* írni az értékeket.
         */
        case JANUARY:
            /* Ha a case ág üres, akkor automatikusan továbbcsorog a vezérlés
             * a következő, a következő, stb. ágakba, amíg nem találunk egy
             * ágat, ahol nem üres.
             */
        case MARCH:
        case MAY:
        case JULY:
        case AUGUST:
        case OCTOBER:
        case DECEMBER:
            /* Azaz január, március, stb. hónapok 31 naposak. */
            return 31;
            break;

            /* Az ág végét valamilyen elugró utasítás, általában break; (néha
             * return) zárja le! Ezt MINDENKÉPPEN(!) ki kell írni. Ha return
             * van, a break nem KELL, de *valamelyik* kell.
             */

        case APRIL:
        case JUNE:
        case SEPTEMBER:
        case NOVEMBER:
            return 30;

        case FEBRUARY:
            return is_leap_year ? 29 : 28;

        default:
            /* A default ág a "nagy else" az if-elseif-elseif-else lánc végén,
             * azaz ha semelyik specifikus korábbi ág nem illeszkedett és VAN
             * default, akkor a default fog. Ha nincs, akkor a vezérlés úgy
             * megy tovább, mintha a switchben nem lett volna semmi.
             */
            fprintf(stderr,
                    "critical error in days_in_month: invalid month value %d given!\n",
                    m);
            exit(1); /* érvénytelen érték miatt most leállunk. */
            break;
    }
    /* Mivel korábban mindenhol volt már return, ide nem juthatunk el. */
}

const char * month_to_str(const enum Month m)
{
    /* Mivel C-ben nincs lehetőség az enum értéket szövegesen megjeleníteni
     * automatikusan, ezt kézzel kell megtennünk.
     */
    switch (m)
    {
        case JANUARY: return "január";
        case FEBRUARY: return "február";
        case MARCH: return "március";
        case APRIL: return "április";
        case MAY: return "május";
        case JUNE: return "június";
        case JULY: return "július";
        case AUGUST: return "augusztus";
        case SEPTEMBER: return "szeptember";
        case OCTOBER: return "október";
        case NOVEMBER: return "november";
        case DECEMBER: return "december";
        default: return "";
    }
}
