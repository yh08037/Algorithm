# Algorithm
2019년 경북대학교 2학기 알고리즘1


## 예습

### Insertion Sort & Merge Sort
정렬 알고리즘을 공부해야 하는 진짜 이유는 정렬 알고리즘 뒤에 숨어있는 개념이 다른 많은 문제를 해결하는 데 쓰이는 알고리즘에도 적용되기 때문이다. 실제로 힙 정렬을 자료 구조와 관련되어 있고 퀵 정렬은 무작위화, 병합 정렬은 분할 정복과 관련되어 있다.

#### Insertion Sort (삽입 정렬)
배열 내에서 정렬된 영역과 정렬되지 않은 부분을 만들어 낸다. 매번 순환을 할 때마다 다음으로 정렬되지 않은 원소가 정렬된 영역에서 제자리를 찾아가게 된다.

```c
#include <algorithm>  // std::swap()

// swap을 통해 한칸씩 삽입 위치로 내려감
void insertion_sort(int s[], int n) {
    int i, j;

    for (i=1; i<n; i++) {
        j = i;
        while ((j>0) && (s[j-1] > s[j])) {
            std::swap(s[j], s[j-1]);
            j = j-1;
        }
    }
}
```

```c
// 대입을 통해 뒤로 한칸씩 밀어낸 후 삽입
void insertion_sort(int s[], int n) {
    int i, j, key;

    for (i=1; i<n; i++) {
        key = s[i];
        j = i;
        while ((j>0) && (s[j-1] > key)) {
            s[j] = s[j-1];
            j = j-1;
        }
        s[j] = key;
    }
}
```


## Dynamic Programming

### 1. LCS :  Longest Common Subsequence

```pseudocode
m, n = length of x, y

for i = 1 to m	c[i, 0] = 0
for j = 1 to n	c[0, j] = 0

for i = 1 to m
  for j = 1 to n
    if x[i] == y[j]  c[i, j] = c[i-1, j-1] + 1
    else             c[i, j] = max(c[i, j-1], c[i-1, j])
        
result = c[m, n]
```

### 2. 0-1 Knapsack

~~~ pseudocode
W = max weight
n = number of items

for w = 0 to W  B[0, w] = 0
for i = 0 to n  B[i, 0] = 0

for i = 0 to n
  for w = 0 to W
    if w[i] <= w  B[i, w] = max(b[i] + B[i-1, w-w[i]], B[i-1, w])
    else          B[i, w] = B[i-1, w]
    
result = B[n, W]
~~~

## Greedy Algorithm

### 1. Coin Change

``` pseudocode
모든 동전의 액수가 배수 관계에 있을 때, 액수가 가장 큰 동전부터 최대한 많이 포함시키면 최적해
70원, 160원 등의 동전이 존재한다면 Greedy로 풀이 불가능
```

### 2. Fractional Knapsack

```pseudocode
단위 무게 당 가장 가치가 높은 item부터 sack에 포함시키면 최적해
임의의 비율로 item을 자를 수 없다면 Greedy로 풀이 불가능
```

### 3. Set Cover



### 4. 



## 과제
### HW1 : Binary Search
### HW2 : Insertion Sort & Merge Sort
### HW3 : Binary Search Tree
