# Registru Consultare AI - Laborator 01

## Descriere
Acest fișier documentează utilizarea asistentului AI (LLM) pentru crearea structurii proiectului Cyber Defense și pentru redactarea fișierelor de documentație Markdown (`README.md` și `prompts_lab01.md`) în cadrul Lucrării de Laborator Nr. 1.

---

### Prompt 1: Structura de bază a proiectului
* **Context:** Era necesară structura inițială a unui proiect C++ pentru un joc Tower Defense simplu.
* **Prompt adresat AI:** Propunerea structurii de bază a unui proiect C++ pentru un joc Tower Defense simplu, cu fișierele `Engine.hpp`, `Renderer.hpp` și `Listener.hpp`, structurile principale și o descriere în `README.md`, fără implementarea completă a jocului.
* **Rezultat & Soluție:** Au fost create fișierele `.hpp` cu structurile și clasele de bază, iar în `README.md` au fost adăugate denumirea proiectului, descrierea, regulile și explicația structurilor de date. Prima variantă conținea implementarea completă a unui joc de consolă; după verificarea cerințelor și a baremului, proiectul a fost simplificat.

---

### Prompt 2: Alinierea proiectului cu structura proiectului de referință
* **Context:** Ramura `lab01` conținea doar fișiere `.hpp` în directorul `include`. Structura trebuia adusă la forma proiectului de referință `TicTacToe_Lab01` (ramura `lab01`): fișiere în rădăcina proiectului, implementări `.cpp`, `main.cpp`, directorul soluției Visual Studio, `.gitignore`, `README.md` și `prompts_lab01.md`.
* **Prompt adresat AI:** Solicitare ca ramura `lab01` din `CyberDefense` să fie identică ca structură cu `TicTacToe_Lab01`, dar cu jocul Cyber Defense.
* **Rezultat & Soluție:** Fișierele `.hpp` au fost mutate în rădăcină, au fost adăugate `Engine.cpp`, `Renderer.cpp`, `Listener.cpp` și `main.cpp` (o variantă de consolă cu tură de joc, construirea turnurilor și valuri de inamici), directorul `CyberDefense_VS`, iar `.gitignore`, `README.md` și acest registru au fost actualizate.
