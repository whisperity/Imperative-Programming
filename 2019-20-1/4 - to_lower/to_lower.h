/* Fejlécállomány, konvencionálisan ".h" végződéssel.
 * 
 * Miért használunk fejlécállományokat?
 * ------------------------------------
 * C (és C++) fordítás során ún. "separate translation", vagyis egymástól
 * független fordítóprogram lefutásokból áll össze a teljes projekt
 * fordítási folyamata.
 * Ez hasznos tud lenni, mert az egymástól független fordítóprogram-hívások
 * párhuzamosíthatóak, ha nagy mennyiségű processzor-szál és memória áll
 * rendelkezésre.
 * 
 * Azonban ahhoz, hogy egy fordítási egység értelmes legyen, abban szerepelnie
 * kell a használt függvények prototípusának (deklarációjának), és a típusok
 * definíciójának (pl. a pár egy olyan típus, amely X és Y mezőket tartalmaz,
 * amelyek számok).
 * 
 * Ennek egy lehetséges módja kézzel beírni minden forrásfájlba ezeket az
 * információkat, azonban ezt az utat követve beleütközhetünk abba a hibába,
 * hogy később a fájlokat módosítva elfelejtjük minden helyen jól átírni a
 * kódot. A kódismétlés nem egy jó szokás, főleg nem nagyméretű projektekben.
 * 
 * Ehelyett rábízzuk magunkat a preprocesszor #include direktívájára, hogy
 * elvégezze a bemásolását a header tartalmának.
 * 
 * Mit teszünk a headerekbe?
 * -------------------------
 * Típusinformációkat, deklarációkat, makró definíciókat. Implementációt
 * (függvény törzsét) a legtöbb esetben nem!
 * 
 * Tehát a headerbe az kerül, ami ahhoz kell, hogy értelmesen (a szükséges
 * típusokat ismerve) meghívható legyen egy függvény.
 */

/* Header is (általában szokott) tovább includeolni headereket. Ebből két
 * probléma származik: a headerek egymástól körkörösen függhetnek, amely nem
 * feloldható, másrészt ha egy fordítási egységbe ugyanaz a header többször
 * kerül, akkor többször másolódik be egy típus definíciója, amely fordítási
 * hibát okoz.
 * 
 * Ezért a headereket mindig "header guard"-okkal vesszük körül. Ez három
 * preprocesszor direktíva: ifndef, define, endif sorrendben, a header
 * tartalma ezek közé kerül. (ifndef = IF Not DEFined)
 * 
 * Jelentése: a header minden include-olásakor a preprocesszor először
 * megvizsgálja, hogy az #ifndef után írt makrónév definiálásra került-e.
 * Első vizsgálatkor ez nem igaz, úgyhogy a header tartalma (az #endif-ig)
 * feldolgozásra kerül.
 * Ennek első lépése a vizsgált makrónév (!!!) #define -olása. Jegyezzük meg,
 * hogy az első két sorban a név UGYANAZ KELL LEGYEN, és ez a név egyedi kell
 * legyen a projektre nézve - általában a header neve valamilyen átalakítással
 * (nem lehet makró névben . - és hasonló dolgok, _ viszont igen) jó döntés.
 * 
 * Második és további feldolgozáskor (azonos fordításon belül!) a makrónév már
 * be lesz állítva, így az egész #ifndef és #endif közötti rész kivágásra kerül,
 * vagyis a header helyett egy "üres fájlt" fog #include -olni, és elkerüljük a
 * többszörös #include miatti problémákat.
 */
#ifndef TO_LOWER_H
#define TO_LOWER_H

/* A megvalósított függvény prototípusa/deklarációja: nem tér vissza semmivel,
 * és átvesz egy tömböt. Tömb átvételekor mindig át kell vennünk egy külön
 * paraméterben annak hosszát is. Itt most a hossz N, a tömb neve pedig S
 * lesz, és karakterekből áll.
 * 
 * Tömbök paraméterben SOSEM másolódnak le, hanem a ("külső, hívási helyen
 * átadott") tömb változik meg. Az int érték lemásolódik, ennek a függvényben
 * értéket adva nem "rontjuk el" a híváskor átadott változót.
 * 
 * A függvény kisbetűsre alakítja a tömb összes (angol ábécébeli) nagybetűjét.
 * Jegyezzük meg, hogy az eredeti tömb változik meg.
 */
void to_lower(int N, char* S);

#endif
