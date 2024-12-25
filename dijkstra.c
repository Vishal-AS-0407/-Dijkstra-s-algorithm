#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

#define INF 6969
#define MAX_NODES 20

void printGraph(double cost[MAX_NODES][MAX_NODES], int nodes) {
    printf("\nAdjacency Matrix:\n");
    
    // Print column headers
    printf("    ");
    for (int i = 1; i <= nodes; i++) {
        printf("%-7d", i);
    }
    printf("\n");
    
    // Print separator line
    printf("    ");
    for (int i = 0; i < nodes; i++) {
        printf("-------");
    }
    printf("\n");
    
    // Print matrix with row headers
    for (int i = 0; i < nodes; i++) {
        printf("%-3d |", i + 1);
        for (int j = 0; j < nodes; j++) {
            if (cost[i][j] == INF) {
                printf(" ∞     ");
            } else {
                printf(" %-6.2f", cost[i][j]);
            }
        }
        printf("\n");
    }
    printf("\n");
}



// Function prototypes
void printGraph(double cost[MAX_NODES][MAX_NODES], int nodes);
void dijkstra(double cost[MAX_NODES][MAX_NODES], int source, int target, int nodes);
void exportToHTML(double cost[MAX_NODES][MAX_NODES], int nodes, int *path, int pathLength);
bool validateInput(int value, int min, int max, const char* errorMsg);

int main() {
    int nodes, i, j;
    int source, target;

    printf("\t DIJKSTRA'S SHORTEST PATH FINDER ALGORITHM in C \n\n");
    printf("Please use the value %d to enter infinity!!\n", INF);

    printf("Enter the number of nodes in the graph (up to %d): ", MAX_NODES);
    if (!validateInput(scanf("%d", &nodes), 1, MAX_NODES, "Invalid number of nodes")) {
        return EXIT_FAILURE;
    }

    double cost[MAX_NODES][MAX_NODES];

    // Initialize cost matrix with infinity
    for (i = 0; i < nodes; i++) {
        for (j = 0; j < nodes; j++) {
            cost[i][j] = (i == j) ? 0 : INF;
        }
    }

    // Input edge weights
    for (i = 0; i < nodes - 1; i++) {
        for (j = i + 1; j < nodes; j++) {
            double weight;
            printf("Enter the weight of the path between nodes %d and %d (or %d for no path): ", 
                   i + 1, j + 1, INF);
            
            if (scanf("%lf", &weight) != 1) {
                printf("Invalid input. Weight should be a valid decimal value.\n");
                return EXIT_FAILURE;
            }

            if (weight < 0) {
                printf("Invalid input. Path weight cannot be negative.\n");
                j--;
                continue;
            }

            cost[i][j] = cost[j][i] = weight;
        }
        printf("\n");
    }

    printGraph(cost, nodes);

    printf("\nEnter the source node (1-%d): ", nodes);
    if (!validateInput(scanf("%d", &source), 1, nodes, "Invalid source node")) {
        return EXIT_FAILURE;
    }

    printf("Enter the target node (1-%d): ", nodes);
    if (!validateInput(scanf("%d", &target), 1, nodes, "Invalid target node")) {
        return EXIT_FAILURE;
    }

    dijkstra(cost, source, target, nodes);

    return EXIT_SUCCESS;
}

bool validateInput(int value, int min, int max, const char* errorMsg) {
    if (value < min || value > max) {
        printf("%s. Value should be between %d and %d.\n", errorMsg, min, max);
        return false;
    }
    return true;
}

void dijkstra(double cost[MAX_NODES][MAX_NODES], int source, int target, int nodes) {
    double dist[MAX_NODES];
    int prev[MAX_NODES];
    bool visited[MAX_NODES] = {false};
    
    // Initialize distances
    for (int i = 0; i < nodes; i++) {
        dist[i] = INF;
        prev[i] = -1;
    }

    dist[source - 1] = 0;

    // Main algorithm loop
    for (int count = 0; count < nodes - 1; count++) {
        double min = INF;
        int minIndex = -1;

        // Find vertex with minimum distance
        for (int v = 0; v < nodes; v++) {
            if (!visited[v] && dist[v] < min) {
                min = dist[v];
                minIndex = v;
            }
        }

        if (minIndex == -1) break; // No path exists
        
        visited[minIndex] = true;

        // Update distances of adjacent vertices
        for (int v = 0; v < nodes; v++) {
            if (!visited[v] && 
                cost[minIndex][v] != INF && 
                dist[minIndex] != INF && 
                dist[minIndex] + cost[minIndex][v] < dist[v]) {
                dist[v] = dist[minIndex] + cost[minIndex][v];
                prev[v] = minIndex;
            }
        }
    }

    // Reconstruct and print path
    if (dist[target - 1] == INF) {
        printf("\nNo path exists between nodes %d and %d\n", source, target);
        return;
    }

    int path[MAX_NODES];
    int pathLength = 0;
    int current = target - 1;

    while (current != -1) {
        path[pathLength++] = current + 1;
        current = prev[current];
    }

    printf("\nShortest path from %d to %d:\n", source, target);
    for (int i = pathLength - 1; i >= 0; i--) {
        printf("%d", path[i]);
        if (i > 0) printf(" -> ");
    }
    printf("\nTotal distance: %.2f\n", dist[target - 1]);

    exportToHTML(cost, nodes, path, pathLength);
}



