#ifndef POINT_H
#define POINT_H
/* A beépített típusok (int, char, long, double, stb...) kombinálásával új
 * típusok készíthetőek, amelyek használatával a programunk szövegét
 * kifejezőbbé tehetjük.
 * 
 * Például két dátum különbségénél látványosabb és többet elmond a
 * "két dátum közötti különbség, mint eltelt napok száma" megvalósításról az:
 *     int date_diff(struct Date a, struct Date b);
 * mint az
 *     int date_diff(int year1, int month1, int day1,
 *                   int year2, int month2, int day2);
 * függvények.
 */

/* Az egyik lehetséges felhasználói adattípus a rekord típus: a rekord típusnak
 * névvel ellátott és típussal rendelkező mezői vannak. A rekordban minden mező
 * fizikailag (a memóriában) megtalálható, és mindegyik használható.
 * 
 * A rekordok mérete legalább akkora, mint a mezők méretének összege, de
 * amennyiben az egymást követő mezők a memóriában a processzor számára
 * kényelmetlen, nem optimális sorrendben és mérettel helyezkednének el, akkor
 * a fordítóprogram megteheti, hogy két mező közé felhasználatlan területet,
 * "padding"-et helyez.
 * 
 * Például az alábbi egy derékszögű koordinátarendszerben ábrázolt pont típus,
 * melyet két egész számmal ábrázolunk.
 */
struct Point
{
    int x;
    int y;
};
/* ellenben a függvényekkel, a struct (, union, enum, typedef) végét ; zárja. */

/* Ha van egy rekord típusú változónk, azt a rekord "példányának" nevezzük.
 * A példány adattagjaira/mezőire hivatkozás a . operátorral (pl. P.x) tehetjük
 * meg. A mező közönséges változóhoz hasonlóan viselkedik: kiolvasható, írható,
 * állítható rá pointer (címe vehető).
 */

/* A rekord típusok pontosan ugyanolyan típusok, mint a "függvények"
 * (prototípusai), így a felhasználási hely(ek) előtt (ahol paraméter,
 * visszatérési érték, lokális változó, stb.) definiálva kell legyen.
 */

/* Beolvas a felhasználótól standard inputról egy x és y koordinátát, és azt
 * pont adatként visszaadja. */
struct Point read_a_point(void);

#endif // POINT_H