#!/usr/bin/env python3
def tc():
    s = "abcde"
    ans = ["z"] * 5
    found = []

    # First loop to identify letters based on responses
    for iter in range(5):
        print(f"? {s}")
        resp = input().strip()  # Read response from input

        for i in range(5):
            if resp[i] != 'W':
                found.append(chr(ord('a') + iter * 5 + i))
        
        # Increment each character in `s` by 5
        s = ''.join(chr(ord(c) + 5) for c in s)

    # Second loop to refine answer based on found characters
    for i in range(min(len(found), 4)):
        print(f"? {found[i] * 5}")
        resp = input().strip()

        for j in range(5):
            if resp[j] != 'W':
                ans[j] = found[i]

    # If found has 5 elements, use the 5th element for any 'z' in ans
    if len(found) == 5:
        ans = [found[4] if ch == 'z' else ch for ch in ans]

    print(f"! {''.join(ans)}")

def main():
    t = int(input().strip())  # Number of test cases
    for _ in range(t):
        tc()

if __name__ == "__main__":
    main()
