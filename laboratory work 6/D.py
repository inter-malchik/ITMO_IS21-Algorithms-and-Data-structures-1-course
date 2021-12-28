def hashify(string, maximun, k):
    result = 0
    argument = 1
    for symbol in string:
        result += ord(symbol) * argument
        argument *= k
    return result % maximun


class HashSet:
    def __init__(self, hashtable_size=73):
        self.hashtable = [[] for _ in range(hashtable_size)]
        self.size = hashtable_size
        self.power = 0

    def add(self, element):
        key = hashify(element, self.size, 3)
        if not self.hashtable[key]:
            self.hashtable[key].append(element)
            self.power += 1
        else:
            if not any(a == element for a in self.hashtable[key]):
                self.hashtable[key].append(element)
                self.power += 1

    def delete(self, element):
        key = hashify(element, self.size, 3)
        try:
            self.hashtable[key].remove(element)
            self.power -= 1
            if not self.hashtable[key]:
                self.hashtable[key] = []
        except ValueError:
            return

    def getall(self):
        answer = ' '.join(sum(filter(lambda x: bool(x), self.hashtable), start=[]))
        if not answer:
            return '0'
        return f"{self.power} {answer}"


class MultiMap:
    class MapNode:
        def __init__(self, key):
            self.key = key
            self.data = HashSet()

    def __init__(self, hashmap_size=99907):
        self.hashtable = [[] for _ in range(hashmap_size)]
        self.size = hashmap_size

    def add(self, element, value):
        hashkey = hashify(element, self.size, 137)
        if not self.hashtable[hashkey]:
            newnode = self.MapNode(element)
            newnode.data.add(value)
            self.hashtable[hashkey].append(newnode)
        else:

            for a in self.hashtable[hashkey]:
                if a.key == element:
                    a.data.add(value)
                    return
            newnode = self.MapNode(element)
            newnode.data.add(value)
            self.hashtable[hashkey].append(newnode)

    def deletepair(self, element, value):
        hashkey = hashify(element, self.size, 137)
        try:
            for node in self.hashtable[hashkey]:
                if node.key == element:
                    node.data.delete(value)
        except ValueError:
            return

    def deleteall(self, element):
        hashkey = hashify(element, self.size, 137)
        try:
            self.hashtable[hashkey] = list(filter(lambda x: x.key != element, self.hashtable[hashkey]))
            if not self.hashtable[hashkey]:
                self.hashtable[hashkey] = []
        except ValueError:
            return

    def get(self, element):
        hashkey = hashify(element, self.size, 137)
        if not self.hashtable[hashkey]:
            return '0'
        else:
            try:
                return tuple(filter(lambda x: x.key == element, self.hashtable[hashkey]))[0].data.getall()
            except IndexError:
                return '0'


def main():
    fin, fout = open('multimap.in', 'r'), open('multimap.out', 'w')
    our_multimap = MultiMap()
    while True:
        line = fin.readline()
        if not line:
            break
        if line[-1] == '\n':
            line = line[:-1]
        command, *arguments = line.split()
        if command == 'put':
            our_multimap.add(arguments[0], arguments[1])
        elif command == 'get':
            fout.write(our_multimap.get(arguments[0]))
            fout.write('\n')
        elif command == 'delete':
            our_multimap.deletepair(arguments[0], arguments[1])
        elif command == 'deleteall':
            our_multimap.deleteall(arguments[0])
    fin.close()
    fout.close()


if __name__ == "__main__":
    main()
