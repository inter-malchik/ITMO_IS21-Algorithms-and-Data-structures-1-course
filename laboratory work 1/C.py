def turtle(matrix, H: int, W: int):
    generate_max = []
    for i in range(H):
        if i == 0:
            generate_max.append([matrix[0][0]] + [0] * (W - 1))
        else:
            generate_max.append([0] * W)
    for i in range(1, W):
        generate_max[0][i] = generate_max[0][i - 1] + matrix[0][i]
    for i in range(1, H):
        generate_max[i][0] = generate_max[i - 1][0] + matrix[i][0]
    for i in range(1, H):
        for j in range(1, W):
            generate_max[i][j] = max(generate_max[i][j - 1], generate_max[i - 1][j]) + matrix[i][j]
    return generate_max[H - 1][W - 1]


if __name__ == "__main__":
    file = open('turtle.in', 'r')
    height, width = map(int, file.readline().split())
    matrix = []
    for _ in range(height):
        matrix.append(list(map(int, file.readline().split())))
    file.close()
    result = turtle(matrix[::-1], height, width)
    file = open('turtle.out', 'w')
    file.write(f'{result}')
    file.close()
