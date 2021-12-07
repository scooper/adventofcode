package main

import (
	utilities "adventofcode/utility"
	"fmt"
	"sort"
)

// give this a sorted list
func minimumSumOfDistancesBetweenAllPositionsSlow(positions []int, rateIncrease bool) int {
	minSum := -1
	testPosition := 0
	for testPosition <= positions[len(positions)-1] {
		tempSum := 0
		for i := 0; i < len(positions); i++ {
			diff := utilities.AbsI(positions[i] - testPosition)

			if rateIncrease {
				// not that much more complex to add rate increase
				tempSum += ((diff * (diff + 1)) / 2)
			} else {
				tempSum += diff
			}
		}

		resultSum := utilities.MinI(minSum, tempSum)

		if resultSum < 0 {
			minSum = tempSum
		} else {
			minSum = resultSum
		}

		testPosition++
	}

	return minSum
}

// give this a sorted list
func minimumSumOfDistancesBetweenAllPositions(positions []int) int {
	// get median
	median := positions[(len(positions)-1)/2]

	minSum := 0

	for _, pos := range positions {
		minSum += utilities.AbsI(pos - median)
	}

	return minSum
}

func main() {
	input, err := utilities.SplitFileByDelimiter("input", ",")

	utilities.CheckError(err)

	initialCrabPositions := utilities.StringSliceToIntSlice(input)

	// sort ascending
	sort.Slice(initialCrabPositions, func(i, j int) bool {
		return initialCrabPositions[i] < initialCrabPositions[j]
	})

	fmt.Printf("Min Fuel Used (Slow Approach): %d\n", minimumSumOfDistancesBetweenAllPositionsSlow(initialCrabPositions, false))
	fmt.Printf("Min Fuel Used (Fast Approach): %d\n", minimumSumOfDistancesBetweenAllPositions(initialCrabPositions))

	fmt.Printf("Min Fuel Used w/ Rate Increase (Slow Approach): %d\n", minimumSumOfDistancesBetweenAllPositionsSlow(initialCrabPositions, true))

	// part 2 notes:
	// instead of stepping through and adding 1 every time we can calculate the distance the same way
	// but use sum of 1 to n which is: (n(n+1))/2
}
