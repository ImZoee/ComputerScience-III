``` c
int nr_cifre(int n) {
    int count = 0;
    
    while (n > 0) {
        count++;
        n = n / 10;
    }
    
    return count;
}

int main() {
    int n;
    printf("Introdu un numar: ");
    scanf("%d", &n);

    printf("Numarul de cifre: %d\n", nr_cifre(n));

    return 0;
}
```

Preconditia:
I = N, Pi(n): n ∈ N, (n > 0)

Postconditia:
O = N, (∀)n ∈ I, Po((n,count), count=nr_cifre(n)

Demonstram ca algoritmul este partial corect INVARIANTUL este:
I(n,count):numarul de cifre eliminate din n este count,iar n este partea intreaga ramasa din n  dupa eliminarea acelor cifre.

PROPRIETATEA 1: Invariantul este adevarat inainte de inceperea instructiunii repetitive.  
La inceput, inainte de intrarea in bucla, avem count = 0 si n = n0(valoarea initiala), deci nu s-a eliminat nicio cifra, numarul de cifre eliminate este count = 0 iar n este n0 fara 0 cifre taiate.  
Prin urmare I(n, count) = TRUE inainte de bucla.

PROPRIETATEA 2: Invariantul este mentinut in timpul executiei buclei.  
Consideram o iteratie generica a buclei in care conditia `n > 0` este adevarata si presupunem ca la inceputul iteratiei invariantul `I(n, count)` este adevarat, adica `n = floor(n0 / 10^count)` (s-au eliminat `count` cifre din `n`), apoi in interiorul buclei executam instructiunile `count++` si `n = n / 10`, astfel incat dupa `count++` numarul de cifre eliminate devine `count_nou = count_vechi + 1`, iar dupa `n = n / 10` obtinem
$$
n_{\text{nou}}
= \left\lfloor \frac{n_{\text{vechi}}}{10} \right\rfloor
= \left\lfloor \frac{\left\lfloor \frac{n0}{10^{\text{count}_{\text{vechi}}}} \right\rfloor}{10} \right\rfloor
= \left\lfloor \frac{n0}{10^{\text{count}_{\text{vechi}}+1}} \right\rfloor
= \left\lfloor \frac{n0}{10^{\text{count}_{\text{nou}}}} \right\rfloor .
$$

Deci dupa iteratie sunt eliminate exact `count_nou` cifre din `n0` si `n_nou` este partea intreaga ramasa din `n0` dupa eliminarea acestor `count_nou` cifre.  
Prin urmare invariantul ramane adevarat, adica `I(n_nou, count_nou) = TRUE`.

PROPRIETATEA 3: Invariantul este adevarat la terminarea buclei (postconditie).  
Bucla se opreste cand conditia `n > 0` devine falsa. Exemplu: `while (n > 0){...}` se termina cu `n = 0`.  
La terminarea buclei: ¬(n > 0) => n = 0.
$$I(n,\text{count}) : n = \left\lfloor \frac{n0}{\text{10count}}  \right\rfloor .$$
Deoarece bucla s-a oprit la primul moment cand `n` a devenit `0`, rezulta: `n = floor(x / 10^count) = 0`, iar inaintea ultimei iteratii `n ≠ 0`.  
De aici rezulta ca `n0 / 10^count < 1` ⇒ `n0 < 10^count` si inainte de ultima impartire `n0 / 10^{count-1} ≥ 1` ⇒ `n0 => 10^{count-1}`. Cu alte cuvinte `n` este un numar cu exact `count` cifre in baza 10 deci `count = nr_cifre(n0)`.
Prin urmare postconditia este indeplinita O = N, (∀)n ∈ I, Po((n,count), count=nr_cifre(n).

Algoritmul este partial corect si finititudinea (n = n / 10) => algoritm total corect.