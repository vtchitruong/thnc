def ceiling_power_of_two(n):
    if n == 0:
        return 1

    n -= 1
    
    n |= n >> 1
    n |= n >> 2
    n |= n >> 4
    n |= n >> 8
    n |= n >> 16
    
    n += 1

    return n


if __name__ == '__main__':
    num = int(input('Nhập n: '))

    result = ceiling_power_of_two(num)
    print(f'Luỹ thừa của 2 nhỏ nhất mà lớn hơn hoặc bằng {num}: {result}')