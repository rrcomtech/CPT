def can_leave_dungeon(situations):
    for situation in situations:
        w, h, p = situation['dimensions']
        party_positions = situation['party_positions']

        # Create a graph representation of the dungeon
        dungeon = [[0] * w for _ in range(h)]
        for x, y in party_positions:
            dungeon[y-1][x-1] = 1

        # Perform a graph traversal from each party member's position
        for i, (x, y) in enumerate(party_positions):
            visited = [[False] * w for _ in range(h)]
            queue = [(x-1, y-1)]
            while queue:
                curr_x, curr_y = queue.pop(0)
                visited[curr_y][curr_x] = True

                # Check if current position is at the dungeon's edge
                if curr_x == 0 or curr_x == w-1 or curr_y == 0 or curr_y == h-1:
                    break

                # Add adjacent rooms to the queue
                if curr_x > 0 and not visited[curr_y][curr_x-1]:
                    queue.append((curr_x-1, curr_y))
                if curr_x < w-1 and not visited[curr_y][curr_x+1]:
                    queue.append((curr_x+1, curr_y))
                if curr_y > 0 and not visited[curr_y-1][curr_x]:
                    queue.append((curr_x, curr_y-1))
                if curr_y < h-1 and not visited[curr_y+1][curr_x]:
                    queue.append((curr_x, curr_y+1))
            else:
                # If the traversal ended without reaching the edge, it's not possible
                print("NO")
                break
        else:
            # If all traversals reached the edge, it's possible
            print("YES")

# Example usage
situations = [
    {
        'dimensions': (3, 4, 5),
        'party_positions': [(1, 4), (2, 2), (2, 3), (2, 4), (3, 3)]
    },
    {
        'dimensions': (5, 5, 5),
        'party_positions': [(3, 2), (2, 3), (3, 3), (4, 3), (3, 4)]
    }
]

can_leave_dungeon(situations)
