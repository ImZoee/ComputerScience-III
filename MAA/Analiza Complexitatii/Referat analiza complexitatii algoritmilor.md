### Analiza complexitatii pentru un algoritmul numărarea cifrelor unui număr(recursiv)
```C
int nr_cifre(int n) {
    if (n < 10)
        return 1;
    else
        return 1 + nr_cifre(n / 10);
}
```

### Etapele analizei complexitatii pentru algoritmul recursiv:
1. **Stabilirea dimensiunii datelor de intrare**
Dimensiunea datelor de intrare este `n` care reprezinta valoarea numarului citit. La fiecare apel recursiv `n` se imparte la 10, prin urmare dimensiunea problemei v-a scadea.

2. **Initializarea recursiei pe anumte cazuri initiale**
`n=7 -> T(7)=1 si n=0 -> T(0)=1`

3. **Rezolvarea relatiei de recursie prin metoda substitutiei inapoi pentru a determina** 
Conditia de oprire `n<10`
Cazul de baza `T(n) = 1, n<10`.

```
T(n) = T(n/10) + 1
	=T(n/100) + 2
	=T(n/1000) + 3
	=T(n/10000) + 4
	.
	.
	.
	=T(n/10k)+k
``` 

```
T(n) = T(n/10) +1 = [T(n/100)+1] +1 =
	=T(n/100) +2 = [T(n/1000)+1] +1 =
	=T(n/1000) +3 = [T(n/10000)+1] +1 =
	=T(n/10000) +4 = ......
	= ... T(n/10^k)+k -> T(n)=O(logn)
``` 