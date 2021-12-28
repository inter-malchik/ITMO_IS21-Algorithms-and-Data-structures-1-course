class Node:
    def __init__(self, key, left=None, right=None):
        self.key = key
        self.left = left
        self.right = right


class BinarySearchTree:
    def __init__(self):
        self.root = None

    def add(self, key):
        if not self.root:
            self.root = Node(key)
        else:
            self.insert(key, self.root)

    def insert(self, new_key, current):
        if new_key > current.key:
            if current.right:
                self.insert(new_key, current.right)
            else:
                current.right = Node(new_key)
        elif new_key < current.key:
            if current.left:
                self.insert(new_key, current.left)
            else:
                current.left = Node(new_key)

    def delete(self, key):
        if not self.root:
            return
        self.root = self.deleted(key, self.root)

    def deleted(self, our_key, root):
        if not root:
            return None
        if root.key > our_key:
            root.left = self.deleted(our_key, root.left)
        elif root.key < our_key:
            root.right = self.deleted(our_key, root.right)
        elif not root.left and not root.right:
            return None
        elif root.left and root.right:
            root.key = self.successor(root.key, root).key
            root.right = self.deleted(root.key, root.right)
        else:
            if root.left:
                return root.left
            else:
                return root.right
        return root

    def exists(self, key, root):
        if not root:
            return False
        while True:
            if key == root.key:
                return True
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

    def successor(self, our_key, current):
        answer = None
        while current:
            if our_key >= current.key:
                current = current.right
            else:
                answer, current = current, current.left
        return answer

    def predecessor(self, our_key, current):
        answer = None
        while current:
            if our_key <= current.key:
                current = current.left
            else:
                answer, current = current, current.right
        return answer


def main():
    our_binary_search_tree = BinarySearchTree()
    fin, fout = open("bstsimple.in", 'r'), open("bstsimple.out", 'w')
    for command in fin.read().split('\n'):
        if not command:
            continue
        identificator, argument = command.split()
        argument = int(argument)
        if identificator == "insert":
            our_binary_search_tree.add(argument)
        elif identificator == "delete":
            our_binary_search_tree.delete(argument)
        elif identificator == "exists":
            if our_binary_search_tree.exists(argument, our_binary_search_tree.root):
                fout.write("true")
            else:
                fout.write("false")
            fout.write('\n')
        elif identificator == "next":
            output_answer = our_binary_search_tree.successor(argument, our_binary_search_tree.root)
            if output_answer:
                fout.write(f"{output_answer.key}")
            else:
                fout.write("none")
            fout.write('\n')
        elif identificator == "prev":
            output_answer = our_binary_search_tree.predecessor(argument, our_binary_search_tree.root)
            if output_answer:
                fout.write(f"{output_answer.key}")
            else:
                fout.write("none")
            fout.write('\n')
    fin.close()
    fout.close()


if __name__ == "__main__":
    main()
