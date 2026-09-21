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
* **`Position`** (`struct`): Reține coordonatele (`x`, `y`) ale unui obiect pe hartă.
* **`TowerType`** (`enum class`): Definește tipurile posibile de turnuri (`Basic`, `Fast`, `Heavy`).
* **`Tower`** (`struct`): Reține poziția, tipul, puterea, raza și costul unui turn.
* **`Enemy`** (`struct`): Reține viața, viteza, recompensa și poziția unui inamic pe traseu (`pathIndex`).
* **`GameState`** (`struct`): Starea generală a jocului: credite, viața bazei, valul curent, traseul, turnurile și inamicii.
* **`Renderer`** (`class`): Componenta de afișare; desenează harta, turnurile, inamicii și interfața în consolă și curăță ecranul între pași.
* **`Listener`** (`class`): Gestionarul de intrare de la tastatură; citește comenzile jucătorului, tipul și poziția turnului și opțiunea de rejucare (`y/n`).
* **`Engine`** (`class`): Motorul principal; coordonează fluxul jocului, construiește turnurile, pornește valurile, actualizează starea jocului (`update`) și menține bucla principală (`run`).

Structurile de date se află în `GameTypes.hpp`, iar clasele în perechile de fișiere `Engine`, `Renderer` și `Listener` (`.hpp` și `.cpp`). Punctul de intrare este `main.cpp`.
