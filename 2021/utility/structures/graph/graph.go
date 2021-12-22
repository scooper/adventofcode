package graph

import (
	"fmt"
)

type Node struct {
	Data interface{}
}

type graph struct {
	nodes []*Node
	// key nodes are not pointers because even if it points
	// to the same node it might not be the same pointer
	edges map[Node][]*Node
}

type Graph interface {
	AddNode(n *Node)
	AddEdge(a *Node, b *Node)
	GetNodeConnections(n *Node) []*Node
	// gets the first node whose data evaluates to true though the predicate function
	GetNodeWhere(predicate func(data interface{}) bool) *Node
	GetNodesWhere(predicate func(data interface{}) bool) []*Node
	Print(nodeFormat func(data interface{}) string)
}

func (g *graph) AddNode(n *Node) {
	g.nodes = append(g.nodes, n)
}

func (g *graph) AddEdge(a *Node, b *Node) {
	g.edges[*a] = append(g.edges[*a], b)
	g.edges[*b] = append(g.edges[*b], a)
}

func (g *graph) GetNodeConnections(n *Node) []*Node {
	return g.edges[*n]
}

// gets the first node whose data evaluates to true though the predicate function
// 0(n) - has chance to complete early
func (g *graph) GetNodeWhere(predicate func(data interface{}) bool) *Node {
	for _, node := range g.nodes {
		if predicate(node.Data) {
			return node
		}
	}
	return nil
}

// gets all nodes whose data evaluates to true though the predicate function
// 0(n)
func (g *graph) GetNodesWhere(predicate func(data interface{}) bool) []*Node {
	var nodes []*Node
	for _, node := range g.nodes {
		if predicate(node.Data) {
			nodes = append(nodes, node)
		}
	}

	return nodes
}

func (g *graph) Print(nodeFormat func(data interface{}) string) {
	for _, n := range g.nodes {
		fmt.Printf("%s ->", nodeFormat(n.Data))
		for _, cn := range g.edges[*n] {
			fmt.Printf(" %s", nodeFormat(cn.Data))
		}
		fmt.Println()
	}
}

func NodeFormatInterface(data interface{}) string {
	return fmt.Sprintf("%v", data)
}

func NewGraph() Graph {
	return &graph{
		nodes: make([]*Node, 0),
		edges: make(map[Node][]*Node),
	}
}
