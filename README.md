Tento projekt umožňuje ovládání tří LED diod (červené, zelené a modré) pomocí infračerveného dálkového ovládání a Arduino. 

Hardwarové požadavky:
- Arduino
- IR přijímač (připojený na pin 12)
- Červená LED (připojená na pin 6)
- Zelená LED (připojená na pin 5)
- Modrá LED (připojená na pin 9)

Návod k použití:
1. Připojte IR přijímač k pinu 12 na Arduinu.
2. Připojte červenou LED k pinu 6, zelenou LED k pinu 5 a modrou LED k pinu 9 na Arduinu.
3. Nahrajte kód na Arduino.
4. Otevřete Serial Monitor v Arduino IDE (nastavte rychlost na 9600 baudů).

Použití:
1. Zapněte Serial Monitor pro sledování výstupů.
2. Pomocí dálkového ovládání zadejte hodnoty (0-255) pro jednotlivé LED diody v následujícím pořadí:
   - První hodnota nastaví jas červené LED.
   - Druhá hodnota nastaví jas zelené LED.
   - Třetí hodnota nastaví jas modré LED.
3. Pro zadání hodnot:
   - Stiskněte tlačítka na dálkovém ovládání odpovídající číslům (0-9).
   - Každý stisk tlačítka zobrazí aktuální stav zadávaného čísla v Serial Monitoru.
4. Po zadání čísla stiskněte tlačítko ENTER (EQ) na dálkovém ovládání, aby se hodnota nastavila na aktuální LED.
5. Po nastavení modré LED (třetí hodnoty) se cyklus opakuje a můžete zadávat hodnoty znovu od červené LED.

Příklad:
- Chcete nastavit červenou LED na hodnotu 150, zelenou LED na hodnotu 100 a modrou LED na hodnotu 200.
- Stiskněte tlačítka: 1, 5, 0 (červená LED), ENTER (EQ).
- Stiskněte tlačítka: 1, 0, 0 (zelená LED), ENTER (EQ).
- Stiskněte tlačítka: 2, 0, 0 (modrá LED), ENTER (EQ).

