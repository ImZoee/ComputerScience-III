### Analiza complexitatii pentru un algoritmul numărarea cifrelor unui număr(iterativ)
```c
int sumaDeasupraDiagonalei(int a[][100], int n) {
    int suma = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (j > i) {         
                suma += a[i][j]; 
            }
        }
    }
    return suma;
}
```


| `Instructiune`                | `Cost`            | `Nr. Rep`     |
| ----------------------------- | ----------------- | ------------- |
| `int suma = 0;`               | `c`               | `1`           |
| `for (int i = 0; i < n; i++)` | `c + c(n+1) + cn` | `n + 1`       |
| `for (int j = 0; j < n; j++)` | `c + c(n+1) + cn` | `n*(n + 1)`   |
| `if (j > i)`                  | `c`               | `n * n = n^2` |
| `suma += a[i][j];`            | `c`               | `n * (n-1)/2` |
| `return suma;`                | `c`               | `1`           |

|       | `c`   | `c(n+1)` | `cn`  |
| ----- | ----- | -------- | ----- |
| `for` | `i=0` | `i<n`    | `i++` |
| `for` | `j=0` | `j<n`    | `j++` |
**Algoritmul nu prezinta un caz favorabil/defavorabil deoarece nu are oprire anticipata.**
TCMF(n)=c⋅1 +(c⋅1+c(n+1)+cn) +n(c⋅1+c(n+1)+cn) +c⋅n2 +c⋅n(n−1)/2 +c⋅1 -> O(n)
TCMD(n)= ........ -> O(n)