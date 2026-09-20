# Cyber Defense

## Descrierea proiectului

**Cyber Defense** este un joc de tip Tower Defense cu temă cyberpunk. Jucătorul trebuie să protejeze un server central de roboții care se deplasează pe un traseu prestabilit.

Aceasta este prima etapă a proiectului. În laboratorul curent sunt definite structura proiectului și elementele de bază necesare pentru dezvoltarea ulterioară a jocului.

## Regulile jocului

1. Inamicii se deplasează pe un traseu spre baza jucătorului.
2. Jucătorul poate construi turnuri în afara traseului.
3. Turnurile atacă automat inamicii aflați în raza lor.
4. Eliminarea unui inamic oferă credite.
5. Creditele sunt utilizate pentru construirea altor turnuri.
6. Jucătorul pierde dacă viața bazei ajunge la zero.

## Structurile de date

- `Position` — coordonatele unui obiect pe hartă.
- `TowerType` — tipurile posibile de turnuri: Basic, Fast și Heavy.
- `Tower` — poziția, tipul, puterea, raza și costul unui turn.
- `Enemy` — viața, viteza, recompensa și poziția unui inamic pe traseu.
- `GameState` — starea generală a jocului: credite, viața bazei, valul curent, traseul, turnurile și inamicii.

## Fișierele principale

- `GameTypes.hpp` — structurile de date ale jocului.
- `Engine.hpp` — definiția motorului jocului.
- `Renderer.hpp` — definiția desenatorului jocului.
- `Listener.hpp` — definiția ascultătorului pentru comenzile jucătorului.
- `prompts_lab01.md` — prompturile utilizate pentru asistența LLM.

## Etapa următoare

În laboratoarele următoare vor fi implementate metodele declarate în fișierele `.hpp`, afișarea hărții și mecanicile de bază ale jocului.
