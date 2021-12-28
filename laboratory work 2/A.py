from random import randint


def qsort(arr, n):
    if n <= 1:
        return arr
    contl, contb = 0, 0
    bigger, smaller = [], []
    indk = randint(0, n - 1)
    key = arr[indk]
    for i in range(n):
        if i == indk:
            continue
        elem = arr[i]
        if elem > key:
            bigger.append(elem)
            contb += 1
        else:
            smaller.append(elem)
            contl += 1
    del arr
    return qsort(smaller, contl) + [key] + qsort(bigger, contb)


f1, f2 = open('sort.in', 'r'), open('sort.out', 'w')

N = int(f1.readline()[:-1])
f2.write(' '.join([str(x) for x in qsort(list(map(int, f1.readline().split())), N)]))

f1.close()
f2.close()
