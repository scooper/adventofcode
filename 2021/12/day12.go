package main

import (
	utilities "adventofcode/utility/common"
	"adventofcode/utility/structures/graph"
	"fmt"
	"strings"
)

type caveType int

const (
	caveTypeStart caveType = iota
	caveTypeEnd
	caveTypeSmall
	caveTypeBig
)

type cave struct {
	name string
	t    caveType
}

func getCaveType(input string) caveType {
	switch input {
	case "start":
		return caveTypeStart
	case "end":
		return caveTypeEnd
	default:
		if strings.ToLower(input) == input {
			return caveTypeSmall
		} else {
			return caveTypeBig
		}
	}
}

// graph search to find all paths
// returns slice of paths (slice of Nodes)
func getAllPaths(src *graph.Node, dst *graph.Node, g graph.Graph) [][]*graph.Node {

	paths := make([][]*graph.Node, 0)
	path := make([]*graph.Node, 0)
	visited := make(map[graph.Node]int)
	//

	dfsStorePaths(src, dst, &paths, visited, &path, g)

	return paths
}

func dfsStorePaths(current *graph.Node,
	dst *graph.Node,
	paths *[][]*graph.Node,
	visited map[graph.Node]int,
	path *[]*graph.Node,
	g graph.Graph) {

	// mark node visited
	visited[*current] += 1
	// add to current path
	*path = append(*path, current)
	pathLen := len(*path)
	if *current == *dst {
		newPath := make([]*graph.Node, len(*path))
		copy(newPath, *path)
		*paths = append(*paths, newPath)
	} else {
		connections := g.GetNodeConnections(current)
		for _, c := range connections {
			if _, found := visited[*c]; !found || c.Data.(cave).t == caveTypeBig {
				dfsStorePaths(c, dst, paths, visited, path, g)
			}
		}
	}

	// mark as unvisited
	delete(visited, *current)
	// remove end element
	if pathLen > 0 {
		*path = (*path)[:pathLen-1]
	}
}

func main() {
	input, err := utilities.ReadFileIntoSliceSplitString("input3", "-")

	utilities.CheckError(err)

	uniqueNodes := make(map[string]int)

	g := graph.NewGraph()

	for _, line := range input {
		caveA := cave{name: line[0], t: getCaveType(line[0])}
		a := &graph.Node{Data: caveA}
		if _, found := uniqueNodes[caveA.name]; !found {
			uniqueNodes[caveA.name]++
			g.AddNode(a)
		}

		caveB := cave{name: line[1], t: getCaveType(line[1])}
		b := &graph.Node{Data: caveB}
		if _, found := uniqueNodes[caveB.name]; !found {
			g.AddNode(b)
			uniqueNodes[caveB.name]++
		}

		g.AddEdge(a, b)
	}

	start := g.GetNodeWhere(func(data interface{}) bool {
		return data.(cave).t == caveTypeStart
	})

	end := g.GetNodeWhere(func(data interface{}) bool {
		return data.(cave).t == caveTypeEnd
	})

	allPaths := getAllPaths(start, end, g)

	for _, path := range allPaths {
		for _, n := range path {
			if *n == *end {
				fmt.Printf("%s", n.Data.(cave).name)
			} else {
				fmt.Printf("%s -> ", n.Data.(cave).name)
			}
		}
		fmt.Println()
	}

	fmt.Printf("%d paths found\n", len(allPaths))

	//g.Print(graph.NodeFormatInterface)
	// part 2: list of small caves, loop it, run the path algorithm each loop
	//         the selected small cave can be visited twice this iteration
	//         squash the results into one list (removing duplicates)

	allSmallCaves := g.GetNodesWhere(func(data interface{}) bool {
		return data.(cave).t == caveTypeSmall
	})

	fmt.Println(allSmallCaves)

}
