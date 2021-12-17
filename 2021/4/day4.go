package main

import (
	utilities "adventofcode/utility/common"
	"fmt"
	"strings"
)

type board struct {
	id      int
	grid    [][]int
	gridHit [][]bool
	won     bool
}

func printBoard(b *board) {
	fmt.Printf("--- Board ID: %2d ---\n", b.id)
	for row := 0; row < len(b.grid); row++ {
		for col := 0; col < len(b.grid[row]); col++ {
			if b.gridHit[row][col] {
				fmt.Printf("[%2d]", b.grid[row][col])
			} else {
				fmt.Printf("%3d ", b.grid[row][col])
			}
		}
		fmt.Printf("\n")
	}
	fmt.Printf("--------------------\n")
}

func checkNumOnBoard(b *board, number int) {
	for row := 0; row < len(b.grid); row++ {
		for col := 0; col < len(b.grid[row]); col++ {
			if b.grid[row][col] == number {
				b.gridHit[row][col] = true
			}
		}
	}
}

func getSumOfAllNumsNotHit(b *board) int {
	result := 0
	for row := 0; row < len(b.gridHit); row++ {
		for col := 0; col < len(b.gridHit[row]); col++ {
			if b.gridHit[row][col] == false {
				result += b.grid[row][col]
			}
		}
	}
	return result
}

func checkBoardForWin(b *board) {
	// check rows
	for row := 0; row < len(b.gridHit); row++ {
		rowResult := true
		// cycle elements in row, if our row result is still true then they must all be 'hits'
		for col := 0; col < len(b.gridHit[0]); col++ {
			rowResult = rowResult && b.gridHit[row][col]
		}
		if rowResult {
			b.won = true
			return
		}
	}

	// check columns
	for col := 0; col < len(b.gridHit[0]); col++ {
		colResult := true
		// cycle elements in row, if our row result is still true then they must all be 'hits'
		for row := 0; row < len(b.gridHit); row++ {
			colResult = colResult && b.gridHit[row][col]
		}
		if colResult {
			b.won = true
			return
		}
	}

	b.won = false
	return
}

func part1(boards []board, numbers []int) {
	won := false
	for _, number := range numbers {
		for i := 0; i < len(boards); i++ {
			// skip if already won
			if boards[i].won {
				continue
			}
			checkNumOnBoard(&boards[i], number)
			checkBoardForWin(&boards[i])
			if boards[i].won {
				sum := getSumOfAllNumsNotHit(&boards[i])
				fmt.Printf("Board: %d, Num Called: %d, Non-called Num Sum: %d, Multiplied: %d\n", boards[i].id, number, sum, number*sum)
				printBoard(&boards[i])
				won = true
				break
			}
		}
		if won {
			break
		}
	}
}

func part2(boards []board, numbers []int) {
	var winningBoard *board
	var numberCalledAtWin int
	// just cycle boards and store each winner
	// when the loop ends it should hold the last winner
	for _, number := range numbers {
		for i := 0; i < len(boards); i++ {
			// skip if already won
			if boards[i].won {
				continue
			}
			checkNumOnBoard(&boards[i], number)
			checkBoardForWin(&boards[i])
			if boards[i].won {
				winningBoard = &boards[i]
				numberCalledAtWin = number
			}
		}
	}

	sum := getSumOfAllNumsNotHit(winningBoard)
	fmt.Printf("Board: %d, Num Called: %d, Non-called Num Sum: %d, Multiplied: %d\n", winningBoard.id, numberCalledAtWin, sum, numberCalledAtWin*sum)
	printBoard(winningBoard)
}

func main() {
	input, err := utilities.SplitFileByDelimiter("input", "\n\n")

	utilities.CheckError(err)

	// make the boards and number list
	var numbers []int
	var boards []board
	for i, section := range input {
		if i == 0 {
			numbers = utilities.StringSliceToIntSlice(strings.Split(section, ","))
			continue
		}

		rows := strings.Split(section, "\n")
		var b board
		b.id = i
		b.grid = make([][]int, len(rows))
		b.gridHit = make([][]bool, len(rows))

		for i, row := range rows {
			b.gridHit[i] = make([]bool, len(rows))
			b.grid[i] = append(b.grid[i], utilities.StringSliceToIntSlice(strings.Fields(row))...)
		}

		boards = append(boards, b)
	}

	part1(boards, numbers)
	part2(boards, numbers)
}
