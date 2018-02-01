n = int(raw_input())
nums = map(int, raw_input().split())
aux = {}

for v in nums:
        aux[v] = 0

ans = 0
sum = 0
for i in range(n):
        sum += nums[i]
        aux[nums[i]] += 1
        x = sum - aux[nums[i]] * nums[i]
        y = i + 1 - aux[nums[i]]
        if (nums[i]-1) in aux:
                x -= aux[nums[i]-1] * (nums[i]-1)
                y -= aux[nums[i]-1]
        if (nums[i]+1) in aux:
                x -= aux[nums[i]+1] * (nums[i]+1)
                y -= aux[nums[i]+1]
        ans += y*nums[i] - x

print ans
