def merge_sort(arr: list):
    n = len(arr)
    if n <= 1:
        return arr
    key_ind = n // 2
    left, right = arr[:key_ind], arr[key_ind:]
    return merge(merge_sort(left), merge_sort(right))


def key_sravn(x, y):
    if x[0] > y[0] or x[0] == y[0] and x[1] > y[1]:
        return 1  # bigger
    elif x[0] < y[0] or x[0] == y[0] and x[1] < y[1]:
        return -1  # smaller
    return 0  # equal


def merge(a: list, b: list):
    n, k = len(a), len(b)
    n1 = k1 = 0
    merged = []
    while n1 != n and k1 != k:
        if key_sravn(a[n1], b[k1]) > 0:
            merged.append(b[k1])
            k1 += 1
        elif key_sravn(a[n1], b[k1]) < 0:
            merged.append(a[n1])
            n1 += 1
        else:
            merged.append(a[n1])
            merged.append(b[k1])
            n1 += 1
            k1 += 1
    merged.extend(a[n1:])
    merged.extend(b[k1:])
    return merged


f1, f2 = open('race.in', 'r'), open('race.out', 'w')
n = int(f1.readline())
data = []
for i in range(n):
    country, runner = f1.readline().split()
    place = i + 1
    data.append((country, place, runner))
data = merge_sort(data)
# print(data)
cntr_prev = data[0][0]
f2.write(f'=== {cntr_prev} ===\n')
for n2, obj in enumerate(data):
    if cntr_prev == obj[0]:
        f2.write(f'{obj[-1]}')
        if n2 < n-1:
            f2.write('\n')
    else:
        f2.write(f'=== {obj[0]} ===\n')
        f2.write(f'{obj[-1]}')
        if n2 < n - 1:
            f2.write('\n')
        cntr_prev = obj[0]

f1.close()
f2.close()
