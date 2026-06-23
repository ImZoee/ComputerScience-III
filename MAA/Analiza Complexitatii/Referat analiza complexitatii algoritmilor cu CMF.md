### Analiza complexitatii pentru un algoritmul numărarea cifrelor unui număr(iterativ) CMF/CMD
```c
int sumaDeasupraDiagonalei(int a[][100], int n) {
    int suma = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (a[i][j] < 0) break;
            suma += a[i][j];
        }
    }
    return suma;
}
```


| `Instructiune`                    | `Cost`            | `Nr. Rep`     |
| --------------------------------- | ----------------- | ------------- |
| `int suma = 0;`                   | `c`               | `1`           |
| `for (int i = 0; i < n; i++)`     | `c + c(n+1) + cn` | `n + 1`       |
| `for (int j = i + 1; j < n; j++)` | `c + c(n+1) + cn` | `n*(n + 1)`   |
| `if (a[i][j] < 0)`                | `c`               | `δ(n)`        |
| `suma += a[i][j];`                | `c`               | `n * (n-1)/2` |
| `break`                           | `c`               | `n-1`         |
| `suma += a[i][j];`                | c                 | `δ(n)`        |
| `return suma;`                    | c                 | 1             |

|       | `c`       | `c(n+1)` | `cn`  |
| ----- | --------- | -------- | ----- |
| `for` | `i=0`     | `i<n`    | `i++` |
| `for` | `j= i + 1 | `j<n`    | `j++` |

`CMF: ∀i, a[i][i+1]<0⇒δ(n)=0`
`CMD: (n)=c1+c2⋅n+c3⋅(n−1)+c4⋅δ(n)`

`TCMF(n)=c⋅1 +(c⋅1+c(n+1)+cn) +n(c⋅1+c(n+1)+cn) +c⋅n2 +c⋅n(n−1)/2 +c⋅1 -> O(n)`
`TCMD(n)= ........ -> O(n)`

