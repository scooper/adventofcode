package main

import (
	utilities "adventofcode/utility"
	"fmt"
)

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
	lines, err := utilities.ReadFileIntoSliceI("input")

	if err != nil {
		panic(err)
	}

	fmt.Printf("Part 1: %d\n", getNumOfDepthIncreases(lines))
	fmt.Printf("Part 2: %d\n", getNumOfDepthIncreasesRollingWindow(lines, 3))

}
