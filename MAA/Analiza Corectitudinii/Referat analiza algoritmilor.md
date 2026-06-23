### Analiza corectitudinii pentru un algoritmul numărarea cifrelor unui număr(recursiv)
``` c
int nr_cifre(int n) {
    if (n < 10)
        return 1;
    else
        return 1 + nr_cifre(n / 10);
}

int main() {
    int n;
    printf("Introdu un numar: ");
    scanf("%d", &n);

    printf("Numarul de cifre: %d\n", nr_cifre(n));

    return 0;
}

```
Pentru a putea demonstra ca algoritmul este partial corect vom folosi precondtiii si postconditii:

Preconditii:
I = N, Pi(n): n ∈ N, (n > 0)

Postconditie
O = N, (∀)n ∈ I Po(nr_cifre(n)) : 10^(nr_cifre(n)-1) ≤ n < 10^(nr_cifre(n))

1. Etapa de verificare:
Apelam functia nr_cifre(n) unde n = 475 astfel conditia if(475 < 10) este falsa iar functia trece pe ramura else, unde trebuie sa calculeze 1 + nr_cifre(475 / 10) unde rezultatul este 47 iar expresia devine 1 + nr_cifre(47), funcția se auto-apelează. În acest nou apel, condiția `if(47 < 10)` este falsă, deci se trece din nou pe ramura `else` pentru a calcula `1 + nr_cifre(47/10)`, adică `1 + nr_cifre(4)`. In ultimul apel, pentru `n = 4`, condiția `if(4 < 10)` este adevărată, iar funcția returnează `1`. Acest rezultat se propagă înapoi: calculul anterior devine `1 + 1 = 2`, iar calculul inițial devine `1 + 2 = 3`, care este rezultatul final.

2. Etapa de demonstratie
În etapa de demonstrare, pentru `n >= 10` se face apelul recursiv, iar noi presupunem că `nr_cifre` este corectă pentru un număr cu `k` cifre; prin apelul `1 + nr_cifre(n / 10)`, funcția se autoapelează cu un număr de `k` cifre (`n / 10`), care conform ipotezei returnează `k`, iar rezultatul final `1 + k` este exact numărul de cifre al lui `n` => Algoritm parțial corect.