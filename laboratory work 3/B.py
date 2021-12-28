class Heap:
    def __init__(self):
        self.heap_size = 0
        self.data = [None]

    def root(self):
        if self.heap_size:
            return self.data[1]

    def parent(self, i):
        if i > 1:
            return i // 2

    def left(self, i):
        if 2 * i <= self.heap_size:
            return 2 * i

    def right(self, i):
        if 2 * i + 1 <= self.heap_size:
            return 2 * i + 1


class MaxHeap(Heap):
    def __init__(self, arr):
        super().__init__()
        self.heap_size += len(arr)
        self.data.extend(arr)
        self.build_max_heap()

    def build_max_heap(self):
        for i in range(self.heap_size // 2, 0, -1):
            self.max_heapify(i)

    def heap_sort(self):
        for i in range(self.heap_size, 1, -1):
            self.data[1], self.data[i] = self.data[i], self.data[1]
            self.heap_size -= 1
            self.max_heapify(1)
        return self.data[1:]

    def max_heapify(self, ind):
        left, right = self.left(ind), self.right(ind)
        if left and self.data[left] > self.data[ind]:
            maxi = left
        else:
            maxi = ind
        if right and self.data[right] > self.data[maxi]:
            maxi = right
        if maxi != ind:
            self.data[ind], self.data[maxi] = self.data[maxi], self.data[ind]
            self.max_heapify(maxi)

    def __str__(self):
        return ' '.join(str(x) for x in self.data[1:])


if __name__ == "__main__":
    fin, fout = open('sort.in', 'r'), open('sort.out', 'w')
    n = int(fin.readline())
    pyramid = MaxHeap(list(map(int, fin.readline().split())))
    pyramid.heap_sort()
    fout.write(str(pyramid))
