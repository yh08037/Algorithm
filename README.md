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



## 과제
### HW1 : Binary Search
### HW2 : Insertion Sort & Merge Sort
### HW3 : Binary Search Tree
