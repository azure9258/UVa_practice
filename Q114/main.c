/*
method : build cost, value 2D array first (including walls), if hitting obstacle then use it directly
Last modified : 2014/05/24
*/
#include <stdio.h>
#include <string.h>

struct bumper
{
    int value, cost;
};
struct direction
{
    int x, y;
};

int main()
{
    int i, j, k; /* for loop */
    int grid_x, grid_y; /* x, y-coordinate */
    int num_bumper; /* numbers of bumpers */
    int cost_wall; /* the cost of hitting a wall */
    int lifetime; /* lifetime of ball */
    int dir_now;
    struct bumper bumpers[51][51];
    int surface[51][51];
    int x, y, value, cost; /* input */
    struct direction dir[4];
    int score = 0, sum_score = 0;

    /* freopen("input.txt", "r", stdin); */

    memset(surface, 0, sizeof(surface));
    dir[0].x = 1;
    dir[0].y = 0;
    dir[1].x = 0;
    dir[1].y = 1;
    dir[2].x = -1;
    dir[2].y = 0;
    dir[3].x = 0;
    dir[3].y = -1;
    scanf("%d %d %d %d", &grid_x, &grid_y, &cost_wall, &num_bumper);
    /* printf("%d %d %d %d", grid_x, grid_y, cost_wall, num_bumper); */

    for(i=1;i<=grid_x;i++)
    {
        surface[i][1] = 1;
        surface[1][i] = 1;
        surface[grid_x][i] = 1;
        surface[i][grid_y] = 1;
        bumpers[i][1].cost = cost_wall;
        bumpers[1][i].cost = cost_wall;
        bumpers[grid_x][i].cost = cost_wall;
        bumpers[i][grid_y].cost = cost_wall;
        bumpers[i][1].value = 0;
        bumpers[1][i].value = 0;
        bumpers[grid_x][i].value = 0;
        bumpers[i][grid_y].value = 0;
    }

    for(i=0;i<num_bumper;i++)
    {
        scanf("%d %d %d %d", &x, &y, &value, &cost);
        surface[x][y] = 1;
        bumpers[x][y].value = value;
        bumpers[x][y].cost = cost;
    }

    while(scanf("%d %d %d %d", &x, &y, &dir_now, &lifetime) == 4)
    {
        score = 0;
        lifetime--;
        while(lifetime > 0)
        {
            lifetime--;
            x += dir[dir_now].x;
            y += dir[dir_now].y;
            if(surface[x][y] == 1)
            {
                lifetime -= bumpers[x][y].cost;
                score += bumpers[x][y].value;
                x -= dir[dir_now].x;
                y -= dir[dir_now].y;
                dir_now = (dir_now + 3) % 4; /* turn right */
            }
        }
        printf("%d\n", score);
        sum_score += score;
    }
    printf("%d\n", sum_score);

    return 0;
}
