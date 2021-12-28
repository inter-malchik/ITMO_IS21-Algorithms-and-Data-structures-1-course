def min_antiq(arr):
    for i in range(n):
        if i <= 1:
            continue
        else:
            arr[i // 2], arr[i] = arr[i], arr[i // 2]
    return arr


f1, f2 = open('antiqs.in', 'r'), open('antiqs.out', 'w')
n = int(f1.readline())
a = []
for i in range(n):
    a.append(i + 1)
f2.write(' '.join(str(x) for x in min_antiq(a)))
f1.close()
f2.close()
