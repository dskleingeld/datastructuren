readme.txt

#1 - Info
Datastructuren Opdracht 2 - Expressie
Auteurs: 
David Kleingeld
Lisa Pothoven
Datum:
12-11-2016

#2 - Uitleg
De functie 'main' accepteert een txt file als volgt:
./expressie2 test.txt

Vervolgens kunnen via de command line meer opdrachten worden gegeven.

Het programma kan een expressie inlezen en weergeven in de commandline (exp, print).

Ook kan de boom worden weggeschreven naar een .dot bestand, met door de user gegeven bestandsnaam (dot).

Daarnaast is het programma in staat een waarde voor x in te vullen in de expressie (evaluate).

(simp)
Ook kan een expressie tot op zekere hoogte versimpeld worden. Het programma lost operaties tussen twee getallen op (zoals 3 * 4 = 12).
Operaties die zowel in het linker- als rechterkind een getal hebben, worden uitgevoerd.
Ook sommaties van drie lagen (zoals 2 + x + 4) worden versimpeld. Hetzelfde geldt voor producten (zoals 2 * x * 4).
Een deling door nul levert een foutmelding op, maar mag wel in de boom blijven staan.

(diff)
Differentieren werkt voor de meeste uitdrukkingen. Alleen gecompliceerde functies, zoals a^x, hebben we achterwege gelaten.
Het programma laat dan d/dx als ouder-knoop van de niet-differentieerdbare functie in de boom staan.

#3 - Over de Code
main.cpp bevat het user menu. Van hieruit kan de user een aantal public functies van klasse Boom aanroepen.

boom.cpp bestaat uit vijf gedeeltes, in de volgende volgorde: inlezen, afbeelden, versimpelen, evalueren en differentieren.