fin, fout = open('radixsort.in', 'r'), open('radixsort.out', 'w')
n, m, k = map(int, fin.readline().split())
arr = []
for i in range(n):
    arr.append(fin.readline()[:m])
ind = m
for _ in range(k):
    ind -= 1
    buffer = [0] * 256
    for i in range(n):
        buffer[ord(arr[i][ind])] += 1
    for temp in range(1, len(buffer)):
        buffer[temp] += buffer[temp - 1]
    ans = arr[::]
    for i in range(n - 1, -1, -1):
        line = arr[i]
        ans[buffer[ord(line[ind])] - 1] = line
        buffer[ord(line[ind])] -= 1
    arr = ans
fout.write('\n'.join(arr))
fin.close()
fout.close()
