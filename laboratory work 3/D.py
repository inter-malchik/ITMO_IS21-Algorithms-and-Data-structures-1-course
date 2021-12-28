from math import inf as infinity


class Heap:
    def __init__(self):
        self.heap_size = 0
        self.data = [[None, None]]

    def parent(self, i):
        if i > 1:
            return i // 2

    def left(self, i):
        if 2 * i <= self.heap_size:
            return 2 * i

    def right(self, i):
        if 2 * i + 1 <= self.heap_size:
            return 2 * i + 1

    def __str__(self):
        return ' '.join(str(x) for x in self.data[1:])


class MinHeap(Heap):
    def build_min_heap(self):
        for i in range(self.heap_size // 2, 0, -1):
            self.min_heapify(i)

    def min_heapify(self, ind):
        left_kid, right_kid = self.left(ind), self.right(ind)
        if left_kid and self.data[left_kid][0] < self.data[ind][0]:
            mini = left_kid
        else:
            mini = ind
        if right_kid and self.data[right_kid][0] < self.data[mini][0]:
            mini = right_kid
        if mini != ind:
            self.data[ind], self.data[mini] = self.data[mini], self.data[ind]
            self.min_heapify(mini)


class MinPriorityQueue(MinHeap):
    def get_minimum(self):
        if self.heap_size:
            return self.data[1]

    def extract_min(self):
        mini = self.get_minimum()
        if not mini:
            return '*'
        self.data[1] = self.data[self.heap_size]
        del self.data[self.heap_size]
        self.heap_size -= 1
        self.min_heapify(1)
        return mini

    def decrease_key(self, line_num, new_value, ind=0):
        if not ind:
            for i in range(1, self.heap_size + 1):
                if self.data[i][1] == line_num:
                    ind = i
                    break
        self.data[ind][0] = new_value
        while ind > 1 and self.data[self.parent(ind)][0] > self.data[ind][0]:
            self.data[ind], self.data[self.parent(ind)] = self.data[self.parent(ind)], self.data[ind]
            ind = self.parent(ind)

    def add(self, value, line_num):
        self.heap_size += 1
        self.data += [[infinity, line_num]]
        self.decrease_key(line_num, value, ind=self.heap_size)


def main():
    our_queue = MinPriorityQueue()
    line_number = 1
    line = fin.readline()
    first_output = True
    while line and line != '\n':
        command, *arguments = line.split()
        if command == 'push':
            our_queue.add(int(arguments[0]), line_number)
        elif command == 'extract-min':
            if not first_output:
                fout.write('\n')
            else:
                first_output = False
            fout.write(str(our_queue.extract_min()[0]))
        elif command == 'decrease-key':
            our_queue.decrease_key(int(arguments[0]), int(arguments[1]))
        line = fin.readline()
        line_number += 1


if __name__ == "__main__":
    fin, fout = open('priorityqueue.in', 'r'), open('priorityqueue.out', 'w')
    main()
    fin.close()
    fout.close()
