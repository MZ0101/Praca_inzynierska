# **Projekt analizy mikrostruktury elektrod ogniw paliwowych typu SOFC (Solid Oxide Fuel Cell)**

## **Opis**
   
Projekt został stworzony w celu znalezienia najkrótszych ścieżek  w mikrostrukturach elektrod ogniw paliwowych typu SOFC (stało tlenkowych ogniw paliwowych). Program wykorzystuje algorytmy Dijkstry i A* oraz bibliotekę Qt, aby przetworzyć obrazy o rozszerzeniu .BMP. Dodatkowo, biblioteka Qt została użyta do tworzenia prostego interfejsu użytkownika.

## **Opis Obrazów**

Obrazy, na których program działa, mają wymiary 200x200 pikseli, co można traktować jako graf pikseli. Piksele na obrazach występują w kolorach czarnym, białym lub różnych odcieniach szarości. Obecnie algorytm działa w taki sposób, że jeśli piksel jest biały, to przez ten obszar może przejść cząsteczka wodoru. Aby uruchomić algorytm, użytkownik musi wybrać punkt początkowy i końcowy, czyli numer obrazu oraz współrzędne piksela. Współrzędne można wprowadzić z klawiatury lub wybrać za pomocą narzędzia zaznaczania, co ułatwia wybór obrazu i punktów na obrazie. Program umożliwia także wybór liczby zestawów współrzędnych, na których ma działać algorytm - użytkownik może wybrać jeden lub dziesięć zestawów. W przypadku wyboru dziesięciu zestawów danych zostanie również obliczona średnia kosztu drogi.

## **Przetwarzanie Obrazów**

Program przetwarza obrazy, a wyniki działania algorytmu są wizualizowane na obrazach. Piksele o kolorach niebieskich symbolizują odwiedzone piksele, piksele zielone reprezentują ścieżkę, a piksele czerwone oznaczają punkty początkowe i końcowe.

## **Rodzaje Wyszukiwania Najkrótszej Ścieżki**
Na chwilę obecną program oferuje trzy różne kryteria wyszukiwania najkrótszej ścieżki:

- Koszt Dojścia do Wierzchołka (Algorytm Dijkstry): Algorytm ten zapewnia najbardziej dokładne wyniki, ale może być czasochłonny.<br>
- Koszt Dojścia + Odległość Euklidesowa (Algorytm A):* Ten tryb uwzględnia koszt dojścia do wierzchołka oraz odległość estymowaną, która jest obliczana jako odległość euklidesowa. Jest to kompromis między dokładnością a wydajnością.<br>
- Odległość Euklidesowa (Algorytm A):* Ten tryb jest najszybszy, ale nie zawsze daje najbardziej dokładne wyniki. Może być używany do ogólnego sprawdzenia możliwości znalezienia ścieżki.<br>

## **Możliwe Rozszerzenia**
Projekt można rozwijać, dodając nowe funkcje:

- Można dodać więcej algorytmów wyszukiwania ścieżki, aby dodać więcej opcji użytkownikowi.<br>
- Dodanie funkcji zapisywania wyników działania algorytmu bezpośrednio do pliku .xlsx lub .txt, co ułatwi analizę wyników.<br>
- Kontrola wielkości okien w programie w zależności od rozdzielczości wyświetlacza.
- Umożliwienie użytkownikowi przeglądania wyników przetwarzania w różnych zestawach danych.<br>
- Pozwolić użytkownikowi wybierać kryterium wyszukiwania ścieżki z poziomu przeglądu rezultatów.<br>
- Utworzyć instalator, który ułatwi innym użytkownikom instalację programu.<br>
- Można zoptymalizować działanie programu.<br>

