# Proiect: Cyber Defense

## Scop
În cadrul acestei lucrări de laborator a fost creată structura de bază a unui joc de tip Tower Defense în limbajul C++, utilizând sistemul de control al versiunilor Git și platforma GitHub pentru organizarea codului sursă.

## Descrierea Proiectului și Regulile Jocului
**Cyber Defense** este un joc de tip Tower Defense cu temă cyberpunk. Jucătorul trebuie să protejeze un server central (`S`) de roboții (`E`) care se deplasează pe un traseu prestabilit (`#`).
* Inamicii se deplasează pe un traseu spre baza jucătorului.
* Jucătorul poate construi turnuri în afara traseului.
* Turnurile atacă automat inamicii aflați în raza lor.
* Eliminarea unui inamic oferă credite.
* Creditele sunt utilizate pentru construirea altor turnuri.
* Jucătorul pierde dacă viața bazei ajunge la zero.
* La finalul jocului, jucătorului i se oferă opțiunea de a juca din nou sau de a ieși.

Comenzile disponibile în fiecare tură: `b` (construiește un turn: se alege tipul, apoi coloana și rândul), `s` (pornește valul), `n` (pasul următor) și `q` (ieșire).

Tipurile de turnuri: `B` Basic (cost 50), `F` Fast (cost 60, trage de două ori pe pas) și `H` Heavy (cost 120, rază mare, daune mari).

## Structuri de date și descrierea lor
* **`Position`** (`struct`): Reține coordonatele (`x`, `y`) ale unui obiect pe hartă. Metode: `operator==`, `isInsideMap()`, `distanceSquaredTo()`.
* **`TowerType`** (`enum class`): Definește tipurile posibile de turnuri (`Basic`, `Fast`, `Heavy`).
* **`Tower`** (`struct`): Reține poziția, tipul, puterea, raza și costul unui turn. Metode: `create()` (fabrică statică după tip), `isInRange()`, `shotsPerStep()`.
* **`Enemy`** (`struct`): Reține viața, viteza, recompensa și poziția unui inamic pe traseu (`pathIndex`). Metode: `spawnForWave()` (fabrică statică), `isAlive()`, `advance()`, `applyDamage()`, `hasReachedEnd()`.
* **`GameState`** (`struct`): Starea generală a jocului: credite, viața bazei, valul curent, traseul, turnurile și inamicii. Metode: `isPositionOnPath()`, `isPositionOccupied()`, `canAfford()`, `spendCredits()`, `addCredits()`, `isGameOver()`.
* **`Renderer`** (`class`): Componenta de afișare; desenează harta, turnurile, inamicii și interfața în consolă și curăță ecranul între pași.
* **`Listener`** (`class`): Gestionarul de intrare de la tastatură; citește comenzile jucătorului, tipul și poziția turnului și opțiunea de rejucare (`y/n`).
* **`Engine`** (`class`): Motorul principal; coordonează fluxul jocului, delegând validările și modificările de stare metodelor structurilor de mai sus, și menține bucla principală (`run`).

Structurile de date se află în `GameTypes.hpp`/`GameTypes.cpp`, iar clasele în perechile de fișiere `Engine`, `Renderer` și `Listener` (`.hpp` și `.cpp`). Punctul de intrare este `main.cpp`.

## Construcția proiectului

Fișiere sursă: `main.cpp`, `Engine.cpp`, `Renderer.cpp`, `Listener.cpp`, `GameTypes.cpp` (și header-ele asociate).

### 1. Compilare manuală, pas cu pas (linia de comandă)

Fiecare fișier `.cpp` este compilat separat într-un fișier obiect (`.o`), apoi fișierele obiect sunt legate (linked) într-un singur executabil:

