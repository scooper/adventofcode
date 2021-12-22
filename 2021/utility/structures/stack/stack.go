package stack

import (
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
