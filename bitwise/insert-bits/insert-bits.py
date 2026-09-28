def insert_bits(n, m, start, end) -> int:
    # Tạo chuỗi bit 1 nằm bên trái của start
    left = ~0 << (start + 1)

    # Tạo chuỗi bit 1 nằm bên phải của end
    right = (1 << end) - 1

    # Tạo mặt nạ để che hai bên của start và end, đồng thời để hở khoảng giữa từ start đến end
    mask = left | right

    # Áp mặt nạ vào n để "xóa" các bit ở vị trí từ start đến end
    n_cleared = n & mask

    # Dịch chuyển các bit của m sang trái end bước để khớp với đoạn cần chèn trong n
    m_shifted = m << end

    # Chèn m vô n
    return n_cleared | m_shifted


if __name__ == '__main__':
    n = 0b1010101010101010
    m = 0b10011

    # Formatting integer to 16-bit binary string
    print(f'n = {n:016b}')
    print(f'm = {m:016b}')

    start = 6
    end = 2

    res = insert_bits(n, m, start, end)

    # Chuyển bit thành chuỗi 16 bit
    bits = f'{res:016b}'

    # Định dạng lại để dễ quan sát khi in ra
    part1 = bits[: 15 - start]
    part2 = bits[15 - start : 15 - end + 1]
    part3 = bits[15 - end + 1 :]

    formatted = f'{part1} {part2} {part3}'

    print(f'Sau khi chèn m vô n: {formatted}')