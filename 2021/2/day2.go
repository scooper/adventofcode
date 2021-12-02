package main

import (
	utilities "adventofcode/utility"
	"fmt"
	"strconv"
)

type submarine struct {
	horizontal int
	depth      int
	aim        int
}

func part1(instructions [][]string) {

	sub := submarine{horizontal: 0, depth: 0}

	for _, instruction := range instructions {
		direction := instruction[0]
		value, aotiErr := strconv.Atoi(instruction[1])

		utilities.CheckError(aotiErr)

		switch direction {
		case "forward":
			sub.horizontal += value
		case "up":
			sub.depth -= value
		case "down":
			sub.depth += value
		}
	}

	fmt.Printf("Part 1: Resulting Depth * Horizontal Position: %d\n", sub.depth*sub.horizontal)
}

func part2(instructions [][]string) {

	sub := submarine{horizontal: 0, depth: 0, aim: 0}

	for _, instruction := range instructions {
		direction := instruction[0]
		value, aotiErr := strconv.Atoi(instruction[1])

		utilities.CheckError(aotiErr)

		switch direction {
		case "forward":
			sub.horizontal += value
			sub.depth += sub.aim * value
		case "up":
			sub.aim -= value
		case "down":
			sub.aim += value
		}
	}

	fmt.Printf("Part 2 (w/ aim): Resulting Depth * Horizontal Position: %d\n", sub.depth*sub.horizontal)
}

func main() {

	instructions, fileReadErr := utilities.ReadFileIntoSliceSplitString("input", " ")

	utilities.CheckError(fileReadErr)

	part1(instructions)
	part2(instructions)

}