```bash
g++ -std=c++14 -Wall -Wextra -c main.cpp     -o main.o
g++ -std=c++14 -Wall -Wextra -c Engine.cpp   -o Engine.o
g++ -std=c++14 -Wall -Wextra -c Renderer.cpp -o Renderer.o
g++ -std=c++14 -Wall -Wextra -c Listener.cpp -o Listener.o
g++ -std=c++14 -Wall -Wextra -c GameTypes.cpp -o GameTypes.o

g++ -std=c++14 main.o Engine.o Renderer.o Listener.o GameTypes.o -o cyber_defense
./cyber_defense
```

### 2. Construcție cu `Makefile` (recomandat)

```bash
make        # compilează tot (obiecte + link)
make run    # compilează și rulează jocul
make clean  # șterge fișierele .o și executabilul
```

### 3. Construcție cu CMake (folosit și de Visual Studio, "Open Folder")

```bash
cmake -S . -B build
cmake --build build
```

În Visual Studio: `File > Open > Folder...` pe rădăcina proiectului — `CMakeLists.txt` este detectat automat.

## Lab3 — Constructori și operatori

Lab3 extinde versiunea actualizată a Lab2, păstrând regulile jocului.

Pentru `Position`, `Tower`, `Enemy` și `GameState` sunt declarați și definiți:
- constructor implicit, constructor de copiere și constructor cu parametri;
- operator de atribuire `operator=` care returnează referința la obiect;
- operatorii `==`, `!=`, `<`, `>`, `<=`, `>=`;
- operatorii de flux `>>` și `<<` care permit înlănțuirea.

Constructorul implicit, copierea și atribuirea folosesc `= default`: compilatorul copiază toate câmpurile, iar `std::vector` își copiază independent elementele. Autoatribuirea este sigură. Constructorii cu parametri folosesc liste de inițializare. Parametrii vectoriali ai `GameState` sunt primiți prin valoare și mutați în obiect.

Egalitatea compară toate câmpurile. Ordinea este lexicografică, în ordinea declarării câmpurilor, pentru a permite utilizarea cu `std::sort` și containere ordonate. Această ordine descrie valorile obiectelor, nu prioritatea atacurilor din joc.

### Formatul fluxurilor

Datele sunt separate prin spații, fără mesaje interactive în operatori:
- `Position`: `x y`;
- `Tower`: `x y type damage range cost`, unde `type` este 0 (Basic), 1 (Fast), 2 (Heavy);
- `Enemy`: `health speed reward pathIndex`;
- `GameState`: `credits baseHealth wave`, apoi cele trei colecții (`path`, `towers`, `enemies`), fiecare precedată de numărul elementelor.

Exemplu de turn Fast: `1 2 1 6 2 60`.

`>>` citește într-un obiect temporar și actualizează destinația doar după succesul întregii operații. Intrările incomplete, tipurile de turn invalide și dimensiunile de colecții negative sau mai mari de 100000 setează `failbit`. Fluxurile reprezintă datele obiectului; verificarea pozițiilor admise pentru construirea unui turn rămâne în motorul jocului. `Listener::readPosition` utilizează acum operatorul `>>`.

### Clasă abstractă pentru afișare

`IRenderer` declară șase metode virtuale pure și un destructor virtual. `Renderer` moștenește această interfață și implementează metodele cu `override`. `Engine` utilizează o referință `IRenderer&`; implicit folosește afișarea în consolă, iar constructorul cu parametru permite injectarea altui renderer. Rendererul extern trebuie să existe pe toată durata utilizării motorului. Copierea motorului este dezactivată pentru a evita referințe către rendererul intern al altui obiect.

### Compilare și verificare

Din directorul proiectului, cu CMake și un compilator C++14:

```sh
cmake -S . -B build
cmake --build build --config Debug
ctest --test-dir build -C Debug --output-on-failure
```

Pe Windows, executabilul se află în `build/Debug/cyber_defense.exe`. Pe sistemele cu generator cu o singură configurație poate fi direct în `build/`.

Testele din `tests/Lab3Tests.cpp` verifică semantica valorilor, serializarea, intrările invalide, compatibilitatea cu `std::sort`, moștenirea abstractă și un ciclu de joc. Verificat cu MSVC și CTest: toate testele au trecut.
