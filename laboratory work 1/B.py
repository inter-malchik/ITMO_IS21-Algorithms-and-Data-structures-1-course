f = open('aplusbb.in', 'r')
a, b = map(int, f.readline().split())
f.close()
answer = a + b * b
f = open('aplusbb.out', 'w')
f.write(f'{answer}')
f.close()
