package structures

import (
	"fmt"
	"reflect"
)

func uniqueTypeString(t reflect.Type) string {
	return t.PkgPath() + "-" + t.Name()
}

func isSameType(v interface{}, t reflect.Type) bool {
	vType := reflect.TypeOf(v)
	if t != nil && uniqueTypeString(vType) != uniqueTypeString(t) {
		return false
	}
	return true
}

//
// Stack Code
//
type Stack interface {
	Push(interface{})
	Pop() interface{}
	Size() int
	Empty() bool
}

type stack struct {
	internalStack []interface{}
	dataType      reflect.Type
	unused        bool
}

func (s stack) Push(v interface{}) {
	if v == nil {
		panic("value pushed to stack is nil")
	}

	if s.unused {
		s.dataType = reflect.TypeOf(v)
		s.unused = false
	}

	if !isSameType(v, s.dataType) {
		panic("wrong type pushed to stack")
	}

	s.internalStack = append(s.internalStack, v)
}

func (s stack) Pop() interface{} {
	// nil for empty stack
	if s.Empty() {
		return nil
	}

	size := s.Size()
	popped := s.internalStack[size-1]
	s.internalStack = s.internalStack[:size-1]

	return popped
}

func (s stack) Size() int {
	return len(s.internalStack)
}

func (s stack) Empty() bool {
	return s.Size() == 0
}

func NewStack() Stack {
	return stack{
		internalStack: []interface{}{},
		unused:        true,
	}
}

//
// Matrix Code
//
type Matrix interface {
	Set(m int, n int, val interface{})
	Get(m int, n int) interface{}
	Size() (m, n int)
	GetIndicesOfNeighboursMeetingCondition(m, n int,
		includeDiagonals bool,
		condition func(original interface{}, neighbour interface{}) bool) map[string]interface{}
	GetIndicesOfNeighbours(m, n int, includeDiagonals bool) map[string]interface{}
}

type matrix [][]interface{}

func (mat matrix) Set(m int, n int, val interface{}) {
	mat[m][n] = val
}

func (mat matrix) Get(m int, n int) interface{} {
	return mat[m][n]
}

func (a matrix) Size() (m, n int) {

	m = len(a)
	if m > 0 {
		n = len(a[0])
	} else {
		n = 0
	}
	return
}

func (a matrix) GetIndicesOfNeighboursMeetingCondition(m, n int,
	includeDiagonals bool,
	condition func(original interface{}, neighbour interface{}) bool) map[string]interface{} {

	minM := 0
	minN := 0
	maxM, maxN := a.Size()

	neighbours := make(map[string]interface{})

	for subM := m - 1; subM <= m+1; subM++ {
		for subN := n - 1; subN <= n+1; subN++ {
			// matrix bounds
			if subN < minN || subN >= maxN || subM < minM || subM >= maxM {
				continue
			}

			// diagonals
			if (subM != m && subN != n) && !includeDiagonals {
				continue
			}

			// ignore the original coordinate
			if subM == m && subN == n {
				continue
			}

			o := a.Get(m, n)
			n := a.Get(subM, subN)

			if condition(o, n) {
				key := fmt.Sprintf("%d-%d", subM, subN)
				neighbours[key] = n
			}
		}
	}

	return neighbours
}

func (a matrix) GetIndicesOfNeighbours(m, n int, includeDiagonals bool) map[string]interface{} {
	return a.GetIndicesOfNeighboursMeetingCondition(m, n, includeDiagonals, func(original, neighbour interface{}) bool {
		return true
	})
}

// basically overlaying 2 matrices, you can choose how the values interact
// e.g int + int or float + float would make the most sense as a matrix
// but the intention is to be able to do what you like
func AddMatrices(a Matrix, b Matrix, add func(m, n int) interface{}) Matrix {
	ma, na := a.Size()
	mb, nb := b.Size()

	newMatrix := NewMatrix(ma, na)

	if ma != mb || na != nb {
		panic("matrices must be of the same dimensions")
	}

	for mi := 0; mi < ma; mi++ {
		for ni := 0; ni < na; ni++ {
			newMatrix.Set(mi, ni, add(mi, ni))
		}
	}

	return newMatrix
}

func AddIntMatrices(a Matrix, b Matrix) Matrix {
	return AddMatrices(a, b, func(m, n int) interface{} {
		return a.Get(m, n).(int) + b.Get(m, n).(int)
	})
}

// returns an initialised matrix
func NewMatrix(m, n int) Matrix {
	// initialise full matrix

	newMatrix := make([][]interface{}, m)

	for mi := 0; mi < m; mi++ {
		newMatrix[mi] = make([]interface{}, n)
	}

	return matrix(newMatrix)
}

func interfaceToInterfaceSlice(input interface{}) []interface{} {

	tK := reflect.TypeOf(input).Kind()

	if tK == reflect.Slice || tK == reflect.Array {
		output := make([]interface{}, 0)
		s := reflect.ValueOf(input)
		for i := 0; i < s.Len(); i++ {
			output = append(output, s.Index(i).Interface())
		}

		return output
	}

	return nil
}

func NewMatrixFromInput(input interface{}) Matrix {

	arr1D := interfaceToInterfaceSlice(input)

	arr2D := make([][]interface{}, 0)

	for i := 0; i < len(arr1D); i++ {
		arr2D = append(arr2D, interfaceToInterfaceSlice(arr1D[i]))
	}

	return matrix(arr2D)
}
