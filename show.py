import matplotlib.pyplot as plt

# ---------------------------------
# 1️⃣ 좌표 데이터 불러오기
# ---------------------------------
vertices = []
with open('tsp/mona-lisa100K.tsp', 'r') as f:
    lines = f.readlines()

start_idx = next(i for i, line in enumerate(lines) if line.strip() == 'NODE_COORD_SECTION') + 1
for line in lines[start_idx:]:
    if line.strip() == 'EOF':
        break
    parts = line.split()
    if len(parts) == 3:
        _, x, y = parts
        vertices.append((int(x), int(y)))

# ---------------------------------
# 2️⃣ 경로(+마킹) 데이터 불러오기 (1-based → 0-based)
# ---------------------------------
path = []
marked = []
with open('/Users/jojaemin/Desktop/UNIST/2025 1학기/알고리즘/Homework_2/result_path/mona-lisa100K_myalgo_path_marking', 'r') as f:
    for line in f:
        parts = line.strip().split()
        if not parts:
            continue
        idx = int(parts[0])
        is_marked = (len(parts) > 1 and parts[1] == 'c')
        path.append(idx)
        marked.append(is_marked)

print(f'불러온 경로 길이: {len(path)} / 마킹된 점 개수: {sum(marked)}')

# ---------------------------------
# 3️⃣ 시각화: 구간별로 색 구분
# ---------------------------------
plt.figure(figsize=(10, 8))

for i in range(len(path) - 1):
    x1, y1 = vertices[path[i]]
    x2, y2 = vertices[path[i+1]]
    # 양쪽이 모두 마킹된 구간만 빨간색, 나머지는 파란색
    color = 'r' if marked[i] and marked[i+1] else 'b'
    plt.plot([x1, x2], [y1, y2], color=color, linewidth=1)

# # (선택) 마킹된 점 강조
# mx = [vertices[p][0] for p, m in zip(path, marked) if m]
# my = [vertices[p][1] for p, m in zip(path, marked) if m]
# plt.scatter(mx, my, c='r', s=10, label='marked')

plt.title('TSP MYALGORITHM (marked segments in red)')
plt.xlabel('X')
plt.ylabel('Y')
plt.legend()
plt.grid(True)
plt.show()
