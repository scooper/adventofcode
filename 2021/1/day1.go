package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
)

func readFileIntoSlice(path string) ([]int, error) {
	file, err := os.Open(path)
	if err != nil {
		return nil, err
	}

	defer file.Close()

	var lines []int
	scanner := bufio.NewScanner(file)
	for scanner.Scan() {
		lineInt, err := strconv.Atoi(scanner.Text())
		if err != nil {
			return nil, err
		}
		lines = append(lines, lineInt)
	}

	return lines, scanner.Err()
}

func getNumOfDepthIncreases(depths []int) int {
	previous := -1
	var increasedCount int
	for _, depth := range depths {
		if previous != -1 {
			if depth > previous {
				increasedCount++
			}
		}
		previous = depth
	}
	return increasedCount
}

func getNumOfDepthIncreasesRollingWindow(depths []int, windowSize int) int {
	var depthSums []int

	for i := range depths {
		if (i + windowSize) > len(depths) {
			break
		}
		sum := 0
		for j := i; j < i+windowSize; j++ {
			sum += depths[j]
		}

		depthSums = append(depthSums, sum)
	}

	return getNumOfDepthIncreases(depthSums)
}

func main() {
	lines, err := readFileIntoSlice("input")

	if err != nil {
		panic(err)
	}

	fmt.Printf("Part 1: %d\n", getNumOfDepthIncreases(lines))
	fmt.Printf("Part 2: %d\n", getNumOfDepthIncreasesRollingWindow(lines, 3))

}
