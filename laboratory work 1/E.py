f = open('sortland.in', 'r')
N = int(f.readline())
people = []
for number, price in enumerate(f.readline().split()):
    people.append((float(price), number + 1))
f.close()
for i in range(N):
    for j in range(N - i - 1):
        if people[j][0] > people[j + 1][0]:
            people[j], people[j + 1] = people[j + 1], people[j]
f = open('sortland.out', 'w')
f.write(f'{people[0][1]} {people[N // 2][1]} {people[-1][1]}')
f.close()
