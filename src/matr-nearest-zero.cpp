/*
    Given a matrix consists of 0 and 1, find the distance of the nearest 0 for each cell.
    The distance between two adjacent cells is 1.

    Example 1:

        Input:
            [[0,0,0],
             [0,1,0],
             [0,0,0]]

        Output:
            [[0,0,0],
             [0,1,0],
             [0,0,0]]

    Example 2:

        Input:
            [[0,0,0],
             [0,1,0],
             [1,1,1]]

        Output:
            [[0,0,0],
             [0,1,0],
             [1,2,1]]

    Note:
        The number of elements of the given matrix will not exceed 10,000.
        There are at least one 0 in the given matrix.
        The cells are adjacent in only four directions: up, down, left and right.
*/

#include <vector>
#include <list>
#include <queue>
#include <tuple>
#include <algorithm>
#include <limits>

#include <iostream>
#include <ostream>

using namespace std;

using visited_t = vector<vector<bool>>;
using matrix_t = vector<vector<int>>;

visited_t newVisitedMatrix(const matrix_t& matrix, size_t i, size_t j) 
{
    visited_t visited(matrix.size(), vector<bool>(matrix[0].size(), false));

    visited[i][j] = true;

    return visited;
}        

size_t findDistanceToZero(
    const matrix_t& matrix, 
    visited_t& visited, 
    size_t i, size_t j)
{
    constexpr size_t INF = 1<<20;//numeric_limits<size_t>::max();
    
    if (i >= matrix.size() || j >= matrix[0].size())
    {
        return INF;
    }

    if (matrix[i][j] == 0)
    {
        return 0;
    }

    visited[i][j] = true;

    size_t dist_right = 0; 
    size_t dist_left = 0; 
    size_t dist_up = 0; 
    size_t dist_down = 0; 

    if (i < matrix.size() - 1 && !visited[i+1][j]) 
        dist_right = findDistanceToZero(matrix, visited, i + 1, j);
    else
        dist_right = INF;

    if (i > 0 && !visited[i-1][j]) 
        dist_left = findDistanceToZero(matrix, visited, i - 1, j);
    else
        dist_left = INF;

    if (j > 0 && !visited[i][j-1]) 
        dist_up = findDistanceToZero(matrix, visited, i, j - 1);
    else
        dist_up = INF;

    if (j < matrix[0].size() - 1 && !visited[i][j+1]) 
        dist_down = findDistanceToZero(matrix, visited, i, j + 1);        
    else
        dist_down = INF;

    visited[i][j] = false;

    return 1 + min(min(dist_right, dist_left), min(dist_up, dist_down));
}

matrix_t updateMatrixBruteForce(const matrix_t& matrix) 
{
    matrix_t distance(matrix.size(), vector<int>(matrix[0].size(), 0));

    for (size_t i = 0; i < matrix.size(); ++i)
    {
        for (size_t j = 0; j < matrix[0].size(); ++j)
        {
            if (matrix[i][j] != 0)
            {
                auto visited = newVisitedMatrix(matrix, i, j);
                distance[i][j] = findDistanceToZero(matrix, visited, i, j);
            }
        }            
    }

    return distance;
}

matrix_t updateMatrixPreprocess(const matrix_t& matrix) 
{
    matrix_t distance(matrix.size(), vector<int>(matrix[0].size(), 0));

    list<tuple<size_t, size_t>> zeros;

    for (size_t i = 0; i < matrix.size(); ++i)
    {
        for (size_t j = 0; j < matrix[0].size(); ++j)
        {
            if (matrix[i][j] == 0)
            {
                zeros.push_back({i, j});
            }
        }            
    }
    
    for (size_t i = 0; i < matrix.size(); ++i)
    {
        for (size_t j = 0; j < matrix[0].size(); ++j)
        {
            if (matrix[i][j] != 0)
            {
                size_t nearest = 40000;
                
                for (const auto& [k, l] : zeros)
                {
                    nearest = min(nearest, (size_t)(abs((int)i-(int)k) + abs((int)j-(int)l)));
                }
                
                distance[i][j] = nearest;
            }
        }            
    }        

    return distance;
}    

