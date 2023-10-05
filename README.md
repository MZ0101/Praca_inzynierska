# Inzynierka_2
Projekt służy do znajdowania najkrótszej ścieżki w analizie mikrostruktury elektrod ogniw paliwowych typu SOFC. 
Do określenia najkrutrzej sciezki zastosowano algorytm Dikstry oraz A*, ponadto wykożystano biblioteke Qt w celu sprawnejszego przetwarzania obrazów w formacie .BMP.
Biblioteke Qt wykożystano również do późniejszego opracowania prostego interfejsu.

Obrazy , na którch program pracuje posiadają wymiar 200x200 pikseli, czyli w zasadze jest to graf pikseli. Obrazy zostały uprzednio przygotowane w wyniku czego pkslese posiadają kolory czarne, białe lub odcenie szarości. 
Obecnie algorytm dział tak, że jeżeli tylko piksel jest biały to czasteczka wodoru może przejść tą drogą. Aby algorytm rozpoczą pracę należy wybrac punkt począdkowy oraz końcowy, czyli numer obrazu oraz współżędne piksela.
Współżędne mozna wpisać z klawaitury lub wybrac opcję zaznaczania spowoduje to, że będze można wybrać obraz oraz zaznaczyć współżędne piksela za pomocą myszki. Program posiada opcję wyboru na ilu zestawach współżędnych ma pracować, jeden lub dziesięć.
W przypadku wyboru dzisięciu zestawów danych zostanie rówaniez obliczona średnia kosztu drogi. 
Na końcu można przejżeć rezultaty działania algorytmu, obrazy które zostały przetworzone zostają zapisane. Piksele o kolorach niebieskich symbolizują odwiedzony piksel, piksele zielone ścierzkę natomiast czerwone współżędne startowe oraz końcowe. 

Na chwilę obecną algorytm oferuje wyszukiwanie najkrótszej ścieżki na trzy sposoby, uwzględniając trzy różne kryteria:
- koszt dojścia do wierzchołka (algorytm dikstry)
- suma kosztu dojscia do wierzchołka oraz odległości estymowanej, która w tym przypadku jest odległoscią eukleidesową (algorytm A*)
- odległość eukleidesowa (algorytm A*)

Wyżej wymienione sposoby wyszukiwania najkrutrzej ścieżki różnia się dokładnością oraz czasem wykoanania, wyszukiwanie najkrutrzej ścierzki bazując na algorytmie dikstry jest najbardziej dokładne oraz czasochłonne.
Natomiast wyszukiwanie poprzez odległośc eukleidesowa jest najmniej dokładną metodą ale najszybszą, może na przykład posłużyc do określenia czy jest możlwie znalezienie scierzki.

Ogólne rzecz ujmując możliwe jest rozbudowanie programu o:
- zapis wyników jego działąnia bezpośrednio w pliku .xlsx lub posrednio porzez plik .txt, następnie okreslenie najlepszego sposobu wyszukiwania najkrutrzej ścierzki przez analize wyników działania algorytmu.
- wybór folderu z danymi.
- wybór sposbu 


