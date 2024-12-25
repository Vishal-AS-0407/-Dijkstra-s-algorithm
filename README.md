# Dijkstra's Shortest Path Algorithm 🛣️

## Overview 📝

This C program implements **Dijkstra’s Shortest Path Algorithm**, which is a famous algorithm used to find the shortest paths between nodes in a graph. The program calculates the shortest distance between a source and a target node, given an adjacency matrix of weights. It also visualizes the result in an HTML format for easy understanding.

---

## Features ✨

- **Shortest Path Calculation**: Finds the shortest path between two nodes in the graph.
- **Adjacency Matrix Representation**: Displays the graph using an adjacency matrix.
- **Path Visualization**: Exports the shortest path and graph to a **beautiful HTML page**.
- **Easy to Use**: User-friendly interface to input the graph data and visualize the result.
- **Supports Infinity Representation**: Uses a predefined constant (`6969`) to represent infinity in the graph.

---

## Getting Started 🚀

### Prerequisites 📌

To run this program, you need a C compiler. Ensure you have the following installed:
- **GCC** (GNU Compiler Collection) or any C compiler.

---

### How to Run 🖥️

1. **Clone this repository**:
   ```bash
   git clone https://github.com/yourusername/dijkstra-algorithm.git
   cd dijkstra-algorithm
   ```

2. **Compile the code**:
   ```bash
   gcc -o dijkstra dijkstra.c
   ```

3. **Run the program**:
   ```bash
   ./dijkstra
   ```

4. Follow the on-screen prompts to enter the number of nodes, edge weights, source, and target nodes.

---

## How It Works 💡

1. **Input Graph Data**:
   - The graph is represented as an adjacency matrix.
   - You enter the number of nodes, and the program will prompt you to input the weights of the edges (or infinity for no path).

2. **Running Dijkstra's Algorithm**:
   - The algorithm will compute the shortest distance from the source node to the target node.
   - It will also calculate and display the shortest path.

3. **Output**:
   - The result will be displayed on the console and exported to an HTML file (`dijkstra_result.html`) for better visualization.

---

## Example

Here’s an example of the input and output:

**Input:**
```
Enter the number of nodes in the graph (up to 20): 5
Enter the weight of the path between nodes 1 and 2: 10
Enter the weight of the path between nodes 1 and 3: 15
...
Enter the source node (1-5): 1
Enter the target node (1-5): 5
```

**Output:**
```
Shortest path from 1 to 5:
1 -> 3 -> 5
Total distance: 25.00
```

Additionally, the program generates an **HTML file** that visualizes the graph and highlights the shortest path.

---

## HTML Output Preview 🌐

The HTML file will look like this:
![sample output](https://github.com/user-attachments/assets/abfc5361-f894-41d5-a2c4-285926f7d15f)


---


## Code Structure 📂

- **`main.c`**: The main driver code that accepts inputs and runs the algorithm.
- **`printGraph()`**: A helper function to display the adjacency matrix.
- **`dijkstra()`**: Implements Dijkstra’s algorithm to calculate the shortest path.
- **`exportToHTML()`**: Exports the graph and path to an HTML file for visualization.
- **`validateInput()`**: A helper function to validate user inputs for node numbers and edge weights.

---
### 🌟 **Show Your Support!**  

If you find this project helpful, give it a ⭐ on GitHub and share it with others! 😊  
