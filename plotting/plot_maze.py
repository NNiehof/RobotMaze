import os.path
import matplotlib.pyplot as plt

def plot_maze(maze, start=None, goal=None, save_as=None):
    """
    Plot a line maze.

    Args:
        maze (array): each element is a nested list with the tile type
            number of each tile in a row of the maze. The y-axis will be 
            inverted for plotting to retain the topography of the maze array.
        start (array, optional): Location of the start position, in row
            and columns indices of the maze. Will draw a triangle at the start 
            tile. Defaults to None.
        goal (array, optional): Location of the goal position, in row
            and columns indices of the maze. Will draw a square at the goal
            tile. Defaults to None.
        save_as (string, optional): File path to save the figure as image.
    """

    # line pieces in orientations north, east, south, west
    n = [[0.5, 0.5], [0.5, 1.0]]
    e = [[0.5, 1.0], [0.5, 0.5]]
    s = [[0.5, 0.5], [0.5, 0.0]]
    w = [[0.5, 0.0], [0.5, 0.5]]

    # all possible tiles
    tiles = {
        # dead ends
        0: [n],
        1: [e],
        2: [s],
        3: [w],
        # corners
        4: [n, e],
        5: [e, s],
        6: [s, w],
        7: [w, n],
        # straight + turn
        8: [n, e, s],
        9: [e, s, w],
        10: [s, w, n],
        11: [w, n, e],
        # straight
        12: [n, s],
        13: [e, w],
        # crossing
        14: [n, e, s, w],
        # empty tile
        15: []
    }

    ax = plt.subplot(1, 1, 1)

    # flip y-axis for plotting
    for y_offset, row in enumerate(reversed(maze)):
        for x_offset, tilenum in enumerate(row):
            # get tile layout
            tile = tiles[tilenum]
            for line in tile:
                # shift the line by the tile coordinates
                x = [x_val + x_offset for x_val in line[0]]
                y = [y_val + y_offset for y_val in line[1]]

                plt.plot(x, y, 'k-')

    # indicate maze start tile
    if start:
        # get a start triangle pointing in the starting direction
        start_tile = maze[start[0]][start[1]]
        if start_tile == 0:
            marker = "^"
        elif start_tile == 1:
            marker = ">"
        elif start_tile == 2:
            marker = "v"
        elif start_tile == 3:
            marker = "<"
        else:
            marker = "^"

        # flipped y-axis
        start_y = len(maze) - 1 - start[0] + 0.5
        start_x = start[1] + 0.5

        # plot triangle marker
        plt.plot(start_x, start_y, marker=marker, markersize=12, color='black', linestyle='None')

    # indicate maze goal tile
    if goal:
        # flipped y-axis
        goal_x = goal[1] + 0.5
        goal_y = len(maze) - 1 - goal[0] + 0.5

        # plot square marker
        plt.plot(goal_x, goal_y, marker='s', markersize=12, color='black', linestyle='None')

    ax.set_xlim(0.0, len(maze[0]))
    ax.set_ylim(0.0, len(maze))
    plt.gca().set_aspect('equal')
    plt.axis('off')
    plt.tight_layout()

    if save_as:
        plt.savefig(save_as)

    plt.show()

if __name__ == "__main__":
    maze = [
        [2, 1, 13, 13, 13, 9, 6, 5, 13, 3, 15],
        [12, 5, 13, 13, 13, 10, 12, 12, 5, 3, 15],
        [8, 11, 13, 9, 13, 7, 12, 12, 12, 15, 15],
        [4, 9, 13, 14, 13, 13, 11, 11, 10, 5, 6],
        [1, 11, 13, 11, 13, 13, 13, 3, 4, 11, 7]
    ]
    start = [4, 0]
    goal = [1, 9]

    root_path = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
    save_file = root_path + "/mazes/maze1.png"

    plot_maze(maze, start=start, goal=goal, save_as=save_file)