#**Inzynierka_2 - Projekt Analizy Mikrostruktury Elektrod SOFC**

#**Opis**

Projekt "Inzynierka_2" został stworzony w celu znajdowania najkrótszych ścieżek w analizie mikrostruktury elektrod ogniw paliwowych typu SOFC (stałotlenkowych ogniw paliwowych). Program wykorzystuje algorytmy Dijkstry i A* oraz bibliotekę Qt, aby efektywnie przetwarzać obrazy w formacie .BMP. Ponadto, biblioteka Qt została użyta do stworzenia prostego interfejsu użytkownika.

#**Opis Obrazów**

Obrazy, na których program działa, mają wymiary 200x200 pikseli, co można traktować jako graf pikseli. Piksele na obrazach występują w kolorach czarnym, białym lub różnych odcieniach szarości. Obecnie algorytm działa w taki sposób, że jeśli piksel jest biały, to przez ten obszar może przejść cząsteczka wodoru. Aby uruchomić algorytm, użytkownik musi wybrać punkt początkowy i końcowy, czyli numer obrazu oraz współrzędne piksela. Współrzędne można wprowadzić z klawiatury lub wybrać za pomocą narzędzia zaznaczania, co ułatwia wybór obrazu i punktów na obrazie. Program umożliwia także wybór liczby zestawów współrzędnych, na których ma działać algorytm - użytkownik może wybrać jeden lub dziesięć zestawów. W przypadku wyboru dziesięciu zestawów danych zostanie również obliczona średnia kosztu drogi.

#**Przetwarzanie Obrazów**

Program przetwarza obrazy, a wyniki działania algorytmu są wizualizowane na obrazach. Piksele o kolorach niebieskich symbolizują odwiedzone piksele, piksele zielone reprezentują ścieżkę, a piksele czerwone oznaczają punkty początkowe i końcowe.

**Rodzaje Wyszukiwania Najkrótszej Ścieżki**
Na chwilę obecną program oferuje trzy różne kryteria wyszukiwania najkrótszej ścieżki:

-Koszt Dojścia do Wierzchołka (Algorytm Dijkstry): Algorytm ten zapewnia najbardziej dokładne wyniki, ale może być czasochłonny.

-Koszt Dojścia + Odległość Euklidesowa (Algorytm A):* Ten tryb uwzględnia koszt dojścia do wierzchołka oraz odległość estymowaną, która jest obliczana jako odległość euklidesowa. Jest to kompromis między dokładnością a wydajnością.

-Odległość Euklidesowa (Algorytm A):* Ten tryb jest najszybszy, ale nie zawsze daje najbardziej dokładne wyniki. Może być używany do ogólnego sprawdzenia możliwości znalezienia ścieżki.

#**Możliwe Rozszerzenia**
Projekt można rozwijać, dodając nowe funkcje:

Dodanie Dodatkowych Algorytmów: Można dodać więcej algorytmów wyszukiwania ścieżki, aby dać użytkownikowi więcej opcji.
Optymalizacja: Można zoptymalizować działanie programu, aby działał jeszcze szybciej i bardziej efektywnie.
Zapis Wyników: Dodanie funkcji zapisywania wyników działania algorytmu bezpośrednio do pliku .xlsx lub .txt, co ułatwi analizę wyników.
Wybór Folderu z Danymi: Dodać możliwość wyboru folderu z danymi do przetworzenia.
Nawigacja po Wynikach: Umożliwienie użytkownikowi przeglądania wyników przetwarzania w różnych zestawach danych.
Wybór Kryterium Wyszukiwania: Pozwolić użytkownikowi wybierać kryterium wyszukiwania ścieżki z poziomu interfejsu użytkownika.
Instalator: Utworzyć instalator, który ułatwi innym użytkownikom instalację programu.
