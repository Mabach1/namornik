# **Namornik (Ver. 1)** ⛵

Opily namornik se musi dostat pres molo. Jak je sance, ze nespadne do vody?🌊

## Zakladni princip namornika
Namornik je tak opily, ze jeho kroky jsou naprosto nahodne. 

Namornik se muze pohybovat po nasi tabulce do vsech smeru, vcetne pohybu po diagonale (samozrejme ne mimo tabulku🙄)

Z duvodu naproste nahodnosti se muze stat, ze namornik bude chodit tam a zpatky porad dokola.
Namornik teda nema v sobe zadny algoritmus, ktery by se snazil byt alespon trochu efektivni, ale presto je zde sance, ze se ve zdravi dostane pres molo.

## vizualizace namornika na mole (pro lepsi predstavu)
<img width="550" alt="image" src="https://user-images.githubusercontent.com/105239325/216777050-4b6d5d34-dafe-440c-a715-a297db25c186.png">

## Jaka je teda sance?
<img width="550" alt="image" src="https://user-images.githubusercontent.com/105239325/216755887-6291e40d-024f-4f2d-b07a-7b0f63aef7cd.png">

## upravy
V programu lze upravit delku (makro Y v programu) mola (sirku ne😔) a pocet nezdaru nebo vyher, ktere namornik musi podstoupit (makro NUM_OF_COMP).

Pro vizualizaci je take mozne upravit rychlost jakou bude namornik chodit (refresh rate console), ale pozor u console od Windows, tato console je velmi pomala a pri prislis vysokem freshratu (v programu cim nizzsi hodnota makra STEP tim rychlejsi refresh) by to nemusela byt schopna zvladat 

### ruzne delky mola
Zajimalo by vas, jaka je pravdepodobnost pri ruznych delkach mola, ale nechcete si hrat s programem? 🤔

Zde jsou [tabulky](https://docs.google.com/spreadsheets/d/1pEDCkVzpSHybAYuHYpAJt6x_jD3YWkuXaNvfHq2mxgU/edit?usp=sharing) s nekolika ruznymi delkami☺️

# **Namornik (ver. 2)** 🚢

## Co je jine?

V druhe verzi programu 'namornik' je mozne upravovat i sirku mola. Pro upravu sirky mola jsem se zbavil orkaju tabulky, na ktere by se, teoreticky, nemel namornik nikdy dostat. Tabulka pro uprave s mole sirky 3 a dely 5 by pak vypadala nejak takto:

<img width="400" alt="image" src="https://user-images.githubusercontent.com/105239325/216808389-a7be0391-2272-4c23-af0c-249f7317985d.png">

Pri testovani jsem vsak zijstil, ze sance namornika na vyhru se zdvojnasobila. Krom zmenseni tabulky jsem udelal i dalsi upravy a vse jsem poctive otestoval (vsechny zmeny, krome tabulky jsem vyzkousel i na Ver. 1) a nakonec jsem zijstil, ze opravdu jen odstraneni casti tabulky, na ktereou by namornik nemel nikdy slapnout, nam snizovala (ve Ver. 1) sanci na vyhru o polovinu.

## Pro se to deje? 🤔

Odstranenim dvou sloupcu vody doslo k celkovemu posunuti tabulky, zmeneni indexu a tudiz i lehke zmene vypoctu. Je taky mozne, ze kdyz je namornik na jednom z rohu dojde k uprednostneni mola, jelikoz sance, ze spadne do vody je, kvuli odstraneni nekolika bunek vody, mensi.

Velky problem je, ale pak samotna generace nahodnych cisel. Funkce rand() nemusi stihat a tudiz nedochazi k nalezite generaci.

# **Ver. 1 VS Ver. 2**

Nemuzu posoudit, ktera verze je presnejsi, protoze takovy problem, se dvema verzemi, nemel vubec nastat. Pres vsechny problemy se, ale jedna o zajimavy ukol.