void exportToHTML(double cost[MAX_NODES][MAX_NODES], int nodes, int *path, int pathLength) {
    FILE *file = fopen("./dijkstra_result.html", "w");
    if (!file) {
        printf("Error: Could not create HTML file.\n");
        return;
    }

    // Previous style definitions remain the same until the table cell styling
    fprintf(file, "<!DOCTYPE html>\n"
                  "<html lang=\"en\">\n"
                  "<head>\n"
                  "<meta charset=\"UTF-8\">\n"
                  "<title>Dijkstra Path Visualization</title>\n"
                  "<style>\n"
                  "body {\n"
                  "    font-family: 'Segoe UI', Arial, sans-serif;\n"
                  "    margin: 0;\n"
                  "    padding: 20px;\n"
                  "    min-height: 100vh;\n"
                  "    background: linear-gradient(135deg, #6DD5FA, #2980B9, #1e3c72);\n"
                  "    color: #333;\n"
                  "}\n"
                  ".container {\n"
                  "    max-width: 1200px;\n"
                  "    margin: 0 auto;\n"
                  "    background: rgba(255, 255, 255, 0.95);\n"
                  "    border-radius: 15px;\n"
                  "    padding: 30px;\n"
                  "    box-shadow: 0 10px 20px rgba(0, 0, 0, 0.2);\n"
                  "}\n"
                  "h1, h2 {\n"
                  "    color: #2c3e50;\n"
                  "    text-align: center;\n"
                  "    margin-bottom: 30px;\n"
                  "}\n"
                  "table {\n"
                  "    border-collapse: separate;\n"
                  "    border-spacing: 4px;\n"
                  "    margin: 20px auto;\n"
                  "    background: white;\n"
                  "    border-radius: 8px;\n"
                  "    overflow: hidden;\n"
                  "}\n"
                  "td {\n"
                  "    border: none;\n"
                  "    width: 60px;\n"
                  "    height: 60px;\n"
                  "    text-align: center;\n"
                  "    background: #f5f6fa;\n"
                  "    transition: all 0.3s ease;\n"
                  "    border-radius: 4px;\n"
                  "    font-size: 14px;\n"
                  "}\n"
                  ".infinity {\n"
                  "    color: #999;\n"
                  "    font-style: italic;\n"
                  "}\n"
                  ".no-path {\n"
                  "    color: #ccc;\n"
                  "}\n"
                  "td:first-child {\n"
                  "    background: #2980B9;\n"
                  "    color: white;\n"
                  "    font-weight: bold;\n"
                  "}\n"
                  "tr:first-child td {\n"
                  "    background: #2980B9;\n"
                  "    color: white;\n"
                  "    font-weight: bold;\n"
                  "}\n"
                  ".path {\n"
                  "    background: linear-gradient(45deg, #FF416C, #FF4B2B);\n"
                  "    color: white;\n"
                  "    font-weight: bold;\n"
                  "    box-shadow: 0 4px 15px rgba(255, 75, 43, 0.3);\n"
                  "    transform: scale(1.05);\n"
                  "}\n"
                  // ... rest of the styles remain the same ...
                  "</style>\n"
                  "</head>\n"
                  "<body>\n"
                  "<div class=\"container\">\n"
                  "<h1>Dijkstra's Shortest Path Visualization</h1>\n");

    // Create table visualization
    fprintf(file, "<table>\n");
    
    // Print column headers
    fprintf(file, "<tr><td></td>");
    for (int i = 0; i < nodes; i++) {
        fprintf(file, "<td>Node %d</td>", i + 1);
    }
    fprintf(file, "</tr>\n");

    // Print matrix with path highlighting
    for (int i = 0; i < nodes; i++) {
        fprintf(file, "<tr><td>Node %d</td>", i + 1);
        for (int j = 0; j < nodes; j++) {
            bool isInPath = false;
            for (int k = 0; k < pathLength - 1; k++) {
                if ((path[k] - 1 == i && path[k + 1] - 1 == j) ||
                    (path[k] - 1 == j && path[k + 1] - 1 == i)) {
                    isInPath = true;
                    break;
                }
            }

            if (isInPath) {
                fprintf(file, "<td class='path'>%.2f</td>", cost[i][j]);
            } else if (cost[i][j] == INF) {
                fprintf(file, "<td class='infinity'>&infin;</td>");
            } else if (cost[i][j] == 0 && i != j) {
                fprintf(file, "<td class='no-path'>-</td>");
            } else if (i == j) {
                fprintf(file, "<td class='no-path'>-</td>");
            } else {
                fprintf(file, "<td>%.2f</td>", cost[i][j]);
            }
        }
        fprintf(file, "</tr>\n");
    }
    fprintf(file, "</table>\n");

    // Print path information in a styled container
    fprintf(file, "<div class=\"path-info\">\n");
    fprintf(file, "<h2>Shortest Path</h2>\n<p>");
    for (int i = pathLength - 1; i >= 0; i--) {
        fprintf(file, "Node %d", path[i]);
        if (i > 0) fprintf(file, "<span class=\"path-arrow\">→</span>");
    }
    fprintf(file, "</p>\n");

    // Calculate and print total distance
    double totalDistance = 0;
    for (int i = 0; i < pathLength - 1; i++) {
        totalDistance += cost[path[i] - 1][path[i + 1] - 1];
    }
    fprintf(file, "<div class=\"total-distance\">Total Distance: %.2f</div>\n", totalDistance);
    fprintf(file, "</div>\n"); // Close path-info div

    fprintf(file, "</div>\n"); // Close container div
    fprintf(file, "</body>\n</html>");
    fclose(file);


    // Rest of the function remains the same...
    // ... (Path info and closing tags)

    fprintf(file, "</div>\n</body>\n</html>");
    fclose(file);

    #ifdef _WIN32
        system("start dijkstra_result.html");
    #endif
    printf("\nVisualization has been exported to 'dijkstra_result.html'\n");
}
