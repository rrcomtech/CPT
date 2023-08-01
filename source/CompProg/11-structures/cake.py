import math

def build_segment_tree(arr, tree, start, end, node):
    if start == end:
        tree[node] = arr[start]
        return

    mid = (start + end) // 2
    left_node = 2 * node + 1
    right_node = 2 * node + 2

    build_segment_tree(arr, tree, start, mid, left_node)
    build_segment_tree(arr, tree, mid + 1, end, right_node)

    tree[node] = math.gcd(tree[left_node], tree[right_node])

def query_segment_tree(tree, start, end, node, left, right):
    print(f"query recursing ({start},{end})")
    if start > right or end < left:  # No overlap
        return 0

    if left <= start and right >= end:  # Complete overlap
        return tree[node]

    mid = (start + end) // 2
    left_gcd = query_segment_tree(tree, start, mid, 2 * node + 1, left, right)
    right_gcd = query_segment_tree(tree, mid + 1, end, 2 * node + 2, left, right)

    return math.gcd(left_gcd, right_gcd)

def update_segment_tree(arr, tree, start, end, node, index, new_val):
    print(f"update recursing ({start}, {end})")
    if start == end:
        arr[index] = new_val
        tree[node] = new_val
        return

    mid = (start + end) // 2
    left_node = 2 * node + 1
    right_node = 2 * node + 2

    if index <= mid:
        update_segment_tree(arr, tree, start, mid, left_node, index, new_val)
    else:
        update_segment_tree(arr, tree, mid + 1, end, right_node, index, new_val)

    tree[node] = math.gcd(tree[left_node], tree[right_node])

def build_gcd_segment_tree(arr):
    n = len(arr)
    tree = [0] * (4 * n)
    build_segment_tree(arr, tree, 0, n - 1, 0)
    return tree

n, q = [int(x) for x in input().split(" ")]
arr = [int(x) for x in input().split(" ")]

segment_tree = build_gcd_segment_tree(arr)

for _ in range(0, q):
    query = input()
    if query.startswith("?"):
        type, temp_left, temp_right = query.split(" ")
        left = int(temp_left) - 1
        right = int(temp_right) - 1
        result = query_segment_tree(segment_tree, 0, len(arr) - 1, 0, left, right)
        print(result)

    else:
        type, name, temp_index, temp_val = query.split(" ")

        index = int(temp_index) - 1
        new_val = arr[index] - int(temp_val)

        update_segment_tree(arr, segment_tree, 0, len(arr) - 1, 0, index, new_val)
