class QuackVirtualMachine:
    class BinarySearchTree:
        class Node:
            def __init__(self, key, value, left=None, right=None):
                self.key = key
                self.value = value
                self.left = left
                self.right = right

        def __init__(self):
            self.root = None

        def add(self, key, value):
            if not self.root:
                self.root = self.Node(key, value)
            else:
                self.insert(key, value, self.root)

        def insert(self, new_key, new_value, current):
            if new_key > current.key:
                if current.right:
                    self.insert(new_key, new_value, current.right)
                else:
                    current.right = self.Node(new_key, new_value)
            elif new_key < current.key:
                if current.left:
                    self.insert(new_key, new_value, current.left)
                else:
                    current.left = self.Node(new_key, new_value)

        def get(self, key):
            root = self.root
            if not root:
                return False
            while True:
                if key == root.key:
                    return root.value
                elif key > root.key:
                    if root.right:
                        root = root.right
                    else:
                        return False
                else:
                    if root.left:
                        root = root.left
                    else:
                        return False

    class Queue:
        def __init__(self):
            self.stack_first = []
            self.stack_second = []

        def puts(self, num):
            self.stack_first.append(num)

        def gets(self):
            if self.stack_first or self.stack_second:
                if not self.stack_second:
                    while self.stack_first:
                        self.stack_second.append(self.stack_first.pop())
                return self.stack_second.pop()

    def __init__(self):
        self.labels = self.BinarySearchTree()
        self.queue = self.Queue()
        self.registers = [0] * 26


def main():
    quack_vm = QuackVirtualMachine()
    fin, fout = open("quack.in", 'r'), open("quack.out", 'w')
    commands = fin.read().split('\n')
    if not commands[-1]:
        del commands[-1]
    num_of_command = 0
    for n, i in enumerate(commands):
        if not i:
            continue
        if i[0] == ':':
            quack_vm.labels.add(i[1:], n)
    while True:
        try:
            command = commands[num_of_command]
        except IndexError:
            break
        if not command:
            continue
        if command.isnumeric():
            quack_vm.queue.puts(int(command) % 65536)
        elif command[0] == '+':
            quack_vm.queue.puts((quack_vm.queue.gets() + quack_vm.queue.gets()) % 65536)
        elif command[0] == '-':
            quack_vm.queue.puts((quack_vm.queue.gets() - quack_vm.queue.gets()) % 65536)
        elif command[0] == '*':
            quack_vm.queue.puts((quack_vm.queue.gets() * quack_vm.queue.gets()) % 65536)
        elif command[0] == '/':
            x, y = quack_vm.queue.gets(), quack_vm.queue.gets()
            if y == 0:
                quack_vm.queue.puts(0)
            else:
                quack_vm.queue.puts((x // y) % 65536)
        elif command[0] == '%':
            x, y = quack_vm.queue.gets(), quack_vm.queue.gets()
            if y == 0:
                quack_vm.queue.puts(0)
            else:
                quack_vm.queue.puts(x % y)
        elif command[0] == 'P':
            try:
                fout.write(f"{quack_vm.registers[ord(command[1]) % ord('a')]}\n")
            except IndexError:
                fout.write(f"{quack_vm.queue.gets()}\n")
        elif command[0] == 'C':
            try:
                val = quack_vm.registers[ord(command[1]) % ord('a')]
            except IndexError:
                val = quack_vm.queue.gets()
            fout.write(chr(val % 256))
        elif command[0] == '>':
            quack_vm.registers[ord(command[1]) % ord('a')] = quack_vm.queue.gets()
        elif command[0] == '<':
            quack_vm.queue.puts(quack_vm.registers[ord(command[1]) % ord('a')])
        elif command[0] == 'J':
            num_of_command = quack_vm.labels.get(command[1:])
            continue
        elif command[0] == 'Z':
            if quack_vm.registers[ord(command[1]) % ord('a')] == 0:
                num_of_command = quack_vm.labels.get(command[2:])
                continue
        elif command[0] == 'E':
            if quack_vm.registers[ord(command[1]) % ord('a')] == \
                    quack_vm.registers[ord(command[2]) % ord('a')]:
                num_of_command = quack_vm.labels.get(command[3:])
                continue
        elif command[0] == 'G':
            if quack_vm.registers[ord(command[1]) % ord('a')] > \
                    quack_vm.registers[ord(command[2]) % ord('a')]:
                num_of_command = quack_vm.labels.get(command[3:])
                continue
        elif command[0] == 'Q':
            break
        num_of_command += 1
    fin.close()
    fout.close()


if __name__ == "__main__":
    main()
