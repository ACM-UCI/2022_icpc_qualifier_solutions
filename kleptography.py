N,M = map(int, input().rstrip().split())

recovered = [ord(c)-ord('a') for c in input().rstrip()[::-1]]
ciphertext = [ord(c)-ord('a') for c in input().rstrip()[::-1]]

ans = ''
for i in range(M):
    ans += chr(recovered[i] + ord('a'))
    recovered.append((ciphertext[i] - recovered[i]) % 26)

print(ans[::-1])
