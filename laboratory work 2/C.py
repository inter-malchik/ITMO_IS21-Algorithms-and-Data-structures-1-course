def inversion(lis):
    global count

    def merge_sort(arr: list):
        n = len(arr)
        if n <= 1:
            return arr
        key_ind = n // 2
        left, right = arr[:key_ind], arr[key_ind:]
        return merge(merge_sort(left), merge_sort(right))

    def merge(a: list, b: list):
        global count
        n, k = len(a), len(b)
        n1 = k1 = 0
        merged = []
        while n1 != n and k1 != k:
            if a[n1] > b[k1]:
                merged.append(b[k1])
                k1 += 1
                count = count + n - n1
            elif a[n1] < b[k1]:
                merged.append(a[n1])
                n1 += 1
            else:
                merged.append(a[n1])
                n1 += 1
        merged.extend(a[n1:])
        merged.extend(b[k1:])
        if k < n != n1:
            count = count + n - n1
        return merged

    merge_sort(lis)
    return count


f1, f2 = open('inversions.in', 'r'), open('inversions.out', 'w')
n = int(f1.readline())
count = 0
f2.write(f'{inversion(list(map(int, f1.readline().split())))}')
f1.close()
f2.close()
