# IVS projekt 1

## Prostředí
Ubuntu 20.04

## Hodnocení
14.5/18
    - Špatné pochopení assert/expect. 
    - Expect nemůže být v cyklu, při chybě musí končit a ne pokračovat => assert.
<details>
<summary>Podrobné hodnocení.</summary>

```
Poznámky k úkolům:
	Black Box Testing:
		FIND: Při spuštění došlo k selhání. (Možná příčina je opomenutí ASSERT nebo je místo něj EXPECT.)
		Axiom 3: nedostatečně otestováno
		INSERT: Při spuštění došlo k selhání. (Možná příčina je opomenutí ASSERT nebo je místo něj EXPECT.)
		Axiom 2: nedostatečně otestováno
	White Box Testing:
		solveEquation: nedostatečně otestováno
	Test Driven Development:
		OK
Detail k bodům:
	Black Box Testing: 3.0      /6
	White Box Testing: 5.5      /6
	Test Driven Development: 6  /6
```
</details>
  

## Popis projektu
Implementace kódu na základě TDD testů, implementace testů WhiteBox a BlackBox.
[Celé zadání](https://github.com/Suikell/1.rocnik/blob/main/2.%20semestr/IVS/1.%20projekt/zad%C3%A1n%C3%AD.pdf)
