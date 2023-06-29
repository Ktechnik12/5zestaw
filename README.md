# Program rysujący na płótnie

Program rysujący różne figury na płótnie oraz generujący cień na podstawie dostępnego światła.

## Opis

Ten program umożliwia rysowanie różnych figur, takich jak kwadraty, koła i trójkąty, na płótnie o określonych wymiarach. Dodatkowo, można określić położenie źródła światła, które generuje cień dla figur na płótnie.

## Wymagania

Aby uruchomić program, wymagane jest posiadanie kompilatora C++ oraz biblioteki standardowej C++. Program wykorzystuje bibliotekę `iostream` do obsługi wejścia/wyjścia, `fstream` do operacji na plikach, `vector` do przechowywania figur, `string` do manipulacji łańcuchami znaków, `sstream` do parsowania danych wejściowych oraz `cmath` do obliczeń matematycznych.

## Instrukcje

1. Skompiluj program, używając kompilatora C++.
2. Uruchom program, podając nazwę pliku konfiguracyjnego jako argument.
3. Plik konfiguracyjny powinien zawierać informacje o wymiarach płótna, nazwie pliku wyjściowego, symbolu pustego miejsca na płótnie oraz figurach do narysowania.
4. Figury mogą być kwadratami, kołami lub trójkątami. Każda figura jest określona przez typ figury, współrzędne jej środka, rozmiar oraz symbol do rysowania.
5. Opcjonalnie, można określić również położenie źródła światła, które generuje cień dla figur na płótnie.
6. Po zakończeniu program wyświetli rysunek na standardowym wyjściu oraz, jeśli podano nazwę pliku wyjściowego, zapisze rysunek do pliku.

## Przykład użycia

`$ ./program plik_konfiguracyjny.txt`

## Format pliku konfiguracyjnego

Plik konfiguracyjny powinien mieć następujący format:

- canvas_width *`szerokość_płótna`*
- canvas_height *`wysokość_płótna`*
- output_filename *`nazwa_pliku_wyjściowego`*
- empty_symbol *`symbol_pustego_miejsca`*
- figure *`typ_figury x y rozmiar symbol`*
- light *`x y symbol_oznaczający_miejsce symbol_światła`*

## Typy figur

- *`square x y rozmiar symbol`* - generuje kwadrat o środku w punkcie *`x`*, *`y`*; długości boku *`rozmiar`*. Jest on narysowany znakiem *`symbol`*.
- *`circle x y promien symbol`* - generuje koło o środku w punkcie *`x`*, *`y`*; promieniu *`promien`*. Jest on narysowany znakiem *`symbol`*.
- *`triangle1 x y rozmiar symbol`* - generuje prawy trójkąt rosnący o środku w punkcie *`x`*, *`y`*; rozimarze *`rozmiar`*. Jest on narysowany znakiem *`symbol`*.
- *`triangle2 x y rozmiar symbol`* - generuje prawy trójkąt malejący o środku w punkcie *`x`*, *`y`*; rozimarze *`rozmiar`*. Jest on narysowany znakiem *`symbol`*.
- *`triangle3 x y rozmiar symbol`* - generuje lewy trójkąt rosnący o środku w punkcie *`x`*, *`y`*; rozimarze *`rozmiar`*. Jest on narysowany znakiem *`symbol`*.
- *`triangle4 x y rozmiar symbol`* - generuje lewy trójkąt malejący o środku w punkcie *`x`*, *`y`*; rozimarze *`rozmiar`*. Jest on narysowany znakiem *`symbol`*.

## Trójkąty:

Przykłady narysowanych trójkątów:

1. `triangle1 x y rozmiar symbol`:
* o
oo
ooo*

2. `triangle2 x y rozmiar symbol`:
*ooo
oo
o

3. `triangle3 x y rozmiar symbol`
*   o
  oo
 ooo
oooo

4. `triangle4 x y rozmiar symbol`
*oooo
 ooo
  oo
   o




