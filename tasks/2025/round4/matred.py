#!/usr/bin/env python3
# // @check-accepted: *
import sys

a = None


def doop(op):
    """
    Apply an update operation to the global matrix a.
    op is a tuple (x1, x2, y1, y2, val).
    The operation adds op[4] to every cell a[i][j] for i in [x1,x2] and j in [y1,y2].
    """
    x1, x2, y1, y2, val = op
    for i in range(x1, x2 + 1):
        for j in range(y1, y2 + 1):
            a[i][j] += val


def main():
    global a
    n, m = map(int, input().split())

    # Allocate a as a (n+1) x (m+1) matrix (using 1-indexing).
    a = [[0] * (m + 1) for _ in range(n + 1)]

    # s[0] and s[1] are 3-element lists.
    s = [[0, 0, 0], [0, 0, 0]]

    # Read the matrix and update the two checksum arrays.
    # (The original code uses indices 1..n and 1..m.)
    for i in range(1, n + 1):
        row = list(map(int, input().split()))
        for j in range(1, m + 1):
            a[i][j] = row[j - 1]
            s[0][(i + j) % 3] += a[i][j]
            s[1][(i + 2 * j) % 3] += a[i][j]

    # Check the necessary condition.
    for j in range(3):
        if s[0][j] != s[0][(j + 1) % 3] or s[1][j] != s[1][(j + 1) % 3]:
            print("NO")
            return

    # List of operations (each op is a tuple: (x1, x2, y1, y2, val)).
    v = []

    # Process rows 1 to n-3.
    # (Note: the loop in C++ is: for (i = 1; i <= n-3; i++). In Python, use range(1, n-2) since range’s end is exclusive.)
    for i in range(1, n - 2):
        # Find the maximum in row i.
        maxi = 0
        for j in range(1, m + 1):
            maxi = max(maxi, a[i][j])
        maxi += 1

        # For every column j, bring a[i][j] up to (maxi) by adding (maxi - a[i][j])
        for j in range(1, m + 1):
            op = (i, i + 2, j, j, maxi - a[i][j])
            doop(op)
            v.append(op)

        # For every block of 3 columns, do two operations.
        for j in range(1, m - 1, 3):
            # Subtract maxi from the entire triple in row i.
            op = (i, i, j, j + 2, -maxi)
            doop(op)
            v.append(op)
            # Determine the minimum value among the three cells in row i+1.
            val = 10 ** 17  # A large number (1e17)
            for k in range(j, j + 3):
                val = min(val, a[i + 1][k])
            # Subtract that minimum from the triple in row i+1.
            op = (i + 1, i + 1, j, j + 2, -val)
            doop(op)
            v.append(op)

        # If the number of columns is not a multiple of 3, do two more steps.
        if m % 3 != 0:
            # Step 1: For the last few columns, add maxi to each of the cells in rows i to i+2.
            # Loop: for (j = m-m%3; j > m-3; j--)
            for j in range(m - (m % 3), m - 3, -1):
                op = (i, i + 2, j, j, maxi)
                doop(op)
                v.append(op)
            # Step 2: Subtract maxi from the first two cells of the last triple.
            op = (i, i, m - 2, m, -maxi)
            doop(op)
            v.append(op)

    # Now, only the last 3 rows (rows n-2, n-1, n) may be nonzero.
    # Process columns 1 to m-2.
    for col in range(1, m - 1):
        maxi = 0
        for i in range(n - 2, n + 1):
            maxi = max(maxi, a[i][col])
        maxi += 1
        # For each of the last three rows, adjust the triple (columns col, col+1, col+2).
        for i in range(n - 2, n + 1):
            op = (i, i, col, col + 2, maxi - a[i][col])
            doop(op)
            v.append(op)
        # Then subtract maxi from the triple in the first column of these groups.
        op = (n - 2, n, col, col, -maxi)
        doop(op)
        v.append(op)

    # Finally, perform two operations to cancel out the remaining nonzero values.
    op = (n - 2, n, m - 1, m - 1, -a[n - 2][m - 1])
    doop(op)
    v.append(op)
    op = (n - 2, n, m, m, -a[n - 2][m])
    doop(op)
    v.append(op)

    print("YES")
    print(len(v))
    for op in v:
        print(op[0], op[2], op[1], op[3], op[4])


if __name__ == '__main__':
    main()
