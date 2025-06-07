import matplotlib.pyplot as plt

# ---------------------------------
# 1️⃣ 좌표 데이터 불러오기
# ---------------------------------
vertices = []

with open('tsp/mona-lisa100K.tsp', 'r') as f:
    lines = f.readlines()

# 'NODE_COORD_SECTION' 이후부터 데이터 시작
start_idx = 0
for idx, line in enumerate(lines):
    if line.strip() == 'NODE_COORD_SECTION':
        start_idx = idx + 1
        break

# EOF 제외하고 데이터 읽기
for line in lines[start_idx:]:
    if line.strip() == 'EOF':
        break
    parts = line.strip().split()
    if len(parts) == 3:
        _, x, y = parts
        vertices.append( (int(x), int(y)) )

print(f'불러온 좌표 개수: {len(vertices)}')

# ---------------------------------
# 2️⃣ 경로(순회 경로) 데이터 불러오기
# ---------------------------------
with open('/Users/jojaemin/Desktop/UNIST/2025 1학기/알고리즘/Homework_2/result_path/mona-lisa100K_myalgo_path', 'r') as f:
    path_lines = f.readlines()

# 경로 데이터는 1-based → 0-based로 변환
path = [int(line.strip()) for line in path_lines]

print(f'불러온 경로 길이: {len(path)}')

# ---------------------------------
# 3️⃣ 경로 좌표 추출
# ---------------------------------
path_x = [vertices[i][0] for i in path]
path_y = [vertices[i][1] for i in path]

# ---------------------------------
# 4️⃣ 시각화
# ---------------------------------
plt.figure(figsize=(10, 8))
plt.plot(path_x, path_y, linestyle='-', color='b', linewidth=1)  # marker 제거
plt.title('TSP MYALGORITHM')
plt.xlabel('X')
plt.ylabel('Y')
plt.grid(True)
plt.show()