package main

import (
	utilities "adventofcode/utility"
	"fmt"
	"sort"
)

var validOpenCloseMap = map[rune]rune{'{': '}', '[': ']', '(': ')', '<': '>'}
var syntaxErrorPointsMap = map[rune]int{')': 3, ']': 57, '}': 1197, '>': 25137}
var autocompletePointsMap = map[rune]int{')': 1, ']': 2, '}': 3, '>': 4}

type syntax_error struct {
	character   rune
	expected    rune
	position    int
	incomplete  bool
	stackAtTime stack
}

// maybe make this generic and put it in common area
type stack []rune

func (s *stack) Push(val rune) {
	*s = append(*s, val)
}

func (s *stack) Pop() (rune, bool) {
	stackSize := len(*s)
	if stackSize == 0 {
		return rune(0), true
	}

	popped := (*s)[stackSize-1]
	*s = (*s)[:stackSize-1]

	return popped, false
}

func (s *stack) Peek() (rune, bool) {
	stackSize := len(*s)
	if stackSize == 0 {
		return rune(0), true
	}

	return (*s)[stackSize-1], false
}

func (s *stack) Empty() bool {
	return len(*s) == 0
}

// gets the first error or incomplete stack, nil if no error
func checkErr(line string) *syntax_error {

	charStack := new(stack)

	for i, char := range line {
		if _, found := validOpenCloseMap[char]; found {
			charStack.Push(char)
		} else {

			popped, empty := charStack.Pop()

			// this case would mean incomplete opening characters
			// it doesn't apply in this challenge
			if empty {
				return nil
			}

			poppedClosing := validOpenCloseMap[popped]
			if poppedClosing != char {
				return &syntax_error{char, poppedClosing, i, false, nil}
			}
		}
	}

	// if we've ran out of characters and the stack is empty
	// it means no error
	if charStack.Empty() {
		return nil
	}

	// being here means having stuff left in the stack
	// which means no corresponding closing brackets
	return &syntax_error{rune(0), rune(0), -1, true, *charStack}
}

func main() {

	input, err := utilities.ReadFileIntoSliceString("input")

	utilities.CheckError(err)

	sumPointsCorrupt := 0
	var autocompletePointsPerLine []int
	for i, line := range input {
		syntax_err := checkErr(line)

		if syntax_err != nil {
			if !syntax_err.incomplete {
				fmt.Printf("%s: Error (CORRUPT) at line %d:%d, expected '%c' but found '%c'\n",
					line, i+1, syntax_err.position+1, syntax_err.expected, syntax_err.character)
				sumPointsCorrupt += syntaxErrorPointsMap[syntax_err.character]
			} else {
				fmt.Printf("%s: Error (INCOMPLETE) at line %d, stack: '%s'\n", line, i+1, string(syntax_err.stackAtTime))
				autocompletePoints := 0
				// pop stack, get matching bracket and calculate points
				for !syntax_err.stackAtTime.Empty() {
					popped, _ := syntax_err.stackAtTime.Pop()
					matchingClosing := validOpenCloseMap[popped]
					pointsForChar := autocompletePointsMap[matchingClosing]
					autocompletePoints = (autocompletePoints * 5) + pointsForChar
				}
				autocompletePointsPerLine = append(autocompletePointsPerLine, autocompletePoints)
			}
		}
	}

	sort.Ints(autocompletePointsPerLine)

	medianAutocompletePoints := autocompletePointsPerLine[len(autocompletePointsPerLine)/2]

	fmt.Printf("Sum of points for first illegal characters: %d\n", sumPointsCorrupt)
	fmt.Printf("Median of autocomplete scores: %d\n", medianAutocompletePoints)
}
