# IZG – Projekt: Softvérový GPU Renderer

Riešenie projektu z predmetu IZG (Základy počítačovej grafiky) na FIT VUT.

## Obsah úlohy
Cieľom projektu bolo naprogramovať **softvérovú implementáciu grafickej karty** (zjednodušenú grafickú pipeline) v jazyku C++.
- **Vertex Processor** – transformácia vrcholov (Model-View-Projection).
- **Rasterizácia** – prevod trojuholníkov na fragmenty (pixely) pomocou barycentrických súradníc.
- **Fragment Processor** – výpočet finálnej farby pixelu (tieňovanie).
- **Buffer Management** – práca s Framebufferom a Depth-bufferom (Z-buffer).

Projekt bol vytvorený výlučne na vzdelávacie účely.

> **Poznámka:** Projekt obsahuje čiastočnú implementáciu pipeline (zameranie na základnú rasterizáciu a prácu s buffermi).

## Hodnotenie
- Získané body: **8.57 / 20**

---

<details>
<summary><b>Zobraziť rekonštruované zadanie</b></summary>

### Cieľ projektu
Vašou úlohou je implementovať funkčnú grafickú pipeline v jazyku C++, ktorá simuluje správanie reálneho GPU. Dostanete kostru aplikácie, ktorá sa stará o oknový systém a zobrazenie výsledného obrázku. Vy musíte doprogramovať vnútro "grafickej karty".

### Hlavné časti implementácie
Projekt je zameraný na pochopenie toho, čo sa deje "pod kapotou" grafických API ako OpenGL alebo Vulkan.

1.  **Vertex Shader:**
    * Implementovať funkciu pre transformáciu vrcholov z 3D priestoru do Clip-Space.
    * Aplikácia projekčných matíc.

2.  **Primitive Assembly & Clipping:**
    * Zostavenie trojuholníkov.
    * Orezanie geometrie, ktorá je mimo pohľadu kamery (Clipping).

3.  **Rasterizácia (Rasterizer):**
    * Kľúčová časť projektu.
    * Implementácia algoritmu (zvyčajne Pineda/Barycentric), ktorý určí, ktoré pixely patria danému trojuholníku.
    * Interpolácia atribútov (farba, normály, UV súradnice) pre jednotlivé fragmenty pomocou perspektívnej korekcie.

4.  **Fragment Shader:**
    * Výpočet osvetlenia (napr. Lambert, Blinn-Phong).
    * Textúrovanie (čítanie farby z textúry na základe UV).

5.  **Per-Fragment Operations:**
    * **Depth Test:** Implementácia Z-bufferu pre správne vykresľovanie prekrývajúcich sa objektov (riešenie viditeľnosti).

### Vstupy a Výstupy
* **Vstup:** Zoznam vrcholov (vertices) a indexov.
* **Výstup:** Vyrenderovaný 2D obrázok vo Framebufferi.

### Technické obmedzenia
* Zákaz používania externých grafických knižníc (OpenGL, DirectX) pre samotný výpočet – všetku matematiku a rasterizáciu musíte napísať sami nad poľom pixelov.

</details>
