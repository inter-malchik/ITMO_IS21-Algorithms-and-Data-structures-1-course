f = open('smallsort.in', 'r')
N = int(f.readline())
array = list(map(int, f.readline().split()))
f.close()
for i in range(1, N):
    x = array[i]
    ind = i
    while ind > 0 and array[ind - 1] > x:
        array[ind], array[ind - 1] = array[ind - 1], array[ind]
        ind -= 1
f = open('smallsort.out', 'w')
f.write(f'{array[0]}')
for i in array[1:]:
    f.write(f' {i}')
f.close()
