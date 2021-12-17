package main

import (
	utilities "adventofcode/utility/common"
	"fmt"
)

type fish struct {
	new        bool
	timer      int
	daySpawned int
}

var cache map[string]int

func iterateFishXDays(fishList []fish, days int) int {
	for d := 1; d <= days; d++ {
		var newFish []fish
		for i := 0; i < len(fishList); i++ {
			fishi := &fishList[i]
			switch fishi.timer {
			case 0:
				newFish = append(newFish, fish{true, 8, 0})
				fishi.new = false
				fishi.timer = 6
			default:
				fishi.timer--
			}
		}
		fishList = append(fishList, newFish...)
	}

	return len(fishList)
}

func iterateFishXDaysEfficientRecursive(fishList []fish, days int) int {
	numFish := 0

	for i := 0; i < len(fishList); i++ {
		fishi := &fishList[i]

		daysLeftForFish := days - fishi.daySpawned

		normaliseDays := (daysLeftForFish + 1) + (6 - fishi.timer)

		fishSpawned := normaliseDays / 7

		if normaliseDays%7 == 0 {
			fishSpawned -= 1
		}

		if fishSpawned <= 0 {
			continue
		}

		nextCycleForFish := fishi.daySpawned + (fishi.timer + 1)

		var childFishResult int
		key := fmt.Sprintf("%d-%d", fishi.daySpawned, fishi.timer)
		if val, found := cache[key]; found {
			childFishResult = val
		} else {
			childFishResult = iterateFishXDaysEfficientRecursive(makeNewFish(fishSpawned, nextCycleForFish, days), days)
			cache[key] = childFishResult
		}

		numFish += fishSpawned + childFishResult

	}

	return numFish
}

func iterateFishXDaysEfficient(fishList []fish, days int) int {

	cache = make(map[string]int)

	numFish := iterateFishXDaysEfficientRecursive(fishList, days)
	numFish += len(fishList)

	return numFish
}

func makeNewFish(amount int, initialSpawnDay int, days int) []fish {
	var newFish []fish
	for i := 0; i < amount; i++ {
		spawnDay := initialSpawnDay + (i * 7)
		if spawnDay > days {
			break
		}
		newFish = append(newFish, fish{true, 8, spawnDay})
	}

	return newFish
}

func main() {
	input, err := utilities.SplitFileByDelimiter("input", ",")

	utilities.CheckError(err)

	startingFishNums := utilities.StringSliceToIntSlice(input)

	var fishList []fish

	for _, startingFish := range startingFishNums {
		fishList = append(fishList, fish{false, startingFish, 0})
	}

	var fishList2 []fish
	fishList2 = make([]fish, len(fishList))
	copy(fishList2, fishList)

	days80 := 80
	days256 := 256

	fishNum := iterateFishXDays(fishList, days80)
	fmt.Printf("Num fish at %d with original algorithm: %d\n", days80, fishNum)

	efFISHent := iterateFishXDaysEfficient(fishList2, days256)
	fmt.Printf("Num fish at %d with efficient algorithm: %d\n", days256, efFISHent)
}
