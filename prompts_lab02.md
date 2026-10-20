# Registru Consultare AI - Laborator 02

## Descriere
Acest fișier documentează utilizarea asistentului AI (LLM) pentru implementarea metodelor pe structurile de date și pentru construcția manuală a proiectului (fișier obiect, `Makefile`), în cadrul Lucrării de Laborator Nr. 2.

---

### Consultație 1: Implementarea metodelor pentru structuri și construcție din linia de comandă
* **Context:** Structurile `Position`, `Tower`, `Enemy` și `GameState` din Laboratorul 1 conțineau doar date, fără metode. Era necesară adăugarea de metode pentru fiecare structură, compilarea manuală a unui fișier `.cpp` într-un fișier obiect, crearea unui fișier de construcție (`Makefile`), actualizarea `.gitignore` și a `README.md`.
* **Prompt adresat AI:** Solicitare de a implementa metode pentru fiecare structură declarată, de a muta logica relevantă din `Engine.cpp` (validări, calcule de distanță, daune, generarea inamicilor, cheltuirea creditelor) în metodele structurilor corespunzătoare, de a crea un `Makefile` pentru construcție manuală și de a actualiza documentația.
* **Rezultat & Soluție:**
  * A fost creat fișierul `GameTypes.cpp` cu implementarea metodelor: `Position::operator==`, `Position::isInsideMap`, `Position::distanceSquaredTo`; `Tower::create`, `Tower::isInRange`, `Tower::shotsPerStep`; `Enemy::spawnForWave`, `Enemy::isAlive`, `Enemy::advance`, `Enemy::applyDamage`, `Enemy::hasReachedEnd`; `GameState::isPositionOnPath`, `GameState::isPositionOccupied`, `GameState::canAfford`, `GameState::spendCredits`, `GameState::addCredits`, `GameState::isGameOver`.
  * `Engine.cpp` a fost simplificat, logica repetitivă fiind înlocuită cu apeluri la metodele de mai sus; comportamentul jocului a fost verificat ca fiind identic cu versiunea din Laboratorul 1 (simulare automată, aceleași rezultate).
  * A fost compilat manual `Engine.cpp` într-un fișier obiect (`g++ -c Engine.cpp -o Engine.o`) pentru a demonstra pasul de construcție din linia de comandă.
  * A fost creat fișierul `Makefile` cu țintele `all`, `run` și `clean`, care compilează fiecare `.cpp` separat și apoi leagă fișierele obiect.
  * `.gitignore`-ul din Laboratorul 1 acoperea deja fișierele `.o` și executabilul, deci nu a necesitat modificări.
  * `README.md` a fost actualizat cu descrierea celor trei metode de construcție (manual pas cu pas, `Makefile`, CMake) și cu metodele noi ale fiecărei structuri.