matrix_t updateMatrixBFS(const matrix_t& matrix) 
{    
    matrix_t distance(matrix.size(), vector<int>(matrix[0].size(), 0));

    for (size_t i = 0; i < matrix.size(); ++i)
    {
        for (size_t j = 0; j < matrix[0].size(); ++j)
        {
            if (matrix[i][j] != 0)
            {
                list<tuple<size_t, size_t>> bfs;
                auto                        visited = newVisitedMatrix(matrix, i, j);

                bfs.push_back({i, j});

                while (!bfs.empty())
                {
                    const auto [k, l] = bfs.front();

                    bfs.pop_front();

                    if (matrix[k][l] == 0)
                    {
                        distance[i][j] = abs((int)k-(int)i) + abs((int)l-(int)j);
                        break;
                    }

                    visited[k][l] = 1;

                    if (k > 0 && !visited[k-1][l]) bfs.push_back({k-1, l});
                    if (l > 0 && !visited[k][l-1]) bfs.push_back({k, l-1});

                    if (l < matrix[0].size() - 1 && !visited[k][l+1]) bfs.push_back({k, l+1});
                    if (k < matrix[0].size() - 1 && !visited[k+1][l]) bfs.push_back({k+1, l});
                }
            }
        }            
    }        

    return distance;
}    

matrix_t updateMatrixBFS2(const matrix_t& matrix)
{
    int rows = matrix.size();

    if (rows == 0)
        return matrix;

    int cols = matrix[0].size();

    // For non-zero elements the duistance is set to INFINITY

    matrix_t dist(rows, vector<int>(cols, numeric_limits<int>::max()));

    queue<pair<int, int>> q;

    // For zero-valued elements, the distance is set to 0,
    // and these elements go into the queue

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (matrix[i][j] == 0) 
            {
                dist[i][j] = 0;
                q.push({ i, j });
            }
        }
    }

    int dir[4][2] = { { -1, 0 }, { 1, 0 }, { 0, -1 }, { 0, 1 } };

    while (!q.empty()) 
    {
        const auto [k, l] = q.front();
        q.pop();

        for (int i = 0; i < 4; i++) 
        {
            int new_r = k + dir[i][0];
            int new_c = l + dir[i][1];

            if (new_r >= 0 && new_c >= 0 && new_r < rows && new_c < cols) 
            {
                if (dist[new_r][new_c] > dist[k][l] + 1) 
                {
                    dist[new_r][new_c] = dist[k][l] + 1;
                    
                    q.push({ new_r, new_c });
                }
            }
        }
    }

    return dist;
}

matrix_t updateMatrixDP(const matrix_t& matrix)
{
    int rows = matrix.size();

    if (rows == 0)
        return matrix;

    int cols = matrix[0].size();

    matrix_t dist(rows, vector<int>(cols, 8888888)); // Initialize distances to INFINITY

    // First pass: check for left and top

    for (int i = 0; i < rows; i++) 
    {
        for (int j = 0; j < cols; j++) 
        {
            if (matrix[i][j] == 0) 
            {
                dist[i][j] = 0;
            }
            else 
            {
                if (i > 0) dist[i][j] = min(dist[i][j], dist[i - 1][j] + 1);
                if (j > 0) dist[i][j] = min(dist[i][j], dist[i][j - 1] + 1);
            }
        }
    }

    // Second pass: check for bottom and right

    for (int i = rows - 1; i >= 0; i--) 
    {
        for (int j = cols - 1; j >= 0; j--) 
        {
            if (i < rows - 1) dist[i][j] = min(dist[i][j], dist[i + 1][j] + 1);
            if (j < cols - 1) dist[i][j] = min(dist[i][j], dist[i][j + 1] + 1);
        }
    }

    return dist;
}

ostream& operator << (ostream& ostr, vector<vector<int>> matr)
{
    ostr << "[";
    for (const auto& row : matr)
    {
        ostr << "[";
        for (const auto& item : row)
        {
            ostr << item << ",";
        }
        ostr << "]";        
    }
    ostr << "]";

    return ostr;
}

int main()
{
    vector<vector<int>> matrix;

    matrix.push_back({0,0,0});
    matrix.push_back({0,1,0});
    matrix.push_back({1,1,1});

    cout << "Distance BFS: " << updateMatrixBFS(matrix) << endl;
    cout << "Distance BFS2: " << updateMatrixBFS2(matrix) << endl;
    cout << "Distance DP: " << updateMatrixDP(matrix) << endl;
    cout << "Distance Preprocess: " << updateMatrixPreprocess(matrix) << endl;
    cout << "Distance Brute Force: " << updateMatrixBruteForce(matrix) << endl;
}
