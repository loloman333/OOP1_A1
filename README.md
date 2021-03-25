# Assignment 1

Ziel von Assignment 1 ist es, einen Pathfinding-Algorithmus selbst zu implementieren.  

Einfache Beispiele für Pathfinding-Algorithmen sind zB. [*Breadth First Search*](https://de.wikipedia.org/wiki/Breitensuche) oder [*Depth First Search*](https://de.wikipedia.org/wiki/Tiefensuche). Welchen Algorithmus du implementierst, bleibt dir überlassen.

Es soll überprüft werden, ob ein Pfad zwischen zwei Items auf einem Spielfeld (Board) besteht. Das Board besteht auf Feldern. Ein Feld kann leer sein, eine Straße sein, eine geblockte Straße sein oder es liegt ein Item an dieser Stelle.

Zunächst sind drei Klassen zum gegebenen Framework hinzuzufügen, danach ist der Pathfinding-Algorithmus in der Klasse `Board` zu implementieren. 

Solltest du weitere Klassen/Attribute/Methoden benötigen kannst du diese beliebig hinzufügen. **Die `main.cpp` darf jedoch nicht verändert werden!** 

*Tipp: In der main.cpp werden bereits die zu implementierenden Klassen verwendet, daher kompiliert das Programm erst, wenn alle Klassen implementiert wurden.*

## Config File

Das Einlesen des Config-Files (.txt-File) wird vom Framework bereits vollständig übernommen. Du musst dich daher auch nicht um die Behandlung von fehlerhaften oder falschen Config-Files kümmern. 

#### Aufbau

| Zeile | Beschreibung                      |
| ----- | --------------------------------- |
| 1     | Höhe des Boards               |
| 2     | Breite des Boards             |
| 3     | Anzahl an Items auf dem Board |
| 4-X   | Das Board                     |

#### Beispiel-Config-File (*.txt)

```
4
4
2
#A##
 # %
## B
 ###
```

#### Feld-Typen

| Symbol | Bezeichnung                                                  |
| ------ | ------------------------------------------------------------ |
| ' '    | Leeres Feld: Hier ist weder eine Straße, noch ein Item. Repräsentiert als NULL auf dem Board |
| #      | Straßenfeld: Straßen stellen Verbindungen zwischen Items her. |
| %      | Geblocktes Straßenfeld: Straße, die aktuell gesperrt ist und nicht verwendet werden kann. |
| X      | Itemfeld: Hier liegt ein Item auf dem Board. `X` ist der Name des Items und dieser besteht nur aus einem Großbuchstaben (A-Z). |





## Klasse Field (zu implementieren)

Die Klasse `Field` repräsentiert ein Feld auf dem Board. Ein Feld auf dem Board kann entweder leer sein (NULL), ein `Item` oder eine `Road` sein. 

Die Klasse `Field` ist eine **abstrakte Klasse** und die Basisklasse für die Klassen `Item` und `Road`.

Innerhalb der Klasse soll folgendes struct verwendet werden (Definition außerhalb der Klasse in *Field.hpp*):

```
typedef struct _Coordinates_ 
{
  size_t row_;
  size_t column_;
} Coordinates;
```



##### Attribute

- `field_id_`
  - Die ID des Feldes als int
- `position_`
  - Die Position des Feldes am `board_` als Datentyp `Coordinates` 

##### Konstruktoren

- `Field(Coordinates pos)`
  - setzt die Attribute:
    - `field_id_` auf die nächste ID des Fields (erstelle dafür einen static counter)
    - `position_` auf `pos`

##### Methoden

- `getFieldId()`
  - Rückgabewert: int
  - gibt das Attribut `field_id_` zurück
- `getPosition()`
  - Rückgabewert: Coordinates
  - gibt das Attribut `Coordinates` zurück
- `isBlocked()`
  - eine rein virtuelle ("pure virtual") Methode der Klasse
  - Rückgabewert: bool
  - muss von den abgeleiteten Klassen implementiert werden
- `print()`
  - eine rein virtuelle ("pure virtual") Methode der Klasse
  - Rückgabewert: void
  - muss von den abgeleiteten Klassen implementiert werden




## Klasse Item (zu implementieren)

`Item` ist ein Spezialfall von `Field` und soll daher von `Field` abgeleitet werden. 

##### Attribute

- `name_`
  - Der Name des Items bestehend aus einem einzigen Großbuchstaben

##### Konstruktoren

- `Item(char name, Coordinates pos)`
  - setzt das Attribut 
    - `position_` (von Field) auf pos
    - `name_` auf `name`
  

##### Methoden

- `getName()`
  - Rückgabewert: char
  - gibt das Attribut `name_` zurück
- `isBlocked()`
  - Implementierung der virtuellen Methode der Basisklasse
  - Items blockieren immer das Weiterkommen in diese Richtung auf dem Board
  - Rückgabewert: bool
  - Rückgabewert: `true`
- `print()`
  - Implementierung der virtuellen Methode der Basisklasse
  - Rückgabewert: void
  - gibt das Attribut `name_` auf `stdout` aus (also genau einen char, keinen zusätzlichen Whitespace)



## Klasse Road (zu implementieren)

`Road` ist ein Spezialfall von `Field` und soll daher von `Field` abgeleitet werden. 

##### Attribute

- `blocked_`
  - Gibt als bool an, ob diese Road blockiert ist
- `number_of_blocked_roads_`
  - Die Gesamtzahl an geblockten Roads als Ganzzahl 
  - ein Counter für **ALLE** Instanzen der Klasse (static)

##### Konstruktoren

- `Road(bool blocked, Coordinates pos)`
  - setzt das Attribut 
    - `position_` (von Field) auf `pos`
    - `blocked_` auf `blocked`

##### Methoden

- `getNumberOfBlockedRoads()`
  - Rückgabewert: static int
  - gibt das Attribut `number_of_blocked_roads_` zurück
- `isBlocked()`
  - Implementierung der virtuellen Methode der Basisklasse
  - Roads können `blocked` sein, das bedeutet man kann sie nicht verwenden
  - Rückgabewert: bool
  - gibt das Attribut `blocked_` zurück
- `print()`
  - Implementierung der virtuellen Methode der Basisklasse
  - Rückgabewert: void
  - gibt auf `stdout` aus (wiederum genau einen char, keinen zusätzlichen Whitespace)
    - `%` wenn die Straße blockiert ist (bei printf ist `%` der format specifier - [Tipp](https://www.geeksforgeeks.org/how-to-print-using-printf/))
    - `#` wenn die Straße verwendet werden kann





## Klasse Board (teilweise implementiert)

Wenn die obigen 3 Klassen implementiert wurden, kann die Klasse Board erweitert werden. Diese repräsentiert das Board und ist bereits teilweise implementiert.  Die fehlenden Implementierungen sind mit **TODO begin** und **TODO end** gekennzeichnet.

##### Attribute

- `height_`
  - Die Höhe des Boards
- `width_`
  - Die Breite des Boards
- `number_items_`
  - Die Anzahl an Items am Board
- `board_`
  - Das Board als 2D-std::vector vom Datentyp `Field*`
  - `Field*` ist NULL (Nullpointer) wenn das Feld leer ist
  - ansonsten liegt an dieser Stelle ein `Item*` oder ein `Road*`
- `items_`
  - Die Items als 1D-std::vector vom Datentyp `Item*`

##### Konstruktoren

- `Board(size_t height, size_t width, size_t nr_items, char** fields)`
  - bereits implementiert

##### Destruktor

- ~Board()
  - bereits implementiert
  - gibt den Speicher für `board_` und `items_` wieder frei

##### Methoden

- `initializeFields(char** fields)`
  - muss implementiert werden
  - iteriert über das gesamte 2D-`fields` (aus Methodenargument)
  - erstellt für jedes Feld das entsprechende Objekt am Heap und fügt dieses am Attribut `board_` ein.
    - ' ' leere Felder werden am `board_` als NULL dargestellt
    - `#` : `Road`-Objekt
    - `%` : geblockte `Road`-Objekte
    - `X` : `Item`-Objekte, wobei `X` alle Großbuchstaben A-Z annehmen kann
  - ist das Feld ein Item, soll es auch in den Item-Vector `items_` gespeichert werden. 
- `deleteFields()`
  - muss implementiert werden
  - iteriert über das gesamte 2D-`board_`
  - gibt den angeforderten Speicher (aus `initializeFields()`) der Felder am `board_` wieder frei
- `findPath(Item* from_item, Item* to_item)`
  - muss implementiert werden
  - Hier kann ein Pathfinding-Algorithmus eurer Wahl implementiert werden
    - z.B. *Breadth First Search* oder *Depth First Search*
  - Rückgabewert: bool
  - gibt `true` zurück, wenn ein Pfad zwischen `from_item` und `to_item` existiert (siehe [Pathfinding-Algorithmus](#Pathfinding-Algorithmus))
  - und `false`, wenn dieser nicht existiert





## Pathfinding-Algorithmus

Wenn die Klassen implementiert sind, soll bestimmt werden, ob zwischen 2 Items ein Weg besteht, der ausschließlich über nicht blockierte Straßen verläuft.



#### Implementierung

In der Klasse Board existiert bereits eine Methode 

 `bool findPath(Item* from_item, Item* to_item)`

welche Pointer auf die beiden Items als Argumente erhält. In dieser Methode soll nun herausgefunden werden, ob ein Pfad zwischen den beiden Items auf dem `board_` existiert oder nicht. Gibt es einen durchgehenden Weg, soll die Funktion `true` zurückgeben, andernfalls `false`. Trivialerweise sind Items die (vertikal oder horizontal) unmittelbar nebeneinander liegen immer miteinander verbunden, ebenso wenn `from_item` und `to_item` ident sind.



#### Beispiele Weg zwischen `Item A` und `Item B` vorhanden

Ein Weg zwischen zwei Items besteht dann, wenn eine durchgehende Straße (vertikal oder horizontal) zwischen beiden Items vorhanden ist (diagonal gilt nicht als durchgehend!):

```
A#B
```

```
A##
  #
  B
```

```
A#####
     #
B#####
```

```
A       B#
#  ###   #
#### #####
```

Der Pfad kann an anderen Items vorbeiführen:

```
A# 
 ##
 C#
B##
```

Solang es **einen** Weg ohne geblockte Straßen gibt, ist ein Weg vorhanden:

```
A#######
 %#%  %#
###%#####
%  %%%#%%
B########
```



#### Beispiel Weg zwischen  `Item A` und `Item B`  nicht vorhanden

```
A# B
```

Diagonale Verbindungen zählt nicht als durchgehend:

```
A##
   ##B
```

```
 A####
#     #
###B###
```

Verstellt ein weiteres Item den Weg zwischen A und B, so ist ein Pfad zwischen A und B nicht vorhanden:

```
A###C##B
```

```
A# 
 # 
#C#
B##
```

Verstellen geblockte Straße den Weg, ist der Pfad zwischen A und B nicht vorhanden:

```
A##%##B
```

```
#####A
  ##
  %#
  #
  B
```

```
A#######
 %#%  %#
###%#####
%  %%%#%%
B####%###
```





## Spezifikation

- nur geforderte Ausgaben

- main.cpp darf nicht verändert werden



## Erlaubte Bibliotheken

- alle Bibliotheken der C++ Standard Library



## Abgabe und Bewertung

- Push auf das *eigene* Gitlab Repository **auf einen Branch namens `submission`**
- **Deadline: 7.4.2021** (Achtung geändert !)

#### Ausbesserung

Falls die benötigten 3 Testcases zur Deadline am 7.4.2021 noch nicht bestanden werden, gibt es die Möglichkeit einer **Ausbesserung ohne Punkteabzug bis 10.4.2021**. Die Abgabe erfolgt ebenfalls auf das eigene Gitlab Repository **auf einen Branch namens `submission`**.

#### Bewertung

- Die Punkte werden anhand der bestanden Testcases vergeben. Andere Kriterien (wie z.B. Style Guide) kommen bei Assignment 1 nicht zur Anwendung. Das heißt, ein Programm, das beispielsweise 80% der Testcases besteht, bringt auch 80% der bei Assignment 1 erreichbaren Punkte.
- Es müssen **mindestens 3 der *öffentlichen* 6 Testcases** bestanden werden.
  - 6 Testcases werden veröffentlicht (public testcases), 6 private testcases
- Im Falle von Warnings (Speicherlöchern) [Verstößen gegen Spezifikationen in diesem Dokument] werden 10 (25) [25] % der erreichten Punkte abgezogen – bitte deshalb sehr gewissenhaft arbeiten.
